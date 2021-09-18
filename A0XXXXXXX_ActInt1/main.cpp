//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//A01638258 Enrique Israel Delgado Joaquin
//A01638129 Andres Olvera Rodriguez
//A01630791 Oscar Miranda Escalante
//17 de Septiembre del 2021
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<fstream>
#include<string>
using namespace std;

/**
 * kmp
 *
 * Implementación de algoritmo KMP
 * Imprime posición de patrón "mcode" dentro de "transmission"
 *
 * Complejidad lineal: O(n)
 * */
void kmp(string transmission, string mcode, vector<int> aux, int i, int j)
{
	int idx_transmission = 0, idx_mcode = 0;

	while ((unsigned)idx_transmission < transmission.size())
	{
		if (mcode[idx_mcode] == transmission[idx_transmission])
		{
			idx_mcode++;
			idx_transmission++;
		}

		if ((unsigned)idx_mcode == mcode.size())
		{
			cout << "true " << (idx_transmission - idx_mcode) << endl;
			// idx_mcode = aux[idx_mcode - 1];
			return;
		}

		if ((unsigned)idx_transmission < transmission.size() &&
			mcode[idx_mcode] != transmission[idx_transmission])
		{
			if (idx_mcode)
				idx_mcode = aux[idx_mcode - 1];
			else
				idx_transmission++;
		}
	}

	cout << "false " << endl;
}

/**
 * prefix
 *
 * Función que genera el arreglo de prefijo-sufijo para KMP
 * Llena un vector "aux" con enteros
 *
 * Complejidad lineal: O(n)
 * */
void prefix(string mcode, vector<int>& aux)
{
	aux[0] = 0;
	int j = 0, i = 1;

	while ((unsigned)i < mcode.size())
	{
		if (mcode[i] == mcode[j])
		{
			j++;
			aux[i] = j;
			i++;
		} else
		{
			if (j)
				j = aux[j - 1];
			else
			{
				aux[i] = 0;
				i++;
			}
		}
	}
}

/**
 * palindromo
 *
 * Algoritmo para búsqueda del palíndromo más largo
 * Imprime posición de inicio y fin del palíndromo más largo
 *
 * Complejidad cúbica: O(n^2*m), donde n es transmission.size() y m es distancia entre
 * 	primer y segundo índice
 * */
void palindromo(string transmission) {
	int inicio, final;
	int longitud = 1;
	string maxpalindromo = transmission.substr(0, 1);
	//recorre el string desde el inicio
	for (int i = 0; i < transmission.size(); ++i) {
		//recorre el string desde el final restandole el inicio y se le va restando 1
		for (int j = transmission.size() - i; j > 1; --j) {
			int izquierda = i, derecha = i + j - 1;
			//checa si es palindromo empezando desde las orillas
			while (izquierda <= derecha && transmission[izquierda] == transmission[derecha]) {
				izquierda++;
				derecha--;
			}
			//si imin es mayor a imax quiere decir que ya recorrio todas las soluciones posibles
			if (izquierda > derecha) {
				//verifica que el palindromo aun que sea es de 2 caracteres
				if (j > longitud) {
					//longitus del palindromo
					longitud = j;
					//guarda el palindromo encontrado en una variable
					maxpalindromo = transmission.substr(i, j);
					inicio = i;
					final = inicio + longitud;
				}
			}
		}
	}
	cout << inicio << " " << final << endl;
}

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

/**
 * lcs
 *
 * implementación de algoritmo Longest Common Substring
 * con programación dinámica
 *
 * imprime posición donde se encuentra lcs en string "a"
 *
 * Complejidad cuadrática: O(n*m) donde n es la s.size() y m es b.size()
 * */
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



int main() {
	// lectura de archivos
	string nombretxt, mcode[3], transmission[2];

	for (int i = 0;i < 3;i++) {
		//cout<<i<<endl;
		nombretxt = "mcode";
		nombretxt += to_string(i + 1);
		//cout<<codigo<<endl;
		mcode[i] = leer(nombretxt);
		//cout<<mcode[i]<<endl;
	}
	for (int i = 0;i < 2;i++) {
		//cout<<i<<endl;
		nombretxt = "transmission";
		nombretxt += to_string(i + 1);
		//cout<<codigo<<endl;
		transmission[i] = leer(nombretxt);
		//cout<<transmission[i]<<endl;
	}

	// parte 1
	for (int i = 0;i < 2;i++) {
		for (int j = 0;j < 3;j++) {
			vector<int> aux(mcode[j].size());
			prefix(mcode[j], aux);
			kmp(transmission[i], mcode[j], aux, i, j);
		}
	}

	// parte 2
	palindromo(transmission[0]);
	palindromo(transmission[1]);

	// parte 3
	lcs(transmission[0], transmission[1]);

	return 0;
}
