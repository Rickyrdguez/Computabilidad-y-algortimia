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
// Archivo dfa2grammar.cc: programa principal. Lee la especificación de un DFA
// desde un fichero .dfa y genera en un fichero .gra una gramática regular que
// genera el lenguaje reconocido por el autómata.
//
// Uso: ./dfa2grammar input.dfa output.gra
//
// Historial de revisiones
// 02/11/2026 - Creación (primera versión) del código
// 04/11/2026 - Última modificación

#include "clases.h"

int main(int argc, char* argv[]) {
  if (argc == 2 && std::string{argv[1]} == "--help") {
    MostrarAyuda();
    return 0;
  }

  if (argc != 3) {
    MostrarUso();
    return 1;
  }

  Automata automata{argv[1]};

  if (automata.EsInvalido()) {
    std::cerr << "ERROR: El autómata es inválido. Se finaliza la ejecución "
                 "del programa.\n";
    return 1;
  }

  if (!automata.EsDFA()) {
    std::cerr << "ERROR: El autómata no es determinista (DFA). Solo se puede "
                 "generar la gramática a partir de un DFA.\n";
    return 1;
  }

  const Grammar gramatica = automata.ConvertToGrammar();
  gramatica.EscribirEnFichero(argv[2]);

  return 0;
}