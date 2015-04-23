#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read.h"

int main(int argc, char* argv[]){

	int n = 2; // rząd n-gramów, domyślnie 2
	int a = 4; // liczba akapitów do generacji, domyślnie 4
	int s = 80; // liczba słów do generacji, domyślnie 80
	int z = 16; // liczba zdań do generacji, domyślnie 16
   
	int i, tmp;
    
	int  p = 0;
	char * pEnd;
	int max_s = 2048;
	int max_a = 100;
	int max_z = 400;
 
	int flaga_s = 0;
	int flaga_a = 0;
	int flaga_z = 0;
	int flaga_stat = 0;
   
   char *output = "../utworzone/tekst.txt";
	FILE *out = fopen(output, "w");
 //flagi długości 
if (argc == 1){
    fprintf( stderr, "%s: błąd: proszę podać flagę wywołania (wpisz '-help' aby dowiedzieć się więcej)\n", argv[0] ); 
    return EXIT_FAILURE;
}

if (argc > 21){
	fprintf( stderr, "%s: błąd: zbyt dużo arumentów (wpisz '-help' aby dowiedzieć się więcej)\n", argv[0] ); 
    return EXIT_FAILURE;
}

if (strcmp( argv[1], "-s") == 0){
    if(2 < argc){
        if (atoi(argv[2]) > 0 && flaga_s == 0 && atoi(argv[2]) <= max_s){
            s = atoi (argv[2]);
			flaga_s = 1;
		}
	}
    else{
		fprintf( stderr, "%s: błąd! Proszą podać właściwą liczbę słów do generacji \n", argv[0]);
            return EXIT_FAILURE;
    }
}

else if (strcmp( argv[1], "-a") == 0){
    if(2 < argc){
        if (atoi(argv[2]) > 0 && flaga_a == 0 && atoi(argv[2]) <= max_a){
            a = atoi (argv[2]);
            flaga_a = 1;
		}
	}
    else{
		fprintf( stderr, "%s: błąd! Proszą podać właściwą liczbę akapitów do generacji \n", argv[0]);
        return EXIT_FAILURE;
    }
}

else if (strcmp( argv[1], "-z") == 0){
    if(2 < argc){
        if (atoi(argv[2]) > 0 && flaga_z == 0 && atoi(argv[2]) <= max_z){
            z = atoi (argv[2]);
            flaga_z = 1;
		}
	}
    else{
		fprintf( stderr, "%s: blad! Proszą podać właściwą liczbę zdań do generacji \n", argv[0]);
        return EXIT_FAILURE;
    }
}

// flagi stat
else if (strcmp( argv[1], "-sstat") == 0){
    if(2 < argc){
        if (atoi(argv[2]) > 0 && flaga_s == 0 && atoi(argv[2]) <= max_s){
            s = atoi (argv[2]);
            flaga_s = 1;
			flaga_stat = 1;
		}
	}
    else{
		fprintf( stderr, "%s: błąd! Proszą podać właściwą liczbę słów do generacji \n", argv[0]);
        return EXIT_FAILURE;
    }
}

else if (strcmp( argv[1], "-astat") == 0){
    if(2 < argc){
        if (atoi(argv[2]) > 0 && flaga_a == 0 && atoi(argv[2]) <= max_a){
            a = atoi (argv[2]);
            flaga_a = 1;
			flaga_stat = 1;
		}
	}
    else{
		fprintf( stderr, "%s: błąd! Proszą podać właściwą liczbę akapitów do generacji \n", argv[0]);
        return EXIT_FAILURE;
    }
}

else if (strcmp( argv[1], "-zstat") == 0){
    if(2 < argc){
        if (atoi(argv[2]) > 0 && flaga_z == 0 && atoi(argv[2]) <= max_z){
            z = atoi (argv[2]);
            flaga_z = 1;
			flaga_stat = 1;
		}
	}
    else{
		fprintf( stderr, "%s: błąd! Proszą podać właściwą liczbę zdań do generacji \n", argv[0]);
        return EXIT_FAILURE;
    }
}

else if (strcmp( argv[1], "-stat") == 0){
    flaga_stat = 1;
}
// inne flagi
else if (strcmp( argv[1], "-help") == 0){   // DO UZUPEŁNIENIA PÓŹNIEJ
printf( "Witamy w programie sluzacym do generacji pseudo losowego tekstu! Przykladowe wywolanie: \n a.out -s 15 plikwyjsciowy.txt 4 tekstwejsciowy1.txt tekst2.txt tekst3.txt ...\n Gdzie pierwszy argument to flaga wywolania (w tym wypadku podajaca format dlugosci - slowa) drugi argument to ilosc jednostek obranych flaga, trzeci - plik docelowy, czwarty - wielkosc n-gramu(domyslnie 2), a pozostale pliki to tekst na ktorym program bedzie bazowal \n Dostępne flagi:\n  -s dlugosc okreslana iloscia slow\n -a dlugosc okreslana iloscia akapitow\n -z dlugosc okreslana iloscia zdan.\n -stat dodatkowy wypis prawdopodobienstwa uzycia slow zawartych w wygenerowanych zdaniach (np w celach testu algorytmu)\n");
    return 0;
}

else if (strcmp( argv[1], "-d") != 0){
	fprintf( stderr, "%s: błąd! Prosze podać flagę wywołania (-help for more info) \n", argv[0]);
    return EXIT_FAILURE;
}
//obsługa pozostałych argumentów
if ((flaga_s == 1 || flaga_a == 1 || flaga_z == 1) && argc == 4){
	if (strtol(argv[3],&pEnd,10) != 0L)
		n = atoi(argv[3]);
	else
		out = fopen(argv[3], "w");
}

if ((flaga_s == 1 || flaga_a == 1 || flaga_z == 1) && argc == 5){
	if ((strtol(argv[3],&pEnd,10) == 0L) && (strtol(argv[4],&pEnd,10) != 0L)){
		out = fopen(argv[3], "w");
		n = atoi(argv[4]);
	}
	else if ((strtol(argv[3],&pEnd,10) != 0L) && (strtol(argv[4],&pEnd,10) == 0L)){
		n = atoi(argv[3]);
		
		p = 4;
	}
	else if ((strtol(argv[3],&pEnd,10) == 0L) && (strtol(argv[4],&pEnd,10) == 0L)){
		out = fopen(argv[3], "w");
		p = 4;			
	}
}

if ((flaga_s == 1 || flaga_a == 1 || flaga_z == 1) && argc > 5){
	if ((strtol(argv[3],&pEnd,10) == 0L) && (strtol(argv[4],&pEnd,10) != 0L)){
		out = fopen(argv[3], "w");
		n = atoi(argv[4]);
		p = 5;
	}

	else if ((strtol(argv[3],&pEnd,10) != 0L) && (strtol(argv[4],&pEnd,10) == 0L)){
		n = atoi(argv[3]);
		p = 4;
		
	}
	else if ((strtol(argv[3],&pEnd,10) == 0L) && (strtol(argv[4],&pEnd,10) == 0L)){
		out = fopen(argv[3], "w");
		p = 4;
		
	}
}

if ((flaga_s == 0 && flaga_a == 0 && flaga_z == 0) && argc == 3){
	if (strtol(argv[2],&pEnd,10) != 0L)
		n = atoi(argv[2]);
	else 
		out = fopen(argv[2], "w");
}

if ((flaga_s == 0 && flaga_a == 0 && flaga_z == 0) && argc == 4){
	if ((strtol(argv[2],&pEnd,10) == 0L) && (strtol(argv[3],&pEnd,10) != 0L)){
		out = fopen(argv[2], "w");
		n = atoi(argv[3]);
	}
	else if (strtol(argv[2],&pEnd,10) != 0L && (strtol(argv[3],&pEnd,10) == 0L)){
		n = atoi(argv[2]);
		p = 3 ;
	}
	else if (strtol(argv[2],&pEnd,10) == 0L && (strtol(argv[3],&pEnd,10) == 0L)){
		out = fopen(argv[2], "w");
		p = 3;
	}
}

if ((flaga_s == 0 && flaga_a == 0 && flaga_z == 0) && argc > 4){
	if ((strtol(argv[2],&pEnd,10) == 0L) && (strtol(argv[3],&pEnd,10) != 0L)){
		out = fopen(argv[2], "w");
		n = atoi(argv[3]);
		p = 4;
		
	}

	else if ((strtol(argv[2],&pEnd,10) != 0L) && (strtol(argv[3],&pEnd,10) == 0L)){
		n = atoi(argv[2]);
		p = 3;
	}
	else if ((strtol(argv[2],&pEnd,10) == 0L) && (strtol(argv[3],&pEnd,10) == 0L)){
		out = fopen(argv[2], "w");
		p = 3;
	}
}
if(flaga_s == 1){
	a = s/20;
	z = s/5;
}
if(flaga_a == 1){
	s = a*20;
	z = a*4;
}
if(flaga_z == 1){
	a = z/4;
	s = z*5;
}

if(flaga_s == 1){
	a = s/20;
	z = s/5;
}
if(flaga_a == 1){
	s = a*20;
	z = a*4;
}
if(flaga_z == 1){
	a = z/4;
	s = z*5;
}

    FILE *in[30];
    int x = 0;
    char *folder = "../baza/";
    char buf[100];
    strcpy(buf,folder);
    int d = 8;
    char *domyslny = "../baza/Krzyzacy.txt"; 
    if(p == 0){
	strcpy(buf,domyslny);
	in[x] = fopen(buf, "r");
	x++;
    }
    else{
        for( tmp = p; tmp < argc; tmp++){
    	   /*odczyt plików*/
              for(d = 8; d < 100; d++){
                 buf[d] = argv[tmp][d-8];
              }
              in[x] = fopen(buf, "r");
              if (in[x] == NULL){
                 printf("Nie mozna otworzyc %s\n", argv[tmp]);
                 return 1;
              }
	x++;
        }
   }
        
    

    int ile_slow;
    ile_slow = slowa(in,x);
 
if(ile_slow < n || ile_slow < s){
	printf("Teksty źródłowe zawierają zbyt mało tekstu! Wprowadź większą bazę lub zmniejsz wymagania ilości słów/ wielkości ngramu do generacji.\n");
	return 1;
}
	
    if(read_file(n,in,x,ile_slow,s,flaga_stat) != 0){
        return 1;
    }
    
    for(d = 0; d < x; d++)
       fclose(in[d]);
    return 0;
}
