/* Primitive hacks to calculate ratio of atmospheric density to normal.
   From ideal gas equation, r/r0=p/p0 t0/t
   From simple theory of atmosphere, when temperature constant over range
   of heights z0 to z, p/p0=exp[-(z-z0)g/RT], where T is temperature over range
   and R is the gas constant for air, 287 J/degK/kg.  The constant
   RT/g is called H, the "scale height of the atmosphere".  Unfortunately, for
   the range of altitudes one usually shoots at, the temperature is NOT 
   uniform, but rather obeys T(z)=T(0)-6.5 (deg/km)z, with z in km.  Sigh.
   But all the hacks I've seen so far assume constant T, and p/p0=exp[-z/H],
   with H=8438 meters.  This assumes a temperature of 15 deg C(=288.15 deg K)

   This hack ignores all effects of moisture, and does not include temperature
   corrections to the altitude, the way that W.C. Davis includes it in his.
   The effect of those corrections should be small anyway.  If you understand
   how those corrections are derived, email to me and I'll include them. 
   Otherwise, they appear to be nearly voodoo to me, so I neglect them.
   */

#include <math.h>
#define R 287
#define G 9.8
#define T0 288.15           /* only for pressure calculation */
#define H  (R*T0/G)
#define ABSZER 273.15
#define C(F)  ((F-32)*5.0/9.0)
#define K(F)  (C(F)+ABSZER)
#define ABSZERR 491.67
#define degR(F)  (F+ABSZERR)
#define FEETPERMETER 3.2808
#define METERSPERFOOT (1.0/FEETPERMETER)

double prat(altitude)
double altitude;
{
  double altinmeters,presrat;
  altinmeters=METERSPERFOOT*altitude;
  presrat=exp(-(altinmeters/H));
  return(presrat);
}

double rhorat(altitude,p,p0,t0,t)
double p,p0;
double altitude,t0,t;
{

  double temprat,prat();
  temprat=K(t)/K(t0);
  
  return ((p/p0)/temprat);
}

double machrat(t,t0)
double t,t0;
{
  return (sqrt(degR(t)/degR(t0)));
}

