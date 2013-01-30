/* Given a value of s, return value of v corresponding.
   This version uses linear interpolation, but that'll probably need to
   be refined to quadratic interpolation.  We do a binary search to find the
   starting point.
*/
#include "dragfun.h"
double vofs(s,dragfun)
double s;
sandtstruct dragfun;
{
  double stest,vlow,vhigh,m;
  double v;
  int range_min,range_max,testpoint;
  sttab_entry *sttab;
  int nent;

  sttab=dragfun.sttab;
  nent=dragfun.nent;
  range_min=0;range_max=nent-1;

  for (testpoint=(range_max+range_min)/2,stest=sttab[testpoint].s;
       (range_max-range_min)>1;
       testpoint=(range_max+range_min)/2,stest=sttab[testpoint].s)
    {
      if (stest>s)
	range_max=testpoint;
      else if (stest < s)
	range_min=testpoint;
      else if (stest == s)
	break;
    }

  stest=sttab[testpoint].s;
  if (stest==s)
    v=sttab[testpoint].v;
  else
    {
      if (stest>s && sttab[testpoint-1].s < s)
	{
	  vlow=(double)sttab[testpoint].v;
	  vhigh=(double)sttab[testpoint-1].v;
	  m=(sttab[testpoint-1].s-stest)/(vhigh-vlow);
	  v=vlow+(s-stest)/m;
	}
      else
	{
	  if (stest<s && sttab[testpoint+1].s >s)
	    {
	      vlow=(double)sttab[testpoint+1].v;
	      vhigh=(double)sttab[testpoint].v;
	      m=(stest-sttab[testpoint+1].s)/(vhigh-vlow);
	      v=vlow+(s-sttab[testpoint+1].s)/m;
	    }
	  else
	    {
	      printf("Good god, what a mess!\n");
	      v=-1000.0;
	    }
	}
    }
  return(v);
}
