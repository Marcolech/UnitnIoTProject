C_VERSION		:= c99
# TODO change here with the path to your gcc compiler
GCC_BIN_DIR		:= {TI_INSTALLATION_DIR}/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major/bin/
CC = $(GCC_BIN_DIR)arm-none-eabi-gcc
LD = $(GCC_BIN_DIR)arm-none-eabi-gcc

# COMPILER
CC_FLAGS = \
-std=$(C_VERSION) \
-mcpu=$(TARGET_CPU) \
-march=$(TARGET_ARCH) \
-mfloat-abi=$(TARGET_FLOAT_HARDWARE) \
-mfpu=$(TARGET_FLOAT_FORMAT) \
-D$(TARGET_SYMBOL_BOARD) \
-D$(TARGET_SYMBOL_FAMILY) \
-mthumb \
-ffunction-sections \
-fdata-sections \
-g \
-gdwarf-3 \
-gstrict-dwarf \
-Wall \
-MMD \
-MP

CC_INCLUDE_FLAGS = $(addprefix "-I", $(CC_INCLUDE))


# LINKER
LD_FLAGS = \
-D$(TARGET_SYMBOL_BOARD) \
-D$(TARGET_SYMBOL_FAMILY) \
-march=$(TARGET_ARCH) \
-mfloat-abi=$(TARGET_FLOAT_HARDWARE) \
-mfpu=$(TARGET_FLOAT_FORMAT) \
-Wl,-T"$(LDS_FILE)" \
-Wl,-Map,"$(MAP_FILE)" \
-ffunction-sections \
-fdata-sections \
-g \
-gdwarf-3 \
-gstrict-dwarf \
-Wall \
-mthumb \
-static \
-Wl,--gc-sections \
--specs=nano.specs \
-lgcc \
-lc \
-lm \
-lnosys

# -L folder path to the compiled files
# -l filename
LD_INCLUDE_FLAGS = \
-L"$(dir $(DRIVER_LIB_BINARY_FILE))" \
-l:"$(notdir $(DRIVER_LIB_BINARY_FILE))"

