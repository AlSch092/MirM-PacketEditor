.data

EXTERN lpEncryptPacketAddress : dq

EXTERN lpSendPacketAddress : dq
EXTERN lpSendPacketReturnAddress : dq

EXTERN lpCreatePacketFunc : dq
EXTERN lpCreateRecvPacketFunc : dq

EXTERN lpGameSocket : dq
EXTERN lpKeyPtrLong : dq
EXTERN lpKeyPtrShort : dq
EXTERN lpGetGameSocketReturnAddress : dq

.code

HandleOutboundPackets PROC

	pop r10 ;hook API cleanup

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

	sub rsp, 28h
	mov rcx, rdx
	mov rdx, rbp
	call lpCreatePacketFunc
	add rsp, 28h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	; original bytes of where we hooked would go here, omitted from github version
	jmp lpSendPacketReturnAddress
HandleOutboundPackets ENDP

HandleInboundPackets PROC

	pop r10 ;hook API cleanup

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

	sub rsp, 28h
	mov rcx, [r14]
	mov rdx, [r14 + 8]
	call lpCreateRecvPacketFunc
	add rsp, 28h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	; original bytes of where we hooked would go here, omitted from github version
	ret
HandleInboundPackets ENDP

GetGameSocket PROC

	pop r10 ;hook API cleanup

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

	;sub rsp, 28h
	mov lpGameSocket, rcx
	;add rsp, 28h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	; original bytes of where we hooked would go here, omitted from github version
	jmp lpGetGameSocketReturnAddress
GetGameSocket ENDP

_EncryptPacket PROC

	sub rsp, 58h
	push rsi

	mov rdx, 6 ; # bytes to encrypt...
	mov rsi, 6

	call lpEncryptPacketAddress
	pop rsi
	add rsp, 58h
	ret
_EncryptPacket ENDP

_EncryptPacketHook PROC

	pop r10
	push r11 
	mov r11, [rsp+88h] ;length
	cmp r11, 6
	jg _long
	mov lpKeyPtrShort, rcx
	jmp cleanup
_long:
	mov lpKeyPtrLong, rcx
cleanup:
	; original bytes of where we hooked would go here, omitted from github version
	
	mov rax, lpEncryptPacketAddress
	add rax, 5
	jmp rax
_EncryptPacketHook ENDP

END