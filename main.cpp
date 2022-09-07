#include <iostream>
#include <fstream>


using namespace std;

void mostrar(string v[], int dim){
    for(int i = 0; i < dim; i++)
        cout << "v[" << i << "] = " << v[i] << endl;
}

void matriz(double  v[][5], int fil){
    const int col {5};
    for(int i = 0; i < fil; i++){
        for(int j = 0; j < col; j++)
                cout << v[i][j] << '\t';
        cout << endl;
    }
}   

void listado(double mat[][5], int dclient, string cliente[], string producto []){
    const int dprod {5};
    cout << "Listado: " << endl;
    for(int i = 0; i < dclient; i++){
        for(int j = 0; j < dprod; j++){
                if(mat[i][j] > 13000){
                    cout << cliente[i] << "::" << producto[j] << endl;
                }
        }
    }
}

int mascant(double mat[][5], int dclient){
    const int dprod {5};
    int max = 0;
    int temp = 0;
    int posmax {0};
    for(int i = 0; i < dclient; i++){
        for(int j = 0; j < dprod; j++){
            if(mat[i][j] > 13000){
                temp++;
            }
        }
        if(temp > max){
            max = temp;
            posmax = i;
        }
        temp = 0;
    }
    return posmax;
}

void ascendente(double v[], int dim, int aux[]){
    int i, pos, imin;

    for(pos = 0; pos < dim - 1; pos++){
        imin = pos;
        for(i = pos + 1; i < dim; i++){
            if(v[i] < v[imin]){
                imin = i;
            }
        }
        swap(v[pos], v[imin]);
        swap(aux[pos], aux[imin]);
        
    }
}

void mostrar2(double vec[], int dim, string producto[], int pos []){
    for(int i = 0; i < dim; i++){
        cout << producto[pos[i]] << ": " << vec[i] << endl;
    }
}

int main(){
    const int clien {8};
    const int prod {5};
    double pesos[clien][prod] {};
    double distancia[clien][prod] {};
    bool debug{false};
    int entregas[prod] {};
    

    string cliente[clien];
    string producto[prod];

    ifstream archilec;
    archilec.open("Nombres.txt");
    if(!archilec){
        cout << "Error al tratar de abrir el archivo 1";
        return 1;
    }

    for(int i = 0; i < clien && archilec >> cliente[i]; i++);
    for(int i = 0; i < prod && archilec >> producto[i]; i++);

    archilec.close();

    if(debug){
        mostrar(cliente, clien);
        cout << "=================" << endl;
        mostrar(producto, prod);
        cout << endl;
    }

    archilec.open("Datos.txt");
    if(!archilec){
        cout << "Error al tratar de abrir el archivo 2";
        return 1;
    }

    int codcli, codpro {0};
    double kg, dist {0};

    while(archilec >> codcli >> codpro >> kg >> dist){ 
        pesos[codcli][codpro] += kg;
        distancia[codcli][codpro] += dist;
        entregas[codpro]++; 
    }

    if(debug){
        matriz(distancia, clien);
        cout << "============" << endl;
        matriz(pesos, clien);
        cout << endl;
    }
    
    //Punto 1 :) 
    listado(pesos, clien, cliente, producto);
    cout << endl;
    /* Una forma que se me ocurrio con matriz
    string supera[clien][prod+1] {};
    for(int i = 0; i < clien; i++){
        supera[i][0] = cliente[i] + ":";
    }

    for(int i = 0; i < clien; i++){
        for(int j = 0; j < prod; j++){
            if(pesos[i][j] >= 13000){
                supera[i][j+1] = producto[j];
            }
        }
    }   

    cout << "Listado por clientes de los tipos de productos que superen los 13000kg acumulados: " << endl;
    for(int i = 0; i < clien; i++){
        for(int j = 0; j < prod+1; j++)
                cout << supera[i][j] << '\t';
        cout << endl;
    }
    cout << endl;
    */
   
    //Punto 2 :)
    int max = mascant(pesos, clien);
    
    int vec [prod];
    double maxim [prod];
    
    for(int i = 0; i < clien; i++){
        for(int j = 0; j < prod; j++){
            vec[j] = j;
            maxim[j] = distancia[max][j];
        }
    }

    if(debug){
        for(int i = 0; i < prod; i++){
        cout << producto[i] << ": " << maxim[i] << endl;
        }
    }
    
    ascendente(maxim, prod, vec);
    
    cout << "Listado de Km recorridos por tipo de producto (ascendente)" << endl;
    mostrar2(maxim, prod, producto, vec);

    if(debug){ //Me aseguro que no se cambio el vector con los productos
        mostrar(producto, prod);
    }
    
    //Punto 3 :)
     //Es el ultimo elemento en una escala ordenada ascendente
    int entregamax = entregas[3];
    cout << endl;
    cout << "Cantidad de entregas para el tipo de producto Textiles: " << entregamax; 
    
    return 0;
}