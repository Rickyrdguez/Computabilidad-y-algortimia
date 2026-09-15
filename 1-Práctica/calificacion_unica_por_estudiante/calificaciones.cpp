// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 1: Contenedores asociativos
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 13/09/2023
// Archivo calificaciones.cpp: funciones de la clase
//
// Historial de revisiones
// 12/09/2023 - Creación (primera versió) del código

#include "calificaciones.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

/**
 * @brief Función encargada encargada de comprobar si un usuario ya ha sido
 * registrado, si lo está compara las notas y se queda con la más alta, y si no
 * está, lo añade junto a su nota
 *
 * @param usuario String que contiene el nombre de usuario
 * @param nota Double que representa la nota que ha sacado el usuario
 */

void Calificaciones::InsertarDatos(const std::string& usuario, double nota) {
  std::map<std::string, double>::iterator iterador =
      calificaciones_.find(usuario);

  if (iterador != calificaciones_.end()) {
    if (nota > iterador->second) {
      iterador->second = nota;
    }
  } else {
    calificaciones_[usuario] = nota;
  }
}

/**
 * @brief Función encargada de abrir y procesar el fichero de entrada
 *
 * @param nombre_fichero String que contiene el nombre del fichero a leer
 */
void Calificaciones::LeerArchivo(const std::string& nombre_fichero) {
  std::ifstream entrada{nombre_fichero};

  if (!entrada.is_open()) {
    std::cerr << "Ha ocurrido un error al abrir el fichero\n";
    return;
  }

  std::string usuario{};
  double nota{0.0};

  while (entrada >> usuario >> nota) {
    InsertarDatos(usuario, nota);
  }
}

/**
 * @brief Función encargada de mostrar por pantalla el usuario junto con la nota
 * más alta al lado
 */
void Calificaciones::MostrarPorPantalla() const {
  for (const auto& elemento : calificaciones_) {
    std::cout << elemento.first << " " << elemento.second << std::endl;
  }
}

/**
 * @brief Función encargada de mostrar por pantalla una breve información sobre
 * como usar el programa
 */
void Calificaciones::ExplicacionDelPrograma(
    const std::string& entrada_del_programa) const {
  if (entrada_del_programa == "--help") {
    std::cout << "Uso: p01_single_grades <fichero.txt>\n\n";
    std::cout << "Este programa lee un fichero de calificaciones y muestra,\n";
    std::cout << "para cada estudiante, la nota mas alta obtenida.\n\n";
    std::cout
        << "Formato del fichero de entrada (una linea por calificacion):\n";
    std::cout << "  aluXXXXXXXXXX nota\n";
    std::cout << "Ejemplo:\n";
    std::cout << "  alu0122334455 5.25\n";

    return;
  }
}