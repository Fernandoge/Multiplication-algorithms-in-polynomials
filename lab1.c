/*
* Fernando Garcia Polgatti
* Felipe Parra Castañeda
* Martin Carrasco Godoy
*
* Entorno de prueba:
* Ubuntu 18.04
* Compilador: GCC 7.21
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Coeficientes mápolinomioInAimos para el tamaño de los arreglos dinámicos
#define MAXCOEF (1048576) // 2^20
#define MAXGRADE (4194304) // 2^22

//Struct que tendrá la estructura para representar los polinomios
typedef struct Polinomio {
   long *p; // Arreglo que contendrá los coeficientes del polinomio
   unsigned long g; //grado que tendrá el polinomio
} polinomio;  
	


// Declaración de funciones

void mostrarPolinomio(polinomio polinomioInA, char name);
polinomio crearPolinomio(unsigned long grado, int esAleatorio);
polinomio copiarPolinomio(polinomio polinomioInA, int signo, unsigned long grado);
polinomio copiaEspecial(polinomio polinomioInA, unsigned long inicio, unsigned long fin);
polinomio sumarPolinomios(polinomio polinomioInA, polinomio polinomioInB);
polinomio restarPolinomios(polinomio polinomioInA, polinomio polinomioInB);
polinomio multiplicacionClasica(polinomio polinomioInA, polinomio polinomioInB);
polinomio multiplicacionClasicaRyD(polinomio polinomioInA, polinomio polinomioInB);
polinomio polinomioConstante(polinomio polinomioInA, unsigned long a);
polinomio elevarPolinomio(polinomio polinomioInA, unsigned long a);
polinomio multiplicacionInduccion(polinomio polinomioInA, polinomio polinomioInB);
polinomio multiplicacionKaratsuba(polinomio polinomioInA, polinomio polinomioInB);

// Función Main
int main()
{
	int opcion;
	//Polinomios de entrada y resultantes
	polinomio A, B, C, D;	
	
	//Variables que servirá para la medición de tiempos
	double time_spent;
	clock_t begin, end;	

	printf("\nIngrese los grados de los polinomios, considere que para la realización de multiplicaciones\nambos polinomios tienen que tener el mismo grado");
	printf("\nPolinomio 1:\n");
	scanf("%lu", &A.g);
	printf("\nPolinomio 2:\n");
	scanf("%lu", &B.g);	
	
	printf("\nSelecciones si desea ingresar los coeficientes manualmente o de manera aleatoria.\n");
	printf("1- Ingresar coeficientes manualmente\n");
	printf("2- Generar los coeficientes de manera aleatoria.\n");
	printf("Opcion:");
	scanf("%d", &opcion);

	//Switch que verificará si el usuario ingresará los valores manualmente o los quiere generar de manera aleatoria
	switch(opcion){ 
		case 1:
			//En caso que se desee agregar los valores manualmente, se llama a la función crearPolinomio
			printf("Ingrese los coeficientes del polinomio 1 :\n");
			A = crearPolinomio(A.g, 0);
			printf("Ingrese los coeficientes del polinomio 2:\n");
			B = crearPolinomio(B.g, 0);
			break;
		case 2:
			//En caso que se desee crear los valores aleatoriamente.
			srand(time(NULL));
			A = crearPolinomio(A.g, 1);				
			B = crearPolinomio(B.g, 1);				
			break;
		default:
			//En caso que el usuario ingrese una opción erronea, se libera la memoria
			printf("Opcion invalida\n");
			free(A.p);
			free(B.p);
			exit(EXIT_SUCCESS);
	}

	printf("\nP o l i n o m i o s  I n g r e s a d o s:\n\n");
	printf("polinomioA:\n");
	mostrarPolinomio(A, 'A');
	printf("polinomioB:\n");
	mostrarPolinomio(B, 'B');
	printf("\n\nC o p i a  D e  P o l i n o m i o s:\n\n");
	printf("Se copian los 2 polinomios anteriores en los nuevos polinomios C y D\n");
	printf("Polinomio C, el cual almacena los datos del polinomio A:\n");
	C = copiarPolinomio(A, 0,A.g);
	mostrarPolinomio(C, 'C');
	printf("\nPolinomio D, el cual almacena los datos del polinomio B:\n");
	D = copiarPolinomio(B, 0,B.g);
	mostrarPolinomio(D, 'D');

	printf("\n\nS u m a  D e  P o l i n o m i o s:\n\n");

	printf("Se suman los polinomios A y B y se guarda en un nuevo polinomio C:\n\n");
	begin = clock();
	mostrarPolinomio(sumarPolinomios(A, B), 'C');
	end = clock();
	time_spent = (double)(end - begin)/CLOCKS_PER_SEC; 
	printf("Tiempo que tardó en realizar la suma:\t%f\n", time_spent);
	
	printf("\n\nR e s t a  D e  P o l i n o m i o s:\n\n");
	
	printf("Se restan los polinomios A y B y se guarda en un nuevo polinomio C:\n\n");
	begin = clock();
	mostrarPolinomio(restarPolinomios(A, B), 'C');
	end = clock();
	time_spent = (double)(end - begin)/CLOCKS_PER_SEC; 
	printf("Tiempo que tardó en realizar la resta:\t%f\n", time_spent);
	
	printf("\n\nM u l t i p l i c a c i ó n  C l á s i c a:\n\n");
	printf("Se multiplican los polinomios A y B utilizando el método tradicional:\n\n");
	begin = clock();
	mostrarPolinomio(multiplicacionClasica(A, B), 'C');
	end = clock();
	time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
	printf("Tiempo que tardó en realizar la multiplicación tradicional:\t%f\n", time_spent);
	
	if(A.g == B.g)
	{
		printf("\n\nM u l t i p l i c a c i ó n  R e d u c i r  y  C o n q u i s t a r\n\n");
		
		printf("Se multiplican los polinomios A y B utilizando el método \"reducir y conquistar\"\n\n");
			begin = clock();
			mostrarPolinomio(multiplicacionClasicaRyD(A, B), 'C');
			end = clock();
			time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
		printf("Tiempo que tardó en realizar la multiplicación utilizando el método \"dividir y conquistar\":\t%f\n", time_spent);	


		printf("\n\nM u l t i p l i c a c i ó n  D i v i d i r  y  C o n q u i s t a r\n\n");

		printf("\nSe multiplican los polinomios A y B y utilizando el método \"Dividir y conquistar\"\n");	
			begin = clock();
			mostrarPolinomio(multiplicacionInduccion(A, B), 'C');
			end = clock();
			time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
		printf("Tiempo que tardó en realizar la multiplicación utilizando el método \"Dividir y conquistar\":\t%f\n", time_spent);
		
		
		printf("\n\nM u l t i p l i c a c i ó n  K a r a t s u b a\n\n");
		
		printf("Se multiplican los polinomios A y B utilizando el método \"Karatsuba\"\n");
			begin = clock();
			mostrarPolinomio(multiplicacionKaratsuba(A, B), 'C');
			end = clock();
			time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
		printf("Tiempo que tardó en realizar la multiplicación utilizando el método \"Karatsuba\":\t%f\n\n\n", time_spent);
	}

	else
	{
		printf("\n\nComo los grados de los polinomios A y B, eran distintos, no se realizaron las multiplicaciones utilizando los métodos: Reducir y Conquistar; Dividir y Conquistar; Karatsuba.\n\n");
	}
	

	// Se liberan los espacios de memorias.
	free(A.p);
	free(B.p);
	free(C.p);
	free(D.p);
    return 0;
}

/*
Función mostrar recibe un polinomio como entrada y recorre término por término y lo va mostrando por pantalla, cada i
representa el grado que acompaña de X que acompaña al coeficiente que está en polIn[i]
*/

