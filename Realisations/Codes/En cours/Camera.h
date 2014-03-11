/*********************************************************
 * Camera.h
 *
 *      Author: Frédéric Gicquel
 *
 *  Classe qui capture le flux vidéo et renvoie une image
 *  @return: Image numérisée
 *
 *********************************************************/
#ifndef CAMERA_H
#define CAMERA_H


#include <stdio.h>
#include <iostream>
using namespace std;

// Pour interface grpah, manip fichier img/vidéo, interface de capture
#include <opencv2/highgui/highgui.hpp>


/********************************/
/*** Déclaration de la classe ***/
/********************************/
class Camera
{
public:
    /** Constructeur */
    Camera();

    /** Destructeur */
    virtual ~Camera();

    /** Méthodes */
    /* Getter de l'image récupérée */
    IplImage* getImage();

protected:

private:
    /** Attributs */
    CvCapture* m_Capture;
    IplImage* m_Image;

    /** Méthodes */
    void close();
    CvCapture* open();
    IplImage* capturedImg();
};

#endif // CAMERA_H
