####################################
##        CONFIGURATION           
####################################

DEBUG = 1

## Device configuration
FLASH_ADDRESS = 0x08000000      # Flash memory address
DEVICE = STM32F103RB            # Target device
INTERFACE = SWD                 # Interface type
SPEED = 4000                    # Speed in kHz

## Path and filename definitions
NAME = hello

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj/
BIN_DIR = $(BUILD_DIR)/bin/
SCRIPT_DIR = scripts

ELF = $(BIN_DIR)$(NAME).elf
BIN = $(BIN_DIR)$(NAME).bin

CODE_DIRS= ./src ./drivers/src/
INC_DIRS= ./inc ./drivers/inc/

## Compiler and linker settings
# toolchain
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
NM = arm-none-eabi-nm


# warnings
WAR_FLAGS = -W -Wall -Wextra -Werror -Wshadow -Wdouble-promotion -Wundef -fno-common -Wformat-truncation -Wconversion

# debug build: max debug info, zero optimization
DEBUG_FLAGS = -g3 -O0

# production build: no debug info, max size-optimization
PROD_FLAGS = -Os

# common: 
# -ffunction-sections -fdata-sections: don't include unused code and data
# -ffreestanding: no operating system
# -c: don't link
COMMON_FLAGS = -ffunction-sections -fdata-sections -ffreestanding -c

# processor specific flags
ARM_FLAGS = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft

# generate .d dependency files (containes list of header files that .c depends on)
# this way if the .h file changes the .c file will recompile
DEP_FLAGS = -MP -MD

# all flags for compilation
CFLAGS = $(WAR_FLAGS) $(ARM_FLAGS) $(DEP_FLAGS) $(COMMON_FLAGS) $(foreach D, $(INC_DIRS), -I$(D))
ifeq ($(DEBUG), 1)
	CFLAGS += $(DEBUG_FLAGS)
else	
	CFLAGS += $(PROD_FLAGS)
endif

# all flags for linking
# -Tlink.ld: use custom link.ld linker script
# -Wl,: pass option to the linker
# -Map=$@.map: create map file called <target>.map
# -nostdlib: don't link c startup file (crt0.o) and and standard libraries
LDFLAGS ?= -Tlinker.ld $(ARM_FLAGS) -Wl,-Map=$@.map -nostdlib

## Creating full names for objectfiles and dependency files 
# list of all C files
C_FILES = $(foreach D,$(CODE_DIRS),$(wildcard $(D)*.c))
# generate path for dependeny and object files
# notdir: remove dir prefix
OBJ_FILES = $(addprefix $(OBJ_DIR), $(patsubst %.c,%.o,$(notdir $(C_FILES))))
DEP_FILES = $(addprefix $(OBJ_DIR), $(patsubst %.c,%.d,$(notdir $(C_FILES))))



################################################
##                 RECIPES
################################################
# $< : first dependency
# $^ : all dependency
# $@ : target

## Creating executable
all: $(BUILD_DIR) $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) $(OBJ_DIR) $(BIN_DIR)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@
	
# linking object files
$(ELF): $(OBJ_FILES) 
	$(CC) $(LDFLAGS) $^ -o $@ 

# rule for creating object files
# include the dependencies but don't generate an error if they don't exist (-)
# dependency files (.d) track which source files depend on which headers
-include $(DEP_FILES)

# only want the .c file dependency here, thus $< instead of $^.
$(OBJ_DIR)%.o:drivers/src/%.c
	$(CC) $(CFLAGS) $< -o $@ 

$(OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) $< -o $@ 



## Analyzing






## Flashing

# flashing if the programmer runs st firmware
stflash: $(BIN)
	@echo "flashing with st..."
	st-flash --reset write $< $(FLASH_ADDRESS)

# flashing if the programmer runs jlink firmware
jflash: flash_script.jlink
	@echo "flashing with jlink..."
	JLinkExe -CommanderScript flash_script.jlink

# Create the J-Link script file
flash_script.jlink: $(BIN)
	@touch $@
	@echo "device $(DEVICE)" > $@
	@echo "if $(INTERFACE)" >> $@
	@echo "speed $(SPEED)" >> $@
	@echo "loadbin $< $(FLASH_ADDRESS)" >> $@
	@echo "r" >> $@
	@echo "g" >> $@ 
	@echo "qc" >> $@ 

# Cleaning up
clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all