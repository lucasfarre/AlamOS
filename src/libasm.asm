GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL  _int_09_hand
GLOBAL  _int_1A_hand
GLOBAL  _int_80_hand
GLOBAL  _int_21_hand
GLOBAL  _int_22_hand
GLOBAL  _mascaraPIC1, _mascaraPIC2, clearInterrupts, setInterrupts
GLOBAL  outportb, inportb
GLOBAL  outportb32, inportb32
GLOBAL  temp_asm, tj_max
GLOBAL  _debug
GLOBAL  read_int80h
GLOBAL  write_int80h

EXTERN  int_08
EXTERN  int_09
EXTERN  int_1A
EXTERN  write
EXTERN  read

SECTION .text


clearInterrupts:
	cli			   ; limpia flag de interrupciones
	ret

setInterrupts:
	sti			   ; habilita interrupciones por flag
	ret

outportb:
    push ebp
    mov ebp, esp
    
    mov dx,word[ebp + 8]  ;en EAX pongo el primer parametro port
    mov al,byte[ebp + 12] ;en EBX pongo el segundo parametro source
    out dx, al

    mov esp, ebp
    pop ebp
    ret

inportb:
    push ebp
    mov ebp, esp
    
    mov eax, 0
    mov dx, word[ebp + 8]  ;en EAX pongo el primer parametro port
    in al, dx
    
    mov esp,ebp
    pop ebp
    ret
    
outportb32:
    push ebp
    mov ebp, esp
    
    mov dx,word[ebp + 8]    ;en EAX pongo el primer parametro port
    mov eax,dword[ebp + 12] ;en EBX pongo el segundo parametro source
    out dx, eax

    mov esp, ebp
    pop ebp
    ret

inportb32:
    push ebp
    mov ebp, esp
    
    mov eax, 0
    mov dx, word[ebp + 8]  ;en EAX pongo el primer parametro port
    in eax, dx
    
    mov esp,ebp
    pop ebp
    ret

tj_max:
    push ebp
    mov ebp, esp
        
    mov ecx, 1A2h       ; 1A2h (MSR_TEMPERATURE_TARGET)
    rdmsr               ; Read MSR specified by ECX into EDX:EAX.
    ror eax, 16
    and eax, 0FFh       ; Me quedo con el Tj Max (~100°C)
        
    mov esp, ebp
    pop ebp
    ret

temp_asm:
    push ebp
    mov ebp, esp

    mov ecx, 19Ch    ; 1B1h (IA32_PACKAGE_THERM_STATUS) 19Ch (IA3_THERM_STATUS)
    rdmsr            ; Read MSR specified by ECX into EDX:EAX.
    ror eax, 16     
    and eax, 07Fh    ; Me quedo con el Digital Readout
    
    mov esp, ebp
    pop ebp
    ret

_mascaraPIC1:			; Escribe mascara del PIC 1
    push ebp
    mov ebp, esp
    mov ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out	21h,al
    pop ebp
    retn

_mascaraPIC2:			; Escribe mascara del PIC 2
    push ebp
    mov ebp, esp
    mov ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out	0A1h,al
    pop ebp
    retn

_read_msw:
    smsw ax		; Obtiene la Machine Status Word
    retn


_lidt:		    ; Carga el IDTR
    push ebp
    mov ebp, esp
    push ebx
    mov ebx, [ss: ebp + 6]  ; ds:bx = puntero a IDTR 
    rol	ebx,16		    	
    lidt [ds: ebx]          ; carga IDTR
    pop ebx
    pop ebp
    retn


_int_08_hand:				; Handler de INT 8 ( Timer tick)
    push ds
    push es                 ; Se salvan los registros
    pusha                   ; Carga de DS y ES con el valor del selector
    mov ax, 10h			    ; a utilizar.
    mov ds, ax
    mov es, ax                  
    call int_08                 
    mov al,20h			    ; Envio de EOI generico al PIC
    out 20h,al
    popa                            
    pop es
    pop ds
    iret

_int_09_hand:			    ; Handler de INT9 (Teclado)
    pushad                  ; Buckupea todos los registros.
    pushf                   ; Backupea todos los flags.
    mov eax,0
    in al,060h              ; Le pido el scancode al teclado.
    push eax
    call int_09
    pop eax
    mov	al,20h			    ; Le mando el EOI generico al PIC.
    out 20h,al
    popf                    ; Restauro todos los flags.
    popad                   ; Restauro todos los registros.
    iretd

_int_80_hand:               ; Pensada para manejar las system calls y
    cli                     ; hacer una diferencia entre user y kernel space.
    cmp eax, dword 3        ; Lamentablemente, luego de muchos testeos, no 
    je call_read            ; logramos hacerla funcionar.
    cmp eax, dword 4
    je call_write
    sti
    iretd       
call_write:
    push dword edx
    push dword ecx
    push dword ebx
    call write
    pop dword ebx
    pop dword ecx
    pop dword edx
    sti
    iretd
call_read:
    push dword edx
    push dword ecx
    push dword ebx
    call read
    pop dword ebx
    pop dword ecx
    pop dword edx
    sti
    iretd
   
read_int80h:
    push ebp
    mov ebp, esp
        
    mov ebx, dword[ebp + 8]
    mov	ecx, dword[ebp + 12]
    mov	edx, dword[ebp + 16]

    mov eax, dword 3
    int 80h
       
    mov esp, ebp
    pop ebp
    ret   
        
write_int80h:
    push ebp
    mov ebp, esp

    mov ebx, dword [ebp + 8]
    mov	ecx, dword [ebp + 12]
    mov	edx, dword [ebp + 16]
        
    mov eax, dword 4
    int 80h
        
    mov esp, ebp
    pop ebp
    ret
        
; Debug para el BOCHS, detiene la ejecución; 
; Para continuar colocar en el BOCHSDBG: set $eax=0

_debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	    ax, 0
        jne	    vuelve
        pop	    ax
        pop     bp
        retn
