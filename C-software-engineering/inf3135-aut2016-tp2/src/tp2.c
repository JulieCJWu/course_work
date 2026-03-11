/* tp2.c
 *
 * This program displays information of a country or of the countries in a region, including the languages spoken, the capital city, the neighbouring countries and the national flag.
 *
 * This program first charges the countries data from a git submodule, and displays information upon user's request as in TEXT format, or with the aide of Graphviz software in DOT or PNG formats. The DOT and TEXT formats can be displayed in standard output or file. The PNG format is only available in file.  
 *
 * @author Michael Tessier, Mathieu Loyer, Chao-Jung (Julie) Wu
 * @version 1.00.04
 * @since 2016-10-22
 */
#ifndef GETARGS_H
    #define GETARGS_H
    #include "getArgs.h"
#endif
#ifndef COUNTRIES_H
    #define COUNTRIES_H
    #include "countries.h"
#endif
#ifndef CREATEDOT_H
    #define CREATEDOT_H 
    #include "createdot.h"
#endif
#ifndef DISPLAYTEXT_H
    #define DISPLAYTEXT_H
    #include "displaytext.h"
#endif

/**
 * Main
 *
 * @param    argc    the nomber of arguments passed
 * @param    argv    the table of arguments passed
 * @return   0       means ending the program normally 
 * @return   1       means exiting the program with an error
 */
int main(int argc, char *argv[]) {
    struct argFlags flags;
    initArgs(&flags, argc, argv);
    struct countryArray countries;

    countryArrayInit(&countries);
    if(!countriesFetchFromJson(&countries)) {
            printf("Error! The countries data can not be obtained.\n");
            getArgsClearMemory(&flags);
            return 1;
    }

    if ( strlen(flags.format) == 3 ){
        output_DOT_PNG(countries, flags);
    }
    else if (strlen(flags.country) == 0 && strlen(flags.region) == 0) {
            if (strcmp(flags.filename, "") == 0 ) 
                displayTextAllCountry(countries, flags);
            else createFILETextAllCountry(countries, flags);
    }
    else if (strlen(flags.country) == 3) {
        if ( strlen(flags.format) == 0  ||  (strcmp(flags.format, "text") == 0)) {
            if (strcmp(flags.filename, "") == 0 ) 
                displayTextOneCountry(countries, flags);
            else createFILETextOneCountry(countries, flags);
        }
    }
    else {
        if (strcmp(flags.filename, "") == 0 ) 
            displayTextReginalCountry(countries, flags);
        else createFILETextReginalCountry(countries, flags);
    }
    
    countryArrayDelete(&countries);
    getArgsClearMemory(&flags);
    return 0;
}


