; assembly code

section .text
bits 64
default rel ; support address relocation and relativity

global calc1D_Stencil_asmfunc
extern printf
; vectorX -> [RCX], vectorY -> [RDX], size -> R8
calc1D_Stencil_asmfunc: 
    push rsi
    push rbx
    push r12
    push r13
    push rbp 
    mov rbp, rsp
    add rbp, 16
    add rbp, 32 ; +32 for 4 additional pushes (rsi, rbx, r12, and r13)
        xor rax, rax    ; return integer
        xor rbx, rbx    ; initialize for int i in for loop 
        xor r13, r13    ; for vectorY reference
        xor r12, r12    ; for vectorX indexing
        xor r11, r11    ; for vectorY indexing (yIndex)
        xor r10, r10    ; initialize for limit variable in code: limit = size - 3;
        add r10, r8     ; limit = limit + size
        sub r10, 3      ; limit = limit - 3
        lea rsi, [rcx]
        lea r13, [rdx]
        

        mov rbx, 3      ; i = 3
        
    L1:
        CMP RBX, R10
        JE END
        
        pxor xmm4, xmm4 ; 
        addsd xmm4, [rsi + 8*(rbx-3)]
        addsd xmm4, [rsi + 8*(rbx-2)]
        addsd xmm4, [rsi + 8*(rbx-1)]
        addsd xmm4, [rsi + 8*(rbx)]
        addsd xmm4, [rsi + 8*(rbx+1)]
        addsd xmm4, [rsi + 8*(rbx+2)]
        addsd xmm4, [rsi + 8*(rbx+3)]
        
        movsd [r13 + 8*r11], xmm4
        INC R11
        INC RBX
        JMP L1
    
    END:
        mov rax, 1  ; 1 if function was successful
        pop rbp
        pop r13
        pop r12
        pop rbx
        pop rsi
        ret
    
    

