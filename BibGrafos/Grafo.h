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
#include <queue>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

template < typename V >
class Grafo {
    // Representa grafos con vértices de tipo V.
    // V debe tener el constructor de copias y la sobrecarga de operator=.
    // Los vértices se identifican con números enteros de 0 a N-1.
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
    bool xstVrt(int x) const;

    // EFE: retorna true si existe la adyacencia (vrtO, vrtD).
    bool xstAdy(int vrtO, int vrtD) const;

    // EFE: retorna la cantidad total de vértices en *this.
    long obtTotVrt() const;

    // EFE: retorna la cantidad total de adyacencias en *this.
    long obtTotAdy() const;

    // EFE: retorna una hilera que representa a *this.
    // {<#vrt-ady11,...#vrt-ady1i>, <#vrt-ady21>...<#vrt-ady2j>...<#vrt-adyN1,#vrt-adyNk>}
    // Una estructura <...> por cada vértice en *this.
    string aHil() const;

    // EFE: retorna las posiciones de los vértices adyacentes a vrt.
    //      Si vrt > N, el vector resultante estará vacío.
    vector<int>& obtAdy(int vrt) const;

    /* OBSERVADORES NO BÁSICOS */

    // EFE: retorna true si *this es conexo y false en caso contrario.
    bool conexo() const;

    // EFE: retorna true si *this tiene al menos un ciclo que inicia en x y 
    //      false en caso contrario.
    bool ciclos(int x, string& hsal) const;

    vector< vector<int> >& rutasEntre(int vO, int vD) const;

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

        Nodo() {
        };

        Nodo(const T& v_init) : vrt(v_init) {
        };

        Nodo(const Nodo& orig) : vrt(orig.vrt), ady(orig.ady) {
        };
    };

    typedef vector< Nodo< V > > T_vecNdo;
    vector< Nodo< V > > vecVrt; // vector de nodos que incluyen vértices

    static vector<int> rsl; // se usa para retornar vectores de int, por ejemplo adyacencias.
    static vector< vector< int > > rsl2;

    // misceláneos:
    static string vecAhil(vector<int> vecEnt);
};

template < typename V >
vector<int> Grafo<V>::rsl;

template < typename V >
vector< vector<int> > Grafo<V>::rsl2;

