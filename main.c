#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"funktion.h"
#include"onPicture.h"
#include"struct.h"
#include"option.h"







/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] szarosci liczba odcieni szarosci					    *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/



int main(int argc, char ** argv) 
{
  
  dane_obrazu ob;
  
  int odczytano = 0;
  int zapisano=0;
  FILE *plik;
  char nazwa[100];
  char nazwazapis[100];
  int prog;
  char wyb[100];
  char chwilowy[]="tmp.pgm";
  
  w_opcje opcje;
  if(argc>1){
	printf("%d\n", przetwarzaj_opcje(argc,argv,&opcje));
	if(opcje.plik_we != NULL){czytaj(opcje.plik_we, &ob);}
 if(opcje.progowanie == 1){
   progowanie(&ob, opcje.w_progu);}
 if(opcje.negatyw == 1){
   negatyw(&ob);}
 if(opcje.rozmywaniepon == 1){rozmywaniepon(&ob);}
 if(opcje.konturowanie == 1){konturowanie(&ob);}
 if(opcje.wyswietlenie == 1){ plik=fopen(chwilowy,"w");
	    zapisz(plik,&ob);
	    fclose(plik);	    
	    wyswietl(chwilowy);}
 if(opcje.plik_wy!=NULL)zapisz(opcje.plik_wy, &ob);
 return 0;}

 
	if(argc==1){
  printf("\tprogram do wczytwania/zapisywania/formatowania\n\t\t obrazow pgm i (ppm jezeli dam rade przed 12 ) o wyiarach jakie chcesz");
  
  while(wyb[0]==wyb[0])                                                                 /*MENU*/
      {
	if(wyb[0]=='E'){printf("koniec\n"); break;}                                             /*przerwanie menu*/
 	printf("\nMENU\n1-WCZYTAJ OBRAZ\n2-ZAPISZ OBRAZ\n3-WYSWIETL\n4-NEGATYW\n5-KONTUROWANIE\n");
	printf("6-ROZMYWANIE PIONOWE\n7-PROGOWANIE\nE-KONIEC\nWYBIERZ:  ");
	scanf("%s", wyb);          /*zczytanie wyboru*/
    
      if(wyb[0]!='E')
	{

	  switch(wyb[0])  /*wybor na podstawie pierwszego znaku*/                            
	  {
	case '1' :/* Wczytanie zawartosci wskazanego pliku do pamieci */
	  printf("Podaj nazwe pliku:\n");
	  scanf("%s",nazwa);
	  plik=fopen(nazwa,"r");

	  if (plik != NULL) 
	    {    /* co spowoduje zakomentowanie tego warunku */
	    odczytano = czytaj(plik,&ob);
	    fclose(plik);
	  printf("\t\tWCZYTANO\n");
	    }
	  else printf("pusty plik\n");
	  
	  break;
	  case '2' : 
	    printf("podaj pod jaka nazwa chcesz zapisac\n");
					   scanf("%s",nazwazapis);
					   plik=fopen(nazwazapis,"w");
					   zapisano= zapisz(plik,&ob);           /*zapisanie obrazka*/
					   fclose(plik);
					   printf("\t\tZAPISANO\n");
	  
	    
	  break;
	  case '3' : /* Wyswietlenie poprawnie wczytanego obraza zewnetrznym programem */
	    plik=fopen(chwilowy,"w");
	    zapisz(plik,&ob);
	    fclose(plik);	    
	    wyswietl(chwilowy);
	    if(odczytano==0) printf("\t\tNIE WCZYTANO OBRAZKA");
	    break;
	  default : printf("\t\tWYBARANO NIE PRAWIDLOWOM OPCJE");     /*gdy uzytkownik wpisze inna opcje*/ 
	    break;
	  case '4' :if(odczytano!=0){negatyw(&ob);
	      printf("\t\tZNEGATYWOWANO\n"); }
	    else printf("\t\tNIE WCZYTANO OBRAZKA");                                      /*zrobienie negatywu*/
	    break;
	  case '6' :if(odczytano!=0){rozmywaniepon(&ob);
	      printf("\t\tROZMYTO\n");}                                                  /*rozmycie obrazka*/
	     else printf("\t\tNIE WCZYTANO OBRAZKA");
	    break;
	  case '7' :if(odczytano !=0)
	      {
		printf("podaj wartosc progu");
		scanf("%d",&prog);
		if(prog>0 && prog<512){
		  progowanie(&ob,prog);                                 /*zprogowanie*/
		printf("\t\tZPROGOWANO\n");
		}
		if(prog<=0 || prog>=512)printf("ZLA WARTOSC");
	      }
	    else printf("\t\tNIE WCZYTANO OBRAZKA");
	    break;
	  case '5' : if(odczytano!=0){konturowanie(&ob);printf("\t\tZKONTUROWANO\n"); }   /*konturownie*/
	    else printf("\t\tNIE WCZYTANO OBRAZKA");
	    break;
	  }
	}
      }	/*koniec menu*/
    
	}
      remove("tmp.ppm");   
  remove("tmp.pgm");
  return odczytano*zapisano;   /*zwrocenie wartosci odczytania*/
      
	
}
