/* given ballistic coefficient and initial velocity determine
   remaining velocity and time of flight
   Adjustments for nonstandard atmospheric conditions must be done to C and V
   by the caller
 */
#include <stdio.h>
#include "dragfun.h"
int vatr(c,x,v0,vf,t,dragfun)
double c,x,v0,*vf,*t;
sandtstruct dragfun;
{
  double tofv(),vofs(),sofv();
  double srem,vrem,t0,tf;
  int retval;
  retval=0;
  if (v0>dragfun.maxvel || v0<dragfun.minvel)
    retval=-1;
  else
    {
      srem=sofv(v0,dragfun)+x/c;
      if (srem >dragfun.sttab[dragfun.nent-1].s ||
	  srem >dragfun.sttab[dragfun.nent-1].s )
	retval=-2;
      else
	{
	  vrem=vofs(srem,dragfun);
	  *vf=vrem;
	  t0=tofv(v0,dragfun);
	  if (vrem < dragfun.sttab[dragfun.nent-1].v )
	    retval=-3;
	  else
	    {
	      tf=tofv(vrem,dragfun);
	      *t=c*(tf-t0);
	    }
	}
    }
  return(retval);
}
  
char *decode_vatr_err(i)
int i;
{
  char *a;
  a="unknown error";
  switch(i)
    {
    case -1:
      a="initial velocity out of range";
      break;
    case -2:
      a="S out of range";
      break;
    case -3:
      a="final velocity out of range";
      break;
    }
  return (a);
}
