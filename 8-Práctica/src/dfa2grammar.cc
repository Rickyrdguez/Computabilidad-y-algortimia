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