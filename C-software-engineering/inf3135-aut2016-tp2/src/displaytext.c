/* displaytext.c
 *
 * @author Michael Tessier, Mathieu Loyer, Chao-Jung (Julie) Wu
 * @version 2.00.00
 * @since 2016-10-22
 */

#include "displaytext.h"

void displayTextOneCountryCoreCode(int i, struct countryArray countries, struct argFlags flags) {
    int j;
    printf("Name: %s\nCode: %s\n", countries.countries[i].name, countries.countries[i].code);
    if (getArgsShowingCapital(&flags))
        printf("Capital: %s\n", countries.countries[i].capital);
    if (getArgsShowingLanguage(&flags)) {
        printf("Languages: ");
            for(j = 0; j < countries.countries[i].languages.count; j++){
                if(j == countries.countries[i].languages.count - 1){
                    printf("%s\n", countries.countries[i].languages.strings[j]);
                    break;
                } 
                printf("%s, ", countries.countries[i].languages.strings[j]);
            }
            if (countries.countries[i].languages.count == 0)
                printf("\n");
    }
    if (getArgsShowingBorders(&flags)) {
        printf("Borders: ");
            for(j = 0; j < countries.countries[i].borders.count; j++){
                if (j == countries.countries[i].borders.count - 1){
                    printf("%s\n", countries.countries[i].borders.strings[j]);
                    break;
                } 
                printf("%s, ", countries.countries[i].borders.strings[j]);
            }
            if (countries.countries[i].borders.count == 0)
                printf("\n");
    } 
}

void displayTextAllCountry(struct countryArray countries, struct argFlags flags){
    int i;
    for(i = 0; i < countries.count; i++)
        displayTextOneCountryCoreCode(i, countries, flags);
}

void displayTextOneCountry(struct countryArray countries, struct argFlags flags){
    char code[4]; 
    int i;
    Bool isCountryFound = FALSE;
    for(i = 0; i < countries.count; i++) {
        strncpy(code, flags.country, 4);
        strtoupper(code);
        if ( strcmp(code, countries.countries[i].code) == 0) {
            displayTextOneCountryCoreCode(i, countries, flags);
            isCountryFound = TRUE;
            break;
        }
     }
    if (isCountryFound == FALSE)
        printf("error: country code \"%s\" not found\n", code);
}

void displayTextReginalCountry(struct countryArray countries, struct argFlags flags){
    if (getArgsCountryIsSet(&flags)) {
        printf("error: the length of country code is 3\n"); 
        return;
    }
    int i;
    char region[50];
    Bool isCountryFound = FALSE;
    strncpy (region, flags.region, 50);
    firstUPrestLOW (region);
    if ( strcmp(region, "World") == 0){
        displayTextAllCountry(countries, flags);
        return;
    }
    for(i = 0; i < countries.count; i++)
        if ( strcmp(region, countries.countries[i].region) == 0) {
            displayTextOneCountryCoreCode(i, countries, flags);
            isCountryFound = TRUE;
        }
    if (isCountryFound == FALSE) {
        printf("error: region name \"%s\" not found\n", flags.region);
    }
}

void createFILETextOneCountryCoreCode(FILE *fp, int i, struct countryArray countries, struct argFlags flags) {
    int j;
    fprintf(fp, "Name: %s\nCode: %s\n", countries.countries[i].name, countries.countries[i].code);
    if (getArgsShowingCapital(&flags))
        fprintf(fp, "Capital: %s\n", countries.countries[i].capital);
    if (getArgsShowingLanguage(&flags)) {
        fprintf(fp, "%s", "Languages: ");
            for(j = 0; j < countries.countries[i].languages.count; j++){
                if(j == countries.countries[i].languages.count - 1){
                    fprintf(fp, "%s\n", countries.countries[i].languages.strings[j]);
                    break;
                } 
                fprintf(fp, "%s, ", countries.countries[i].languages.strings[j]);
            }
        if (countries.countries[i].languages.count == 0)
                fprintf(fp, "\n");
    }
    if (getArgsShowingBorders(&flags)) {
        fprintf(fp, "%s", "Borders: ");
            for(j = 0; j < countries.countries[i].borders.count; j++){
                if(j == countries.countries[i].borders.count - 1){
                    fprintf(fp, "%s\n", countries.countries[i].borders.strings[j]);
                    break;
                }
                fprintf(fp, "%s, ", countries.countries[i].borders.strings[j]);
            }
            if (countries.countries[i].borders.count == 0)
                fprintf(fp, "\n");
    }
}

void createFILETextAllCountry(struct countryArray countries, struct argFlags flags){
    char filename[30] = "data/"; 
    FILE * fp;
    int i;
    strncat(filename, flags.filename, strlen(flags.filename));
    strtolower(filename);
    fp = fopen (filename, "w+");
    for(i = 0; i < countries.count; i++)
        createFILETextOneCountryCoreCode(fp, i, countries, flags);
    fclose(fp);
}

void createFILETextOneCountry(struct countryArray countries, struct argFlags flags){
    char code[4], filename[30] = "data/"; 
    int i;
    FILE * fp;
    Bool isCountryFound = FALSE;
    strncat(filename, flags.filename, strlen(flags.filename));
    strtolower(filename);
    strncpy(code, flags.country, 4);
    strtoupper(code);
    for(i = 0; i < countries.count; i++) {
        if (strcmp(code, countries.countries[i].code) == 0) {
            fp = fopen (filename, "w+");
            createFILETextOneCountryCoreCode(fp, i, countries, flags);
            fclose(fp);
            isCountryFound = TRUE;
            break;
        }
     }
    if (isCountryFound == FALSE)     
        printf("error: country code \"%s\" not found\n", code);
}

void createFILETextReginalCountry(struct countryArray countries, struct argFlags flags){
    if (getArgsCountryIsSet(&flags)) {
        printf("error: the length of country code is 3\n"); 
        return;
    }
    int i;
    char region[50], filename[30] = "data/"; 
    FILE * fp;
    Bool isCountryFound = FALSE;
    strncpy (region, flags.region, 50);
    firstUPrestLOW (region);
    if (strcmp(region, "World") == 0){
        createFILETextAllCountry(countries, flags);
        return;
    }
    strncat(filename, flags.filename, strlen(flags.filename));
    strtolower(filename);
    fp = fopen (filename, "w+");
    for(i = 0; i < countries.count; i++)
        if (strcmp(region, countries.countries[i].region) == 0) {
            createFILETextOneCountryCoreCode(fp, i, countries, flags);
            isCountryFound = TRUE;
        }
    if (isCountryFound == FALSE) 
        printf("error: region name \"%s\" not found\n", flags.region);
    fclose(fp);
}
