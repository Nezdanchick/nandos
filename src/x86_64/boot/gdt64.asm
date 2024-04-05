global gdt64.pointer
global gdt64.code_segment

section .rodata
gdt64:
	dq 0	; entry
.code_segment equ $ - gdt64
	dq (1 << 41) | (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)
.data_segment equ $ - gdt64
	dq (1 << 41) | (1 << 44) | (1 << 47)
.pointer:
	dw $ - gdt64 - 1
	dq gdt64