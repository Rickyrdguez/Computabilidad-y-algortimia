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
// Archivo tag.cc: fichero con la implementación de los métodos de la clase
// Tag y de la sobrecarga de su operador de salida.
//
// Historial de revisiones
// 05/10/2026 - Creación (primera versión) del código
// 05/10/2026 - Última modificación

#include "clases.h"

/**
 * @brief Función que añade un atributo de etiquetas html
 * 
 * @param nombre String que contiene el nombre del atributo 
 * @param contenido String que contiene el contenido del atributo
 */
void Tag::AniadirAtributo(const std::string& nombre, const std::string& contenido) {
  atributo_.push_back(Attribute(nombre, contenido));
}

/**
 * @brief Sobrecarga del operador del flujo de salida
 * 
 * @param os Flujo de salida 
 * @param tag Objeto tag
 */
std::ostream& operator<<(std::ostream& os, const Tag& tag) {
  os << "[Line " << tag.GetLinea() << "]" << " ";
  
  if(tag.EsCierre()) {
    os << "/";
  }

  os << tag.GetEtiqueta() << "\n";

  return os;
}

/**
 * @brief Función que devuelve el vector de atributos de la clase Tag
 */
const std::vector<Attribute>& Tag::DevolverLista() const {
  return atributo_;
}