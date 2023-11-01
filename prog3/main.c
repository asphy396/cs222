/*********************************
 *
 * CS222 Programming Assignment 3
 *
 * Mert Albayrak (malbayra@gmu.edu)
 *
 * main.c
 *
 * Driver program for firewall_log
 * Takes a filepath from the user
 * and, if valid, parses the logs 
 * from the file, printing the 
 * entries afterward
 *
 *********************************/

#include "firewall_log.h"

#include <stdio.h>

#define LINE_LEN 512
#define LOG_NUM 100

int sectionf(firewall_log_t logs[100]){

  int idx = 0;

  while(idx++<100){
    firewall_log_t current = logs[idx];
    if(current.event_outcome == blocked && current.event_category == phish && current.server_bytes>4000) {
      print_log(current);
      return idx;
    }
  }
  
  return -1;
}

int main(int argc, char* argv[]){

  char* path = "firewall.log"; //default path

  if(argc>1) path = argv[1];

  FILE* file = fopen(path,"r");

  if(file == NULL){
    printf("Invalid file!\n");
    exit(1);
  }

  firewall_log_t logs[LOG_NUM];
  
  {
    int idx = 0;
    char line[LINE_LEN];

    while(idx < LOG_NUM && !feof(file)){
      logs[idx++] = parse_log_line(fgets(line,LINE_LEN,file));
    }
  }

  printf("Finished parsing logs...\n");
  
  printf("Printing first log:\n");
  print_log(logs[0]);
  
  //printf("%d",sectionf(logs)); // printed 50, so log 51

  /*
  for(int i = 0; i < LOG_NUM; i++)
    print_log(logs[i]);
  */

  return 0;
}

/* sample run: 
  asphy@framework:~/cs222/prog3$ ./program3 firewall.log
  Finished parsing logs...
  Printing first log:
  event.start = 01:05:2021 05:11:10
  destination.ip = 93.115.29.34, destination.host = test.creditcard.com
  source.ip = 10.189.90.63, source.host = u120823domain.corp.com
  client.bytes = 177, server.bytes = 4919, http.request.time = 14, http.response.time = 113
  user.name = u120823
  event.outcome = blocked, event.type = firewall, event.category = adware, event.action = threat_filter
*/



