import socket
import json
import paho.mqtt.client as mqtt


def start_udp_server(ip: str = "0.0.0.0", port: int = 7000, broker_ip: str = "127.0.0.1", broker_port: int = 7000,
                     buffer_size: int = 2048):
    # Create a datagram socket and bind ip:port
    udp_server_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    udp_server_socket.bind((ip, port))

    print(f"UDP server up and listening {ip}:{port}")

    while True:
        bytes_address_pair = udp_server_socket.recvfrom(buffer_size)

        message = bytes_address_pair[0]
        address = bytes_address_pair[1]

        print(f"Client {address} message: {message}")
        try:
            json_message = json.loads(message)
            print(f"Site: {json_message['site']}\tfield: {json_message['field']}\tvalue: {json_message['value']}")

            mqtt_send_message(broker_ip, broker_port, "middleware", "sensors",
                              f"{json_message['field']},site={json_message['site']} value={json_message['value']}")
        except ValueError:
            print(f"{address} invalid message: {message}")
        # Send a reply to client
        udp_server_socket.sendto(str.encode(str(message).upper()), address)


# Read the conf.json and return the fields
def read_config_file(path):
    file = open(path, 'r').read()
    return json.loads(file)


def mqtt_send_message(broker_ip: str, broker_port: int, client_id: str, topic, payload):
    client = mqtt.Client(client_id=client_id)
    client.connect(broker_ip, broker_port)
    client.publish(topic, payload)
    client.disconnect()


if __name__ == '__main__':
    print("Running..")
    config = read_config_file("config/config.json")
    start_udp_server(config["listenIp"], config["listenPort"], config["brokerIp"], config["brokerPort"], 2048)
