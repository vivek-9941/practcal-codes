; ---------- MACROS ----------
%macro IO 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

; ---------- DATA ----------
section .data
    menu: db "MENU for conversion: ",10
          db "1. BCD to Hex",10
          db "2. Hex to BCD",10
          db "3. Exit",10
    menulen equ $-menu

    cho: db "Enter your choice: "
    lenc equ $-cho

    msg: db " ",10
    len equ $-msg

    msg1: db "Enter the number: "
    len1 equ $-msg1

    res1: db "Result: "
    lres equ $-res1

    arr dd 10000, 1000, 100, 10, 1   ; Array for BCD weights (32-bit)

; ---------- BSS ----------
section .bss
    disparr resb 16       ; Buffer for displaying hex results
    choice resb 2         ; User's menu choice
    num resb 6            ; Buffer for user input (5 digits + newline)
    res resq 1            ; 64-bit result storage

; ---------- TEXT ----------
section .text
    global _start

_start:
    ; Main menu loop
menu_label:
    IO 1, 1, menu, menulen    ; Display menu
    IO 1, 1, cho, lenc        ; Prompt for choice
    IO 0, 0, choice, 2        ; Read choice

    cmp byte [choice], '1'
    je bcd_hex
    cmp byte [choice], '2'
    je hex_bcd
    cmp byte [choice], '3'
    je exit
    jmp menu_label            ; Invalid choice, loop back

; ---------- BCD to HEX Conversion ----------
bcd_hex:
    IO 1, 1, msg1, len1       ; Prompt for number
    IO 0, 0, num, 6           ; Read 5-digit BCD + newline

    mov rsi, num               ; Point to input
    xor rax, rax               ; Clear RAX (stores result)
    mov rcx, 5                 ; Loop counter (5 digits)
    mov rbx, arr               ; Point to BCD weights

convert_bcd_loop:
    xor rdx, rdx               ; Clear RDX
    mov dl, [rsi]              ; Read ASCII digit
    sub dl, '0'                ; Convert to binary
    imul rax, rax, 10          ; RAX *= 10
    add rax, rdx               ; RAX += digit
    inc rsi                    ; Next digit
    loop convert_bcd_loop

    ; Store result and display
    mov [res], rax
    IO 1, 1, res1, lres        ; "Result: "
    call display_hex           ; Display in hex
    IO 1, 1, msg, len          ; Newline
    jmp menu_label             ; Back to menu

; ---------- HEX to BCD Conversion ----------
hex_bcd:
    IO 1, 1, msg1, len1        ; Prompt for number
    IO 0, 0, num, 5            ; Read 4-digit hex + newline

    ; Convert ASCII hex to binary
    mov rsi, num
    call ascii_hex_to_bin
    mov [res], rax             ; Store hex value

    ; Convert to BCD
    mov rax, [res]
    mov rbx, 10                ; Divisor for BCD
    mov rcx, 0                 ; Digit counter
    mov rsi, disparr + 15      ; End of buffer (write backwards)

bcd_convert_loop:
    xor rdx, rdx               ; Clear RDX for division
    div rbx                    ; RAX = quotient, RDX = remainder (digit)
    add dl, '0'                ; Convert digit to ASCII
    mov [rsi], dl              ; Store in buffer
    dec rsi                    ; Move buffer pointer back
    inc rcx                    ; Increment digit count
    test rax, rax              ; Check if quotient is zero
    jnz bcd_convert_loop       ; If not, continue

    ; Display BCD result
    IO 1, 1, res1, lres        ; "Result: "
    inc rsi                    ; Point to first digit
    mov rdx, rcx               ; Number of digits
    IO 1, 1, rsi, rdx          ; Display BCD digits
    IO 1, 1, msg, len          ; Newline
    jmp menu_label             ; Back to menu

; ---------- Helper Functions ----------
ascii_hex_to_bin:
    xor rax, rax               ; Clear RAX
hex_loop:
    movzx rdx, byte [rsi]      ; Load next ASCII char
    test rdx, rdx              ; Check for null terminator
    jz hex_done
    cmp rdx, '9'               ; Check if digit or letter
    jbe digit
    sub rdx, 'A' - 10          ; Convert A-F to 10-15
    jmp shift_add
digit:
    sub rdx, '0'               ; Convert 0-9 to binary
shift_add:
    shl rax, 4                 ; Shift left by 4 bits
    add rax, rdx               ; Add new digit
    inc rsi                    ; Next char
    jmp hex_loop
hex_done:
    ret

display_hex:
    mov rsi, disparr + 15      ; End of buffer
    mov byte [rsi], 0          ; Null terminator
    mov rcx, 16                ; Max 16 hex digits
    mov rbx, [res]             ; Load value to display
hex_display_loop:
    dec rsi                    ; Move buffer pointer back
    mov rdx, rbx
    and rdx, 0xF               ; Get last 4 bits
    cmp rdx, 9
    jbe hex_digit
    add rdx, 'A' - 10          ; Convert 10-15 to A-F
    jmp hex_store
hex_digit:
    add rdx, '0'               ; Convert 0-9 to ASCII
hex_store:
    mov [rsi], dl              ; Store ASCII char
    shr rbx, 4                 ; Shift right by 4 bits
    loop hex_display_loop       ; Repeat for all digits

    ; Display the result
    mov rdx, disparr + 16      ; Calculate length
    sub rdx, rsi
    IO 1, 1, rsi, rdx          ; Write to stdout
    ret

exit:
    mov rax, 60                ; sys_exit
    xor rdi, rdi               ; Exit code 0
    syscall
