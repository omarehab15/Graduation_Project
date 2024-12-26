#Prepared by Eng: Omar Ehab (Learn in depth)
CC =arm-none-eabi-
CFLAGS = -mcpu=cortex-m4 -gdwarf-2 -g
INCS =-I .
LIBS =
SRC =$(wildcard *.c)
OBJ =$(SRC:.c=.o)
AS =$(wildcard *.s)
ASOBJ =$(AS:.s=.o)
project_name =unit4_lab4_cortexM4

all: $(project_name).bin
	@echo "======== build is done ========"


%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS)  $< -o $@

$(project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS)  $(OBJ) $(ASOBJ) -o $@ -Map=Map_file.map
	cp $(project_name).elf $(project_name).axf

$(project_name).bin: $(project_name).elf
	$(CC)objcopy.exe -O binary $< $@
clean_all:
	rm  *.o *.elf *.map *.bin
clean:
	rm *.elf *.bin