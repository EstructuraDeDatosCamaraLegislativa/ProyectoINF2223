#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_TABLA_HASH 100  /* Definimos un tamaño de 100 para la tabla hash */

/* ESTRUCTURAS */

/* Estructura para almacenar los votos de los parlamentarios en un proyecto de ley */
struct VotacionParlamentarios {
    int parlamentarioID;                            /* ID único del parlamentario */
    int voto;                                       /* 1: A favor, 0: En Contra, -1: Abstención */
    int proyectoID;
    struct VotacionParlamentarios *siguiente;       /* Puntero al siguiente voto en la lista */
};

/* Estructura del Proyecto Ley */
struct ProyectoLey {
    int ID;                                            /* ID del proyecto de ley */
    char titulo[100];                                  /* Título del proyecto de ley */
    char descripcion[500];                             /* Descripción del proyecto de ley */
    char actor[100];                                   /* Actor que presenta la iniciativa */
    char estado[100];                                  /* Estado actual del proyecto (Tramitación, Promulgación, Publicado) */
    int numFirmas;                                     /* Número de firmas requeridas para el proyecto */
    int urgencia;                                      /* Nivel de urgencia del proyecto (1: Simple, 2: Suma, 3: Discusión inmediata) */
    char fechaIngreso[11];                             /* Fecha de ingreso del proyecto (DD-MM-YYYY) */
    struct VotacionParlamentarios *camaraDiputados;    /* Votaciones de la Cámara de Diputados */
    struct VotacionParlamentarios *camaraSenado;       /* Votaciones de la Cámara Senado */
    struct VotacionParlamentarios *comisionMixta;      /* Votaciones de la Comisión Mixta */
};

/* Nodo del árbol binario de búsqueda de proyectos de ley */
struct NodoArbol {
    struct NodoArbol *izq;              /* Puntero al hijo izquierdo */
    struct NodoArbol *der;              /* Puntero al hijo derecho */
    struct ProyectoLey *proyecto;       /* Puntero al proyecto de ley almacenado en este nodo */
};

/* Estructura para la tabla hash */
struct HashTable {
    struct ProyectoLey* proyectos[TAM_TABLA_HASH];  // Array de punteros a proyectos
};

/* Estructura de la Camara Legislativa */
struct CamaraLegislativa {
    char nombreCamara[100];              /* Nombre de la camara (Diputado o Senado) */
    struct ProyectoLey *proyecto;        /* Puntero al proyecto de ley */
};

/* Estructura de la Comisión Mixta */
struct ComisionMixta {
    struct ProyectoLey *proyecto;                       /* Puntero al proyecto de ley */
};

/* Estructura que representa todo el proceso legislativo */
struct ProcesoLegislativo {
    struct HashTable *ProyectosTab;              /* Puntero a la tabla hash de proyectos */
    struct NodoArbol *Proyectos;                 /* Paso 1: Iniciativa Legislativa (Árbol con proyectos de ley) */
    struct CamaraLegislativa *camaras[2];        /* Paso 2: Cámara Legislativa */
    struct ComisionMixta *comisionMixta;         /* Paso 3: Comisión Mixta */
};

/* FUNCIONES */

