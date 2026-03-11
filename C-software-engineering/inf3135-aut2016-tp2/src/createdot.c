/* createdot.c
 *
 * @author Chao-Jung (Julie) Wu
 * @version 2.00.04
 * @since 2016-10-22
 */

#include "createdot.h"

void output_DOT_PNG(struct countryArray countries, struct argFlags flags) {
    if ( strcmp(flags.format, "dot") == 0) {
        if (strlen(flags.filename) == 0) {
            if (strlen(flags.country) == 3)
                displayDOTstring (countries, flags);
            else displayRegionalDOTstring (countries, flags);
            return;
        } 
        if (strlen(flags.country) == 3) {
            createDOTstringFile(countries, flags);
            return;
        }
        else if (strcmp(flags.region, "") == 0) {
            createWorldDOTstringFile(countries, flags);
            return;
        }
        else {
            createRegionalDOTstringFile(countries, flags);
            return;
        }
    }
    if ( strlen(flags.filename) > 5 && strcmp(flags.format, "png") == 0) {
        createPNGfile(countries, flags); 
        return;
    }
    else 
        printf("error: this program does not support:   \nthe format \"%s\" or the filename \"%s\".\nread --help\n\n", flags.format, flags.filename);
}

struct country searchCountrybyCode(const char* code, const struct countryArray countries){
    struct country country;
    int i;
    bool found = false;
    char upperCode[4];
    strncpy(upperCode, code, strlen(code)+1);
    strtoupper(upperCode);
    for (i = 0; i < countries.count; i++)
        if (strcmp(countries.countries[i].code, upperCode) == 0){
            found = true;
            break;
        }
    if (found) countrycpy(&country, countries.countries[i]);
    else {
        printf("error: country code \"%s\" not found\n", code);
    }
    return country;
}

void countrycpy(struct country* country, const struct country source) {
    int j;
    strncpy(country->name, source.name, strlen(source.name)+1);
    strncpy(country->code, source.code, strlen(source.code)+1);
    strncpy(country->capital, source.capital, strlen(source.capital)+1);
    strncpy(country->region, source.region, strlen(source.region)+1);
    country->languages.count = source.languages.count;
    country->borders.count = source.borders.count;
    for (j = 0; j < country->languages.count; j++)
        country->languages.strings[j] = source.languages.strings[j];
    for (j = 0; j < country->borders.count; j++)
        country->borders.strings[j] = source.borders.strings[j];
}

void createDOTstringFile(const struct countryArray countries, const struct argFlags flags) {
    char  *dotstring, suffix[5] = ".dot", filename[36] = "data/"; 
    FILE * fp;
    dotstring = (char*)calloc(1200, sizeof(char));
    createDOTstring(dotstring, countries, flags);
    if (strcmp(flags.filename, "") == 0) {
        strncat(filename, flags.country, strlen(flags.country)+1);
        strncat (filename, suffix, strlen(suffix)+1);
    } else {
        strncat(filename, flags.filename, strlen(flags.filename)-4);
        strncat(filename, ".dot", strlen(".dot")+1);
    }
    strtolower(filename);
    fp = fopen (filename, "w+");
    fprintf(fp, "%s", dotstring);
    fclose(fp);
    free(dotstring);  
}

