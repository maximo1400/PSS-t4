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
int fin=0, count=0, otherCount=0;
double ret=0;
void* serv(void* ptr){
    int s= (intptr_t)ptr;
    double step =(double)1.0/SIZE;
    pthread_mutex_lock(&m);

    while(!fin){
        double aux=0;
        double xi=count*step;
        double xf=(count+1)*step;
        if (xf==1)
            fin=1;
        printf("env [%f, %f]\n",xi,xf);
        count++;
        pthread_mutex_unlock(&m);
        write(s,(char*)&xi, sizeof(xi));
        write(s,(char*)&xf, sizeof(xf));
        leer(s,(char*)&aux, sizeof(aux));
        pthread_mutex_lock(&m);
        otherCount++;
        ret+=(double)aux;
        if(otherCount==SIZE){
            fin=1;
            printf("integral= %f\n",ret);
        }

    }
    pthread_mutex_unlock(&m);
    close(s);

    return NULL;
}

int main(int argc, char **argv) {
    long s, s2;
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