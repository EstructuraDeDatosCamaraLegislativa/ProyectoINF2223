// Estructura del proyecto de ley (estática)
struct proyecto_ley {
    char titulo[100];           // Título del proyecto de ley
    char descripcion[500];      // Breve descripción del proyecto de ley
    char actor[100];            // Actor que presenta la iniciativa (Presidente, Parlamentario, ciudadanía)
    int numFirmas;              // Número de firmas requeridas (si es iniciativa popular)
    char estado[50];            // Estado del proyecto (Cámara de Origen, Cámara Revisora, Comisión Mixta)
    int urgencia;               // Nivel de urgencia (1: baja, 2: media, 3: alta)
    char fechaIngreso[11];      // Fecha de ingreso del proyecto (YYYY-MM-DD)
};

// Estructura para los votos (estática)
struct votos {
    int aFavor;                 // Número de votos a favor
    int enContra;               // Número de votos en contra
    int abstenciones;           // Número de abstenciones
    float porcentajeAprobacion; // Porcentaje de aprobación
};

// Definición de un parlamentario (estática)
struct Parlamentario {
    int id;                     // Identificador único del parlamentario
    char nombre[100];           // Nombre del parlamentario
    char camara[50];            // Cámara de Diputados o Senado
    char especialidad[100];     // Área de conocimiento
    char partido[50];           // Partido político
};

// Estructura para gestionar la lista de parlamentarios (encapsulamiento)
struct ListaParlamentarios {
    struct NodoParlamentario* inicio;
    int cantidad;
};

// Nodo para la lista dinámica de parlamentarios (lista simplemente enlazada)
struct NodoParlamentario {
    struct Parlamentario* parlamentario;  // Puntero al parlamentario
    struct NodoParlamentario* siguiente;  // Puntero al siguiente nodo en la lista
};

// Estructura para gestionar el arreglo de comisiones (encapsulamiento)
struct ArregloComisiones {
    struct Comision** comisiones;
    int cantidad;
    int capacidad;
};

// Definición de una comisión (dinámica)
struct Comision {
    char nombre[100];                     // Nombre de la comisión
    struct ListaParlamentarios* miembros; // Lista encapsulada de parlamentarios
    char tema[100];                       // Área temática
    char estado[50];                      // Estado actual de la comisión
    struct proyecto_ley* proyectoActual;  // Proyecto en discusión
};

// Estructura para las cámaras (dinámica)
struct camara {
    char tipo_camara[50];                // Tipo de cámara: "Cámara de Origen" o "Cámara Revisora"
    char nombre_camara[50];              // Nombre de la cámara: "Cámara de Diputados" o "Senado"
    struct ArregloComisiones* comisiones;// Arreglo encapsulado de comisiones
    struct proyecto_ley* proyecto_actual;// Proyecto en discusión actual
    struct votos resultado_votacion;     // Resultado de la votación
};

// Definición de la Comisión Mixta (dinámica)
struct ComisionMixta {
    int acuerdos;                           // Indica si se alcanzó un acuerdo 1: Sí, 0: No
    struct proyecto_ley *proyecto;          // Proyecto en discusión
    struct ListaParlamentarios* miembros;   // Lista encapsulada de parlamentarios
    char estado[50];                        // Estado actual de la comisión mixta
};

// Estructura para la promulgación y veto presidencial (dinámica)
struct promulgacion_veto {
    struct proyecto_ley *proyecto;       // Proyecto promulgado o vetado
    int promulgado;                      // 1: Sí, 0: No
    char fechaPromulgacion[11];          // Fecha de promulgación (YYYY-MM-DD)
    int hayVeto;                         // 1: Sí, 0: No
    char tipoVeto[20];                   // "Total" o "Parcial"
    char observaciones[500];             // Observaciones del veto
};

// Estructura para la publicación y entrada en vigencia (dinámica)
struct PublicacionEntradaVigencia {
    struct proyecto_ley *proyecto;       // Proyecto correspondiente
    char nombreLey[100];                 // Nombre de la ley
    char fechaPublicacion[11];           // Fecha de publicación
    int vigenciaInmediata;              // 1: inmediata, 0: con plazo
    char detallesVigencia[200];         // Detalles de vigencia
    char numeroLey[20];                 // Número asignado a la ley
};

// Estructura para el control constitucional (dinámica)
struct ControlConstitucional {
    struct proyecto_ley *proyecto;       // Proyecto a revisar
    char nombreLey[100];                 // Nombre de la ley
    int esConstitucional;               // 1: constitucional, 0: inconstitucional
    char fundamentacion[500];           // Fundamentación de la decisión
    char fechaRevision[11];            // Fecha de la revisión
};

// Estructura para gestionar el árbol de proyectos (encapsulamiento)
struct ArbolProyectos {
    struct NodoABB* raiz;
    int cantidadProyectos;
};

// Árbol binario de búsqueda (ABB) para proyectos de ley (dinámica compleja)
struct NodoABB {
    struct proyecto_ley* proyecto;
    struct NodoABB* izquierda;
    struct NodoABB* derecha;
};

// Funciones básicas para la gestión de ListaParlamentarios
struct ListaParlamentarios* crearListaParlamentarios() {
    struct ListaParlamentarios* lista = (struct ListaParlamentarios*)malloc(sizeof(struct ListaParlamentarios));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->cantidad = 0;
    }
    return lista;
}

