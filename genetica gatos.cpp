#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//===========================================================
// ESTRUCTURA FECHA
// Almacena el mes y año de nacimiento o fallecimiento
//===========================================================
struct Fecha {
    int mes;
    int anio;
};

//===========================================================
// ESTRUCTURA PADRES
// Guarda la información de los progenitores del gato
//===========================================================
struct Padres {
    int padre;      // ID del padre
    int madre;      // ID de la madre
    string familia; // Nombre de la familia
};

//===========================================================
// ESTRUCTURA GENERAL
// Contiene los datos generales del gato
//===========================================================
struct General {
    string nombre;
    int edad;
    char sexo;
    Fecha fecha_nacimiento;
    Fecha fecha_fallecimiento;
};

//===========================================================
// ESTRUCTURA FENOTIPO
// Representa las características observables del gato
//===========================================================
struct Fenotipo {
    char tipo_sangre[2];
    string tipo_pelaje;
    string tipo_color;
};

//===========================================================
// ESTRUCTURA GENES
// Almacena los alelos que posee el gato
//===========================================================
struct Genes {
    char grupo_sangre[2];
    char gen_pelaje[2];
    char gen_color[2];
};

//===========================================================
// ESTRUCTURA MIEMBRO
// Reúne toda la información de un gato
//===========================================================
struct Miembro {
    int id_miembro;
    Padres padres;
    General general;
    Fenotipo fenotipo;
    Genes genes;
};

//===========================================================
// ESTRUCTURA DEL ÁRBOL BINARIO
//
// Padre -> hijo izquierdo
// Madre -> hijo derecho
//
// Cada nodo representa un gato dentro del árbol genealógico
//===========================================================
struct NodoGato {
    Miembro dato;
    NodoGato* padre_izq;
    NodoGato* madre_der;
};

//===========================================================
// FUNCIÓN: heredarAlelo
//
// Recibe dos alelos y devuelve uno aleatoriamente.
// Simula la herencia genética de uno de los genes del padre
// o de la madre.
//===========================================================
char heredarAlelo(char alelo1, char alelo2) {
    if (rand() % 2 == 0)
        return alelo1;

    return alelo2;
}

//===========================================================
// FUNCIÓN: ordenarAlelos
//
// Coloca primero el alelo dominante (mayúscula)
// para facilitar la interpretación genética.
//===========================================================
void ordenarAlelos(char alelos[2]) {

    if (alelos[0] >= 'a' && alelos[0] <= 'z' &&
        alelos[1] >= 'A' && alelos[1] <= 'Z') {

        char temp = alelos[0];
        alelos[0] = alelos[1];
        alelos[1] = temp;
    }
}

//===========================================================
// FUNCIÓN: determinarFenotipo
//
// Convierte los genes (genotipo) en características visibles
// (fenotipo).
//
// Reglas:
//
// Sangre:
// A domina sobre B
//
// Pelaje:
// C = Corto (dominante)
// c = Largo (recesivo)
//
// Color:
// N = Negro (dominante)
// n = Naranja (recesivo)
//===========================================================
Fenotipo determinarFenotipo(Genes g) {

    Fenotipo f;

    //-------------------------------
    // Determinar tipo de sangre
    //-------------------------------
    if (g.grupo_sangre[0] == 'A') {
        f.tipo_sangre[0] = 'A';
        f.tipo_sangre[1] = '\0';
    }
    else if (g.grupo_sangre[0] == 'B') {
        f.tipo_sangre[0] = 'B';
        f.tipo_sangre[1] = '\0';
    }

    //-------------------------------
    // Determinar tipo de pelaje
    //-------------------------------
    if (g.gen_pelaje[0] == 'C')
        f.tipo_pelaje = "Corto";
    else
        f.tipo_pelaje = "Largo";

    //-------------------------------
    // Determinar color
    //-------------------------------
    if (g.gen_color[0] == 'N')
        f.tipo_color = "Negro";
    else
        f.tipo_color = "Naranja";

    return f;
}

