#include <stdio.h>
#ifdef __STDC__
#include <stdlib.h>
#include <unistd.h>
#endif
#include <math.h>
#include "dragfun.h"
#include "g1.h"
#ifdef USE_G7
#include "g7.h"
#endif
#define maxord(t) 48*t*t
#define FPM 5280
#define InPF 12
#define SECPERHR 3600
#define FTPERYD 3.0
#define InPSperMPH(x) ((x)*FPM/SECPERHR*InPF)
#define MAXTITLE 128

double vofs();
double sofv();
double tofv();
double drop();
double rhorat();
double machrat();
double prat();

main(argc,argv)
int argc;
char **argv;
{

  double muzvel,balcoef,range,vel_left,
         time_of_flight,d,sight_height,max_ordinate,max_height,elev;
  double C1,altitude,temp,a,rho,pressure;
  int number_of_intervals,errno,i;
  double interval_length,x,zero_range;
  double *ranges,*vels,*times,*ys;
  double atof();
  int v0;
  int ch;
  int specprec;
  double windvel;
  sandtstruct *thedfun;
  char title[MAXTITLE]="Untitled load";

/* set defaults */
  a=1.0;
  altitude=0.0;
  pressure=g1.stdpress;
  temp=g1.stdtmp;
  muzvel=0.0;
  C1=0.0;
  range=0.0;
  number_of_intervals=10;
  sight_height=.5;
  zero_range=0.0;
  windvel=10.0;
  thedfun=&g1;
  specprec=0;
  while ((ch=getopt(argc,argv,"a:p:t:v:c:r:n:h:w:z:7T:"))!=EOF) 
    {
      switch(ch)
	{
	case 'a': 
	  altitude=atof(optarg);
	  break;
	case 'p':
	  pressure=atof(optarg);
	  specprec=1;
	  break;
	case 't':
	  temp=atof(optarg);
	  break;
	case 'v':
	  muzvel=atof(optarg);
	  break;
	case 'c':
	  C1=atof(optarg);
	  break;
	case 'r':
	  range=atof(optarg);
	  break;
	case 'n':
	  number_of_intervals=atoi(optarg);
	  break;
	case 'h':
	  sight_height=atof(optarg);
	  break;
	case 'w':
	  windvel=atof(optarg);
	  break;
	case 'z':
	  zero_range=atof(optarg);
	  break;
#ifdef USE_G7
	case '7':
	  thedfun=&g7;

/*	  fprintf(stderr," I hope that you put any temperature and pressure specifications AFTER the g7, coz otherwise they'll get overwritten!\n"); */
	  pressure=g7.stdpress;
	  temp=g7.stdtmp;
	  break;
#endif
	case 'T':
	  strncpy(title,optarg,MAXTITLE);
	  break;
	default:
	  fprintf(stderr,"%s: unknown switch %c\n",argv[0],ch);
	  fprintf(stderr,"Usage: %s [-a altitude] [-p pressure] [-t temp] -v veloc -c balcoef -r range [-n number_of_intervals] [-h sight_height] [-z zero_range] [-7 (use g7 function)] [-T title] [-w wind velocity]\n",argv[0]);
	  exit(1);
	}
    }
  if (muzvel==0.0) 
    {
      fprintf(stderr,"Must specify muzzle velocity\n");
      exit (1);
    }
  if (C1 == 0.0) 
    {
      fprintf(stderr,"Must specify a ballistic coef at STP\n");
      exit(1);
    }
  if (range == 0.0)
    {
      fprintf(stderr,"Must specify a range for the table\n");
      exit(1);
    }
  if (zero_range == 0.0) 
    zero_range = range;

  if (!specprec && altitude != 0) pressure = thedfun->stdpress*prat(altitude);

/* Allocate core for arrays */
  ranges=(double *)malloc((number_of_intervals+1)*sizeof(double));
  vels=(double *)malloc((number_of_intervals+1)*sizeof(double));
  times=(double *)malloc((number_of_intervals+1)*sizeof(double));
  ys=(double *)malloc((number_of_intervals+1)*sizeof(double));

/* do atmospheric corrections if necessary */
  rho=1.0;
  if (temp != thedfun->stdtmp) a=machrat(temp,thedfun->stdtmp);
  rho=rhorat(altitude,pressure,thedfun->stdpress,thedfun->stdtmp,temp);
  balcoef=C1/rho;

/* Split up range into nice sized intervals for the table */
  range=range*FTPERYD;
  zero_range=zero_range*FTPERYD;
  interval_length = range/number_of_intervals;

  printf("TTL %s\n",title);
  printf("DF %s\n",thedfun->tabnam);
  printf(" MV %5.1f f.p.s.\n",muzvel);
  printf("STPBC %4.3f \n CBC %4.3f \n",C1,balcoef);
  printf("RNG %5.1f \n 0RNG %5.1f \n",range/3.0,zero_range/3.0);
  printf("ALT %4.2f \n    TEMP %4.2f \n  PRESS %4.2f\n",altitude,temp,pressure);
  printf("WIND %f \n",windvel);

  ranges[0]=0.0;
  for (i=1;i<=number_of_intervals;i++)
    {
      x=interval_length*i;
      ranges[i]=x;
    }
  traject(*thedfun,zero_range,balcoef,muzvel,sight_height,ranges,ys,vels,times,number_of_intervals+1,a);
  for (i=0;i<number_of_intervals+1;i++)
    {
      printf(
"BT %4d            %5.1f       % 5.1f            %4.3f        %5.1f\n",(int)(ranges[i]/3),vels[i],ys[i],times[i],InPSperMPH(windvel)*(times[i]-ranges[i]/muzvel));
    }

}
