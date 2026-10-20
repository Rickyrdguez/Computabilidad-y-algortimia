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
// Archivo p06_DFA_simulation.cc: programa principal del simulador. Lee la
// definición de un DFA desde un fichero .dfa y simula su comportamiento con
// las cadenas de un fichero .txt.
//
// Uso: ./p06_DFA_simulator input.dfa input.txt
//
// Historial de revisiones
// 17/10/2026 - Creación (primera versión) del código
// 21/10/2026 - Última modificación

#include "dfa.h"

int main(int argc, char* argv[]) {
  if (argc == 2 && std::string{argv[1]} == "--help") {
    MostrarAyuda();
    return 0;
  }

  if (argc != 3) {
    MostrarUso();
    return 1;
  }

  std::string direccion_dfa{argv[1]};
  std::string direccion_entrada{argv[2]};

  std::ifstream inp_dfa(direccion_dfa);

  if (!inp_dfa.is_open()) {
    std::cerr
        << "ERROR: No se pudo abrir el fichero de especificación del DFA: "
        << direccion_dfa << "\n";
    return 1;
  }

  std::ifstream inp_txt(direccion_entrada);
  if (!inp_txt.is_open()) {
    std::cerr << "ERROR: No se pudo abrir el fichero de cadenas de entrada: "
              << direccion_entrada << "\n";
    return 1;
  }

  Automata automata;
  inp_dfa >> automata;

  if (automata.getter_invalido()) {
    std::cerr << "ERROR: El autómata es inválido o no compatible. Se finaliza "
                 "la ejecución del programa.\n";
    return 1;
  }

  std::cout << automata;

  std::string cadena;
  while(std::getline(inp_txt, cadena)) {
    if(!cadena.empty() && cadena.back() == '\r') {
      cadena.pop_back();
    }

    automata.ComprobarCadena(cadena);
    std::cout << "\n";
  }

  return 0;
}