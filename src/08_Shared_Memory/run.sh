#!/bin/bash

SET="shmwrite"
GET="shmread"
CFLAGS="-lrt"


gcc ${CFLAGS} -o ${SET} ${SET}.c
gcc ${CFLAGS} -o ${GET} ${GET}.c

./${SET} 
./${GET}

ls -l /dev/shm

sleep 1

rm ${SET} ${GET}
