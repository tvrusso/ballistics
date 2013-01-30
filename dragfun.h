/* Header file for drag function structure
   Thomas Russo
   9 Jan 1994
*/
typedef struct
{
  int v;
  double s;
  double t;
} sttab_entry;

typedef struct 
{
  char tabnam[32];         /* Identifies table */
  double stdtmp,stdpress;  /* Table is for this temp and press */
  int nent;                /* Number of velocities tabulated */
  unsigned maxvel,minvel;  /* min and max tabulated velocities */
  sttab_entry *sttab;      /* The table of s and t values, with velocities */
} sandtstruct;


