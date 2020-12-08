nasm bootload.asm
dd if=/dev/zero of=floppya.img bs=512 count=2880
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
bcc -ansi -c -o kernel.o kernel.c
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o kernel_asm.o
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3
dd if=message.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc
dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc
gnome-terminal -e "./fuse-smallfs/bin/sfs floppya.img sfs_root/ -f -s"
sleep 2
            cp message.txt sfs_root/
            cp test.c sfs_root/
            cp syscall-test sfs_root/
            cp shell sfs_root/
            cp os-api.asm sfs_root/
dd if=map.img of=floppya.img bs=512 count=1 seek=11 conv=notrunc
c | bochs -f ./bochsrc-2.6.9.bxrc
rm *.o
fusermount -u sfs_root