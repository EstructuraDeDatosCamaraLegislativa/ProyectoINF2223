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
    int ID;
    char titulo[100];
    char descripcion[500];
    char actor[100];
    char estado[100];
    int numFirmas;
    int urgencia;
    char fechaIngreso[11];
    struct VotacionParlamentarios *votacionDiputados;
    struct VotacionParlamentarios *votacionSenado;
    struct VotacionParlamentarios *votacion;  /*Lista de votos de los parlamentarios en este proyecto */
};

/* Nodo del árbol binario de búsqueda de proyectos de ley */
struct NodoArbol {
    struct NodoArbol *izq;
    struct NodoArbol *der;
    struct ProyectoLey *proyecto;
};

/* Estructura para representar una cámara legislativa (Diputados o Senado) */
struct CamaraLegislativa {
    struct ProyectoLey *proyectoActual;         /* Proyecto actualmente en discusión */
};

/* Estructura para una comisión mixta que discute un proyecto de ley */
struct ComisionMixta {
    struct ProyectoLey *proyecto;             /* Proyecto en discusión en la comisión */
    struct VotacionParlamentarios *votacion;  /* Resultado de votación en la comisión */
};


/* Estructura principal que representa el proceso legislativo */
struct ProcesoLegislativo {
    struct NodoArbol *Proyectos;        /* Árbol binario de proyectos de ley */
    struct CamaraLegislativa *camaras[2]; /* Array de 2 cámaras: [0] para Diputados, [1] para Senado */
    struct ComisionMixta *comisiones;   /* Lista de comisiones mixtas */
};


/* Función para crear un nuevo proyecto de ley */
struct ProyectoLey *crearProyectoLey(int ID, char *titulo, char *descripcion, char *actor, char *estado, int numFirmas, int urgencia, char *fechaIngreso) {
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
    nuevoProyecto->votacionDiputados = NULL;
    nuevoProyecto->votacionSenado = NULL;
    nuevoProyecto->votacion = NULL;  // Comisión Mixta
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
    }
    if (proyecto->ID < raiz->proyecto->ID) {
        raiz->izq = insertarProyecto(raiz->izq, proyecto);
    } else if (proyecto->ID > raiz->proyecto->ID) {
        raiz->der = insertarProyecto(raiz->der, proyecto);
    } else {
        printf("Proyecto con ID %d ya existe.\n", proyecto->ID);
    }
    return raiz;
}

/* Función para agregar un proyecto al árbol y asignarlo a las cámaras */
void agregarProyecto(struct ProcesoLegislativo *proceso) {
    int ID, numFirmas, urgencia;
    char titulo[100], descripcion[500], actor[100], estado[100], fechaIngreso[11];
    struct ProyectoLey *proyecto;

    printf("Ingrese el ID del proyecto de ley: ");
    scanf("%d", &ID);
    fflush(stdin);

    printf("Ingrese el título del proyecto de ley: ");
    scanf(" %[^\n]", titulo);
    
    printf("Ingrese la descripción del proyecto de ley: ");
    scanf(" %[^\n]", descripcion);
    
    printf("Ingrese el actor (quien presenta la iniciativa): ");
    scanf(" %[^\n]", actor);
    
    printf("Ingrese el estado del proyecto (Tramitacion, Promulgacion, Publicado): ");
    scanf(" %[^\n]", estado);

    printf("Ingrese el número de firmas requeridas: ");
    scanf("%d", &numFirmas);

    printf("Ingrese el nivel de urgencia (1: baja, 2: media, 3: alta): ");
    scanf("%d", &urgencia);
    fflush(stdin);

    printf("Ingrese la fecha de ingreso (DD-MM-YYYY): ");
    scanf(" %[^\n]", fechaIngreso);

    proyecto = crearProyectoLey(ID, titulo, descripcion, actor, estado, numFirmas, urgencia, fechaIngreso);

    if (proyecto != NULL) {
        proceso->Proyectos = insertarProyecto(proceso->Proyectos, proyecto);
        printf("Proyecto de ley agregado al árbol.\n");

        // Asignar el proyecto como proyectoActual en ambas cámaras
        proceso->camaras[0]->proyectoActual = proyecto;
        proceso->camaras[1]->proyectoActual = proyecto;
    } else {
        printf("Error al crear el proyecto de ley.\n");
    }
}


