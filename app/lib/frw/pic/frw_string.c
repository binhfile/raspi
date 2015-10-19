#include "frw_string.h"

int     strcmp(const char *s1, const char *s2){
    for(; (*s1 != '\0') && (*s2 != '\0'); s1++, s2++){
        if(*s1 != *s2)
            break;
    }
    if(*s1 == *s2) return 0;
    else return 1;
}
char *	strcpy(char *dest, const char *src){
    while(*src != '\0'){
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return dest;
}
size_t strlen(const char *s){
    size_t ret = 0;
    while(*s != '\0'){
        ret++;
        s++;
    }
    return ret;
}
void *	memset(void *s, int val, size_t count){
    char* p = (char*)s;
    int i;
    for(i = 0; i < count; i++){
        p[i] = val;
    }
    return s;
}
//end of file

