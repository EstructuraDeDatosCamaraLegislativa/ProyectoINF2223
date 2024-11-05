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
    struct VotacionParlamentarios *votacionDiputados; /* Lista de votos en Diputados */
    struct VotacionParlamentarios *votacionSenado;    /* Lista de votos en Senado */
    struct VotacionParlamentarios *votacion; /* Lista de votos de los parlamentarios en este proyecto */
};

/* Nodo del árbol binario de búsqueda de proyectos de ley */
struct NodoArbol {
    struct NodoArbol *izq;              /* Puntero al hijo izquierdo */
    struct NodoArbol *der;              /* Puntero al hijo derecho */
    struct ProyectoLey *proyecto;       /* Puntero al proyecto de ley */
};

/* Estructura para representar a los parlamentarios */
struct Parlamentario { 
    int ID;                             /* ID único del parlamentario */
    char nombre[100];                   /* Nombre del parlamentario */
    char partido[50];                   /* Partido político del parlamentario */
    struct Parlamentario *siguiente;    /* Puntero al siguiente parlamentario en la lista */
};

/* Estructura para representar una cámara legislativa (Diputados o Senado) */
struct CamaraLegislativa {
    char tipoCamara[50];                        /* Tipo de cámara (Diputados o Senado) */
    char nombreCamara[50];                      /* Nombre de la cámara */
    struct ProyectoLey *proyectoActual;         /* Proyecto actualmente en discusión */
    struct Parlamentario *parlamentarios;       /* Lista de parlamentarios en esta cámara */
};

/* Estructura para una comisión mixta que discute un proyecto de ley */
struct ComisionMixta {
    char nombre[100];                         /* Nombre de la comisión */
    struct ProyectoLey *proyecto;             /* Proyecto en discusión en la comisión */
    struct VotacionParlamentarios *votacion;  /* Resultado de votación en la comisión */
    struct Parlamentario *parlamentarios;     /* Lista de parlamentarios en la comisión */
};

/* Estructura que almacena detalles de publicación de una ley */
struct PublicacionEntradaVigencia {
    struct ProyectoLey *proyecto;       /* Proyecto correspondiente */
    char nombreLey[100];                /* Nombre de la ley */
    char fechaPublicacion[11];          /* Fecha de publicación */
    int vigenciaInmediata;              /* 1: inmediata, 0: con plazo */
    struct PublicacionEntradaVigencia *siguiente, *anterior; /* Puntero al siguiente y anterior elemento en la lista */
};

