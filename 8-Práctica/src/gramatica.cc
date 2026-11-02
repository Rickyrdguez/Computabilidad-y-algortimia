#include "clases.h"

/**
 * @brief Muestra el modo correcto de ejecución del programa.
 */
void MostrarUso() {
  std::cout << "Modo de empleo: ./dfa2grammar input.dfa output.gra\n"
            << "Pruebe './dfa2grammar --help' para más información.\n";
}

/**
 * @brief Muestra la ayuda detallada del programa.
 */
void MostrarAyuda() {
  std::cout
      << "Genera una gramática regular a partir de un DFA.\n\n"
      << "USO:\n"
      << "  ./dfa2grammar <input.dfa> <output.gra>\n\n"
      << "PARÁMETROS:\n"
      << "  <input.dfa>   Fichero con la especificación de un DFA.\n"
      << "  <output.gra>  Fichero de salida con la gramática regular G tal "
         "que L(G) = L(M).\n\n"
      << "FORMATO DEL FICHERO .dfa:\n"
      << "  Línea 1: símbolos del alfabeto separados por espacios.\n"
      << "  Línea 2: número total de estados.\n"
      << "  Línea 3: estado de arranque.\n"
      << "  Resto: una línea por estado: identificador, 1 si es de aceptación "
         "o 0 si no, número de transiciones y, por cada una, el símbolo y el "
         "estado destino.\n";
}

/**
 * @brief Construye una gramática sin producciones.
 *
 * @param terminales Alfabeto de la gramática.
 * @param simbolo_arranque Símbolo de arranque (se registra como no terminal).
 */
Grammar::Grammar(const std::set<char>& terminales,
                 const std::string& simbolo_arranque)
    : terminales_(terminales), simbolo_arranque_(simbolo_arranque) {
  no_terminales_.insert(simbolo_arranque);
}

/**
 * @brief Registra un símbolo como no terminal de la gramática.
 *
 * @param no_terminal Nombre del no terminal a añadir.
 */
void Grammar::AnadirNoTerminal(const std::string& no_terminal) {
  no_terminales_.insert(no_terminal);
}

/**
 * @brief Añade una producción a la gramática.
 *
 * @param izquierda No terminal de la parte izquierda.
 * @param derecha Parte derecha ("&" representa la cadena vacía).
 */
void Grammar::AnadirProduccion(const std::string& izquierda,
                               const std::string& derecha) {
  producciones_.push_back({izquierda, derecha});
}

/**
 * @brief Escribe la especificación de la gramática en un fichero .gra
 *
 * @param nombre_fichero Ruta del fichero de salida.
 */
void Grammar::EscribirEnFichero(const std::string& nombre_fichero) const {
  std::ofstream fichero(nombre_fichero);

  if (!fichero.is_open()) {
    std::cerr << "ERROR: No se pudo abrir el fichero de salida: "
              << nombre_fichero << "\n";
    return;
  }

  fichero << terminales_.size() << "\n";
  for (const char terminal : terminales_) {
    fichero << terminal << "\n";
  }

  fichero << no_terminales_.size() << "\n";
  for (const std::string& no_terminal : no_terminales_) {
    fichero << no_terminal << "\n";
  }

  fichero << simbolo_arranque_ << "\n";

  fichero << producciones_.size() << "\n";
  for (const Produccion& produccion : producciones_) {
    fichero << produccion.izquierda << " -> " << produccion.derecha << "\n";
  }
}

/**
 * @brief Función que lee y valida la línea de un estado: identificador,
 * indicador de aceptación, número de transiciones y las transiciones (símbolo
 * destino).
 *
 * @param flujo Línea del estado ya cargada en un stringstream
 * @param numero_linea Número de línea del fichero (para los mensajes)
 * @param estados_vistos Estados ya definidos, para detectar repetidos
 * @return true si la línea es correcta; false si hay algún error
 */
