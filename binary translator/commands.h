CMD(END, {
			dw (0x8148) db (0xc5) dd (0x400)
			db (0xb8)   dd (0x3c)					//mov rax, 60
			dw (0x3148) db (0xff)					//xor rdi, rdi
			dw (0x050f) 							//syscall

		})

CMD (ADD, {
			db (0x5b)								//pop rbx
			db (0x58)								//pop rax
			dw (0x0148) db (0xd8)					//add rax, rbx
			db (0x50)								//push rax
			})

CMD (SUB, {
			db (0x5b)						//pop rbx
			db (0x58)						//pop rax
			dw (0x2948) db (0xd8)			//SUB rax, rbx
			db (0x50)						//push rax
			})
CMD (MUL, {
			db (0x5b)						//pop rbx
			db (0x58)						//pop rax
			db (0x52)						//push rdx
			dw (0xf748) db (0xeb)					//imul rbx
			db (0x5a)						//pop rdx
			db (0x50)						//push rax
		})

CMD (DIV, {							//39
		db (0x5b)						//pop rbx
		db (0x58)						//pop rax
		db (0x52)						//push rdx
		dw (0x3148) db (0xd2)					//xor rdx, rdx
		dw (0x8348) db (0xf8) db (0x00)				//cmp rax, 0
		db (0x7d) db (0x16)					//jge .znak
		db (0xb9) dd (0x00)					//mov rcx, 0
		dw (0x2948) db (0xc1)					//sub rcx, rax
		dw (0x8948) db (0xc8)					//mov rax, rcx
		db (0xb9) dd (0x00)					//mov rcx, 0
		dw (0x2948) db (0xd9)					//sub rcx, rbx
		dw (0x8948) db (0xcb)					//mov rbx, rcx
		dw (0xf748) db (0xfb)					//idiv rbx
		db (0x5a)						//pop rdx
		db (0x50)						//push rax
		})


CMD (SQRT, {
			dw (0x2cdf) db (0x24)					//fild qword [rsp]
			dw (0xfad9)								//fsqrt
			dw (0x3cdf) db (0x24)					//fistp qword [rsp]
	})

CMD (PUSH, {
			db(0x68)
			dd(GETINT)
})

CMD (R_PUSH, {
			db (0x50 + GETCOM)
})

CMD (M_PUSH,{
			db (0x55)								//push rbp
			dw (0x8148) db (0xed) dd (GETINT * 8)	//sub rbp, <int>*8
			dd (0x458b48)							//mov rax, [rbp]
			db (0x5d)								//pop rbp
			db (0x50)								//push rax
})

CMD (R_POP, {
			db (0x58 + GETCOM)
})

