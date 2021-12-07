gcc src/memory.c  src/basic.c  kernel.c src/io.c src/keyboard/ps2.c src/acpi.c src/pci.c -ffreestanding -nostdlib -O2 -Wall -Wextra -T linker.ld -o kernel.elf
