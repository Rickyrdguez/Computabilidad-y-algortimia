// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo Jesús Rodríguez Pérez
// Correo: alu0101797557@ull.edu.es
// Fecha: 16/09/2026
//
// Archivo alfabeto.cpp: implementación de los métodos de la clase Alfabeto.
//
// Historial de revisiones
// 16/09/2026 - Creación (primera versión) del código
// 21/09/2026 - Última modificación

#include "p02_string.h"

/**
 * @brief Función encargada de mostrar el funcionamiento y manual del programa
 */
void FuncionamientoDelPrograma() {
  std::cout << R"(
  Programa: p02_strings
  
  Este programa lee un fichero de texto donde en cada línea deberá de aparecer
  una cadena y su alfabeto correspondiente (separados por un espacio) y en
  función del opcode realizará una acción distinta.
  
  USO CORRECTO DEL PROGRAMA:
  ./p02_strings <fichero_entrada.txt> <fichero_salida.txt> <opcode>
  
  FORMATO DEL FICHERO DE ENTRADA:
    cadena alfabeto
    Ejemplo: hola ahlo
    Nota: el símbolo '&' representa la cadena vacía

  CÓDIGOS DE OPERACION (opcode):
    '1' : Alfabeto    - Escribe el alfabeto asociado a la cadena.
    '2' : Longitud    - Calcula y devuelve la longitud de la cadena.
    '3' : Inversa     - Genera y devuelve la inversa de la cadena. 
    '4' : Prefijos    - Genera y devuelve todos los prefijos posibles de la cadena.
    '5' : Sufijos     - Genera y devuelve todos los sufijos posibles de la cadena.
    '6' : Validación  - Comprueba si la cadena está en el afabeto (OK/ERROR).
    '7' : Exponente   - Dado un número devuelve la concatenación de una cadena n veces.
                      - la entrada debe de ser ./p02_strings <fichero_entrada.txt> <fichero_salida.txt> <opcode> <exponente>

  )";
}

/**
 * @brief Constructor del tipo alfabeto
 *
 * @param cadena String que contiene la cadena de símbolos
 */
Alfabeto::Alfabeto(const std::string& cadena) { InsertarEnAlfabeto(cadena); }

/**
 * @brief Función encargada de insertar los simbolos en un alfabeto
 *
 * @param cadena String que contiene la cadena de símbolos
 */
void Alfabeto::InsertarEnAlfabeto(const std::string& cadena) {
  for (char iterador : cadena) {
    if (iterador != '&') {
      alfabeto_.insert(iterador);
    }
  }
}

/**
 * @brief Función que comprueba si un simbolo de una cadena no pertence al
 * alfabeto
 *
 * @param cadena String que contiene la cadena de símbolos a analizar
 */
bool Alfabeto::ComprobarPertenceAlfabeto(char simbolo) const {
  return alfabeto_.find(simbolo) != alfabeto_.end();
}

/**
 * @brief Sobrecarga del operador de salida del programa
 *
 * @param os Operador de salida
 * @param alfabeto Obejto de la alfabeto
 */
std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto) {
  bool primer_elemento = true;

  os << "{";

  for (char caracter : alfabeto.alfabeto_) {
    if (primer_elemento == false) {
      os << ", " << caracter;
    } else {
      os << caracter;
      primer_elemento = false;
    }
  }
  os << "}\n";

  return os;
}

/**
 * @brief Sobrecarga del flujo de insercción del programa
 *
 * @param is Flujo de entrada del programa
 * @param alfabeto Objeto de la clase alfabeto
 */
std::istream& operator>>(std::istream& is, Alfabeto& alfabeto) {
  std::string simbolos;

  if (is >> simbolos) {
    alfabeto.InsertarEnAlfabeto(simbolos);
  }

  return is;
}

// Estudio para la sesión práctica

/**
 * @brief Sobrecarga del operador '+' que permite la union de dos alfabetos
 *
 * @param alfabeto_1 Primer objeto alfabeto
 * @param alfabeto_2 Segundo objeto alfabeto
 */
Alfabeto operator+(const Alfabeto& alfabeto_1, const Alfabeto& alfabeto_2) {
  if (alfabeto_1.alfabeto_.empty()) {
    return alfabeto_2;
  }
  if (alfabeto_2.alfabeto_.empty()) {
    return alfabeto_1;
  }

  Alfabeto resultado;

  for (char caracter : alfabeto_1.alfabeto_) {
    resultado.alfabeto_.insert(caracter);
  }

  for (char caracter : alfabeto_2.alfabeto_) {
    resultado.alfabeto_.insert(caracter);
  }
  return resultado;
}