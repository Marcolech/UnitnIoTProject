LDS_FILE 				= $(CONFIG_DIR)/msp432p401r.lds
DRIVER_LIB_BINARY_FILE 	= $(LIB_DIR)/msp432_driverlib/driverlib/MSP432P4xx/gcc/msp432p4xx_driverlib.a

# Add here libraries path to include
CC_INCLUDE = \
$(SRC_DIR) \
$(SRC_DIR)/board \
$(LIB_DIR)/msp432_driverlib/driverlib/MSP432P4xx \
$(LIB_DIR)/msp432_driverlib/inc \
$(LIB_DIR)/msp432_driverlib/inc/CMSIS