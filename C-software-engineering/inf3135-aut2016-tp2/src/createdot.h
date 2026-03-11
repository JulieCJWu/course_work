/* createdot.h
 *
 * This module executes the tasks of generating dot strings in standard output, 
 *   and dot files or png files for a specified country or region
 *
 * @author Chao-Jung (Julie) Wu
 * @version 2.00.00
 * @since 2016-10-22
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

/** /////////////////////
 *
 *  Structures of data
 *
 *//////////////////////

/** 
 *  stores the paired codes of two countries which share borders
 *
 *  @param    key     the code of the country A
 *  @param    value   the code of the country B that shares border with country A
 */
struct link {
    char key[4];
    char value[4];
};

/** 
 *  stores the link array of two countries which share borders
 *
 *  @param    link    the array of the paired codes of two countries which share borders
 *  @param    count   the number of links in the array
 */
struct linkage {
    struct link link[350];
    int count;
};

/** /////////////////////
 *
 *  Functions
 *
 *//////////////////////

/** 
 *  decides which functions to be executed for dot and png formats according to user arguments stored in flags
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void output_DOT_PNG(struct countryArray countries, struct argFlags flags);

/**
 *  finds the country data in the countries array by code
 *
 *  Note that this function can return a null object. It is important to verify if the country is null.
 *  An example verification is:     
 *      if (strlen(country.code) == 0) return;
 *
 *  @param    code        the cca3 code of a country
 *  @param    countries   the array containing the data of countries
 *  @return   country     the country found in the countries array by the code 
 */
struct country searchCountrybyCode(const char* code, const struct countryArray countries);

/**
 *  copies the country data from source to country
 *
 *  @param    country    the destination of the copied country data
 *  @param    source     the source of the country data, usually a country at certain index postion in the countries array
 */
void countrycpy(struct country* country, const struct country source);

/**
 *  creates the file containing dot string of a specified country
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createDOTstringFile(const struct countryArray countries, const struct argFlags flags);

/**
 *  creates the dot node string of a specified country
 *
    char model[1200] = "\
    can [\n\
        shape = none,\n\
        label = <<table border=\"0\" cellspacing=\"0\">\n\
            <tr><td align=\"center\" border=\"1\" fixedsize=\"true\" width=\"200\" height=\"100\"><img src=\"./data/countries/data/can.png\" scale=\"true\"/></td></tr>\n\
            <tr><td align=\"left\" border=\"1\"><b>Name</b>: Canada</td></tr>\n\
            <tr><td align=\"left\" border=\"1\"><b>Code</b>: CAN</td></tr>\n\
            <tr><td align=\"left\" border=\"1\"><b>Capital</b>: Ottawa</td></tr>\n\
            <tr><td align=\"left\" border=\"1\"><b>Language</b>: French, English</td></tr>\n\
            <tr><td align=\"left\" border=\"1\"><b>Borders</b>: USA</td></tr>\n\
        </table>>\n\
    ];\
    ";
 *
 *  @param    dotstring    the string to receive the created dot node string
 *  @param    code         the cca3 code of a country
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createDOTnode(char* dotstring, const char* code, const struct countryArray countries, struct argFlags flags);

/**
 *  creates the complete dot string (containing a dot node) of a specified country
 *
 *  @param    dotstring    the string to receive the created dot node string
 *  @param    code         the cca3 code of a country
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createDOTstring(char* dotstring, const struct countryArray countries, struct argFlags flags);

/**
 *  displays the dot string created by createDotstring function for a specified country
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void displayDOTstring (const struct countryArray countries, struct argFlags flags);

/**
 *  create the file in png format from the dot string of a country, a region, or the world
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createPNGfile(const struct countryArray countries, const struct argFlags flags);

/**
 *  verifies of a file exists
 *
 *  @param    fname    the filename to be verified
 */
bool exists(const char *fname);

/**
 *  maps and registers the pairs of countries that share borders
 *
 *  @param    linkgae      the array of the paired codes of two countries which share borders
 *  @param    region       the region in which the countries' border pairs to be mapped
 *  @param    countries    the array containing the data of countries
 */
void mapLinkage(struct linkage *linkage, char* region, const struct countryArray countries);

/**
 *  verifies if this pair of countries has been registered
 *
 *  the logic behind the verification is:
 *    if this key-value pair has been registered before, the value must have been the key in the registry.
 *    so in the registry, it exists the reverse pair, value-key.
 *    then this function checks if the value can be found in the keys of the registry.
 *
 *  @param    value        the country code to be verified its appearance in the linkage registry
 *  @param    linkage      the registed array of the paired codes of two countries which share borders
 *  @param    nblinkage    the number of the current registered linkage array
 */
bool linkageExists(char* value, struct linkage *linkage, int nblinkage);

/**
 *  creates the file containing dot string of a specified region
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createRegionalDOTstringFile(const struct countryArray countries, struct argFlags flags);

/**
 *  creates the complete dot string (containing several dot nodes) of a specified region
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void displayRegionalDOTstring(const struct countryArray countries, struct argFlags flags);

/**
 *  creates the complete dot string (containing several dot nodes) of the world
 *
 *  @param    countries    the array containing the data of countries
 *  @param    flags        the user arguments
 */
void createWorldDOTstringFile(const struct countryArray countries, struct argFlags flags);
