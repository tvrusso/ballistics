/*  simple.c
    An extraordinarily simplistic (if not "simple") program to compute
    bullet trajectories from Siacci tables for drag functions */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "dragfun.h"
#include "g1.h"
#include "g7.h"
/* conversion factors */
#define FeetPerMile 5280
#define InchesPerFoot 12
#define SecondsPerHour 3600
#define FeetPerYard 3.0
/* return inches per second given miles per hour */
#define InPSperMPH(x) ((x)*FeetPerMile/SecondsPerHour*InchesPerFoot)
#define MAXTITLE 128

#include "ballistics_prototypes.h"
#include "atmos.h"

int main(int argc,char **argv)
{

  double muzvel,balcoef,range,sight_height;
  double C1,altitude,temp,a,rho,pressure;
  int number_of_intervals,i;
  double interval_length,x,zero_range;
  double *ranges,*vels,*times,*ys;
  double atof();
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
	case '7':
	  thedfun=&g7;
	  fprintf(stderr," I hope that you put any temperature and pressure specifications AFTER the g7, coz otherwise they'll get overwritten!\n");
	  pressure=g7.stdpress;
	  temp=g7.stdtmp;
	  break;
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
  range=range*FeetPerYard;
  zero_range=zero_range*FeetPerYard;
  interval_length = range/number_of_intervals;

  printf("%s\n",title);
  printf("Drag function: %s\n",thedfun->tabnam);
  printf("Muzzle velocity=%5.1f f.p.s.\n",muzvel);
  printf("ballistic coefficient at STP=%4.3f, corrected to=%4.3f \n",C1,balcoef);
  printf("range=%5.1f yds., rifle zeroed at %5.1f yds\n",range/3.0,zero_range/3.0);
  printf("altitude: %4.2f     Temperature: %4.2f    pressure: %4.2f\n",altitude,temp,pressure);
  printf("Wind velocity %f MPH (%f InPS)\n",windvel,InPSperMPH(windvel));
  printf("\n");

  ranges[0]=0.0;
  for (i=1;i<=number_of_intervals;i++)
    {
      x=interval_length*i;
      ranges[i]=x;
    }
  traject(*thedfun,zero_range,balcoef,muzvel,sight_height,ranges,ys,vels,times,number_of_intervals+1,a);
  printf(
"Range          Vel           Y(R) (moa)             T(R)         defl(R)\n");
  for (i=0;i<number_of_intervals+1;i++)
    {
      printf(
"%4d            %5.1f       %5.1f (%5.1f)            %4.3f        %5.1f\n",(int)(ranges[i]/3),vels[i],ys[i],ranges[i]==0?0:ys[i]/(ranges[i]/300),times[i],InPSperMPH(windvel)*(times[i]-ranges[i]/muzvel));
    }

  exit(0);
}
