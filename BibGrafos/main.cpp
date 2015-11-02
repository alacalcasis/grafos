/* 
 * File:   main.cpp
 * Author: alan.calderon
 *
 * Created on 25 de septiembre de 2015, 05:16 PM
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Grafo.h"

void aplicaPruebasRutasEntre(int o, int d) {
    string prefijo = "grafoRutasEntre";
    string sufijo = to_string(0) + to_string(d) + ".txt";
    Grafo<int> grf(prefijo + sufijo);
    //cout << grf.aHil() << endl;
    vector< vector< int > > rutas = grf.rutasEntre(0, d);
    for(int i = 0; i < rutas.size(); i++){
        for(int j = 0; j < rutas[i].size(); j++)
            cout << rutas[i][j] << ',';
        cout << endl;
    }
}

int main(int argc, char** argv) {
    //string nombre_archivo = "grafoMuyMuyPeqConCiclos3.txt";
//    string nombre_archivo = "grafoMuyPeq.txt";
//    string salida;
//    Grafo<int> grfInt(nombre_archivo);
//    cout << grfInt.aHil() << endl;
//    if (grfInt.ciclos(0, salida))
//        cout << "sí encontró un ciclo: " << salida << endl;
//    else cout << "no encontró un ciclo: " << salida << endl;

    // Ahora vamos con las pruebas de rutasEntre:
    cout << "rutas entre 0,1 en #01" << endl; 
    aplicaPruebasRutasEntre(0,1);
    cout << "rutas entre 0,2 en #02" << endl;
    aplicaPruebasRutasEntre(0,2);
    cout << "rutas entre 0,3 en #03" << endl;
    aplicaPruebasRutasEntre(0,3);
    cout << "rutas entre 0,4 en #04" << endl;
    aplicaPruebasRutasEntre(0,4);
    //aplicaPruebasRutasEntre(0,6);
    return 0;
}

