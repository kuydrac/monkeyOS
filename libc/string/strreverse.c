#include <string.h>

void strreverse(char* s){
    size_t i, j;
    char c;
    for (i=0, j=strlen(s)-1; i < j; i++,j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
