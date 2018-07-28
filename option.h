/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,konturowanie,rozmywaniepon,wyswietlenie;      /* opcje */
  int w_progu;              /* wartosc progu dla opcji progowanie */ 
} w_opcje;

void wyzeruj_opcje(w_opcje * wybor);
int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor);
