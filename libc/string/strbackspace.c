#include <string.h>

void strbackspace(char* s){
    size_t len = strlen(s);
    s[len-1] = '\0';
}
