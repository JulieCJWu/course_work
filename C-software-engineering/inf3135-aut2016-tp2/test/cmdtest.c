/* cmdtest.c
 *
 * @author Chao-Jung (Julie) Wu
 * @version 1.00.06
 * @since 2016-11-09
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void separateLine (char* cmd, char* testname, char* logfile);
bool exists_non_empty(const char *fname);
bool hasContent(FILE *f);




int main(){
    system("make clean");
    system("make");
    
    char cmd[200], redirected[100] =  " >> ", testname[10], logfile[60] = "log_cmdtest_tp2output.txt";
    int response = 0;
    strcat(redirected, logfile);
    
    printf("%s\n", "\nThis test suite only verifies if the command line is executed normally, \nand if output file is generated with content. \nIt does not verify if the outputs are correct.");
    printf("%s\n", "------- tests begin -------------------------------");




    strcpy(testname, "test1");
    separateLine (cmd, testname, logfile);
    //#1 Can
    strcpy(cmd, "./bin/tp2 --country Can --show-languages --show-capital --show-borders");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test1");
    else printf("%s\n\n", "NOT pass: test1");

    strcpy(testname, "test2");
    separateLine (cmd, testname, logfile);
    //#2 invalid country name
    strcpy(cmd, "./bin/tp2 --country CAX --show-languages --show-capital --show-borders");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test2");
    else printf("%s\n\n", "NOT pass: test2");

    strcpy(testname, "test3a");
    separateLine (cmd, testname, logfile);
    //#3a can, 2 languages formatting
    strcpy(cmd, "./bin/tp2 --country can --show-languages --show-capital --show-borders");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test3a");
    else printf("%s\n\n", "NOT pass: test3a");
    
    strcpy(testname, "test3b");
    separateLine (cmd, testname, logfile);
    //#3b usa, 2 borders formatting
    strcpy(cmd, "./bin/tp2 --country usa --show-languages --show-capital --show-borders");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test3b");
    else printf("%s\n\n", "NOT pass: test3b");

    strcpy(testname, "test3c");
    separateLine (cmd, testname, logfile);
    //#3b usa, 2 borders formatting
    strcpy(cmd, "./bin/tp2 --country usa --show-languages --show-capital --show-borders --output-filename test3c.txt");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test3c");
    else printf("%s\n\n", "NOT pass: test3b");

    strcpy(testname, "test4a");
    separateLine (cmd, testname, logfile);
    //#4a
    strcpy(cmd, "./bin/tp2 --region oceania --show-languages --show-capital --show-borders");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test4a");
    else printf("%s\n\n", "NOT pass: test4a");

    strcpy(testname, "test4b");
    separateLine (cmd, testname, logfile);
    //#4b
    strcpy(cmd, "./bin/tp2 --region Oceania --show-languages --show-capital --show-borders --output-filename test4b.txt");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test4b");
    else printf("%s\n\n", "NOT pass: test4b");

    strcpy(testname, "test4c");
    separateLine (cmd, testname, logfile);
    //#4c invalid region name
    strcpy(cmd, "./bin/tp2 --region Oceaniax --show-languages --show-capital --show-borders");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test4c"); 
    else printf("%s\n\n", "NOT pass: test4c"); 

    strcpy(testname, "test4d");
    separateLine (cmd, testname, logfile);
    //#4d 
    strcpy(cmd, "./bin/tp2 --region Africa --show-languages --show-capital --show-borders");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test4d"); 
    else printf("%s\n\n", "NOT PASS: test4d");
     
    strcpy(testname, "test4e");
    separateLine (cmd, testname, logfile);
    //#4c invalid region name
    strcpy(cmd, "./bin/tp2 --region Europe --show-languages --show-capital --show-borders");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test4e"); 
    else printf("%s\n\n", "NOT pass: test4e"); 
 
    strcpy(testname, "test5a");
    separateLine (cmd, testname, logfile);
    //#5a
    strcpy(cmd, "./bin/tp2 --country can --output-format text");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test5a");
    else printf("%s\n\n", "NOT pass: test5a");
    
    strcpy(testname, "test5b");
    separateLine (cmd, testname, logfile);
    //#5b
    strcpy(cmd, "./bin/tp2 --country can --output-format dot --show-languages --show-capital \
                 --show-borders --show-flag");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) printf("%s\n\n", "pass: test5b");
    else printf("%s\n\n", "NOT pass: test5b");


    strcpy(testname, "test6");
    separateLine (cmd, testname, logfile);
    //#6
    strcpy(cmd, "./bin/tp2 --country can --show-languages --show-capital --show-borders \
                 --show-flag --output-format dot --output-filename canada_6.dot");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) {
        if (exists_non_empty("data/canada_6.dot"))
            printf("%s\n\n", "pass: test6, \"data/canada_6.dot\" is generated with content");
    } else printf("%s\n\n", "NOT pass: test6, \"data/canada_6.dot\" is not generated with content");
   
    strcpy(testname, "test7a");
    separateLine (cmd, testname, logfile);
    //#7a
    strcpy(cmd, "./bin/tp2 --country fra --show-languages --show-capital --show-borders \
                 --show-flag --output-format png --output-filename fra_7.png");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) {
        if (exists_non_empty("data/fra_7.dot") && exists_non_empty("data/fra_7.png") )
            printf("%s\n\n", "pass: test7a,  \"data/fra_7.dot\" and \"data/fra_7.png\" are generated with content");
        else printf("%s\n\n", "NOT pass: test7a,  \"data/fra_7.dot\" and \"data/fra_7.png\" are not generated with content");
    } else printf("%s\n\n", "NOT pass: test7a,  \"data/fra_7.dot\" and \"data/fra_7.png\" are not generated with content");

    strcpy(testname, "test7b");
    separateLine (cmd, testname, logfile);
    //#7b not specify png filename, reject the task
    strcpy(cmd, "./bin/tp2 --country fra --show-languages --show-capital --show-borders \
                 --show-flag --output-format png");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response != 0) printf("%s\n\n", "pass: test7b");
    else printf("%s\n\n", "NOT pass: test7b");

    strcpy(testname, "test8");
    separateLine (cmd, testname, logfile);
    //#8
    strcpy(cmd, "./bin/tp2 --region Asia --show-languages --show-capital --show-borders \
                 --show-flag --output-format png --output-filename asia.png");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) {
        if (exists_non_empty("data/asia.dot") && exists_non_empty("data/asia.png"))
            printf("%s\n\n", "pass: test8, \"data/asia.dot\" and \"data/asia.png\" are generated with content");
        else printf("%s\n\n", "NOT pass: test8, \"data/asia.dot\" and \"data/asia.png\" are not generated with content");
    } else printf("%s\n\n", "NOT pass: test8, \"data/asia.dot\" and \"data/asia.png\" are not generated with content");

    strcpy(testname, "test9a");
    separateLine (cmd, testname, logfile);
    //#9a
    strcpy(cmd, "./bin/tp2 --region Europe --show-languages --show-capital --show-borders \
                 --show-flag --output-format png --output-filename europe.png");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) {
        if (exists_non_empty("data/europe.dot") && exists_non_empty("data/europe.png"))
            printf("%s\n\n", "pass: test9a, \"data/europe.dot\" and \"data/europe.png\" are generated with content");
        else printf("%s\n\n", "NOT pass: test9a, \"data/europe.dot\" and \"data/europe.png\" are not generated with content");
    } else printf("%s\n\n", "NOT pass: test9a, \"data/europe.dot\" and \"data/europe.png\" are not generated with content");

    strcpy(testname, "test9b");
    separateLine (cmd, testname, logfile);
    //#9b
    strcpy(cmd, "./bin/tp2 --region Africa --show-languages --show-capital --show-borders \
                 --show-flag --output-format png --output-filename africa.png");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) {
        if (exists_non_empty("data/africa.dot") && exists_non_empty("data/africa.png"))
            printf("%s\n\n", "pass: test9b, \"data/africa.dot\" and \"data/africa.png\" are generated with content");
        else printf("%s\n\n", "NOT pass: test9b, \"data/africa.dot\" and \"data/africa.png\" are not generated with content");
    } else printf("%s\n\n", "NOT pass: test9b, \"data/africa.dot\" and \"data/africa.png\" are not generated with content");

    strcpy(testname, "test9c");
    separateLine (cmd, testname, logfile);
    //#9b
    strcpy(cmd, "./bin/tp2 --region Oceania --show-languages --show-capital --show-borders \
                 --show-flag --output-format png --output-filename oceania.png");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) {
        if (exists_non_empty("data/oceania.dot") && exists_non_empty("data/oceania.png"))
            printf("%s\n\n", "pass: test9c, \"data/oceania.dot\" and \"data/oceania.png\" are generated with content");
        else printf("%s\n\n", "NOT pass: test9c, \"data/oceania.dot\" and \"data/oceania.png\" are not generated with content");
    } else printf("%s\n\n", "NOT pass: test9c, \"data/oceania.dot\" and \"data/oceania.png\" are not generated with content");

    strcpy(testname, "test10");
    separateLine (cmd, testname, logfile);
    //#10
    strcpy(cmd, "./bin/tp2 --show-languages --show-capital --show-borders \
                 --show-flag --output-format png --output-filename world.png");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) {
        if (exists_non_empty("data/world.dot") && exists_non_empty("data/world.png"))
            printf("%s\n\n", "pass: test10, \"data/world.dot\" and \"data/world.png\" are generated with content");
        else printf("%s\n\n", "NOT pass: test10, \"data/world.dot\" and \"data/world.png\" are not generated with content");
    } else printf("%s\n\n", "NOT pass: test10, \"data/world.dot\" and \"data/world.png\" are not generated with content");

    strcpy(testname, "test11");
    separateLine (cmd, testname, logfile);
    //#11 generating a text file
    strcpy(cmd, "./bin/tp2 --country can --show-borders --output-filename can.txt");
    strcat(cmd, redirected);
    response = system(cmd);
    if (response == 0) {
        if (exists_non_empty("data/can.txt"))
            printf("%s\n\n", "pass: test11, \"data/can.txt\" is generated with content");
    } else printf("%s\n\n", "NOT pass: test11, \"data/can.txt\" is not generated with content");

    strcpy(testname, "test12");
    separateLine (cmd, testname, logfile);
    //#11 invalid region for dot file
    strcpy(cmd, "./bin/tp2 --output-format dot --region x --output-filename test123.dot");
    strcat(cmd, redirected);
    response = system(cmd);
    if (! exists_non_empty("data/test123.dot"))
        printf("%s\n\n", "pass: test12");
    else printf("%s\n\n", "NOT pass: test12");








    printf("%s\n", "END OF CMDTEST");
    return 0;
}




void separateLine (char* cmd, char* testname, char* logfile) {
    strcpy(cmd, "echo \"\n=== \"");
    strcat(cmd, testname);
    strcat(cmd, " ========================================== >> ");
    strcat(cmd, logfile);
    system(cmd);
}

bool exists_non_empty(const char *fname) {
    FILE *file;
    file = fopen(fname, "r");
    if (file)
        return hasContent(file);
    return false;
}

bool hasContent(FILE *f) {
    int size = 0;
    fseek(f, 0, SEEK_END); 
    size = ftell(f);
    fclose(f);
    return size > 20;
}

