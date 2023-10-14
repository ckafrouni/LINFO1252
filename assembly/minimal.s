
.text

.globl _start

_start:

    # Exit syscall
    movl $1, %eax  # syscall number for sys_exit
    movl $0x0, %ebx  # exit code
    int $0x80      # invoke syscall
