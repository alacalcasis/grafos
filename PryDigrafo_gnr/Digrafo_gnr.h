/* 
 * File:   Digrafo_gnr.h
 * Author: alan.calderon
 *
 * Created on 3 de noviembre de 2015, 06:30 PM
 */

#ifndef DIGRAFO_GNR_H
#define	DIGRAFO_GNR_H

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "AnchuraConst.h"

template < typename T >
class Digrafo_gnr {
    // Representa un digrafo cuyos vértices son de tipo T.
    // Supuestos sobre T:
    // #1 Tiene un constructor de copias.
    
public:
    /* CONSTRUCTORES */
    
    // Construye un digrafo con los datos del archivo nArch.
    // El archivo debe ser *.txt con datos separados por comas.
    // En la primera aparece la cantidad de actividades N.
    // En el primer bloque de N líneas aparecen los identificadores de los vértices.
    // En el segundo bloque de N líneas aparecen los sucesores de cada vértice:
    // id_vrt, id_vrt_suc1, id_vrt_scu2...    
    Digrafo_gnr(string nArch);
    
    // Construye una copia de orig.
    Digrafo_gnr(const Digrafo_gnr& orig);
    
    virtual ~Digrafo_gnr();

    /* MÉTODOS OBSERVADORES BÁSICOS */
    
    // EFE: retorna true si existe el vértice idVrt.
    bool xstVrt(string idVrt) const;
    
    // REQ: existan en *this los vértices idVrtO e idVrtD.
    // EFE: retorna true si idVrtD es sucesor de idVrtO.
    bool xstDpn(string idVrtO, string idVrtD) const;
    
    // REQ: que exista en *this el vértice idVrt.
    // EFE: retorna un vector de identificadores de vértices sucesores de idVrt.
     const vector<string>& obtSucesores(string idVrt) const;

    // REQ: que exista en *this el vértice idVrt.
    // EFE: retorna un vector de identificadores de vértices predecesores de idVrt.
     const vector<string>& obtPredecesores(string idVrt) const;     
     
    // REQ: que exista en *this el vértice idVrt.
    // EFE: retorna el dato de tipo T cuyo identificador asociado es idVrt.
    T& obtDatoVrt(string idVrt);
     
    // EFE: retorna el total de vértices en *this.
    int obtTotVrt() const;
    
    // EFE: retorna una hilera con sucesores de cada nodo en *this.
    // {<idVrt,idVrt-suc1,idVrt-suc2...>,...}
    string aHil() const;
    
    // EFE: retorna una hilera con predecesores de cada nodo en *this.
    // {<idVrt,dVrt-prd1,idVrt-prd2...>,...}
    string aHilInv() const;
    
    /* MÉTODOS OBSERVADORES NO BÁSICOS */
    
    // EFE: retorna true si existe al menos un ciclo en *this y false en caso
    //      contrario.
    bool xstCiclo() const;

    // REQ: existan en *this los vértices idVrtO e idVrtD.
    // EFE: retorna un vector con todas las rutas posibles entre idVrtO e idVrtD.
    //      cada ruta se representa como un vector de idVrt.
    //      si no existiera ninguna ruta, el vector retorna vacío.
    vector< vector< string > >& rutasEntre(string idVrtO, string idVrtD) const;
    
    /* MODIFICADORES */

    // MOD: *this.
    // EFE: agrega el dato "nv" al vértice indicado por "idVrt".
    void asgDatoVrt(const T& nv, string idVrt);   
    
    /* CREADORES DE ITERADORES */
    typedef AnchuraConst< T > a_const_iterator;
    
    // EFE: retorna una instancia de iterador constante en posición
    //      inicial, que permite un recorrido por anchura sobre *this
    //      empezando por un vértice escogido al azar.
    a_const_iterator& begin() const;

    // EFE: retorna una instancia de iterador constante en posición
    //      inicial, que permite un recorrido por anchura sobre *this
    //      empezando por el vértice identificado por idVrtIn.
    a_const_iterator& begin( string idVrtIn) const;    
    
    // EFE: retorna una instancia de iterador constante en posición
    //      final.    
    a_const_iterator& end() const;
    
private:
    
    template < typename V > // plantilla empotrada, ocupa otra variable de tipo
    struct Nodo {
        V vrt;
        vector< string > sucesores;
        vector< string > predecesores;

        Nodo(): vrt() {
        };

        Nodo(const V& v_init) : vrt(v_init) {
        };

        Nodo(const Nodo& orig) : vrt(orig.vrt), sucesores(orig.sucesores), predecesores(orig.predecesores) {
        };
    };    
    
    typedef map< string, Nodo< T > > T_mapDep;
    T_mapDep mapDep;
    static vector< vector< string > > rsl; // para devolver vector de rutas
};

template < typename T >
vector< vector< string > > Digrafo_gnr< T >::rsl;

template < typename T >
Digrafo_gnr< T >::Digrafo_gnr(string nArch){
}

template < typename T >
Digrafo_gnr< T >::Digrafo_gnr(const Digrafo_gnr& orig) {
}

template < typename T >
Digrafo_gnr< T >::~Digrafo_gnr() {
}

template < typename T >
bool Digrafo_gnr< T >::xstVrt(string idVrt) const {
}

template < typename T >
bool Digrafo_gnr< T >::xstDpn(string idVrtO, string idVrtD) const {
}

template < typename T >
const vector<string>& Digrafo_gnr< T >::obtSucesores(string idVrt) const {
}

template < typename T >
const vector<string>& Digrafo_gnr< T >::obtPredecesores(string idVrt) const {
}

template < typename T >
vector< vector< string > >& Digrafo_gnr< T >::rutasEntre(string idVrtO, string idVrtD) const {
}

template < typename T >
T& Digrafo_gnr< T >::obtDatoVrt(string idVrt) {
}

template < typename T >
int Digrafo_gnr< T >::obtTotVrt() const {
}

template < typename T >
string Digrafo_gnr< T >::aHil() const {
}

template < typename T >
string Digrafo_gnr< T >::aHilInv() const {
}

template < typename T >
bool Digrafo_gnr< T >::xstCiclo() const {
}

template < typename T >
void Digrafo_gnr< T >::asgDatoVrt(const T& nv, string idVrt) {
}

template < typename T >
AnchuraConst< T >& Digrafo_gnr< T >::begin() const {
}

template < typename T >
AnchuraConst< T >& Digrafo_gnr< T >::begin( string idVrtIn) const {
}

template < typename T >
AnchuraConst< T >& Digrafo_gnr< T >::end() const {
}

#endif	/* DIGRAFO_GNR_H */

