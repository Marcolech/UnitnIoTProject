FROM python:3.8

# container expose port 7000 udp for service
EXPOSE 7000/udp

# create and set working directory
RUN mkdir -p /opt/service
WORKDIR /opt/service

# add sourcecode and settings
ADD src .

#RUN pip install libraries
RUN pip install -r requirements.txt

CMD [ "python", "./main.py" ]
