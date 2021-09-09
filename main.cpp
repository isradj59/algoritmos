//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//A01638258 Enrique Israel Delgado Joaquin
//A01638129 Andres Olvera Rodriguez
//03 de Septiembre del 2021
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void leeArchivo(const char* nombreArchivo)
{
    ifstream inFile;
    char x;

    inFile.open(nombreArchivo);

    if(!inFile)
    {
        cerr << "No se abrio el archivo";
        exit(1);
    }

    while(inFile >> x)
    {
        cout << x;
    }
    cout << endl;
    cout << endl;

    inFile.close();
}

int main()
{
    leeArchivo("mcode1.txt");
    leeArchivo("mcode2.txt");
    leeArchivo("mcode3.txt");

    system("pause");
}
