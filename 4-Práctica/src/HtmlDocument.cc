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
// Archivo HtmlDocument.cc: fichero con la implementación de los métodos de la
// clase HtmlDocument y de la sobrecarga de su operador de salida.
//
// Historial de revisiones
// 05/10/2026 - Creación (primera versión) del código
// 07/10/2026 - Última modificación
// Resaltando lo siguiente: Sesión de evaluación . Encontrará las modificaciones

#include "clases.h"

/**
 * @brief Sobrecarga del operador del flujo de salida del programa
 *
 * @param os Flujo de salida
 * @param documento Objeto de la clase HtmlDocument
 */
std::ostream& operator<<(std::ostream& os, const HtmlDocument& documento) {
  os << "PROGRAM: " << documento.nombre_fichero_ << "\n";
  os << "\n";

  os << "DESCRIPTION:\n";
  if (!documento.comentarios_.empty() &&
      documento.comentarios_[0].EsDescripcion()) {
    for (size_t i{0};
         i < documento.comentarios_[0].GetContenidoComentario().size(); ++i) {
      os << documento.comentarios_[0].GetContenidoComentario()[i] << "\n";
    }
  }
  os << "\n";

  os << "STRUCTURE:\n";
  os << "HTML: " << (documento.html_ ? "True" : "False") << "\n";
  os << "HEAD: " << (documento.head_ ? "True" : "False") << "\n";
  os << "BODY: " << (documento.body_ ? "True" : "False") << "\n";
  os << "DOCTYPE: " << documento.doctype_ << "\n";
  os << "\n";

  os << "TAGS:\n";
  for (size_t i{0}; i < documento.etiquetas_.size(); ++i) {
    os << documento.etiquetas_[i];
  }
  os << "\n";

  os << "ATTRIBUTES:\n";
  for (size_t i{0}; i < documento.etiquetas_.size(); ++i) {
    if (!documento.etiquetas_[i].DevolverLista().empty()) {
      os << documento.etiquetas_[i];
      for (size_t j{0}; j < documento.etiquetas_[i].DevolverLista().size();
           ++j) {
        os << documento.etiquetas_[i].DevolverLista()[j];
      }
      os << "\n";
    }
  }

  os << "COMMENTS:\n";
  for (size_t i{0}; i < documento.comentarios_.size(); ++i) {
    os << documento.comentarios_[i];
    if (i != (documento.comentarios_.size() - 1)) {
      os << "\n\n";
    }
  }

  // SESIÓN DE EVALUACIÓN

  os << "\nLINKS:\n";
  for (const Link& enlace : documento.enlaces_) {
    os << "[Line " << enlace.linea << "]\n"
       << "PROTOCOL: " << enlace.protocolo << "\n"
       << "TEXT: " << enlace.texto << "\n";
  }

  return os;
}

/**
 * @brief Función encargada de añadir las etiquetas al vector etiquetas de la
 * clase html
 *
 * @param etiqueta Objeto de la clase Tag
 */
void HtmlDocument::AniadirEtiquetas(const Tag& etiqueta) {
  etiquetas_.push_back(etiqueta);
}

/**
 * @brief Función encargada de añadir los comentarios al vector comentarios de
 * la clase html
 *
 * @param comSesión de evaluaciónentarios Objeto de la clase Comment
 */
void HtmlDocument::AniadirComentarios(const Comment& comentario) {
  comentarios_.push_back(comentario);
}

// SESIÓN DE EVALUACIÓN

/**
 * @brief Función encargada de añadir los enlaces al vector enlaces de la
 * clase html
 *
 * @param enlace Objeto de la clase Link
 */
void HtmlDocument::AniadirEnlace(const Link& enlace) {
  enlaces_.push_back(enlace);
}
