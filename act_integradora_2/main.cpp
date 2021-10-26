/**
 * Actividad integradora 2
 *
 * A01638258 Enrique Israel Delgado Joaquin
 * A01638129 Andres Olvera Rodriguez
 * A01630791 Oscar Miranda Escalante
 *
 * 09 de octubre de 2021
 * Análisis y diseño de algoritmos avanzados
 * */
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

struct Point {
  int x;
  int y;
  Point() {
    this->x = 0;
    this->y = 0;
  }
  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }
  Point(string s) {
    string x_string = "", y_string = "";

    int i = 1;
    while (s[i] != ',') {
      x_string += s[i];
      i++;
    }

    i++;
    while (i != s.size() - 1) {
      y_string += s[i];
      i++;
    }

    this->x = stoi(x_string);
    this->y = stoi(y_string);
  }
  string toString() {
    return "(" + to_string(this->x) + "," + to_string(this->y) + ")";
  }
};

class Data {
private:
  vector<vector<int>> distancias;
  vector<vector<int>> capacidades;
  vector<Point> ubicaciones;
public:
  Data() {
    ifstream file;

    string path = "test1.txt";
    file.open(path);
    if (file.fail()) {
      cout << "no se encontro el archivo";
      exit(1);
    }

    int n;
    file >> n;


    // leer matriz de distancias
    for (int i = 0; i < n; i++) {
      this->distancias.push_back(vector<int>(n));
      for (int j = 0; j < n; j++) {
        file >> this->distancias[i][j];
      }
    }

    // leer matriz de capacidades
    for (int i = 0; i < n; i++) {
      this->capacidades.push_back(vector<int>(n));
      for (int j = 0; j < n; j++) {
        file >> this->capacidades[i][j];
      }
    }

    // leer conjunto de puntos
    string s;
    for (int i = 0; i < n; i++) {
      file >> s;
      this->ubicaciones.push_back(Point(s));
    }

    file.close();
  }

  void printDistancias() const {
    printMatrix(this->distancias);
  }

  void printCapacidades() const {
    printMatrix(this->capacidades);
  }

  void printMatrix(const vector<vector<int>>& m) const {
    for (int i = 0; i < m.size(); i++) {
      for (int j = 0; j < m.size(); j++) {
        cout << m[i][j] << ' ';
      }
      cout << endl;
    }
  }

  void printUbicaciones() const {
    for (Point p : this->ubicaciones) {
      cout << p.toString() << endl;
    }
  }

  const vector<vector<int>>& getDistancias() const {
    return this->distancias;
  }

  const vector<vector<int>>& getCapacidades() const {
    return this->capacidades;
  }

  const vector<Point>& getUbicaciones() const {
    return this->ubicaciones;
  }
};

void funcionEjemplo(const Data& d) {
  /**
   * Función de ejemplo
   * objeto 'd' otorga acceso a todos
   * los datos obtenidos en input
   * */


   // copiar "distancias"
  vector<vector<int>> distancias = d.getDistancias();

  // copiar "capacidades"
  vector<vector<int>> capacidades = d.getCapacidades();

  // copiar "ubicaciones"
  vector<Point> ubicaciones = d.getUbicaciones();

  // ej. acceder a una coordenada de una ubicación (problema 4)
  Point p = ubicaciones[0];
  int x = p.x;
  int y = p.y;
}


int main() {
  Data data;



  return 0;
}
