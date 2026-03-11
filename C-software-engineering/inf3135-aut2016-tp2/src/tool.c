/* tool.c
 *
 * @author Chao-Jung (Julie) Wu
 * @version 2.00.00
 * @since 2016-10-22
 */

#include "tool.h"

void strtoupper(char* str) {
    int i;
    for (i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
}

void strtolower(char* str) {
    int i;
    for (i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

void firstUPrestLOW(char* str) {
    int i;
    str[0] = toupper(str[0]);
    for (i = 1; str[i]; i++)
        str[i] = tolower(str[i]);
}

int areSameString(const char* str1, const char* str2){
    return !strcmp(str1, str2);
}