void mostrarPolinomio(polinomio polIn, char name) {
	unsigned long i;
	printf("El polinomio tiene grado: %lu.\n%c(X) = ", polIn.g, name);
	if(polIn.p[0] != 0)
		printf("%ld", polIn.p[0]);
	else
		printf("0"); 	
		for(i=1; i<(polIn.g)+1; i++)
	{
		if(polIn.p[i]<0)
			printf(" %ld(X^%lu)", polIn.p[i], i); 
		else
		{
			if(polIn.p[i] == 0)
				continue;
			else
				printf(" + %ld(polIn^%lu)", polIn.p[i], i); 
		}
	}
	printf("\n\n");
}

/*
Funcion crearPolinomio Recibe el grado que se desea para la creación del polinomio, y según la opción  si es aleatorio o no
realiza la creación aleatoria o manual.
*/
polinomio crearPolinomio(unsigned long grado, int esAleatorio) {
	unsigned long i;
	polinomio polOut;
	polOut.g = grado;
	polOut.p = (long *)calloc( grado+1, sizeof(long));
	if(polOut.p == NULL)
	{
		printf("No se incializó el arreglo\n");
		exit(0);
	}
	if(esAleatorio) 
	{			
		for(i=0; i<polOut.g+1; i++)
		{ 
			polOut.p[i] = rand()/( RAND_MAX / (MAXCOEF+1) ); 
			if(rand()%2 == 0)
			{
				polOut.p[i] = -polOut.p[i];
			}
		}

	} else {
		for(i=0; i< (polOut.g)+1; i++)
		{
			printf("Ingresar coeficiente de polinomioInA^%lu:", i);
			scanf("%ld", &polOut.p[i]);
		}
		if(polOut.p[polOut.g] == 0)
			(polOut.g)--; 
	}
	return polOut;
}

