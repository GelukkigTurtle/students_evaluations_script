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
#include <iostream>
#include <algorithm>    // funcion min y swap
#include <iomanip>
#include <fstream>

using namespace std;

/* Variables Globales */

// Constantes
const int NUM_NOTAS = 3, STU_NUM = 10, STU_LENGTH = 30;

// Contador de estudiantes, lleva la cuenta de cuantos estudiantes se han ingresado al arreglo
int CONTADOR_STU = 0;

// Arreglos donde se guardan los datos de los estudiantes
char nombres[STU_NUM][STU_LENGTH];
char nombresOrdenados[STU_NUM][STU_LENGTH];
int	 notas[STU_NUM][NUM_NOTAS];

// Banderas 
bool abrirArchivo = false;

// Stream del archivo donde se escribe
ofstream escribir;

// Variables para imprimir tabla con buen formato
const char separator = ' ';
const int nameWidth = 17;
const int numberWidth = 7;
/*  Fin Variables Globales */

/* Funciones de Utilidad */

template<typename T> void printElement(T t, const int& width)
{
	cout << left << setw(width) << setfill(separator) << t;
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

void mostrarMenu()
{
	std::cout << endl;
	std::cout << "*************************************************\n";
	std::cout << "\tMENU DE OPCIONES\n";
	std::cout << "*************************************************\n";
	std::cout << "1) Capturar Datos\n";
	std::cout << "2) Ordenar de forma alfabetica (ASCENDENTE)\n";
	std::cout << "3) Mostrando contenido\n";
	std::cout << "4) Salir\n\n\n";
}

// Funcion para obtener cada nombre de la lista de estudiantes
void obtenerNombres()
{
	for (int i = CONTADOR_STU;i < CONTADOR_STU + 1;i++)
	{
		cout << "Ingresar nombre del  [" << CONTADOR_STU + 1 << "] estudiante : ";
		cin.getline(nombres[i], STU_LENGTH);
	}
}


// Funcion para obtener solo las notas de cada estudiante ingresado
void obtenerNotas()
{
	for (int i = CONTADOR_STU; i < CONTADOR_STU + 1; i++)
	{
		for (int j = 0; j < NUM_NOTAS; j++)
		{
			cout << "Ingresar la nota [" << (j + 1) << "] del estudiante " << nombres[i] << " :";
			cin >> notas[i][j];
		}
	}
}

// Funcion para preguntar si desea agregar otro estudiante a la lista actual
bool preguntarPorOtroEstudiante() {

	bool continua = false;

	std::cout << "\nEl total de estudiantes actual es: " << CONTADOR_STU << '\n';
	char respuesta[25];

	if (CONTADOR_STU < STU_NUM)
	{ // Si no ha alcanzado el limite de estudiantes

		std::cout << "\nDesea agregar otro estudiante?(y/n)\n";
		std::cin >> respuesta;
		cin.ignore();

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

// Funcion para escribir tablas de informacion en el archivo creado
void escribirEnArchivo(char titulo[300])
{
	escribir << endl;
	escribir << titulo;
	escribir << "# NOMBRES\t\t";
	escribir << "N1\t";
	escribir << "N2\t";
	escribir << "N3\t";
	escribir << endl;
	escribir << "------------------------------------------------------" << endl;

	for (int i = 0; i < CONTADOR_STU; i++)
	{
		escribir << i + 1;
		escribir << ") ";
		escribir << nombres[i] << "\t\t";
		for (int j = 0; j < NUM_NOTAS; j++)
		{
			escribir << notas[i][j] << "\t";
		}
		escribir << endl;
	}
	escribir << endl;
}

// Funcion para mostrar toda la informacion de los estudiantes ingresados
void mostrarInformacion(char titulo[300], char nombresParam[STU_NUM][STU_LENGTH])
{
	cout << endl;
	cout << titulo;
	printElement("#   NOMBRES", nameWidth + 3);
	printElement("N1", numberWidth);
	printElement("N2", numberWidth);
	printElement("N3", numberWidth);
	std::cout << endl;
	std::cout << "--------------------------------------------------" << endl;
	for (int i = 0; i < CONTADOR_STU; i++)
	{
		printElement(i + 1, 2);
		cout << ") ";
		printElement(aMayusculas(nombresParam[i]), nameWidth);

		for (int j = 0; j < NUM_NOTAS; j++)
		{
			printElement(notas[i][j], numberWidth);

		}
		std::cout << endl;
	}
	std::cout << endl;

}

//Funcion para ordenar el listado de estudiantes alfabeticamente Ascendente
void ordenarAlfabeticamenteAsc()
{

	// Realizamos un copia del arreglo original al que sera ordenado
	for (int z = 0; z < CONTADOR_STU; z++) {
		strcpy_s(nombresOrdenados[z], nombres[z]);
	}

	int n = CONTADOR_STU, k, l;

	// Se emplea metodo de la burbuja para ordenar el arreglo de nombres de estudiantes
	for (int i = 0;i<n - 1;i++) {
		for (int j = 0; j<n - i - 1; j++) {
			l = min(strlen(nombresOrdenados[j]), strlen(nombresOrdenados[j + 1]));
			for (k = 0;k<l;++k)
				if (nombresOrdenados[j + 1][k]<nombresOrdenados[j][k]) {
					swap(nombresOrdenados[j], nombresOrdenados[j + 1]); // movemos nombre de posicion
					swap(notas[j], notas[j + 1]);             // movemos notas de posicion para mantenerlas con el nombre asociado
					break;
				}
				else if (nombresOrdenados[j + 1][k]>nombresOrdenados[j][k]) break;
				if (k == l && strlen(nombresOrdenados[j]) > strlen(nombresOrdenados[j + 1]))
				{
					swap(nombresOrdenados[j], nombresOrdenados[j + 1]); // movemos nombre de posicion
					swap(notas[j], notas[j + 1]);             // movemos notas de posicion para mantenerlas con el nombre asociado
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

		std::cout << endl << "ATENCION!: YA NO SE PUEDE AGREGAR MAS ESTUDIANTES, LIMITE EXCEDIDO!" << endl;
	}
}

void opcion2()
{
	if (CONTADOR_STU > 0) // Si existe al menos un estudiante en la lista
	{
		char titulo[300] = "|||||||| LISTADO ORDENADO ASCENDENTE ||||||||||||\n\n";
		ordenarAlfabeticamenteAsc();
		mostrarInformacion(titulo, nombresOrdenados);
		escribirEnArchivo(titulo);
	}
	else
	{ // No existe ninguno
		cout << endl << "ATENCION!: LA LISTA ESTA VACIA" << endl;
	}

}
void opcion3()
{
	if (CONTADOR_STU > 0)// Si existe al menos un estudiante en la list
	{
		char titulo[300] = "|||||||||     LISTADO ORIGINAL      |||||||||||||\n\n";
		mostrarInformacion(titulo, nombres);
		escribirEnArchivo(titulo);
	}
	else
	{ //No existe ninguno
		cout << endl << "ATENCION!: LA LISTA ESTA VACIA" << endl;
	}

}
/* Fin Funciones que realizan las tareas de cada opcion del menu */


// Funcion principal a ejecutar
int main()
{
	// Se crea un archivo donde se escribiran las tablas de informacion mostradas
	if (!abrirArchivo) // Si no se ha abierto el archivo
	{
		escribir.open("alumnos_report.txt", ios::out | ios::app);
		if (!escribir.fail()) {
			abrirArchivo = true;
			cout << "-- Archivo alumnos_report.txt creado --" << endl << endl;
		}

	}

	int opcion_seleccionada;

	mostrarMenu();

	//leemos opcion ingresada
	std::cin >> opcion_seleccionada;
	std::cin.ignore(); // limpiamos buffer, para que no afecte futuros ingresos de informacion

	switch (opcion_seleccionada)
	{
	case 1:
		//Obtenemos el nombre de los estudinates hasta que el usuario decida que ya no quiera ingresar uno nuevo
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
		escribir.close();
		return 0;
	default:
		//Limpiamos el buffer para que no entre en bucle infinito
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		main();
		break;

	}

}