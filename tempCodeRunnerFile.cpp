#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{   
    int Length,disponibles,contador;
    string res;
    cin>>Length;
    if(Length>0&&Length<10001){
        vector <string> caracteres(Length);
        vector <int> distancia(Length);
        vector <int> ntables(Length);
        bool ocupado=false;

        for(int i=0;i<Length;i++){
            cin>>ntables[i];
            cin>>distancia[i];
            cin>>caracteres[i];
        }
        for(int i=0;i<Length;i++){
            contador=0;
            ocupado=false;
            for(int j=0;j<caracteres[i].length();j++){
                
                if(caracteres[i][j]=='1'){
                    
                    //cout<<"llegue"<<endl;
                    contador=distancia[i]+1;
                    //cout<<caracteres[i][j]<<" "<<contador<<endl;
                }else if(caracteres[i][j]=='0'){
                    ocupado=false;
                    //cout<<caracteres[i][j]<<" a comparar"<<endl;
                    //cout<<caracteres[i].length()<<" "<<j<<endl;
                    if(j<caracteres[i].length()){
                        for(int k=1;k<distancia[i]+1;k++){
                            //cout<<caracteres[i][j+k]<<" delante"<<endl;
                            if(caracteres[i][j+k]=='1'){
                                ocupado=true;
                            }
                         }
                    }
                    
                    for(int k=1;k<distancia[i]+1;k++){
                        //cout<<caracteres[i][j-k]<<" detras"<<endl;
                        if(caracteres[i][j-k]=='1'){
                            ocupado=true;
                        }
                    }
                    //cout<<ocupado<<endl;
                    if(!ocupado){
                        caracteres[i][j]='1';
                        disponibles+=1;
                        contador=distancia[i]+1;
                        //cout<<caracteres[i]<<endl;
                        ocupado=false;
                    }

                }else if(contador==0 && caracteres[i][j]=='0'){
                    //cout<<"llegue2"<<endl;
                    caracteres[i][j]='1';
                    disponibles+=1;
                    contador=distancia[i]+1;
                    //cout<<caracteres[i][j]<<" "<<contador<<endl;
                }
                contador--;
            }
            contador=0;
            //cout<<"distancia: "<<distancia[i]<<endl;
            //cout<<caracteres[i]<<endl;
            //cout<<"disponibles: "
            cout<<disponibles<<endl;
            disponibles=0;    
        }
    }
    //cout<<"finalize"<<endl;
    
}