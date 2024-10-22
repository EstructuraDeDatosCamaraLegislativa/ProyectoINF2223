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



