/*
 * ThreshedImage.h
 *
 *      Author: Frédéric Gicquel
 *
 *  Classe qui Détermine filtre une image grisée d'un objet selon une couleur
 *  @return: Image traitée
 *
 */
#ifndef THRESHEDIMAGE_H
#define THRESHEDIMAGE_H

#include <iostream>
using namespace std;

#include  <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class ThreshedImage
{
public:
    /* Constructeur */
    ThreshedImage();

    /* Destructeur */
    virtual ~ThreshedImage();

    /* Getters/Setters */
    // Retour de l'image traiter
    IplImage* getThresholdedImage();
    // Réception de l'imge à traiter
    void setThresholdedImage(IplImage*);

protected:

private:
    /* Attributs */
    IplImage* m_img;
    IplImage* m_imgHSV;
    IplImage* m_imgThreshed;

    /* Méthodes */
    void hsvImage();
    void threshedImage();
    void thresholdedImage();
};

#endif // THRESHEDIMAGE_H
