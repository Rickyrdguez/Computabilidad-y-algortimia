// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de DFAs
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 20/10/2026
//
// Archivo dfa.cc: fichero con la implementación de la clase Automata, de la
// lectura y validación del fichero .dfa y de las funciones de ayuda.
//
// Historial de revisiones
// 17/10/2026 - Creación (primera versión) del código
// 21/10/2026 - Última modificación

#include "dfa.h"

/**
 * @brief Sobrecarga del operador del flujo de salida de alfabeto
 *
 * @param os Flujo de salida del programa
 * @param alfabeto set de tipo char
 */
std::ostream& operator<<(std::ostream& os, const std::set<char>& alfabeto) {
  os << "{";
  auto it = alfabeto.begin();
  while (it != alfabeto.end()) {
    os << *it;
    it++;
    if (it != alfabeto.end()) {
      os << ",";
    }
  }
  os << "}\n";

  return os;
}

/**
 * @brief Sobrecarga del operador del flujo de salida de estados_aceptacion_
 *
 * @param os Flujo de salida del programa
 * @param estados_aceptacion Std::set<int> a mostrar
 */
std::ostream& operator<<(std::ostream& os,
                         const std::set<int>& estados_aceptacion) {
  os << "{";
  auto it = estados_aceptacion.begin();
  while (it != estados_aceptacion.end()) {
    os << *it;
    it++;
    if (it != estados_aceptacion.end()) {
      os << ",";
    }
  }
  os << "}";

  return os;
}

/**
 * @brief Sobrecarga del operador del flujo de salida de la clase Automata
 *
 * @param os Flujo de salida del programa
 * @param automata Objeto constante de la clase Automata a imprimir
 */
std::ostream& operator<<(std::ostream& os, const Automata& automata) {
  os << "Alfabeto: " << automata.alfabeto_;
  os << "Número de estados: " << automata.cantidad_de_estados_ << "\n";
  os << "Estado de arranque: " << automata.estado_arranque_ << "\n";
  os << "Estados de aceptación: " << automata.estados_aceptacion_ << "\n";

  return os;
}

/**
 * @brief Función encargadad de comprobar que una cadena sea aceptada por el DFA
 *
 * @param cadena String a evaluar caracter a caracter
 */
void Automata::ComprobarCadena(const std::string& cadena) const {
  std::cout << std::left << std::setw(15) << "Est. Actual" << std::setw(12)
            << "Entrada" << std::setw(12) << "Nuevo Est. \n";

  int estado_actual{estado_arranque_};

  if (cadena == "&") {
    if (estados_aceptacion_.count(estado_arranque_)) {
      std::cout << "\nCadena de entrada ACEPTADA.\n";
    } else {
      std::cout << "\nCadena de entrada NO ACEPTADA.\n";
    }
    return;
  }

  for (const char entrada : cadena) {
    if (!alfabeto_.count(entrada)) {
      std::cout << "ERROR: El símbolo de entrada " << entrada
                << " no pertenece al alfabeto. Luego, la cadena no ha sido "
                   "aceptada.\n";
      return;
    }

    int estado_siguiente{-1};
    std::pair<int, char> clave{estado_actual, entrada};

    if (estado_actual != -1 && funcion_transicion_.count(clave) > 0) {
      estado_siguiente = funcion_transicion_.at(clave);
    }

    std::cout << std::left << std::setw(15)
              << (estado_actual == -1 ? "Muerte (-1)"
                                      : std::to_string(estado_actual))
              << std::setw(12) << entrada << std::setw(12)
              << (estado_siguiente == -1 ? "Muerte (-1)"
                                         : std::to_string(estado_siguiente))
              << "\n";

    estado_actual = estado_siguiente;
  }

  bool aceptada =
      (estado_actual != -1) && (estados_aceptacion_.count(estado_actual) > 0);

  if (aceptada) {
    std::cout << "\nCadena de entrada ACEPTADA.\n";
  } else {
    std::cout << "\nCadena de entrada NO ACEPTADA.\n";
  }
}

/**
 * @brief Sobrecarga del operador del flujo de insercción para la clase dfa
 *
 * @param is Flujo de entrada del programa
 * @param automata Objeto de la clase automata
 */
