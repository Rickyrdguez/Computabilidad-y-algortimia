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
// Archivo dfa.h: fichero con la declaración de la clase Automata, que modela
// un autómata finito determinista (DFA).
//
// Historial de revisiones
// 17/10/2026 - Creación (primera versión) del código
// 21/10/2026 - Última modificación

#ifndef DFA_H_
#define DFA_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>


void MostrarUso();
void MostrarAyuda();

class Automata {
 public:
  Automata() {};
  void ComprobarCadena(const std::string& cadena) const;
  bool getter_invalido() const { return automata_invalido_; }

  // Sobrecarga del operador para el flujo de salida y entrada de autómata
  friend std::ostream& operator<<(std::ostream& os, const Automata& automata);
  friend std::istream& operator>>(std::istream& is, Automata& automata);

  // Sobrecarga del operador del flujo de salida de std::set<char> alfabeto_
  friend std::ostream& operator<<(std::ostream& os,
                                  const std::set<char>& alfabeto);

  // Sobrecarga del operador del flujo de salida de estados de aceptacion
  friend std::ostream& operator<<(std::ostream& os,
                                  const std::set<int>& estados_aceptacion);

  // Sobrecarga del operador del flujo de salida para funcion_transicion_
  friend std::ostream& operator<<(
      std::ostream& os,
      const std::map<std::pair<int, char>, int>& funcion_transicion_);

  // ESTUDIO PARA LA PRÁCTICA
  std::vector<int> EstadosBucle() const;
  std::vector<int> EstadosAbsorcion() const;
  void HacerComplementario();

  // SESIÓN DE EVALUACIÓN
  bool Acepta(const std::string& cadena) const;
  void GenerarCadenas(int numero_n) const;

 private:
  int cantidad_de_estados_{0};
  std::set<char> alfabeto_;
  int estado_arranque_{-1};
  std::set<int> estados_aceptacion_;
  std::map<std::pair<int, char>, int> funcion_transicion_;
  bool automata_invalido_{false};
}; 

#endif  // DFA_H_