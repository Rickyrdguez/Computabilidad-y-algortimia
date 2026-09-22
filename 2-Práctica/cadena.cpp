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
// Archivo cadena.cpp: implementación de los métodos de la clase Cadena.
//
// Historial de revisiones
// 16/09/2026 - Creación (primera versión) del código
// 21/09/2026 - Última modificación

#include "p02_string.h"

/**
 * @brief Sobrecarga del operador del flujo de salida
 *
 * @param os Flujo de salida
 * @param cadena Cadena que contiene la serialización de los carácteres
 */
std::ostream& operator<<(std::ostream& os, const Cadena& cadena) {
  if (cadena.cadena_.empty()) {
    os << "&";
  } else {
    os << cadena.cadena_;
  }

  return os;
}

/**
 * @brief Sobrecarga del operador del flujo de insercción
 *
 * @param is Flujo de entrada
 * @param cadena Cadena que contiene la serialización de los carácteres
 */
std::istream& operator>>(std::istream& is, Cadena& cadena) {
  std::string cadena_nueva;

  if (is >> cadena_nueva) {
    cadena.cadena_ = cadena_nueva;
  }

  return is;
}

/**
 * @brief Sobrecarga del operador "menor que(<)"
 *
 * @param cadena1 Primera cadena
 * @param cadena2 Segunda cadena
 */
bool operator<(const Cadena& cadena1, const Cadena& cadena2) {
  if (cadena1.cadena_.size() == cadena2.cadena_.size()) {
    return cadena1.cadena_ < cadena2.cadena_;
  }

  return cadena1.cadena_.size() < cadena2.cadena_.size();
}

/**
 * @brief Función enargada de devolver la longitud de una cadena
 */
int Cadena::LongitudCadena() const { return static_cast<int>(cadena_.size()); }

/**
 * @brief Función encargada de devolver una cadena pero al revés
 */
std::string Cadena::CadenaInversa() const {
  if (cadena_ == "&") {
    return "&";
  }

  std::string cadena_inversa{};

  for (int i = static_cast<int>(cadena_.size()) - 1; i >= 0; --i) {
    cadena_inversa += cadena_[i];
  }

  return cadena_inversa;
}

/**
 * @brief Función que devuelve un conjunto de prefijos
 */
Lenguaje Cadena::ConjuntoPrefijos() const {
  Lenguaje conjunto_prefijos;
  conjunto_prefijos.InsertarEnLenguaje(Cadena{""});

  std::string cadena{};

  for (int i{0}; i < static_cast<int>(cadena_.size()); ++i) {
    cadena += cadena_[i];
    conjunto_prefijos.InsertarEnLenguaje(Cadena{cadena});
  }

  return conjunto_prefijos;
}

/**
 * @brief Función que devuelve un conjunto de sufijos
 */
Lenguaje Cadena::ConjuntoSufijos() const {
  Lenguaje conjunto_sufijos;
  conjunto_sufijos.InsertarEnLenguaje(Cadena{""});

  std::string cadena{};

  for (int i = static_cast<int>(cadena_.size()) - 1; 0 <= i; --i) {
    cadena = cadena_[i] + cadena;
    conjunto_sufijos.InsertarEnLenguaje(Cadena(cadena));
  }

  return conjunto_sufijos;
}

/**
 * @brief Función encargada de comprobar que la cadena pertenece al alfabeto
 *
 * @param alfabeto Alfabeto de la cadena
 */
bool Cadena::Validacion(const Alfabeto& alfabeto) const {
  for (char caracter : cadena_) {
    if (!alfabeto.ComprobarPertenceAlfabeto(caracter)) {
      return false;
    }
  }

  return true;
}

// Estudio para la sesión de evaluación

/**
 * @brief Sobrecarga del operador de comparacion '=='
 *
 * @param cadena_1 Primer objeto de la cadena a concatenar
 * @param cadena_2 Segundo objeto de la cadena a concatenar
 */
bool operator==(const Cadena& cadena_1, const Cadena& cadena_2) {
  if (cadena_1.cadena_.size() != cadena_2.cadena_.size()) {
    return false;
  }
  for (int i{0}; i < static_cast<int>(cadena_1.cadena_.size()); ++i) {
    if (cadena_1.cadena_[i] != cadena_2.cadena_[i]) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Sobrecarga del operador de suma de la clase cadena
 *
 * @param cadena_1 Primer objeto de la cadena a concatenar
 * @param cadena_2 Segundo objeto de la cadena a concatenar
 */
Cadena operator+(const Cadena& cadena_1, const Cadena& cadena_2) {
  if (cadena_1.cadena_.empty()) {
    return cadena_2;
  }
  if (cadena_2.cadena_.empty()) {
    return cadena_1;
  }

  return Cadena{cadena_1.cadena_ + cadena_2.cadena_};
}

/**
 * @brief Funcion encargada de comprobar que una cadena es subcadena de otra
 *
 * @param subcadena Objeto cadena a comprar si es subcadena de otra
 */
bool Cadena::EsSubcadena(const Cadena& subcadena) const {
  if (subcadena.cadena_ == "") return true;
  return cadena_.find(subcadena.cadena_) != std::string::npos;
}

/**
 * Sobrecarga del operador de potencia '^' para devolver la concatenación
 * sucesiva de la cadena n veces
 *
 * @param cadena_1 Cadena a concatenar
 * @param exponente Entero que representa el número de veces que se concatena la
 * cadena
 */
Cadena operator^(const Cadena& cadena_1, int exponente) {
  if (exponente <= 0) {
    return Cadena{""};
  }

  if (exponente == 1 || cadena_1.cadena_ == "") {
    return cadena_1;
  }

  std::string resultado{};

  for (int i{1}; i <= exponente; ++i) {
    resultado += cadena_1.cadena_;
  }

  return resultado;
}

/**
 * @brief Funcion que dado una cadena comprueba si esta es palíndroma o no
 */
bool Cadena::EsPalindromo() const {
  int j = static_cast<int>(cadena_.size()) - 1;

  for (int i{0}; i < (static_cast<int>(cadena_.size())); ++i) {
    if (cadena_[i] != cadena_[j]) {
      return false;
    }
    j -= 1;
  }
  return true;
}

/**
 * @brief Sobrecarga del operador [] con el objetivo de acceder a los elementos
 * de una posicion de una cadena
 *
 * @param posicion Entero que nos dice a que posicion queremos acceder
 */
char Cadena::operator[](int posicion) const { return cadena_[posicion]; }