std::istream& operator>>(std::istream& is, Automata& automata) {
  std::string linea;
  int contador_linea{1};
  int contador_estados{0};
  std::set<int> estados_vistos;

  automata.automata_invalido_ = false;
  automata.alfabeto_.clear();
  automata.estados_aceptacion_.clear();
  automata.funcion_transicion_.clear();

  while (std::getline(is, linea)) {
    // '\r' comprobación para ficheros creados en windows
    if (!linea.empty() && linea.back() == '\r') {
      linea.pop_back();
    }

    if (linea.empty()) {
      continue;
    }

    if (linea.length() >= 2 && linea.substr(0, 2) == "//") {
      continue;
    }
    std::stringstream string_stream{linea};

    switch (contador_linea) {
      case 1: {
        std::string simbolos;
        while (string_stream >> simbolos) {
          for (const char caracter : simbolos) {
            automata.alfabeto_.insert(caracter);
          }
        }
        break;
      }
      case 2:
        string_stream >> automata.cantidad_de_estados_;
        break;

      case 3:
        string_stream >> automata.estado_arranque_;

        if (automata.estado_arranque_ < 0 ||
            automata.estado_arranque_ >= automata.cantidad_de_estados_) {
          std::cout << "ERROR: El estado de arranque "
                    << automata.estado_arranque_
                    << " no es un estado válido del autómata\n";
          automata.automata_invalido_ = true;
          return is;
        }

        break;
      default:
        break;
    }

    if (contador_linea > 3) {
      int estado, aceptacion;
      char simbolo_entrada;
      int estado_siguiente;

      if (!(string_stream >> estado >> aceptacion)) {
        std::cout << "ERROR: Formato incorrecto en la línea: " << contador_linea
                  << "\n";
        automata.automata_invalido_ = true;
        return is;
      }

      if (estado < 0 || estado >= automata.cantidad_de_estados_) {
        std::cout << "ERROR: El estado: " << estado
                  << " no es un estado válido en el autómata\n";
        automata.automata_invalido_ = true;
        return is;
      }

      if (estados_vistos.count(estado)) {
        std::cout << "ERROR: El estado " << estado
                  << " está definido más de una vez en el fichero\n";
        automata.automata_invalido_ = true;
        return is;
      }

      estados_vistos.insert(estado);

      if (aceptacion == 1) {
        automata.estados_aceptacion_.insert(estado);
      } else if (aceptacion != 0) {
        std::cout << "ERROR: El indicador de aceptación debe de ser o 0 o 1\n";
        automata.automata_invalido_ = true;
        return is;
      }

      std::size_t transiciones_leidas{0};

      while (string_stream >> simbolo_entrada >> estado_siguiente) {
        if (!automata.alfabeto_.count(simbolo_entrada)) {
          std::cout << "ERROR: El símbolo: " << simbolo_entrada
                    << " no está contenido en el alfabeto\n";
          automata.automata_invalido_ = true;
          return is;
        }

        if (estado_siguiente < 0 ||
            estado_siguiente >= automata.cantidad_de_estados_) {
          std::cout << "ERROR: El estado destino: " << estado_siguiente
                    << " no es un estado válido en el autómata\n";
          automata.automata_invalido_ = true;
          return is;
        }

        std::pair<int, char> par_estado_simbolo{estado, simbolo_entrada};
        automata.funcion_transicion_.insert(
            {par_estado_simbolo, estado_siguiente});
        ++transiciones_leidas;
      }

      if (transiciones_leidas != automata.alfabeto_.size()) {
        std::cout << "ERROR: El estado " << estado
                  << " no tiene una transición por cada símbolo del "
                     "alfabeto\n";
        automata.automata_invalido_ = true;
        return is;
      }

      ++contador_estados;
    }
    ++contador_linea;
  }

  if (automata.cantidad_de_estados_ < 1) {
    std::cout << "ERROR: El autómata debe tener al menos un estado\n";
    automata.automata_invalido_ = true;
    return is;
  }

  if (automata.cantidad_de_estados_ != contador_estados) {
    std::cout << "ERROR: La cantidad de estados (" << contador_estados
              << ") no coincide con los especificados en el fichero: "
              << automata.cantidad_de_estados_ << "\n";
    automata.automata_invalido_ = true;
    return is;
  }

  return is;
}

/**
 * @brief Muestra el modo correcto de ejecución del programa.
 */
void MostrarUso() {
  std::cout << "Modo de empleo: ./p06_DFA_simulator input.dfa input.txt\n"
            << "Pruebe './p06_DFA_simulator --help' para más información.\n";
}

/**
 * @brief Muestra la ayuda detallada del programa.
 */
void MostrarAyuda() {
  std::cout
      << "Simulador de Autómatas Finitos Deterministas (DFA).\n\n"
      << "USO:\n"
      << "  ./p06_DFA_simulator <input.dfa> <input.txt> \n\n"
      << "PARÁMETROS:\n"
      << "  <input.dfa>  Fichero de texto con la especificación de un DFA.\n"
      << "  <input.txt>  Fichero de texto con una serie de cadenas (una por "
         "línea) sobre el alfabeto del autómata a evaluar.\n\n"
      << "FORMATO DEL FICHERO .dfa:\n"
      << "  Línea 1: símbolos del alfabeto, sin espacios (ej. ab).\n"
      << "  Línea 2: número total de estados.\n"
      << "  Línea 3: estado de arranque.\n"
      << "  Resto: una línea por estado: identificador, 1 si es de aceptación "
         "o 0 si no, y pares 'símbolo estado_destino'.\n"
      << "  Las líneas que empiezan por // son comentarios.\n"
      << "\n";
}

// ESTUDIO PARA LA PRÁCTICA

/**
 * @brief Identifica los estados que poseen al menos un bucle hacia sí mismos.
 */
std::vector<int> Automata::EstadosBucle() const {
  std::set<int> estados_unicos;

  for (const auto& par_transicion : funcion_transicion_) {
    int estado_origen = par_transicion.first.first;
    int estado_destino = par_transicion.second;

    if (estado_origen == estado_destino) {
      estados_unicos.insert(estado_origen);
    }
  }

  std::vector<int> estados_bucle(estados_unicos.begin(), estados_unicos.end());

  return estados_bucle;
}