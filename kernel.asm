section .text
bits 64
default rel

global vec_product_asm
vec_product_asm:
    ; Function to calculate dot product (sum of element-wise products)
    ; Arguments (Windows x64 calling convention):
    ; RCX: vec1 pointer (float*)
    ; RDX: vec2 pointer (float*)
    ; R8: result pointer (float*) - where to store the single sum result
    ; R9: length (int)

    MOV R10, RCX                ; R10 = vec1 base address
    MOV R11, RDX                ; R11 = vec2 base address
    MOV R12, R8                 ; R12 = result pointer
    MOV EAX, R9D                ; EAX = length (int)

    ; Initialize sum to 0
    XORPS XMM2, XMM2            ; XMM2 = running sum (initialized to 0)
    XOR RCX, RCX                ; RCX = loop counter

.loop:
    CMP RCX, RAX                ; if (i >= length) break;
    JGE .done

    ; Load vec1[i] and vec2[i]
    MOVSS XMM0, [R10 + RCX * 4] ; Load vec1[i]
    MOVSS XMM1, [R11 + RCX * 4] ; Load vec2[i]

    ; Multiply: vec1[i] * vec2[i]
    MULSS XMM0, XMM1

    ; Add to running sum: sum += (vec1[i] * vec2[i])
    ADDSS XMM2, XMM0

    ; i++
    INC RCX
    JMP .loop

.done:
    ; Store the final sum result
    MOVSS [R12], XMM2
    RET