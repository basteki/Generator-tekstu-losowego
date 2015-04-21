#include "write.h"

void wypisz(struct gram wektor[], int n, int licznik_struktur){

    int k,j,i;
    FILE *out = fopen("../utworzone/wektor_struktur.txt","w");
    for (k = 0; k < licznik_struktur; k++){
        fprintf(out,"[ ");
        for (j = 0; j < n; j++){

            fprintf(out,"%s",wektor[k].tabgram[j]);
            fprintf(out," ");
        }   
        fprintf(out,"]\t\t ");
        for(i = 0; i < wektor[k].i; i++)
            fprintf(out,"[%s]",wektor[k].tabslowa[i]);
        fprintf(out,"\n");
    }   
    fprintf (out,"ilość  =  %d \n", licznik_struktur);
    fclose(out);
}