/*
Función copiarPolinomio recibe un polinomio de entrada con su grado y signo, y crea una variable polinomio polOut
que será el polinomio resultante con la copia del polinomio de entrada
*/
polinomio copiarPolinomio(polinomio polinomioInA, int signo, unsigned long grado) {
	polinomio polOut;												
	unsigned long i;

	if(grado == polinomioInA.g) {
		polOut.p = (long *)calloc( (polinomioInA.g)+1, sizeof(long));
		polOut.g = polinomioInA.g;
		
		if(polOut.p == NULL){
			printf("No se incializó el arreglo.\n");
			exit(0);
		}
		
		if(!signo)
			for(i=0; i<(polinomioInA.g)+1; i++) 
				polOut.p[i]=polinomioInA.p[i];
		else
			for(i=0; i<(polinomioInA.g)+1; i++) 
				polOut.p[i]=(-1)*polinomioInA.p[i];
		
		return polOut;
	} else	if (grado < polinomioInA.g) {
				polOut.p = (long *)calloc( (grado)+1, sizeof(long));
				polOut.g = grado;

				if(polOut.p == NULL){
					printf("No se incializó el arreglo.\n");
					exit(0);
				}

				if(!signo)
					for(i=0; i<(grado)+1; i++)
						polOut.p[i]=polinomioInA.p[i];
				else
					for(i=0; i<(grado)+1; i++) 
						polOut.p[i]=(-1)*polinomioInA.p[i];

				return polOut;		

			} else {
				printf("El polinomio epolinomioInAcede el rango disponible.\n");
				exit(0);
				}
}


/*
Funcion sumarPolinomios, recibe 2 polinomios de entrada y crea un polinomio salida, e irá sumando los términos [i] de los
polinomios de entrada y los irá agregando a la ubicación [i] del ṕolinomio de salida
*/
polinomio sumarPolinomios(polinomio polinomioInA, polinomio polinomioInB){ 
	unsigned long i=0, mapolinomioInA, sizepolinomioInA = (polinomioInA.g)+1, sizepolinomioInB = (polinomioInB.g)+1;
	polinomio polOut;	
	
	mapolinomioInA = sizepolinomioInA <= sizepolinomioInB ? sizepolinomioInB : sizepolinomioInA;	
	polOut.p = (long *)calloc(mapolinomioInA, sizeof(long));
	polOut.g = mapolinomioInA-1;
	
	if(polOut.p == NULL){
		printf("Memoria no reservada\n");
		exit(0);
	}		

	if(sizepolinomioInA <= sizepolinomioInB){
		polOut = copiarPolinomio(polinomioInB, 0, polinomioInB.g);
		while(i < sizepolinomioInA)
		{
			polOut.p[i] = polinomioInA.p[i]+polOut.p[i];
			i++;
		}		
	}	
	else{
		polOut = copiarPolinomio(polinomioInA, 0, polinomioInA.g);
		while(i < sizepolinomioInB)
		{
			polOut.p[i] = polOut.p[i]+polinomioInB.p[i];
			i++;
		}
	}
	return polOut;
}