/* Función para crear un nuevo proyecto de ley */
struct ProyectoLey *crearProyectoLey(int ID, char *titulo, char *descripcion, char *actor, char *estado, int numFirmas, int urgencia, char *fechaIngreso) {
    struct ProyectoLey *nuevoProyecto = (struct ProyectoLey *)malloc(sizeof(struct ProyectoLey)); /* Asignación de memoria para un nuevo proyecto de ley */
    if (!nuevoProyecto) return NULL;                         /* Verificar si la asignación fue exitosa */
    nuevoProyecto->ID = ID;                                  /* Asignar el ID del proyecto */
    strcpy(nuevoProyecto->titulo, titulo);                   /* Copiar el título del proyecto */
    strcpy(nuevoProyecto->descripcion, descripcion);         /* Copiar la descripción del proyecto */
    strcpy(nuevoProyecto->actor, actor);                     /* Copiar el actor que presenta la iniciativa */
    strcpy(nuevoProyecto->estado, estado);                   /* Copiar el estado del proyecto */
    nuevoProyecto->numFirmas = numFirmas;                    /* Asignar el número de firmas */
    nuevoProyecto->urgencia = urgencia;                      /* Asignar el nivel de urgencia */
    strcpy(nuevoProyecto->fechaIngreso, fechaIngreso);       /* Copiar la fecha de ingreso */
    /* Listas */
    nuevoProyecto->camaraDiputados = NULL;  /* Inicializar la lista de votaciones de Diputados */
    nuevoProyecto->camaraSenado = NULL;     /* Inicializar la lista de votaciones de Senado */ 
    nuevoProyecto->comisionMixta = NULL;    /* Inicializar la lista de votaciones de la comisión mixta */

    return nuevoProyecto;         /* Devolver el nuevo proyecto creado */
}

/* Función para crear un nuevo nodo del árbol con un proyecto de ley */
struct NodoArbol *crearNodoArbol(struct ProyectoLey *proyecto) {
    struct NodoArbol *nuevoNodo = (struct NodoArbol *)malloc(sizeof(struct NodoArbol));   /* Asignación de memoria para un nuevo nodo */
    if (!nuevoNodo) return NULL;                  /* Verificar si la asignación fue exitosa */
    nuevoNodo->proyecto = proyecto;               /* Asignar el proyecto al nodo */
    nuevoNodo->izq = NULL;                        /* Inicializar el hijo izquierdo como NULL */
    nuevoNodo->der = NULL;                        /* Inicializar el hijo derecho como NULL */
    return nuevoNodo;                             /* Devolver el nuevo nodo creado */
};

/* Función para insertar un proyecto de ley en el árbol binario de búsqueda */
struct NodoArbol *insertarProyecto(struct NodoArbol *nodo, struct ProyectoLey *proyecto) {
    if (nodo == NULL) {                        /* Si el nodo es NULL, hemos encontrado la posición de inserción */
        return crearNodoArbol(proyecto);       /* Crear y devolver un nuevo nodo */
    }

    if (proyecto->ID < nodo->proyecto->ID) {                           /* Si el ID del proyecto es menor, ir a la izquierda */
        nodo->izq = insertarProyecto(nodo->izq, proyecto);             /* Insertar recursivamente en la subárbol izquierdo */
    } else {
        if (proyecto->ID > nodo->proyecto->ID) {                       /* Si el ID del proyecto es mayor, ir a la derecha */
            nodo->der = insertarProyecto(nodo->der, proyecto);         /* Insertar recursivamente en la subárbol derecho */
        } else {                                                       /* Si es igual */
            return nodo;                                               /* Retornar el nodo sin cambios */
        }
    }
    return nodo;         /* Retorna el nodo del árbol */
};

