#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <zmq.h>
#include "mtx_policy.h"

int mtx_open(pid_t pid)
{
    //conectarea la server
    void *context = zmq_ctx_new();//crearea unui nou context 0MQ
    void *requester = zmq_socket (context, ZMQ_REQ);//crearea unui socket 0MQ
    zmq_connect (requester, "tcp://localhost:5555");//conectarea la un socket

    char buf_pid[24];//cream buffer-ul pentru a fi trimis la daemon
    sprintf(buf_pid, "%d", pid);/*sprintf inseamna „String print”. In loc sa tipareasca pe consola, stocheaza iesirea
    pe buffer-ul de caractere specificat in sprintf*/

    char buffer[101];
    strcpy(buffer, "mtx_open");
    strcat(buffer, " ");
    strcat(buffer, buf_pid);//process id

    zmq_send(requester, buffer, 101, ZMQ_DONTWAIT);/*trimite buffer-ul de lungime 101 catre socket-ul 0MQ,
    avand optiunea ca operatiunea sa fie efectuata in modul non-blocare*/

    char buff_received[10];//ceea ce se primeste de la server
    zmq_recv (requester, buff_received, 10, 0);//se primeste un mesaj de la socket si se stocheaza in buff_receiver


    int ok;//0 in caz de reuista si -1 in caz de eroare
    if (strstr(buff_received, "-"))
    {
        ok = -1;
        printf("Open: %d\n", ok);
        printf("Procesul %s nu poate deschide niciun mutex.\n", buf_pid);
    }
    else
    {
        printf("Open: %d\n", ok);
        int mtx = atoi(buff_received);
        printf("Procesul %s a deschis mutex-ul %d.\n", buf_pid, mtx);
        ok = mtx;
    }

    zmq_close (requester);//inchidem socket-ul
    zmq_ctx_destroy (context);//distrugem contextul 0MQ creat

    return ok;
}


int mtx_close(int id, pid_t pid)
{
    void *context = zmq_ctx_new();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    char buf_pid[24],buf_id[24];//buf_pid este pentru id-ul procesului, iar buf_id este id-ul mutex-ului
    sprintf(buf_pid, "%d", pid);
    sprintf(buf_id, "%d", pid);

    char buffer[101];
    strcpy(buffer, "mtx_close");
    strcat(buffer, " ");
    strcat(buffer, buf_id);
    strcat(buffer, " ");
    strcat(buffer, buf_pid);

    zmq_send(requester, buffer, 101, ZMQ_DONTWAIT);

    char buff_received[10];
    zmq_recv (requester, buff_received, 10, 0);

    int ok;//0 in caz de reuista si -1 in caz de eroare
    if (strstr(buff_received, "-"))
    {
        ok = -1;
        printf("Close: %d\n", ok);
        printf("Procesul %s nu poate inchide mutex-ul %s.\n", buf_pid, buf_id);
    }
    else
    {
        printf("Close: %d\n", ok);
        printf("Procesul %s a inchis mutex-ul %s.\n", buf_pid, buf_id);
    }

    zmq_close (requester);
    zmq_ctx_destroy (context);

    return ok;
}


int mtx_lock(int id, pid_t pid)
{
    void *context = zmq_ctx_new();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    char buf_pid[24],buf_id[24];//buf_pid este pentru id-ul procesului, iar buf_id este id-ul mutex-ului
    sprintf(buf_pid, "%d", pid);
    sprintf(buf_id, "%d", pid);

    char buffer[101];
    strcpy(buffer, "mtx_close");
    strcat(buffer, " ");
    strcat(buffer, buf_id);
    strcat(buffer, " ");
    strcat(buffer, buf_pid);

    zmq_send(requester, buffer, 101, ZMQ_DONTWAIT);

    int ok;//0 in caz de reuista si -1 in caz de eroare
    char buff_received[10];
    zmq_recv (requester, buff_received, 10, 0);

    if (strstr(buff_received, "-"))
    {
        ok = -1;
        printf("Lock: %d", ok);
        printf("Procesul %s nu poate bloca mutex-ul %s.\n", buf_pid, buf_id);
        break;
    }
    else if (strstr(received_text, "0"))
    {
        printf("Lock: %d\n", ok);
        printf("Procesul %s a blocat mutex-ul %s.\n", buf_pid, buf_id);
        break;
    }

    zmq_close (requester);
    zmq_ctx_destroy (context);

    return ok;
}


int mtx_unlock(int id, pid_t pid)
{
    void *context = zmq_ctx_new();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    char buf_pid[24],buf_id[24];//buf_pid este pentru id-ul procesului, iar buf_id este id-ul mutex-ului
    sprintf(buf_pid, "%d", pid);
    sprintf(buf_id, "%d", pid);

    char buffer[101];
    strcpy(buffer, "mtx_close");
    strcat(buffer, " ");
    strcat(buffer, buf_id);
    strcat(buffer, " ");
    strcat(buffer, buf_pid);

    zmq_send(requester, buffer, 101, ZMQ_DONTWAIT);

    char buff_received[10];
    zmq_recv (requester, buff_received, 10, 0);

    int ok;//0 in caz de reuista si -1 in caz de eroare
    if (strstr(buff_received, "-"))
    {
        ok = -1;
        printf("Close: %d\n", ok);
        printf("Procesul %s nu poate debloca mutex-ul %s.\n", buf_pid, buf_id);
    }
    else
    {
        printf("Close: %d\n", ok);
        printf("Procesul %s a deblocat mutex-ul %s.\n", buf_pid, buf_id);
    }

    zmq_close (requester);
    zmq_ctx_destroy (context);

    return ok;
}
