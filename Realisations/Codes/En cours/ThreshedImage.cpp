/*
 * ThreshedImage.cpp
 *
 *      Author: Frédéric Gicquel
 *
 */
#include "ThreshedImage.h"

/* Constructeur */
ThreshedImage::ThreshedImage()
{
    /* Contrôle dans un terminal :
     *
     * \E[3x;1m ... \E[m : couleur d'affichage (30 < x < 37) => ici vert
     *
     */
    cout << "\E[32;1mThreshedImage::constructeur(0) :\E[m\n";
}

/* Destructeur */
ThreshedImage::~ThreshedImage()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1mThreshedImage::destructeur() :\E[m\n";

    /*
    * C: void cvReleaseImage(IplImage** image)
    * => Désalloue la mémoire associée à l'image créée
    * @param: m_img, m_imgHSV, m_imgThreshed
    */
    cvReleaseImage(&m_img);
    cvReleaseImage(&m_imgHSV);
    cvReleaseImage(&m_imgThreshed);
}

/*
* Méthode setThresholdedImage(IplImage* img)
* => Réception de l'image à traiter
* @param: img => Image qui va être traitée
* @return:
*/
void ThreshedImage::setThresholdedImage(IplImage* img)
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1mThreshedImage::setThresholdedImage(1) :\E[m\n";

    /* Pointeur sur l'image reçu
    * @param: m_img => pointeur
    */
    m_img = img;
}

/*
* Méthode getThresholdedImage()
* => Renvoie de l'image traitée
* @param:
* @return: m_imgThreshed => Image Grisée
*/
IplImage* ThreshedImage::getThresholdedImage()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1mThreshedImage::getThresholdedImage(5) :\E[m\n";

    /* Appel de la méthode thresholdedImage() */
    thresholdedImage();

    return m_imgThreshed;
}

/*
* Méthode hsvImage()
* =>
* @param: m_img => pointeur sur l'image traitée
* @return:
*/
void ThreshedImage::hsvImage()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1mThreshedImage::hsvImage(2) : \E[m\n";

    /*
    * Création d'un en-tête de l'image qui va être traitée et alloue les données
    * C: IplImage* cvCreateImage(CvSize size, int depth, int channels)
    * @param: m_img => Définition de la largeur et hauteur de l'image par la méthode
    *                   C: CvSize cvGetSize(const CvArr* arr)
    * @param: 8 => Profondeur des élements d'images (bits) ??
    * @param: 3 => Nombre de canaux par pixels
    * @return: m_imgHSV => mage prête à être traitée
    */
    m_imgHSV = cvCreateImage(cvGetSize(m_img), 8, 3);

    /*
    * Convertion d'une image RGB en HSV
    *  C++: void cvtColor(InputArray src, OutputArray dst, int code, int dstCn=0 )
    * => une couleur = un canal = 8 octets
    * HSV => Espace colorimétrique défini selon
    *    la teinte (Hue) -> selon l'angle,
    *    la saturation (Saturation) -> intensité de la couleur,
    *    et la valeur (Value) -> brillance de la couleur
    * @param: m_img => Image source
    * @param: m_imgHSV => Image de destination de même taille et profondeur que l'image source
    * @param: CV_BGR2HSV => Code de conversion d'espace couleur RGB -> HSV
    * @return: m_imgHSV => image convertie en HSV
    */
    cvCvtColor(m_img, m_imgHSV, CV_BGR2HSV);
}

/*
* Méthode threshedImage()
* =>Création d'une image à traitée
*
* @param:
* @return:
*/
void ThreshedImage::threshedImage()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1mThreshedImage::threshedImage(3): \E[m\n";

    /*
    * Création d'un en-tête de l'image qui va être traitée et alloue les données
    * C: IplImage* cvCreateImage(CvSize size, int depth, int channels)
    * @param: m_img => Définition de la largeur et hauteur de l'image par la méthode
    *                   C: CvSize cvGetSize(const CvArr* arr)
    * @param: 8 => Profondeur des élements d'images (bits) ??
    * @param: 3 => Nombre de canaux par pixels
    * @return: m_imgThreshed => mage prête à être traitée
    */
    m_imgThreshed = cvCreateImage(cvGetSize(m_img), 8, 1);
}

/*
* Méthode thresholdedImage()
* => Définie une image grisée selon une échelle de couleur définie
* @param:
* @return:
*/
void ThreshedImage::thresholdedImage()
{
    /* Appel des méthodes hsvImage() et threshedImage() */
    hsvImage();
    threshedImage();

    /* Contrôle dans un terminal */
    cout << "\E[32;1mThreshedImage::thresholdedImage(4) : \E[m\n";

    /*
    * Vérification des élements du tableau d'entrée et sélection des élements selon
    * un code couleur min et max sur 3 canaux.
    * C++: void inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst)
    *
    * @param: m_imgHSV => Tableau d'entrée
    * @param: cvScalar(35, 100, 100) => scalaire de champs inférieur (-> fonction de plusieurs variables qui associe un seul nombre à chaque point de l'espace)
    * @param: cvScalar(75, 255, 255) => Scalaire de champs supérieur
    * @param: m_imgThreshed => Image de sortie de la même taille que la source et de type CV_8U
    *   (Matrice d'entier 8 Bits non signées => IPL_DEPTH_8U)
    *
    */
    cvInRangeS(m_imgHSV, cvScalar(35, 100, 100), cvScalar(75, 255, 255), m_imgThreshed);
}