//===========================================================
// FUNCIÓN: cruzarGatos
//
// Genera una nueva cría utilizando los genes del padre y
// la madre.
//
// Pasos:
// 1. Crear la cría.
// 2. Registrar a los padres.
// 3. Heredar alelos.
// 4. Calcular el fenotipo.
// 5. Conectar la cría al árbol genealógico.
//===========================================================
NodoGato* cruzarGatos(
    NodoGato* nodoPadre,
    NodoGato* nodoMadre,
    int nuevoId,
    string nombreCria,
    char sexoCria) {

    // Reservar memoria para la nueva cría
    NodoGato* cria = new NodoGato;

    //-------------------------------
    // Datos básicos
    //-------------------------------
    cria->dato.id_miembro = nuevoId;

    //-------------------------------
    // Registrar progenitores
    //-------------------------------
    cria->dato.padres.padre =
        nodoPadre->dato.id_miembro;

    cria->dato.padres.madre =
        nodoMadre->dato.id_miembro;

    //-------------------------------
    // Heredar familia
    //-------------------------------
    cria->dato.padres.familia =
        nodoPadre->dato.padres.familia;

    //-------------------------------
    // Datos generales
    //-------------------------------
    cria->dato.general.nombre = nombreCria;
    cria->dato.general.edad = 0;
    cria->dato.general.sexo = sexoCria;

    cria->dato.general.fecha_nacimiento.mes = 6;
    cria->dato.general.fecha_nacimiento.anio = 2026;

    //-------------------------------
    // HERENCIA DEL GRUPO SANGUÍNEO
    //-------------------------------
    cria->dato.genes.grupo_sangre[0] =
        heredarAlelo(
            nodoPadre->dato.genes.grupo_sangre[0],
            nodoPadre->dato.genes.grupo_sangre[1]);

    cria->dato.genes.grupo_sangre[1] =
        heredarAlelo(
            nodoMadre->dato.genes.grupo_sangre[0],
            nodoMadre->dato.genes.grupo_sangre[1]);

    ordenarAlelos(
        cria->dato.genes.grupo_sangre);

    //-------------------------------
    // HERENCIA DEL PELAJE
    //-------------------------------
    cria->dato.genes.gen_pelaje[0] =
        heredarAlelo(
            nodoPadre->dato.genes.gen_pelaje[0],
            nodoPadre->dato.genes.gen_pelaje[1]);

    cria->dato.genes.gen_pelaje[1] =
        heredarAlelo(
            nodoMadre->dato.genes.gen_pelaje[0],
            nodoMadre->dato.genes.gen_pelaje[1]);

    ordenarAlelos(
        cria->dato.genes.gen_pelaje);

    //-------------------------------
    // HERENCIA DEL COLOR
    //-------------------------------
    cria->dato.genes.gen_color[0] =
        heredarAlelo(
            nodoPadre->dato.genes.gen_color[0],
            nodoPadre->dato.genes.gen_color[1]);

    cria->dato.genes.gen_color[1] =
        heredarAlelo(
            nodoMadre->dato.genes.gen_color[0],
            nodoMadre->dato.genes.gen_color[1]);

    ordenarAlelos(
        cria->dato.genes.gen_color);

    //-------------------------------
    // Calcular características visibles
    //-------------------------------
    cria->dato.fenotipo =
        determinarFenotipo(cria->dato.genes);

    //-------------------------------
    // Conectar con los padres
    //-------------------------------
    cria->padre_izq = nodoPadre;
    cria->madre_der = nodoMadre;

    return cria;
}

//===========================================================
// FUNCIÓN: imprimirGato
//
// Muestra en pantalla toda la información de un gato.
//===========================================================
void imprimirGato(NodoGato* n) {

    if (!n)
        return;

    cout << "---------------------------------------" << endl;

    cout << "ID: "
         << n->dato.id_miembro
         << " | Nombre: "
         << n->dato.general.nombre
         << " | Sexo: "
         << n->dato.general.sexo
         << endl;

    cout << "Padre ID: "
         << n->dato.padres.padre
         << " | Madre ID: "
         << n->dato.padres.madre
         << endl;

    cout << "[GENES] "
         << "Sangre: "
         << n->dato.genes.grupo_sangre[0]
         << n->dato.genes.grupo_sangre[1]
         << " | Pelaje: "
         << n->dato.genes.gen_pelaje[0]
         << n->dato.genes.gen_pelaje[1]
         << " | Color: "
         << n->dato.genes.gen_color[0]
         << n->dato.genes.gen_color[1]
         << endl;

    cout << "[FENOTIPO] "
         << "Sangre: "
         << n->dato.fenotipo.tipo_sangre
         << " | Pelaje: "
         << n->dato.fenotipo.tipo_pelaje
         << " | Color: "
         << n->dato.fenotipo.tipo_color
         << endl;
}


//===========================================================
// FUNCIÓN: mostrarGenealogia
//
// Muestra en pantalla el arbol de la genealogia
//===========================================================


