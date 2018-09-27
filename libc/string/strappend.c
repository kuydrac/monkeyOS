#include <string.h>

void strappend(char* s, char n){
    size_t len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}
