/* 
 * File:   Grafo.h
 * Author: alan.calderon
 *
 * Created on 25 de septiembre de 2015, 05:17 PM
 */

#ifndef GRAFO_H
#define	GRAFO_H

#include <stdlib.h>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

template < typename V >
class Grafo {
    
    // Representa grafos con vértices de tipo V.
    // V debe tener el constructor de copias y la sobrecarga de operator=.
    // Los vértices se identifican con números enteros de 1 a N.
    // N es la cantidad total de vértices que debe registrarse en la primera
    // línea del archivo que se usa para construir las adyacencias.
    
public:

    // Construye un grafo a partir de un archivo.
    // el formato del archivo es:
    // Primera línea: cantidad de vértices.
    // Las líneas subsiguientes contienen las adyacencias para cada vértice.
    // Ejemplo: 3,5,2,9,....
    // nota: SÓLO CONSTRUYE LAS ADYACENCIAS, deben inicializarse los vértices por aparte.
    Grafo(string nmbArc);

    // Construye una copia de orig.
    Grafo(const Grafo& orig);

    // Construye un grafo al azar con N vértices aplicando algún algoritmo 
    // generador de las adyacencias.
    Grafo(int N);

    virtual ~Grafo();

    /* OBSERVADORES BÁSICOS */

    // EFE: retorna true si el vértice #x existe en *this y false en caso contrario.
    bool xstVrt(int x);

    // EFE: retorna true si existe la adyacencia (vrtO, vrtD).
    bool xstAdy(int vrtO, int vrtD);

    // EFE: retorna la cantidad total de vértices en *this.
    long obtTotVrt();

    // EFE: retorna la cantidad total de adyacencias en *this.
    long obtTotAdy();

    // EFE: retorna una hilera que representa a *this.
    // {<#vrt-ady11,...#vrt-ady1i>, <#vrt-ady21>...<#vrt-ady2j>...<#vrt-adyN1,#vrt-adyNk>}
    // Una estructura <...> por cada vértice en *this.
    string aHil();

    /* OBSERVADORES NO BÁSICOS */

    // EFE: retorna true si *this es conexo y false en caso contrario.
    bool conexo();

    // EFE: retorna true si *this tiene al menos un ciclo y false en caso contrario.
    bool ciclos();

    /* MODIFICADORES */
    
    // REQ: 1 <= ind_vrt <= N.
    // MOD: *this.
    // EFE: agrega el dato "nv" al vértice indicado por "ind_vrt".
    void asgDatoVrt(const V& nv, int ind_vrt);
    
    /* ITERADORES */

private:

    template < typename T >
    struct Nodo {
        T vrt;
        vector<int> ady;

        Nodo() {};
        Nodo(const T& v_init) : vrt(v_init) {};
        Nodo(const Nodo& orig) : vrt(orig.vrt), ady(orig.ady) {};
    };

    vector< Nodo< V > > vecVrt; // vector de nodos que incluyen vértices
    int cntVrt; // cantidad de vértices que tendrá el grafo
};

template < typename V >
Grafo<V>::Grafo(string nmbArc) {
    ifstream archivoLineasEntrada(nmbArc.c_str(), ios::in);
    string linea = ""; // línea que se lee del archivo
    int ind_vrt = 0; // índice de vértice recién leído del archivo
    cntVrt = 0; 
    
    if (!archivoLineasEntrada) { // operador ! sobrecargado
        cerr << "No se pudo abrir el archivo de entrada" << endl;
        exit(1);
    }
    
    // se lee la primera línea que contiene la cantidad de vértices
    getline(archivoLineasEntrada, linea); 
    cntVrt = atoi(linea.c_str());
    vecVrt.reserve(cntVrt); // se crea un vector con la capacidad requerida
    vecVrt.resize(cntVrt); // agrega la cantidad de entradas requeridas
    
    getline(archivoLineasEntrada, linea); // se lee la primera lista de adyacencias
    while (!archivoLineasEntrada.eof()) {
        int i = 0;
        int uc = -1; // posíción de la última coma no existe al principio
        while (i < linea.length()) { // se procesa una línea
            if (linea[i] == ',') {
                string sni = linea.substr(uc + 1, i - uc - 1); // hilera de nuevo índice
                // int ni = strtol(sni.c_str(), 0, 10);
                int ni = atoi(sni.c_str());
                vecVrt[ind_vrt].ady.push_back(ni);
                uc = i;
            }
            i++;
        }

        // se lee otra línea
        getline(archivoLineasEntrada, linea);
        ind_vrt++;
    }
}

template < typename V >
Grafo<V>::Grafo(const Grafo& orig):vecVrt(orig.vecVrt),cntVrt(orig.cntVrt) {
}

template < typename V >
Grafo<V>::Grafo(int N) {
    // Escoger un método e implementarlo
}

template < typename V >
Grafo<V>::~Grafo() {
}

/* OBSERVADORES BÁSICOS */

template < typename V >
bool Grafo<V>::xstVrt(int x) {
    return ((1 <= x)&&(x <= cntVrt));
}

template < typename V >
bool Grafo<V>::xstAdy(int vrtO, int vrtD) {
    return ((find(vecVrt[vrtO].ady.begin(),vecVrt[vrtO].ady.end(),vrtD) != vecVrt[vrtO].ady.end())&&
            (find(vecVrt[vrtD].ady.begin(),vecVrt[vrtD].ady.end(),vrtO) != vecVrt[vrtD].ady.end()));
}

template < typename V >
long Grafo<V>::obtTotAdy() {
    long rsl = 0;
    for(int i = 0; i < cntVrt; i++) rsl = rsl + vecVrt[i].ady.size();
    return rsl/2;
}

template < typename V >
long Grafo<V>::obtTotVrt() {
    return cntVrt;
}

template < typename V >
string Grafo<V>::aHil() {
    stringstream salida; // flujo de salida de datos
    for(int i = 0; i < cntVrt; i++){
        for(vector< int >::const_iterator itr = vecVrt[i].ady.begin();
                itr != vecVrt[i].ady.end(); itr++)
            salida << (*itr) << ',';
        salida << endl;
    }
    return salida.str();
}

/* OBSERVADORES NO BÁSICOS */

template < typename V >
bool Grafo<V>::conexo() {

}

template < typename V >
bool Grafo<V>::ciclos() {

}

/* MODIFICADORES */

template < typename V >
void Grafo<V>::asgDatoVrt(const V& nv, int ind_vrt) {
    vecVrt[ind_vrt].vrt = nv;
}

/* ITERADORES */

#endif	/* GRAFO_H */

