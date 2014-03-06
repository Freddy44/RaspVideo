/*********************************
 * Uart.cpp
 *
 *      Author: Frédéric Gicquel
 *
 *********************************/


#include "Uart.h"

/*** Constructeur ***/
Uart::Uart()
{
    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (0.0): Constructeur \E[m\n"; // jaune
}
/*** Destructeur ***/
Uart::~Uart()
{
    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (1.0): Destructeur \E[m\n";

}


/***
* Méthode uartInit(void)
* Création d'un port série (fichier)
* @param:
* @return: int port //fichier avec ses caractéristiques
*/
int Uart:: uartInit(void)
{
    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (2.0): uartInit(void) \E[m\n";

    //int port;

    //termios - Structure contenant les options de manipulation du port
    struct termios specs; // specs => pour les options de configuration

    /************************/
    /*** Creation du port ***/
    /************************/

    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (2.1): uartInit(void) : Creation du portSerie \E[m\n";

    //Ouverture du port et stockage du fichier de description du port
    //port = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    //Port Usb : sur raspberry/pc =>arduino
    m_port = open("/dev/ttyACM0",O_CREAT| O_RDWR | O_NOCTTY| O_NONBLOCK |O_TRUNC );// | O_NDELAY);
    if (m_port == -1)
    {
        // Could not open the port
        perror("open_port: Unable to open ttyUSB0 - ");
    }
    else
    {
        //leave this en mode non bloquant => |O_NONBLOCK
        fcntl(m_port, F_SETFL, fcntl(m_port,F_GETFL)&~O_NONBLOCK);
    }

    /***********************************/
    /*** Configuration de la liaison ***/
    /***********************************/

    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (2.2): uartInit(void) : Configuration de la liaison \E[m\n";
    /*Retrieving and changing terminal settings
    tcgetattr() gets the parameters associated with the object referred  by
    port  and  stores  them in the termios structure referenced by termios_p.
    This function may be invoked from a background  process;  however,  the
    terminal  attributes  may  be  subsequently  changed  by  a  foreground
    process.*/
    //lecture des paramètres courant
    tcgetattr(m_port, &specs);


    /*tcflag_t c_cflag;*/      /* modes de contrôle */
    /*9600 baud
      CS8 8 bits n 1
      CLOCAL connexion locale, pas de contrôle par le modem
      CREAD  permet la réception des caractères
      CRTSCTS : contrôle de flux matériel (uniquement utilisé si le câble a
     les lignes nécessaires.
    */
    specs.c_cflag = (9600 |CS8| CLOCAL | CREAD);// |CRTSCTS ); //control flags


    /*tcflag_t c_oflag;*/      /* modes de sorties */
    /*OPOST  Enable implementation-defined output processing.
          CR3 - delay of 150ms after transmitting every line
    */
    specs.c_oflag = (OPOST | CR3);


    /*
     ICANON  : active l'entrée en mode canonique
     désactive toute fonctionnalité d'echo, et n'envoit pas de signal au
     programme appelant.
     specs.c_lflag = ICANON;
    */
    /*tcflag_t c_lflag;*/      /* modes locaux */
    /* positionne le mode de lecture (non canonique, sans echo, ...) */
    /* L'entrée non canonique va prendre en charge un nombre fixé de caractère par lecture, et 		autorise l'utilisation d'un compteur de temps pour les caractères. Ce mode doit être utilisé si 	votre application lira toujours un nombre fixé de caractères*/
    specs.c_lflag = 0;
    //specs.c_lflag = ICANON;


    /*
     IGNPAR  : ignore les octets ayant une erreur de parité.
     ICRNL   : transforme CR en NL (sinon un CR de l'autre côté de la ligne
     ne terminera pas l'entrée).
     sinon, utiliser l'entrée sans traitement (device en mode raw).
    */
    specs.c_iflag = IGNPAR |ICRNL;//| IGNCR;


    /* cc_t c_cc[NCCS]; */     /* Caractères de contrôle */
    /* Caracteres immediatement disponibles */
    specs.c_cc[VMIN] = 1;	/*  en mode non-canonique, spécifie le nombre de caractéres que doit contenir le tampon pour être accessible à la lecture. En général, on fixe cette valeur à 1. */
    specs.c_cc[VTIME] = 0;	/* en mode non-canonique, spécifie, en dixièmes de seconde, le temps au bout duquel un caractère devient accessible, même si le tampon ne contient pas c_cc[VMIN] caractères. Une valeur de 0 représente un temps infini.  */

    //our custom specifications set to the port
    //TCSANOW - constant that prompts the system to set
    //specifications immediately.

    /* pour éliminer tous les caractères reçus par le noyau mais non encore lus par read()
    */
    tcflush(m_port, TCIFLUSH);

    /******************************************/
    /*** Sauvegarde des nouveaux paramètres ***/
    /******************************************/
    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (2.3): uartInit(void) : Sauvegarde de la config du portSerie \E[m\n";

    /* tcsetattr() sets the parameters associated with  the  terminal  (unless
        support is required from the underlying hardware that is not available)
        from the termios structure referred to by termios_p.   optional_actions
        specifies when the changes take effect:
    TCSANOW - constant that prompts the system to set*/
    tcsetattr(m_port,TCSANOW,&specs);

    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (2.4): uartInit(void): Retour de l'identitee du portSerie \E[m\n";

    return (m_port);
}


int Uart::getPort()
{
    uartInit();
    int port = m_port;
    return port;
}

void Uart::uartClose()
{
    close (m_port);

}

/***
* Méthode send_data(char* commande, int port)
* Envoie de données à l'autre bout du port série
* @param: char* trame // Trame encapsulant les données
* @param: int port // Port série par lequel transit les données
* @return:
*/
void Uart::send_data(char* trame, int port)
{

    int envoie=0;
    /* Passe en mode bloquant */
    fcntl(port,F_SETFL,fcntl(port,F_GETFL)&~O_NONBLOCK);

    printf("test fonction send_data\n");

    /*envoie des caractères*/
    if ((envoie=(write(port,trame,16))) == -1)
    {
        perror("probleme ecriture:");
    }

    printf("envoie:%s\n",trame);
    printf("envoie:%d\n",envoie);

    /* Repasse en mode non-bloquant */
    fcntl(port,F_SETFL,fcntl(port,F_GETFL)|O_NONBLOCK);

}

/***
* Méthode read_data(int port)
* Lecture de données arrivant de l'autre bout du port série
* @param: int port // Port série par lequel transit les données
* @return:
*/
void Uart::read_data(int port)
{

    /* Passe en mode bloquant */
    fcntl(port,F_SETFL,fcntl(port,F_GETFL)&~O_NONBLOCK);


    printf("test fonction read_data\n");

    char buf[17]= {0};
    int reception=0;

    /*reception des caractères*/
    reception=read (port,buf,14);
    if (reception == -1)
    {
        close(port);
        perror("Erreur reception fichier");
        exit(EXIT_FAILURE);
    }
    usleep(50000);
    printf("retour:%s\n",buf);
    printf("retour:%d\n",reception);

}

