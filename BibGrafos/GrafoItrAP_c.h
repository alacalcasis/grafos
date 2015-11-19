/* 
 * File:   GrafoItrAP_c.h
 * Author: alan.calderon
 *
 * Created on 18 de noviembre de 2015, 12:10 PM
 */

#ifndef GRAFOITRAP_C_H
#define	GRAFOITRAP_C_H

#include <queue>
#include <random>
#include <algorithm>
#include <memory>
using namespace std;

#include "Grafo.h"

template < typename V >
class GrafoItrAP_c {
public:
    // Representa un iterador constante anchura-primero sobre un Grafo.

    friend class Grafo< V >;
    GrafoItrAP_c(const GrafoItrAP_c< V >& orig);
    virtual ~GrafoItrAP_c();

    /* OPERADORES */
    const V* operator->();
    const V& operator*();
    GrafoItrAP_c< V >& operator++();
    bool operator==(const GrafoItrAP_c< V >& orig);
    bool operator!=(const GrafoItrAP_c< V >& orig);
    GrafoItrAP_c< V >& operator=(const GrafoItrAP_c< V >& orig);

private:

    // EFE: construye un iterador anchura-primero constante para luego asociarlo
    //      mediante el begin que sólo puede ser invocado por métodos de Grafo < V >.
    GrafoItrAP_c();
    
    // EFE: construye un iterador anchura-primero constante para recorrer g a 
    //      de un vértice escogido al azar.
    GrafoItrAP_c(const Grafo< V >& g);

    // EFE: construye un iterador anchura-primero constante para recorrer g a de vO.
    GrafoItrAP_c(const Grafo< V >& g, int vO);
    
    void asgGrafo(Grafo< V >& g); // sólo para ser usado por Grafo< V >::begin(...)
    void asgOrigen(int vO); // sólo para ser usado por Grafo< V >::begin(...)
    void asgOrigenAlAzar(); // sólo para ser usado por Grafo< V >::begin(...)
    void clear(); // limpia el itr_begin de Grafo< V >.
    
    shared_ptr< Grafo< V > > g_ptr; // puntero al grafo que se va a recorrer
    queue< int > cola; // para el recorrido anchura-primero del grafo
    vector< int > marcados; // para evitar recorrer dos veces el mismo vértice
    bool fin; // variable que representa la terminación del recorrido
};

template < typename V >
GrafoItrAP_c< V >::GrafoItrAP_c():g_ptr(0),fin(false) {
}

//template < typename V >
//GrafoItrAP_c< V >::GrafoItrAP_c(const Grafo< V >& g) : g_ptr(&g),fin(false) {
//    int t = g.vecVrt.size();
//    std::default_random_engine generador;
//    std::uniform_int_distribution<int> distribucion(0, t - 1);
//    int inicio = distribucion(generador);
//    cola.push(inicio);
//}
//
//template < typename V >
//GrafoItrAP_c< V >::GrafoItrAP_c(const Grafo< V >& g, int vO) : g_ptr(shared_ptr< Grafo< V > >(&g)),fin(false) {
//    cola.push(vO);
//}

template < typename V >
GrafoItrAP_c< V >::GrafoItrAP_c(const GrafoItrAP_c& orig) : g_ptr(orig.g_ptr),cola(orig.cola),marcados(orig.marcados),fin(orig.fin) {
}

template < typename V >
void GrafoItrAP_c< V >::asgGrafo( Grafo< V >& g) {
    g_ptr = shared_ptr< Grafo< V > >(&g);
}

template < typename V >
void GrafoItrAP_c< V >::asgOrigen( int vO ) {
    cola.push(vO);
}

template < typename V >
void GrafoItrAP_c< V >::asgOrigenAlAzar() {
    int t = g_ptr->vecVrt.size();
    std::default_random_engine generador;
    std::uniform_int_distribution<int> distribucion(0, t - 1);
    int inicio = distribucion(generador);
    cola.push(inicio);
}

template < typename V >
void GrafoItrAP_c< V >::clear() {
    g_ptr = 0;
    while (!cola.empty())
        cola.pop();
    marcados.clear();
    fin = false;
}

template < typename V >
GrafoItrAP_c< V >::~GrafoItrAP_c() {
}

/* OPERADORES */

template < typename V >
const V* GrafoItrAP_c< V >::operator->() {
    return &cola.front();
}

template < typename V >
const V& GrafoItrAP_c< V >::operator*() {
    return cola.front();
}

template < typename V >
GrafoItrAP_c< V >& GrafoItrAP_c< V >::operator++() {
    if (!cola.empty()) {
        int listo = cola.front();
        cola.pop();
        marcados.push_back(listo);
        for (vector< int >::const_iterator itr = g_ptr->vecVrt.at(listo).ady.begin();
                itr != g_ptr->vecVrt.at(listo).ady.end(); ++itr)
            if (find(marcados.begin(), marcados.end(), *itr) == marcados.end())
                cola.push(*itr);
    } else fin = true;
}

template < typename V >
bool GrafoItrAP_c< V >::operator==(const GrafoItrAP_c& orig) {
    return ( fin && orig.fin ) || ( cola == orig.cola );
}

template < typename V >
bool GrafoItrAP_c< V >::operator!=(const GrafoItrAP_c& orig) {
    return cola != orig.cola;
}

template < typename V >
GrafoItrAP_c< V >& GrafoItrAP_c< V >::operator=(const GrafoItrAP_c& orig) {
    cola = orig.cola;
    g_ptr = orig.g_ptr;
    marcados = orig.marcados;
    fin = orig.fin;
}

#endif	/* GRAFOITRAP_C_H */

