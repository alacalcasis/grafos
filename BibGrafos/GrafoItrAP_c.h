/* 
 * File:   GrafoItrAP_c.h
 * Author: alan.calderon
 *
 * Created on 18 de noviembre de 2015, 12:10 PM
 */

#ifndef GRAFOITRAP_C_H
#define	GRAFOITRAP_C_H

#include <deque>
#include <random>
#include <chrono>
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
    void asgNvoOrigenDeFaltantesAlAzar(); // sólo para ser usado por operator++ para reiniciar recorrido
    void clear(); // limpia el itr_begin de Grafo< V >.

    Grafo< V >* g_ptr; // puntero al grafo que se va a recorrer
    deque< int > cola; // para el recorrido anchura-primero del grafo
    vector< int > marcados; // para evitar recorrer dos veces el mismo vértice
    bool fin; // variable que representa la terminación del recorrido
};

template < typename V >
GrafoItrAP_c< V >::GrafoItrAP_c() : g_ptr(0) {
}

template < typename V >
GrafoItrAP_c< V >::GrafoItrAP_c(const GrafoItrAP_c& orig) : g_ptr(orig.g_ptr), cola(orig.cola), marcados(orig.marcados), fin(orig.fin) {
}

template < typename V >
void GrafoItrAP_c< V >::asgGrafo(Grafo< V >& g) {
    g_ptr = &g;
}

template < typename V >
void GrafoItrAP_c< V >::asgOrigen(int vO) {
    cola.push_back(vO);
}

template < typename V >
void GrafoItrAP_c< V >::asgOrigenAlAzar() {
    int t = g_ptr->vecVrt.size();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generador(seed);
    std::uniform_int_distribution<int> distribucion(0, t - 1);
    int inicio = distribucion(generador);
    cola.push_back(inicio);
}

template < typename V >
void GrafoItrAP_c< V >::asgNvoOrigenDeFaltantesAlAzar() {
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
    cola.push_back(faltantes[inicio]);
}

template < typename V >
void GrafoItrAP_c< V >::clear() {
    g_ptr = 0;
    while (!cola.empty())
        cola.pop_front();
    marcados.clear();
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
        int listo;
        listo = cola.front();
        cola.pop_front();
        marcados.push_back(listo);
        for (vector< int >::const_iterator itr = g_ptr->vecVrt.at(listo).ady.begin();
                itr != g_ptr->vecVrt.at(listo).ady.end(); ++itr)
            if ((find(marcados.begin(), marcados.end(), *itr) == marcados.end()) &&
                    (find(cola.begin(), cola.end(), *itr) == cola.end())) {
                int nuevo = *itr;
                cola.push_back(*itr);
            }
        if ((cola.empty())&&(marcados.size() < g_ptr->vecVrt.size()))
            asgNvoOrigenDeFaltantesAlAzar();
    }
}

template < typename V >
bool GrafoItrAP_c< V >::operator==(const GrafoItrAP_c& orig) {
    return (cola == orig.cola);
}

template < typename V >
bool GrafoItrAP_c< V >::operator!=(const GrafoItrAP_c& orig) {
    return !(*this == orig);
}

template < typename V >
GrafoItrAP_c< V >& GrafoItrAP_c< V >::operator=(const GrafoItrAP_c& orig) {
    cola = orig.cola;
    g_ptr = orig.g_ptr;
    marcados = orig.marcados;
}

#endif	/* GRAFOITRAP_C_H */

