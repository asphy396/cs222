#ifndef FIREWALL_H
#define FIREWALL_H

#define HOSTNAME_MAX 063

#include <sys/types.h>
#include <arpa/inet.h>
#include <time.h>

extern const char* event_category_l[];
enum event_category {
  unclassified,
  phish,
  adware,
  command_and_control,
  spyware,
};

extern const char* event_outcome_l[];
enum event_outcome {
  blocked,
  allowed,
};

extern const char* event_type_l[];
enum event_type {
  firewall,
  // no other types present, this is just for completeness
};

extern const char* event_action_l[];
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

firewall_log_t parse_log_line(char* s);
int print_log(firewall_log_t log);

#endif
