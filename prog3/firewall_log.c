#include "firewall_log.h"

#include <arpa/inet.h>
#include <stdio.h>

// _l == "lookup"
const char *event_category_l[] = {"unclassified", "phish", "adware",
                                  "command_and_control", "spyware"};
const char *event_outcome_l[] = {"blocked", "allowed"};
const char *event_type_l[] = {"firewall"};
const char *event_action_l[] = {"threat_filter"};

firewall_log_t parse_log_line(char *line) {

  const char *formatstr =
      "{\"event.start\": \"%19c\",\"destination.ip\": "
      "\"%s\",\"destination.host\": \"%s\",\"source.ip\": "
      "\"%s\",\"source.host\": \"%s\",\"client.bytes\": "
      "\"%d\",\"server.bytes\": \"%d\",\"http.request.time\": "
      "\"%d\",\"http.response.time\": \"%d\",\"user.name\": "
      "\"u%d\",\"event.outcome\": \"%s\",\"event.type\": "
      "\"%s\",\"event.category\": \"%s\",\"event.action\": \"%s\"}";

  firewall_log_t log;

  // intermediary variables required for some fields
  // where not required, pointers are used for consistency's sake
  char time_s[20];
  char dest_ip_s[17];
  char src_ip_s[17];

  char* src_host = log.src_host;
  char* dest_host = log.dest_host;
  
  unsigned int* client_bytes = &log.client_bytes;
  unsigned int* server_bytes = &log.server_bytes;
  unsigned int* http_request_time = &log.http_request_time;
  unsigned int* http_response_time = &log.http_response_time;
  unsigned int* username = &log.username;

  char event_outcome_s[8]; // 'blocked' or 'allowed'
  char event_type_s[9]; // firewall
  char event_category_s[20];
  char event_action_s[14];

  sscanf(line,formatstr,&time_s,&dest_ip_s,&dest_host,src_ip_s,src_host,client_bytes,server_bytes,http_request_time,http_response_time,username,&event_outcome_s,&event_type_s,&event_category_s,&event_action_s);
  printf("%s",line);
  printf("%s|%s|%s\n",time_s,dest_ip_s,src_ip_s);
  printf("%s|%s\n",dest_host,src_host);
  printf("%s %s %s %s\n",event_outcome_s,event_type_s,event_category_s,event_action_s);

  log.username = 5;

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
         event_outcome_l[log.event_outcome], event_type_l[log.event_type],
         event_category_l[log.event_category],
         event_action_l[log.event_action]);

  return 0;
}
