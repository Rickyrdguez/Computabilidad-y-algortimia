// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 1: Contenedores asociativos
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 13/09/2023
// Archivo calificacion_multiple.h: declaracion de las funciones de la clase
//
// Historial de revisiones
// 12/09/2023 - Creación (primera versió) del código

#ifndef CALIFICACION_MULTIPLE_H
#define CALIFICACION_MULTIPLE_H

#include <map>
#include <string>

class CalificacionMultiple {
 public:
  void EntradaFichero(const std::string& nombre_fichero);
  void MostrarPorPantalla() const;
  void ProcesaDatos(const std::string& usuario, double notas);
  void GuiaDelPrograma(const std::string& entrada_del_programa) const;

 private:
  std::multimap<std::string, double> calificaciones_;
};

#endif  // CALIFICACION_MULTIPLE_H