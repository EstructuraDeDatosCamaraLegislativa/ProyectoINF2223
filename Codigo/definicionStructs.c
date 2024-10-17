struct ProyectoDeLey {
    int id;
    char nombre[100];
    char descripcion[255];
};

// Estructura para Iniciativa Legislativa
struct IniciativaLegislativa {
    struct ProyectoDeLey *proyecto;  // Apunta al proyecto de ley propuesto.
    char actor[50];                  // Presidente, Parlamentario, Diputado, etc
    struct IniciativaLegislativa *siguiente;  // Lista enlazada para múltiples iniciativas
};

// Estructura para Votos en las cámaras
struct Votos {
    int aFavor;
    int enContra;
};

// Estructura para Cámara de Origen 
struct CamaraOrigen {
    struct ProyectoDeLey *proyecto;    // Referencia al proyecto de ley en esta cámara
    struct Votos resultadosVotacion;   // Resultado de la votación en Cámara de Origen
};

// Estructura para Cámara de Revisión
struct CamaraRevision {
    struct ProyectoDeLey *proyecto;    // Referencia al proyecto de ley aprobado en Cámara de Origen
    struct Votos resultadosVotacion;   // Resultado de la votación en Cámara de Revisión
};

// Estructura para Comisión Mixta (donde sí pueden darse modificaciones)
struct ComisionMixta {
    struct ProyectoDeLey *proyecto;       // Proyecto en discusión
    int acuerdos;                         // Indica si se alcanzó un acuerdo
    struct Modificacion *modificaciones;  // Lista doblemente enlazada de las modificaciones propuestas.
};

// Estructura para Promulgación y Veto Presidencial
struct Promulgacion {
    struct ProyectoDeLey *proyecto;       // Proyecto de ley que llega a esta etapa
    int veto;                             // 1 si hay veto parcial presidencial, 0 si no lo hay, 2 veto total.
    struct Promulgacion *siguiente;       // Lista circular (si hay más de uno)
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
    struct NodoABB *izquierda;            // Subárbol izquierdo (proyectos con ID menor)
    struct NodoABB *derecha;              // Subárbol derecho (proyectos con ID mayor)
};

// Estructura para Control Constitucional (ABB)
struct ControlConstitucional {
    struct NodoABB *raiz;    // La raíz del árbol binario de búsqueda
};

// Estructura para Modificaciones como lista doblemente enlazada
struct Modificacion {
    char descripcion[255];
    struct Modificacion *siguiente;  // Puntero a la siguiente modificación (hacia adelante)
    struct Modificacion *anterior;   // Puntero a la modificación anterior (hacia atrás)
};
