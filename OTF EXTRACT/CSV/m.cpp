#include <iostream>
#include <string.h>
int main()
{
    char c[] = {
        0x43, 0x6F, 0x6D, 0x70, 0x75, 0x74, 0x65, 0x72
    };

    // for(int i = 0; i < 8 ;i++)
    // {
    //     printf(" %c ",  c[i]);
    // }

    // const char* s = "Science";
    // int s_s = strlen(s);

    // for(int i = 0 ; i < s_s; i++)
    // {
    //     printf(" %x ", s[i]);
    // }

    uint16_t g = 0b1101011100110010;
    printf("%d",g);
}