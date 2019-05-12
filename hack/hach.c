#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int size_of_file (FILE* file)
{
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);

    return size;
}

unsigned int hash_gnu (char* string, int size)
{
    unsigned int hash = 0;
    int i = 0;
    for (char* cur = string; *cur != '\0'; cur++)
    {
        hash = ( (hash << 5) + hash) + (*cur);
    }

    return hash;
}
const int hash = 4294967224;

int main()
{
    printf("Welcome to Hack-Wizard!\n");
    FILE* file = fopen("PASSWORD.COM", "r + w");

    assert(file);

    int size = size_of_file (file);
    char* buffer = (char*) calloc (size, 1);
    fread(buffer, size, sizeof(char*), file);
    hash_gnu(buffer, size);

    if (hash_gnu(buffer,size) != hash)
    {
        printf("Wrong file!\n");
        return 0;
    }

    if (buffer[0x00000000DB] == 0x01)
    {
        printf("File has already been patched\n");
        return 0;
    }
    else
    {
    fseek (file, 0xDB, SEEK_SET);
    putc(0x1, file);
    }
    printf("Fenixx-repack\n\n");
    printf("%x %x %x",buffer[0x00000000DA] ,buffer[0x00000000DB],buffer[0x00000000DC]  );

    fclose(file);
    return 0;
}