/* Función para agregar un voto a la lista de votaciones */
void agregarVoto(struct VotacionParlamentarios **votacion, int parlamentarioID, int voto) {
    struct VotacionParlamentarios *nuevoVoto = (struct VotacionParlamentarios *)malloc(sizeof(struct VotacionParlamentarios));
    if (!nuevoVoto) return;
    nuevoVoto->parlamentarioID = parlamentarioID;
    nuevoVoto->voto = voto;
    nuevoVoto->siguiente = *votacion;
    *votacion = nuevoVoto;
}

/* Función para ingresar votos de los parlamentarios manualmente */
void ingresarVotos(struct VotacionParlamentarios **votacionLista) {
    int numParlamentarios, id, voto;
    int i;

    printf("Ingrese el número de parlamentarios en la votación: ");
    scanf("%d", &numParlamentarios);
    fflush(stdin);

    for (i = 0; i < numParlamentarios; i++) {
        printf("Ingrese el ID del parlamentario %d: ", i + 1);
        scanf("%d", &id);
        fflush(stdin);

        do {
            printf("Ingrese el voto del parlamentario %d (1: A favor, 0: En Contra, -1: Abstención): ", i + 1);
            scanf("%d", &voto);
            fflush(stdin);
        } while (voto != 1 && voto != 0 && voto != -1);

        agregarVoto(votacionLista, id, voto);
    }
}

/* Función para calcular el resultado de la votación en una lista de votaciones */
char* resultadoVotacion(struct VotacionParlamentarios *votacion) {
    int aFavor = 0, enContra = 0, abstenciones = 0;
    struct VotacionParlamentarios *actual = votacion;

    while (actual != NULL) {
        if (actual->voto == 1) {
            aFavor++;
        } else if (actual->voto == 0) {
            enContra++;
        } else {
            abstenciones++;
        }
        actual = actual->siguiente;
    }

    if (aFavor > enContra) {
        return "Aprobado";
    } else if (enContra > aFavor) {
        return "Rechazado";
    } else {
        return "Desacuerdo";
    }
}

/* Función para seleccionar la cámara de origen y asignar la revisión */
struct CamaraLegislativa* seleccionarCamaraOrigen(struct ProcesoLegislativo *proceso, struct CamaraLegislativa **camaraRevision, char **nombreCamaraOrigen, char **nombreCamaraRevision) {
    int tipoOrigen;
    printf("Seleccione la cámara de origen:\n");
    printf("1. Diputados\n");
    printf("2. Senado\n");
    printf("Ingrese su elección: ");
    scanf("%d", &tipoOrigen);

    // Asignar cámaras de origen y revisión según la selección
    if (tipoOrigen == 1) {
        *camaraRevision = proceso->camaras[1]; // Cámara de Senado como revisión
        *nombreCamaraOrigen = "Diputados";    // Nombre de la cámara de origen
        *nombreCamaraRevision = "Senado";     // Nombre de la cámara de revisión
        return proceso->camaras[0];           // Cámara de Diputados como origen
    } else if (tipoOrigen == 2) {
        *camaraRevision = proceso->camaras[0]; // Cámara de Diputados como revisión
        *nombreCamaraOrigen = "Senado";       // Nombre de la cámara de origen
        *nombreCamaraRevision = "Diputados";  // Nombre de la cámara de revisión
        return proceso->camaras[1];           // Cámara de Senado como origen
    } else {
        printf("Selección inválida.\n");
        return NULL;
    }
}

