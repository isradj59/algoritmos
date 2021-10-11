#include <iostream>
#include <fstream>
using namespace std;

struct lcsStruct {
  int i, j, val;
  lcsStruct() {
    this->i = 0;
    this->j = 0;
    this->val = 0;
  }
  lcsStruct(int i, int j, int val) {
    this->i = i;
    this->j = j;
    this->val = val;
  }
};

void lcs(string a, string b) {
  // 1. declarar tabla de (n+1)x(m+1)
  // 2. comparar cada caracter a[i-1] con b[j-1]
  //				si coinciden, dpTable <- elem. en diagonal superior izq. + 1
  // 				ir almacenando coordenada valor más grande y su coordenada i o j en lcsEnd
  // 4. al llenar dTable, el último char del lcs estará en posición lcsEnd - 1
  // 5. inicio de lcs es lcsEnd - 1 - valor más grande en dpTable

  int n = a.size(),
    m = b.size();

  if (m == 0 || n == 0) {
    cout << "No existe lcs" << endl;
    return;
  }

  // inicializar dpTable
  int dpTable[n + 1][m + 1];
  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < m + 1; j++) {
      dpTable[i][j] = 0;
    }
  }

  // llenar tabla
  lcsStruct* max = new lcsStruct;

  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < m + 1; j++) {
      if (a[i - 1] == b[j - 1]) {
        dpTable[i][j] = dpTable[i - 1][j - 1] + 1;
      } else {
        dpTable[i][j] = 0;
      }

      if (dpTable[i][j] > max->val) {
        max = new lcsStruct(i, j, dpTable[i][j]);
      }
    }
  }

  // analizar resultado
  if (max->val == 0) {
    cout << "No existe lcs" << endl;
    return;
  }
  int lcsEnd = max->i - 1;
  int lcsBegin = max->i - max->val;

  cout << lcsBegin << ' ' << lcsEnd << endl;

  // imprimir lcs
  /*
  cout << endl;
  for (int i = lcsBegin; i <= lcsEnd; i++) {
    cout << a[i];
  }
  cout << endl;
  */
}

string leer(string nombretxt) {
  ifstream archivo;
  string texto, codigo;

  archivo.open(nombretxt + ".txt", ios::in);
  if (archivo.fail()) {
    cout << "no se encontro el archivo";
    exit(1);
  }
  while (!archivo.eof()) {
    getline(archivo, texto);
    codigo += texto;
  }
  archivo.close();
  return codigo;
}


int main()
{
  string nombretxt, transmission[2];

  for (int i = 0;i < 2;i++) {
    //cout<<i<<endl;
    nombretxt = "../transmission";
    nombretxt += to_string(i + 1);
    //cout<<codigo<<endl;
    transmission[i] = leer(nombretxt);
    //cout<<transmission[i]<<endl;
  }

  lcs(transmission[0], transmission[1]);

  return 0;
}