/* Función para capturar los datos del proyecto */
void solicitarDatosProyecto(int *ID, char titulo[100], char descripcion[500], char actor[100], char estado[100], int *numFirmas, int *urgencia, char fechaIngreso[11]) {
    // Solicitar ID del proyecto
    printf("Ingrese el ID del proyecto de ley: ");
    scanf("%d", ID);
    fflush(stdin); // Limpiar el búfer
    // Solicitar el título del proyecto
    printf("Ingrese el título del proyecto de ley: ");
    scanf(" %[^\n]", titulo);  // Leer hasta el salto de línea

    // Solicitar la descripción del proyecto
    printf("Ingrese la descripción del proyecto de ley: ");
    scanf(" %[^\n]", descripcion);  // Leer hasta el salto de línea

    // Solicitar el actor
    printf("Ingrese el actor (quien presenta la iniciativa): ");
    scanf(" %[^\n]", actor);  // Leer hasta el salto de línea

    // Solicitar el estado del proyecto
    printf("Ingrese el estado del proyecto (Tramitacion, Promulgacion, Publicado): ");
    scanf(" %[^\n]", estado);  // Leer hasta el salto de línea

    // Solicitar el número de firmas requeridas
    printf("Ingrese el número de firmas requeridas: ");
    scanf("%d", numFirmas);
    fflush(stdin); // Limpiar el búfer

    // Solicitar el nivel de urgencia
    printf("Ingrese el nivel de urgencia (1: Simple, 2: Suma, 3: Discusión inmediata): ");
    scanf("%d", urgencia);  // Leer hasta el salto de línea

    // Solicitar la fecha de ingreso
    printf("Ingrese la fecha de ingreso (DD-MM-YYYY): ");
    scanf(" %[^\n]", fechaIngreso);  // Leer hasta el salto de línea
}

/* Función para agregar un proyecto al árbol y asignarlo a las cámaras */
void agregarProyecto(struct ProcesoLegislativo *proceso) {
    int ID, numFirmas, urgencia;
    char titulo[100], descripcion[500], actor[100], estado[100], fechaIngreso[11];
    struct ProyectoLey *proyecto;

    // Solicitar los datos del proyecto
    solicitarDatosProyecto(&ID, titulo, descripcion, actor, estado, &numFirmas, &urgencia, fechaIngreso);

    // Crear el proyecto con los datos obtenidos
    proyecto = crearProyectoLey(ID, titulo, descripcion, actor, estado, numFirmas, urgencia, fechaIngreso);

    if (proyecto != NULL) {
        // Insertar el proyecto en el árbol de proyectos
        proceso->Proyectos = insertarProyecto(proceso->Proyectos, proyecto);

        // Asignar el proyecto a ambas cámaras
        proceso->camaras[0]->proyecto = proyecto;  // Cámara de Diputados
        proceso->camaras[1]->proyecto = proyecto;  // Cámara de Senado
    }
}

/* Función para agregar un voto a la lista de votaciones */
void agregarVoto(struct VotacionParlamentarios **votacion, int parlamentarioID, int voto, int proyectoID) {
    struct VotacionParlamentarios *nuevoVoto = (struct VotacionParlamentarios *)malloc(sizeof(struct VotacionParlamentarios));
    if (!nuevoVoto) return; // Verificar si la asignación fue exitosa
    nuevoVoto->parlamentarioID = parlamentarioID;
    nuevoVoto->voto = voto;
    nuevoVoto->proyectoID = proyectoID; // Asociar el voto al proyecto
    nuevoVoto->siguiente = *votacion;
    *votacion = nuevoVoto;
}


/* Función para ingresar votos de los parlamentarios manualmente */
void ingresarVotos(struct VotacionParlamentarios **votacionLista, int proyectoID) {
    int numParlamentarios, id, voto; // Variables para el número de parlamentarios, ID y voto
    int i;

    printf("Ingrese el número de parlamentarios en la votación: ");
    scanf("%d", &numParlamentarios); // Leer el número de parlamentarios
    fflush(stdin); // Limpiar el búfer

    for (i = 0; i < numParlamentarios; i++) {
        printf("Ingrese el ID del parlamentario %d: ", i + 1);
        scanf("%d", &id); // Leer el ID del parlamentario
        fflush(stdin); // Limpiar el búfer

        do {
            printf("Ingrese el voto del parlamentario %d (1: A favor, 0: En Contra, -1: Abstención): ", i + 1);
            scanf("%d", &voto); // Leer el voto
            fflush(stdin); // Limpiar el búfer
        } while (voto != 1 && voto != 0 && voto != -1); // Validar que el voto sea correcto

        agregarVoto(votacionLista, id, voto, proyectoID); // Agregar el voto a la lista
    }
}

