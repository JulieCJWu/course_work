/* displaytext.h
 *
 * This module executes the tasks of displaying text output in standard output or generating a text file
 * for a specified country or region
 *
 * @author Michael Tessier, Mathieu Loyer, Chao-Jung (Julie) Wu
 * @version 2.00.01
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
#ifndef TOOL_H
    #define TOOL_H
    #include "tool.h"
#endif

/**
 *  In order not to include stdbool.h (purposely) but to be able to use a boolean for isCountryFound, declare this Bool type.
 *  An exercise of using typedef enum.
 */
typedef enum { FALSE, TRUE } Bool;

/** 
 *  accepts the request to display the data of all countries in text format
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void displayTextAllCountry(struct countryArray countries,
        struct argFlags flags);

/** 
 *  accepts the request to display the data of one country in text format
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void displayTextOneCountry(struct countryArray countries,
        struct argFlags flags);

/** 
 *  accepts the request to display the data of one region in text format
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void displayTextReginalCountry(struct countryArray countries,
        struct argFlags flags);

/** 
 *  displays the data of one country in text format, this function is to be
 *  called by other functions in this module
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void displayTextOneCountryCoreCode(int i, struct countryArray countries,
        struct argFlags flags);

/** 
 *  registers the data of one country in text format in a file, this function is to be
 *  called by other functions in this module
 *
 *  @param    fp           the pointer to the text file to be wriiten
 *  @param    i            the index of the country to be processed
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createFILETextOneCountryCoreCode(FILE *fp, int i, struct countryArray countries, 
        struct argFlags flags);

/** 
 *  registers the data of all countries in text format in a file
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createFILETextAllCountry(struct countryArray countries, 
        struct argFlags flags);

/** 
 *  registers the data of one country in text format in a file
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createFILETextOneCountry(struct countryArray countries, 
        struct argFlags flags);

/** 
 *  registers the data of the countries in a region in text format in a file
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createFILETextReginalCountry(struct countryArray countries, 
        struct argFlags flags);

