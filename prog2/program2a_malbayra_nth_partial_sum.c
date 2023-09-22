/*********************************
*
* CS222 Programming Assignment 2a
*
* Mert Albayrak (malbayra@gmu.edu)
*
* Program prompts user for an 
* integer, and computes the
* partial sum using two approaches
* 
*********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define RANDOM_N 0

int calculate(int input){
  if(input == 0) return 0; // base case 
  return input + calculate(input-1); // add previous number
}

int getInput(void){
  char buf[128]; // buffer to hold line
  fgets(buf,sizeof(buf),stdin); // get user input from stdin
  return atoi(buf); // convert line to integer 
}

int main(void){

  int input = 0;

  if(RANDOM_N){
    srand(time(0)); // seed rng
    input = rand()%15+1;
    assert(input >= 1); 
    printf("Random number n in between 1 and 15: %d\n",input);
  } else {
    // Prompt user 
    printf("Please enter an integer: ");
    input = getInput();
  }

  // loop until positive int is entered
  while(input<1){ // if RANDOM_N is set, input is consequently >=1
    printf("n must be > 0. Re-enter a positive int (n > 0): ");
    input = getInput();
  }

  int result1 = (input*(input+1))/2; // equation (int divison doesnt matter since result of multiply is inherently even)
  int result2 = calculate(input); // function

  printf("Result with formula: %d\nResult with function: %d\n",result1,result2);
  printf("The two approaches are%s equal\n",result1==result2 ? "\0" : " not");

  return EXIT_SUCCESS;
}

/* Sample run (#define RANDOM_N 0)
 * asphy@framework:~/cs222/prog2$ ./build.sh && ./partial
 * + gcc -o partial program2_malbayra_nth_partial_sum.c
 * Please enter an integer: c
 * n must be > 0. Re-enter a positive int (n > 0): -3
 * n must be > 0. Re-enter a positive int (n > 0): 5
 * Result with formula: 15
 * Result with function: 15
 * The two approaches are equal
 */

/* Sample run (#define RANDOM_N 0)
 * asphy@framework:~/cs222/prog2$ ./build.sh && ./partial
 * + gcc -o partial program2_malbayra_nth_partial_sum.c
 * Random number n in between 1 and 15: 14
 * Result with formula: 105
 * Result with function: 105
 * The two approaches are equal
 */
