/*************************************************************************
 * Uart.h
 *
 *      Author: Frédéric Gicquel
 *
 *  Classe qui : 1.Ouvre une connexion USB : ttyACM0 => port arduino vu du Rpi
                 2.Envoie une trame
                 3.Lis une trame
 *************************************************************************/



#ifndef UART_H
#define UART_H

#include <stdio.h>      // Standard input/output definitions
#include <fcntl.h>      // File control definitions
#include <termios.h>    // POSIX terminal control definitions
#include <stdlib.h>     //malloc/calloc/free/exit

#include <iostream>
using namespace std;


class Uart
{
public:
    /** Constructeur */
    Uart();
    /** Destructeur */
    virtual ~Uart();

    /** Méthodes */
    int uartInit();
    void uartClose();
    void send_data(char* commande, int port);
    void read_data(int port);

    /** Setters */
    int getPort();

protected:
private:
    /** Attributs*/
    int m_port;
};

#endif // UART_H
