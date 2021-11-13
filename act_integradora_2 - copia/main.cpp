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

float merge(vector<vector<int>> &v3, float l, float r)
{
  int centro = (l + r) / 2;
  float j = l;
  int k = centro + 1;
  float size = r - l + 1;
  vector<vector<int>> datosTmp;

  for (int i = 0; i < size; i++) {
    if (j <= centro && k <= r) {
      if (v3[j][0] < v3[k][0]) {
        datosTmp.push_back(v3[j++]);

      } else {
        datosTmp.push_back(v3[k++]);
      }
    } else if (j <= centro) {
      datosTmp.push_back(v3[j++]);
    } else {
      datosTmp.push_back(v3[k++]);
    }
  }
  for (int m = 0; m < size; m++) {
    v3[l + m] = datosTmp[m];
  }
  return 0;
}
int ordenaMerge(vector<vector<int>> &v3,float l,float r)
{

  if (l < r) {

       int m = (r + l) / 2;
       ordenaMerge(v3, l, m);
       ordenaMerge(v3, m + 1, r);
       float contador=merge(v3, l,r);

  }
  return 0;
}

int ordenaMerge(vector<vector<int>> &v3)
{
  float contador = 0;
  contador = ordenaMerge(v3, 0, v3.size() -1);
  return 0;
}
int buscar(vector<vector<int>> &v3,int bus)
{
  int x=v3.size();
  x=x-1;
  int i,j;
  j=-1,i=-1;     
  do
  { i++;
    cout<<".";
    if(v3[i][1]==bus){
      j=i;
    }   
  }
  while((i<x)&&(v3[i][1]!=bus));
  if(j==-1)
  {
    cout<<"el numero ingresado no se encuentra en el tablas\n ";
    return j;
  }
  else
  {
    cout<<"el numero ingresado se encuentra en la tabla\n" ;
    cout<<"esta en la posicion:"<<j<<endl;
    return j;
  }
}
void viajero(const Data& d){
  int swap;
  int contador=0;
  vector<int> aux(4);
  vector<int> visitados;
  vector<vector<int>> distanciasordenadas;
  vector<vector<int>> distanciasrecorridas;
  vector<vector<int>> distancias = d.getDistancias();
  for (int i = 0; i < distancias.size(); i++)
  {
    for (int j = i+1; j < distancias.size(); j++)
    {
      aux[0]=distancias[i][j];
      aux[1]=i;
      aux[2]=j;
      aux[3]=0;
      distanciasordenadas.push_back(aux);
    }
    visitados.push_back(0);
  }
  ordenaMerge(distanciasordenadas);
  for (int i = 0; i < distanciasordenadas.size(); i++)
  {
    //cout<<visitados[distanciasordenadas[i][1]]<<","<<visitados[distanciasordenadas[i][2]]<<endl;
    if (visitados[distanciasordenadas[i][1]]<2 and visitados[distanciasordenadas[i][2]]<2)
    {
      //cout<<"entre"<<endl;
      contador+=1;
      visitados[distanciasordenadas[i][1]]+=1;
      visitados[distanciasordenadas[i][2]]+=1;
      distanciasrecorridas.push_back(distanciasordenadas[i]);
      for (int j = 0; j < distanciasrecorridas.size(); j++)
      {
        for (int k = 0; k < distanciasrecorridas.size(); k++)
        {
          if (distanciasrecorridas[j][1]==distanciasrecorridas[k][1] and j!=k)
          {
            swap=distanciasrecorridas[k][1];
            distanciasrecorridas[k][1]=distanciasrecorridas[k][2];
            distanciasrecorridas[k][2]=swap;
          }
        }
      }
    }
    //cout<<"hola"<<endl;
    for (int y = 0; y < distanciasrecorridas.size(); y++)
      {
        distanciasrecorridas[y][3]=0;
      }

    int camino = (-1);
    int caminopasado=(-1);
    int repeticiones=0;
    bool repetido=false;
    bool falta=true;
    //cout<<"hola"<<endl;
    
      for (int ii = 0; ii < distanciasrecorridas.size(); ii++)
      {

        

        if (camino==-1)
        {
          int l=-1;
          for (int m = 0; m < distanciasrecorridas.size(); m++)
          {
            if (distanciasrecorridas[m][3]==0)
            {
              l=m;
              m=distanciasrecorridas.size();
            } 
          }
          camino=l;
        }
        if (camino!=(-1))
        {
          if (distanciasrecorridas[camino][3]==0 or (visitados[distanciasrecorridas[camino][1]]==2 and visitados[distanciasrecorridas[camino][2]]==2 and visitados[distanciasrecorridas[caminopasado][1]]==2))
          {
            distanciasrecorridas[camino][3]+=1;
          }
        }
        caminopasado=camino;
        camino=buscar(distanciasrecorridas,distanciasrecorridas[camino][2]);

         for (int i = 0; i < distanciasrecorridas.size(); i++)
        {
          for (int j = 0; j < 4; j++)
          {
            cout<<distanciasrecorridas[i][j]<<",";
          }
          cout<<endl;
        }
        for (int i = 0; i < visitados.size(); i++)
        {
          cout<<visitados[i]<<",";
        }
        cout<<endl;
        /*if (ii==distanciasrecorridas.size()-1)
        {
          for (int m = 0; m < distanciasrecorridas.size(); m++)
          {
            if (distanciasrecorridas[m][3]==0)
            {
              ii--;
            }
            else if(distanciasrecorridas[m][3]==2)
            {
              ii=distanciasrecorridas.size();
            }
          }
        }*/
        
        
      }
      cout<<"camino "<<camino<<endl;
      if (camino!=(-1))
        {
          if (distanciasrecorridas[camino][3]==0 or visitados[distanciasrecorridas[camino][1]]==2 and visitados[distanciasrecorridas[camino][2]]==2)
          {
            distanciasrecorridas[camino][3]+=1;
          }
        }

      for (int y = 0; y < distanciasrecorridas.size(); y++)
      {
        if (distanciasrecorridas[y][3]==2)
        {
          repetido=true;
        }
      }
    if (repetido==true)
    {
      visitados[distanciasrecorridas[distanciasrecorridas.size()-1][1]]-=1;
      visitados[distanciasrecorridas[distanciasrecorridas.size()-1][2]]-=1;
      distanciasrecorridas.pop_back();
    }
    
  }

  for (int i = 0; i < distanciasordenadas.size(); i++)
  {
    for (int j = 0; j < 3; j++)
    {
      cout<<distanciasordenadas[i][j]<<",";
    }
    cout<<endl;
  }
  cout<<endl;
  for (int i = 0; i < distanciasrecorridas.size(); i++)
  {
    for (int j = 0; j < 4; j++)
    {
      cout<<distanciasrecorridas[i][j]<<",";
    }
    cout<<endl;
  }
  for (int i = 0; i < visitados.size(); i++)
  {
    cout<<visitados[i]<<",";
  }
  
  

}

int main() {
  Data data;
  viajero(data);



  return 0;
}
