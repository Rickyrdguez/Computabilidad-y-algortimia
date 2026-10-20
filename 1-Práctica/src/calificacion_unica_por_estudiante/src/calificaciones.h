// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 1: Contenedores asociativos
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 13/09/2023
// Archivo calificaciones.h: declaracion de las funciones de la clase
//
// Historial de revisiones
// 12/09/2023 - Creación (primera versió) del código

#ifndef CALIFICACIONES_H
#define CALIFICACIONES_H

#include <map>
#include <string>

class Calificaciones {
 public:
  void LeerArchivo(const std::string& nombre_fichero);
  void InsertarDatos(const std::string& usuario, double notas);
  void MostrarPorPantalla() const;
  void ExplicacionDelPrograma(const std::string& entrada_del_programa) const;

  // Sesión de práctica
  void ConsultaAlumnoConcreto(const std::string& usuario) const;
  bool ComprobarExisteEstudiante(const std::string& usuario);

 private:
  std::map<std::string, double> calificaciones_;
};

#endif  // CALIFICACIONES_H