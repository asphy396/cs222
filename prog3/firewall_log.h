#ifndef FIREWALL_H
#define FIREWALL_H

#define HOSTNAME_MAX 063

#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern const char* event_category_list[];
enum event_category {
  unclassified,
  phish,
  adware,
  command_and_control,
  spyware,
};

extern const char* event_outcome_list[];
enum event_outcome {
  blocked,
  allowed,
};

extern const char* event_type_list[];
enum event_type {
  firewall,
  // no other types present, this is just for completeness
};

extern const char* event_action_list[];
enum event_action{
  threat_filter,
  // no other actions present, this is just for completeness
};

typedef struct firewall_log_t {

  struct tm start_time;

  struct in_addr dest_ip;
  struct in_addr src_ip;

  char src_host[HOSTNAME_MAX];
  char dest_host[HOSTNAME_MAX];

  unsigned int client_bytes;
  unsigned int server_bytes;
  unsigned int http_request_time;
  unsigned int http_response_time;
  unsigned int username;

  enum event_outcome event_outcome;
  enum event_type event_type;
  enum event_category event_category;
  enum event_action event_action;

} firewall_log_t;

firewall_log_t parse_log_line(char* s); // main function to parse lines, returns a log struct
int print_log(firewall_log_t log);
char* find_value(const char* key, const char* line); // finds the corresponding value field of a key in a line
struct tm parse_time(char* time_str); // converts time string to tm struct 
struct in_addr parse_ip(char* ip_str); // converts ip address string to inet_addr struct
int parse_enum(char* str, const char** list); // converts event_xyz string to the correct enum value

#endif
