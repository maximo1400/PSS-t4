#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "jsocket.h"
#include "util.h"

#define SIZE 1000
pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
typedef void*(*Thread_fun) (void*);

void* serv(void* ptr){
    int s= (intptr_t)ptr;
    double ret=0;
    double step = 0.001;
    int finished=0;
    pthread_mutex_lock(&m);
    for (int i = 0; i < SIZE; i++) {
        double aux=0;
        double xi=i*step;
        double xf=(i+1)*step;
        printf("env [%f, %f]\n",xi,xf);
        pthread_mutex_unlock(&m);
        write(s,(char*)&xi, sizeof(xi));
        write(s,(char*)&xf, sizeof(xf));
        leer(s,(char*)&aux, sizeof(aux));
        finished++;
        ret+=(double)aux;
        pthread_mutex_lock(&m);

    }
    pthread_mutex_unlock(&m);
    close(s);
    if (finished==1000)
        printf("integral= %f\n",ret);
    return NULL;
}

int main(int argc, char **argv) {
    intptr_t s, s2;
    pthread_t pid;

    signal(SIGPIPE, SIG_IGN);
    s = j_socket();

    if (j_bind(s, 3000) < 0)
        error("bind fallo.  Port 3000 ocupado?");


    for(;;) {
        pthread_attr_t attr;
        s2= j_accept(s);
        pthread_attr_init(&attr);
        if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
            fprintf(stderr, "No se puede establecer el atributo\n");
        }
        if ( pthread_create(&pid, &attr, (Thread_fun)serv, (void *)s2) != 0) {
            fprintf(stderr, "No pude crear thread para nuevo cliente %ld!!!\n", s2);
            close(s2);
        }
        pthread_attr_destroy(&attr);
    }

}