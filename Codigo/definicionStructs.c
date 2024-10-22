// Estructura del proyecto de ley 
struct proyecto_ley {
    char titulo[100];           // Título del proyecto de ley
    char descripcion[500];      // Breve descripción del proyecto de ley
    char actor[100];            // Actor que presenta la iniciativa (Presidente, Parlamentario, ciudadanía)
    int numFirmas;              // Número de firmas requeridas (si es iniciativa popular)
    char estado[50];            // Estado del proyecto (Cámara de Origen, Cámara Revisora, Comisión Mixta)
};

// Estructura para los votos
struct votos {
    int aFavor;                 // Número de votos a favor
    int enContra;               // Número de votos en contra
    int abstenciones;           // Número de abstenciones
};

// Definición de un parlamentario
struct Parlamentario {
    int id;                     // Identificador único del parlamentario
    char nombre[100];           // Nombre del parlamentario
    char camara[50];            // Cámara de Diputados o Senado
    char especialidad[100];     // Área de conocimiento
};

// Definición de una comisión
struct Comision {
    char nombre[100];                    // Nombre de la comisión, ej: "Comisión de Educación"
    struct Parlamentario** parlamentarios;  // Lista de parlamentarios en la comisión
    int num_parlamentarios;              // Número de parlamentarios en la comisión
    char tema[100];                      // Área temática que cubre la comisión (ej: educación, salud)
};

// Estructura para las cámaras (Cámara de Origen y Cámara Revisora)
struct camara {
    char tipo_camara[50];                // Tipo de cámara: "Cámara de Origen" o "Cámara Revisora"
    char nombre_camara[50];              // Nombre de la cámara: "Cámara de Diputados" o "Senado"
    struct Comision** comisiones;        // Lista de comisiones que analizan el proyecto (arreglo de comisiones)
    int num_comisiones;                  // Número de comisiones en la cámara
    struct proyecto_ley* proyecto_actual; // Proyecto que está siendo discutido actualmente
    struct votos resultado_votacion;     // Resultado de la votación
};

// Definición de la Comisión Mixta
struct ComisionMixta {
    int acuerdos;                        // Indica si se alcanzó un acuerdo 1: Sí, 0: No
    struct proyecto_ley *proyecto;       // Proyecto en discusión
    struct Parlamentario** parlamentarios; // Lista de parlamentarios de ambas cámaras
    int num_parlamentarios;              // Número de parlamentarios en la comisión mixta
};

















































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







2.0
// Estructura del proyecto de ley 
struct proyecto_ley {
    char titulo[100];           // Título del proyecto de ley
    char descripcion[500];      // Breve descripción del proyecto de ley
    char actor[100];            // Actor que presenta la iniciativa (Presidente, Parlamentario, ciudadania)
    int numFirmas;              // Número de firmas requeridas (si es iniciativa popular)
};

// Estructura para los votos
struct votos {
    int aFavor;     // Número de votos a favor
    int enContra;  // Número de votos en contra
};

// Definición de un parlamentario
struct Parlamentario {
    char nombre[100];
    char camara[50];  // Cámara de Diputados o Senado
    char especialidad[100]; // Área de conocimiento
};

// Definición de una comisión
struct Comision {
    char nombre[100]; // Nombre de la comisión, ej: "Comisión de Educación"
    struct Parlamentario** parlamentarios; // Lista de parlamentarios
    int num_parlamentarios; // Número de parlamentarios en la comisión
};
// Estructura única para ambas cámaras (Cámara de Origen y Cámara Revisora)
struct camara {
    char tipo_camara[50];          // Tipo de cámara: "Cámara de Origen" o "Cámara Revisora"
    char nombre_camara[50];        // Nombre de la cámara: "Cámara de Diputados" o "Senado"
    struct comision *comisiones;   // Lista de comisiones que analizan el proyecto
    struct votos resultado_votacion; // Resultado de la votación
};

// Definición de la Comisión Mixta
struct ComisionMixta {
    int acuerdos;                         // Indica si se alcanzó un acuerdo 1: Sí, 0: No
    struct ProyectoDeLey *proyecto; // Proyecto en discusión
    struct Parlamentario** parlamentarios; // Lista de parlamentarios de ambas cámaras
};





// Estructura para las comisiones en cada cámara
struct comision {
    char nombre[100];              // Nombre de la comisión (Ej: Comisión de Hacienda)
    struct comision *siguiente;    // Puntero a la siguiente comisión (lista simple)
};
// Estructura para Comisión Mixta
struct ComisionMixta {
    struct ProyectoDeLey *proyecto;       // Proyecto en discusión
    int acuerdos;                         // Indica si se alcanzó un acuerdo 1: Sí, 0: No
    struct Comision *parlamentarios; // Lista de parlamentarios
};




// Definición de una cámara (Cámara de Origen o Cámara Revisora)
struct Camara {
    char nombre[50]; // Cámara de Diputados o Senado
    struct Comision** comisiones; // Lista de comisiones
    int num_comisiones; // Número de comisiones en la cámara
};














// Estructura para Votos en las cámaras
struct Votos {
    int aFavor;
    int enContra;
};

// Estructura de las cámaras origen y revision
struct Camara {
    char tipoCamara[20];  // "Senado" o "Cámara de Diputados"
    struct ProyectoDeLey *proyecto;    // Referencia al proyecto de ley en esta cámara
    struct Votos resultadosVotacion; // Resultado de la votación en Cámara de Origen
    struct Comision *parlamentarios; // Lista de parlamentarios
};

// Estructura para la comision de senado o diputado
struct Comision {
    char nombre[50];
    struct Comision *siguiente; // Lista simplemente enlazada para los parlamentarios
    int voto; // 1: a favor, 0: en contra
};

// Estructura para Comisión Mixta
struct ComisionMixta {
    struct ProyectoDeLey *proyecto;       // Proyecto en discusión
    int acuerdos;                         // Indica si se alcanzó un acuerdo 1: Sí, 0: No
    struct Comision *parlamentarios; // Lista de parlamentarios
};

struct promulgacion_veto {
    int promulgado;  // 1: Sí, 0: No
    char fechaPromulgacion[11];
    int hayVeto;     // 1: Sí, 0: No
    char tipoVeto[20];  // "Total" o "Parcial"
};


    
