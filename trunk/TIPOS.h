// Estructura generica
typedef struct arch_gen {
	int cod;			// Código 
	char flag;				// Condicion que indica si el registro fue dado de baja o no
}Archivo;

// Estructura de Libros
typedef struct libro {
	int cod;				// Código interno de la biblioteca (ISSN) que se le asignó al libro el ingresar al sistema.-
	char flag;				// Condicion que indica si el registro fue dado de baja o no
	char cod_tema[MAX];		// Código interno con el que la biblioteca distingue cada tema.-
	char titulo[100];		// Título completo del libro.-
	char cod_autor[MAX];	// Codigo de autor
	char ubicacion[10];		// Ubicacion dentro de la biblioteca
}Libros;

// Estructura de Temas
typedef struct tema {
	char cod[MAX];			// Código interno con el que la biblioteca distingue cada tema.-
	char flag;				// Condicion que indica si el registro fue dado de baja o no
}Temas;

// Estructura de Prestamos
typedef struct prestamo {
	int cod;				// Codigo del prestamo
	char flag;
	int cod_socio;			// Codigo del socio
	int cod_libro;			// Código interno de la biblioteca (ISSN) que se le asignó al libro el ingresar al sistema.-
}Prestamos;

// Estructura de Autores
typedef struct autor {
	char cod[MAX];			// Nombre del autor
	char flag;				// Condicion que indica si el registro fue dado de baja o no
}Autores;

// Estructura de Socios
typedef struct socio {
	int cod;				// Codigo del socio
	char flag;
	char nombreyapellido[100];	// Nombre y apellido del socio
	long dni;				// DNI del socio
	char direccion[100];	// Dirección del socio.
}Socios;


typedef struct indice{
	int cod;
	char flag;
	long pos;
}Index;
 
typedef struct indice_alfa{
	char cod[MAX];
	char flag;
	long pos;
}IndexS;

char nom_arch_Libros[128];
char nom_arch_Temas[128];
char nom_arch_Prestamos[128];
char nom_arch_Autores[128];
char nom_arch_Socios[128];