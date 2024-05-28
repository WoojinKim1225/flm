.section .text
.global _start
_start:
call main
mov %eax, %ebx
mov $1, %eax
syscall

.global main
main:
mov $2, %eax
ret
