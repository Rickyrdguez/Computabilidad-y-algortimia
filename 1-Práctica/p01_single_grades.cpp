#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "calificaciones.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Modo de empleo: " << argv[0] << " <nombre_del_archivo.txt>\n";
    std::cout << "Pruebe '" << argv[0] << " --help' para mas informacion.\n";
    return -1;
  }

  std::string entrada{argv[1]};

  if (entrada == "--help") {
    std::cout << "Uso: p01_single_grades <fichero.txt>\n\n";
    std::cout << "Este programa lee un fichero de calificaciones y muestra,\n";
    std::cout << "para cada estudiante, la nota mas alta obtenida.\n\n";
    std::cout
        << "Formato del fichero de entrada (una linea por calificacion):\n";
    std::cout << "  aluXXXXXXXXXX nota\n";
    std::cout << "Ejemplo:\n";
    std::cout << "  alu0122334455 5.25\n";
  }

  Calificaciones calificaciones;

  calificaciones.LeerArchivo(argv[1]);
  calificaciones.MostrarPorPantalla();

  return 0;
}