#include <stdio.h>
#include "dragfun.h"
#include "g1.h"
sttab_entry foo[3]={{4095,0.000,0.000},{4094,2.371120,0.000579},
		      {4093,4.742755,0.001158}};
double vofs();

main()
{
  int i;
  double stofind,vfound;
  printf("%s\n",g1.tabnam);
  printf(" Has %d elements \n",g1.nent);
  printf(" std temp=%f, std press=%f\n",g1.stdtmp,g1.stdpress);
/*  for (i=0;i<g1.nent;i++)
    printf("%d %f %f\n",g1.sttab[i].v,g1.sttab[i].s,g1.sttab[i].t);
*/

  stofind=28.4;
  vfound=vofs(stofind,g1.sttab,g1.nent);
  printf("s(v)=%f corresponds to v=%f\n",stofind,vfound);

/*  for (i=0;i<3;i++)
    printf("%d %f %f\n",foo[i].v,foo[i].s,foo[i].t);
*/
}