/* Función para calcular el resultado de la votación en una lista de votaciones */
char* resultadoVotacion(struct VotacionParlamentarios *votacion) {
    int aFavor = 0, enContra = 0, abstenciones = 0; // Contadores para los resultados de la votación
    struct VotacionParlamentarios *actual = votacion; // Puntero para recorrer la lista de votaciones

    // Contar los votos
    while (actual != NULL) {
        if (actual->voto == 1) {
            aFavor++; // Incrementar si el voto es a favor
        } else {
            if (actual->voto == 0) {
                enContra++; // Incrementar si el voto es en contra
            } else {
                abstenciones++; // Incrementar si es abstención
            }
        }
        actual = actual->siguiente; // Avanzar al siguiente voto
    }

    // Determinar el resultado
    if (aFavor > enContra) {
        return "Aprobado"; // Mayoría a favor
    }
    
    if (enContra > aFavor) {
        return "Rechazado"; // Mayoría en contra
    }

    // Si no se cumple ninguna de las condiciones anteriores, es un empate
    return "Desacuerdo"; // Empate
}


/* Función para seleccionar la cámara de origen y asignar la revisión */
struct CamaraLegislativa* seleccionarCamaraOrigen(struct ProcesoLegislativo *proceso, struct CamaraLegislativa **camaraRevision, char **nombreCamaraOrigen, char **nombreCamaraRevision) {
    int tipoOrigen; // Variable para almacenar la selección de la cámara de origen
    printf("Seleccione la cámara de origen:\n");
    printf("1. Diputados\n");
    printf("2. Senado\n");
    printf("Ingrese su elección: ");
    scanf("%d", &tipoOrigen); // Leer la elección

    // Asignar cámaras de origen y revisión según la selección
    if (tipoOrigen == 1) {
        *camaraRevision = proceso->camaras[1]; // Cámara de Senado como revisión
        *nombreCamaraOrigen = "Diputados";    // Nombre de la cámara de origen
        *nombreCamaraRevision = "Senado";     // Nombre de la cámara de revisión
        return proceso->camaras[0];           // Cámara de Diputados como origen
    }

    if (tipoOrigen == 2) {
        *camaraRevision = proceso->camaras[0]; // Cámara de Diputados como revisión
        *nombreCamaraOrigen = "Senado";       // Nombre de la cámara de origen
        *nombreCamaraRevision = "Diputados";  // Nombre de la cámara de revisión
        return proceso->camaras[1];           // Cámara de Senado como origen
    }

    printf("Selección inválida.\n"); // Mensaje si la selección no es válida
    return NULL; // Retornar NULL en caso de error
}

void mostrarProyectoVotacion(struct CamaraLegislativa *camara) {
    printf("\n--- Proyecto de Ley en Discusión ---\n");
    printf("ID: %d\n", camara->proyecto->ID);
    printf("Título: %s\n", camara->proyecto->titulo);
    printf("Descripción: %s\n", camara->proyecto->descripcion);
    printf("Presentado por: %s\n", camara->proyecto->actor);
    printf("Estado: %s\n", camara->proyecto->estado);
    printf("Urgencia: %d\n", camara->proyecto->urgencia);
    printf("Número de Firmas Requeridas: %d\n", camara->proyecto->numFirmas);
    printf("Fecha de Ingreso: %s\n", camara->proyecto->fechaIngreso);
    printf("----------------------------------\n");
}


/* Función para realizar la votación en una cámara y almacenar el resultado */
void realizarVotacionCamara(struct CamaraLegislativa *camara, char *resultado, int esDiputados) {
    // Mostrar información del proyecto que se está votando
    mostrarProyectoVotacion(camara); 

    if (esDiputados) {
        ingresarVotos(&(camara->proyecto->camaraDiputados), camara->proyecto->ID);
        strcpy(resultado, resultadoVotacion(camara->proyecto->camaraDiputados));
        printf("Resultado en la Cámara de Diputados: %s\n", resultado);
    } else {
        ingresarVotos(&(camara->proyecto->camaraSenado), camara->proyecto->ID);
        strcpy(resultado, resultadoVotacion(camara->proyecto->camaraSenado));
        printf("Resultado en la Cámara de Senado: %s\n", resultado);
    }
}


