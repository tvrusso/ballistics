/* Given a value of v and a table of s and t's with unit increment in v from
   tabmax to tabmin,
   return value of s for that v by linear interpolation.
*/
#include "dragfun.h"

double sofv(double v,sandtstruct dragfun)
{
  int vi,nent,tabmin,tabmax;
  double slow,shigh,vlow,vhigh,s,m;
  sttab_entry *sttab;
  sttab=dragfun.sttab;
  tabmin=dragfun.minvel;
  tabmax=dragfun.maxvel;
  nent=dragfun.nent;
  vi=(int)v;
  if (vi==v)
    s=sttab[tabmax-vi].s;
  else
    {
      vi=tabmax-vi;
      vlow=sttab[vi].v;
      vhigh=sttab[vi-1].v;
      slow=sttab[vi-1].s;
      shigh=sttab[vi].s;
      m=(slow-shigh)/(vhigh-vlow);
      s=shigh+m*(v-vlow);
    }
  return s;
}
