#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include "integral.h"
#include "util.h"

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
  double step=(xf-xi)/p;
  pid_t pid[p];
  int infds[p];
  for (int i=0; i<p; i++){
      int fds[2];
      pipe(fds);
      pid[i]=fork();
      if (pid[i]==0){
          close(fds[0]);
          double area=integral(f,ptr,i*step,(i+1)*step,n);
          write(fds[1],&area, sizeof(area));
          exit(0);
      }else{
          close(fds[1]);
          infds[i]=fds[0];
      }
  }
  double res=0;
    for (int j = 0; j < p; j++) {
        double area=0;
        leer(infds[j],(char*)&area, sizeof(area));
        res+=area;
        waitpid(pid[j],NULL,0);
    }
    return res;
}