/* Función para realizar la votación en una cámara y almacenar el resultado */
void realizarVotacionCamara(struct CamaraLegislativa *camara, char *resultado, int esDiputados) {
    // Realizar la votación en la cámara correspondiente
    if (esDiputados) {
        ingresarVotos(&(camara->proyectoActual->votacionDiputados));
        strcpy(resultado, resultadoVotacion(camara->proyectoActual->votacionDiputados));
        printf("Resultado en la Cámara de Diputados: %s\n", resultado);
    } else {
        ingresarVotos(&(camara->proyectoActual->votacionSenado));
        strcpy(resultado, resultadoVotacion(camara->proyectoActual->votacionSenado));
        printf("Resultado en la Cámara de Senado: %s\n", resultado);
    }
}

/* Función para manejar el desacuerdo entre cámaras mediante una comisión mixta */
void manejarDesacuerdo(struct ComisionMixta *comision) {
    char resultadoComision[20];

    printf("Iniciar votación en la Comisión Mixta:\n");
    ingresarVotos(&comision->proyecto->votacion);  // Usar votacion para los votos de la comisión mixta
    strcpy(resultadoComision, resultadoVotacion(comision->proyecto->votacion));

    printf("Resultado en la Comisión Mixta: %s\n", resultadoComision);

    if (strcmp(resultadoComision, "Aprobado") == 0) {
        printf("Proyecto aprobado por la Comisión Mixta.\n");
    } else if (strcmp(resultadoComision, "Rechazado") == 0) {
        printf("Proyecto rechazado por la Comisión Mixta.\n");
    } else {
        printf("La Comisión Mixta no pudo llegar a un acuerdo.\n");
    }
}

/* Función principal para configurar y realizar la votación */
void configurarYVotar(struct ProcesoLegislativo *proceso) {
    char resultadoOrigen[20], resultadoRevision[20];
    struct CamaraLegislativa *camaraOrigen = NULL;
    struct CamaraLegislativa *camaraRevision = NULL;
    struct ComisionMixta *comision = NULL;
    char *nombreCamaraOrigen, *nombreCamaraRevision;

    camaraOrigen = seleccionarCamaraOrigen(proceso, &camaraRevision, &nombreCamaraOrigen, &nombreCamaraRevision);
    if (camaraOrigen == NULL) {
        printf("Selección inválida de cámara.\n");
        return;
    }

    // Imprimir el nombre de la cámara de origen y realizar la votación
    printf("Iniciar votación en la Cámara de %s (Origen):\n", nombreCamaraOrigen);
    realizarVotacionCamara(camaraOrigen, resultadoOrigen, strcmp(nombreCamaraOrigen, "Diputados") == 0 ? 1 : 0);

    // Imprimir el nombre de la cámara de revisión y realizar la votación
    printf("\nIniciar votación en la Cámara de %s (Revisión):\n", nombreCamaraRevision);
    realizarVotacionCamara(camaraRevision, resultadoRevision, strcmp(nombreCamaraRevision, "Diputados") == 0 ? 1 : 0);

    if (strcmp(resultadoOrigen, "Aprobado") == 0 && strcmp(resultadoRevision, "Aprobado") == 0) {
        printf("Proyecto aprobado en ambas cámaras.\n");
    } else if (strcmp(resultadoOrigen, "Rechazado") == 0 && strcmp(resultadoRevision, "Rechazado") == 0) {
        printf("Proyecto rechazado en ambas cámaras.\n");
    } else if ((strcmp(resultadoOrigen, "Aprobado") == 0 && strcmp(resultadoRevision, "Rechazado") == 0) || 
               (strcmp(resultadoOrigen, "Rechazado") == 0 && strcmp(resultadoRevision, "Aprobado") == 0)) {
        printf("Desacuerdo entre las cámaras, se requiere intervención de una comisión mixta.\n");
        
        comision = (struct ComisionMixta *)malloc(sizeof(struct ComisionMixta));
        if (comision != NULL) {
            // Aquí solo pasamos el puntero a la comisión
            manejarDesacuerdo(comision);
        } else {
            printf("Error al asignar memoria para la comisión mixta.\n");
        }
    }
}



