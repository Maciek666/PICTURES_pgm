#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"onPicture.h"
#define DL_LINII 1024




int** dwad(int y, int x)
{
	int f;
	int** wsk = NULL;



	wsk = malloc(sizeof(int*)*y);
	

	for (f = 0; f < y; f++){	
		wsk[f] = malloc(sizeof(int)*x);
        
	
	}	return wsk;
}	






 int czytaj(FILE *plik_we, dane_obrazu *ob)
  {
    char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
    int znak;                /* zmienna pomocnicza do czytania komentarzy */
    int koniec=0;            /* czy napotkano koniec danych w pliku */
    int i,j;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;
                                /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {printf("%d %d",buf[0],buf[1]);  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM ani PPM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",&(ob->wymx),&(ob->wymy),&(ob->odcieni))!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  
  ob->tab=dwad(ob->wymy,ob->wymx);
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<ob->wymy;i++) {
    for (j=0;j<ob->wymx;j++) {

      if (fscanf(plik_we,"%d",&(ob->tab[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return (ob->wymx)*(ob->wymy);
  }

 


/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
  void wyswietl(char *n_pliku){
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

int zapisz(FILE *plik_wyj,dane_obrazu *ob){      /*funkcja zapisuje obraz */ 
  int i,j;
  if(plik_wyj!=NULL){
    
  fprintf(plik_wyj,"P2\n %d %d %d\n", ob->wymx, ob->wymy, ob->odcieni);
    for(i=0; i<ob->wymy; i++)
      {
      for(j=0; j<ob->wymx; j++)
	{
	  fprintf(plik_wyj,"%d  ",ob->tab[i][j]);
	}
      fprintf(plik_wyj,"\n");
      }
  }

  return ob->wymx*(ob->wymy);
}