/* Función para manejar el desacuerdo entre cámaras mediante una comisión mixta */
void manejarDesacuerdo(struct ComisionMixta *comision) {
    char resultadoComision[20]; // Variable para almacenar el resultado de la comisión

    printf("Iniciar votación en la Comisión Mixta:\n");
    ingresarVotos(&comision->proyecto->comisionMixta, comision->proyecto->ID);  // Usar votación para los votos de la comisión mixta
    strcpy(resultadoComision, resultadoVotacion(comision->proyecto->comisionMixta)); // Calcular el resultado

    printf("Resultado en la Comisión Mixta: %s\n", resultadoComision); // Mostrar el resultado

    // Determinar el resultado de la comisión
    if (strcmp(resultadoComision, "Aprobado") == 0) {
        printf("Proyecto aprobado por la Comisión Mixta.\n");
    } else {
        if (strcmp(resultadoComision, "Rechazado") == 0) {
            printf("Proyecto rechazado por la Comisión Mixta.\n");
        } else {
            printf("La Comisión Mixta no pudo llegar a un acuerdo.\n");
        }
    }
}


/* Función principal para configurar y realizar la votación */
void configurarYVotar(struct ProcesoLegislativo *proceso) {
    char resultadoOrigen[20], resultadoRevision[20]; // Variables para almacenar los resultados
    struct CamaraLegislativa *camaraOrigen = NULL; // Puntero para la cámara de origen
    struct CamaraLegislativa *camaraRevision = NULL; // Puntero para la cámara de revisión
    struct ComisionMixta *comision = NULL; // Puntero para la comisión mixta
    char *nombreCamaraOrigen, *nombreCamaraRevision; // Variables para los nombres de las cámaras
    
    // Verificar si hay un proyecto disponible
    if (proceso->Proyectos == NULL) {
        printf("No hay un proyecto disponible para votar.\n");
        return; // Salir de la función si no hay proyecto
    }
    
    camaraOrigen = seleccionarCamaraOrigen(proceso, &camaraRevision, &nombreCamaraOrigen, &nombreCamaraRevision); // Seleccionar la cámara de origen
    if (camaraOrigen == NULL) { // Si hay un error en la selección
        printf("Selección inválida de cámara.\n");
        return; // Salir de la función
    }

    // Imprimir el nombre de la cámara de origen y realizar la votación
    printf("Iniciar votación en la Cámara de %s (Origen):\n", nombreCamaraOrigen);
    realizarVotacionCamara(camaraOrigen, resultadoOrigen, strcmp(nombreCamaraOrigen, "Diputados") == 0 ? 1 : 0); // Realizar la votación

    // Imprimir el nombre de la cámara de revisión y realizar la votación
    printf("\nIniciar votación en la Cámara de %s (Revisión):\n", nombreCamaraRevision);
    realizarVotacionCamara(camaraRevision, resultadoRevision, strcmp(nombreCamaraRevision, "Diputados") == 0 ? 1 : 0); // Realizar la votación

    // Evaluar los resultados de las votaciones
    if (strcmp(resultadoOrigen, "Aprobado") == 0) {
        if (strcmp(resultadoRevision, "Aprobado") == 0) {
            printf("Proyecto aprobado en ambas cámaras.\n");
        } else {
            printf("Desacuerdo entre las cámaras, se requiere intervención de una comisión mixta.\n");
            comision = (struct ComisionMixta *)malloc(sizeof(struct ComisionMixta)); // Asignar memoria para la comisión
            if (comision != NULL) {
                manejarDesacuerdo(comision); // Manejar el desacuerdo
            } else {
                printf("Error al asignar memoria para la comisión mixta.\n"); // Mensaje de error
            }
        }
    } else {
        if (strcmp(resultadoOrigen, "Rechazado") == 0) {
            if (strcmp(resultadoRevision, "Rechazado") == 0) {
                printf("Proyecto rechazado en ambas cámaras.\n");
            } else {
                printf("Desacuerdo entre las cámaras, se requiere intervención de una comisión mixta.\n");
                comision = (struct ComisionMixta *)malloc(sizeof(struct ComisionMixta)); // Asignar memoria para la comisión
                if (comision != NULL) {
                    manejarDesacuerdo(comision); // Manejar el desacuerdo
                } else {
                    printf("Error al asignar memoria para la comisión mixta.\n"); // Mensaje de error
                }
            }
        }
    }
}





