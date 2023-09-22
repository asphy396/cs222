#!/bin/sh

set -xe

gcc -Wall -Wextra -o partial program2a_malbayra_nth_partial_sum.c
gcc -Wall -Wextra -o data program2b_malbayra_data_breaches.c -lm
