// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramática regular a partir de un DFA
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 02/11/2026
//
// Archivo automata.cc: fichero con la implementación de la clase Automata:
// lectura y validación del fichero .dfa y conversión del DFA a una gramática
// regular.
//
// Historial de revisiones
// 02/11/2026 - Creación (primera versión) del código
// 04/11/2026 - Última modificación

#include "clases.h"

/**
 * @brief Construye el autómata leyendo su especificación de un fichero .dfa
 *
 * @param nombre_fichero Ruta del fichero .dfa de entrada.
 */
Automata::Automata(const std::string& nombre_fichero) {
  std::ifstream fichero(nombre_fichero);

  if (!fichero.is_open()) {
    std::cerr << "ERROR: No se pudo abrir el fichero de especificación del DFA: "
              << nombre_fichero << "\n";
    automata_invalido_ = true;
    return;
  }

  fichero >> *this;
}

/**
 * @brief Sobrecarga del operador de extracción para la clase Automata
 *
 * @param is Flujo de entrada del programa
 * @param automata Objeto de la clase Automata
 */
std::istream& operator>>(std::istream& is, Automata& automata) {
  std::string linea;
  int contador_linea{1};
  int contador_estados{0};
  std::set<int> estados_vistos;

  automata.automata_invalido_ = false;
  automata.es_dfa_ = true;
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
      if (!automata.LeerLineaEstado(string_stream, contador_linea,
                                    estados_vistos)) {
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