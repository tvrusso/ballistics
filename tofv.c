/* Given a value of v and a table of s and t's with unit increment in v,
   return value of t for that v by linear interpolation.
*/
#include "dragfun.h"

double tofv(double v,sandtstruct dragfun)
{
  int vi;
  sttab_entry *sttab;
  int tabmin,tabmax;
  int nent;
  double slow,shigh,vlow,vhigh,s,m;

  sttab=dragfun.sttab;
  nent=dragfun.nent;
  tabmin=dragfun.minvel;
  tabmax=dragfun.maxvel;
  vi=(int)v;
  if (vi==v)
    s=sttab[tabmax-vi].t;
  else
    {
      vi=tabmax-vi;
      vlow=sttab[vi].v;
      vhigh=sttab[vi-1].v;
      slow=sttab[vi-1].t;
      shigh=sttab[vi].t;
      m=(slow-shigh)/(vhigh-vlow);
      s=shigh+m*(v-vlow);
    }
  return s;
}
