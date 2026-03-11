/** 
 * getArgs.c
 *
 * @author Mathieu Loyer
 * @version 1.01.00
 * @since 2016-11-16
 */

#include "getArgs.h"

// max length per argument type
#define MAX_CHARS_FORMAT 5
#define MAX_CHARS_FILENAME 20
#define MAX_CHARS_COUNTRY 4 
#define MAX_CHARS_REGION 10
// short form of argument names
#define FORMAT 'F'
#define FILE_NAME 'N'
#define COUNTRY 'C'
#define REGION 'R'
#define NO_MORE_OPTIONS -1
// error messages
#define ERR_MSG_COUNTRY_AND_REGION "Error, country and region cannot be "\
    "specified at the same time.\n"
#define ERR_MSG_SHOW_FLAGS_AND_FOMAT_TEXT "Error, show-flags is not valid for "\
    "text format.\n"
#define ERR_MSG_OUTPUT_FORMAT_INVALID "Error, output format invalid\n"
#define ERR_MSG_PNG_FORMAT_WITHOUT_OUTPUT_FILENAME "Error, output filename is "\
    "mandatory for the \"png\" format.\n"
#define ERR_MSG_REGION_INVALID "Error, region entered is invalid.\n"
// constants
#define NOT_DEFINED ""
#define DEFAULT_FORMAT "text"
#define DEFAULT_OUTPUT_FILENAME "stdout"
// usage message
#define USAGE "Usage:\n\
bin/tp2 [--help] [--output-format FORMAT]\
 [--output-filename FILENAME] [--show-languages] [--show-capital]\
 [--show-borders] [--show-flag] [--country COUNTRY] [--region REGION]\n"
// help message
#define HELP "Usage:\n"\
"bin/tp2 [--help] [--output-format FORMAT] [--output-filename FILENAME]\n"\
" [--show-languages] [--show-capital] [--show-borders] [--show-flag]\n"\
" [--country COUNTRY | --region REGION]\n"\
"\n"\
"Displays information about countries.\n"\
"\n"\
"Optional arguments:\n"\
"  --help                     Show this help message and exit.\n"\
"  --output-format FORMAT     Selects the ouput format (either \"text\", \"dot\" or \"png\").\n"\
"                             The \"dot\" format is the one recognized by Graphviz.\n"\
"                             The default format is \"text\".\n"\
"  --output-filename FILENAME The name of the output filename. This argument is\n"\
"                             mandatory for the \"png\" format. For the \"text\" and \"dot\"\n"\
"                             format, the result is printed on stdout if no output\n"\
"                             filename is given.\n"\
"  --show-all                 Equivalent as adding all the --show.\n"\
"  --show-most                Equivalent to --show-all excluding flag.\n"\
"  --show-languages           The official languages of each country are displayed.\n"\
"  --show-capital             The capital of each country is displayed.\n"\
"  --show-borders             The borders of each country is displayed.\n"\
"  --show-flag                The flag of each country is displayed\n"\
"                             (only for \"dot\" and \"png\" format).\n"\
"  --country COUNTRY          The country code (e.g. \"can\", \"usa\") to be displayed.\n"\
"  --region REGION            The region of the countries to be displayed.\n"\
"                             The supported regions are \"world\", \"africa\", \"americas\",\n"\
"                             \"asia\", \"europe\" and \"oceania\".\n"

void usage();
void argsLogic(struct argFlags* flags);
int isDefined(char* s);
int formatIsText(char* s);
int formatIsValid(char* choice);
int outputFormatIsPnG(char* s);
int regionIsInvalid(char* choice);

void initArgs(struct argFlags* flags, int argc, char *argv[]) {

    int help_flag;
    int show_all_flag;
    int show_most_flag;
    int show_languages_flag;
    int show_capital_flag;
    int show_borders_flag;
    int show_flag_flag;

    flags->country = (char*) malloc(MAX_ARG_LEN * sizeof(char*));
    flags->region = (char*) malloc(MAX_ARG_LEN * sizeof(char*));
    flags->format = (char*) malloc(MAX_ARG_LEN * sizeof(char*));
    flags->filename = (char*) malloc(MAX_ARG_LEN * sizeof(char*));
    strncpy(flags->country, NOT_DEFINED, MAX_ARG_LEN);
    strncpy(flags->region, NOT_DEFINED, MAX_ARG_LEN);
    strncpy(flags->format, NOT_DEFINED, MAX_ARG_LEN);
    strncpy(flags->filename, NOT_DEFINED, MAX_ARG_LEN);

    struct option long_options[] = {
        /* These options set a flag. */
        // syntax: {name, argNeeded, flag, setFlagTo}
        {"help", no_argument, &help_flag, 1},
        {"show-languages", no_argument, &show_languages_flag, 1},
        {"show-capital", no_argument, &show_capital_flag, 1},
        {"show-borders", no_argument, &show_borders_flag, 1},
        {"show-flag", no_argument, &show_flag_flag, 1},
        {"show-most", no_argument, &show_most_flag, 1},
        {"show-all", no_argument, &show_all_flag, 1},
        /* These options do not set a flag.
        We distinguish them by their indices. */
        // syntax: {name, argNeeded, flag, indices}
        {"output-format", required_argument, 0, FORMAT},
        {"output-filename", required_argument, 0, FILE_NAME},
        {"country", required_argument, 0, COUNTRY},
        {"region", required_argument, 0, REGION},
        {0, 0, 0, 0}
    };
    
    int currentOption;
    while (1){
        /* getopt_long stores the option index here. */
        int option_index;

        currentOption = getopt_long (argc, argv, "F:N:C:R:",
                long_options, &option_index);

        if (currentOption == NO_MORE_OPTIONS)
            break;

        switch (currentOption){
            case 0:
                if (long_options[option_index].flag)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case FORMAT:
                strncpy(flags->format, optarg, MAX_ARG_LEN);
                break;

            case FILE_NAME:
                strncpy(flags->filename, optarg, MAX_ARG_LEN);
                break;

            case COUNTRY:
                strncpy(flags->country, optarg, MAX_ARG_LEN);
                break;

            case REGION:
                strncpy(flags->region, optarg, MAX_ARG_LEN);
                break;

            case '?':
                usage();
                getArgsClearMemory(flags);
                exit(1);
                break;

            default:
                printf("The argument parsing aborted\n");
                abort ();
        }
    }

    if(show_most_flag){
        show_languages_flag = 1;
        show_capital_flag = 1;
        show_borders_flag = 1;
    }
    if(show_all_flag){
        show_languages_flag = 1;
        show_capital_flag = 1;
        show_borders_flag = 1;
        show_flag_flag = 1;
    }
    flags->helpFlag = help_flag;
    flags->showLanguageFlag = show_languages_flag;
    flags->showCapitalFlag = show_capital_flag;
    flags->showBordersFlag = show_borders_flag;
    flags->showFlagsFlag = show_flag_flag;
 
    if (optind < argc){
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
        usage();
        getArgsClearMemory(flags);
        exit(1);
    }

    argsLogic(flags);
}

