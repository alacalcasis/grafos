/* 
 * File:   newsimpletest.cpp
 * Author: alan.calderon
 *
 * Created on 05/11/2015, 02:53:46 PM
 */

#include <stdlib.h>
#include <iostream>
#include "Grafo.h"

/*
 * Simple C++ Test Suite
 */

void testCiclos() {
    int x;
    string& hsal;
    Grafo grafo;
    bool result = grafo.ciclos(x, hsal);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testCiclos (newsimpletest) message=error message sample" << std::endl;
    }
}

void testObtAdy() {
    int vrt;
    Grafo grafo;
    vector<int>& result = grafo.obtAdy(vrt);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testObtAdy (newsimpletest) message=error message sample" << std::endl;
    }
}

void testObtTotVrt() {
    Grafo grafo;
    long result = grafo.obtTotVrt();
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testObtTotVrt (newsimpletest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testCiclos (newsimpletest)" << std::endl;
    testCiclos();
    std::cout << "%TEST_FINISHED% time=0 testCiclos (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testObtAdy (newsimpletest)" << std::endl;
    testObtAdy();
    std::cout << "%TEST_FINISHED% time=0 testObtAdy (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testObtTotVrt (newsimpletest)" << std::endl;
    testObtTotVrt();
    std::cout << "%TEST_FINISHED% time=0 testObtTotVrt (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

