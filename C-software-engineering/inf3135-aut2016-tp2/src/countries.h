/** 
 * countries.h
 *
 * The purpose of the countries module, made of the files countries.h and 
 * countries.c, is to read the countries.json file using the jansson library 
 * and store them into the momery to be used by the program.
 *
 * @author Michael Tessier
 * @Version 1.01.00
 * @since 2016-11-16
 */

#ifndef STDIO_H
    #define STDIO_H
    #include <stdio.h>
#endif
#ifndef STRING_H
    #define STRING_H
    #include <string.h>
#endif
#ifndef STDBOOL_H
    #define STDBOOL_H
    #include <stdbool.h>
#endif

#include <jansson.h>

struct stringArray {
    char *strings[100];
    int count;
};

struct country {
    char name[50], code[4], capital[50], region[50];
    struct stringArray languages, borders;
};

struct countryArray {
    struct country countries[250];
    int count; 
};

/**
 * This method is used to initialize the count member of the stringArray 
 * structure to 0.
 * @param struct StringArray *_stringArray This is the structure getting
 *        initialized.
 */
void stringArrayInit(struct stringArray *_stringArray);

/**
 * This method is to initialize the count member of the countryArray
 * structure and call the initiallization of the strinbArray
 * members of each countries; languages and borders.
 * @param struct countryArray *_countryArray This is the structure
 *        getting initialized.
 */
void countryArrayInit(struct countryArray *_countryArray);

/**
 * Free the memory allocated to store information in the countryArray
 * structure.
 * @param struct countryArray *_countryArray This is the structure
 *        getting freed.
 */
void countryArrayDelete(struct countryArray *_countryArray);

/**
 * Open the .json file, read it and store the information in a countryArray 
 * structure using the functions in the jansson library.
 * @param struct countryArray *countryArray The struct where the information
 *        in the .json file is stored.
 */
bool countriesFetchFromJson(struct countryArray *countryArray);

