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
// Archivo clases.h: fichero de cabecera con la definición de las clases
// Attribute, Tag, Comment, HtmlDocument y HtmlAnalyzer.
//
// Historial de revisiones
// 05/10/2026 - Creación (primera versión) del código
// 05/10/2026 - Última modificación

#ifndef CLASES_H_
#define CLASES_H_

#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

// Métodos que se encuentran en attribute.cc
void MostrarUso();
void MostrarAyuda();

class Attribute {
 public:
  // Constructor
  Attribute(const std::string& nombre, const std::string& contenido)
      : nombre_{nombre}, contenido_{contenido} {}

  // Getters
  std::string GetNombre() const { return nombre_; }
  std::string GetContenido() const { return contenido_; }

 private:
  std::string nombre_;
  std::string contenido_;
};

// Sobrecarga del oeprador del flujo de salida de la clase Attribute
std::ostream& operator<<(std::ostream& os, const Attribute& atributo);

/////////////////////////////////////////////////////////////////////////////

class Tag {
 public:
  // Constructor
  Tag(const std::string& etiqueta, int linea, bool etiqueta_de_cierre)
      : etiqueta_{etiqueta},
        linea_{linea},
        etiqueta_de_cierre_{etiqueta_de_cierre} {}

  // Getters
  std::string GetEtiqueta() const { return etiqueta_; }
  int GetLinea() const { return linea_; }
  bool EsCierre() const { return etiqueta_de_cierre_; }

  // Métodos de la clase
  void AniadirAtributo(const std::string& nombre, const std::string& contenido);
  const std::vector<Attribute>& DevolverLista() const;

 private:
  std::string etiqueta_;
  int linea_;
  bool etiqueta_de_cierre_;
  std::vector<Attribute> atributo_;
};

// Sobrecarga del operador del flujo de salida de la clase Tag
std::ostream& operator<<(std::ostream& os, const Tag& tag);

///////////////////////////////////////////////////////////////////////////////

class Comment {
 public:
  // Constructor
  Comment(int inicio_comentario, int final_comentario,
          const std::vector<std::string>& contenido_comentario,
          bool descripcion)
      : inicio_comentario_{inicio_comentario},
        final_comentario_{final_comentario},
        contenido_comentario_{contenido_comentario},
        descripcion_{descripcion} {}

  // Getters
  int GetInicioComentario() const { return inicio_comentario_; }
  int GetFinalComentario() const { return final_comentario_; }
  const std::vector<std::string>& GetContenidoComentario() const {
    return contenido_comentario_;
  }

  // Metodos de la clase
  bool EsDescripcion() const { return descripcion_; }

 private:
  int inicio_comentario_, final_comentario_;
  std::vector<std::string> contenido_comentario_;
  bool descripcion_;
};

// Sobrecarga del operador del flujo de salida de la clase Comment
std::ostream& operator<<(std::ostream& os, const Comment& comment);

///////////////////////////////////////////////////////////////////////////////

class HtmlDocument {
 public:
  // Constructor
  HtmlDocument(bool html = false, bool head = false, bool body = false)
      : html_{html}, head_{head}, body_{body} {}

  // Setters
  void SetHtml() { html_ = true; }
  void SetHead() { head_ = true; }
  void SetBody() { body_ = true; }
  void SetDoctype(const std::string& doctype) { doctype_ = doctype; }
  void SetNombreFichero(const std::string& nombre_fichero) {
    nombre_fichero_ = nombre_fichero;
  }

  // Sobrecarga de operadores
  friend std::ostream& operator<<(std::ostream& os,
                                  const HtmlDocument& documento);

  // Métodos de la clase
  void AniadirEtiquetas(const Tag& etiqueta);
  void AniadirComentarios(const Comment& comentario);

 private:
  std::vector<Tag> etiquetas_;
  std::vector<Comment> comentarios_;
  bool html_;
  bool head_;
  bool body_;
  std::string doctype_;
  std::string nombre_fichero_;
};

///////////////////////////////////////////////////////////////////////////////

class HtmlAnalyzer {
 public:
  HtmlAnalyzer() {}

  // Setters
  void SetFichero(const std::string& fichero_entrada) {
    fichero_entrada_ = fichero_entrada;
    documento_.SetNombreFichero(fichero_entrada);
  }

  // Getters
  const HtmlDocument& GetDocumento() const { return documento_; }

  // Métodos de la clase
  void Analizador();

 private:
  std::string fichero_entrada_;
  HtmlDocument documento_;
  std::vector<std::string> contenido_comentario_;
  bool dentro_comentario_{false};
  int inicio_comentario_{0};
  bool descripcion_{false};
  int linea_doctype_{0};

  // Métodos privados
  void DetectarDoctype(const std::string& contenido, int numero_linea);
  void DetectarEtiquetas(const std::string& contenido, int numero_linea);
  void DetectarComentario(const std::string& contenido, int numero_linea);
};

#endif  // CLASES_H_
