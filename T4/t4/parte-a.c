#include "integral.h"

double integral(Funcion f, void *p, double xi, double xf, int n) {
    double h =(xf-xi)/n;
    double aux1= ((f)(p,xi)+(f)(p,xf))/2;
    double aux2=0;
    for (int k = 1; k < n; k++) {
        aux2+=(f)(p,xi+k*h);
    }
    double ret=h*(aux1+aux2);
    return ret;
}