/*
Funcion sumarPolinomios, recibe 2 polinomios de entrada y crea un polinomio salida, e irá restando los términos [i] de los
polinomios de entrada y los irá agregando a la ubicación [i] del ṕolinomio de salida
*/
polinomio restarPolinomios(polinomio polinomioInA, polinomio polinomioInB){ 
	unsigned long i=0, mapolinomioInA, sizepolinomioInA = (polinomioInA.g)+1, sizepolinomioInB = (polinomioInB.g)+1;
	polinomio polOut;
	
	mapolinomioInA = sizepolinomioInA <= sizepolinomioInB ? sizepolinomioInB : sizepolinomioInA;	
	polOut.p = (long *)calloc(mapolinomioInA, sizeof(long));
	polOut.g = mapolinomioInA-1;
	
	if(polOut.p == NULL){
		printf("Memoria no reservada\n");
		exit(0);
	}	
	
	if(sizepolinomioInA <= sizepolinomioInB){
		polOut = copiarPolinomio(polinomioInB, 1, polinomioInB.g);
		while(i < sizepolinomioInA){
		polOut.p[i] = polinomioInA.p[i]+polOut.p[i];
		i++;
		}
	}	
	else{
		polOut = copiarPolinomio(polinomioInA, 0, polinomioInA.g);
		while(i < sizepolinomioInB){
		polOut.p[i] = polOut.p[i]-polinomioInB.p[i];
		i++;
		}
	}

	return polOut;
}

/*
Funcion utilizada para generar un polinomio constante en base a un polinomio de entrada
*/
polinomio polinomioConstante(polinomio polinomioInA, unsigned long a) { 
	unsigned long i;
	polinomio polOut;

	polOut.g = polinomioInA.g;
	polOut.p = (long *)calloc( (polinomioInA.g)+1, sizeof(long));	
	
	if(polOut.p == NULL){
		printf("Memoria no reservada\n");
		exit(0);
	}

	for(i=0; i<(polinomioInA.g)+1; i++) {
		polOut.p[i] = a*(polinomioInA.p[i]); 
	}

	return polOut;
}


/*
Funcion elevarPolinomio aumenta en 1 el  grado del polinomio entrante y crea un polinomio de salida con este nuevo grado,
al cual le va agregando los coeficientes del polinomio de entrada.
*/
polinomio elevarPolinomio(polinomio polinomioInA, unsigned long a) { 
	unsigned long i;
	polinomio polOut;

	polOut.g = (polinomioInA.g)+a;
	polOut.p = (long *)calloc( (polOut.g)+1, sizeof(long));	
	
	if(polOut.p == NULL){
		printf("Memoria no reservada\n");
		exit(0);
	}

	for(i=0; i<(polinomioInA.g)+1; i++) { 
		polOut.p[i+a] = polinomioInA.p[i]; 
	}

	return polOut;
}

/*
Implementación de la multiplicación clásica entre 2 polinomios
*/
polinomio multiplicacionClasica(polinomio polinomioInA, polinomio polinomioInB){ 
	unsigned long i, j, sizepolinomioInA = (polinomioInA.g)+1, sizepolinomioInB = (polinomioInB.g)+1;
	polinomio polOut;

	polOut.g = polinomioInA.g + polinomioInB.g;
	polOut.p = (long *)calloc( (polOut.g)+1, sizeof(long));
	
	
	if(polOut.p == NULL){
		printf("Memoria no reservada\n");
		exit(0);
	}	

	for(i=0; i<sizepolinomioInA; i++){
		for(j=0; j<sizepolinomioInB; j++){
			polOut.p[i+j] += polinomioInA.p[i]*polinomioInB.p[j];
		}
	}

	return polOut;
}

/*
Implementación de la multiplicación RyD entre 2 polinomios
*/
polinomio multiplicacionClasicaRyD(polinomio polinomioInA, polinomio polinomioInB) { 
	polinomio polOut, A, B;

	polOut.g = polinomioInA.g + polinomioInB.g;
	polOut.p = (long *)calloc( (polOut.g)+1, sizeof(long));

	if(polOut.p == NULL){
		printf("Memoria no reservada\n");
		exit(0);
	}

	if(polOut.g == 0) {
		polOut.p[0]=0;
		return polOut;
	} else {
		A = copiarPolinomio(polinomioInA, 0, (polinomioInA.g)-1); 
		B = copiarPolinomio(polinomioInB, 0, (polinomioInB.g)-1);

		polOut.p[(polOut.g)] = (polinomioInA.p[polinomioInA.g])*(polinomioInB.p[polinomioInB.g]); 
		polOut = sumarPolinomios( polOut, elevarPolinomio( sumarPolinomios( polinomioConstante(B, polinomioInA.p[polinomioInA.g]), polinomioConstante(A, polinomioInB.p[polinomioInB.g]) ), polinomioInA.g ) ); 
		polOut = sumarPolinomios(polOut, multiplicacionClasica(A, B) );

	return polOut;
	}
	
}

