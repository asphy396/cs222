#include "firewall_log.h"

#include <stdio.h>

#define LINE_LEN 512

int main(int argc, char* argv[]){
/*
  FILE* file = fopen("firewall.log","r");

  firewall_log_t logs[100];
  
  {
    int idx = 0;
    char line[LINE_LEN];

    while(idx < 100 && !feof(file)){
      logs[idx++] = parse_log_line(fgets(line,LINE_LEN,file));
    }
  }

  for(int i = 0; i < 100; i++)
    print_log(logs[i]);
*/
  firewall_log_t a;
  time_t now = time(0);
  
  a.start_time = *localtime(&now);
  
  inet_pton(AF_INET,"192.168.0.0",&a.dest_ip);
  inet_pton(AF_INET,"192.168.0.1",&a.src_ip);
  
  a.src_host[0] = 'a';
  a.src_host[1] = '\0';
  a.dest_host[0] = 'b';
  a.dest_host[1] = '\0';

  a.client_bytes = 10;
  a.server_bytes = 20;
  a.http_request_time = 30;
  a.http_response_time = 40;
  a.username = 23134;
  
  a.event_outcome = 0;
  a.event_type = 0;
  a.event_category = 0;
  a.event_action = 0;

  print_log(a);
  return 0;

}


