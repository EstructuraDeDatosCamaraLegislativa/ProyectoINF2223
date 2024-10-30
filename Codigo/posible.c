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
    struct VotacionParlamentarios *votacion;    /* Resultado de votación en la comisión */
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
    struct PublicacionEntradaVigencia *siguiente, *anterior; // Puntero al siguiente y anterior elemento en la lista
};

/* Estructura principal que representa el proceso legislativo */
struct ProcesoLegislativo {
    struct NodoArbol *Proyectos;        /* Árbol binario de proyectos de ley */
    struct CamaraLegislativa *camaras[2]; /* Array de 2 cámaras: [0] para Diputados, [1] para Senado */
    struct ComisionMixta *comisiones;   /* Lista de comisiones mixtas */
    struct PublicacionEntradaVigencia *publicaciones;  /* Lista de publicaciones de leyes */
};
