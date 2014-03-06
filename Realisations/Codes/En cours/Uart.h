/*********************************
 * Uart.h
 *
 *      Author: Frédéric Gicquel
 *
 *********************************/



#ifndef UART_H
#define UART_H

#include <stdio.h>     // Standard input/output definitions
#include <string.h>    // String function definitions
#include <unistd.h>   // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>     // Error number definitions
#include <termios.h>  // POSIX terminal control definitions
#include <stdlib.h>	//malloc/calloc/free/exit


#include <iostream>
using namespace std;


class Uart
{
public:
    /* Constructeur */
    Uart();
    /* Destructeur */
    virtual ~Uart();

    /* Méthodes */
    int uartInit();
    void uartClose();
    void send_data(char* commande, int port);
    void read_data(int port);

    /* Setters */
    int getPort();

protected:
private:
    /*Attributs*/
    int m_port;
};

#endif // UART_H
