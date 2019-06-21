#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "jsocket.h"
#include "util.h"
#include "integral.h"

int main(int argc, char **argv) {
    signal(SIGPIPE,SIG_DFL);
    int s = j_socket();
    if(j_connect(s,"localhost",3000)<0){
        perror("localhost:3000");
        exit(1);
    }
    for (;;) {
        double xi,  xf, ret;
        if (leer(s,(char*)&xi, sizeof(xi)))
            break;
        if (leer(s,(char*)&xf, sizeof(xf)))
            error("fallo la conexion");
        printf("rec [%f, %f]\n",xi,xf);
        ret=integral_f(xi,xf);
        write(s,&ret, sizeof(ret));
    }
    close(s);
    return 0;


}
