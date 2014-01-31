/************************************************
 * Camera.h
 *
 *      Author: Frédéric Gicquel
 *
 *  Classe qui capture et renvoie le flux vidéo
 *  @return: Image numérisée
 *
 ************************************************/
#ifndef CAMERA_H
#define CAMERA_H


#include <stdio.h>
#include <iostream>
using namespace std;

//=>Video
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
// VideoCapture
#include  <opencv2/opencv.hpp>

/********************************/
/*** Déclaration de la classe ***/
/********************************/
class Camera
{
public:
    /* Constructeur */
    Camera();

    /* Destructeur */
    virtual ~Camera();

    /* Méthodes */
    // Getter de l'image récupérée
    IplImage* getFrame();

protected:

private:
    /* Attributs */
    CvCapture* m_Capture;
    IplImage* m_frame;

    /* Méthodes */
    void close();
    CvCapture* open();
    IplImage* grabOneFrame();
};

#endif // CAMERA_H
