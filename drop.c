/* DROP.C                                                                 */
/* Thomas Russo                                                           */
/* 9 Jan 1994                                                             */
/* Function to calculate the drop at final velocity v, time t             */
/* return drop in inches                                                  */
/* The function phi is the one given by McShane, Kelly and Reno as "Phi2" */
/* and is strictly approprate only for a constant K_d model, although it  */
/* turns out that it has wider applicablilty than that.  The W.C. Davis   */
/* code TRAG1Q uses a quadratic fit to this function, which actually fits */
/* quite well.  But the function is so simple, why bother?                */
#include <math.h>
double drop(double v, double v0, double t)
{

  double phi,rat,d;

  rat=v0/v;
  if (rat == 1.0)
    d=0.0;
  else
    {
      phi=.5+1.0/(rat-1.0)-1.0/((rat-1.0)*(rat-1.0))*log(rat);
      d=12.0*16*phi*t*t;
    }
  return (d);

}
