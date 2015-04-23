#include "generator.h"
int generuj(struct gram wektor[],int licznik,int n, int w, int stat){

    FILE *out = fopen("../utworzone/tekst.txt", "w");
    
    if (out == NULL){
        fprintf(stdout,"0 można pisać do pliku");
        return 1;
    }

    srand(time(NULL));
    int i,j,k,l;
	int a,z;
    int pierwszy_n_gram;
    int slowo;
    pierwszy_n_gram = rand()%licznik;
    int flaga;
    i = n+1;
  
  for(j = 0; j < n; j++){
        fprintf(out,"%s ",wektor[pierwszy_n_gram].tabgram[j]);
    }
        slowo = rand()%(wektor[pierwszy_n_gram].i);
        fprintf(out,"%s ", wektor[pierwszy_n_gram].tabslowa[slowo]);

    for(k = (n + 1); k < w; k++, z++, a++){
        for(l = 0; l < licznik; l++){
            flaga = 1;
            for(j = 0; j < (n-1); j++){
                if(strcmp(wektor[pierwszy_n_gram].tabgram[j+1],wektor[l].tabgram[j])!= 0){
                    flaga = 0;
                    break;
                }
            }
            if(flaga == 1 && strcmp(wektor[pierwszy_n_gram].tabslowa[slowo],wektor[l].tabgram[n-1]) == 0){
                slowo = rand()%(wektor[l].i);
                fprintf(out,"%s ",wektor[l].tabslowa[slowo]);
				if(z == 5){
					fprintf(out,".");
					z = 0;
				}
				if(a == 20){
					fprintf(out,"\n");
					a = 0;
				}
				pierwszy_n_gram = l;
                ++i;
                break;
            }
        }
    }
    fclose(out);
    printf("wygenerowano tekst wyjściowy!\n");
    if(stat_out(i, stat) != 0)
        return 1;
    return 0;
}
