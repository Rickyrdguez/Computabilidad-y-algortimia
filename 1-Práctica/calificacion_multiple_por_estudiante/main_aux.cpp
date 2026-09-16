// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 1: Contenedores asociativos
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 13/09/2023
// Archivo cya_P01_multiple_grades.cc: programa cliente.
// Contiene la función main del proyecto que usa la clase CalificacionMultiple
//
// Historial de revisiones
// 12/09/2023 - Creación (primera versió) del código

#include <iostream>
#include <string>

#include "calificacion_multiple.h"

int main(int argc, char* argv[]) {
  CalificacionMultiple calificaciones;

  if (argc < 2) {
    std::cout << "Modo de empleo: " << argv[0] << " <nombre_del_archivo.txt>\n";
    std::cout << "Pruebe '" << argv[0] << " --help' para mas informacion.\n";
    return -1;
  } else if (argc == 2) {
    std::string entrada = argv[1];

    if (entrada == "--help") {
      calificaciones.GuiaDelPrograma(entrada);
      return 0;
    } else {
      calificaciones.EntradaFichero(entrada);
      calificaciones.MostrarPorPantalla();
      std::cout << "\n";

      char opcion = 'a';
      std::string usuario{};
      double nota{0.0};

      while (opcion != 'q') {
        std::cout
            << "Si quiere añadir de forma manual un usuario pinche 'a' si "
               "quiere salir pinche 'q': ";
        std::cin >> opcion;

        switch (opcion) {
          case 'a':
            std::cout << "Añada <usuario> <nota>: ";
            std::cin >> usuario >> nota;

            calificaciones.ProcesaDatos(usuario, nota);
            calificaciones.MostrarPorPantalla();
            break;

          case 'q':
            break;
        }
        std::cout << "\n";
      }
    }
  } else if (argc == 3) {
    std::string Max = argv[2];

    if (Max == "--max") {
      std::cerr << "Error, es necesario el usuario a buscar la nota máxima\n";
      return -1;
    } else {
      std::cerr << "Error, opción no conocida\n";
    }
  } else if (argc == 4) {
    std::string Max = argv[2];

    if (Max == "--max") {
      std::string usuario_nota_max = argv[3];
      std::string entrada = argv[1];
      
      calificaciones.EntradaFichero(entrada);
      calificaciones.EncontrarNotaMaxima(usuario_nota_max);
    } else {
      std::cerr << "Error, opción no conocida\n";
    }
  }
}