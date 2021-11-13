/**
 * Actividad integradora 2
 *
 * A01638258 Enrique Israel Delgado Joaquin
 * A01638129 Andres Olvera Rodriguez
 * A01630791 Oscar Miranda Escalante
 *
 * 12 de noviembre de 2021
 * Análisis y diseño de algoritmos avanzados
 * */
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <climits>
#include <queue>
#include <algorithm>

 // includes para voronoi
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>

// typedefs para el voronoi adaptor
typedef CGAL::Exact_predicates_inexact_constructions_kernel                  K;
typedef CGAL::Delaunay_triangulation_2<K>                                    DT;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DT>                 AT;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT> AP;
typedef CGAL::Voronoi_diagram_2<DT, AT, AP>                                  VD;

// typedef para el punto en el diagrama de voronoi
typedef DT::Point                    DPoint;



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
  vector<DPoint> centrales;
public:
  Data() {
    ifstream file;

    string path = "../test1.txt";
    file.open(path);
    if (file.fail()) {
      cout << "no se encontro el archivo (ejecutable debe estar dentro de carpeta build)";
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
      Point p(s);
      this->centrales.push_back(DPoint(p.x, p.y));
    }

    file.close();
  }

  Data(vector<vector<int>> distancias, vector<vector<int>> capacidades, vector<DPoint> ubicaciones) {
    this->distancias = distancias;
    this->capacidades = capacidades;
    this->centrales = ubicaciones;
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

  void printCentrales() const {
    for (DPoint s : this->centrales) {
      cout << s.x() << ", " << s.y() << endl;
    }
  }

  const vector<vector<int>>& getDistancias() const {
    return this->distancias;
  }

  const vector<vector<int>>& getCapacidades() const {
    return this->capacidades;
  }

  const vector<DPoint>& getCentrales() const {
    return this->centrales;
  }
};

/**
 * Parte 1
 * Algoritmo Floyd-Warshall
 * Para esta solución utilizamos el algoritmo Floyd-Warshall que tiene una complejidad O(n^3)
 * En cuanto el algoritmo detecta que hay una distancia más corta que la default entonces,
 * se toman en cuenta los arcos que forman el camino más corto.
 * */
void connectColonies(const Data& d) {
  cout << "Parte 1: conectar colonias" << endl;

  vector<vector<int>> tempM = d.getDistancias();

  int n = tempM.size();
  string arcos[n][n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      arcos[i][j] = Point(i, j).toString();
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if ((tempM[j][k] > (tempM[j][i] + tempM[i][k]) || (tempM[j][k] == -1)) && (tempM[i][k] != -1 && tempM[j][i] != -1)) {
          arcos[j][k] = Point(j, i).toString() + " " + Point(i, k).toString();
          tempM[j][k] = tempM[j][i] + tempM[i][k];
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j)
        cout << "Colonia " << i + 1 << " a la colina " << j + 1 << ": " << arcos[i][j] << endl;
    }
  }
  cout << endl;
}


/**
 * Parte 2
 * Algoritmo Nearest-neighbor
 * Se corre el algoritmo para cada vértice y posteriormente se comparan los resultados par 
 * obtener el mejor
 * Complejidad: O(n^3)
 * */
void viajero(const Data& d) {
  cout << "Parte 2: ruta de colonias" << endl;

  int camino, menor, menorpos;
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
    visitados[i] = 1;
    distanciasrecorridas[i][0] = i;
    camino = i;
    for (int k = 1; k < distancias.size(); k++)
    {
      for (int j = 0; j < distancias.size(); j++)
      {
        if (visitados[j] == 0)
        {
          menor = distancias[camino][j];
          menorpos = j;
          j = distancias.size();
        }
      }
      for (int j = 0; j < distancias.size(); j++)
      {
        if ((distancias[camino][j] < menor) and visitados[j] == 0) {
          menor = distancias[camino][j];
          menorpos = j;
        }
      }
      camino = menorpos;
      visitados[camino] = 1;
      distanciasrecorridas[i][k] = menorpos;
      distanciasrecorridas[i][distanciasrecorridas[i].size() - 1] += menor;
    }
    distanciasrecorridas[i][distanciasrecorridas[i].size() - 1] += distancias[i][distanciasrecorridas[i][distanciasrecorridas[i].size() - 2]];
    for (int j = 0; j < distancias.size(); j++)
    {
      visitados.pop_back();
    }
  }
  menor = distanciasrecorridas[0][distanciasrecorridas[0].size() - 1];
  menorpos = 0;
  for (int j = 0; j < distanciasrecorridas.size(); j++)
  {
    if (distanciasrecorridas[j][distanciasrecorridas[j].size() - 1] < menor) {
      menor = distanciasrecorridas[j][distanciasrecorridas[j].size() - 1];
      menorpos = j;
    }
  }
  for (int i = 0; i < distanciasrecorridas[menorpos].size() - 1; i++)
  {
    cout << distanciasrecorridas[menorpos][i] << ",";
    if (i == distanciasrecorridas[menorpos].size() - 2)
    {
      cout << " La distancia es: " << distanciasrecorridas[menorpos][i + 1] << endl;
    }
  }
  cout << endl;
}