/* Función para buscar un proyecto en el árbol por ID */
struct ProyectoLey* buscarProyectoPorID(struct NodoArbol* nodo, int ID) {
    if (nodo == NULL) {
        return NULL;
    }
    if (nodo->proyecto->ID == ID) {
        return nodo->proyecto;
    }
    if (ID < nodo->proyecto->ID) {
        return buscarProyectoPorID(nodo->izq, ID);
    }
    return buscarProyectoPorID(nodo->der, ID);
}

/* Función para buscar un proyecto y mostrar su información */
void buscarProyecto(struct ProcesoLegislativo *proceso) {
    int ID;
    struct ProyectoLey* proyecto;

    printf("Ingrese el ID del proyecto a buscar: ");
    scanf("%d", &ID);
    
    proyecto = buscarProyectoPorID(proceso->Proyectos, ID);

    if (proyecto != NULL) {
        printf("Proyecto encontrado:\n");
        printf("Título: %s\n", proyecto->titulo);
        printf("Descripción: %s\n", proyecto->descripcion);
        printf("Actor: %s\n", proyecto->actor);
        printf("Estado: %s\n", proyecto->estado);
        printf("Urgencia: %d\n", proyecto->urgencia);
        printf("Fecha de ingreso: %s\n", proyecto->fechaIngreso);
    } else {
        printf("Proyecto no encontrado.\n");
    }
}

void modificarProyecto(struct ProcesoLegislativo *proceso) {
    int ID;
    struct ProyectoLey* proyecto;  // Declaración al inicio de la función
    char titulo[100];
    char descripcion[500];
    char actor[100];
    char estado[100];
    
    printf("Ingrese el ID del proyecto a modificar: ");
    scanf("%d", &ID);
    proyecto = buscarProyectoPorID(proceso->Proyectos, ID);
    
    if (proyecto != NULL) {
        printf("Proyecto encontrado. Ingrese los nuevos datos:\n");

        printf("Ingrese el nuevo título del proyecto: ");
        fflush(stdin);
        gets(titulo);
        strcpy(proyecto->titulo, titulo);

        printf("Ingrese la nueva descripción del proyecto: ");
        fflush(stdin);
        gets(descripcion);
        strcpy(proyecto->descripcion, descripcion);

        printf("Ingrese el nuevo actor que presenta la iniciativa: ");
        fflush(stdin);
        gets(actor);
        strcpy(proyecto->actor, actor);

        printf("Ingrese el nuevo estado del proyecto: ");
        fflush(stdin);
        gets(estado);
        strcpy(proyecto->estado, estado);

        printf("Ingrese el nuevo número de firmas requeridas: ");
        scanf("%d", &proyecto->numFirmas);

        printf("Ingrese el nuevo nivel de urgencia (1: baja, 2: media, 3: alta): ");
        scanf("%d", &proyecto->urgencia);

        printf("Proyecto modificado exitosamente.\n");
    } else {
        printf("Proyecto no encontrado.\n");
    }
}


/* Función para encontrar el nodo con el valor mínimo en un árbol binario */
struct NodoArbol* encontrarMinimo(struct NodoArbol* nodo) {
    struct NodoArbol* actual = nodo;
    while (actual != NULL && actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}

/* Función para eliminar un nodo con un proyecto específico del árbol binario */
struct NodoArbol* eliminarNodoProyecto(struct NodoArbol* raiz, int ID) {
    struct NodoArbol* temp;  // Mueve la declaración al inicio de la función
    
    if (raiz == NULL) {
        return raiz;
    }
    
