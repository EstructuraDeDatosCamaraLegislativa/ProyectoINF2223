#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructura para almacenar los votos de los parlamentarios en un proyecto de ley */
struct VotacionParlamentarios {
    int parlamentarioID;                /* ID único del parlamentario */
    int voto;                           /* 1: A favor, 0: En Contra, -1: Abstención */
    struct VotacionParlamentarios *siguiente; /* Puntero al siguiente voto en la lista */
};

/* Estructura que representa un proyecto de ley */
struct ProyectoLey {
    int ID;                             /* ID único del proyecto de ley */
    char titulo[100];                   /* Título del proyecto de ley */
    char descripcion[500];              /* Breve descripción del proyecto */
    char actor[100];                    /* Actor que presenta la iniciativa */
    char estado[100];                   /* Estado: Tramitacion - Promulgacion - Publicado */
    int numFirmas;                      /* Número de firmas requeridas (si es iniciativa popular) */
    int urgencia;                       /* Nivel de urgencia (1: baja, 2: media, 3: alta) */
    char fechaIngreso[11];              /* Fecha de ingreso del proyecto (DD-MM-YYYY) */
    struct VotacionParlamentarios *votacion; /* Lista de votos de los parlamentarios en este proyecto */
};

/* Nodo del árbol binario de búsqueda de proyectos de ley */
struct NodoArbol {
    struct NodoArbol *izq;              /* Puntero al hijo izquierdo */
    struct NodoArbol *der;              /* Puntero al hijo derecho */
    struct ProyectoLey *proyecto;       /* Puntero al proyecto de ley */
};

/* Estructura principal que representa el proceso legislativo */
struct ProcesoLegislativo {
    struct NodoArbol *Proyectos;        /* Árbol binario de proyectos de ley */
};

/* Función para crear un nuevo proyecto de ley */
struct ProyectoLey *crearProyectoLey(int ID, const char *titulo, const char *descripcion, const char *actor, const char *estado, int numFirmas, int urgencia, const char *fechaIngreso) {
    struct ProyectoLey *nuevoProyecto = (struct ProyectoLey *)malloc(sizeof(struct ProyectoLey));
    if (!nuevoProyecto) return NULL;
    nuevoProyecto->ID = ID;
    strcpy(nuevoProyecto->titulo, titulo);
    strcpy(nuevoProyecto->descripcion, descripcion);
    strcpy(nuevoProyecto->actor, actor);
    strcpy(nuevoProyecto->estado, estado);
    nuevoProyecto->numFirmas = numFirmas;
    nuevoProyecto->urgencia = urgencia;
    strcpy(nuevoProyecto->fechaIngreso, fechaIngreso);
    nuevoProyecto->votacion = NULL;
    return nuevoProyecto;
}

/* Función para crear un nuevo nodo del árbol con un proyecto de ley */
struct NodoArbol *crearNodoArbol(struct ProyectoLey *proyecto) {
    struct NodoArbol *nuevoNodo = (struct NodoArbol *)malloc(sizeof(struct NodoArbol));
    if (!nuevoNodo) return NULL;
    nuevoNodo->proyecto = proyecto;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

/* Función para insertar un proyecto de ley en el árbol binario de búsqueda */
struct NodoArbol *insertarProyecto(struct NodoArbol *raiz, struct ProyectoLey *proyecto) {
    if (raiz == NULL) {
        return crearNodoArbol(proyecto);
    } if (proyecto->ID < raiz->proyecto->ID) {
        raiz->izq = insertarProyecto(raiz->izq, proyecto);
        return raiz;
    } if (proyecto->ID > raiz->proyecto->ID) {
        raiz->der = insertarProyecto(raiz->der, proyecto);
        return raiz;
    }

