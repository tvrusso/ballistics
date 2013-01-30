#include <stdio.h>

main()
{
  short int i1,i2;
  unsigned short u1,maxvel,minvel;
  double d1,d2;
  float f1,f2,d3[2];
  float *stab,*ttab;
  char tabnam[32];

  fread (&i1,sizeof(short int),1,stdin);
  printf("truncated revision number=%d\n",-i1);
  fread(&f1,sizeof(float),1,stdin);
  printf("full revision number=%f\n",f1);
  fread(tabnam,sizeof(tabnam),1,stdin);
  printf("Table name: %s\n",tabnam);
  fread(&d1,sizeof(double),1,stdin);
  printf("Std temp: %f  ",d1);
  fread(&d1,sizeof(double),1,stdin);
  printf("std press: %f\n",d1);
  fread(&maxvel,sizeof(unsigned short),1,stdin);
  printf("max vel: %u\n",maxvel);
  fread(&minvel,sizeof(unsigned short),1,stdin);
  printf("min vel: %u\n",minvel);
  stab=calloc(4096,sizeof(float));
  ttab=calloc(4096,sizeof(float));
  d1=0.0;
  fread(stab,sizeof(float),4096,stdin);
  fread(ttab,sizeof(float),4096,stdin);
  fread(&f2,sizeof(float),1,stdin);
  printf("{\n");
  for (i1=maxvel;i1>=minvel;i1--)
    {
      d1=d1+stab[i1]-ttab[i1];
      printf("{%d,%f,%f}",i1,stab[i1],ttab[i1]);
      if (i1>minvel)
	printf(",\n");
      else
	printf("}\n");
      
    }
  printf("checksum=%f(%f)\n",f2,d1);

}
