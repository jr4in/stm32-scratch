### Variables to play with
BUILD_DIR = build

C_FILES = src/startup.c \
	  src/main.c \
	  src/syscalls.c \
	  src/driver/hal_dev.c \
	  src/driver/hal_uart.c

### C Macros -D name=definition or -D name -U name
C_MACROS = 

### C Includes --include file
C_INCLUDES =-I include/


### Standard flags
C_FLAGS =-std=c11

### If debug enabled
C_FLAGS +=-g -gdwarf-2

### Optimization level
#C_FLAGS +=-Og

### Error flags
C_FLAGS +=-Wall -Wpedantic -Wextra -Wabi

### CPU FLAGS
C_FLAGS +=-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb

LD_SCRIPT = stm32f4.ld

.PHONY : clean debug


### Processing

OBJ_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(C_FILES)))
vpath %.c $(sort $(dir $(C_FILES)))

all: $(BUILD_DIR)/OUT/build.elf $(BUILD_DIR)/OUT/build.hex $(BUILD_DIR)/OUT/build.bin


$(BUILD_DIR)/OUT/build.elf: $(BUILD_DIR) $(OBJ_FILES) $(LD_SCRIPT) Makefile
	arm-none-eabi-gcc $(C_FLAGS) -T $(LD_SCRIPT) -nostartfiles -Wl,-Map=$(BUILD_DIR)/OUT/build.map -o $(BUILD_DIR)/OUT/build.elf -Wl,--gc-sections $(OBJ_FILES)

$(BUILD_DIR)/OUT/build.hex: $(BUILD_DIR)/OUT/build.elf
	arm-none-eabi-objcopy -O ihex $< $@

$(BUILD_DIR)/OUT/build.bin: $(BUILD_DIR)/OUT/build.elf
	arm-none-eabi-objcopy -O binary -S $< $@


$(BUILD_DIR): Makefile
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/OUT

$(BUILD_DIR)/%.o: %.c Makefile
	arm-none-eabi-gcc $(C_FLAGS) $(C_INCLUDES) -c $< -MMD -MF$(@:%.o=%.d) -MP -o $@
clean:
	rm -rf $(BUILD_DIR) compile_commands.json

debug: $(BUILD_DIR)/OUT/build.elf
	arm-none-eabi-gdb $(BUILD_DIR)/OUT/build.elf -ex "target extended-remote localhost:3333" -ex "monitor reset halt" -ex "load"

flash: $(BUILD_DIR)/OUT/build.bin
	st-flash erase
	st-flash write  $(BUILD_DIR)/OUT/build.bin 0x8000000


-include $(wildcard $(BUILD_DIR)/*.d)

