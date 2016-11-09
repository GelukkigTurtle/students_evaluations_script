/** Created by: Freddy Ayala @gelukkigturtle
    
  This script shows a user menu with 4 options. 
  
  1) Fill a students array and fill 3 evaluations per each student,
     maximum 10 students configurated.
	 
  2) Order the students array by allphabetically ascending order and 
     print a formatted table for the user.
  
  3) Show the original student array
  
  4) Exit
  
  Note: every time the user print the table on the screen
        the program will write the table in a file 

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Variables Globales */

// Constantes
const int NUM_NOTAS = 3, STU_NUM = 10, STU_LENGTH = 30;

// Contador de estudiantes, lleva la cuenta de cuantos estudiantes se han ingresado al arreglo
int CONTADOR_STU = 0;

// Arreglos donde se guardan los datos de los estudiantes
char nombres[10][30];
char nombresOrdenados[10][30];
char notas[10][11];

// Banderas 
bool abrirArchivo = false;

// Stream del archivo donde se escribe
FILE *f;

// Variables para imprimir tabla con buen formato
const char separator = ' ';
const int columnWidth = 15;

/*  Fin Variables Globales */

/* Funciones de Utilidad */
void mostrarMenu()
{
	printf("\n**********************************************\n");
	printf("\tMENU DE OPCIONES\n");
	printf("**********************************************\n");
	printf("1) Capturar Datos\n");
	printf("2) Ordenar de forma alfabetica (ASCENDENTE)\n");
	printf("3) Mostrando contenido\n");
	printf("4) Salir\n\n\n");
}

// Funcion para obtener cada nombre de la lista de estudiantes
void obtenerNombres()
{
	for (int i = CONTADOR_STU;i < CONTADOR_STU + 1;i++)
	{
		printf("Ingresar nombre del [%d] estudiante : ",i+1);
		scanf_s(" %[^\n]",&nombres[i],30);
		//scanf_s("%s", &nombres[i]);
	}
}

// Funcion para convertir cadenas de minuscula a mayusculas
char* aMayusculas(char* palabra)
{
	for (char* p = palabra; *p != '\0'; p++)
	{
		if (*p >= 'a' && *p <= 'z')  //Solo si es una letra minuscula
			*p -= 32;
	}
	return palabra;
}

// Funcion para obtener solo las notas de cada estudiante ingresado
void obtenerNotas()
{
	for (int i = CONTADOR_STU; i < CONTADOR_STU + 1; i++)
	{
		for (int j = 0; j < NUM_NOTAS; j++)
		{
			printf("Ingresar la nota [%d] del estudiante %s :",j+1,nombres[i]);
			scanf_s("%d", &notas[i][j]);
		}
	}
}

// Funcion para preguntar si desea agregar otro estudiante a la lista actual
bool preguntarPorOtroEstudiante() {

	bool continua = false;

	printf("\nEl total de estudiantes actual es: %d\n",CONTADOR_STU);
	char respuesta[25];

	if (CONTADOR_STU < STU_NUM)
	{ // Si no ha alcanzado el limite de estudiantes

		printf("\nDesea agregar otro estudiante?(y/n)\n");
		scanf_s("%s", &respuesta, 25
		);

		//Si desea agregar otro estudiante
		if (respuesta[0] == 'y')
		{
			continua = true;
		}
		else if (respuesta[0] == 'n')
		{
			continua = false;
		}
		else
		{
			continua = false;
		}
	}

	return continua;

}

// Funcion para mostrar toda la informacion de los estudiantes ingresados
void mostrarInformacion(char titulo[300], char nombresParam[10][30])
{
	printf("\n %s",titulo);
	printf("%-17s","# NOMBRES");
	printf("%-8s","N1");
	printf("%-8s","N2");
	printf("%-8s","N3");
	printf("\n-------------------------------------------------");
	for (int i = 0; i < CONTADOR_STU; i++)
	{
		printf("\n");
		printf("%-2d) %-15s",i+1, aMayusculas(nombresParam[i]));

		for (int j = 0; j < NUM_NOTAS; j++)
		{
			printf("%-7d", notas[i][j]);


		}
	}
	printf("\n");

}
// Funcion para escribir tablas de informacion en el archivo creado
void escribirEnArchivo(char titulo[300])
{
	

	fprintf(f, "%s", titulo);
	
	fprintf(f, "%s", "\n# NOMBRES\t\t");
	fprintf(f, "%s", "N1\t");
	fprintf(f, "%s", "N2\t");
	fprintf(f, "%s", "N3\t\n");
	
	fprintf(f, "%s", "-------------------------------------------------\n");

	for (int i = 0; i < CONTADOR_STU; i++)
	{
		fprintf(f, "%d) %s \t\t",i+1, nombres[i]);
		for (int j = 0; j < NUM_NOTAS; j++)
		{
			fprintf(f, "%d \t", notas[i][j] );
		}
		fprintf(f, "%s", "\n");
	}
	fprintf(f, "%s", "\n");
}

