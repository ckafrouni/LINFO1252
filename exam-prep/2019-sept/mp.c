// mp:
//   subl $8, %esp
//   movl 16%(esp), %edx
//   movl 12%(esp), %ecx
//   movl %ecx,%eax
//   addl %ecx,%ecx
//   addl %eax,%ecx
//   cmpl %edx,%ecx
//   jle mZ
//   movl %edx, %eax
//   addl $8, %esp
//   ret
// mZ:
//   movl %ecx, %eax
//   addl $8, %esp
//   ret

int mp(int d, int c)
{
    c *= 3;
    // if (d <= c)
    // {
    //     return c;
    // }
    // return d;
    return d <= c ? c : d;
}
