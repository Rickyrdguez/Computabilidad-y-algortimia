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
// Archivo p04_html_analyzer.cc: programa cliente que recibe por línea de comandos un
// fichero HTML de entrada y un fichero de salida, analiza el HTML y escribe
// un resumen de su estructura.
//
// Historial de revisiones
// 05/10/2026 - Creación (primera versión) del código
// 05/10/2026 - Última modificación

#include "clases.h"

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string{argv[1]} == "--help") {
        MostrarAyuda();
        return 0;
    }

    if (argc != 3) {
        MostrarUso();
        return -1;
    }

    std::string direccion_entrada{argv[1]};
    std::string direccion_salida{argv[2]};

    std::ofstream out(direccion_salida);

    if (!out) {
        std::cout << "No se ha podido abrir el documento " << direccion_salida << ".\n";
        MostrarAyuda();
        return 1;
    }

    HtmlAnalyzer html;
    html.SetFichero(direccion_entrada);
    html.Analizador();
    out << html.GetDocumento();

    return 0;
  }