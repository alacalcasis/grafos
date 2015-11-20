/* 
 * File:   AnchuraConst.h
 * Author: alan.calderon
 *
 * Created on 9 de noviembre de 2015, 05:10 PM
 */

#ifndef ANCHURACONST_H
#define	ANCHURACONST_H

#include "Digrafo_gnr.h" // sustituye a la declaración adelantada.

template< typename T >
class AnchuraConst {
    // Representa un iterador sobre un DigrafoGnr que permitirá
    // a un programa de aplicación hacer un recorrido por anchura
    // sobre el digrafo asociado.
    
    friend class Digrafo_gnr< T >;
    
public:

    AnchuraConst(const AnchuraConst& orig);
    virtual ~AnchuraConst();

    // EFE: avanza *this a la siguiente posición válida.
    AnchuraConst& operator++();
    
    // EFE: si *this != end(), retorna referencia de objeto de tipo T apuntado.
    const T& operator*();
    
    // EFE: si *this != end(), retorna puntero a objeto de tipo T apuntado.    
    const T* operator->();
    
    // EFE: retorna true si el estado de *this es idéntico al de o.
    bool operator==(const AnchuraConst< T >& o);
    
    // EFE: retorna true si el estado de *this es diferente al de o.
    bool operator!=(const AnchuraConst< T >& o);
    
    // EFE: copia en *this estado de o.
    void operator=(const AnchuraConst< T >& o);
    
private:
    
    // EFE: construye una instancia asociada al digrafo dgf.
    // El recorrido iniciará en un vértice escogido al azar.
    // Sólo puede ser invocado por Digrafo_gnr::begin() y por
    // Digrafo_gnr::end().
    AnchuraConst(const Digrafo_gnr< T >& dgf);

    // EFE: construye una instancia asociada al digrafo dgf.
    // El recorrido iniciará en el vértice identificado por idVrtI.
    // Sólo puede ser invocado por Digrafo_gnr::begin(string).    
    AnchuraConst(const Digrafo_gnr< T >& dgf, string idVrtI);
};

template< typename T >
AnchuraConst< T >::AnchuraConst(const Digrafo_gnr< T >& dgf) {
}

template< typename T >
AnchuraConst< T >::AnchuraConst(const Digrafo_gnr< T >& dgf, string idVrtI) {
}

template< typename T >
AnchuraConst< T >::AnchuraConst(const AnchuraConst& orig) {
}

template< typename T >
AnchuraConst< T >::~AnchuraConst() {
}

template< typename T >
AnchuraConst< T >& AnchuraConst< T >::operator++() {
}

template< typename T >
const T& AnchuraConst< T >::operator*() {
}

template< typename T >
const T* AnchuraConst< T >::operator->() {
}

template< typename T >
bool AnchuraConst< T >::operator==(const AnchuraConst< T >& o) {
}

template< typename T >
bool AnchuraConst< T >::operator!=(const AnchuraConst< T >& o) {
}

template< typename T >
void AnchuraConst< T >::operator=(const AnchuraConst< T >& o) {
}
#endif	/* ANCHURACONST_H */

