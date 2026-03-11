/**
 * This tp1.c program displays a mountain with water in its concaves to the standard output 
 * @author Chao-Jung (Julie) Wu
 * @version 1.02.06 
 * @since 2016-09-17
 */

/**
 * Headers
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Constants
 */
#define CHARACTER_EMPTY '-'
#define HEIGHT_MAX 15
#define WIDTH_MAX 20
#define DELIM ','

/**
  * Structures of data
  */
struct TabHeights {
    unsigned int width;
    char content[WIDTH_MAX + 1];
};

struct Mountain {
    unsigned int height;
    unsigned int width;
    char content[WIDTH_MAX][HEIGHT_MAX];
};

/**
  * Prototypes
  */
bool isSingleCharacter(char *str);
bool isDigit(char *str, const char delim);
bool calculateHeights(char *s, struct TabHeights *tab, const char delim);
bool areValideHeights(struct TabHeights *tab);
unsigned int obtainMaxHeightInTab(struct TabHeights *tab);
void buildMountain(char earth, struct TabHeights *tab, 
                                    struct Mountain *mountain);
void displayMountain(struct Mountain *mountain);
bool shouldContainWater(struct Mountain *mountain, struct TabHeights *tab, char earth, char water);
unsigned int minBarrier (char a, char b);
void addWater (char earth, char water, struct Mountain *mountain, 
                                unsigned int h, unsigned int l, unsigned int minBarrier);
/**
 * Main
 *
 * @param    argc    the nomber of arguments passed
 * @param    argv    the table of arguments passed
 * @return   0       means ending the program normally 
 * @return   1       means exiting the program for user's error
 */
int main (int argc, char *argv[]) {

    struct TabHeights tab; 
    tab.width = 0; 

    struct Mountain mountain; 
    mountain.height = 0;
    mountain.width = 0;

    const char delim = DELIM;
  
	if (argc != 4){
		printf("Nombre d'arguments invalides: il en faut 3\n");
		return 1;
	}


    char *earth = argv[1];
    if (! isSingleCharacter( earth ) ) {
        printf("Code XA invalide: il doit etre un caractere unique\n");
        return 1;
    }


    char *water = argv[2];
    if (! isSingleCharacter( water ) ) {
        printf("Code eau invalide: il doit etre un caractere unique\n");
        return 1;
    }


    if (*earth == *water) {
        printf("Les codes doivent etre distincts\n");
        return 1;
    }


    if ( !  isDigit( argv[3], delim)  ) {
        printf("Hauteur invalide: la hauteur doit etre un nombre entre 0 et 15\n");
        return 1;
    }


    calculateHeights(argv[3], &tab, delim); 
                                         

    if ( ( tab.width > WIDTH_MAX ) || ( tab.width == 0 ) ) {
        printf("Largeur invalide: le nombre de hauteurs doit etre entre 1 et 20\n");
        return 1;
    }


    if ( ! areValideHeights(&tab) ){
       printf ("Hauteur invalide: la hauteur doit etre un nombre entre 0 et 15\n");
       return 1;
    };

    
    buildMountain(*earth, &tab, &mountain);

    shouldContainWater(&mountain, &tab, *earth, *water);

    displayMountain( &mountain );

	return 0;
}


/**
 * Functions
 */

/**
 * validates if a string only contains a character
 */
bool isSingleCharacter(char *str) {
    if (strlen(str) == 1)
        return true;
    else
        return false;
};


/**
 * validates if a character between the delimiter is a digit, digit by digit
 *
 * @param    str    the string whose content to be verified
 * @param    delim  the delimiter
 */
bool isDigit(char *str, const char delim ) {
    int count = 0; 
    while(  str[++count] != '\0'  );
    
    int i;
    for (i = 0; i < count; i++) {
        if  ( ! (str[i] == delim) ) 
            if (! isdigit( (char)str[i] )) 
                return false;
    }
    return true;
}



/**
 * registers numbers in a structured table from a string seperated by the delimiter
 * in this format: tab.content[index] = number
 * and assigns the table with its width
 *
 * @param str    the string to be tokenized into numbers
 * @param tab    the table to receive the numbers
 * @param delim  the delimiter
 */