/* Función para buscar un proyecto en el árbol por ID */
struct ProyectoLey* buscarProyectoPorID(struct NodoArbol* nodo, int ID) {
    if (nodo == NULL) { // Si el nodo es NULL, el proyecto no fue encontrado
        return NULL; 
    }
    if (nodo->proyecto->ID == ID) { // Si encontramos el proyecto
        return nodo->proyecto; // Retornar el proyecto
    }
    if (ID < nodo->proyecto->ID) { // Buscar en el subárbol izquierdo
        return buscarProyectoPorID(nodo->izq, ID);
    }
    return buscarProyectoPorID(nodo->der, ID); // Buscar en el subárbol derecho
}

/* Función para buscar un proyecto y mostrar su información */
void buscarProyecto(struct ProcesoLegislativo *proceso) {
    int ID; // Variable para el ID del proyecto a buscar
    struct ProyectoLey* proyecto; // Puntero para el proyecto encontrado

    printf("Ingrese el ID del proyecto a buscar: ");
    scanf("%d", &ID); // Leer el ID del proyecto
    
    proyecto = buscarProyectoPorID(proceso->Proyectos, ID); // Buscar el proyecto

    if (proyecto != NULL) { // Si el proyecto fue encontrado
        printf("Proyecto encontrado:\n");
        printf("Título: %s\n", proyecto->titulo);
        printf("Descripción: %s\n", proyecto->descripcion);
        printf("Actor: %s\n", proyecto->actor);
        printf("Estado: %s\n", proyecto->estado);
        printf("Urgencia: %d\n", proyecto->urgencia);
        printf("Fecha de ingreso: %s\n", proyecto->fechaIngreso);
    } else {
        printf("Proyecto no encontrado.\n"); // Mensaje si el proyecto no fue encontrado
    }
}

/* Función para modificar un proyecto existente */
void modificarProyecto(struct ProcesoLegislativo *proceso) {
    int ID; // Variable para el ID del proyecto a modificar
    struct ProyectoLey* proyecto;  // Puntero para el proyecto a modificar
    char titulo[100], descripcion[500], actor[100], estado[100]; // Variables para los nuevos datos del proyecto
    
    printf("Ingrese el ID del proyecto a modificar: ");
    scanf("%d", &ID); // Leer el ID del proyecto
    proyecto = buscarProyectoPorID(proceso->Proyectos, ID); // Buscar el proyecto
    
    if (proyecto != NULL) { // Si el proyecto fue encontrado
        printf("Proyecto encontrado. Ingrese los nuevos datos:\n");

        printf("Ingrese el nuevo título del proyecto: ");
        fflush(stdin); // Limpiar el búfer
        gets(titulo); // Leer el nuevo título
        strcpy(proyecto->titulo, titulo); // Actualizar el título

        printf("Ingrese la nueva descripción del proyecto: ");
        fflush(stdin); // Limpiar el búfer
        gets(descripcion); // Leer la nueva descripción
        strcpy(proyecto->descripcion, descripcion); // Actualizar la descripción

        printf("Ingrese el nuevo actor que presenta la iniciativa: ");
        fflush(stdin); // Limpiar el búfer
        gets(actor); // Leer el nuevo actor
        strcpy(proyecto->actor, actor); // Actualizar el actor

        printf("Ingrese el nuevo estado del proyecto: ");
        fflush(stdin); // Limpiar el búfer
        gets(estado); // Leer el nuevo estado
        strcpy(proyecto->estado, estado); // Actualizar el estado

        printf("Ingrese el nuevo número de firmas requeridas: ");
        scanf("%d", &proyecto->numFirmas); // Leer el nuevo número de firmas

        printf("Ingrese el nuevo nivel de urgencia (1: baja, 2: media, 3: alta): ");
        scanf("%d", &proyecto->urgencia); // Leer el nuevo nivel de urgencia

        printf("Proyecto modificado exitosamente.\n"); // Mensaje de éxito
    } else {
        printf("Proyecto no encontrado.\n"); // Mensaje si el proyecto no fue encontrado
    }
}

