#ifndef BALLISTICS_PROTOTYPES_H
#define BALLISTICS_PROTOTYPES_H

double vofs(double,sandtstruct);
double sofv(double,sandtstruct);
double tofv(double,sandtstruct);
double drop(double,double,double);
void traject(sandtstruct dragfun, double zero_range, double c,
             double v0, double sight_height,
             double *ranges, double *y, double *v, double *t, int nr, double a);
#endif


