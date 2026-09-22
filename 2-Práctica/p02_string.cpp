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
// Archivo p02_string.cpp: programa cliente. Contiene la función main que lee
// el fichero de entrada, aplica la operación indicada por el opcode a cada
// cadena y escribe el resultado en el fichero de salida.
//
// Historial de revisiones
// 16/09/2026 - Creación (primera versión) del código
// 21/09/2026 - Última modificación

#include "p02_string.h"

int main(int argc, char* argv[]) {
  if (argc == 2 && std::string{argv[1]} == "--help") {
    FuncionamientoDelPrograma();
    return 0;
  }

  if (argc <= 3 || argc > 5) {
    std::cout << R"(
    Modo de empleo: ./p02_strings <filein.txt> <fileout.txt> <opcode> <palabra>
    Pruebe: './p02_strings --help' para más información
    )";
    return 0;
  }

  std::ifstream fichero_entrada{argv[1]};
  std::ofstream fichero_salida{argv[2]};
  int opcode{std::stoi(argv[3])};

  if (!fichero_entrada.is_open()) {
    std::cerr << "Ha ocurrido un error al abrir " << argv[1]
              << " inténtelo de nuevo\n";
    return -1;
  }
  if (!fichero_salida.is_open()) {
    std::cerr << "Ha ocurrido un error al abrir " << argv[2]
              << " inténtelo de nuevo\n";
    return -1;
  }

  std::string linea;

  while (std::getline(fichero_entrada, linea)) {
    std::istringstream flujo{linea};
    Cadena cadena;
    Alfabeto alfabeto;

    if (flujo >> cadena >> alfabeto) {
      switch (opcode) {
        case 1:
          fichero_salida << cadena << ": " << alfabeto << "\n";
          break;

        case 2:
          fichero_salida << cadena.LongitudCadena() << "\n";
          break;

        case 3:
          fichero_salida << cadena << " -> " << cadena.CadenaInversa() << "\n";
          break;

        case 4:
          fichero_salida << cadena.ConjuntoPrefijos() << "\n";
          break;

        case 5:
          fichero_salida << cadena.ConjuntoSufijos() << "\n";
          break;

        case 6:
          fichero_salida << (cadena.Validacion(alfabeto) ? "OK" : "ERROR")
                         << "\n";
          break;

        case 7: {
          std::string cadena_introducida{argv[4]};
          fichero_salida << cadena << ": " << cadena + cadena_introducida
                         << "\n";
          break;
        }

        default:
          std::cout << "Error: Código de operación (opcode) no válido.\n";
          FuncionamientoDelPrograma();
          return -1;
      }
    }
  }

  return 0;
}