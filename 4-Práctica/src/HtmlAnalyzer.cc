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
// Archivo HtmlAnalyzer.cc: fichero con la implementación de los métodos de la
// clase HtmlAnalyzer, que analiza un fichero HTML mediante expresiones
// regulares.
//
// Historial de revisiones
// 05/10/2026 - Creación (primera versión) del código
// 07/10/2026 - Última modificación
// Resaltando lo siguiente: Sesión de evaluación . Encontrará las modificaciones

#include "clases.h"

/**
 * @brief Función que indica que tipo de DOCTYPE está usando el fichero de
 * entrada
 *
 * @param contenido String a analizar
 */
void HtmlAnalyzer::DetectarDoctype(const std::string& contenido,
                                   int numero_linea) {
  std::regex expresion{"<!DOCTYPE html>"};

  if (std::regex_match(contenido, expresion)) {
    documento_.SetDoctype("HTML5");
    linea_doctype_ = numero_linea;
  }
}

/**
 * @brief Función encargada de procesar todas las etiquetas del archivo
 *
 * @param contenido String a analizar
 * @param numero_linea Número de línea donde empieza
 */
void HtmlAnalyzer::DetectarEtiquetas(const std::string& contenido,
                                     int numero_linea) {
  std::regex etiquetas{"<(/?)(html|head|title|body|h1|p|a|img)(.*?)>"};
  std::regex atributos{"(\\w+)=\"([^\"]*)"};
  std::string etiqueta_de_cierre, etiqueta_de_atributos;

  for (std::sregex_iterator it{contenido.begin(), contenido.end(), etiquetas};
       it != std::sregex_iterator{}; ++it) {
    std::string etiqueta = (*it)[2].str();
    etiqueta_de_cierre = (*it)[1].str();
    etiqueta_de_atributos = (*it)[3].str();
    bool cierre = !etiqueta_de_cierre.empty();

    Tag tag{etiqueta, numero_linea, cierre};

    for (std::sregex_iterator it2{etiqueta_de_atributos.begin(),
                                  etiqueta_de_atributos.end(), atributos};
         it2 != std::sregex_iterator{}; ++it2) {
      tag.AniadirAtributo((*it2)[1].str(), (*it2)[2].str());
    }

    documento_.AniadirEtiquetas(tag);

    if (etiqueta == "html") {
      documento_.SetHtml();
    } else if (etiqueta == "head") {
      documento_.SetHead();
    } else if (etiqueta == "body") {
      documento_.SetBody();
    }
  }
}

/**
 * @brief Función encargada de procesar si estamos dentro de un comentario
 *
 * @param contenido String con las palabras a analizar
 * @param numero_linea Numero de linea donde comienza el comentario
 */
void HtmlAnalyzer::DetectarComentario(const std::string& contenido,
                                      int numero_linea) {
  std::regex inicio{"<!--"};
  std::regex final{"-->"};
  std::regex cualquiera{"<!--|-->"};

  if (std::regex_search(contenido, inicio)) {
    dentro_comentario_ = true;
    inicio_comentario_ = numero_linea;
  }

  if (dentro_comentario_ == true) {
    std::string limpia = std::regex_replace(contenido, cualquiera, "");

    if (!limpia.empty()) {
      contenido_comentario_.push_back(limpia);
    }
  }

  if (std::regex_search(contenido, final)) {
    dentro_comentario_ = false;
    if (inicio_comentario_ == linea_doctype_ + 1) {
      descripcion_ = true;
    } else {
      descripcion_ = false;
    }

    Comment comentario{inicio_comentario_, numero_linea, contenido_comentario_,
                       descripcion_};
    contenido_comentario_.clear();
    documento_.AniadirComentarios(comentario);
  }
}

// SESIÓN DE EVALUACIÓN

/**
 * @brief Función encargada de detectar los enlaces y extraer su protocolo y
 * su texto mediante grupos de captura
 *
 * @param contenido String a analizar
 * @param numero_linea Número de línea donde aparece la etiqueta <a>
 */
void HtmlAnalyzer::DetectarEnlaces(const std::string& contenido,
                                   int numero_linea) {
  std::regex enlace{"<a\\s[^>]*href=\"(\\w+)://[^\"]*\"[^>]*>(.*?)</a>"};

  for (std::sregex_iterator it{contenido.begin(), contenido.end(), enlace};
       it != std::sregex_iterator{}; ++it) {
    documento_.AniadirEnlace({numero_linea, (*it)[1].str(), (*it)[2].str()});
  }
}

/**
 * @brief Función encargada de abrir el archivo y analizarlo
 */
void HtmlAnalyzer::Analizador() {
  std::ifstream entrada{fichero_entrada_};

  if (!entrada.is_open()) {
    return;
  }

  int numero_linea{0};
  std::string contenido{};

  while (std::getline(entrada, contenido)) {
    numero_linea += 1;
    DetectarDoctype(contenido, numero_linea);
    DetectarEtiquetas(contenido, numero_linea);
    DetectarComentario(contenido, numero_linea);
    // Sesión de evaluación
    DetectarEnlaces(contenido, numero_linea);
  }
}