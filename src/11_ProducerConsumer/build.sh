#!/bin/bash

gcc -c shm_buffer.c 

gcc -o producer_consumer shm_buffer.o producer_consumer.c
gcc -o producer          shm_buffer.o producer.c
gcc -o consumer          shm_buffer.o consumer.c

rm -f /dev/shm/SHM_BUFFER

ls -al /dev/shm

