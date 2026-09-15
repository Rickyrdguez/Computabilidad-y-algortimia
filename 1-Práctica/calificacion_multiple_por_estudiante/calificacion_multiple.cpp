// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 1: Contenedores asociativos
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 13/09/2023
// Archivo calificacion_multiple.cpp: funciones de la clase
//
// Historial de revisiones
// 12/09/2023 - Creación (primera versió) del código

#include "calificacion_multiple.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

/**
 * @brief Función encargada de procesar los datos del fichero
 *
 * @param usuario String que contiene el nombre de usuario
 * @param nota Double que contiene el valor de la nota obtenida por el usuario
 */
void CalificacionMultiple::ProcesaDatos(const std::string& usuario,
                                        double nota) {
  calificaciones_.insert(std::pair<std::string, double>(usuario, nota));
}

/**
 * @brief Función encargada de abrir y leer los contenidos de un fichero
 *
 * @param nombre_fichero String que indica el nombre del fichero
 */
void CalificacionMultiple::EntradaFichero(const std::string& nombre_fichero) {
  std::ifstream entrada{nombre_fichero};

  if (!entrada.is_open()) {
    std::cerr << "Ha ocurrido un error al abrir el archivo, por favor "
                 "intentelo de nuevo\n";
    return;
  }

  std::string usuario{};
  double nota{0.0};

  while (entrada >> usuario >> nota) {
    ProcesaDatos(usuario, nota);
  }
}

/**
 * @brief Función encarga de mostrar por pantalla todas las notas de un usuario
 */
void CalificacionMultiple::MostrarPorPantalla() const {
  std::multimap<std::string, double>::const_iterator iterador =
      calificaciones_.begin();

  std::string alu_actual{};

  while (iterador != calificaciones_.end()) {
    alu_actual = iterador->first;
    std::cout << alu_actual << ": ";
    auto rango = calificaciones_.equal_range(alu_actual);

    for (auto it = rango.first; it != rango.second; ++it) {
      std::cout << it->second << " ";
    }

    std::cout << std::endl;
    iterador = rango.second;
  }
}

/**
 * @brief Funcion que comprueba si la entrada introducida por el usuario es
 * "--help" y en ese caso muestra por pantalla una guía de uso del programa
 *
 * @param entrada_del_programa String que introduce el usuario
 */
void CalificacionMultiple::GuiaDelPrograma(
    const std::string& entrada_del_programa) const {
    std::cout << "Uso: p01_multiple_grades <fichero.txt>\n\n";
    std::cout << "Este programa lee un fichero de calificaciones y muestra,\n";
    std::cout << "para cada estudiante, todas sus notas.\n\n";
    std::cout
        << "Formato del fichero de entrada (una linea por calificacion):\n";
    std::cout << "  aluXXXXXXXXXX nota\n";
    std::cout << "Ejemplo:\n";
    std::cout << "  alu0122334455 5.25\n";
    std::cout << "Este programa da la opción de añadir usuarios y notas de "
                 "forma manual\n";
    std::cout << "Para ello, cuando se lo pida pinche la tecla 'a' y añada el "
                 "usuario seguido de la nota\n\n";
    std::cout << "Para salir de ese menú, pinche la tecla 'q' y saldrá del "
                 "programa \n";
  }