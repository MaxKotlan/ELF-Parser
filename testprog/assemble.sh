nasm -f elf32 test.asm -o test32.o
ld -m elf_i386 -o test32 test32.o

#nasm -f elf64 test.asm -o test64.o
#ld -m elf_x86_64 -o test64 test64.o