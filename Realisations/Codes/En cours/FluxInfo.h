/*
 * FluxInfo.h
 *
 *      Author: Frédéric Gicquel
 *
 *  Classe qui
 *  @return:
 *
 */


#ifndef FLUXINFO_H
#define FLUXINFO_H

#include <sstream>      // std::ostringstream
#include <iostream>
#include <fstream>
using namespace std;

class FluxInfo
{
public:
    FluxInfo();
    virtual ~FluxInfo();

    //Méthodes
    void fluxOpen();
    void fluxClose();
    void fluxWrite();

    static void memory_usage();

protected:
private:
    //Déclaration d'un flux permettant d'écrire un fichier.
    ofstream monFlux;



};

#endif // FLUXINFO_H
