// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 1: Contenedores asociativos
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 13/09/2023
// Archivo cya_P01_single_grades.cc: programa cliente.
// Contiene la función main del proyecto que usa la clase CalificacionMultiple
//
// Historial de revisiones
// 12/09/2023 - Creación (primera versió) del código

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
  Calificaciones calificaciones;

  calificaciones.ExplicacionDelPrograma(entrada);
  calificaciones.LeerArchivo(argv[1]);
  calificaciones.MostrarPorPantalla();

  return 0;
}