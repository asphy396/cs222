/*********************************
* 
* CS222 Programming Assignment #1
*
* Mert Albayrak (malbayra@gmu.edu)
* 
* Program allows for the input of 
* an integer, manipulates it, and 
* then displays a result.
*
*********************************/

#include <stdlib.h>
#include <stdio.h>

#define MULTIPLIER_CONSTANT 2
#define SUBTRACTION_CONSTANT 100

int main(int argc, char* argv[]){

  int input; // declare variable to store user input in

  if(argc == 2) // check if command line argument was passed
    input = atoi(argv[1]); // store argument as the input
  else { // if not passed, gather input from user
    printf("Enter integer: ");
    scanf("%d",&input);
  }

  input = input * MULTIPLIER_CONSTANT - SUBTRACTION_CONSTANT;

  printf("Result %d, formatted as %.2f\n",input,(double)input);

  exit(EXIT_SUCCESS);
}
