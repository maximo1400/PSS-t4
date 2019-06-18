
typedef double (*Funcion)(void *ptr, double x);

// La funcion pedida en la parte a
double integral(Funcion f, void *ptr, double xi, double xf, int n);

// La funcion pedida en la parte b
double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p);


// Definidas en fun.c
double integral_g_dx_dy(double xi, double xf, int n,
                        double yi, double yf, int m);
double integral_g_dx_dy_par(double xi, double xf, int n,
                        double yi, double yf, int m, int p);
double integral_f(double xi, double xf);
