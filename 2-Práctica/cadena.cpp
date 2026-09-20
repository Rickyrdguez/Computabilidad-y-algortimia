/**
 *   ;

  ;
  Lenguaje ConjuntoSufijos() const;
  Lenguaje PosiblesSubcadenas() const;

  private:
  std::string cadena_;
};
 */

#include <iostream>
#include <set>
#include <string>

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