#include <math.h>
#include "integral.h"

/* Calcula integral sin(x+y) dx dy numericamente
 * En este archivo la funcion sin(x+y) es g(x,y)
 *
 * integral_g_dx(y, xi, xf, n) ~=
 *                    integral sin(x+y) dx en [xi,xf]
 *                  = integral sin(x) dx en [xi+y, xf+y]
 *                  = (-cos(xf+y)) - (-cos(xi+y))
 *
 * integral integral_g_dx(y) dy en [yi, yf]=
 *                    integral -cos(xf+y) - (-cos(xi+y)) dy en [yi, yf]
 *                  = - integral cos(xf+y) dy en [yi, yf] +
 *                      integral cos(xi+y) dy en [yi, yf]
 *                  = - integral cos(y) dy en [xf+yi, xf+yf] +
 *                      integral cos(y) dy en [xi+yi, xi+yf]
 *                  = - ( sin(xf+yf) - sin(xf+yi) ) +
 *                      ( sin(xi+yf) - sin(xi+yi) )
 */

typedef struct {
  double yi, yf;
  int m;
} Arg;

double g(double x, double y) {
  return sin(x+y);
}

double g_aux(void *ptr, double y) {
 double x= *(double *)ptr;
 return g(x, y);
}

double integral_f(double xi, double xf) {
  return integral_g_dx_dy(xi, xf, 10, 0.0, 0.5, 20000);
}

double integral_g_dy(void *ptr, double x) {
  Arg *p= ptr;
  return integral(g_aux, &x, p->yi, p->yf, p->m);
}

double integral_g_dx_dy(double xi, double xf, int n,
                        double yi, double yf, int m) {
  Arg a= { yi, yf, m };
  return integral(integral_g_dy, &a, xi, xf, n);
}

double integral_g_dx_dy_par(double xi, double xf, int n,
                        double yi, double yf, int m, int p) {
  Arg a= { yi, yf, m };
  return integral_par(integral_g_dy, &a, xi, xf, n, p);
}

