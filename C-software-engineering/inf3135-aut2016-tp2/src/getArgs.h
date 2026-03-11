/** 
 * getArgs.h
 *
 * The purpose of the getArgs module, made of the files getArgs.h and 
 * getArgs.c, is to retreive the parameters (and their arguments where
 * applicable) entered by the user at the command line. This is done using
 * the getopt library. The information is stored into memory for use by the
 * program.
 *
 * @author Mathieu Loyer
 * @Version 1.01.00
 * @since 2016-11-16
 */

#ifndef STDLIB_H
    #define STDLIB_H
    #include <stdlib.h>
#endif
#ifndef GETOPT_H
    #define GETOPT_H
    #include <getopt.h>
#endif
#ifndef STDIO_H
    #define STDIO_H
    #include <stdio.h>
#endif
#ifndef STRING_H
    #define STRING_H
    #include <string.h>
#endif

#define FORMAT 'F'
#define FILE_NAME 'N'
#define COUNTRY 'C'
#define REGION 'R'
#define NO_MORE_OPTIONS -1
#define NB_OUTPUT_FORMATS 3
#define MAX_ARG_LEN 20

// int values indicate if flags were entered by user 0: no, other value: yes

struct argFlags{
    int helpFlag;           // --help
    int showMostFlag;       // --show-most // shows all expect flag
    int showAllFlag;        // --show-all
    int showLanguageFlag;   // --show-language
    int showCapitalFlag;    // --show-capital
    int showBordersFlag;    // --show-borders
    int showFlagsFlag;      // --show-flag
    char* format;           // <format> from --output-format <format>
    char* filename;         // <filename> from --output-filename <filename>
    char* country;          // <country> from --country <country>
    char* region;           // <region> from --region <region>
};
// supported output formats
#define FORMAT_TEXT "text"
#define FORMAT_DOT "dot"
#define FORMAT_PNG "png"
// supported regions
#define REGION_AFRICA "africa"
#define REGION_AMERICAS "americas"
#define REGION_ASIA "asia"
#define REGION_EUROPE "europe"
#define REGION_OCEANIA "oceania"
#define REGION_WORLD "world"

/**
* initialyse a struct argFlags with the arguments (aka flags) entered by the
* user
*
* getArgsClearMemory(struct argFlags* Flags) must be called when Flags is no
* longer needed.
*
* @param flags the struct argFlags* that will hold the data
* @param argc is the same argc passed from the main function
* @return argv is the same argv passed from the main function
*/
void initArgs(struct argFlags* Flags, int argc, char *argv[]);

/**
* know if --show-language was entered
*
* @Flags a struct argFlags* 
* @return 1 if was true or 0 if not
*/
int getArgsShowingLanguage(struct argFlags* Flags);

/**
* know if --show-capital was entered
*
* @Flags a struct argFlags* 
* @return 1 if was true or 0 if not
*/
int getArgsShowingCapital(struct argFlags* Flags);

/**
* know if --show-borders was entered
*
* @Flags a struct argFlags* 
* @return 1 if was true or 0 if not
*/
int getArgsShowingBorders(struct argFlags* Flags);

/**
* know if --show-flag was entered
*
* @Flags a struct argFlags* 
* @return 1 if was true or 0 if not
*/
int getArgsShowingFlag(struct argFlags* Flags);

/**
* know if output-format was entered
*
* @Flags a struct argFlags* 
* @return 1 if was true or 0 if not
*/
int getArgsOutputFormatIsSet(struct argFlags* Flags);

/**
* know if filename was entered
*
* @Flags a struct argFlags* 
* @return 1 if was true or 0 if not
*/
int getArgsFilenameIsSet(struct argFlags* Flags);

/**
* know if country was entered
*
* @Flags a struct argFlags* 
* @return 1 if was true or 0 if not
*/
int getArgsCountryIsSet(struct argFlags* Flags);

/**
* know if region was entered
*
* @Flags a struct argFlags* 
* @return 1 if was true or 0 if not
*/
int getArgsRegionIsSet(struct argFlags* Flags);

/**
* clear the memory used within the parameters of Flags
*
* @Flags a struct argFlags* 
* @return void
*/
void getArgsClearMemory(struct argFlags* Flags);