void createDOTnode(char* dotstring, const char* code, const struct countryArray countries, struct argFlags flags) {
    int i;
    char codeCopy[4];
    struct country country = searchCountrybyCode(code, countries);
    if (strlen(country.code) == 0) 
        return;
    strncpy(codeCopy, code, strlen(code)+1);
    strtolower(codeCopy);
    char s1[300] = "    ";
    char s2[300] = " [\n        shape = none,\n        label = <<table border=\"0\" cellspacing=\"0\">\n";
    char s3[300] = "            <tr><td align=\"center\" border=\"1\" fixedsize=\"true\" width=\"200\" height=\"100\"><img src=\"./data/countries/data/";
    char s4[300] = ".png\" scale=\"true\"/></td></tr>\n";
    char s5[300] = "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: ";
    char s6[300] = "</td></tr>\n            <tr><td align=\"left\" border=\"1\"><b>Code</b>: ";
    char s7[300] = "</td></tr>\n";
    char s8[300] = "            <tr><td align=\"left\" border=\"1\"><b>Capital</b>: ";
    char s10[300] = "            <tr><td align=\"left\" border=\"1\"><b>Language</b>: ";
    char s11[300] = "<br />";
    char s12[300] = ", ";
    char s14[300] = "            <tr><td align=\"left\" border=\"1\"><b>Borders</b>: ";
    char s18[300] = "        </table>>\n    ];\n";

    strncat(dotstring, s1, strlen(s1)+1);
    strncat(dotstring, codeCopy, strlen(codeCopy)+1);
    strncat(dotstring, s2, strlen(s2)+1);
    if (flags.showFlagsFlag == 1) {
        strncat(dotstring, s3, strlen(s3)+1);
        strncat(dotstring, codeCopy, strlen(codeCopy)+1);
        strncat(dotstring, s4, strlen(s4)+1);
    }
    strncat(dotstring, s5, strlen(s5)+1);
    strncat(dotstring, country.name, strlen(country.name)+1);
    strncat(dotstring, s6, strlen(s6)+1);
    strtoupper (codeCopy);
    strncat(dotstring, codeCopy, strlen(codeCopy)+1);
    strncat(dotstring, s7, strlen(s7)+1);
    if (flags.showCapitalFlag == 1) {
        strncat(dotstring, s8, strlen(s8)+1);
        strncat(dotstring, country.capital, strlen(country.capital)+1);
        strncat(dotstring, s7, strlen(s7)+1);
    }
    if (flags.showLanguageFlag == 1) {
        strncat(dotstring, s10, strlen(s10)+1);
        for (i = 0; i < country.languages.count; i++){
            if (i%3 == 2)
                strncat(dotstring, s11, strlen(s11)+1);
            strncat(dotstring, country.languages.strings[i], strlen(country.languages.strings[i])+1);
            if (i < country.languages.count-1)
                strncat(dotstring, s12, strlen(s12)+1);
        }
        strncat(dotstring, s7, strlen(s7)+1);
    }
    if (flags.showBordersFlag == 1) {
        strncat(dotstring, s14, strlen(s14)+1);
        for (i = 0; i < country.borders.count; i++) {
            if (i%5 == 4) 
                strncat(dotstring, s11, strlen(s11)+1);
            strncat(dotstring, country.borders.strings[i], strlen(country.borders.strings[i])+1);
            if (i < country.borders.count-1)
                strncat(dotstring, s12, strlen(s12)+1);
        }
        strncat(dotstring, s7, strlen(s7)+1);
    }
    strncat(dotstring, s18, strlen(s18)+1);
}

void createDOTstring(char* dotstring, const struct countryArray countries, struct argFlags flags) {
    if (strcmp(flags.country, "") == 0) 
        return;
    struct country country = searchCountrybyCode(flags.country, countries);
    if (strlen(country.code) == 0) 
        return;
    strncat(dotstring, "graph {\n", strlen("graph {\n")+1);
    createDOTnode(dotstring, flags.country, countries, flags);
    strncat(dotstring, "}\n", strlen("}\n")+1);
}

void displayDOTstring (const struct countryArray countries, struct argFlags flags) {
    char* dotstring;
    dotstring = (char*)calloc(1200, sizeof(char));
    createDOTstring(dotstring, countries, flags);
    printf("%s", dotstring);
    free(dotstring);
}

void createPNGfile(const struct countryArray countries, const struct argFlags flags) {
    char dot_filename[36] = "data/";
    strncat(dot_filename, flags.filename, strlen(flags.filename)-4);
    strncat(dot_filename, ".dot", strlen(".dot")+1);
    strtolower(dot_filename);    

    if (strlen(flags.country) == 3)
        createDOTstringFile(countries, flags);
    else if (strcmp(flags.region, "world") == 0 || strlen(flags.region) == 0)
        createWorldDOTstringFile(countries, flags);
    else createRegionalDOTstringFile(countries, flags);
    if (! exists(dot_filename))
        return;

    char cmd[100] = "neato -Goverlap=false -Tpng -o data/";
    strncat(cmd, flags.filename, strlen(flags.filename)+1);
    strncat(cmd, " ", strlen(" ")+1);
    strncat(cmd, dot_filename, strlen(dot_filename)+1);
    system(cmd);
}