/*
Copia especial entre 2 polinomios de entrada, que se utiliza en la multiplicación por inducción y karatsuba
*/
polinomio copiaEspecial(polinomio polinomioInA, unsigned long inicio, unsigned long fin) {
	unsigned long i, j;
	polinomio polOut;
	
	if(!inicio)	
		polOut.g = (polinomioInA.g/2)-1;
	else
		if (polinomioInA.g%2 == 0)
			polOut.g = polinomioInA.g/2;
		else
			polOut.g = (polinomioInA.g/2)+1;
	polOut.p = (long *)calloc( (fin-inicio)+1, sizeof(long));		
		
	if(polOut.p == NULL){
		printf("Arreglo no inicializado\n");
		exit(0);
	}

	for(i=inicio, j=0; i<=fin; i++, j++)
		polOut.p[j] = polinomioInA.p[i];

	return polOut;
}
/*
Implementación de la multiplicación entre 2 polinomios utilizando el método de inducción
*/
polinomio multiplicacionInduccion(polinomio polinomioInA, polinomio polinomioInB) {
	unsigned long mid;
	polinomio A0, A1, B0, B1, polOut;

	if(polinomioInA.g == 1 || polinomioInA.g == 0)
		return multiplicacionClasica(polinomioInA, polinomioInB);
	else {
		polOut.g = polinomioInA.g + polinomioInB.g;
		polOut.p = (long *)calloc( (polOut.g)+1, sizeof(long));

		if(polOut.p == NULL){
			printf("Memoria no reservada\n");
			exit(0);
		}
		
		mid = (polinomioInA.g/2);
		A0 = copiaEspecial(polinomioInA, 0, mid-1);
		A1 = copiaEspecial(polinomioInA, mid, polinomioInA.g);
		polinomio copiaEspecial(polinomio polinomioInA, unsigned long inicio, unsigned long fin);
		B0 = copiaEspecial(polinomioInB, 0, mid-1);
		B1 = copiaEspecial(polinomioInB, mid, polinomioInB.g);		
		polOut = multiplicacionClasica(A0, B0);
		polOut = sumarPolinomios(polOut, elevarPolinomio(sumarPolinomios(multiplicacionClasica(A0, B1), multiplicacionClasica(A1, B0)), mid));
		polOut = sumarPolinomios(polOut, elevarPolinomio(multiplicacionClasica(A1, B1), 2*mid));	
		return polOut;
	}	
}

/*
Implementación de la multiplicación entre 2 polinomios utilizando el método de Karatsuba
*/
polinomio multiplicacionKaratsuba(polinomio polinomioInA, polinomio polinomioInB) {
	unsigned long mid;
	polinomio A0, A1, B0, B1, T, U, polOut, W, L;

	L.g = polinomioInA.g + polinomioInB.g;
	L.p = (long *)calloc( (L.g)+1, sizeof(long));

	if(L.p == NULL){
		printf("Memoria no reservada\n");
		exit(0);
	}

	if(polinomioInA.g == 1 || polinomioInA.g == 0)
		return multiplicacionClasica(polinomioInA, polinomioInB);
	else {
		mid = (polinomioInA.g/2);
		A0 = copiaEspecial(polinomioInA, 0, mid-1);
		A1 = copiaEspecial(polinomioInA, mid, polinomioInA.g);
		B0 = copiaEspecial(polinomioInB, 0, mid-1);
		B1 = copiaEspecial(polinomioInB, mid, polinomioInB.g);

		T = multiplicacionClasica(sumarPolinomios(A0, A1), sumarPolinomios(B0, B1));
		U = multiplicacionClasica(A0, B0);
		polOut = multiplicacionClasica(A1, B1);

		W = restarPolinomios(T, U);
		W = restarPolinomios(W, polOut);
		W = elevarPolinomio(W, mid);

		U = sumarPolinomios(U, elevarPolinomio(polOut, 2*mid) );
		L = sumarPolinomios(U, W);

		return L;
	}
}