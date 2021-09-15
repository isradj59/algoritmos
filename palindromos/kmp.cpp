#include<iostream>
#include<vector>
#include<stdlib.h>
#include<fstream>
#include<string>
using namespace std;

void kmp(string transmission, string mcode, vector<int> aux,int i,int j)
{
	int idx_transmission = 0, idx_mcode = 0;

	while((unsigned)idx_transmission < transmission.size())
	{
		if(mcode[idx_mcode] == transmission[idx_transmission])
		{
			idx_mcode++;
			idx_transmission++;
		}

		if((unsigned)idx_mcode == mcode.size())
		{
			cout << "Patron mcode"+to_string(j+1) +" encontrado en transmission"<<i+1<< " en la posicion: " << (idx_transmission - idx_mcode) << endl;
			idx_mcode = aux[idx_mcode - 1];
		}

		if((unsigned)idx_transmission < transmission.size() &&
				mcode[idx_mcode] != transmission[idx_transmission])
		{
			if(idx_mcode)
				idx_mcode = aux[idx_mcode - 1];
			else
				idx_transmission++;
		}
	}
}

void prefix(string mcode, vector<int> & aux)
{
	aux[0] = 0;
	int j = 0, i = 1;

	while((unsigned)i < mcode.size())
	{
		if(mcode[i] == mcode[j])
		{
			j++;
			aux[i] = j;
			i++;
		}
		else
		{
			if(j)
				j = aux[j - 1];
			else
			{
				aux[i] = 0;
				i++;
			}
		}
	}
}
string leer(string nombretxt){
	ifstream archivo;
	string texto,codigo;
 
	archivo.open(nombretxt+".txt",ios::in);
	if(archivo.fail()){
		cout<<"no se encontro el archivo";
		exit(1);
	}
	while(!archivo.eof()){
		getline(archivo,texto);
		cout<<texto<<endl;
        codigo+=texto;
	}
	archivo.close();
	return codigo;
}
void palindromo(string transmission) {
	int inicio,final;
	int longitud=1;
	string maxpalindromo=transmission.substr(0,1);
	//recorre el string desde el inicio
	for(int i=0; i<transmission.size(); ++i){
		//recorre el string desde el final restandole el inicio y se le va restando 1
		for(int j=transmission.size()-i; j>1; --j){
			int izquierda=i, derecha= i+j-1;
			//checa si es palindromo empezando desde las orillas
			while(izquierda<=derecha && transmission[izquierda]==transmission[derecha]){
				izquierda++;
				derecha--;
			}
			//si imin es mayor a imax quiere decir que ya recorrio todas las soluciones posibles
			if(izquierda>derecha){
				//verifica que el palindromo aun que sea es de 2 caracteres
				if(j>longitud){
					//longitus del palindromo
					longitud=j;
					//guarda el palindromo encontrado en una variable
					maxpalindromo = transmission.substr(i,j);
					inicio=i;
					final=inicio+longitud;
				}
			}
		}
	}
			cout<<"palindromo mas largo "<<maxpalindromo<<" Inicia en posicion "<<inicio<<" termina en posicion "<<final<<endl;
}

int main()
{
	string nombretxt,mcode[3],transmission[2];	

	for(int i=0;i<3;i++){
		//cout<<i<<endl;
		nombretxt="mcode";
		nombretxt+=to_string(i+1);
		//cout<<codigo<<endl;
		mcode[i]=leer(nombretxt);
		//cout<<mcode[i]<<endl;
	}
	for(int i=0;i<2;i++){
		//cout<<i<<endl;
		nombretxt="transmission";
		nombretxt+=to_string(i+1);
		//cout<<codigo<<endl;
		transmission[i]=leer(nombretxt);
		//cout<<transmission[i]<<endl;
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<3;j++){
			vector<int> aux(mcode[j].size());
			prefix(mcode[j], aux);
			kmp(transmission[i], mcode[j], aux,i,j);
		}
		palindromo(transmission[i]);
	}
	return 0;
}