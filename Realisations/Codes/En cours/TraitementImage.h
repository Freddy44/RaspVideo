/*******************************************
 * TraitementImage.h
 *
 *      Author: Frédéric Gicquel
 *
 * Classe qui s'occupe de l'analyse et
 * des opérations de traitement de l'image
 ******************************************/

#ifndef TRAITEMENTIMAGE_H
#define TRAITEMENTIMAGE_H


#include <stdio.h>
#include <iostream>
using namespace std;

#include  <opencv2/opencv.hpp>
using namespace cv;

/********************************/
/*** Déclaration de la classe ***/
/********************************/
class TraitementImage
{
public:
    /** Constructeur */
    TraitementImage();

    /** Destructeur */
    virtual ~TraitementImage();

    /** Getters/Setters */

    /* Setter : Image capturée */
    void setTrackImage(IplImage*);

    /* Setters : Valeurs liés aux trackbars */
    void setHueMin(unsigned char);
    void setHueMax(unsigned char);
    void setSatMin(unsigned char);
    void setSatMax(unsigned char);
    void setValMin(unsigned char);
    void setValMax(unsigned char);

    /* Getters : images traitées */
    IplImage* get_ImgCircles();
    IplImage* get_Hsv_Frame();
    IplImage* get_ImgThresholded();

    /* Getters : Point du centre de cercle */
    float get_PointCenterCircleX();
    float get_PointCenterCircleY();
    /* Getter : rayon du cercle entourant l'objet */
    float get_RadiusCircle();

    /** Méthodes */
    void imageProcessing();


protected:

private:
    /** Attributs */
    IplImage* m_img;
    IplImage* m_imgHSV;
    IplImage* m_imgThresholded;

    unsigned char m_hueMin;
    unsigned char m_hueMax;
    unsigned char m_SatMin;
    unsigned char m_SatMax;
    unsigned char m_ValMin;
    unsigned char m_ValMax;

    float m_cercleCentreX;
    float m_cercleCentreY;
    float m_cercleRayon;

    /** Méthodes */

};

#endif // TRAITEMENTIMAGE_H
