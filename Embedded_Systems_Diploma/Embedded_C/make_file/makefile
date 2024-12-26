#Prepared by Eng: Omar Ehab (Learn in depth)
CC =arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -gdwarf-2
INCS =-I .
LIBS =
SRC =$(wildcard *.c)
OBJ =$(SRC:.c=.o)
AS =$(wildcard *.s)
ASOBJ =$(AS:.s=.o)
project_name =learn-in-depth-cortexM4

all: $(project_name).hex
	@echo "======== build is done ========"
startup.o:startup.s
	$(CC)as.exe $(CFLAGS) $< -o $@ 
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS)  $< -o $@
$(project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS)  $(OBJ) $(ASOBJ) -o $@ -Map=m_file.map
$(project_name).hex: $(project_name).elf
	$(CC)objcopy.exe -O binary $< $@
clean_all:
	rm  *.o *.elf *.map *.hex
clean:
	rm *.elf *.bin