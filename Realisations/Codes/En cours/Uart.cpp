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

    /* termios - Structure contenant les options de manipulation du port */
    struct termios specs; // specs => pour les options de configuration

    /************************/
    /*** Creation du port ***/
    /************************/

    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (2.1): uartInit(void) : Creation du portSerie \E[m\n";

    /** Ouverture du port et stockage du fichier de description du port*/
    //port = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    /* Méthode open()
    * @param: "/dev/ttyACM0" => nom du port à ouvrir
    * @param: O_CREAT => créér le fichier si inexistant
    * @param: O_RDWR => en mode lecture/écriture
    * @param: O_NOCTTY => afin de déterminer si ce port doit etre le controlant du processus (tty)
    * @param: O_NONBLOCK => Pour ne pas laisser le processus appelant en attente
    * @param: O_TRUNC => si le fichier existe, il sera troncker
    * @return: m_port => pointeur sur le descripteur de fichier
    */
    //Port Usb : sur raspberry/pc =>arduino
    m_port = open("/dev/ttyACM0",O_CREAT| O_RDWR | O_NOCTTY| O_NONBLOCK |O_TRUNC  );

    /* Afin de vérifier que le fichier est bien ouvert */
    if (m_port == -1)
    {
        perror("open_port: Unable to open ttyACM0 ");
    }
    else
    {
        /* Afin de se livrer à des opérations sur le descripteur du port */
        /* Méthode fcntl() : int fcntl(int fd, int cmd, struct flock *lock);
        * @param: m_port => pointeur sur le fichier du port
        * @param: F_SETFL => Positionner les nouveaux attributs d'état pour le fichier à la valeur indiquée par arg (= O_NONBLOCK)
        * @param: fcntl(m_port,F_GETFL)&~O_NONBLOCK => callback afin de maintenir le port en mode bloqué
        */
        fcntl(m_port, F_SETFL, fcntl(m_port,F_GETFL)&~O_NONBLOCK);
    }

    /***********************************/
    /*** Configuration de la liaison ***/
    /***********************************/

    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (2.2): uartInit(void) : Configuration de la liaison \E[m\n";

    /* Les fonctions termios établissent une interface générale sous forme de terminal, permettant de contrôler les ports de communication asynchrone*/
    /*Fonction int tcgetattr(int fd, struct termios *termios_p);
    * récupère les paramètres associés à l'objet référencé par fd et les stocke dans la structure termios pointée par termios_p
    * @param: m_port => nom du fichier
    * @param: &specs => pointeur sur les @ des parametres
    */
    tcgetattr(m_port, &specs);

    /** Modes de contrôle */
    /*tcflag_t c_cflag;
    * @param: 9600 baud
    * @param: CS8 => 8 bits n 1
    * @param: CLOCAL => connexion locale, pas de contrôle par le modem
    * @param: CREAD  => permet la réception des caractères
    * @return: specs.c_cflag => paramètres de contrôle
    */
    specs.c_cflag = (9600 |CS8| CLOCAL | CREAD);

    /** Modes de sorties */
    /*tcflag_t c_oflag;
    * @param: OPOST =>  Traitement en sortie dépendant de l'implémentation
    * @param: CR3 => Masque du délai du retour chariot fixé à 150ms
    * @return: specs.c_oflag => paramètres de sortie
    */
    specs.c_oflag = (OPOST | CR3);

    /** Modes locaux */
    /*
     ICANON  : active l'entrée en mode canonique
     désactive toute fonctionnalité d'echo, et n'envoit pas de signal au
     programme appelant.
     specs.c_lflag = ICANON;
    */
    /*tcflag_t c_lflag;
    * Positionne le mode de lecture (non canonique, sans echo, ...)
    * L'entrée non canonique va prendre en charge un nombre fixé de caractère par lecture, et
    * autorise l'utilisation d'un compteur de temps pour les caractères. Ce mode doit être utilisé si
    * votre application lira toujours un nombre fixé de caractères
    */
    specs.c_lflag = 0;

    /** Modes d'entrée */
    /*
    * @param: IGNPAR => ignore les octets ayant une erreur de parité.
    * @param: ICRNL  => transforme CR en NL (sinon un CR de l'autre côté de la ligne
    * ne terminera pas l'entrée).
    * @return: specs.c_iflag => paramètres d'entrée
    */
    specs.c_iflag = IGNPAR |ICRNL;

    /** Caractères de contrôle */
    /* cc_t c_cc[NCCS]; */
    /* Caracteres immediatement disponibles */
    specs.c_cc[VMIN] = 1;	/*  en mode non-canonique, spécifie le nombre de caractéres que doit contenir le tampon pour être accessible à la lecture. En général, on fixe cette valeur à 1. */
    specs.c_cc[VTIME] = 0;	/* en mode non-canonique, spécifie, en dixièmes de seconde, le temps au bout duquel un caractère devient accessible, même si le tampon ne contient pas c_cc[VMIN] caractères. Une valeur de 0 représente un temps infini.  */


    /*
    *  élimine toutes les écritures sur l'objet fd pas encore transmises, ainsi que les données reçues mais pas encore lues, ceci en fonction de la valeur de queue_selector :
    */
    tcflush(m_port, TCIFLUSH);

    /******************************************/
    /*** Sauvegarde des nouveaux paramètres ***/
    /******************************************/
    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (2.3): uartInit(void) : Sauvegarde de la config du portSerie \E[m\n";

    /* tcsetattr() fixe les paramètres du terminal
    * @param: m_port => Pointeur sur le descripteur du port
    * @param: TCSANOW => Les modifications sont effectuées immédiatement.
    * @param: &specs => Paramètres à fixer
    */
    tcsetattr(m_port,TCSANOW,&specs);

    /* Contrôle dans un terminal */
    cout << "\E[33;1m Uart (2.4): uartInit(void): Retour de l'identitee du portSerie \E[m\n";

    return (m_port);
}

/***
* Méthode uartClose()
* Ferme le port
* @param:
* @return:
*/
void Uart::uartClose()
{
    close (m_port);
}

/***
* Getter Méthode getPort()
* renvoie un id sur le descripteur du port
* @param:
* @return:
*/
int Uart::getPort()
{
    uartInit();
    int port = m_port;
    return port;
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

