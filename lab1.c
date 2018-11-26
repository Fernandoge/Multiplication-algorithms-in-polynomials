/*
* Fernando Garcia Polgatti
* Felipe Parra Castañeda
* Martin Carrasco Godoy
*
* Entorno de prueba:
* Windows 10 64 bits
* Compilador: GCC 7.21
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXCOEF 1000 //por ahora, luego se aumentara
#define MAXGRADE 1000 // por ahora, luego se aumentara

typedef struct Polinomio {
   long *p; //arreglo de coeficientes del polinomio
   unsigned long g; //grado del polinomio (grado g -> tamano g+1)
} Poly;  
	
void showPoli(Poly X, char name);
Poly createPoly(unsigned long grado, int random);
Poly copyPoli(Poly X, int signo, unsigned long grado);
Poly sumaPoli(Poly X, Poly Y);
Poly restaPoli(Poly X, Poly Y);
Poly mulClas(Poly X, Poly Y);
Poly mulClasRyD(Poly X, Poly Y);
Poly polyByConstant(Poly X, unsigned long a);
Poly polyByX(Poly X, unsigned long a);

/*---------------------------------------------------------------------------------------------------------------------------------------*/

int main(){
	int opcion;
	Poly A, B, C, D;	
	double time_spent;
	clock_t begin, end;	

	printf("Grado polinomio 1: ");
	scanf("%lu", &A.g);
	printf("Grado polinomio 2: ");
	scanf("%lu", &B.g);	
	
	printf("(1) Ingresar polinomios\n");
	printf("(2) Generar polinomios aleatorios\n");
	printf("Opcion: ");
	scanf("%d", &opcion);

	switch(opcion){ 
		case 1:
			printf("Ingresar polinomio 1 :\n");
			A = createPoly(A.g, 0);
			printf("Ingresar polinomio 2 :\n");
			B = createPoly(B.g, 0);
			break;
		case 2:
			srand(time(NULL));
			A = createPoly(A.g, 1);				
			B = createPoly(B.g, 1);				
			break;
			

		default:
			printf("Opcion invalida\n");
			free(A.p);
			free(B.p);
			exit(EXIT_SUCCESS);
	}	
	printf("\n-------------------------------------------------\n");
	printf("Polinomios ingresados:");
	printf("\n-------------------------------------------------\n");
	showPoli(A, 'A');
	showPoli(B, 'B');
	printf("\n-------------------------------------------------\n");
	printf("Polinomios copiados:");
	printf("\n-------------------------------------------------\n");		
	C = copyPoli(A, 0,A.g);
	showPoli(C, 'C');
	D = copyPoli(B, 0,B.g);
	showPoli(D, 'D');

	printf("\n-------------------------------------------------\n");	
	printf("Suma de polinomios C(x)=A(x)+B(x)");
	printf("\n-------------------------------------------------\n");	
	begin = clock();
	showPoli(sumaPoli(A, B), 'C');
	end = clock();
	time_spent = (double)(end - begin)/CLOCKS_PER_SEC; 
	printf("Tiempo empleado:\t%f\n", time_spent);
	
	printf("\n-------------------------------------------------\n");	
	
	printf("Resta de polinomios C(x)=A(x)-B(x)");
	printf("\n-------------------------------------------------\n");	
	begin = clock();
	showPoli(restaPoli(A, B), 'C');
	end = clock();
	time_spent = (double)(end - begin)/CLOCKS_PER_SEC; 
	printf("Tiempo empleado:\t%f\n", time_spent);
	
	printf("\n-------------------------------------------------\n");	
	printf("Multiplicacion Clasica C(x)=A(x)xB(x)");
	printf("\n-------------------------------------------------\n");	
	begin = clock();
	showPoli(mulClas(A, B), 'C');
	end = clock();
	time_spent = (double)(end - begin)/CLOCKS_PER_SEC; //Diferencia y transformacion a segundos
	printf("Tiempo empleado:\t%f\n", time_spent);
	
	printf("\n-------------------------------------------------\n");	
	
	printf("Multiplicacion Clasica Reducir y Conquistar C(x)=A(x)xB(x)");
	printf("\n-------------------------------------------------\n");	
	if(A.g == B.g) {
		begin = clock();
		showPoli(mulClasRyD(A, B), 'C');
		end = clock();
		time_spent = (double)(end - begin)/CLOCKS_PER_SEC; //Diferencia y transformacion a segundos
	printf("Tiempo empleado:\t%f\n", time_spent);
	} else
		printf("Polinomios deben ser de igual grado!");	

	
	free(A.p);
	free(B.p);
	free(C.p);
	free(D.p);

    return 0;
}