void usage(){
    printf(USAGE);
}

void argsLogic(struct argFlags* flags){
    if(flags->helpFlag){
        printf(HELP);
        getArgsClearMemory(flags);
        exit(0);
    }
    if(isDefined(flags->country) && isDefined(flags->region)){
        printf(ERR_MSG_COUNTRY_AND_REGION);
        printf(HELP);
        getArgsClearMemory(flags);
        exit(1);
    }
    if(flags->showFlagsFlag &&
            (formatIsText(flags->format) || !isDefined(flags->format))){
        printf(ERR_MSG_SHOW_FLAGS_AND_FOMAT_TEXT);
        printf(HELP);
        getArgsClearMemory(flags);
        exit(1);
    }
    if(isDefined(flags->format) && !formatIsValid(flags->format)){
        printf(ERR_MSG_OUTPUT_FORMAT_INVALID);
        printf(HELP);
        getArgsClearMemory(flags);
        exit(1);
    }
    if(outputFormatIsPnG(flags->format) && !isDefined(flags->filename)){
        printf(ERR_MSG_PNG_FORMAT_WITHOUT_OUTPUT_FILENAME);
        printf(HELP);
        getArgsClearMemory(flags);
        exit(1);
    }
}

/**
* checks if value is different from ""
*
* @s char*: value to verify
* @return 1 if true and 0 if not
*/
int isDefined(char* s){
    return strcmp(NOT_DEFINED, s);
}

/**
* checks if format entered by user is text
*
* @choice char*: flag entered by user
* @return 1 if true and 0 if not
*/
int formatIsText(char* s){
    return !strcmp(FORMAT_TEXT, s);
}

/**
* checks if format entered by user is valid
* or unambiguously equivalent to a valid region
*
* @choice char*: flag entered by user
* @return 1 if true and 0 if not
*/
int formatIsValid(char* choice){
    return !strcmp(choice, FORMAT_TEXT) || !strcmp(choice, FORMAT_DOT) ||
        !strcmp(choice, FORMAT_PNG);
}

/**
* checks if format entered by user is png
*
* @choice char*: flag entered by user
* @return 1 if true and 0 if not
*/
int outputFormatIsPnG(char* s){
    return !strcmp(s, FORMAT_PNG);
}

/**
* checks if region entered by user is valid
* or unambiguously equivalent to a valid region
*
* @choice char*: flag entered by user
* @return 1 if true and 0 if not
*/
int regionIsInvalid(char* choice){
    return !(!strcmp(choice, NOT_DEFINED) || 
            !strcmp((choice), REGION_AFRICA) ||
            !strcmp((choice), REGION_AMERICAS) || 
            !strcmp((choice), REGION_ASIA) ||
            !strcmp((choice), REGION_EUROPE) || 
            !strcmp((choice), REGION_OCEANIA) ||
            !strcmp((choice), REGION_WORLD));
}

int getArgsShowingLanguage(struct argFlags* Flags){
    return Flags->showLanguageFlag;
}

int getArgsShowingCapital(struct argFlags* Flags){
    return Flags->showCapitalFlag;
}
int getArgsShowingBorders(struct argFlags* Flags){
    return Flags->showBordersFlag;
}
int getArgsShowingFlag(struct argFlags* Flags){
    return Flags->showFlagsFlag;
}
int getArgsOutputFormatIsSet(struct argFlags* Flags){
    return isDefined(Flags->format);
}
int getArgsFilenameIsSet(struct argFlags* Flags){
    return isDefined(Flags->filename);
}
int getArgsCountryIsSet(struct argFlags* Flags){
    return isDefined(Flags->country);
}
int getArgsRegionIsSet(struct argFlags* Flags){
    return isDefined(Flags->region);
}
/**
* description:
*
* @
* @return void
*/
void getArgsClearMemory(struct argFlags* Flags){
        free(Flags->format);
        free(Flags->filename);
        free(Flags->country);
        free(Flags->region);
}