void mostrarGenealogia(NodoGato* nodo, string prefijo = "") {

    if (nodo == NULL)
        return;

    cout << prefijo
         << nodo->dato.general.nombre
         << " (ID:" << nodo->dato.id_miembro << ")"
         << endl;

    if (nodo->padre_izq != NULL)
        mostrarGenealogia(nodo->padre_izq,
                          prefijo + "+- Padre: ");

    if (nodo->madre_der != NULL)
        mostrarGenealogia(nodo->madre_der,
                          prefijo + "+- Madre: ");
}
int main() {

    // Inicializa la semilla para generar números aleatorios.
    // Esto permite que la herencia genética varíe en cada ejecución.
    srand(time(NULL));

    //=======================================================
    // CREACIÓN DEL MACHO FUNDADOR
    //=======================================================

    // Reservar memoria para el gato macho
    NodoGato* macho = new NodoGato;

    // Asignar identificador único
    macho->dato.id_miembro = 1;

    // No tiene padres registrados porque es fundador
    macho->dato.padres.padre = 0;
    macho->dato.padres.madre = 0;

    // Nombre de la familia
    macho->dato.padres.familia = "Michis";

    // Datos generales
    macho->dato.general.nombre = "Leonidas";
    macho->dato.general.sexo = 'M';

    // Genes del macho
    // Sangre AB
    macho->dato.genes.grupo_sangre[0] = 'A';
    macho->dato.genes.grupo_sangre[1] = 'B';

    // Pelaje corto heterocigoto
    macho->dato.genes.gen_pelaje[0] = 'C';
    macho->dato.genes.gen_pelaje[1] = 'c';

    // Color naranja homocigoto recesivo
    macho->dato.genes.gen_color[0] = 'n';
    macho->dato.genes.gen_color[1] = 'n';

    // Calcular fenotipo a partir de los genes
    macho->dato.fenotipo =
        determinarFenotipo(macho->dato.genes);

    // No tiene padres dentro del árbol
    macho->padre_izq = NULL;
    macho->madre_der = NULL;

    //=======================================================
    // CREACIÓN DE LA HEMBRA FUNDADORA
    //=======================================================

    NodoGato* hembra = new NodoGato;

    hembra->dato.id_miembro = 2;

    // Sin padres registrados
    hembra->dato.padres.padre = 0;
    hembra->dato.padres.madre = 0;

    hembra->dato.padres.familia = "Michis";

    // Datos generales
    hembra->dato.general.nombre = "Cleopatra";
    hembra->dato.general.sexo = 'F';

    // Genes de la hembra

    // Sangre BB
    hembra->dato.genes.grupo_sangre[0] = 'B';
    hembra->dato.genes.grupo_sangre[1] = 'B';

    // Pelaje largo homocigoto recesivo
    hembra->dato.genes.gen_pelaje[0] = 'c';
    hembra->dato.genes.gen_pelaje[1] = 'c';

    // Color negro heterocigoto
    hembra->dato.genes.gen_color[0] = 'N';
    hembra->dato.genes.gen_color[1] = 'n';

    // Obtener fenotipo
    hembra->dato.fenotipo =
        determinarFenotipo(hembra->dato.genes);

    // No tiene padres dentro del árbol
    hembra->padre_izq = NULL;
    hembra->madre_der = NULL;

    //=======================================================
    // GENERACIÓN DE DESCENDIENTES (F1)
    //=======================================================

    // Cruce entre Leonidas y Cleopatra
    // Se genera una cría macho llamada Garfield
    NodoGato* cria1 =
        cruzarGatos(
            macho,
            hembra,
            3,
            "Garfield",
            'M');

    // Segunda cría del mismo cruce
    NodoGato* cria2 =
        cruzarGatos(
            macho,
            hembra,
            4,
            "Luna",
            'F');

    //=======================================================
    // MOSTRAR RESULTADOS
    //=======================================================

    cout << "=== ANCESTROS ORIGINALES ==="
         << endl;

    // Mostrar información del padre
    imprimirGato(macho);

    // Mostrar información de la madre
    imprimirGato(hembra);

    cout << "\n=== PRIMERA GENERACION (F1) ==="
         << endl;

    // Mostrar información de la primera cría
    imprimirGato(cria1);

    // Mostrar información de la segunda cría
    imprimirGato(cria2);

	// Mostrar el arbol
		cout << "\n\n=== ARBOL GENEALOGICO ===\n";
	mostrarGenealogia(cria1);
    //=======================================================
    // LIBERACIÓN DE MEMORIA
    //=======================================================
    // Eliminar los nodos creados dinámicamente para evitar
    // fugas de memoria.

    delete macho;
    delete hembra;
    delete cria1;
    delete cria2;

    // Finalizar programa correctamente
    return 0;
}
