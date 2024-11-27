/* Estructura para almacenar los votos de los parlamentarios en un proyecto de ley */
struct VotacionParlamentarios {
    int parlamentarioID;                            /* ID único del parlamentario */
    int voto;                                       /* 1: A favor, 0: En Contra, -1: Abstención */
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
    struct VotacionParlamentarios *camaraDeOrigen;    /* Votaciones de la Cámara de Origen */
    struct VotacionParlamentarios *camaraDeRevision;   /* Votaciones de la Cámara Revisora */
    struct VotacionParlamentarios *comisionMixta;      /* Votaciones de la Comisión Mixta */
};

/* Nodo del árbol binario de búsqueda de proyectos de ley */
struct NodoArbol {
    struct NodoArbol *izq;              /* Puntero al hijo izquierdo */
    struct NodoArbol *der;              /* Puntero al hijo derecho */
    struct ProyectoLey *proyecto;       /* Puntero al proyecto de ley almacenado en este nodo */
};

/* Estructura de la Cámara de Origen */
struct CamaraOrigen {
    char nombreCamara[100];            /* Nombre de la cámara (Ej. "Cámara de Diputados") */
    int totalParlamentarios;           /* Número total de parlamentarios */
    struct NodoArbol *proyectos;       /* Árbol binario de búsqueda de proyectos de ley */
    struct VotacionParlamentarios *camaraDeOrigen;  /* Votaciones en la Cámara de Origen */
};

/* Estructura de la Cámara Revisora */
struct CamaraRevisora {
    char nombreCamara[100];            /* Nombre de la cámara (Ej. "Cámara de Diputados") */
    int totalParlamentarios;           /* Número total de parlamentarios */
    struct NodoArbol *proyectos;       /* Árbol binario de búsqueda de proyectos de ley */
    struct VotacionParlamentarios *camaraDeRevision; /* Votaciones en la Cámara Revisora */
};

/* Estructura de la Comisión Mixta */
struct ComisionMixta {
    int totalParlamentarios;           /* Número total de parlamentarios */
    struct NodoArbol *proyectos;       /* Árbol binario de búsqueda de proyectos de ley */
    struct VotacionParlamentarios *comisionMixta;    /* Votaciones en la Comisión Mixta */
};

/* Estructura que representa todo el proceso legislativo */
struct ProcesoLegislativo {
    struct NodoArbol *Proyectos;                 /* Paso 1: Iniciativa Legislativa (Árbol con proyectos de ley) */
    struct CamaraOrigen *camaraOrigen;           /* Paso 2: Cámara de Origen */
    struct CamaraRevisora *camaraRevisora;       /* Paso 3: Cámara Revisora */
    struct ComisionMixta *comisionMixta;         /* Paso 4: Comisión Mixta */
};
