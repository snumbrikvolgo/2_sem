extern _Asum

global _sum:
section .text

_sum:
    push rbp
    mov rbp, rsp

    call _Asum

    pop rbp

    ret
