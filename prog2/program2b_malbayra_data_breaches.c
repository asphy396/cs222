/*********************************
*
* CS222 Programming Assignment 2b
*
* Mert Albayrak (malbayra@gmu.edu)
*
* Program processes data from a 
* file and calculates various
* statistics 
*
*********************************/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define START_YEAR 2021
const char* months[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};

typedef struct Entry {
  int count;
  int year;
  char const *month;
  struct Entry* next;
} Entry;

Entry fetch_entries(FILE* file){
  Entry first_entry;
  int curr_month = 0;
  int curr_year = START_YEAR;
  Entry* curr_entry = &first_entry;

  while(fscanf(file,"%d",&(curr_entry->count))==1){ // while there are numbers to read in
    curr_entry->year = curr_year;
    curr_entry->month = months[curr_month];
    curr_entry->next = malloc(sizeof(Entry)); // allocate next entry
    curr_entry = curr_entry->next; // set list index to next entry
    
    curr_month++;
    if(curr_month==12) {
      curr_year++; // increment curr_year every 12 months
      curr_month = 0; // reset month
    }
  }
  
  return first_entry;
}

// unused
void print_entries(Entry list){
  Entry* curr = &list;
  while(curr!=NULL){
    printf("count: %d month: %s year: %d\n",curr->count,curr->month,curr->year);
    curr=curr->next;
  }
}

void print_entries_by_year(int year, Entry list){

  Entry* curr = &list;
  
  while(curr!=NULL && curr->year!=year) // seek curr to required year
    curr=curr->next;

  while(curr!=NULL && curr->year==year){
      printf("%d ",curr->count);
    curr=curr->next;
  }
 
  printf("\n");
}

int sum(int year,Entry list){
  
  Entry* curr = &list;
  int sum = 0;

  while(curr!=NULL && curr->year!=year)
    curr=curr->next;
  
  while(curr!=NULL && curr->year==year){
      sum+=curr->count;
    curr=curr->next;
  }

  return sum;
}

const char* max_breach_month(int year,Entry list){

  Entry* curr = &list;
  Entry* max = curr;

  while(curr!=NULL && curr->year!=year)
    curr=curr->next;
  
  while(curr!=NULL && curr->year==year){
    if(curr->count > max->count)
      max = curr;
    curr=curr->next;
  }

  return max->month;
}

double mean(int year,Entry list){
  return (double) sum(year,list) / 12.;
}

double stddev(int year,Entry list){
  
  double result = 0;
  double mean_ = mean(year,list);

  Entry* curr = &list;

  while(curr!=NULL && curr->year!=year)
    curr=curr->next;
  
  while(curr!=NULL && curr->year==year){
    result += pow(curr->count - mean_,2);  
    curr=curr->next;
  }
  
  return sqrt(result/12.);
}

void print_stats(int year,Entry list){
  printf("%d: ",year);
  print_entries_by_year(year,list);
  printf("%d: annual data breaches = %d\n",year,sum(year,list));
  printf("%d: month of max breaches is %s\n",year,max_breach_month(year,list));
  printf("%d: mean is: %.03f and standard deviation is %.03f\n",year,mean(year,list),stddev(year,list));
}

int main(int argc, char* argv[]){

  char path[128]; // path for file to load

  if(argc == 2) // check if command line argument was passed
    memcpy(path,argv[1],sizeof(path)); // store argument as the path
  else { // if not passed, gather input from user
    printf("Enter filename: ");
    scanf("%s",path);
  }

  FILE* file = fopen(path,"r");
  assert(file && "Error: invalid file");

  Entry entrylist = fetch_entries(file);
  //print_entries(entrylist);
  
  print_stats(2021,entrylist);
  printf("-------------------------------------\n");
  print_stats(2022,entrylist);

  return 0;
}

/* Sample run
 * asphy@framework:~/cs222/prog2$ ./build.sh && ./data data.txt
 * + gcc -Wall -Wextra -o partial program2a_malbayra_nth_partial_sum.c
 * + gcc -Wall -Wextra -o data program2b_malbayra_data_breaches.c -lm
 * 2021: 179 161 193 217 300 268 201 170 133 156 164 245
 * 2021: annual data breaches = 2387
 * 2021: month of max breaches is May
 * 2021: mean is: 198.917 and standard deviation is 47.921
 * -------------------------------------
 * 2022: 259 126 174 143 214 351 531 973 258 197 219 134
 * 2022: annual data breaches = 3579
 * 2022: month of max breaches is August
 * 2022: mean is: 298.250 and standard deviation is 230.076
*/

