/* Given zero-in range, ballistic coefficient, muzzle velocity, 
   and sight height,calculate trajectory for ranges in array ranges[].
   also returns remaining velocity and time of flight to that range.
 */
#include <stdio.h>
#include "dragfun.h"

void traject(sandtstruct dragfun, double zero_range, double c,
             double v0, double sight_height,
             double *ranges, double *y, double *v, double *t, int nr, double a)
{
  double drop();
  int vatr(),errno,i;
  double vrem,t_o_f,d,slope;
  char *decode_vatr_err();

  /* first calculate drop for level barrel at zero-in range*/
  if ((errno=vatr(c,zero_range,v0/a,&vrem,&t_o_f,dragfun)))
    {
      fprintf(stderr,"Error: %s \n",decode_vatr_err(errno));
      exit(1);
    }
  t_o_f/=a;
  d=drop(vrem*a,v0,t_o_f);
  /* determine slope of line from which to subtract drop:
     bullet strike is at y=0, muzzle is at y=-h.  Drop
     will be from line between muzzle(y=-h) and y=d-h
     y=-h+(d/R)*x.  Bullet trajectory is Y(x)=y(x)-drop(x) */

  slope=(d+sight_height)/zero_range;
  for (i=0;i<nr;i++)
    {
      if (ranges[i] ==0.0) 
	{
	  d=0.0;
	  v[i]=v0;
	  t[i]=0.0;
	}
      else
	{
	  if (errno=vatr(c,ranges[i],v0/a,&(v[i]),&(t[i]),dragfun))
	    {
	      fprintf(stderr,"Error: %s \n",decode_vatr_err(errno));
	      exit(1);
	    }
	  t[i]/=a;
	  v[i]*=a;
	  d=drop(v[i],v0,t[i]);
	}
      y[i]=slope*ranges[i]-sight_height-d;
    }

}
