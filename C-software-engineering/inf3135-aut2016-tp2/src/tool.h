/* tool.h
 *
 * This module serves as the common tool kits for any project in C language, 
 *   such as functions to convert the format of a string
 *
 * @author Chao-Jung (Julie) Wu
 * @version 2.00.01
 * @since 2016-10-22
 */

#ifndef STRING_H
    #define STRING_H
    #include <string.h>
#endif
#ifndef CTYPE_H
    #include <ctype.h>
#endif

/** 
 *  formats the string to all uppper case, example result: AAAAAA
 *
 *  @param    str    the string to be modified the format
 */
void strtoupper(char* str);

/** 
 *  formats the string to all lower case, example result: aaaaaaaa
 *
 *  @param    str    the string to be modified the format
 */
void strtolower(char* str);

/** 
 *  formats the string to first character upper case, and the rest lowwer
 *  case, example result: Aaaaaa
 *
 *  @param    str    the string to be modified the format
 */
void firstUPrestLOW(char* str);

/** 
 *  checks if two strings have the same value
 *
 *  @param str1 first string in comparison 
 *  @param str2 second string in comparison
 */
int areSameString(const char* str1, const char* str2);
