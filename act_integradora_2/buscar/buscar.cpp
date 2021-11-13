#include<iostream>
#include<conio.h>
#include <vector>
using namespace std;
#define lim 50
  void leer(int*,int);
  //void buscar(vector<vector<int>> &v3,int);
  void leer(int a[lim],int x)
     {
      int i;
       for(i=0;i<x;i++)
        {
         cout<<"elemento ["<<i<<"] :";
         cin>>a[i];
        }
     }

  int buscar(vector<vector<int>> &v3,int x,int bus)
     {
        x=x-1;
       int i,j;
           j=-1,i=-1;
         
         do
          { i++;
          cout<<".";
            if(v3[i][2]==bus){
               j=i;
            }   
          }
            while((i<x)&&(v3[i][2]!=bus));

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
  int main()
     {
      int n,y[lim],m,bus;
      vector<int> d1={7,3,4};
      vector<int> d2={16,1,2};
      vector<int> d3={18,2,3};
      vector<int> d4={32,4,1};
      vector<vector<int>> datosTmp={d1,d2,d3,d4};
      //cout<<"ingresar el numero de elementos del arreglo :";
      //cin>>n;
      //cout<<"ingresar los valores del arreglo :\n";
      //leer(y,n);
      cout<<"ingresar el numero a buscar:";
         cin>>bus;
     cout<<buscar(datosTmp,datosTmp.size(),bus);
      //getch();
     } 