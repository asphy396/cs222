#include "firewall_log.h"

#include <arpa/inet.h>
#include <stdio.h>

const char *event_category_s[] = {"unclassified", "phish", "adware",
                                  "command_and_control", "spyware"};
const char *event_outcome_s[] = {"blocked", "allowed"};
const char *event_type_s[] = {"firewall"};
const char *event_action_s[] = {"threat_filter"};

firewall_log_t parse_log_line(char *line) {

  const char *formatstr =
      "{\"event.start\": \"%s\",\"destination.ip\": "
      "\"%s\",\"destination.host\": \"%s\",\"source.ip\": "
      "\"%s\",\"source.host\": \"%s\",\"client.bytes\": "
      "\"%d\",\"server.bytes\": \"%d\",\"http.request.time\": "
      "\"%d\",\"http.response.time\": \"%d\",\"user.name\": "
      "\"u%d\",\"event.outcome\": \"%s\",\"event.type\": "
      "\"%s\",\"event.category\": \"%s\",\"event.action\": \"%s\"}";

  firewall_log_t log;

  char time_s[20];
  char dest_ip_s[17];
  char src_ip_s[17];
  char src_host_s[HOSTNAME_MAX];
  char dest_host_s[HOSTNAME_MAX];


  sscanf(line,formatstr,);

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
         event_outcome_s[log.event_outcome], event_type_s[log.event_type],
         event_category_s[log.event_category],
         event_action_s[log.event_action]);

  return 0;
}