CMD (M_POP, {
			db (0x58)								//pop rax
			db (0x55)								//push rbp
			dw (0x8148) db (0xed) dd (GETINT * 8)	//sub rbp, <int> * 8
			dd (0x458948)							//mov [rbp], rax
			db (0x5d)								//pop rbp
})
CMD (IN, {
		db (0x53)									//push rbx
		db (0x51)									//push rcx
		db (0x52)									//push rdx

		db (0xb8) dd (0x3)							//mov rax, 3
		db (0xbb) dd (0x2)							//mov rbx, 2
		db (0x48) db (0xb9) dq (0x6000c2)			//mov rcx, buffer
		db (0xba) dd (0xa)							//mov rdx, 10
		dw (0x80cd)									//int 80h
		db (0x48) db (0xbf) dq (0x6000c2)			//mov rdi, buffer
		dw (0x3148) db (0xc0)						//xor rax, rax
		dw (0x3148) db (0xdb)						//xor rbx, rbx
		db (0x8a) db (0x1f)							//mov bl, byte [rdi]
		db (0x80) db (0xfb) db (0x2d)				//cmp bl, '-'
		db (0x75) db (0x05)							//jne    4000f6 <_start.nxt>
		dw (0xff48) db (0xc7)						//inc rdi
		db (0x8a) db (0x1f)							//mov bl, byte [rdi]
													//.next
		db (0x80) db (0xeb) db (0x30)				//sub bl, 30h
		db (0xb9) dd (0xa)							//mov rcx, 10d
		dw (0xf748) db (0xe1)						//mul rcx
		dw (0x0148) db (0xd8)						//add rax, rbx
		dw (0xff48) db (0xc7)						//inc rdi
		dw (0x3148) db (0xdb)						//xor rbx, rbx
		db (0x8a) db (0x1f)							//mov bl, byte [rdi]
		db (0x80) db (0xfb) db (0x1e)				//cmp bl, 30
		db (0x73) db (0xe5)							//jae    4000f6 <_start.nxt>
		dw (0x1c8a) db (0x25) dd (0x6000c2)			//mov bl, byte [buffer]
		db (0x80) db (0xfb) db (0x2d)				//cmp bl, '-'
		db (0x74) db (0x02)							//je     40011f <_start.sign>
		db (0xeb) db (0x0a)							//jmp    400129 <_start.unsign>
													//sign
		db (0x48) dw (0xc2c7) dd (0xffffffff)		//mov rdx, -1
		db (0x48) dw (0xe2f7)						//mul rdx
		db (0x5a)									//pop rdx
													//.unsign
		db (0x59)									//pop rcx
		db (0x5b)									//pop rbx

		db (0x50)									//push rax
		})

		CMD(OUT, {
				db (0x58)							//pop rax

				db (0x53)							//push rbx
				db (0x51)							//push rcx
				db (0x52)							//push rdx

				db (0xbb) dd (0x3b9aca00)			//mov rbx, 1000000000d
				db (0x48) db (0xbf) dq (0x6000c2)	//mov rdi, buffer
				db (0x48) db (0xbe) dq (0x6000b2)	//mov rsi, numbers
				db (0x41) db (0xb8) dd (0x00)		//mov r8, 0
				db (0xb9) dd (0x80000000)//40 		//mov rcx, 80000000h
				db (0x48) db (0x21) db (0xc1)		//and rcx, rax
				dw (0x8348) db (0xf9) db (0x00)		//cmp rcx, 0
				db (0x74) db (0x1b)					//je  <_start.uns>
				db (0x48) dw (0xc1c7) dd (0xffffffff)//mov rcx, -1
				dw (0x3148) db (0xd2)				//xor rdx, rdx
				dw (0xf748) db (0xe1)				//mul rcx
				db (0xb3) db (0x2d)					//mov byte bl, '-'
				db (0x88) db (0x1f)					//mov byte [rdi], bl
				dw (0xff48) db (0xc7)				//inc rdi
				db (0xb9) dd (0x1)					//mov rcx, 1
				db (0xeb) db (0x03)					//jmp    400179

				dw (0x3148) db (0xc9)				//xor rcx, rcx

				db (0xba) dd (0x00)					//mov rdx, 0
				dw (0xf748) db (0xf3)				//div rbx
				db (0x4c) db (0x39) db (0xc0)		//cmp rax, r8
				db (0x74) db (0x18)					//je   <_start.zero>
				db (0x41) db (0xb8) dd (0xb)		//mov r8, 11
				db (0x48) db (0x01) db (0xc6)		//add rsi, rax
				db (0x53)							//push rbx
				db (0x8a) db (0x1e)					//mov byte bl, [rsi]
				db (0x88) db (0x1f)					//mov byte [rdi], bl
				db (0x5b)							//pop rbx
				dw (0x2948) db (0xc6)				//sub rsi, rax
				dw (0xff48) db (0xc7)				//inc rdi
				dw (0xff48) db (0xc1)				//inc rcx

				db (0x52)							//push rdx
				dw (0x8948) db (0xd8)				//mov rax, rbx
				db (0xbb) dd (0xa)					//mov rbx, 10d
				db (0xba) dd (0x00)					//mov rdx, 0
				dw (0xf748) db (0xf3)				//div rbx
				dw (0x8948) db (0xc3)				//mov rbx, rax
				db (0x58)							//pop rax
				dw (0x8348) db (0xfb) db (0x00)		//cmp rbx, 0d
				db (0x75) db (0xc0)					//jne   <_start.Nxt>
				dw (0x8349) dw (0xf8)				//cmp r8, 0
				db (0x75) db (0x0a)					//jne .prt
				db (0xb3) db (0x30)					//mov byte bl, '0'
				db (0x88) db (0x1f)					//mov byte [rdi], bl
				dw (0xff48) db (0xc7)				//inc rdi
				dw (0xff48) db (0xc1)				//inc rcx

				db (0xb3) db (0xa)					//mov byte bl, 0ah
				db (0x88) db (0x1f)					//mov byte [rdi], bl
				dw (0xff48) db (0xc1)				//inc rcx

				db (0xb8) dd (0x1)					//mov rax, 1
				db (0xbf) dd (0x1)					//mov rdi, 1
				dw (0xbe48) dq (0x6000c2)			//mov rsi, buffer
				dw (0x8948) db (0xca)				//mov rdx, rcx
				dw (0x050f)							//syscall

				db (0x5a)							//pop rdx
				db (0x59)							//pop rcx
				db (0x5b)							//pop rbx
				})

CMD (RET, db  (0xc3))//1
CMD (JMP, db (0xe9) dd (GETINT - (size_t)( this -> output_cur) + (size_t) (this -> output_buffer) - 4))

CMD (JA , JUMP (0xd))
CMD (JB , JUMP (0xa))
CMD (JE , JUMP (0x2))
CMD (JAE, JUMP (0xb))
CMD (JBE, JUMP (0xc))
CMD (JNE, JUMP (0x3))

CMD (CALL, db (0xe8) dd (GETINT - (size_t)( this -> output_cur) + (size_t) (this -> output_buffer) - 4))
