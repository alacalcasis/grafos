/* 
 * File:   main.cpp
 * Author: alan.calderon
 *
 * Created on 25 de septiembre de 2015, 05:16 PM
 */

#include <iostream>
#include <string>
using namespace std;

#include "Grafo.h"
/*
 * 
 */
int main(int argc, char** argv) {
    string nombre_archivo = "grafoMuyMuyPeqSinCiclos.txt";
    string salida;
    Grafo<int> grfInt(nombre_archivo);
    cout << grfInt.aHil() << endl;
    if (grfInt.ciclos(0,salida))
        cout << "sí encontró un ciclo: " << salida << endl;
    return 0;
}

