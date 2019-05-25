; ----------------------------------------------------------------
;
;   boot.s -- Kernel
;
; ----------------------------------------------------------------

;-----------------------------------------------------------------------------

; GRUB Multiboot header
; Ref: https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-layout

; field 'magic': the magic number identifying the header
MBOOT_HEADER_MAGIC  equ     0x1BADB002

; bit 0 in field 'flags': aligned on page (4KB) boundaries
MBOOT_PAGE_ALIGN    equ     1 << 0

; bit 1 in field 'flags': 
; available memory via at least the ‘mem_*’ fields of the Multiboot information structure must be included
MBOOT_MEM_INFO      equ     1 << 1    

; Multiboot header
MBOOT_HEADER_FLAGS  equ     MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO

; field 'checksum': 
; when added to the other magic fields, must have a 32-bit unsigned sum of zero.
MBOOT_CHECKSUM      equ     -(MBOOT_HEADER_MAGIC+MBOOT_HEADER_FLAGS)

;-----------------------------------------------------------------------------

[BITS 32]   ; 32-bit asm
section .text   ; code section

; Define the GRUB multiboot header
dd MBOOT_HEADER_MAGIC
dd MBOOT_HEADER_FLAGS
dd MBOOT_CHECKSUM

[GLOBAL start]      ; declare the code entry to the linker
[GLOBAL glb_mboot_ptr]  ; declare the global pointer of the multiboot information structure
[EXTERN kern_entry]     ; declare the entry function of the C kernel

start:
    cli              ; no interrupt handling in protected mode, close the interrupt

    mov esp, STACK_TOP       ; set the kernel stack addr
    mov ebp, 0       ; set stack pointer to 0
    and esp, 0FFFFFFF0H  ; aligned the stack addr on 16-bit
    mov [glb_mboot_ptr], ebx ; move the struct pointer to ebx
    call kern_entry      ; call the kernel entry C function
stop:
    hlt              ; halt
    jmp stop         ; loooooooooop...

;-----------------------------------------------------------------------------

section .bss             ; unintialized global data section
stack:
    resb 32768       ; kernel stack
glb_mboot_ptr:           ; global pointer of the multiboot information structure
    resb 4

STACK_TOP equ $-stack-1      ; the top of the stack, use $ to get the addr of the variable
