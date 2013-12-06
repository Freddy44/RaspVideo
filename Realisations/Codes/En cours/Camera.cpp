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
    /* Contrôle dans un terminal :
     *
     * \E[3x;1m ... \E[m : couleur d'affichage (30 < x < 37) => ici rouge
     *
     */
    cout  <<  "\E[31;1m Camera::constructeur(1.0) :\E[m\n";

    /* Appel de la méthode open() */
    open();


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
    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::open(1.1) :\E[m\n";
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
        //c_kthread->isClose();
        exit(0);
    }

    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::open(1.2) :\E[m\n";

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
     * C: IplImage* cvRetrieveFrame(CvCapture* capture, int streamIdx=0 )
     * combinent VidéoCapture :: grab () et VidéoCapture :: récupérer () en un seul appel.
     * Lecture de fichiers vidéo ou la capture de données de décodage
     * L'image ne peut pas etre travaillée directement
     * @return: cadre attrapé => image attrapée et numérisé
     */
    m_frame = cvQueryFrame(m_Capture);

    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::grabOneFrame(1.4) : m_frame\E[m\n";

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
    /* Contrôle dans un terminal */
    cout << "\E[31;1m Camera::getFrame(1.5) :\E[m\n";

    /* Appel de la méthode */
    grabOneFrame();

    return m_frame;// = cvQueryFrame(m_Capture);

}
