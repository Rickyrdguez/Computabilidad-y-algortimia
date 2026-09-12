#ifndef CALIFICACIONES_H
#define CALIFICACIONES_H

#include <map>
#include <string>

class Calificaciones {
 public:
  void LeerArchivo(const std::string& nombre_fichero);
  void InsertarDatos(const std::string& usuario, double notas);
  void MostrarPorPantalla() const;

 private:
  std::map<std::string, double> calificaciones_;
};

#endif  // CALIFICACIONES_H