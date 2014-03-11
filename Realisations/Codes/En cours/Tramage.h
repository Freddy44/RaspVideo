/*********************************
 * Tramage.h
 *
 *      Author: Frédéric Gicquel
 *
 * Classe qui prépare la trame à envoyer vers le robot
 *********************************/


#ifndef TRAMAGE_H
#define TRAMAGE_H

#include <string.h> //strcpy

#include <iostream>
using namespace std;

class Tramage
{
public:

    /** Constructeur */
    Tramage();

    /* Destructeur */
    virtual ~Tramage();

    /** Méthodes */
    /* Setters */
    void setCommande(char commande);
    /* Getters */
    char* getCommande();
protected:
private:
    /** Méthodes */
    void trameToSpend();
    char to_char(char str);
    /** Attributs */
    char m_trame;
    char m_tramage[14];

};

#endif // TRAMAGE_H
