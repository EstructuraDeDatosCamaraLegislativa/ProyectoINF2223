#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para Proyecto de Ley
struct ProyectoDeLey {
    int id;
    char nombre[100];
    char descripcion[255];
};

// Estructura para Iniciativa Legislativa
struct IniciativaLegislativa {
    struct ProyectoDeLey *proyecto; // Apunta al proyecto de ley propuesto
    char actor[50];                 // Presidente, Parlamentario, Ciudadanía
    struct IniciativaLegislativa *siguiente;  // Lista enlazada para posibles múltiples iniciativas
};

// Estructura para Votos en las cámaras
struct Votos {
    int aFavor;
    int enContra;
};

// Estructura para Modificaciones (enmiendas)
struct Modificacion {
    char descripcion[255];
    struct Modificacion *siguiente;  // Lista enlazada para las enmiendas
};

// Estructura para Cámara de Origen
struct CamaraOrigen {
    struct ProyectoDeLey *proyecto;    // Referencia al proyecto de ley en esta cámara
    struct Votos resultadosVotacion;   // Estructura estática para almacenar los votos
    struct Modificacion *modificaciones;  // Lista enlazada de enmiendas propuestas
};

// Estructura para Cámara de Revisión
struct CamaraRevision {
    struct ProyectoDeLey *proyecto;     // Referencia al proyecto en revisión
    struct Votos resultadosVotacion;    // Resultado de la votación en la cámara revisora
    struct Modificacion *modificaciones;  // Lista enlazada para nuevas enmiendas
};

// Estructura para Comisión Mixta
struct ComisionMixta {
    struct ProyectoDeLey *proyecto;       // Proyecto en discusión
    int acuerdos;                         // Indica si se alcanzó un acuerdo
    struct Modificacion *modificaciones;  // Lista enlazada de enmiendas adicionales
};

// Estructura para Promulgación y Veto Presidencial
struct Promulgacion {
    struct ProyectoDeLey *proyecto;       // Proyecto de ley que llega a esta etapa
    int veto;                             // 1 si hay veto presidencial, 0 si no lo hay
    struct Promulgacion *siguiente;       // Lista enlazada por si hay más de un veto
};

// Estructura para Publicación y Entrada en Vigencia
struct Publicacion {
    struct ProyectoDeLey *proyecto;   // Proyecto de ley publicado
    char fechaPublicacion[20];        // Fecha de publicación
    char fechaVigencia[20];           // Fecha de entrada en vigencia
};

// Nodo del Árbol Binario de Búsqueda (ABB) para Control Constitucional
struct NodoABB {
    struct ProyectoDeLey *proyecto;       // Proyecto que pasa por control constitucional
    struct NodoABB *izquierda;            // Subárbol izquierdo (Árbol Binario de Búsqueda)
    struct NodoABB *derecha;              // Subárbol derecho
};

// Estructura para Control Constitucional (ABB)
struct ControlConstitucional {
    struct NodoABB *raiz;    // Árbol Binario de Búsqueda de proyectos en revisión constitucional
};
