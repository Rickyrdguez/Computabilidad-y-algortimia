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
// Archivo Attribute.cc: fichero con la implementación de la sobrecarga del
// operador de salida de la clase Attribute.
//
// Historial de revisiones
// 05/10/2026 - Creación (primera versión) del código
// 05/10/2026 - Última modificación

#include "clases.h"

/**
 * @brief Muestra el modo correcto de ejecución del programa.
 */
void MostrarUso() {
  std::cout << "Modo de uso: ./ExpresionesRegulares <fichero_entrada.html> "
               "<fichero_salida.txt>\n"
            << "Pruebe './ExpresionesRegulares --help' para mas informacion.\n";
}

/**
 * @brief Muestra la ayuda detallada del programa.
 */
void MostrarAyuda() {
  std::cout
      << "Analizador de codigo HTML mediante Expresiones Regulares.\n\n"
      << "USO:\n"
      << "  ./ExpresionesRegulares <fichero_entrada.html> "
         "<fichero_salida.txt>\n\n"
      << "PARAMETROS:\n"
      << "  <fichero_entrada.html>  Archivo de texto con codigo HTML "
         "sintacticamente correcto a analizar.\n"
      << "  <fichero_salida.txt>    Archivo de texto donde se generara el "
         "resumen de la estructura (etiquetas, atributos y comentarios).\n";
}

/**
 * @brief Sobrecarga del flujo de salida de la clase atributo
 *
 * @param os Flujo de salida
 * @param atributo Objeto atributo
 */
std::ostream& operator<<(std::ostream& os, const Attribute& atributo) {
  os << atributo.GetNombre() << " = " << '"' << atributo.GetContenido() << '"'
     << "\n";

  return os;
}