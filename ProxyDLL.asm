.data

EXTERN lpXAudio2Create : dq
EXTERN lpCreateAudioReverb : dq
EXTERN lpCreateAudioVolumeMeter : dq
EXTERN lpX3DAudioInitialize  : dq
EXTERN lpX3DAudioCalculate  : dq
EXTERN lpCreateFX  : dq

EXTERN MessageBoxA : PROC

dXAudio2Create db "XAudio2Create", 0
dCreateAudioReverb db "dCreateAudioReverb", 0
dCreateAudioVolumeMeter db "dCreateAudioVolumeMeter", 0
dX3DAudioInitialize db "dX3DAudioInitialize", 0
dX3DAudioCalculate db "dX3DAudioCalculate", 0
dCreateFX db "dCreateFX", 0

.code

;jump funcs

PUBLIC XAudio2Create

XAudio2Create PROC

	;call lpXAudio2Create
	jmp lpXAudio2Create

XAudio2Create ENDP

CreateAudioReverb PROC

	sub rsp, 28h
	mov rcx, 0
	lea rdx, dCreateAudioReverb
	mov r8d, 0
	mov r9d, 0
	call MessageBoxA
	add rsp, 28h

	jmp lpCreateAudioReverb
CreateAudioReverb ENDP

CreateAudioVolumeMeter PROC

	sub rsp, 28h
	lea rdx, dCreateAudioVolumeMeter
	mov rcx, 0
	mov r8d, 0
	mov r9d, 0
	call MessageBoxA
	add rsp, 28h


	jmp lpCreateAudioVolumeMeter
CreateAudioVolumeMeter ENDP

CreateFX PROC

	sub rsp, 28h
	lea rdx, dCreateFX
	mov rcx, 0
	mov r8d, 0
	mov r9d, 0
	call MessageBoxA
	add rsp, 28h

	jmp lpCreateFX
CreateFX ENDP

X3DAudioCalculate PROC

	sub rsp, 28h
	lea rdx, dCreateAudioVolumeMeter
	mov rcx, 0
	mov r8d, 0
	mov r9d, 0
	call MessageBoxA
	add rsp, 28h

	jmp lpX3DAudioCalculate
X3DAudioCalculate ENDP

X3DAudioInitialize PROC

	sub rsp, 28h
	lea rdx, dX3DAudioInitialize
	mov rcx, 0
	mov r8d, 0
	mov r9d, 0
	call MessageBoxA
	add rsp, 28h

	jmp lpX3DAudioInitialize
X3DAudioInitialize ENDP

END