GLOBAL run
GLOBAL gdbme
section .text

run:
    mov eax,50
    ret

gdbme:
    push rbp
    mov rbp, rsp

    mov rax, 0xCACAC0DE
    cmp rax, 0x12345678
    je success

    mov rax, 0

    mov rsp, rbp
    pop rbp    

    ret


success: 
    mov rax, 1

    mov rsp, rbp
    pop rbp  

    ret



section .RUN_ME
    sqlito dq 69

