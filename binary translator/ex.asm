
          global    _start

          section   .text
_start:
        ;mov rbp, rsp
        ;sub rsp, 1024d

        mov rax, 60
        xor rdi, rdi
        syscall
