// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 05/10/2026
//
// Archivo Comment.cc: fichero con la implementación de la sobrecarga del
// operador de salida de la clase Comment.
//
// Historial de revisiones
// 05/10/2026 - Creación (primera versión) del código
// 05/10/2026 - Última modificación

#include "clases.h"

/**
 * @brief Sobrecarga del operador del flujo de salida de la clase Comment
 *
 * @param os Flujo de salida
 * @param comment Objeto de la clase comment
 */
std::ostream& operator<<(std::ostream& os, const Comment& comment) {
  const std::vector<std::string>& comentario = comment.GetContenidoComentario();

  os << "[Line " << comment.GetInicioComentario();

  if (comment.GetInicioComentario() != comment.GetFinalComentario()) {
    os << "-" << comment.GetFinalComentario();
  } 
    
  os << "]";

  if (comment.EsDescripcion()) {
    os << " DESCRIPTION";
  }

  if (comment.GetInicioComentario() == comment.GetFinalComentario()) {
    os << "\n<!--";
    for (size_t i{0}; i < comentario.size(); ++i) {
      os << comentario[i];
    }
    os << "-->\n";
  } else {
    os << "\n<!--\n";
    for (size_t i{0}; i < comentario.size(); ++i) {
      os << comentario[i] << "\n";
    }
    os << "-->\n";
  }

  return os;
}