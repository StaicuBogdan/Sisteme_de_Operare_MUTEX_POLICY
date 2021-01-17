#ifndef MUTEX_POLICY
#define MUTEX_POLICY

int mtx_open(pid_t pid);///deschide un mutex
int mtx_close(int id, pid_t pid);///inchide un mutex deschis
int mtx_lock(int id, pid_t pid);/// blocheaza mutex-ul
int mtx_unlock(int id, pid_t pid);///deblocheaza mutex-ul
//int mtx_list(int *d, pid_t *pidlist, size_t nlist);
//int mtx_grant(int d, pid_t pid);///acorda blocarea mutex-ului la firul reprezentat de pid si returneaza 0 la succes si -1 la eroare

#endif
