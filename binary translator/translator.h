#include <iostream>
#include <assert.h>

size_t    size_of_file (FILE* file)
{
    assert(file);
    int cur = fseek(file, 0, SEEK_CUR);
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, cur, SEEK_SET);

    return size;

}

class translator
{
    private:
            void* input_buffer       = nullptr;
            void* output_buffer      = nullptr;
            void* input_cur          = nullptr;
            void* output_cur         = nullptr;

            size_t input_size        = 0;
            size_t output_size       = 0;

            int get_int             ();
            void elf_header         ();

    public:
            translator              ();
            ~translator             ();

            void make_input         ();
            void translate          ();
            void make_output        ();

};



const int max_binary            = 10000;
const int header_size           = 210;

#include "commands.h"



translator:: translator() {}
translator:: ~translator()
{
    free(this -> input_buffer);
    free(this -> output_buffer);

}

int translator:: get_int()
{
    int tmp = 0;
    memcpy (&tmp, this -> input_cur, sizeof(char));
    this -> input_cur += sizeof(int);

    return tmp;
}

void translator:: make_input()
{
    FILE* file = fopen("debug.txt", "r");
    assert(file);

    this -> input_size = size_of_file(file);
    std::cout<< this -> input_size;
    this -> input_buffer = (char*) calloc(this -> input_size, 1);
    //std::cout<< input_buffer ;
    assert(this -> input_buffer);

    fread(this -> input_buffer, 1, this -> input_size, file);
    printf("%s \n", (char*)(this -> input_buffer));
    fclose(file);

}

void translator:: translate()
{
    this -> output_buffer = (char*) calloc (max_binary, 1);
    assert(this -> output_buffer);

    this -> output_cur = this -> output_buffer;

    dw (0x8948)
    db (0xe5)
    dw (0x8148)
    db (0xec)
    dd (0x400)

    this -> output_buffer += 10;

    while ((size_t) ((size_t)(this -> input_cur) - (size_t)(this -> input_buffer)) <= this -> input_size)
    {
        int temp = get_int();
        printf("\ncur int %x\n", temp);
        #define CMD(number, command)        \
                case (number):              \
                {                           \
                    command                 \
                    break;                  \
                }

        // switch(temp)
        // {
        //     CMD(END, {
        //             dw (0x8148) db (0xc5) dd (0x400)
        //             db (0xb8)   dd (0x3c)					//mov rax, 60
        //             dw (0x3148) db (0xff)					//xor rdi, rdi
        //             dw (0x050f) 						//syscall
        //
        //         })
        //
        // }

        #undef CMD

    }

    //free(this -> input_buffer); //????

    this -> output_buffer -= 10;
    this -> output_size = (size_t) ((size_t)this -> output_cur - (size_t)this -> output_buffer);
}

void translator:: make_output()
{
    void* output = calloc(this -> output_size + header_size, 1);
    assert(output);
    std:: cout<< (char*)output_buffer;
    memcpy(output + header_size, this -> output_buffer, this -> output_size);
    //printf("output + header1 %s \n", output + header_size);

    this -> output_buffer = output;
	this -> output_cur = output;

    //printf("output -> buffer + header %s \n", this -> output_buffer + header_size);
    //printf("output -> buffer %s \n", this -> output_buffer);

    elf_header();
    FILE* file = fopen("exit", "w");
    assert (file);

    fwrite(this -> output_buffer , 1, this -> output_size + header_size, file);

    fclose (file);
}

void translator:: elf_header()
{
    /*elf header*/

    db (0x7f)       //.
    db ('E')        //E
    db ('L')        //L
    db ('F')        //F
    db (0x02)       // 64/bit
    db (0x01)       // little endian
    db (0x01)       // elf-version
    db (0x00)       //OS LINUX

    dq (0x00)       //ABI

    dw (0x02)       //executable
    dw (0x3e)       // x86-64

    dd (0x01)       //e-version


    dq (0x4000b0)                              //e_entry - mem_addr of _start
    dq (0x40)                                  //e_phoff - offs of the phdrtab
    dq (0x00)                                  //e_shoff - offs of the shdrtab (I don't use that)

    dd (0x00)                                  //e_flags - depends on the architecture

    dw (0x40)                                  //e_ehsize - hdr_sz
    dw (0x38)                                  //e_phentsize - phdr_sz
    dw (0x02)                                  //e_phnum - num of phdrs

    dw (0x00)                                  //e_shentsize
    dw (0x00)                                  //e_shnum       (I don't create section hdrs)
    dw (0x00)                                  //e_shstrndx

    /*PROGRAM HEADER TABLE*/
        /*.text header*/
    dd (0x01);                                  //PT_LOAD
    dd (0x05);                                  //R E

    dq (0x00);                                  //offset of the segment
    dq (0x400000);                              //virtual addr of the segment in memory
    dq (0x400000);                              //phys    addr of the segment in memory
    dq (max_binary + this -> output_size);             //size of segment in file
    dq (max_binary + this -> output_size);                //size of segment in memory
    dq (0x10);                                  //p_align; ignored, because file is executable

        /*.data header*/
    dd (0x01);                                  //PT_LOAD
    dd (0x06);                                  //RW

    dq (0xb2);                                  //offset of the segment
    dq (0x6000b2);                              //virtual addr of the segment in memory
    dq (0x6000b2);                              //phys    addr of the segment in memory
    dq (0x20);                                  //size of segment in file
    dq (0x20);                                  //size of segment in memory
    dq (0x10);                                  //p_align; ignored, because file is executable

    db (0xeb);                                  //jmp over .data
    db (0x20);

    /*db ('0');                                   //buffer "0123456789abcdef"
    db ('1');
    db ('2');
    db ('3');
    db ('4');
    db ('5');
    db ('6');
    db ('7');
    db ('8');
    db ('9');
    db ('a');
    db ('b');
    db ('c');
    db ('d');
    db ('e');
    db ('f');*/

}
