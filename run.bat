nasm -f win64 kernel.asm
gcc -c main.c -o main.c.obj -m64
gcc -c dot_product_c.c -o dot_product_c.obj -m64
gcc main.c.obj dot_product_c.obj kernel.obj -o main.exe -m64
main.exe
pause