void showPoli(Poly X, char name) {
	unsigned long i;
	
	printf("Polinomio de grado: %lu\n%c(x) = ", X.g, name);
	if(X.p[0] != 0)	// Si el coeficiente de x^0 es 0 no lo imprime
		printf("%ld", X.p[0]);
	else
		printf("0"); 	
		
	for(i=1; i<(X.g)+1; i++) 
		if(X.p[i]<0)
			printf(" %ld(X^%lu)", X.p[i], i); 
		else
		{
			if(X.p[i] == 0)
				continue;
			else
				printf(" + %ld(X^%lu)", X.p[i], i); 
		}
			
	printf("\n");
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

Poly createPoly(unsigned long grado, int random) { //random=1 crear coeficientes random; random=0 usuario ingresa coeficientes
	unsigned long i;
	Poly Z;

	Z.g = grado;
	Z.p = (long *)calloc( grado+1, sizeof(long));
	
	if(Z.p == NULL){
		printf("Error, arreglo no inicializado!\n");
		exit(0);
	}

	if(random) {			
			for(i=0; i<Z.g+1; i++){ 
				Z.p[i] = rand()/( RAND_MAX / (MAXCOEF+1) ); 
				if(rand()%2 == 0)
					Z.p[i] = -Z.p[i];
			}

	} else {
		for(i=0; i< (Z.g)+1; i++){
				printf("Ingresar coeficiente de x^%lu:", i);
				scanf("%ld", &Z.p[i]);
			}
			if(Z.p[Z.g] == 0)
				(Z.g)--; 
	}
	
	return Z;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

Poly copyPoli(Poly X, int signo, unsigned long grado) {
	Poly Z;												
	unsigned long i;

	if(grado == X.g) {
		Z.p = (long *)calloc( (X.g)+1, sizeof(long));
		Z.g = X.g;
		
		if(Z.p == NULL){
			printf("Error, arreglo no inicializado!\n");
			exit(0);
		}
		
		if(!signo)
			for(i=0; i<(X.g)+1; i++) 
				Z.p[i]=X.p[i];
		else
			for(i=0; i<(X.g)+1; i++) 
				Z.p[i]=(-1)*X.p[i];
		
		return Z;
	} else	if (grado < X.g) {
				Z.p = (long *)calloc( (grado)+1, sizeof(long));
				Z.g = grado;

				if(Z.p == NULL){
					printf("Error, arreglo no inicializado!\n");
					exit(0);
				}

				if(!signo)
					for(i=0; i<(grado)+1; i++)
						Z.p[i]=X.p[i];
				else
					for(i=0; i<(grado)+1; i++) 
						Z.p[i]=(-1)*X.p[i];

				return Z;		

			} else {
				printf("Polinomio fuera de rango!\n");
				exit(0);
				}

	
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

Poly sumaPoli(Poly X, Poly Y){ 
	unsigned long i=0, max, sizeX = (X.g)+1, sizeY = (Y.g)+1;
	Poly Z;	
	
	max = sizeX <= sizeY ? sizeY : sizeX;	
	Z.p = (long *)calloc(max, sizeof(long));
	Z.g = max-1;
	
	if(Z.p == NULL){
		printf("Error, memoria no reservada!\n");
		exit(0);
	}		

	if(sizeX <= sizeY){
		Z = copyPoli(Y, 0, Y.g);
		while(i < sizeX){
		Z.p[i] = X.p[i]+Z.p[i];
		i++;
		}		
	}	
	else{
		Z = copyPoli(X, 0, X.g);
		while(i < sizeY){
		Z.p[i] = Z.p[i]+Y.p[i];
		i++;
		}
	}

	return Z;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

Poly restaPoli(Poly X, Poly Y){ 
	unsigned long i=0, max, sizeX = (X.g)+1, sizeY = (Y.g)+1;
	Poly Z;
	
	max = sizeX <= sizeY ? sizeY : sizeX;	
	Z.p = (long *)calloc(max, sizeof(long));
	Z.g = max-1;
	
	if(Z.p == NULL){
		printf("Error, memoria no reservada!\n");
		exit(0);
	}	
	
	if(sizeX <= sizeY){
		Z = copyPoli(Y, 1, Y.g);
		while(i < sizeX){
		Z.p[i] = X.p[i]+Z.p[i];
		i++;
		}
	}	
	else{
		Z = copyPoli(X, 0, X.g);
		while(i < sizeY){
		Z.p[i] = Z.p[i]-Y.p[i];
		i++;
		}
	}

	return Z;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

Poly polyByConstant(Poly X, unsigned long a) { 
	unsigned long i;
	Poly Z;

	Z.g = X.g;
	Z.p = (long *)calloc( (X.g)+1, sizeof(long));	
	
	if(Z.p == NULL){
		printf("Error, memoria no reservada!\n");
		exit(0);
	}

	for(i=0; i<(X.g)+1; i++) {
		Z.p[i] = a*(X.p[i]); 
	}

	return Z;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

Poly polyByX(Poly X, unsigned long a) { 
	unsigned long i;
	Poly Z;

	Z.g = (X.g)+a;
	Z.p = (long *)calloc( (Z.g)+1, sizeof(long));	
	
	if(Z.p == NULL){
		printf("Error, memoria no reservada!\n");
		exit(0);
	}

	for(i=0; i<(X.g)+1; i++) { 
		Z.p[i+a] = X.p[i]; 
	}

	return Z;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/
Poly mulClas(Poly X, Poly Y){ 
	unsigned long i, j, sizeX = (X.g)+1, sizeY = (Y.g)+1;
	Poly Z;

	Z.g = X.g + Y.g;
	Z.p = (long *)calloc( (Z.g)+1, sizeof(long));
	
	
	if(Z.p == NULL){
		printf("Error, memoria no reservada!\n");
		exit(0);
	}	

	for(i=0; i<sizeX; i++){
		for(j=0; j<sizeY; j++){
			Z.p[i+j] += X.p[i]*Y.p[j];
		}
	}

	return Z;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

Poly mulClasRyD(Poly X, Poly Y) { 
	Poly Z, A, B;

	Z.g = X.g + Y.g;
	Z.p = (long *)calloc( (Z.g)+1, sizeof(long));

	if(Z.p == NULL){
		printf("Error, memoria no reservada!\n");
		exit(0);
	}

	if(Z.g == 0) {
		Z.p[0]=0;
		return Z;
	} else {
		A = copyPoli(X, 0, (X.g)-1); 
		B = copyPoli(Y, 0, (Y.g)-1);

		Z.p[(Z.g)] = (X.p[X.g])*(Y.p[Y.g]); 
		Z = sumaPoli( Z, polyByX( sumaPoli( polyByConstant(B, X.p[X.g]), polyByConstant(A, Y.p[Y.g]) ), X.g ) ); 
		Z = sumaPoli(Z, mulClas(A, B) );

	return Z;
	}
	
}
