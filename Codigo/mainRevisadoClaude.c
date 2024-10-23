/* Forward declarations */
struct NodoParlamentario;
struct ListaParlamentarios;
struct Comision;
struct ArregloComisiones;

/* Estructura del proyecto de ley (estática) */
struct proyecto_ley {
    char titulo[100];           /* Título del proyecto de ley */
    char descripcion[500];      /* Breve descripción del proyecto de ley */
    char actor[100];           /* Actor que presenta la iniciativa */
    int numFirmas;             /* Número de firmas requeridas */
    char estado[50];           /* Estado del proyecto */
    int urgencia;              /* Nivel de urgencia (1: baja, 2: media, 3: alta) */
    char fechaIngreso[11];     /* Fecha de ingreso del proyecto (YYYY-MM-DD) */
};

/* Estructura para los votos (estática) */
struct votos {
    int aFavor;                /* Número de votos a favor */
    int enContra;              /* Número de votos en contra */
    int abstenciones;          /* Número de abstenciones */
    float porcentajeAprobacion; /* Porcentaje de aprobación */
};

/* Definición de un parlamentario (estática) */
struct Parlamentario {
    int id;                    /* Identificador único del parlamentario */
    char nombre[100];          /* Nombre del parlamentario */
    char camara[50];           /* Cámara de Diputados o Senado */
    char especialidad[100];    /* Área de conocimiento */
    char partido[50];          /* Partido político */
};

/* Estructura para gestionar la lista de parlamentarios */
struct ListaParlamentarios {
    struct NodoParlamentario * inicio;
    int cantidad;
};

/* Nodo para la lista dinámica de parlamentarios */
struct NodoParlamentario {
    struct Parlamentario * parlamentario;   /* Puntero al parlamentario */
    struct NodoParlamentario * siguiente;   /* Puntero al siguiente nodo */
};

/* Estructura para gestionar el arreglo de comisiones */
struct ArregloComisiones {
    struct Comision * * comisiones;
    int cantidad;
    int capacidad;
};

/* Definición de una comisión (dinámica) */
struct Comision {
    char nombre[100];                      /* Nombre de la comisión */
    struct ListaParlamentarios * miembros; /* Lista de parlamentarios */
    char tema[100];                       /* Área temática */
    char estado[50];                      /* Estado actual de la comisión */
    struct proyecto_ley * proyectoActual; /* Proyecto en discusión */
};

/* Estructura para las cámaras (dinámica) */
struct camara {
    char tipo_camara[50];                 /* Tipo de cámara */
    char nombre_camara[50];               /* Nombre de la cámara */
    struct ArregloComisiones * comisiones;/* Arreglo de comisiones */
    struct proyecto_ley * proyecto_actual;/* Proyecto en discusión actual */
    struct votos resultado_votacion;      /* Resultado de la votación */
};

/* Definición de la Comisión Mixta (dinámica) */
struct ComisionMixta {
    int acuerdos;                          /* Indica si se alcanzó un acuerdo */
    struct proyecto_ley * proyecto;        /* Proyecto en discusión */
    struct ListaParlamentarios * miembros; /* Lista de parlamentarios */
    char estado[50];                      /* Estado actual de la comisión mixta */
};

/* Estructura para la promulgación y veto presidencial */
struct promulgacion_veto {
    struct proyecto_ley * proyecto;        /* Proyecto promulgado o vetado */
    int promulgado;                       /* 1: Sí, 0: No */
    char fechaPromulgacion[11];           /* Fecha de promulgación */
    int hayVeto;                          /* 1: Sí, 0: No */
    char tipoVeto[20];                    /* "Total" o "Parcial" */
    char observaciones[500];              /* Observaciones del veto */
};

/* Estructura para la publicación y entrada en vigencia */
struct PublicacionEntradaVigencia {
    struct proyecto_ley * proyecto;        /* Proyecto correspondiente */
    char nombreLey[100];                  /* Nombre de la ley */
    char fechaPublicacion[11];            /* Fecha de publicación */
    int vigenciaInmediata;                /* 1: inmediata, 0: con plazo */
    char detallesVigencia[200];           /* Detalles de vigencia */
    char numeroLey[20];                   /* Número asignado a la ley */
};

/* Estructura para el control constitucional */
struct ControlConstitucional {
    struct proyecto_ley * proyecto;        /* Proyecto a revisar */
    char nombreLey[100];                  /* Nombre de la ley */
    int esConstitucional;                 /* 1: constitucional, 0: inconstitucional */
    char fundamentacion[500];             /* Fundamentación de la decisión */
    char fechaRevision[11];               /* Fecha de la revisión */
};

/* Estructura para gestionar el árbol de proyectos */
struct ArbolProyectos {
    struct NodoABB * raiz;
    int cantidadProyectos;
};

/* Árbol binario de búsqueda para proyectos de ley */
struct NodoABB {
    struct proyecto_ley * proyecto;
    struct NodoABB * izquierda;
    struct NodoABB * derecha;
};
