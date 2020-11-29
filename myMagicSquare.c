///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2020
//
// Author:           Nathan Smith
// Email:            nvsmith@wisc.edu
// CS Login:         nathans
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:  https://en.wikipedia.org/wiki/Magic_square  used a different
//rotation/reflection of the siamese method that started at middle row last
//column and went up to the right
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;      // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
    int size; //user entered dimension of square

    printf("Enter magic square's size (odd integer >= 3)\n");
    scanf("%i",&size);

    //make sure size is odd
    if(size % 2 == 0){
        printf("Size must be odd.\n");
        exit(1);
    }

    //make sure size is >= 3
    if(size < 3 ){
        printf("Size must be >= 3.\n");
        exit(1);
    }

    return size;
} 
   
/* TODO:
 * Makes a magic square of size n using the alternate 
 * Siamese magic square algorithm from assignment and 
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {
   MagicSquare *squarePtr;//pointer to magicsquare struct
    //allocate memory for the magic square struct
    squarePtr = malloc(sizeof(MagicSquare));
    if(squarePtr == NULL){
      printf("Error while allocating memory.\n");
        exit(1);
    }

    squarePtr->size = n;//set dimension of square
    squarePtr->magic_square = malloc(sizeof(int *) * n);//allocate 1 d array
    if(squarePtr->magic_square == NULL){
        printf("Error while allocating memory.\n");
        exit(1);
    }
    for(int i = 0; i < n; i++){
        *(squarePtr->magic_square +i) = malloc(sizeof(int) * n);//allocate 2d array
        if(*(squarePtr->magic_square + i) == NULL){
            printf("Error while allocating memory.\n");
            exit(1);
        }
    }

    int row = n/2; //calculate row to place next
    int col = n-1; //calculate column to place next

    for(int siam = 1; siam <= n * n;){
        //specific case that would happen after adjusting for used space in top right
        if(row == -1 && col == n){
            row = 0;
            col = n-2;
        }
        else{
            if(col == n ){//wrap if out of solumn bounds
                col = 0;
            }

            if(row < 0){//wrap if out of row bounds
                row = n-1;
            }

        }
        //place to left of current if calculated space is occupied
        if(*(*(squarePtr->magic_square +row) + col)){
            col -= 2;
            row++;
        }
        //if not occupied, then place current, increment the next number
        //move up to the right
        else{
            *(*(squarePtr->magic_square +row) + col) = siam;
            siam++;
            row--;
            col++;
        }

    }


   return squarePtr;
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    FILE *outFile = fopen(filename,"w"); //open file with given name
    if(outFile == NULL){
        printf("Can't open file for writing.\n");
        exit(1);
    }
    fprintf(outFile,"%i\n",magic_square->size);//print the size on first line

    //loop through array and print square
    for(int i = 0; i < magic_square->size; i++){
        for(int j = 0; j < magic_square->size; j++){
            if(j == 0){//if first column, dont put comma before number
                fprintf(outFile,"%i",*(*(magic_square->magic_square + i) + j));
            }
            else{
                fprintf(outFile,",%i",*(*(magic_square->magic_square + i) + j));
            }
        }
        fprintf(outFile,"\n");//make sure to start new row
    }

    //close the file
    if(fclose(outFile) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    }
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
    // TODO: Check input arguments to get output filename
    if(argc == 1 || argc > 2 ) {
        printf("Usage: ./myMagicSquare <outupt_filename>\n");
    }
    char *filename;
    filename = *(argv + 1);


    // TODO: Get magin square's size from user
    int size = getSize();

    // TODO: Generate the magic square
    MagicSquare *magicSquare;
    magicSquare =  generateMagicSquare(size);

    // TODO: Output the magic square
    fileOutputMagicSquare(magicSquare,filename);

    //free all dynamically allocated memory
    for(int i =0; i< size; i++){
        free(*(magicSquare->magic_square +i) );
        *(magicSquare->magic_square +i) = NULL;
    }
    free(magicSquare->magic_square);
    magicSquare->magic_square = NULL;

    free(magicSquare);
    magicSquare = NULL;

    return 0;
} 


                                                         
//				myMagicSquare.c      