bool calculateHeights (char *str, struct TabHeights *tab, const char delim) {
    char *height, unstableS[strlen(str)], *ptr2;
    int counter = 0;
    
    strcpy ( unstableS, str ); 

    height = strtok ( unstableS, &delim ); 

    while ( height != NULL ) {  

        if (counter > WIDTH_MAX)
            break; 
        
        tab->content[ counter ] = strtod(height, &ptr2); 
        height = strtok(NULL, &delim); 
        counter++; 
    };

    tab->width = counter;  
    return true;
}



/**
 * validates that the values of heights are within range
 */
bool areValideHeights (struct TabHeights *tab){
    int i;
    for (i = 0; i < tab->width; i++)
        if (!  ( tab->content[i] <= HEIGHT_MAX  && tab->content[i] >= 0 ) )
            return false;
    return true;
}


/**
 * determines the highest number among the numbers in the table
 *
 * @param  tab       a structured table that stores numbers in its content attribute
 * @return Highest   the highest number
 */
unsigned int obtainMaxHeightInTab(struct TabHeights *tab){
    int i, Highest=0;
    for (i = 0; i< tab->width; i++)
         if (tab->content[i] > Highest)
             Highest = tab->content[i];
    return Highest;
}



/** 
 * assigns the symbols for earth and empty spcae in the matrix representing the mountain
 *
 * @param  earth      the symbol for earth
 * @param  tab        a structured table that stores numbers in its content attribute
 *                    and size of the table in width
 * @param  mountain   a 2D structured matrix to be assigned symbols
 */
void buildMountain(char earth, struct TabHeights *tab, struct Mountain *mountain){
    int i, j;
    mountain->height = obtainMaxHeightInTab(tab);
    mountain->width = tab->width;
    for (i = 0; i < mountain->width; i++){
        for (j = 0; j < tab->content[i]; j++)
            mountain->content[i][j] = earth;
        for (j = tab->content[i]; j < mountain->height; j++)
            mountain->content[i][j] = CHARACTER_EMPTY;
    };
}



/**
 * finds the concaves in the mountain and
 * replaces the empty spcae with water symbol
 *
 * @param  mountain    a 2D structured matrix to be assigned symbols
 * @param  tab         a structured table that stores numbers and width
 * @param  earth       the symbol for earth
 * @param  water       the symbol for water
 */ 
bool shouldContainWater(struct Mountain *mountain, struct TabHeights *tab, char earth, char water) {
    unsigned int i, j, rb, lb, min;
    for (i = 0; i < tab->width; i++)

        if (tab->content[ i ] > tab->content[ i+1 ])
            for (j = i + 2 ; j < tab->width; j++)
                if (tab->content[ j ] > tab->content[ i+1 ]) {  
                    rb = i;
                    lb = j;
                    min = minBarrier(tab->content[ i ], tab->content[ j ]);
                    addWater (earth, water, mountain, rb, lb, min);  
            };
    return true;
}


/**
 * returns the smaller number between the two parameters
 */
unsigned int minBarrier (char a, char b) {
    if (a > b) 
        return b;
    else return a;
}


/**
 * replaces the empty spcae with water symbol
 *
 * @param  earth       the symbol for earth
 * @param  water       the symbol for water
 * @param  mountain    a 2D structured matrix to be assigned symbols
 * @param  rb          the height of right side barrier
 * @param  lb          the height of left side barrier
 * @param  min         the water level in the concave, which is the smaller number between rb and lb
 */
void addWater (char earth, char water, struct Mountain *mountain, unsigned int rb, unsigned int lb, unsigned int min) {
    int i, j;
    for (j = rb + 1; j < lb; j++)
        for (i = 0; i < min ; i++)
            if (mountain->content[j][i] == CHARACTER_EMPTY) 
                mountain->content[j][i] = water;
}



/**
 * reads through the mountain matrix, and 
 * prints from the top to the bottom of the mountain
 */
void displayMountain(struct Mountain *mountain) {
    int i, j;
    for (j = ( (mountain->height) -1 ); j >=0; j--){
        for (i = 0; i < mountain->width; i++)
            printf ("%c", mountain->content[ i ][ j ]);
        printf("\n");
    }   
}
