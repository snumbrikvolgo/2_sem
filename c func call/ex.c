#include <stdio.h>
#include <inttypes.h>

extern int64_t _sum(int64_t a, int64_t b);
int64_t _Asum(int64_t a, int64_t b);

int main()
{
    printf("%ld\n", _sum(64, 16));
}

int64_t _Asum( int64_t a, int64_t b)
{
    return a + b;
}