// Función para encontrar el nodo mínimo en el subárbol derecho
struct NodoArbol* encontrarMinimo(struct NodoArbol* nodo) {
    struct NodoArbol* actual = nodo; // Se inicializa un puntero para recorrer el nodo

    // Recorre hacia la izquierda hasta encontrar el nodo más pequeño
    while (actual != NULL && actual->izq != NULL) {
        actual = actual->izq; // Avanza al hijo izquierdo
    }
    return actual; // Retorna el nodo mínimo encontrado
}

// Función para eliminar un nodo con un proyecto específico del árbol binario
struct NodoArbol* eliminarNodoProyecto(struct NodoArbol* raiz, int ID, int *eliminado) {
    struct NodoArbol* temp; // Declaración de un puntero temporal para manejar nodos

    // Verifica si la raíz es nula, lo que significa que no se encontró el proyecto
    if (raiz == NULL) {
        *eliminado = 0; // Indica que no se encontró el proyecto
        return raiz; // Retorna nulo
    }

    // Compara el ID para decidir si buscar en el subárbol izquierdo o derecho
    if (ID < raiz->proyecto->ID) {
        raiz->izq = eliminarNodoProyecto(raiz->izq, ID, eliminado); // Busca en el subárbol izquierdo
    } else {
        if (ID > raiz->proyecto->ID) {
            raiz->der = eliminarNodoProyecto(raiz->der, ID, eliminado); // Busca en el subárbol derecho
        } else {
            // Proyecto encontrado
            *eliminado = 1; // Marca que se encontró y se debe eliminar

            // Caso cuando el nodo tiene un solo hijo o ningún hijo
            if (raiz->izq == NULL) {
                temp = raiz->der; // Asigna el hijo derecho
                return temp; // Retorna el hijo derecho
            }
            if (raiz->der == NULL) {
                temp = raiz->izq; // Asigna el hijo izquierdo
                return temp; // Retorna el hijo izquierdo
            }

            // Nodo con dos hijos: buscar el sucesor en orden
            temp = encontrarMinimo(raiz->der); // Encuentra el nodo mínimo en el subárbol derecho
            raiz->proyecto = temp->proyecto; // Copia el proyecto del nodo mínimo al nodo actual
            raiz->der = eliminarNodoProyecto(raiz->der, temp->proyecto->ID, eliminado); // Elimina el sucesor encontrado
        }
    }

    return raiz; // Retorna la raíz del árbol (o subárbol) modificado
}


