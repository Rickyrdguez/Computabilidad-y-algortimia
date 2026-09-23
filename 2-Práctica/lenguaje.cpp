// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 16/09/2026
//
// Archivo lenguaje.cpp: implementación de los métodos de la clase Lenguaje.
//
// Historial de revisiones
// 16/09/2026 - Creación (primera versión) del código
// 21/09/2026 - Última modificación

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

// Estudio para la sesión de evaluación

/**
 * @brief Sobrecarga del operador de suma para hacer la concatenación de
 * lenguajes
 *
 * @param lenguaje Lenguaje distinto al de la clase
 */
Lenguaje operator+(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2) {
  Lenguaje concatenacion{};

  for (const auto& cadena1 : lenguaje1.lenguaje_) {
    for (const auto& cadena2 : lenguaje2.lenguaje_) {
      concatenacion.InsertarEnLenguaje(cadena1 + cadena2);
    }
  }

  return concatenacion;
}

/**
 * @brief Sobrecarga del operador de potencia (^) para lenguajes.
 *
 * @param lenguaje Objeto de la clase Lenguaje que actúa como base (L).
 * @param exponente Exponente entero que indica el número de concatenaciones
 * sucesivas.
 */
Lenguaje operator^(const Lenguaje& lenguaje, int exponente) {
  Lenguaje potencia{};
  potencia.InsertarEnLenguaje(Cadena{""});

  if (exponente <= 0) {
    return potencia;
  }

  for (int i{0}; i < exponente; ++i) {
    potencia = potencia + lenguaje;
  }

  return potencia;
}

/**
 * @brief Calcula la unión entre el lenguaje actual y otro proporcionado.
 *
 * @param lenguaje Objeto de la clase Lenguaje a unir.
 */
Lenguaje Lenguaje::Union(const Lenguaje& lenguaje) const {
  Lenguaje union_lenguajes = *this;  // Copiamos el primer lenguaje

  for (const Cadena& cadena : lenguaje.lenguaje_) {
    union_lenguajes.InsertarEnLenguaje(cadena);  // Insertamos el segundo
  }

  return union_lenguajes;
}

/**
 * @brief Función que comprueba si un lenguaje es sublenguaje de otro
 *
 * @param lenguaje Lenguaje distinto del de la clase
 */
bool Lenguaje::EsSublenguaje(const Lenguaje& lenguaje) const {
  if (this->lenguaje_.empty()) {
    return true;
  }

  for (const Cadena& cadena : this->lenguaje_) {
    if (lenguaje.lenguaje_.find(cadena) == lenguaje.lenguaje_.end()) {
      return false;
    }
  }

  return true;
}