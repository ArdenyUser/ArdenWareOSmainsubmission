sudo apt-get update -y
apt install binutils
apt install gcc
apt install unzip
apt install nasm
sudo apt-get install -y nasm
nasm -f aout -o start.o start.asm


gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o scrn.o scrn.c

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o gdt.o gdt.c

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o idt.o idt.c

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o isrs.o isrs.c

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o irq.o irq.c

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o timer.o timer.c

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o keyboard.o keyboard.c

gcc  -g test1.c path.c inode.c super.c cache.c filedes.c myfs.c ./socket/client.c -o filesystem.o

ld -T linker.ld -o kernel.bin start.o main.o scrn.o gdt.o idt.o isrs.o irq.o timer.o keyboard.o filesystem.o

