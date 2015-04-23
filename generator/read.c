#include "read.h"

int slowa(FILE *plik[30], int s){
    int i, lw, c;
    lw = 0;
    int stan;

    for ( i = 0; i < s; i++){
        stan = 0;
        while((c = getc(plik[i])) != EOF){
            if( c == ' '|| c == '\n' || c == '\t')
                stan = 0;
            else if (stan == 0){
                stan = 1;
                ++lw;
            }
        }
        rewind(plik[i]);
    }
    return lw;
}

int read_file (int n,FILE* plik[30],int s, int ile_slow,int wyrazy, int stat){

    int lw,i,j,a;

    lw = ile_slow - n;

    struct gram *wektor = malloc(lw*sizeof(struct gram));

    if(wektor == NULL){
        printf("nie udało się zaalokować pamięci do wektora struktur\n");
        return 1;
    }
    int licznik_struktur = 0;
    char c;

    for(a = 0; a < s; a++){
        for (j = 0; j < n; j++){
            for (i = 0; i < MAXLITER; i++){
                c = getc(plik[a]);
                if(c == ' ' || c == '\n' || c == '\t')
                    break; 
                wektor[licznik_struktur].tabgram[j][i] = c;
            }
            wektor[licznik_struktur].tabgram[j][i] = '\0';
        }

        for (i = 0; i < MAXLITER; i++){
            c = getc(plik[a]);
            if(c == ' ' || c == '\n' ||c == EOF || c == '\t' || c == '.')
                break; 
            wektor[licznik_struktur].tabslowa[0][i] = c;
        }
        wektor[licznik_struktur].tabslowa[0][i] = '\0';
        wektor[licznik_struktur].i = 1;
        ++licznik_struktur;
        
	while( licznik_struktur < lw){
            for(j = 0; j < (n-1); j++){
                for(i = 0; i < MAXLITER; i++){
                    wektor[licznik_struktur].tabgram[j][i] = wektor[licznik_struktur - 1].tabgram[j+1][i];
                }
            }
            for( i = 0; i < MAXLITER; i++)
                wektor[licznik_struktur].tabgram[n-1][i] = wektor[licznik_struktur-1].tabslowa[0][i]; 

            for (i = 0; i < MAXLITER; i++){
                c = getc(plik[a]);
                if(c == ' ' || c == '\n' || c == EOF || c == '\t' || c == '.')
                    break; 
                wektor[licznik_struktur].tabslowa[0][i] = c;
            }
            wektor[licznik_struktur].tabslowa[0][i] = '\0';
            wektor[licznik_struktur].i = 1;
            ++licznik_struktur;     
            if(i == 0){
                -- licznik_struktur; 
            }
            if(c == EOF){
                break;
            }
        }
    }
    
    struct gram *wektor_wynikowy = malloc(lw*sizeof(struct gram));
    if(!wektor_wynikowy)
        printf("brak pamieci!\n");
    int powtorzenie,k;
    int licznik_struktur_wynikowy = 1;
    for(j = 0; j < n; j++){
        for( i = 0; i < MAXLITER; i++)
            wektor_wynikowy[0].tabgram[j][i] = wektor[0].tabgram[j][i];
    }
    for( i = 0; i < MAXLITER; i++)
        wektor_wynikowy[0].tabslowa[0][i] = wektor[0].tabslowa[0][i];
    wektor_wynikowy[0].i = 1;

    for (k = 1; k < licznik_struktur; k++){
        for(a = 0; a < licznik_struktur_wynikowy; a++){
            powtorzenie = 1;
            for(j = 0; j < n; j++){
                if(strcmp(wektor_wynikowy[a].tabgram[j],wektor[k].tabgram[j]) != 0){
                    powtorzenie = 0;
                    break;
                }
            }
            if(powtorzenie == 1)
                break;
        }

        if(powtorzenie == 1){
            for(i = 0; i < MAXLITER; i++)
                wektor_wynikowy[a].tabslowa[wektor_wynikowy[a].i][i] = wektor[k].tabslowa[0][i];
            ++wektor_wynikowy[a].i;
        }

        if(powtorzenie == 0){
            for(j = 0; j < n; j++){
                for(i = 0; i < MAXLITER; i++)
                    wektor_wynikowy[licznik_struktur_wynikowy].tabgram[j][i] = wektor[k].tabgram[j][i];
            }
            for(i = 0; i < MAXLITER; i++)
                wektor_wynikowy[licznik_struktur_wynikowy].tabslowa[0][i] = wektor[k].tabslowa[0][i];
            wektor_wynikowy[licznik_struktur_wynikowy].i = 1;
            ++licznik_struktur_wynikowy;
        }
    }    

  
  if(stat == 1)
    wypisz(wektor_wynikowy,n,licznik_struktur_wynikowy);
   printf("Odczytano pliki i wygenerowano wektor struktur!\n");
    if(generuj(wektor_wynikowy,licznik_struktur_wynikowy,n,wyrazy,stat) != 0){
        return 1;
    }
    if(stat_in(wektor,licznik_struktur,wektor_wynikowy,licznik_struktur_wynikowy,n, stat) != 0)
        return 1;
    free(wektor);
    free(wektor_wynikowy);
        return 0;
}
