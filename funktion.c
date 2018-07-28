#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"funktion.h"
#include"struct.h"
#define DL_LINII 1024


void negatyw(dane_obrazu *ob) /*funkcja robi negatyw*/
{
  int i,j; for (i=0; i<ob->wymy; i++){
    for(j=0; j<ob->wymx; j++){ob->tab[i][j]=ob->odcieni-ob->tab[i][j];
    }
  }
}
void rozmywaniepon(dane_obrazu *ob)
{                                                                             /*funkcja rozmywa pionowo(rozmycie o promieniu 4)*/
  int i,j;
  int x;
  x=4;
  for(i=0; i<ob->wymy; i++)
    {
      for(j=x; j<ob->wymx; j++)
	{
	  ob->tab[i][j]=0.33*(ob->tab[i-x][j]+ob->tab[i][j]+ob->tab[i+x][j]);
	}
    }
}
				
void progowanie(dane_obrazu *ob, int prog){
                                              /*funkcja zamienia piksele ponizej wartosci progu na czarne a piksele powyzej na biale*/
  int i,j;
  for (i=0;i<ob->wymy;i++) {
    for (j=0;j<ob->wymx;j++) {
      if (ob->tab[i][j]<=prog)
   ob->tab[i][j]=0;
      else if (ob->tab[i][j]>prog)
   ob->tab[i][j]=ob->odcieni;
    }
  }
}
void konturowanie(dane_obrazu *ob){ /* funkcja pozostawia same kontury */
 int i,j,x,y;

  for (j=0;j<ob->wymy;j++) {
    for (i=0;i<ob->wymx;i++) {

      if (i+1 <= ob->wymx){                                  /* wyciaganie wartosci bezwzglednej z sasiednich pikseli*/ 
	if (ob->tab[i+1][j]-ob->tab[i][j] >0)
     x=ob->tab[i+1][j]-ob->tab[i][j];
   else x=ob->tab[i][j]-ob->tab[i+1][j];
      }
      else x=ob->tab[i][j];
    
      if (j+1 <= ob->wymy){
   if (ob->tab[i][j+1]-ob->tab[i][j] >0)
     y=ob->tab[i][j+1]-ob->tab[i][j];
   else y=ob->tab[i][j]-ob->tab[i][j+1];
      }
      else y=ob->tab[i][j];
      
      if (x+y<=ob->odcieni)     
   ob->tab[i][j]=x+y;
      else;
    }
  }
}

