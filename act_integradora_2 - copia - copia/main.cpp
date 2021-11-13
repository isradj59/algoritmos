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

    string path = "test3.txt";
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
void viajero(const Data& d){
  int camino,menor,menorpos;
  vector<int> visitados;
  vector<vector<int>> distanciasrecorridas;
  vector<vector<int>> distancias = d.getDistancias();
  vector<int> aux;
  for (int i = 0; i < distancias.size(); i++)
  {
    distanciasrecorridas.push_back(aux);
    for (int j = 0; j < distancias.size(); j++)
    {
      visitados.push_back(0);
      distanciasrecorridas[i].push_back(0);
    }
    distanciasrecorridas[i].push_back(0);
    visitados[i]=1;
    distanciasrecorridas[i][0]=i;
    camino=i;
    for(int k = 1; k < distancias.size(); k++)
    {
      for (int j = 0; j < distancias.size(); j++)
      {
        if (visitados[j]==0)
        {
          menor=distancias[camino][j];
          menorpos=j;
          j=distancias.size();
        }
      }
      for (int j = 0; j < distancias.size(); j++)
      {
        if ((distancias[camino][j] < menor) and visitados[j]==0){
          menor = distancias[camino][j];
          menorpos=j;
        } 
      }
      camino=menorpos;
      visitados[camino]=1;
      distanciasrecorridas[i][k]=menorpos;
      distanciasrecorridas[i][distanciasrecorridas[i].size()-1]+=menor;
    }
    distanciasrecorridas[i][distanciasrecorridas[i].size()-1]+=distancias[i][distanciasrecorridas[i][distanciasrecorridas[i].size()-2]];
    for (int j = 0; j < distancias.size(); j++)
    {
      visitados.pop_back();
    }
  }
  menor=distanciasrecorridas[0][distanciasrecorridas[0].size()-1];
  menorpos=0;
  for (int j = 0; j < distanciasrecorridas.size(); j++)
    {
        if (distanciasrecorridas[j][distanciasrecorridas[j].size()-1] < menor){
          menor = distanciasrecorridas[j][distanciasrecorridas[j].size()-1];
          menorpos=j;
        } 
    }
    for (int i = 0; i < distanciasrecorridas[menorpos].size()-1; i++)
    {
      cout<<distanciasrecorridas[menorpos][i]<<",";
      if (i==distanciasrecorridas[menorpos].size()-2)
      {
        cout<<" La distancia es: "<<distanciasrecorridas[menorpos][i+1];
      }
    }
    cout<<endl;
}

int main() {
  Data data;
  viajero(data);



  return 0;
}
