#include <stdio.h>

int main(void){

  char* mon[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};

  char mon2[4][4] = {"Jan","Feb","Mar","Apr"};

  printf("Adr of mon: %p\n",&mon);
  for(size_t i=0;i<12;i++)
    printf("[%p]: mon[%02zu]: %p -> %s\n",&mon[i],i,mon[i],mon[i]);
  
  printf("\nAdr of mon2: %p\n",&mon);
  for(size_t i=0;i<4;i++)
    printf("[%p]: mon[%02zu]: %p -> %s\n",&mon2[i],i,mon2[i],mon2[i]);

  return 0;
}
