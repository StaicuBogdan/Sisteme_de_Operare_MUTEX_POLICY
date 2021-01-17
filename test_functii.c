///testarea functiilor create

///cc mtx-test2.c test_functii.c -o test_functii -lzmq


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <zmq.h>

#include "mtx_policy.h"

int main()
{
    pid_t pid = getpid();
    int id = mtx_open(pid);
    if (id == -1)
    {
        printf("%s", "Mutex-ul nu poate fi creat!\n");
    }
    else
    {
        mtx_lock(id, pid);
        sleep(20);
        mtx_unlock(id, pid);
        sleep(20);
        mtx_close(id, pid);
        sleep(20);
    }

    return 0;
}
