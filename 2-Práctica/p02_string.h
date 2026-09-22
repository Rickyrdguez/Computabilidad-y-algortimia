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
// Archivo p02_string.h: fichero de cabecera con la definición de las clases
// Alfabeto, Cadena y Lenguaje.
//
// Historial de revisiones
// 16/09/2026 - Creación (primera versión) del código
// 21/09/2026 - Última modificación

#ifndef P02_STRING_H
#define P02_STRING_H

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

void FuncionamientoDelPrograma();  // Se encuentra en alfabeto.cpp

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

  // Estudio para la sesión práctica
  friend Alfabeto operator+(const Alfabeto& alfabeto_1,
                            const Alfabeto& alfabeto_2);

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

  // Estudio para la sesión de evaluación
  friend bool operator==(const Cadena& cadena_1, const Cadena& cadena_2);
  friend Cadena operator+(const Cadena& cadena_1, const Cadena& cadena_2);
  bool EsSubcadena(const Cadena& subcadena) const;
  friend Cadena operator^(const Cadena& cadena_1, int exponente);
  bool EsPalindromo() const;
  char operator[](int posicion) const;

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

  // Estudio para la sesión de evaluación
  friend Lenguaje operator+(const Lenguaje& lenguaje1,
                            const Lenguaje& lenguaje2);
  friend Lenguaje operator^(const Lenguaje& lenguaje, int exponente);
  Lenguaje Union(const Lenguaje& lenguaje) const;
  Lenguaje CierreKleene(int max_potencia) const;
  Lenguaje CierrePositivo(int max_potencia) const;

 private:
  std::set<Cadena> lenguaje_;
};

#endif  // P02_STRING_H