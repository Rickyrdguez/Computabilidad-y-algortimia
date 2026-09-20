#include <iostream>
#include <set>
#include <string>

#include "p02_string.h"

/**
 * @brief Método que se encarga de insertar las cadenas en el lenguaje
 *
 * @param cadena Cadena de símbolos
 */
void Lenguaje::InsertarEnLenguaje(const Cadena& cadena) {
  lenguaje_.insert(cadena);
}

/**
 * @brief Sobrecarga del operador del flujo de salida
 *
 * @param os Flujo de salida
 * @param lenguaje Lenguaje a mostrar
 */
std::ostream& operator<<(std::ostream& os, const Lenguaje& lenguaje) {
  if (lenguaje.lenguaje_.empty()) {
    os << "{}\n";
    return os;
  }

  bool primer_elemento = true;

  os << "{";

  for (auto iterador : lenguaje.lenguaje_) {
    if (primer_elemento == false) {
      os << ", " << iterador;
    } else {
      os << iterador;
      primer_elemento = false;
    }
  }
  os << "}\n";

  return os;
}