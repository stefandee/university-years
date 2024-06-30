	.286		;processor type

	code segment byte
	assume cs:code,ds:code,es:code

	org 100h

start:  jmp mycode
	;data def start

	buf db 16 dup(65)
	prompt 	db "Keep'em coming>$"
	nextline db 13,10,'$'
	addinstr db 'add'
	movinstr db 'mov'
	quitinstr db 'quit'
	reg1 db 1
	reg2 db 2
	reg3 db 3
	reg4 db 4
	op1 db 0
	op2 db 0
	opreq db 0
	cmpres db 0
	errorfile db 'error',0
	corectfile db 'corect',0
	errorhandle dw 0
	corecthandle dw 0
	regdata db 'reg1reg2reg3reg4'

strcmp proc
	push ax
	mov [cmpres],0	;error code = false
cmploop:
	mov al,[si]
	mov ah,[di]
	inc di
	inc si
	sub al,ah
	cmp al,0
	jne cmpend
	loop cmploop
	mov [cmpres],1
cmpend: 
	pop ax
	ret
strcmp endp
	
openfile proc
	mov ah,3ch
	xor cx,cx
	int 21h
	ret
openfile endp

writefile proc
	mov ah,40h
	int 21h
	ret
writefile endp

hexshow proc
 	cmp al,9
	jae letter
	mov dl,48
	jmp hexshowend
letter:
	mov dl,55
hexshowend:
	add dl,al
	mov ah,2
	int 21h
	ret
hexshow endp

hex2ascii proc
	mov bl,al
	and al,240
	shr al,4
	call hexshow

	mov al,bl
	and al,15
	call hexshow
	ret
hex2ascii endp


	;data def end

mycode:	
	mov dx,offset errorfile
	call openfile
	mov [errorhandle],ax

	mov dx,offset corectfile
	call openfile
	mov [corecthandle],ax

main:	
	mov di,offset buf
	xor bx,bx
	
	mov ah,9
	mov dx,offset prompt
	int 21h

a_line:	
	mov ah,1
	int 21h
	cmp al,13
	je  treatline
	mov [di+bx],al
	inc bx
	cmp bx,16
	jae treatline
	jmp a_line

treatline:
	mov dx,offset nextline
	mov ah,9
	int 21h

	mov si,offset quitinstr	
	mov cx,bx
	rep cmpsb
	jne  nextsearch		;quit found - end the program
	jmp theend

nextsearch:
	mov [opreq],1		;in case of found,opreq = add =1
	mov si,offset addinstr
	mov di,offset buf
	mov cx,3
	rep cmpsb
	je sthfound		;add found

	mov[opreq],2
	mov si,offset movinstr
	mov di,offset buf
	mov cx,3
	rep cmpsb
	je sthfound		;mov found

writerror:
	mov cx,bx
	mov bx,[errorhandle]
	mov dx,offset buf
	call writefile		;n-thing found - write it to error file

	mov cx,2
	mov dx,offset nextline
	call writefile		;write an enter

	jmp main

sthfound:
	mov di,offset buf
	cmp byte ptr [di+3],' '
	jne writerror	
	cmp byte ptr [di+8],','
	jne writerror

	mov si,offset regdata
	mov dx,4
	mov [op1],0

trackop1:
	mov di,offset buf
	add di,4
	mov cx,4
	call strcmp
	cmp [cmpres],1
	je  trackedop1
	inc [op1]
	dec dx
	cmp dx,0
	je writerror  		;this means no valid register found op1
	jmp trackop1

trackedop1:		

	mov si,offset regdata
	mov dx,4
	mov [op2],0

trackop2:
	mov di,offset buf
	add di,9
	mov cx,4
	call strcmp
	cmp [cmpres],1
	je  trackedop2
	inc [op2]
	dec dx
	cmp dx,0
	je writerror  		;this means no valid register found op2
	jmp trackop2
	
trackedop2:
	
	xor bx,bx
	mov di,offset reg1	;choose the registers 1-4
	mov bl,[op2]
	mov dh,[di+bx]

	xor bx,bx
	mov bl,[op1]		;bx now contains destination of operation
	mov dl,[di+bx]

	mov al,[opreq]
	cmp al,1
	jne movreq
	add dl,dh
	mov [di+bx],dl
	jmp writecorect
movreq:
	mov [di+bx],dh
writecorect:
	mov cx,13
	mov bx,[corecthandle]
	mov dx,offset buf
	call writefile		

	mov cx,2
	mov dx,offset nextline
	call writefile		;write an enter

	jmp main

theend:	
	mov di,offset reg1
	mov cx,4
showregs:
	lodsb
	call hex2ascii
	mov dx,offset nextline

	mov ah,9
	int 21h
	loop showregs

	mov ah,04Ch 	;exit the program
	int 21h

	code ends
end start