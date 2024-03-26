; assembly code

section .text
	bits 64
	default rel ; support address relocation and relativity

global calc1D_Stencil_asmfunc
extern printf
; vectorX -> [RCX], vectorY -> [RDX], size -> R8
calc1D_Stencil_asmfunc:
    
    push rsi
    push rbp 
    mov rbp, rsp
    add rbp, 16
        xor rbx, rbx    ; initialize for int i in for loop 
        xor r12, r12    ; for vectorX indexing
        xor r11, r11    ; for vectorY indexing (yIndex)
        xor r10, r10    ; initialize for limit variable in code: limit = (size - 6) + 3;
        add r10, r8     ; limit = limit + size
        sub r10, 3      ; limit = limit - 3

        mov rbx, 3      ; i = 3
        
    L1:
        CMP RBX, R10
        JE END
        
        pxor xmm4, xmm4 ; 
        addsd xmm4, [rcx + 8*(rbx-3)]
        addsd xmm4, [rcx + 8*(rbx-2)]
        addsd xmm4, [rcx + 8*(rbx-1)]
        addsd xmm4, [rcx + 8*(rbx)]
        addsd xmm4, [rcx + 8*(rbx+1)]
        addsd xmm4, [rcx + 8*(rbx+2)]
        addsd xmm4, [rcx + 8*(rbx+3)]
        
        movsd [rdx + 8*r11], xmm4
        INC R11
        INC RBX
        JMP L1
    
    END:
        pop rbp
        pop rsi
        ret
    
    

