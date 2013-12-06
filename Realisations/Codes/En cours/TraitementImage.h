#ifndef TRAITEMENTIMAGE_H
#define TRAITEMENTIMAGE_H


#include <fstream>
#include <stdio.h>
#include <iostream>
using namespace std;

#include  <opencv2/opencv.hpp>
using namespace cv;

class TraitementImage
{
public:
    /* Constructeur */
    TraitementImage();

    /* Destructeur */
    virtual ~TraitementImage();

    /* Getters/Setters */
    // Réception de l'image à traiter
    void setThresholdedImage(IplImage*);
    IplImage* get_FrameImg();
    IplImage* get_Hsv_Frame();
    IplImage* get_ImgThresholded();

    void setHueMin(int);
    void setHueMax(int);
    void setSatMin(int);
    void setSatMax(int);
    void setValMin(int);
    void setValMax(int);

    int ecrire();
    int lire();

    void traitementImage();
    void testTracbarCallback();


protected:
private:
    /* Attributs */
    IplImage* m_img;
    IplImage* m_hsv_frame;
    IplImage* m_imgThresholded;

    int m_hueMin;
    int m_hueMax;
    int m_SatMin;
    int m_SatMax;
    int m_ValMin;
    int m_ValMax;

    /* Méthodes */

};

#endif // TRAITEMENTIMAGE_H
