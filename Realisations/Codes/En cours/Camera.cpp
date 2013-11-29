/*
 * Camera.cpp
 *
 *      Author: Frédéric Gicquel
 *
 */

#include "Camera.h"

/* Constructeur */
Camera::Camera()
{
    /* Instanciation de la composition avec la classe VideoThread */
    c_kthread = new VideoThread();

    // Initialisation
    c_kthread->isClose();

    /* Appel de la méthode open() */
    open();

    /* Contrôle dans un terminal :
     *
     * \E[3x;1m ... \E[m : couleur d'affichage (30 < x < 37) => ici rouge
     *
     */
    cout  <<  "\E[31;1m Camera::constructeur(0) :\E[m\n";
}

/* Destructeur */
Camera::~Camera()
{
    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::destructeur() :\E[m\n";

    /* Appel de la méthode close() */
    close();
}

/*
* Méthode close()
* => Fermeture du flux caméra
* @param:
* @return:
*/
void Camera::close()
{
    /* Fermeture du thread camera */
    c_kthread->isClose();

    /* Libération de la mémoire */
    /*
    * C: void cvReleaseCapture(CvCapture** capture)
    * Ferme la caméra
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

/*
* Méthode open()
* => Ouverture du flux caméra
* @param:
* @return: m_Capture =>
*/
CvCapture* Camera::open()
{
    /*
    * C: CvCapture* cvCaptureFromCAM(int device)
    * Constructeur d'un objet VideoCpature
    * @pparam: 0 => la seule caméra connectée
    */
    m_Capture = cvCaptureFromCAM(0);

    /* Vérification de l'ouverture de la caméra */
    if( !m_Capture )
    {
        fprintf( stderr, "ERROR: capture is NULL \n" );
        getchar();
        c_kthread->isClose();
        exit(0);
    }

    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::open(1) :\E[m\n";

    /* Ouverture du thread caméra */
    c_kthread->isOpen();


    return m_Capture;
}

/*
* Méthode grabOneFrame()
* =>Décode et numérise une trame
* @param:
* @return: m_frame => Image décodée et numérisée
*/
//callback
IplImage* Camera::grabOneFrame()
{
    //Décode et renvoie la trame vidéo numérisée.
    //m_frame = cvRetrieveFrame(m_Capture);

    /* Vérification du thread caméra */
    if (!c_kthread->isOpen())
    {
        /* Contrôle dans un terminal */
        cout << "\E[31;1m Camera close :\E[m\n";
        exit(0);
    }
    /*
     * C: IplImage* cvRetrieveFrame(CvCapture* capture, int streamIdx=0 )
     * combinent VidéoCapture :: grab () et VidéoCapture :: récupérer () en un seul appel.
     * Lecture de fichiers vidéo ou la capture de données de décodage
     * L'image ne peut pas etre travaillée directement
     * @return: cadre attrapé => image attrapée et numérisé
     */
    m_frame = cvQueryFrame(m_Capture);

    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::grabOneFrame(2) :\E[m\n";

    return m_frame;
}

/*
* Méthode getFrame()
* => retourne l'image attrapée et numérisée
* @param:
* @return: m_frame => Image décodée et numérisée
*/
IplImage* Camera::getFrame()
{
    /* Appel de la méthode */
    grabOneFrame();

    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::getFrame(3) :\E[m\n";

    return m_frame;// = cvQueryFrame(m_Capture);

}

