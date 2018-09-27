#include <string.h>

void hex_to_ascii(int n, char* str){
    strappend(str, '0');
    strappend(str, 'x');
    char zeros = 0;

    int tmp;
    for (int i=28; i>0; i-=4){
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0){
            continue;
        }
        zeros = 1;
        if (tmp >= 0xA){
            strappend(str, tmp - 0xA + 'A');
        }
        else{
            strappend(str, tmp + '0');
        }
    }

    tmp = n & 0xF;
    if (tmp >= 0xA){
        strappend(str, tmp - 0xA + 'A');
    }
    else{
        strappend(str, tmp + '0');
    }
}