//Funcion para ordenar el listado de estudiantes alfabeticamente Ascendente
void ordenarAlfabeticamenteAsc()
{
	int n = CONTADOR_STU, k, l;
	int len1, len2, min;
	char nombreTemp[30];
	int notaTemp[10];

	// Realizamos un copia del arreglo original al que sera ordenado
	for (int z = 0; z < CONTADOR_STU; z++) {
		strcpy(nombresOrdenados[z], nombres[z]);
	}

	// Se emplea metodo de la burbuja para ordenar el arreglo de nombres de estudiantes
	for (int i = 0;i<n - 1;i++) {
		for (int j = 0; j<n - i - 1; j++) {
			// Ya que C no tiene la funcion min, se encuentra el min paso a paso
			len1 = strlen(nombresOrdenados[j]);
			len2 = strlen(nombresOrdenados[j + 1]);
			if (len1 > len2)
			{
				min = len2;
			}
			else {
				min = len1;
			}
			// Valor min de ambas palabras encontrado
			l = min;

			for (k = 0;k<l;++k)
				if (nombresOrdenados[j + 1][k]<nombresOrdenados[j][k]) {
					// movemos nombre de posicion
					strcpy(nombreTemp , nombresOrdenados[j]);
					strcpy(nombresOrdenados[j], nombresOrdenados[j + 1]);
					strcpy(nombresOrdenados[j + 1], nombreTemp);

					// movemos notas de posicion para mantenerlas con el nombre asociado

					strcpy(notaTemp, notas[j]);
					strcpy(notas[j], notas[j + 1]);
					strcpy(notas[j + 1], notaTemp);

					break;
				}
				else if (nombresOrdenados[j + 1][k]>nombresOrdenados[j][k]) break;
				if (k == l && strlen(nombresOrdenados[j]) > strlen(nombresOrdenados[j + 1]))
				{
					// movemos nombre de posicion
					strcpy(nombreTemp , nombresOrdenados[j]);
					strcpy(nombresOrdenados[j], nombresOrdenados[j + 1]);
					strcpy(nombresOrdenados[j + 1], nombreTemp);

					// movemos notas de posicion para mantenerlas con el nombre asociado

					strcpy(notaTemp ,notas[j]);
					strcpy(notas[j], notas[j + 1]);
					strcpy(notas[j + 1], notaTemp);

				}
		}
	}

}

/*  Fin de Funciones de Utilidad */

/* Funciones que realizan las tareas de cada opcion del menu */

void opcion1()
{
	if (CONTADOR_STU < STU_NUM)
	{ // Si no ha alcanzado el limite de estudiantes

		obtenerNombres();
		obtenerNotas();

		// Incrementamos el contador de estudiantes ya que se agrego uno nuevo
		CONTADOR_STU++;
	}
	else
	{ // Alcanzo el limite de estudiantes

		printf("\nATENCION!: YA NO SE PUEDE AGREGAR MAS ESTUDIANTES, LIMITE EXCEDIDO!\n");
	}
}

void opcion2()
{
	if (CONTADOR_STU > 0) // Si existe al menos un estudiante en la lista
	{
		char titulo[300] = "|||||||| LISTADO ORDENADO ASCENDENTE ||||||||||||\n\n";
		ordenarAlfabeticamenteAsc();
		mostrarInformacion(titulo,nombresOrdenados);
		escribirEnArchivo(titulo);
	}
	else
	{ // No existe ninguno
		printf( "\nATENCION!: LA LISTA ESTA VACIA\n");
	}

}
void opcion3()
{
	if (CONTADOR_STU > 0)// Si existe al menos un estudiante en la list
	{
		char titulo[300] = "|||||||||     LISTADO ORIGINAL      |||||||||||||\n\n";
		mostrarInformacion(titulo,nombres);
		escribirEnArchivo(titulo);
	}
	else
	{ //No existe ninguno
		printf("\nATENCION!: LA LISTA ESTA VACIA\n");
	}

}
/* Fin Funciones que realizan las tareas de cada opcion del menu */




int main()
{
	if (!abrirArchivo) 
	{
		/* Abrimos el archivo para leer */
		f = fopen("alumnos_report.txt", "w+");

		// Nos aseguramos que este abierto.
		if (f == NULL) {
			fprintf(stderr, "No se pudo abrir el archivo.\n");
			exit(EXIT_FAILURE);  // Cerramos el programa indicando fallo
		}
		else 
		{
			printf("-- Archivo alumnos_report.txt creado --\n");
			abrirArchivo = true;
		}
	}
	

	int opcion_seleccionada = 0;

	mostrarMenu();

	//leemos opcion ingresada
	scanf_s("%d",&opcion_seleccionada);

	switch (opcion_seleccionada)
	{
	case 1:
		// Obtenemos el nombre de los estudinates hasta que el usuario decida que ya no quiera ingresar uno nuevo
		// o se alcance el limite de estudiantes
		do {
			opcion1();
		} while (preguntarPorOtroEstudiante());

		main();

		break;
	case 2:
		opcion2();
		main();
		break;
	case 3:
		opcion3();
		main();
		break;
	case 4:
		// Cerramos el flujo de escritura para guardar informacion en archivo
		fclose(f);
		return 0;
	default:
	
		//Limpiamos el buffer para que no entre en bucle infinito
		fseek(stdin, 0, SEEK_END);

		main();
		break;

	}

	return 0;

}