// Función para eliminar un proyecto en el proceso legislativo
void eliminarProyecto(struct ProcesoLegislativo *proceso) {
    int ID; // Variable para almacenar el ID del proyecto a eliminar
    int eliminado = 0; // Indicador de si el proyecto fue eliminado o no

    // Solicita al usuario el ID del proyecto a eliminar
    printf("Ingrese el ID del proyecto a eliminar: ");
    scanf("%d", &ID);

    // Intenta eliminar el proyecto llamando a la función eliminarNodoProyecto
    proceso->Proyectos = eliminarNodoProyecto(proceso->Proyectos, ID, &eliminado);

    // Muestra un mensaje basado en si se logró eliminar el proyecto o no
    if (eliminado) {
        printf("Proyecto de ley eliminado exitosamente.\n");
    } else {
        printf("Proyecto de ley no existente.\n");
    }
}

/* Función para recorrer el árbol en orden (INORDEN) y mostrar proyectos */
void recorrerArbol(struct NodoArbol* nodo) {
    if (nodo != NULL) { // Si el nodo no es NULL
        recorrerArbol(nodo->izq); // Recorrer el subárbol izquierdo
        // Mostrar la información del proyecto
        printf("ID: %d\n", nodo->proyecto->ID);
        printf("Título: %s\n", nodo->proyecto->titulo);
        printf("Descripción: %s\n", nodo->proyecto->descripcion);
        printf("Actor: %s\n", nodo->proyecto->actor);
        printf("Estado: %s\n", nodo->proyecto->estado);
        printf("Urgencia: %d\n", nodo->proyecto->urgencia);
        printf("Fecha de ingreso: %s\n", nodo->proyecto->fechaIngreso);
        printf("-----------------------------------\n");
        recorrerArbol(nodo->der); // Recorrer el subárbol derecho
    }
}

/* Función para listar todos los proyectos */
void listarProyectos(struct ProcesoLegislativo *proceso) {
    printf("Listado de proyectos:\n");
    recorrerArbol(proceso->Proyectos); // Recorrer y mostrar los proyectos en el árbol
}

/* Función para mostrar el menú principal */
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
        agregarProyecto(proceso); // Agregar un nuevo proyecto
    } 
    if (opcion == 2) {
        // Solo permitir configurar cámaras y votar si existe un proyecto actual
        if (proceso->camaras[0] && proceso->camaras[0]->proyecto != NULL) {
            configurarYVotar(proceso); // Configurar cámaras y realizar la votación
        } else {
            printf("Error: Debe agregar un proyecto de ley antes de configurar las cámaras y realizar la votación.\n");
        }
    } 
    if (opcion == 3) {
        buscarProyecto(proceso); // Buscar un proyecto existente
    } 
    if (opcion == 4) {
        modificarProyecto(proceso); // Modificar un proyecto existente
    } 
    if (opcion == 5) {
        eliminarProyecto(proceso); // Eliminar un proyecto existente
    } 
    if (opcion == 6) {
        listarProyectos(proceso); // Listar todos los proyectos
    } 
    if (opcion == 7) {
        printf("Saliendo del sistema...\n"); // Mensaje de salida
    } 
    if (opcion < 1 || opcion > 7) {
        printf("Opción no válida. Intente nuevamente.\n"); // Mensaje si la opción no es válida
    }
}

/* Función para inicializar el proceso legislativo y manejar el menú */
void ejecutarMenu(struct ProcesoLegislativo *proceso) {
    int opcion; // Variable para almacenar la opción seleccionada

    // Bucle principal del menú
    do {
        menu(); // Mostrar el menú
        scanf("%d", &opcion); // Leer la opción seleccionada
        fflush(stdin);  // Limpiar el búfer para evitar problemas con Turbo C
        procesarOpcion(opcion, proceso); // Procesar la opción seleccionada
    } while (opcion != 7); // Repetir hasta que se elija salir
}

/* Función principal para el menú */
int main() {
    struct ProcesoLegislativo *proceso = malloc(sizeof(struct ProcesoLegislativo)); // Asignar memoria para la estructura
    if (proceso != NULL) {
        proceso->Proyectos = NULL; // Inicializar la lista de proyectos como NULL
        ejecutarMenu(proceso); // Ejecutar el menú
    }
    return 0;
}
