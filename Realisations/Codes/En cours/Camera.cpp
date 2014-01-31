/*********************************
 * Camera.cpp
 *
 *      Author: Frédéric Gicquel
 *
 *********************************/

#include "Camera.h"

/*** Constructeur ***/
Camera::Camera()
{
    /* Contrôle dans un terminal :
     * \E[3x;1m ... \E[m : couleur d'affichage (30 < x < 37) => ici rouge
     */
    cout  <<  "\E[31;1m Camera::constructeur(1.0) :\E[m\n";

    /* Appel de la méthode open() */
    open();
}

/*** Destructeur ***/
Camera::~Camera()
{
    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::destructeur() :\E[m\n";

    /* Appel de la méthode close() */
    close();
}


/***
* Méthode open()
* => Ouverture du flux caméra
* @param:
* @return: m_Capture => Structure de capture vidéo : Paramètre utilisé seulement pour les fonctions de capture vidéo
*/
CvCapture* Camera::open()
{
    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::open(1.1) :\E[m\n";

    /*
    * C: CvCapture* cvCaptureFromCAM(int device)
    * Constructeur d'un objet VideoCapture
    * @param: 0 => la seule caméra connectée
    */
    m_Capture = cvCaptureFromCAM(0);

    /* Vérification de l'ouverture de la caméra */
    if( !m_Capture )
    {
        fprintf( stderr, "ERROR: capture is NULL \n" );
        getchar();
        exit(0);
    }

    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::open(1.2) :\E[m\n";

    return m_Capture;
}


/***
* Méthode close()
* => Fermeture du flux caméra
* @param:
* @return:
*/
void Camera::close()
{
    /* Libération de la mémoire */
    /*
    * C: void cvReleaseCapture(CvCapture** capture)
    * => Libère la structure de CvCapture alloué : Ferme le flux caméra
    */
    cvReleaseCapture( &m_Capture );

    /*
    * C: void cvReleaseImage(IplImage** image)
    * => Désalloue la mémoire associée à l'image créée
    * @param: m_frame
    */
    cvReleaseImage(&m_frame);

    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::close(4) :\E[m\n";
}


/***
* Méthode grabOneFrame()
* => Attrape et Décompresse l'image
* @param:
* @return: m_frame => Image décodée et numérisée
*/
IplImage* Camera::grabOneFrame()
{
    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::grabOneFrame(1.3) :\E[m\n";

    /* Vérification de la capture */
    if (!m_Capture)
        //if (!c_kthread->startThread((void*) "cam"))
    {
        /* Contrôle dans un terminal */
        cout << "\E[31;1m Camera::grabOneFrame : Camera close \E[m\n";
        exit(0);
    }
    /*
     * C: IplImage* cvQueryFrame( CvCapture* capture );
     * combinent cvGrabFrame et cvRetrieveFrame en un seul appel.
     * cvGrabFrame :  Le but de cette fonction est de saisir la trame, l'image, très rapide.
     * cvRetrieveFrame retourne le pointeur à l'image attrapé avec fonction cvGrabFrame.
     * @return: cadre attrapé => image attrapée et numérisé
     */
    m_frame = cvQueryFrame(m_Capture);

    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::grabOneFrame(1.4) : m_frame\E[m\n";

    return m_frame;
}

/***
* Méthode getFrame()
* => retourne l'image traitée avec la méthode grabOneFrame()
* @param:
* @return: m_frame => Image décodée et numérisée
*/
IplImage* Camera::getFrame()
{
    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::getFrame(1.5) :\E[m\n";

    /* Appel de la méthode */
    grabOneFrame();

    return m_frame;// = cvQueryFrame(m_Capture);

}
