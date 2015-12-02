/* 
 * File:   GrafoItrPP_c.h
 * Author: alan.calderon
 *
 * Created on 18 de noviembre de 2015, 12:10 PM
 */

#ifndef GrafoItrPP_c_H
#define	GrafoItrPP_c_H

#include <deque>
#include <random>
#include <chrono>
#include <algorithm>
#include <memory>
using namespace std;

#include "Grafo.h"

template < typename V >
class GrafoItrPP_c {
public:
    // Representa un iterador constante profundidad-primero sobre un Grafo.

    friend class Grafo< V >;
    GrafoItrPP_c(const GrafoItrPP_c< V >& orig);
    virtual ~GrafoItrPP_c();

    /* OPERADORES */
    const V* operator->();
    const V& operator*();
    GrafoItrPP_c< V >& operator++();
    bool operator==(const GrafoItrPP_c< V >& orig);
    bool operator!=(const GrafoItrPP_c< V >& orig);
    GrafoItrPP_c< V >& operator=(const GrafoItrPP_c< V >& orig);

private:

    // EFE: construye un iterador profundidad-primero constante para luego asociarlo
    //      mediante el begin que sólo puede ser invocado por métodos de Grafo < V >.
    GrafoItrPP_c();

    // EFE: construye un iterador profundidad-primero constante para recorrer g a 
    //      de un vértice escogido al azar.
    GrafoItrPP_c(const Grafo< V >& g);

    // EFE: construye un iterador profundidad-primero constante para recorrer g a de vO.
    GrafoItrPP_c(const Grafo< V >& g, int vO);

    void asgGrafo(Grafo< V >& g); // sólo para ser usado por Grafo< V >::begin(...)
    void asgOrigen(int vO); // sólo para ser usado por Grafo< V >::begin(...)
    void asgOrigenAlAzar(); // sólo para ser usado por Grafo< V >::begin(...)
    void asgNvoOrigenDeFaltantesAlAzar(); // sólo para ser usado por operator++ para reiniciar recorrido
    void clear(); // limpia el itr_begin de Grafo< V >.

    Grafo< V >* g_ptr; // puntero al grafo que se va a recorrer
    deque< int > pila; // para el recorrido profundidad-primero del grafo
    vector< int > marcados; // para evitar recorrer dos veces el mismo vértice
};

template < typename V >
GrafoItrPP_c< V >::GrafoItrPP_c() : g_ptr(0) {
}

template < typename V >
GrafoItrPP_c< V >::GrafoItrPP_c(const GrafoItrPP_c& orig) : g_ptr(orig.g_ptr), pila(orig.pila), marcados(orig.marcados) {
}

template < typename V >
void GrafoItrPP_c< V >::asgGrafo(Grafo< V >& g) {
    g_ptr = &g;
}

template < typename V >
void GrafoItrPP_c< V >::asgOrigen(int vO) {
    pila.push_front(vO);
}

template < typename V >
void GrafoItrPP_c< V >::asgOrigenAlAzar() {
    int t = g_ptr->vecVrt.size();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generador(seed);
    std::uniform_int_distribution<int> distribucion(0, t - 1);
    int inicio = distribucion(generador);
    pila.push_front(inicio);
}

template < typename V >
void GrafoItrPP_c< V >::asgNvoOrigenDeFaltantesAlAzar() {
    //se crea un vector con idVrt faltantes
    vector< int > faltantes;
    for (int i = 0; i < g_ptr->vecVrt.size(); ++i)
        if (find(marcados.begin(), marcados.end(), i) == marcados.end())
            faltantes.push_back(i);
    // se selecciona uno de los faltantes al azar
    int t = faltantes.size();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generador(seed);
    std::uniform_int_distribution<int> distribucion(0, t - 1);
    int inicio = distribucion(generador);
    // se reinicia el iterador a partir del vértices seleccionado al azar
    pila.push_front(faltantes[inicio]);
}

template < typename V >
void GrafoItrPP_c< V >::clear() {
    g_ptr = 0;
    while (!pila.empty())
        pila.pop_front();
    marcados.clear();
}

template < typename V >
GrafoItrPP_c< V >::~GrafoItrPP_c() {
}

/* OPERADORES */

template < typename V >
const V* GrafoItrPP_c< V >::operator->() {
    return &pila.front();
}

template < typename V >
const V& GrafoItrPP_c< V >::operator*() {
    return pila.front();
}

template < typename V >
GrafoItrPP_c< V >& GrafoItrPP_c< V >::operator++() {
    if (!pila.empty()) {
        int listo;
        listo = pila.front();
        while (!pila.empty()&&find(marcados.begin(), marcados.end(), listo) != marcados.end()) {
            pila.pop_front();
            listo = pila.front();
        };
        if (find(marcados.begin(), marcados.end(), listo) == marcados.end())
            marcados.push_back(listo);
        for (vector< int >::const_iterator itr = g_ptr->vecVrt.at(listo).ady.begin();
                itr != g_ptr->vecVrt.at(listo).ady.end(); ++itr)
            /*if ((find(marcados.begin(), marcados.end(), *itr) == marcados.end()) &&
                    (find(pila.begin(), pila.end(), *itr) == pila.end()))*/
            if (find(marcados.begin(), marcados.end(), *itr) == marcados.end()) {
                int nuevo = *itr;
                pila.push_front(*itr);
            }
        if ((pila.empty())&&(marcados.size() < g_ptr->vecVrt.size()))
            asgNvoOrigenDeFaltantesAlAzar();
    }
}

template < typename V >
bool GrafoItrPP_c< V >::operator==(const GrafoItrPP_c& orig) {
    return (pila == orig.pila);
}

template < typename V >
bool GrafoItrPP_c< V >::operator!=(const GrafoItrPP_c& orig) {
    return !(*this == orig);
}

template < typename V >
GrafoItrPP_c< V >& GrafoItrPP_c< V >::operator=(const GrafoItrPP_c& orig) {
    pila = orig.pila;
    g_ptr = orig.g_ptr;
    marcados = orig.marcados;
}

#endif	/* GrafoItrPP_c_H */

