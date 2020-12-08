bcc -ansi -c -o kernel.o kernel.c
as86 os-api.asm -o os-api.o
ld86 -o shell -d shell.o os-api.o
dd if=syscall-test of=floppya.img bs=512 count=1 seek=11 conv=notrunc