    if (ID < raiz->proyecto->ID) {
        raiz->izq = eliminarNodoProyecto(raiz->izq, ID);
    } else if (ID > raiz->proyecto->ID) {
        raiz->der = eliminarNodoProyecto(raiz->der, ID);
    } else {
        // Caso cuando encontramos el nodo a eliminar
        if (raiz->izq == NULL) {
            temp = raiz->der;
            free(raiz);  // Libera el nodo eliminado
            return temp;
        } else if (raiz->der == NULL) {
            temp = raiz->izq;
            free(raiz);  // Libera el nodo eliminado
            return temp;
        }

        // Nodo con dos hijos: buscar el sucesor en orden (mínimo en el subárbol derecho)
        temp = encontrarMinimo(raiz->der);
        raiz->proyecto = temp->proyecto;
        raiz->der = eliminarNodoProyecto(raiz->der, temp->proyecto->ID);
    }

    return raiz;
}

void eliminarProyecto(struct ProcesoLegislativo *proceso) {
    int ID;
    printf("Ingrese el ID del proyecto a eliminar: ");
    scanf("%d", &ID);
    proceso->Proyectos = eliminarNodoProyecto(proceso->Proyectos, ID);
    printf("Proyecto eliminado exitosamente.\n");
}

/* Función para recorrer el árbol en orden (INORDEN) y mostrar proyectos */
void recorrerArbol(struct NodoArbol* nodo) {
    if (nodo != NULL) {
        recorrerArbol(nodo->izq);
        printf("ID: %d\n", nodo->proyecto->ID);
        printf("Título: %s\n", nodo->proyecto->titulo);
        printf("Descripción: %s\n", nodo->proyecto->descripcion);
        printf("Actor: %s\n", nodo->proyecto->actor);
        printf("Estado: %s\n", nodo->proyecto->estado);
        printf("Urgencia: %d\n", nodo->proyecto->urgencia);
        printf("Fecha de ingreso: %s\n", nodo->proyecto->fechaIngreso);
        printf("-----------------------------------\n");
        recorrerArbol(nodo->der);
    }
}

/* Función para listar todos los proyectos */
void listarProyectos(struct ProcesoLegislativo *proceso) {
    printf("Listado de proyectos:\n");
    recorrerArbol(proceso->Proyectos);
}

/* Modificar el menú principal para incluir las opciones */
void menu() {
    printf("\nSistema de Proceso Legislativo de Chile\n");
    printf("1. Agregar Proyecto de Ley\n");
    printf("2. Configurar Cámaras y Realizar Votación\n");
    printf("3. Buscar Proyecto de Ley\n");
    printf("4. Modificar Proyecto de Ley\n");
    printf("5. Eliminar Proyecto de Ley\n");
    printf("6. Listar todos los Proyectos de Ley\n");
    printf("7. Salir\n");
    printf("Seleccione una opción: ");
}

/* Procesar la opción seleccionada */
void procesarOpcion(int opcion, struct ProcesoLegislativo *proceso) {
    if (opcion == 1) {
        agregarProyecto(proceso);
    } else if (opcion == 2) {
        // Solo permitir configurar cámaras y votar si existe un proyecto actual
        if (proceso->camaras[0] && proceso->camaras[0]->proyectoActual != NULL) {
            configurarYVotar(proceso);
        } else {
            printf("Error: Debe agregar un proyecto de ley antes de configurar las cámaras y realizar la votación.\n");
        }
    } else if (opcion == 3) {
        buscarProyecto(proceso);
    } else if (opcion == 4) {
        modificarProyecto(proceso);
    } else if (opcion == 5) {
        eliminarProyecto(proceso);
    } else if (opcion == 6) {
        listarProyectos(proceso);
    } else if (opcion == 7) {
        printf("Saliendo del sistema...\n");
    } else {
        printf("Opción no válida. Intente nuevamente.\n");
    }
}

/* Función principal para el menú */
int main() {
    struct ProcesoLegislativo proceso;
    int opcion;

    proceso.Proyectos = NULL;

    do {
        menu();
        scanf("%d", &opcion);
        fflush(stdin);  // Limpiar el búfer para evitar problemas con Turbo C
        procesarOpcion(opcion, &proceso);
    } while (opcion != 7);

    return 0;
}
