/*********************************
 * Uart.cpp
 *
 *      Author: Frédéric Gicquel
 *
 *********************************/

#include "Tramage.h"

/*** Constructeur ***/
Tramage::Tramage()
{
    /* Contrôle dans un terminal */
    cout << "\E[34;1m Tramage (0.0): Constructeur \E[m\n"; //bleu
}

/*** Destructeur ***/
Tramage::~Tramage()
{
    /* Contrôle dans un terminal */
    cout << "\E[34;1m Tramage (1.0): Destructeur \E[m\n";
}


/***
* Setter setCommande(char commande)
* Récupération de la commande a convertir en trame
* @param: char commande
*/
void Tramage::setCommande(char commande)
{
    /* Contrôle dans un terminal */
    cout << "\E[34;1m Tramage (2.0): setCommande \E[m\n";
    m_trame = commande;
}



/***
* Méthode
* Convertion de la commande en trame
* @param:
*/
void Tramage::trameToSpend()
{
    /* Contrôle dans un terminal */
    cout << "\E[34;1m Tramage (3.0): trameToSpend \E[m\n";
    switch (m_trame)
    {

        /** Commande pour tourner à gauche */
    case 1:
        m_tramage[0] = '-';
        m_tramage[1] = '0';
        m_tramage[2] = '0';
        m_tramage[3] = '1';
        m_tramage[4] = '0';
        m_tramage[5] = '+';
        m_tramage[6] = '0';
        m_tramage[7] = '0';
        m_tramage[8] = '0';
        m_tramage[9] = '0';
        m_tramage[10] = '0';
        m_tramage[11] = '0';
        m_tramage[12] = '\r';
        m_tramage[13] = '\n';
        /* Contrôle dans un terminal */
        cout << "\E[34;1m Tramage (3.1): trameToSpend => gauche\E[m\n";
        break;

        /** Commande pour tourner à Droite */
    case 2:
        m_tramage[0] = '+';
        m_tramage[1] = '0';
        m_tramage[2] = '0';
        m_tramage[3] = '1';
        m_tramage[4] = '0';
        m_tramage[5] = '+';
        m_tramage[6] = '0';
        m_tramage[7] = '0';
        m_tramage[8] = '0';
        m_tramage[9] = '0';
        m_tramage[10] = '0';
        m_tramage[11] = '0';
        m_tramage[12] = '\r';
        m_tramage[13] = '\n';
        /* Contrôle dans un terminal */
        cout << "\E[34;1m Tramage (3.2): trameToSpend => droite \E[m\n";
        break;

        /** Commande pour attendre */
    case 3:
        m_tramage[0] = '+';
        m_tramage[1] = '0';
        m_tramage[2] = '0';
        m_tramage[3] = '0';
        m_tramage[4] = '0';
        m_tramage[5] = '+';
        m_tramage[6] = '0';
        m_tramage[7] = '0';
        m_tramage[8] = '0';
        m_tramage[9] = '0';
        m_tramage[10] = '0';
        m_tramage[11] = '0';
        m_tramage[12] = '\r';
        m_tramage[13] = '\n';
        /* Contrôle dans un terminal */
        cout << "\E[34;1m Tramage (3.3): trameToSpend => attente \E[m\n";
        break;

        /** Commande pour avancer */
    case 4:
        m_tramage[0] = '+';
        m_tramage[1] = '0';
        m_tramage[2] = '0';
        m_tramage[3] = '0';
        m_tramage[4] = '0';
        m_tramage[5] = '+';
        m_tramage[6] = '0';
        m_tramage[7] = '0';
        m_tramage[8] = '1';
        m_tramage[9] = '0';
        m_tramage[10] = '0';
        m_tramage[11] = '0';
        m_tramage[12] = '\r';
        m_tramage[13] = '\n';
        /* Contrôle dans un terminal */
        cout << "\E[34;1m Tramage (3.4): trameToSpend => avancer \E[m\n";
        break;

        /** Commande pour Tracker la cible */
    case 5:

        /* Contrôle dans un terminal */
        cout << "\E[34;1m Tramage (3.5): trameToSpend => tracker \E[m\n";
        break;

    default:
        cout<<"\E[34;1m Tramage (3.6):Error, bad input, quitting \E[m\n";
        break;
    }
}


/***
* Getter getCommande()
* Retourne la trame envoyé vers l'arduino
* @return: char trame
*/
char* Tramage::getCommande()
{
    /* Contrôle dans un terminal */
    cout << "\E[34;1m Tramage (4.0): getCommande \E[m\n";
    trameToSpend();
    char* trame = 0;
    trame =  m_tramage;
    return trame;
}