/**
 * Parte 3 (A)
 * Función auxiliar augmentingPathExists
 * Realiza un recorrido de tipo BFS por el grafo que representa a la red de cableado
 * Complejidad: O(|V| + |E|) donde |V| es el número de vértices y |E| el número de ejes
 * */
bool augmentingPathExists(const vector<vector<int>>& residual, vector<int>& path) {
  // Recorrido BFS
  int n = residual.size();
  vector<bool> visited(n, false);
  queue<int> q;

  q.push(0);
  visited[0] = true;

  path[0] = 0;

  while (!q.empty()) {
    int current = q.front();
    q.pop();

    for (int i = 0; i < n; i++) {
      if (!visited[i] && residual[current][i] > 0) {
        path[i] = current;
        // si llega a "t" (n-1), sí existe un augmenting path
        if (i == n - 1) return true;
        q.push(i);
        visited[i] = true;
      }
    }
  }

  return false;
}

/**
 * Parte 3 (B)
 * Algoritmo Ford-Fulkerson
 * Calcula el flujo máximo en la red desde su origen hasta el último nodo
 * Complejidad: O((V + E)·f), donde (V + E) representa la complejidad de augmentingPathExist 
 * y f es el flujo máximo (en el peor caso, el flujo máximo aumenta en una unidad cada iteración)
 * */
void fordFulkerson(const Data& d) {
  cout << "Parte 3: máxima transmisión de datos" << endl;

  vector<vector<int>> residual = d.getCapacidades();

  int n = residual.size();
  vector<int> path(n);

  int maxFlux = 0;

  while (augmentingPathExists(residual, path)) {
    // cada ciclo analiza 1 camino
    int minCap = INT_MAX;
    int pathIndex = n - 1;

    while (pathIndex != 0) {
      // recorre todo el camino para conocer residuo mínimo
      minCap = min(minCap, residual[path[pathIndex]][pathIndex]);
      pathIndex = path[pathIndex];
    }

    maxFlux += minCap;

    pathIndex = n - 1;
    while (pathIndex != 0) {
      // recorre una vez más todo el camino para actualizar el residuo
      residual[path[pathIndex]][pathIndex] -= minCap;
      residual[pathIndex][path[pathIndex]] += minCap;
      pathIndex = path[pathIndex];
    }
  }

  cout << "El flujo máximo es: " << maxFlux << endl << endl;
};


/**
 * Parte 4
 * Diagrama de Voronoi
 * Para saber el área donde una central es la más cercana, se calcula el diagrama de Voronoi.
 * Una forma de hacerlo en CGAl es primero obteniendo la triangulación de Delaunay y adaptarla
 * a un diagrama de Voronoi.
 * No conocemos la complejidad del algoritmo de CGAL
 * La complejidad de un algoritmo para calcular el diagrama, como el de Fortune, es O(n·log(n))
 * */
void voronoi(const Data& d) {
  cout << "Parte 4: central más cercana" << endl;

  // crear triangulación
  DT delaunay;
  delaunay.insert(d.getCentrales().begin(), d.getCentrales().end());
  assert(delaunay.is_valid());

  // adaptar triangulación a diagrama de voronoi
  VD voronoi(delaunay);
  assert(voronoi.is_valid());

  // iterar sobre todas las caras
  int index = 1;
  for (VD::Face_iterator fit = voronoi.faces_begin(); fit != voronoi.faces_end(); fit++) {
    cout << "\nPolígono " << index << endl;
    cout << "Lista de puntos (x,y): " << endl;
    VD::Ccb_halfedge_circulator ec_start = fit->ccb();
    VD::Ccb_halfedge_circulator ec = ec_start;

    // iterar sobre todos los arcos
    do {
      if (ec->has_source()) {
        // Si ese arco tiene un vértice definido donde se origina, se imprime el punto
        std::cout << '(' << ec->source()->point().x() << ',' << ec->source()->point().y() << ')' << std::endl;
      }
    } while (++ec != ec_start);

    if (fit->is_unbounded()) {
      // Si es una cara abierta:
      std::cout << "'Unbounded face' (cara abierta)" << std::endl;
    }
    index++;
  }
}


int main() {
  Data data;

  connectColonies(data);
  viajero(data);
  fordFulkerson(data);
  voronoi(data);

  return 0;
}