bool exists(const char *fname) {
    FILE *file;
    file = fopen(fname, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

bool linkageExists(char* value, struct linkage *linkage, int nblinkage) {
    int i;
    strtolower(value);
    for (i = 0; i < nblinkage; i++) {
        if ( strcmp(linkage->link[i].key, value) == 0 ) 
            return true;
    }
    return false;
}

void createRegionalDOTstringFile(const struct countryArray countries, struct argFlags flags) {
    char *dotstring, suffix[5] = ".dot", filename[36] = "data/", region[50]; 
    FILE * fp;
    int i;
    bool isCountryFound = false;
    struct linkage linkage;
    strncat(filename, flags.filename, strlen(flags.filename)-4);
    strncat (filename, suffix, strlen(suffix)+1);
    strtolower(filename);
    fp = fopen (filename, "a+");
    strncpy(region, flags.region, strlen(flags.region)+1);
    firstUPrestLOW (region);
    dotstring = (char*)calloc(1200, sizeof(char));
    strncpy(dotstring, "graph {\n", strlen("graph {\n")+1);
    for (i = 0; i < countries.count; i++)
        if (strcmp(countries.countries[i].region, region) == 0) {
            createDOTnode(dotstring, countries.countries[i].code, countries, flags);
            fprintf(fp, "%s", dotstring);
            isCountryFound = true;
            strncpy(dotstring, "", strlen("")+1);
        }
    if (isCountryFound == false) {
        printf("error: \"%s\" region not found\n", flags.region);
        fclose(fp);
        remove(filename);
        return;
    }
    mapLinkage(&linkage, region, countries);
    for (i = 0; i < linkage.count; i++)
        fprintf(fp, "    %s -- %s;\n", linkage.link[i].key, linkage.link[i].value);
    fprintf(fp, "}\n");
    fclose(fp);
    free(dotstring);  
}

void displayRegionalDOTstring(const struct countryArray countries, struct argFlags flags) {
    if (strlen(flags.country) > 0) {
        printf("error: the length of country code is 3\n"); 
        return;
    }
    char *dotstring, region[50]; 
    int i;
    struct linkage linkage;
    bool isCountryFound = false;
    strncpy(region, flags.region, strlen(flags.region)+1);
    firstUPrestLOW (region);
    dotstring = (char*)calloc(1200, sizeof(char));
    strncpy(dotstring, "graph {\n", strlen("graph {\n")+1);
    for (i = 0; i < countries.count; i++)
        if (strcmp(region, "World") == 0 || strlen(region) == 0) {
            createDOTnode(dotstring, countries.countries[i].code, countries, flags);
            printf("%s", dotstring);
            isCountryFound = true;
            strncpy(dotstring, "", strlen("")+1);
        }
        else if (strcmp(countries.countries[i].region, region) == 0) {
            createDOTnode(dotstring, countries.countries[i].code, countries, flags);
            printf("%s", dotstring);
            isCountryFound = true;
            strncpy(dotstring, "", strlen("")+1);
        }
    if (isCountryFound == false) {
        printf("error: \"%s\" region not found\n", flags.region);
        return;
    }
    mapLinkage(&linkage, region, countries);
    for (i = 0; i < linkage.count; i++)
        printf("    %s -- %s;\n", linkage.link[i].key, linkage.link[i].value);
    printf("}\n");
    free(dotstring);  
}

void createWorldDOTstringFile(const struct countryArray countries, struct argFlags flags) {
    char *dotstring, suffix[5] = ".dot", filename[36] = "data/", region[6] = "World"; 
    FILE * fp;
    int i;
    struct linkage linkage;
    strncat(filename, flags.filename, strlen(flags.filename)-4);
    strncat (filename, suffix, strlen(suffix)+1);
    strtolower(filename);    
    fp = fopen (filename, "a+");
    dotstring = (char*)calloc(1200, sizeof(char));
    strncpy(dotstring, "graph {\n", strlen("graph {\n")+1);  
    for (i = 0; i < countries.count; i++) {
        createDOTnode(dotstring, countries.countries[i].code, countries, flags);
        fprintf(fp, "%s", dotstring);
        strncpy(dotstring, "", strlen("")+1);
    }
    mapLinkage(&linkage, region, countries);
    for (i = 0; i < linkage.count; i++)
        fprintf(fp, "    %s -- %s;\n", linkage.link[i].key, linkage.link[i].value);
    fprintf(fp, "}\n");
    fclose(fp);
    free(dotstring);
}

void mapLinkage(struct linkage *linkage, char* region, const struct countryArray countries) {
    int i, j = 0, k = 0;
    if (strcmp(region, "World") == 0 || strlen(region) == 0) {
        for (i = 0; i < countries.count; i++)
            for (k = 0; k < countries.countries[i].borders.count; k++)
                if( ! linkageExists(countries.countries[i].borders.strings[k], linkage, j) ) {
                    strncpy(linkage->link[j++].key, countries.countries[i].code, strlen(countries.countries[i].code)+1);
                    strncpy(linkage->link[j-1].value, countries.countries[i].borders.strings[k], strlen(countries.countries[i].borders.strings[k])+1);
                    strtolower(linkage->link[j-1].key);
                    strtolower(linkage->link[j-1].value);
                }
        linkage->count = j;
    } 
    else {
        for (i = 0; i < countries.count; i++)
            if (strcmp(countries.countries[i].region, region) == 0)
                for (k = 0; k < countries.countries[i].borders.count; k++)
                    if( ! linkageExists(countries.countries[i].borders.strings[k], linkage, j) ) {
                        strncpy(linkage->link[j++].key, countries.countries[i].code, strlen(countries.countries[i].code)+1);
                        strncpy(linkage->link[j-1].value, countries.countries[i].borders.strings[k], strlen(countries.countries[i].borders.strings[k])+1); 
                        strtolower(linkage->link[j-1].key);
                        strtolower(linkage->link[j-1].value);
                    }
        linkage->count = j;
    }
}
