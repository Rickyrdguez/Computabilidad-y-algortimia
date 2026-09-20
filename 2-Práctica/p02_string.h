// Universidad de La Laguna
// Escuela Superior de Ingenierı́a y Tecnologı́a
// Grado en Ingenierı́a Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 16/09/2025
// Archivo cya-P02-strings.cc: programa cliente.
//
// Contiene la función main del proyecto que usa las clases X e Y
//
// para ... (indicar brevemente el objetivo)
// Referencias:
//
// Enlaces de interés
//
// Historial de revisiones
//
// 18/09/2026 - Creación (primera versión) del código

#ifndef P02_STRING_H
#define P02_STRING_H

#include <iostream>
#include <set>
#include <string>


void FuncionamientoDelPrograma(); // Se encuentra en alfabeto.cpp

class Alfabeto {
 public:
  // Constructor
  Alfabeto() {};
  Alfabeto(const std::string& cadena);

  // Sobrecarga de operadores
  friend std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto);
  friend std::istream& operator>>(std::istream& is, Alfabeto& alfabeto);

  // Métodos de la clase
  bool ComprobarPertenceAlfabeto(char simbolo) const;
  void InsertarEnAlfabeto(const std::string& cadena);

 private:
  std::set<char> alfabeto_;
};

class Lenguaje;

class Cadena {
 public:
  // Constructor
  Cadena() {}
  Cadena(const std::string& cadena) : cadena_{cadena} {}

  // Sobrecarga de operadores
  friend std::ostream& operator<<(std::ostream& os, const Cadena& cadena);
  friend std::istream& operator>>(std::istream& is, Cadena& cadena);
  friend bool operator<(const Cadena& cadena1, const Cadena& cadena2);

  // Métodos de la clase
  int LongitudCadena() const;
  std::string CadenaInversa() const;
  Lenguaje ConjuntoPrefijos() const;
  Lenguaje ConjuntoSufijos() const;
  bool Validacion(const Alfabeto& alfabeto) const;

 private:
  std::string cadena_;
};

class Lenguaje {
 public:
  // Constructor
  Lenguaje() {}

  // Sobrecarga de operadores
  friend std::ostream& operator<<(std::ostream& os, const Lenguaje& lenguaje);

  // Métodos de la clase
  void InsertarEnLenguaje(const Cadena& cadena);

 private:
  std::set<Cadena> lenguaje_;
};

#endif  // P02_STRING_H
