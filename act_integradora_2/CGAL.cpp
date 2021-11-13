// standard includes
#include <fstream>
#include <iostream>
#include <vector>

// includes for drawing the Voronoi Diagram
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
#include <CGAL/draw_voronoi_diagram_2.h>

// typedefs for defining the adaptor
typedef CGAL::Exact_predicates_inexact_constructions_kernel                  K;
typedef CGAL::Delaunay_triangulation_2<K>                                    DT;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DT>                 AT;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT> AP;
typedef CGAL::Voronoi_diagram_2<DT, AT, AP>                                  VD;

// typedef for the result type of the point location
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

void voronoi(const Data& d) {
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
        // Si ese arco tiene un punto definido donde se origina, se imprime el
        std::cout << '(' << ec->source()->point().x() << ',' << ec->source()->point().y() << ')' << std::endl;
      }
    } while (++ec != ec_start);

    if (fit->is_unbounded()) {
      // Si es una cara abierta:
      std::cout << "'Unbounded face' (los vértices faltantes se encuentran en el inf.)" << std::endl;
    }
    index++;
  }
}

int main()
{
  Data d;
  voronoi(d);
  return 0;
}
