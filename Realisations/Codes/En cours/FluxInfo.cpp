/*
 * FluxInfo.cpp
 *
 *      Author: Frédéric Gicquel
 *
 */
#include "FluxInfo.h"

/* Constructeur */
FluxInfo::FluxInfo()
{
    //ctor
}

/* Destructeur */
FluxInfo::~FluxInfo()
{
    //dtor
}

/*
* Méthode
*
* @param:
* @return:
*/
void FluxInfo::fluxOpen()
{
    //Ouvre un fichier texte
    //monFlux.open("~/SEICOM/2013_14/Cours_2013_14/Projet/RaspVideo_/RaspVideo/bin/Debug/nano testEcriture");
    monFlux.open("nano testEcriture");
    //    monFlux.open(testEcriture.c_str());

    if(!monFlux)    //On teste si tout est OK.
    {
        /* Contrôle dans un terminal */
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}

/*
* Méthode
*
* @param:
* @return:
*/
void FluxInfo::fluxClose()
{
    monFlux.close(); //On finit par refermer le fichier
}

/*
* Méthode
*
* @param:
* @return:
*/
void FluxInfo::fluxWrite()
{
    //Tout est OK. On peut utiliser le fichier
    monFlux << "EXTRA ouverture fichier" << endl;

}

/* Connaitre la charge du cpu */
void FluxInfo:: memory_usage()
{
    ostringstream mem;
    string test;
    //PP("hi");
    /*ifstream proc("/proc/self/status");
    string s;
    while(getline(proc, s), !proc.fail())
    {
        if(s.substr(0, 6) == "VmSize")
        {
            mem << s;
            return mem.str();
        }
        test = mem.str();
    }*/
    ofstream cpuFlux("/proc/self/status");
    cout <<cpuFlux << endl;
    //return mem.str();
    //return cpuFlux();
}



