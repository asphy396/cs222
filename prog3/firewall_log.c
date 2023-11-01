#include "firewall_log.h"

#include <arpa/inet.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>

const char *event_category_list[] = {"unclassified", "phish", "adware",
                                  "command_and_control", "spyware"};
const char *event_outcome_list[] = {"blocked", "allowed"};
const char *event_type_list[] = {"firewall"};
const char *event_action_list[] = {"threat_filter"};

char* find_value(const char* key, const char* line){

  int key_len = 0;
  while(key[key_len++] != '\0');
  key_len -= 1; // dont want nullbyte in length for comparison

  const char* idx = line;
  
  while(strncmp(idx++,key,key_len) != 0) // seek idx up to where key starts in line
    if((idx+key_len-line)>=512) abort(); // exit program if end of line is reached without matching
  
  idx+= key_len; // add key_len to idx to move up to where value starts
  
  while(*(idx++) != '"'); // move idx up to start of value field

  int value_len = 0; // value_len
  while(*(idx+value_len++) != '"'); // seek value_len to end of value field (the ")
  value_len -= 1; // subtract the " 

  char* output = malloc(value_len);
  strncpy(output,idx,value_len);

  return output;
}

struct tm parse_time(char* time_str){

  struct tm tm;
  strptime(time_str, "%m:%d:%Y %H:%M:%S",&tm);

  free(time_str);
  return tm;

}

struct in_addr parse_ip(char* ip_str){

  struct in_addr output;
  inet_pton(AF_INET,ip_str,&output);
  
  free(ip_str);
  return output;
}

int parse_enum(char* str,const char** list){
  int output = 0;

  while(strcmp(str,list[output]) != 0)
    output++;

  return output;
}

firewall_log_t parse_log_line(char *line) {

  firewall_log_t log;

  log.start_time = parse_time(find_value("event.start",line));

  log.dest_ip = parse_ip(find_value("destination.ip",line));
  log.src_ip = parse_ip(find_value("source.ip",line));
  
  strncpy(log.dest_host,find_value("destination.host",line),HOSTNAME_MAX);
  strncpy(log.src_host,find_value("source.host",line),HOSTNAME_MAX);
  
  log.client_bytes = strtoul(find_value("client.bytes",line),NULL,10);
  log.server_bytes = strtoul(find_value("server.bytes",line),NULL,10);
  
  log.http_request_time = strtoul(find_value("http.request.time",line),NULL,10);
  log.http_response_time = strtoul(find_value("http.response.time",line),NULL,10);
  log.username = strtoul(find_value("user.name",line)+1,NULL,10);
  log.event_outcome = parse_enum(find_value("event.outcome",line),event_outcome_list);
  log.event_type = parse_enum(find_value("event.type",line),event_type_list);
  log.event_category = parse_enum(find_value("event.category",line),event_category_list);
  log.event_action = parse_enum(find_value("event.action",line),event_action_list);

  return log;
}

int print_log(firewall_log_t log) {

  char start_time_s[100];
  strftime(start_time_s, 100, "%m:%d:%Y %H:%M:%S", &log.start_time);

  char dest_ip_s[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &log.dest_ip, dest_ip_s, INET_ADDRSTRLEN);

  char src_ip_s[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &log.src_ip, src_ip_s, INET_ADDRSTRLEN);

  const char *formatstr = "event.start = %s\n"
                          "destination.ip = %s, destination.host = %s\n"
                          "source.ip = %s, source.host = %s\n"
                          "client.bytes = %u, server.bytes = %u, "
                          "http.request.time = %u, http.response.time = %u\n"
                          "user.name = u%u\n"
                          "event.outcome = %s, event.type = %s, event.category "
                          "= %s, event.action = %s\n";

  printf(formatstr, start_time_s, dest_ip_s, log.dest_host, src_ip_s,
         log.src_host, log.client_bytes, log.server_bytes,
         log.http_request_time, log.http_response_time, log.username,
         event_outcome_list[log.event_outcome], event_type_list[log.event_type],
         event_category_list[log.event_category],
         event_action_list[log.event_action]);

  return 0;
}
