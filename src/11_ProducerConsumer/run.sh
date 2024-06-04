#!/bin/bash

gcc -c shm_buffer.c producer_consumer.c

gcc -o producer_consumer shm_buffer.o producer_consumer.o