template < typename V >
Grafo<V>::Grafo(string nmbArc) {
    ifstream archivoLineasEntrada(nmbArc.c_str(), ios::in);
    string linea = ""; // línea que se lee del archivo
    int ind_vrt = 0; // índice de vértice recién leído del archivo
    int cntVrt = 0;

    if (!archivoLineasEntrada) { // operador ! sobrecargado
        cerr << "No se pudo abrir el archivo de entrada" << endl;
        exit(1);
    }

    // se lee la primera línea que contiene la cantidad de vértices
    getline(archivoLineasEntrada, linea);
    cntVrt = atoi(linea.c_str());
    vecVrt.reserve(cntVrt); // se crea un vector con la capacidad requerida
    vecVrt.resize(cntVrt); // asigna memoria para la cantidad de entradas requeridas

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
Grafo<V>::Grafo(const Grafo& orig) : vecVrt(orig.vecVrt) {
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
bool Grafo<V>::xstVrt(int x) const {
    return ((0 <= x)&&(x <= vecVrt.size() - 1));
}

template < typename V >
bool Grafo<V>::xstAdy(int vrtO, int vrtD) const {
    return ((find(vecVrt[vrtO].ady.begin(), vecVrt[vrtO].ady.end(), vrtD) != vecVrt[vrtO].ady.end())&&
            (find(vecVrt[vrtD].ady.begin(), vecVrt[vrtD].ady.end(), vrtO) != vecVrt[vrtD].ady.end()));
}

template < typename V >
long Grafo<V>::obtTotAdy() const {
    long rsl = 0;
    for (int i = 0; i < vecVrt.size(); i++) rsl = rsl + vecVrt[i].ady.size();
    return rsl / 2;
}

template < typename V >
long Grafo<V>::obtTotVrt() const {
    return vecVrt.size();
}

template < typename V >
string Grafo<V>::aHil() const {
    stringstream salida; // flujo de salida de datos
    for (int i = 0; i < vecVrt.size(); i++) {
        for (vector< int >::const_iterator itr = vecVrt[i].ady.begin();
                itr != vecVrt[i].ady.end(); itr++)
            salida << (*itr) << ',';
        salida << endl;
    }
    return salida.str();
}

template < typename V >
vector<int>& Grafo<V>::obtAdy(int vrt) const {
    rsl = vecVrt[++vrt].ady;
    return rsl;
}

/* OBSERVADORES NO BÁSICOS */

template < typename V >
bool Grafo<V>::conexo() const {

}

template < typename V >
bool Grafo<V>::ciclos(int origen, string& hsal) const {
    stringstream salida;
    bool rsl = false;
    // Primero se busca algún vértice que sea autoadyacente.
    int i = 0, j = 0;
    while ((i < vecVrt.size()) && !rsl) {
        j = 0;
        while ((j < vecVrt[i].ady.size()) && !rsl) {
            if (i == vecVrt[i].ady[j]) {
                rsl = true;
                salida << vecVrt[i].ady[j];
            }
            j++;
        }
        i++;
    }

    if (!rsl) { // Se buscan ciclos mayores.
        // La siguiente matriz de adyacencia se usa para marcar las aristas recorridas
        int vs = vecVrt.size();
        bool *matAdy = new bool[vs * vs];
        for (int i = 0; i < vs; i++)
            for (int j = 0; j < vs; j++)
                matAdy[i * vs + j] = false;

        vector<int> marcados; // vector de nodos marcados
        stack<int> pila; // pila para el recorrido por profundidad
        pila.push(origen); // se apila el origen

        while (!pila.empty() && !rsl) {
            // se sacan del ciclo en construcción los vértices que ya se intentaron
            // porque ya no tienen adyacentes pendientes de recorrer en la pila
            if (!pila.empty() && !marcados.empty()) {
                while (find(vecVrt.at(marcados.back()).ady.begin(),
                        vecVrt.at(marcados.back()).ady.end(),
                        pila.top()) == vecVrt.at(marcados.back()).ady.end()) marcados.pop_back();

            }
            int nvoMrc = pila.top();
            pila.pop();
            // se agrega para intentar hallar un ciclo a partir de nvoMrc
            marcados.push_back(nvoMrc);
            for (int i = 0; i < vecVrt[nvoMrc].ady.size(); i++) {
                int vAdy = vecVrt[nvoMrc].ady.at(i);
                /*if ((vAdy == origen)&& (marcados[marcados.size() - 2] != origen))*/
                 if (find(marcados.begin(),marcados.end(),vAdy) != marcados.end() && (marcados[marcados.size() - 2] != vAdy)){
                    rsl = true;
                    break;
                } else
                    // se agregan a la pila los adyacentes a nvoMrc cuyas aristas no han sido marcadas
                    if (!matAdy[nvoMrc * vs + vAdy]) {
                    pila.push(vAdy);
                    matAdy[nvoMrc * vs + vAdy] = true;
                    matAdy[vAdy * vs + nvoMrc] = true;
                }
            }
        }
        delete[] matAdy;
    }
    return rsl;
}

template < typename V >
vector< vector<int> >& Grafo<V>::rutasEntre(int vO, int vD) const {
    vector< int > rutaEnCnst;
    stack< int > pila;
    pila.push(vO);
    while (!pila.empty()) {
        int vrt = pila.top();
        rutaEnCnst.push_back(vrt);
        pila.pop();
        if (vrt == vD) { // se encontró ruta nueva
            vector< int > ruta = rutaEnCnst;
            reverse(ruta.begin(), ruta.end());
            rsl2.push_back(ruta);
            rutaEnCnst.pop_back(); // se elimina vD para seguir construyendo rutas
            // se sacan de la ruta en construcción los vértices que ya se intentaron
            while (find(vecVrt.at(rutaEnCnst.back()).ady.begin(),
                    vecVrt.at(rutaEnCnst.back()).ady.end(),
                    pila.top()) == vecVrt.at(rutaEnCnst.back()).ady.end()) rutaEnCnst.pop_back();
        } else { // colocar en la pila los adyacentes que no forman ciclos en la ruta
            for (typename T_vecNdo::const_iterator itr = vecVrt.at(pila.top()).ady.begin();
                    itr != vecVrt.at(pila.top()).ady.end(); itr++)
                if (find(rutaEnCnst.begin(), rutaEnCnst.end(), *itr) == rutaEnCnst.end())
                    pila.push(*itr);
        }
    }
    return rsl2;
}

/* MODIFICADORES */

template < typename V >
void Grafo<V>::asgDatoVrt(const V& nv, int ind_vrt) {
    vecVrt[ind_vrt].vrt = nv;
}

/* ITERADORES */

/* misceláneos: */
template < typename V >
string Grafo<V>::vecAhil(vector<int> vecEnt) {
    stringstream salida;
    for (int i = 0; i < vecEnt.size(); i++)
        salida << "," << vecEnt[i];
    return salida.str();
}
#endif	/* GRAFO_H */

