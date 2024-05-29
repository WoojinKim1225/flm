.section .text
.globl _start
_start:
call main
mov %eax, %ebx
mov $1, %eax
int $0x80

.globl main
main:
mov $0, %eax
ret
