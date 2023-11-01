CC = gcc 
CFLAGS = -Wall -Werror

program3: main.c firewall_log.o
	$(CC) $(CFLAGS) main.c -o program3 firewall_log.o

firewall_log.o: firewall_log.c firewall_log.h 
	$(CC) $(CFLAGS) -c firewall_log.c -D_GNU_SOURCE

clean_run: clean program3
	./program3

clean:
	rm -rf program3 firewall_log.o