    // Caso en el que el ID ya existe
    printf("Proyecto con ID %d ya existe.\n", proyecto->ID);
    return raiz;
}

/* Función para agregar un proyecto de ley al árbol en ProcesoLegislativo */
void agregarProyecto(struct ProcesoLegislativo *proceso) {
    int ID, numFirmas, urgencia;
    char titulo[100], descripcion[500], actor[100], estado[100], fechaIngreso[11];

    /* Se ingresan los datos para el proyecto de ley y sus respectivos subcomponentes. */
    printf("Ingrese el ID del proyecto de ley: ");
    scanf("%d", &ID);
    getchar(); // Limpiar el salto de línea residual
    printf("Ingrese el título del proyecto de ley: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = 0;
    printf("Ingrese la descripción del proyecto de ley: ");
    fgets(descripcion, sizeof(descripcion), stdin);
    descripcion[strcspn(descripcion, "\n")] = 0;
    printf("Ingrese el actor (quien presenta la iniciativa): ");
    fgets(actor, sizeof(actor), stdin);
    actor[strcspn(actor, "\n")] = 0;
    printf("Ingrese el estado del proyecto (Tramitacion, Promulgacion, Publicado): ");
    fgets(estado, sizeof(estado), stdin);
    estado[strcspn(estado, "\n")] = 0;
    printf("Ingrese el número de firmas requeridas: ");
    scanf("%d", &numFirmas);
    printf("Ingrese el nivel de urgencia (1: baja, 2: media, 3: alta): ");
    scanf("%d", &urgencia);
    getchar();
    printf("Ingrese la fecha de ingreso (DD-MM-YYYY): ");
    fgets(fechaIngreso, sizeof(fechaIngreso), stdin);
    fechaIngreso[strcspn(fechaIngreso, "\n")] = 0;

    struct ProyectoLey *proyecto = crearProyectoLey(ID, titulo, descripcion, actor, estado, numFirmas, urgencia, fechaIngreso);
    if (proyecto != NULL) {
        proceso->Proyectos = insertarProyecto(proceso->Proyectos, proyecto);
        printf("Proyecto de ley agregado exitosamente.\n");
    } else {
        printf("Error al crear el proyecto de ley.\n");
    }
}

/* Función para recorrer el árbol en orden (INORDEN) */
void recorrerArbol(struct NodoArbol* nodo) {
    if (nodo != NULL) {
        recorrerArbol(nodo->izq);
        printf("ID: %d\n", nodo->proyecto->ID);
        printf("Título: %s\n", nodo->proyecto->titulo);
        printf("Estado: %s\n", nodo->proyecto->estado);
        printf("actor: %s\n", nodo->proyecto->actor);
        printf("Urgencia: %d\n", nodo->proyecto->urgencia);
        printf("Fecha de ingreso: %s\n", nodo->proyecto->fechaIngreso);
        printf("-----------------------------------\n");
        recorrerArbol(nodo->der);
    }
}

struct NodoArbol* encontrarMinimo(struct NodoArbol* nodo) {
    struct NodoArbol* actual = nodo;
    while (actual && actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}

struct NodoArbol* eliminarNodoProyecto(struct NodoArbol* raiz, int ID) {
    if (raiz == NULL) {
        return raiz;
    }
    if (ID < raiz->proyecto->ID) {
        raiz->izq = eliminarNodoProyecto(raiz->izq, ID);
        return raiz;
    } if (ID > raiz->proyecto->ID) {
        raiz->der = eliminarNodoProyecto(raiz->der, ID);
        return raiz;
    }
    // Caso cuando encontramos el nodo a eliminar
    if (raiz->izq == NULL) {
        struct NodoArbol* temp = raiz->der;
        return temp;
    } if (raiz->der == NULL) {
        struct NodoArbol* temp = raiz->izq;
        return temp;
    }

    // Nodo con dos hijos: buscar el sucesor en orden (mínimo en el subárbol derecho)
    struct NodoArbol* temp = encontrarMinimo(raiz->der);
    raiz->proyecto = temp->proyecto;
    raiz->der = eliminarNodoProyecto(raiz->der, temp->proyecto->ID);

    return raiz;
}


void eliminarProyecto(struct ProcesoLegislativo *proceso) {
    int ID;
    printf("Ingrese el ID del proyecto a eliminar: ");
    scanf("%d", &ID);
    proceso->Proyectos = eliminarNodoProyecto(proceso->Proyectos, ID);
    printf("Proyecto eliminado exitosamente.\n");
}

struct ProyectoLey* buscarProyectoPorID(struct NodoArbol* nodo, int ID) {
    if (nodo == NULL) {
        return NULL;
    } if (nodo->proyecto->ID == ID) {
        return nodo->proyecto;
    } if (ID < nodo->proyecto->ID) {
        return buscarProyectoPorID(nodo->izq, ID);
    }
    return buscarProyectoPorID(nodo->der, ID);
}

void buscarProyecto(struct ProcesoLegislativo *proceso) {
    int ID;
    printf("Ingrese el ID del proyecto a buscar: ");
    scanf("%d", &ID);
    struct ProyectoLey* proyecto = buscarProyectoPorID(proceso->Proyectos, ID);
    if (proyecto != NULL) {
        printf("Proyecto encontrado:\n");
        printf("Título: %s\n", proyecto->titulo);
        printf("Descripción: %s\n", proyecto->descripcion);
        printf("actor: %s\n", proyecto->actor);
        printf("Estado: %s\n", proyecto->estado);
        printf("Urgencia: %d\n", proyecto->urgencia);
        printf("Fecha de ingreso: %s\n", proyecto->fechaIngreso);
    } else {
        printf("Proyecto no encontrado.\n");
    }
}

void modificarProyecto(struct ProcesoLegislativo *proceso) {
    int ID;
    printf("Ingrese el ID del proyecto a modificar: ");
    scanf("%d", &ID);
    struct ProyectoLey* proyecto = buscarProyectoPorID(proceso->Proyectos, ID);
    if (proyecto != NULL) {
        printf("Proyecto encontrado. Ingrese los nuevos datos:\n");

        printf("Ingrese el nuevo título del proyecto: ");
        getchar();
        fgets(proyecto->titulo, sizeof(proyecto->titulo), stdin);
        proyecto->titulo[strcspn(proyecto->titulo, "\n")] = '\0';

        printf("Ingrese la nueva descripción del proyecto: ");
        fgets(proyecto->descripcion, sizeof(proyecto->descripcion), stdin);
        proyecto->descripcion[strcspn(proyecto->descripcion, "\n")] = '\0';

        printf("Ingrese el nuevo actor que presenta la iniciativa: ");
        fgets(proyecto->actor, sizeof(proyecto->actor), stdin);
        proyecto->actor[strcspn(proyecto->actor, "\n")] = '\0';

        printf("Ingrese el nuevo estado del proyecto: ");
        fgets(proyecto->estado, sizeof(proyecto->estado), stdin);
        proyecto->estado[strcspn(proyecto->estado, "\n")] = '\0';

        printf("Ingrese el nuevo número de firmas requeridas: ");
        scanf("%d", &proyecto->numFirmas);

        printf("Ingrese el nuevo nivel de urgencia (1: baja, 2: media, 3: alta): ");
        scanf("%d", &proyecto->urgencia);

        printf("Proyecto modificado exitosamente.\n");
    } else {
        printf("Proyecto no encontrado.\n");
    }
}

void listarProyectos(struct ProcesoLegislativo *proceso) {
    printf("Listado de proyectos:\n");
    recorrerArbol(proceso->Proyectos);
}

void menu() {
    printf("\nSistema de Proceso Legislativo de Chile\n");
    printf("1. Agregar Proyecto de Ley\n");
    printf("2. Eliminar Proyecto de Ley\n");
    printf("3. Buscar Proyecto de Ley\n");
    printf("4. Modificar Proyecto de Ley\n");
    printf("5. Listar todos los Proyectos de Ley\n");
    printf("6. Salir\n");
    printf("Seleccione una opción: ");
}

void procesarOpcion(int opcion, struct ProcesoLegislativo *proceso) {
    if (opcion == 1) {
        agregarProyecto(proceso);
    } if (opcion == 2) {
        eliminarProyecto(proceso);
    } if (opcion == 3) {
        buscarProyecto(proceso);
    } if (opcion == 4) {
        modificarProyecto(proceso);
    } if (opcion == 5) {
        listarProyectos(proceso);
    } if (opcion == 6) {
        printf("Saliendo del sistema...\n");
    } if (opcion < 1 || opcion > 6) {
        printf("Opción no válida. Intente nuevamente.\n");
    }
}

void iniciarSistema(struct ProcesoLegislativo *PL) {
    int opcion;
    do {
        menu();
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer de entrada
        procesarOpcion(opcion, PL);
    } while (opcion != 6);
}

int main() {
    struct ProcesoLegislativo *PL = (struct ProcesoLegislativo *)malloc(sizeof(struct ProcesoLegislativo));
    if (PL == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    /* Inicialización de los miembros de ProcesoLegislativo */
    PL->Proyectos = NULL;

    iniciarSistema(PL);
    return 0;
}
