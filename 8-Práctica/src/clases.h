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
// Archivo clases.h: fichero con la declaración de las clases Grammar y
// Automata.

#ifndef CLASES_H_
#define CLASES_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>


// Funciones que se encuentran en gramatica.cc
void MostrarUso();
void MostrarAyuda();

// Una producción de la gramática: izquierda -> derecha
struct Produccion {
  std::string izquierda;  // No terminal de la parte izquierda.
  std::string derecha;    // Símbolos de la parte derecha ("&" = cadena vacía).
};

// Gramática G = (terminales, no terminales, arranque, producciones).
class Grammar {
 public:
  // Constructor
  Grammar(const std::set<char>& terminales,
          const std::string& simbolo_arranque);

  // Métodos de la clase
  void AnadirNoTerminal(const std::string& no_terminal);
  void AnadirProduccion(const std::string& izquierda,
                        const std::string& derecha);
  void EscribirEnFichero(const std::string& nombre_fichero) const;

 private:
  std::set<char> terminales_;
  std::set<std::string> no_terminales_;
  std::string simbolo_arranque_;
  std::vector<Produccion> producciones_;
};

class Automata {
 public:
  // Constructor
  Automata(const std::string& nombre_fichero);

  // Métodos de la clase
  bool EsInvalido() const { return automata_invalido_; }
  bool EsDFA() const { return es_dfa_; }
  Grammar ConvertToGrammar() const;

  // Sobrecarga del operador del flujo de salida
  friend std::istream& operator>>(std::istream& is, Automata& automata);

 private:
  static std::string NombreNoTerminal(int estado);
  bool LeerLineaEstado(std::stringstream& flujo, int numero_linea,
                       std::set<int>& estados_vistos);                   
  int cantidad_de_estados_{0};
  std::set<char> alfabeto_;
  int estado_arranque_{-1};
  std::set<int> estados_aceptacion_;
  std::map<std::pair<int, char>, int> funcion_transicion_;
  bool automata_invalido_{false};
  bool es_dfa_{true};
};

#endif  // CLASES_H_