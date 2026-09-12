#include <iostream>
#include <iostream>

/**
 * @brief Función encarga de hacer el cálculo de la serie de Pell
 *
 * @param numero_n Entero que indica hasta donde llega la serie de pell;
 */
int CalculoPell(int numero_n)
{
  return 2 * (numero_n - 1) + (numero_n - 2);
}

/**
 * @brief Función que muestra la sucesión de la serie de Pell
 *
 * @param posicion Entero que inidica en que número de la serie estamos
 * @param numero_n Numero que indica hasta donde llega la serie de Pell;
 */
void MostrarSeriePell(int posicion, int numero_n) {
  if (posicion == 0) {
    std::cout << '0' << " ";
    MostrarSeriePell(posicion + 1, numero_n);
  }
   if (posicion == 1) {
    std::cout << '1' << " ";
    MostrarSeriePell(posicion + 1, numero_n);
  }
    std::cout << CalculoPell(posicion) << " ";
    MostrarSeriePell(posicion + 1, numero_n);
  return;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cerr << "ERROR. El programa " << argv[0] << " usa <numero_n>" << std::endl;
    return -1;
  }

  int posicion{0};

  MostrarSeriePell(posicion, std::stoi(argv[1]));

  return 0;
}