/* Estructura principal que representa el proceso legislativo */
struct ProcesoLegislativo {
    struct NodoArbol *Proyectos;        /* Árbol binario de proyectos de ley */
    struct CamaraLegislativa *camaras[2]; /* Array de 2 cámaras: [0] para Diputados, [1] para Senado */
    struct ComisionMixta *comisiones;   /* Lista de comisiones mixtas */
    struct PublicacionEntradaVigencia *publicaciones;  /* Lista de publicaciones de leyes */
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

/* Función para agregar un proyecto de ley y asignarlo a ambas cámaras */
void agregarProyecto(struct ProcesoLegislativo *proceso) {
    int ID, numFirmas, urgencia;
    char titulo[100], descripcion[500], actor[100], estado[100], fechaIngreso[11];

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
        // Asegurarse de que las cámaras estén inicializadas
        if (proceso->camaras[0] == NULL) {
            proceso->camaras[0] = (struct CamaraLegislativa *)malloc(sizeof(struct CamaraLegislativa));
            strcpy(proceso->camaras[0]->tipoCamara, "Diputados");
        }
        if (proceso->camaras[1] == NULL) {
            proceso->camaras[1] = (struct CamaraLegislativa *)malloc(sizeof(struct CamaraLegislativa));
            strcpy(proceso->camaras[1]->tipoCamara, "Senado");
        }

        // Asignar el proyecto actual a ambas cámaras
        proceso->camaras[0]->proyectoActual = proyecto;
        proceso->camaras[1]->proyectoActual = proyecto;

        printf("Proyecto de ley agregado y asignado a ambas cámaras.\n");
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
void ingresarVotos(struct ProyectoLey *proyecto, const char *camara) {
    int numParlamentarios, id, voto;
    struct VotacionParlamentarios **votacionLista = NULL;

    if (strcmp(camara, "Diputados") == 0) {
        votacionLista = &proyecto->votacionDiputados;
    } else if (strcmp(camara, "Senado") == 0) {
        votacionLista = &proyecto->votacionSenado;
    }

    printf("Ingrese el número de parlamentarios en la cámara de %s: ", camara);
    scanf("%d", &numParlamentarios);
    getchar();

    for (int i = 0; i < numParlamentarios; i++) {
        printf("Ingrese el ID del parlamentario %d: ", i + 1);
        scanf("%d", &id);
        getchar();

        do {
            printf("Ingrese el voto del parlamentario %d (1: A favor, 0: En Contra, -1: Abstención): ", i + 1);
            scanf("%d", &voto);
            getchar();
        } while (voto != 1 && voto != 0 && voto != -1);

        agregarVoto(votacionLista, id, voto);
    }
}

/* Función para calcular el resultado de la votación en una lista de votaciones */
const char* resultadoVotacion(struct VotacionParlamentarios *votacion) {
    int aFavor = 0, enContra = 0, abstenciones = 0;
    struct VotacionParlamentarios *actual = votacion;

    while (actual != NULL) {
        if (actual->voto == 1) aFavor++;
        else if (actual->voto == 0) enContra++;
        else abstenciones++;
        actual = actual->siguiente;
    }

    if (aFavor > enContra) return "Aprobado";
    else if (enContra > aFavor) return "Rechazado";
    else return "Desacuerdo";
}

/* Función para configurar las cámaras y realizar votación en ambas */
void configurarYVotar(struct ProcesoLegislativo *proceso) {
    int tipoOrigen;
    
    // Solicitar al usuario que determine cuál será la cámara de origen
    printf("Seleccione la cámara de origen:\n");
    printf("1. Diputados\n");
    printf("2. Senado\n");
    printf("Ingrese su elección: ");
    scanf("%d", &tipoOrigen);
    getchar();  // Limpiar el buffer de entrada

    struct CamaraLegislativa *camaraOrigen = NULL;
    struct CamaraLegislativa *camaraRevision = NULL;

    // Asignar las cámaras en función de la elección del usuario
    if (tipoOrigen == 1) {
        camaraOrigen = proceso->camaras[0];    // Diputados
        camaraRevision = proceso->camaras[1];  // Senado
    } else if (tipoOrigen == 2) {
        camaraOrigen = proceso->camaras[1];    // Senado
        camaraRevision = proceso->camaras[0];  // Diputados
    } else {
        printf("Selección inválida.\n");
        return;
    }

    printf("Iniciar votación en la Cámara de %s (Origen):\n", camaraOrigen->tipoCamara);
    ingresarVotos(camaraOrigen->proyectoActual, camaraOrigen->tipoCamara);
    const char *resultadoOrigen = resultadoVotacion(camaraOrigen->proyectoActual->votacionDiputados);

    printf("Resultado en la Cámara de %s (Origen): %s\n", camaraOrigen->tipoCamara, resultadoOrigen);

    printf("\nIniciar votación en la Cámara de %s (Revisión):\n", camaraRevision->tipoCamara);
    ingresarVotos(camaraRevision->proyectoActual, camaraRevision->tipoCamara);
    const char *resultadoRevision = resultadoVotacion(camaraRevision->proyectoActual->votacionSenado);

    printf("Resultado en la Cámara de %s (Revisión): %s\n", camaraRevision->tipoCamara, resultadoRevision);

    // Determinar el resultado final considerando el desacuerdo cuando una cámara aprueba y la otra rechaza
    if (strcmp(resultadoOrigen, "Aprobado") == 0 && strcmp(resultadoRevision, "Aprobado") == 0) {
        printf("Proyecto aprobado en ambas cámaras.\n");
    } else if (strcmp(resultadoOrigen, "Rechazado") == 0 && strcmp(resultadoRevision, "Rechazado") == 0) {
        printf("Proyecto rechazado en ambas cámaras.\n");
    } else if ((strcmp(resultadoOrigen, "Aprobado") == 0 && strcmp(resultadoRevision, "Rechazado") == 0) || (strcmp(resultadoOrigen, "Rechazado") == 0 && strcmp(resultadoRevision, "Aprobado") == 0)) {
        printf("Desacuerdo entre las cámaras, se requiere intervención de una comisión mixta.\n");

    // Configuración y votación en la comisión mixta en caso de desacuerdo
    struct ComisionMixta *comision = (struct ComisionMixta *)malloc(sizeof(struct ComisionMixta));
    if (comision == NULL) {
        printf("Error al asignar memoria para la comisión mixta.\n");
        return;
    }

    strcpy(comision->nombre, "Comisión Mixta de Resolución de Desacuerdos");
    comision->proyecto = camaraOrigen->proyectoActual;

    // Ingreso de votos para la comisión mixta
    printf("Iniciar votación en la Comisión Mixta:\n");
    ingresarVotos(comision->proyecto, "Comisión Mixta");
    const char *resultadoComision = resultadoVotacion(comision->proyecto->votacion);

    printf("Resultado en la Comisión Mixta: %s\n", resultadoComision);

    // Decisión final basada en el resultado de la comisión
    if (strcmp(resultadoComision, "Aprobado") == 0) {
        printf("Proyecto aprobado por la Comisión Mixta.\n");
    } else if (strcmp(resultadoComision, "Rechazado") == 0) {
        printf("Proyecto rechazado por la Comisión Mixta.\n");
    } else {
        printf("La Comisión Mixta no pudo llegar a un acuerdo.\n");
    }

}


/* Modificar el menú principal para incluir la opción de configuración y votación */
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
        // Permitir agregar un proyecto de ley sin restricciones
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

int main() {
    struct ProcesoLegislativo *PL = (struct ProcesoLegislativo *)malloc(sizeof(struct ProcesoLegislativo));
    if (PL == NULL) {
        printf("Error al asignar memoria para el proceso legislativo.\n");
        return 1;
    }

    /* Inicialización de los miembros de ProcesoLegislativo */
    PL->Proyectos = NULL;
    PL->camaras[0] = NULL;
    PL->camaras[1] = NULL;

    int opcion;
    do {
        menu();
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer de entrada
        procesarOpcion(opcion, PL);
    } while (opcion != 3);

    return 0;
}
