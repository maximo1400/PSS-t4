#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include "integral.h"

// Calcula integral sin(x+y) dx dy numericamente con x en [0,1] e y en [0,0.5]

// ----------------------------------------------------
// Funcion que entrega el tiempo transcurrido desde el lanzamiento del
// programa en milisegundos

static int time0= 0;

static int getTime0() {
    struct timeval Timeval;
    gettimeofday(&Timeval, NULL);
    return Timeval.tv_sec*1000+Timeval.tv_usec/1000;
}

void resetTime() {
  time0= getTime0();
}

int getTime() {
  return getTime0()-time0;
}

int main() {
  double xi= 0.0, xf= 1.0;
  double yi= 0.0, yf= 0.5;
  double algebraico= - ( sin(xf+yf) - sin(xf+yi) ) +
                       ( sin(xi+yf) - sin(xi+yi) );

  // Calculo secuencial
  {
    printf("Calculo secuencial\n");
    resetTime();
    double numerico= integral_g_dx_dy(xi, xf, 1250*8, yi, yf, 20000);

    printf("Numerico= %f, Algebraico= %f, error= %e, Tiempo=%d milisegs.\n",
          numerico, algebraico, numerico-algebraico, getTime());
    if (fabs(numerico-algebraico)>0.00001) {
      fprintf(stderr,"El error es demasiado grande.  Revise su solucion\n");
      exit(1);
    }
  }

  {
    printf("Calculo paralelo con 8 procesos\n");
    resetTime();
    double numerico= integral_g_dx_dy_par(xi, xf, 1250, yi, yf, 20000, 8);

    printf("Numerico= %f, Algebraico= %f, error= %e, Tiempo=%d milisegs.\n",
          numerico, algebraico, numerico-algebraico, getTime());
    if (fabs(numerico-algebraico)>0.00001) {
      fprintf(stderr,"El error es demasiado grande.  Revise su solucion\n");
      exit(1);
    }
  }
  printf("Felicitaciones: su solucion de la parte b paso el test\n");
  return 0;
}

