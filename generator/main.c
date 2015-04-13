
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv){


int n = 2; // rz�d n-gram�w, domy�lnie 2
int a = 4; // liczba akapit�w do generacji, domy�lnie 4
int s = 80; // liczba s��w do generacji, domy�lnie 80
int z = 16; // liczba zda� do generacji, domy�lnie 16
 
 int max_s = 2048;
 int max_a = 100;
 int max_z = 400;
 
  int flaga_s = 0;
  int flaga_a = 0;
  int flaga_z = 0;
  int flaga_stat = 0;
  
int i, j, tmp;

FILE *in[20];
FILE *out = "output.txt";

char * pEnd; 
 //flagi d�ugo�ci 
if (argc == 1){
    fprintf( stderr, "%s: b��d: prosz� poda� flag� wywo�ania (wpisz '-help' aby dowiedzie� si� wi�cej)\n", argv[0] ); 
    return EXIT_FAILURE;
}

if (argc > 21){
	fprintf( stderr, "%s: b��d: zbyt du�o arument�w (wpisz '-help' aby dowiedzie� si� wi�cej)\n", argv[0] ); 
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
		fprintf( stderr, "%s: b��d! Prosz� poda� w�a�ciw� liczb� s��w do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: b��d! Prosz� poda� w�a�ciw� liczb� akapit�w do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: blad! Prosz� poda� w�a�ciw� liczb� zda� do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: b��d! Prosz� poda� w�a�ciw� liczb� s��w do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: b��d! Prosz� poda� w�a�ciw� liczb� akapit�w do generacji \n", argv[0]);
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
		fprintf( stderr, "%s: b��d! Prosz� poda� w�a�ciw� liczb� zda� do generacji \n", argv[0]);
        return EXIT_FAILURE;
    }
}

else if (strcmp( argv[1], "-stat") == 0){
    flaga_stat = 1;
}
// inne flagi
else if (strcmp( argv[1], "-help") == 0){   // DO UZUPE�NIENIA PӏNIEJ
	printf( "Placeholder - opis dzia�ania programu \n");
    return 0;
}

else if (strcmp( argv[1], "-d") != 0){
	fprintf( stderr, "%s: b��d! Prosze poda� flag� wywo�ania (-help for more info) \n", argv[0]);
    return EXIT_FAILURE;
}
//obs�uga pozosta�ych argument�w
if ((flaga_s == 1 || flaga_a == 1 || flaga_z == 1) && argc == 4){
	if (strtol(argv[3],&pEnd,10) != 0L)
		n = atoi(argv[3]);
	else
		out = argv[3];
}

if ((flaga_s == 1 || flaga_a == 1 || flaga_z == 1) && argc == 5){
	if ((strtol(argv[3],&pEnd,10) == 0L) && (strtol(argv[4],&pEnd,10) != 0L)){
		out = argv[3];
		n = atoi(argv[4]);
	}
	else if ((strtol(argv[3],&pEnd,10) != 0L) && (strtol(argv[4],&pEnd,10) == 0L)){
		n = atoi(argv[3]);
		in[0] = argv[4];
	}
	else if ((strtol(argv[3],&pEnd,10) == 0L) && (strtol(argv[4],&pEnd,10) == 0L)){
		out = argv[3];
		in[0] = argv[4];
	}
}

if ((flaga_s == 1 || flaga_a == 1 || flaga_z == 1) && argc > 5){
	if ((strtol(argv[3],&pEnd,10) == 0L) && (strtol(argv[4],&pEnd,10) != 0L)){
		out = argv[3];
		n = atoi(argv[4]);
		for(i = 5, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}

	else if ((strtol(argv[3],&pEnd,10) != 0L) && (strtol(argv[4],&pEnd,10) == 0L)){
		n = atoi(argv[3]);
		for(i = 4, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}
	else if ((strtol(argv[3],&pEnd,10) == 0L) && (strtol(argv[4],&pEnd,10) == 0L)){
		out = argv[3];
		for(i = 4, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}
}

if ((flaga_s == 0 && flaga_a == 0 && flaga_z == 0) && argc == 3){
	if (strtol(argv[2],&pEnd,10) != 0L)
		n = atoi(argv[2]);
	else 
		out = argv[2];
}

if ((flaga_s == 0 && flaga_a == 0 && flaga_z == 0) && argc == 4){
	if ((strtol(argv[2],&pEnd,10) == 0L) && (strtol(argv[3],&pEnd,10) != 0L)){
		out = argv[2];
		n = atoi(argv[3]);
	}
	else if (strtol(argv[2],&pEnd,10) != 0L && (strtol(argv[3],&pEnd,10) == 0L)){
		n = atoi(argv[2]);
		in[0] = argv[3];
	}
	else if (strtol(argv[2],&pEnd,10) == 0L && (strtol(argv[3],&pEnd,10) == 0L)){
		out = argv[2];
		in[0] = argv[3];
	}
}

if ((flaga_s == 0 && flaga_a == 0 && flaga_z == 0) && argc > 4){
	if ((strtol(argv[2],&pEnd,10) == 0L) && (strtol(argv[3],&pEnd,10) != 0L)){
		out = argv[2];
		n = atoi(argv[3]);
		for(i = 4, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}

	else if ((strtol(argv[2],&pEnd,10) != 0L) && (strtol(argv[3],&pEnd,10) == 0L)){
		n = atoi(argv[2]);
		for(i = 3, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}
	else if ((strtol(argv[2],&pEnd,10) == 0L) && (strtol(argv[3],&pEnd,10) == 0L)){
		out = argv[2];
		for(i = 3, j = 0; i<argc; i++, j++){
			in[j] = argv[i];
		}
	}
}

printf("n = %i \n s = %i \n a = %i \n z = %i \n out = %s \n flaga s = %i \n flaga stat = %i \n", n, s , a, z, out, flaga_s, flaga_stat);
for (i = 0; i == 6; i++)
	printf("in = %s", in[i])
}
