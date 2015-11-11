/* 
 * File:   main.cpp
 * Author: alan.calderon
 *
 * Created on 3 de noviembre de 2015, 06:29 PM
 */

#include <iostream>
#include <string>
using namespace std;

#include "Digrafo_gnr.h"
/*
 * 
 */
int main(int argc, char** argv) {
    string nombreArchivo = "abe.txt";
    Digrafo_gnr<int> dig_int(nombreArchivo);
    
    for(Digrafo_gnr<int>::a_const_iterator itr = dig_int.begin();
            itr != dig_int.end();
            ++itr)
        cout << *itr << ",";
    cout << endl;
    
    for(Digrafo_gnr<int>::a_const_iterator itr = dig_int.begin("I");
            itr != dig_int.end();
            ++itr)
        cout << *itr << ",";
    cout << endl;
    return 0;
}