bool Automata::LeerLineaEstado(std::stringstream& flujo, int numero_linea,
                               std::set<int>& estados_vistos) {
  int estado{0};
  int aceptacion{0};
  int numero_transiciones{0};

  if (!(flujo >> estado >> aceptacion >> numero_transiciones)) {
    std::cout << "ERROR: Formato incorrecto en la línea: " << numero_linea
              << "\n";
    return false;
  }

  if (estado < 0 || estado >= cantidad_de_estados_) {
    std::cout << "ERROR: El estado: " << estado
              << " no es un estado válido en el autómata\n";
    return false;
  }

  if (estados_vistos.count(estado)) {
    std::cout << "ERROR: El estado " << estado
              << " está definido más de una vez en el fichero\n";
    return false;
  }
  estados_vistos.insert(estado);

  if (aceptacion == 1) {
    estados_aceptacion_.insert(estado);
  } else if (aceptacion != 0) {
    std::cout << "ERROR: El indicador de aceptación debe de ser o 0 o 1\n";
    return false;
  }

  for (int contador{0}; contador < numero_transiciones; ++contador) {
    char simbolo_entrada{};
    int estado_siguiente{0};

    if (!(flujo >> simbolo_entrada >> estado_siguiente)) {
      std::cout << "ERROR: Formato incorrecto en la línea: " << numero_linea
                << "\n";
      return false;
    }

    if (simbolo_entrada != '&' && !alfabeto_.count(simbolo_entrada)) {
      std::cout << "ERROR: El símbolo: " << simbolo_entrada
                << " no está contenido en el alfabeto\n";
      return false;
    }

    if (estado_siguiente < 0 || estado_siguiente >= cantidad_de_estados_) {
      std::cout << "ERROR: El estado destino: " << estado_siguiente
                << " no es un estado válido en el autómata\n";
      return false;
    }

    std::pair<int, char> par_estado_simbolo{estado, simbolo_entrada};

    if (simbolo_entrada == '&' ||
        funcion_transicion_.count(par_estado_simbolo)) {
      es_dfa_ = false;
    } else {
      funcion_transicion_.insert({par_estado_simbolo, estado_siguiente});
    }
  }

  std::string sobrante;
  if (flujo >> sobrante) {
    std::cout << "ERROR: El estado " << estado
              << " tiene más transiciones de las indicadas\n";
    return false;
  }

  return true;
}

/**
 * @brief Convierte el número de un estado en el nombre de un no terminal
 * (0 -> A, 1 -> B, ..., 25 -> Z, 26 -> A1, 27 -> B1, ...).
 *
 * @param estado Número del estado
 * @return Nombre del no terminal asociado al estado
 */
std::string Automata::NombreNoTerminal(int estado) {
  std::string nombre(1, static_cast<char>('A' + estado % 26));

  if (estado >= 26) {
    nombre += std::to_string(estado / 26);
  }

  return nombre;
}

/**
 * @brief Construye la gramática regular (lineal por la derecha) que genera el
 * mismo lenguaje que reconoce el DFA. Solo debe llamarse si EsDFA() es true.
 *
 * @return Gramática equivalente al autómata
 */
Grammar Automata::ConvertToGrammar() const {
  Grammar gramatica(alfabeto_, NombreNoTerminal(estado_arranque_));

  for (int estado{0}; estado < cantidad_de_estados_; ++estado) {
    gramatica.AnadirNoTerminal(NombreNoTerminal(estado));
  }

  for (const auto& transicion : funcion_transicion_) {
    const std::string izquierda{NombreNoTerminal(transicion.first.first)};
    const char simbolo{transicion.first.second};
    const std::string derecha{simbolo + NombreNoTerminal(transicion.second)};
    gramatica.AnadirProduccion(izquierda, derecha);
  }

  for (const int estado : estados_aceptacion_) {
    gramatica.AnadirProduccion(NombreNoTerminal(estado), "&");
  }

  return gramatica;
}