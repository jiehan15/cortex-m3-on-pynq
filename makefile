
# Path of your compiler for Coretx-m3
CC = ./arm2gcc/bin/arm-none-eabi-gcc

# Path of all compiled files
BUILDS = ./builds

COPTS = \
	-march=armv7-m \
	-mcpu=cortex-m3 \
	-mthumb \
	-Os

CDEFS =

CFLAGS = $(COPTS) $(addprefix -D,$(CDEFS))

ASM_SRC = $(wildcard src/*.s)
C_SRC = $(wildcard src/*.c)

ASM_OBJ = $(ASM_SRC:%.s=$(BUILDS)/%.o)
C_OBJ = $(C_SRC:%.c=$(BUILDS)/%.o)

OBJS = $(ASM_OBJ) $(C_OBJ)

LD = ./arm2gcc/bin/arm-none-eabi-ld
LINKER_SCRIPT = link.ld

ELF = m3.elf
BIN = $(basename $(ELF)).bin
DUMP = dump.txt

# RULES
.DEFAULT_GOAL:=all

$(BUILDS):
	@mkdir -p $@

$(BUILDS)/%.o: %.c | $(BUILDS)
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $< -c -o $@

$(BUILDS)/%.o: %.s | $(BUILDS)
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $< -c -o $@

$(ELF): $(OBJS) $(LINKER_SCRIPT)
	$(CC) -T $(LINKER_SCRIPT) -o $(ELF) -nostdlib $(OBJS)

OBJDUMP = ./arm2gcc/bin/arm-none-eabi-objdump
OBJCOPY = ./arm2gcc/bin/arm-none-eabi-objcopy

.PHONY: all clean
all: $(ELF)
	$(OBJDUMP) -D $(ELF) > $(DUMP)
	$(OBJCOPY) -O binary $(ELF) $(BIN)

clean:
	rm -rf $(BUILDS)
	rm -rf $(ELF) $(BIN)
	rm -rf $(DUMP)
