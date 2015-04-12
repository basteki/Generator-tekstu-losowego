#include "main.h"
#include "generator.h"
#include "ngram.h"
#include "read.h"
#include "write.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv){


int n = 2; // rz¹d n-gramów, domyœlnie 2
int a = 4; // liczba akapitów do generacji, domyœlnie 4
int s = 80; // liczba s³ów do generacji, domyœlnie 80
int z = 16; // liczba zdañ do generacji, domyœlnie 16
 
 int max_s = 2048;
 int max_a = 100;
 int max_z = 400;
 
  int flaga_s = 0;
  int flaga_a = 0;
  int flaga_z = 0;
  int flaga_stat = 0;
  
int i, j, tmp;

FILE *in[20];
FILE *out = ../utworzone_teksty/output.txt;
 
 //flagi d³ugoœci 
if (argc == 1){
    fprintf( stderr, "%s: b³¹d: proszê podaæ flagê wywo³ania (wpisz '-help' aby dowiedzieæ siê wiêcej)\n", argv[0] ); 
    return EXIT_FAILURE;
}

if (argc > 21){
	fprintf( stderr, "%s: b³¹d: zbyt du¿o arumentów (wpisz '-help' aby dowiedzieæ siê wiêcej)\n", argv[0] ); 
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
		fprintf( stderr, "%s: b³¹d! Prosz¹ podaæ w³aœciw¹ liczbê s³ów do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: b³¹d! Prosz¹ podaæ w³aœciw¹ liczbê akapitów do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: b³¹d! Prosz¹ podaæ w³aœciw¹ liczbê zdañ do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: b³¹d! Prosz¹ podaæ w³aœciw¹ liczbê s³ów do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: b³¹d! Prosz¹ podaæ w³aœciw¹ liczbê akapitów do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: b³¹d! Prosz¹ podaæ w³aœciw¹ liczbê zdañ do generacji \n", argv[0]);
        return EXIT_FAILURE;
    }
}

else if (strcmp( argv[1], "-stat") == 0){
    flaga_stat = 1;
}

else if (strcmp( argv[1], "-help") == 0){   // DO UZUPE£NIENIA PÓNIEJ
	fprintf( "Placeholder - opis dzia³ania programu \n");
    return 0;
}

else if (strcmp( argv[1], "-d") != 0){
	fprintf( stderr, "%s: b³¹d! Prosze podaæ flagê wywo³ania (-help for more info) \n", argv[0]);
    return EXIT_FAILURE;
}
//obs³uga pozosta³ych argumentów
if ((flaga_s == 1 || flaga_a == 1 || flaga_z == 1) && argc = 4){
	if (argv[3] == (int)argv[3])
		n = argv[3];
	else
		out = argv[2];
}

if ((flaga_s == 1 || flaga_a == 1 || flaga_z == 1) && argc = 5){
	if (argv[3] == (int)argv[3] && argv[4] != (int)argv[4] ){
		out = argv[3];
		n = argv[4];
	}
	else if (argv[3] != (int)argv[3] && argv[4] == (int)argv[4] ){
		n = argv[3];
		in[0] = argv[4];
	}
	else if (argv[3] == (int)argv[3] && argv[4] == (int)argv[4] ){
		out = argv[3];
		in[0] = argv[4];
	}
}

if ((flaga_s == 1 || flaga_a == 1 || flaga_z == 1) && argc > 5){
	if (argv[3] == (int)argv[3] && argv[4] != (int)argv[4] ){
		out = argv[3];
		n = argv[4];
		for(i = 5, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}

	else if (argv[3] != (int)argv[3] && argv[4] == (int)argv[4] ){
		n = argv[3];
		for(i = 4, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}
	else if (argv[3] == (int)argv[3] && argv[4] == (int)argv[4] ){
		out = argv[3];
		for(i = 4, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}
}

if ((flaga_s == 0 && flaga_a == 0 && flaga_z == 0) && argc = 3){
	if (argv[2] == (int)argv[2])
		n = argv[2];
	else 
		out = argv[2];
}

if ((flaga_s == 0 && flaga_a == 0 && flaga_z == 0) && argc = 4){
	if (argv[2] == (int)argv[2] && argv[3] != (int)argv[3] ){
		out = argv[2];
		n = argv[3];
	}
	else if (argv[2] != (int)argv[2] && argv[3] == (int)argv[3] ){
		n = argv[2];
		in[0] = argv[3];
	}
	else if (argv[2] == (int)argv[2] && argv[3] == (int)argv[3] ){
		out = argv[2];
		in[0] = argv[3];
	}
}

if ((flaga_s == 0 && flaga_a == 0 && flaga_z == 0) && argc > 4){
	if (argv[2] == (int)argv[2] && argv[3] != (int)argv[3] ){
		out = argv[2];
		n = argv[3];
		for(i = 4, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}

	else if (argv[2] != (int)argv[2] && argv[3] == (int)argv[3] ){
		n = argv[2];
		for(i = 3, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}
	else if (argv[2] == (int)argv[2] && argv[3] == (int)argv[3] ){
		out = argv[2];
		for(i = 3, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}
}

}