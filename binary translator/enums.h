enum commands {
    POP  = 65,
    PUSH = 66,
    MUL  = 67,
    DIV  = 68,
    ADD  = 69,
    SUB  = 70,
    END  = 71,
    R_PUSH = 72,
    R_POP = 73,
    SQRT = 74,
    SIN = 75,
    COS = 76,
    TAN = 77,
    OUT = 78,
    IN = 79,
    JAE = 84,
    JBE = 85,
    JNE = 86,
    JMP = 80,
    JA = 81,
    JB = 82,
    JE = 83,
    CALL = 87,
    RET = 88,
    M_PUSH = 90,
    M_POP  = 91,
};

#define db(value)\
	{size_t temp = value;\
	memcpy (this -> output_cur, &temp, 1);\
	this -> output_cur += 1;}

#define dw(value)\
	{size_t temp = value;\
	memcpy (this -> output_cur, &temp, 2);\
	this -> output_cur += 2;}

#define dd(value)\
	{size_t temp = value;\
	memcpy (this -> output_cur, &temp, 4);\
	this -> output_cur += 4;}

#define dq(value)\
	{size_t temp = value;\
	memcpy (this -> output_cur, &temp, 8);\
	this -> output_cur += 8;}

#define GETCOM this->get_com()
#define GETINT this->get_int()
#define GETDOUB this->get_doub()

#define JUMP(number)\
	{\
		db (0x5b)\
		db (0x58)\
		db (0x48) db (0x39) db (0xd8)\
		db (0x0f) db (0x82 + number) dd (GETINT - (size_t)( this -> output_cur) + (size_t) (this -> output_buffer) - 4)\
	}