// Funciones básicas para la gestión de ArregloComisiones
struct ArregloComisiones* crearArregloComisiones(int capacidadInicial) {
    struct ArregloComisiones* arreglo = (struct ArregloComisiones*)malloc(sizeof(struct ArregloComisiones));
    if (arreglo != NULL) {
        arreglo->comisiones = (struct Comision**)malloc(sizeof(struct Comision*) * capacidadInicial);
        arreglo->cantidad = 0;
        arreglo->capacidad = capacidadInicial;
    }
    return arreglo;
}

// Funciones básicas para la gestión del ArbolProyectos
struct ArbolProyectos* crearArbolProyectos() {
    struct ArbolProyectos* arbol = (struct ArbolProyectos*)malloc(sizeof(struct ArbolProyectos));
    if (arbol != NULL) {
        arbol->raiz = NULL;
        arbol->cantidadProyectos = 0;
    }
    return arbol;
}

// Función para insertar un proyecto en el ABB
void insertarProyecto(struct ArbolProyectos* arbol, struct proyecto_ley* proyecto) {
    struct NodoABB* nuevo = (struct NodoABB*)malloc(sizeof(struct NodoABB));
    if (nuevo != NULL) {
        nuevo->proyecto = proyecto;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        
        if (arbol->raiz == NULL) {
            arbol->raiz = nuevo;
        } else {
            // Inserción basada en el título del proyecto (orden alfabético)
            struct NodoABB* actual = arbol->raiz;
            struct NodoABB* padre = NULL;
            
            while (actual != NULL) {
                padre = actual;
                if (strcmp(proyecto->titulo, actual->proyecto->titulo) < 0) {
                    actual = actual->izquierda;
                } else {
                    actual = actual->derecha;
                }
            }
            
            if (strcmp(proyecto->titulo, padre->proyecto->titulo) < 0) {
                padre->izquierda = nuevo;
            } else {
                padre->derecha = nuevo;
            }
        }
        arbol->cantidadProyectos++;
    }
}

// Función para agregar un parlamentario a una lista
void agregarParlamentario(struct ListaParlamentarios* lista, struct Parlamentario* parlamentario) {
    struct NodoParlamentario* nuevo = (struct NodoParlamentario*)malloc(sizeof(struct NodoParlamentario));
    if (nuevo != NULL) {
        nuevo->parlamentario = parlamentario;
        nuevo->siguiente = lista->inicio;
        lista->inicio = nuevo;
        lista->cantidad++;
    }
}

// Función para agregar una comisión al arreglo
int agregarComision(struct ArregloComisiones* arreglo, struct Comision* comision) {
    if (arreglo->cantidad >= arreglo->capacidad) {
        // Duplicar la capacidad del arreglo
        int nuevaCapacidad = arreglo->capacidad * 2;
        struct Comision** temp = (struct Comision**)realloc(arreglo->comisiones, 
                                                          sizeof(struct Comision*) * nuevaCapacidad);
        if (temp == NULL) {
            return 0; // Error al redimensionar
        }
        arreglo->comisiones = temp;
        arreglo->capacidad = nuevaCapacidad;
    }
    
    arreglo->comisiones[arreglo->cantidad] = comision;
    arreglo->cantidad++;
    return 1; // Éxito
}

// Función para liberar la memoria de una lista de parlamentarios
void liberarListaParlamentarios(struct ListaParlamentarios* lista) {
    struct NodoParlamentario* actual = lista->inicio;
    while (actual != NULL) {
        struct NodoParlamentario* siguiente = actual->siguiente;
        free(actual->parlamentario);
        free(actual);
        actual = siguiente;
    }
    free(lista);
}

// Función para liberar la memoria de un arreglo de comisiones
void liberarArregloComisiones(struct ArregloComisiones* arreglo) {
    for (int i = 0; i < arreglo->cantidad; i++) {
        liberarListaParlamentarios(arreglo->comisiones[i]->miembros);
        free(arreglo->comisiones[i]);
    }
    free(arreglo->comisiones);
    free(arreglo);
}

// Función recursiva para liberar la memoria del árbol de proyectos
void liberarNodoABB(struct NodoABB* nodo) {
    if (nodo != NULL) {
        liberarNodoABB(nodo->izquierda);
        liberarNodoABB(nodo->derecha);
        free(nodo->proyecto);
        free(nodo);
    }
}

// Función para liberar la memoria del árbol completo
void liberarArbolProyectos(struct ArbolProyectos* arbol) {
    liberarNodoABB(arbol->raiz);
    free(arbol);
}














































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

struct promulgacion_veto {
    int promulgado;  // 1: Sí, 0: No
    char fechaPromulgacion[11];
    int hayVeto;     // 1: Sí, 0: No
    char tipoVeto[20];  // "Total" o "Parcial"
};

struct PublicacionEntradaVigencia {
    char nombreLey[100];         // Nombre de la ley
    char fechaPublicacion[11];   // Fecha de publicación (YYYY-MM-DD)
    int vigenciaInmediata;       // 1 si la vigencia es inmediata, 0 si tiene un plazo
    char detallesVigencia[200];  // Detalles sobre la vigencia si no es inmediata
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


    
