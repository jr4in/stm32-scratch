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
C_INCLUDES = 


### Standard flags
C_FLAGS = -std=c11

### If debug enabled
C_FLAGS += --debug

### Optimization level
C_FLAGS += --debug

### Error flags
C_FLAGS += -Wall -Wpedantic -Wextra -Wabi -Waggregate-return -Walloc-zero -Walloca -Wauto-profile -Wc11-c23-compat -Wc23-c2y-compat -Wc++-compat -Wcannot-profile -Wcast-align -Wcast-qual -Wcompare-distinct-pointer-types -Wconversion -Wdate-time -Wdisabled-optimization -Wdouble-promotion -Wduplicated-branches -Wduplicated-cond -Wflex-array-member-not-at-end -Wfloat-conversion -Wfloat-equal -Wformat=2 -Wformat-signedness -Whardened -Wimplicit -Winline -Winvalid-pch -Winvalid-utf8 -Wjump-misses-init -Wkeyword-macro -Wlogical-op -Wlong-long -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wmusttail-local-addr -Wmaybe-musttail-local-addr -Wnull-dereference -Wopenacc-parallelism -Wopenmp -Woverlength-strings -Wpacked -Wpadded -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wstack-protector -Wswitch-default -Wswitch-enum -Wsync-nand -Wsystem-headers -Wtrailing-whitespace -Wtrampolines -Wtrivial-auto-var-init -Wno-tsan -Wundef -Wunsuffixed-float-constants -Wunused-function -Wunused-macros -Wunused-result -Wunused-value -Wunused-variable -Wuseless-cast -Wvariadic-macros -Wvector-operation-performance -Wvla -Wwrite-strings -Wzero-as-null-pointer-constant

INCLUDES = includes/

LD_SCRIPT = stm32f4.ld

.PHONY : clean


### Processing

OBJ_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(C_FILES)))
vpath %.c $(sort $(dir $(C_FILES)))

all:  $(BUILD_DIR) $(OBJ_FILES) $(LD_SCRIPT)
	arm-none-eabi-gcc -T $(LD_SCRIPT) $(OBJ_FILES) -o $(BUILD_DIR)/OUT/build.elf 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/OUT

$(BUILD_DIR)/%.o: %.c
	arm-none-eabi-gcc $(C_FLAGS) -c $< -MMD -MF$(subst %.o,%.d,$@) -MP  -o $@
clean:
	rm -rf $(BUILD_DIR) compile_commands.json
