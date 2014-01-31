/*********************************
 * TraitementImage.cpp
 *
 *      Author: Frédéric Gicquel
 *
 *********************************/

#include "TraitementImage.h"

/*** Constructeur ***/
TraitementImage::TraitementImage()
{
    /* Contrôle dans un terminal :
     *
     * \E[3x;1m ... \E[m : couleur d'affichage (30 < x < 37) => ici vert
     *
     */
    cout << "\E[32;1m TraitementImage:: Constructeur(2.0) :\E[m\n";


    /*m_hueMin = 0;
    m_hueMax = 0;
    m_SatMin = 0;
    m_SatMax = 0;
    m_ValMin = 0;
    m_ValMax = 0;*/
}

/*** Destructeur ***/
TraitementImage::~TraitementImage()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage:: Destructeur() :\E[m\n";

    /*
    * C: void cvReleaseImage(IplImage** image)
    * => Désalloue la mémoire associée à l'image créée
    * @param: m_img, m_imgHSV, m_imgThresholded
    */
    cvReleaseImage(&m_img);
    cvReleaseImage(&m_imgHSV);
    cvReleaseImage(&m_imgThresholded);
}

                                            /***************/
                                            /*** Setters ***/
                                            /***************/

/***
* Setter setTrackImage(IplImage* img)
* Receptionne l'image captée afin d'en la préparer
* a son traitement à travers 3 images créés à partir de cette dernière
*/
void TraitementImage::setTrackImage(IplImage* img)
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::setTrackImage(2.1) :\E[m\n";

    /*
    * C: IplImage* cvCreateImage(CvSize size, int depth, int channels)
    *
    * @param: C: CvSize cvGetSize(const CvArr* arr) => Retourne le nombre de lignes (CvSize :: hauteur) et le nombre de colonnes (CvSize :: largeur) de la matrice de l'image.
    * @param:int depth => Taille de la bitdepth de l'image - la bitdepth de l'image - le nombre de bits utilisés pour stocker des informations sur une image. Pour la bitdepth on peut
    *   également utiliser les constantes de OpenCV comme IPL_DEPTH_8U, IPL_DEPTH_16S etc canaux - Nombre de canaux dans l'image
    * @param: int channels => Nombre de canaux par pixel
    * @return:
    */
    m_img = img;
    m_imgHSV    = cvCreateImage(cvGetSize(m_img), IPL_DEPTH_8U, 3);
    m_imgThresholded   = cvCreateImage(cvGetSize(m_img), IPL_DEPTH_8U, 1);

    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::setThresholdedImage(2.2) : creations images \E[m\n";
}

/*
void TraitementImage::testTracbarCallback()
{

    Mat src_ = (Mat)m_imgThresholded;
    //src = (Mat)src_;
    cout << "\E[32;1m TraitementImage (2.3) : conversion tracBar \E[m\n";
    Mat dst;
    //int iBrightness  = hueMin;
    src_.convertTo(dst, -1, m_hueMin);

}*/

/***
* Setter setHueMin(unsigned char hm)
* Récupération de la valeur de teinte minimum générée par le trackbar associé
* @param: unsigned char hm
*/
void TraitementImage::setHueMin(unsigned char hm)
{
    m_hueMin = hm;
    cout << "\E[33;1m TraitementImage (2.30) : setHueMin '"  << (int)hm <<"' \E[m\n";
}

/***
* Setter setHueMax(unsigned char hM)
* Récupération de la valeur de teinte maximun générée par le trackbar associé
* @param: unsigned char hM
*/
void TraitementImage::setHueMax(unsigned char hM)
{
    cout << "\E[33;1m TraitementImage (2.31) : setHueMax '"  << (int)hM <<"'\E[m\n";
    m_hueMax = hM;
}

/***
* Setter setSatMin(unsigned char sm)
* Récupération de la valeur de saturation minimum générée par le trackbar associé
* @param: unsigned char sm
*/
void TraitementImage::setSatMin(unsigned char sm)
{
    cout << "\E[33;1m TraitementImage (2.32) : setSatMin '"  << (int)sm <<"'\E[m\n";
    m_SatMin = sm;
}

/***
* Setter setSatMax(unsigned char sM)
* Récupération de la valeur de saturation maximun générée par le trackbar associé
* @param: unsigned char sM
*/
void TraitementImage::setSatMax(unsigned char sM)
{
    cout << "\E[33;1m TraitementImage (2.33) : setSatMaxr '"  << (int)sM <<"'\E[m\n";
    m_SatMax = sM;
}

/***
* Setter setValMin(unsigned char vm)
* Récupération de la valeur de la brillance de la couleur minimum générée par le trackbar associé
* @param: unsigned char vm
*/
void TraitementImage::setValMin(unsigned char vm)
{
    cout << "\E[33;1m TraitementImage (2.34) : setValMin '"  << (int)vm <<"'\E[m\n";
    m_ValMin = vm;
}

/***
* Setter setValMax(unsigned char vM)
* Récupération de la valeur de de la brillance de la couleu maximum générée par le trackbar associé
* @param: unsigned char vM
*/
void TraitementImage::setValMax(unsigned char vM)
{
    cout << "\E[33;1m TraitementImage (2.35) : setValMax '"  << (int)vM <<"'\E[m\n";
    m_ValMax = vM;
}

/***
* Méthode traitementImage()
* Traitements de l'image ( )
* @param:
* @return:
*/
void TraitementImage::traitementImage()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage (2.4) : traitementImage \E[m\n";

    /*** Préparation au traitement ***/
    /*********************************/

    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage (2.41) : CvScalar \E[m\n";

    /* Tableau de valeurs (teinte, saturation, valeur ) */

    ///////exemples /////
    // Detect a red ball<br />
    //CvScalar red_min = cvScalar(150, 84, 130, 0);
    //CvScalar red_max = cvScalar(358, 256, 255, 0);

    // Detection d'une balle jaune */
    //CvScalar jaune_min = cvScalar(50, 100, 100,0);
    //CvScalar jaune_max = cvScalar(75, 255, 255,0);

    CvScalar val_min = cvScalar(m_hueMin, m_SatMin, m_ValMin,0);
    CvScalar val_max = cvScalar(m_hueMax, m_SatMax, m_ValMax,0);

    /*** Convertion d'une image RGB en HSV ***/

    /*
    *  C: void cvCvtColor(const CvArr* src, CvArr* dst, int code)
    * => une couleur = un canal = 8 octets
    * HSV => Espace colorimétrique défini selon
    *    la teinte (Hue) -> selon l'angle,
    *    la saturation (Saturation) -> intensité de la couleur,
    *    et la valeur (Value) -> brillance de la couleur
    * @param: m_img => Image source
    * @param: m_imgHSV => Image de destination de même taille et profondeur que l'image source convertie en HSV
    * @param: CV_BGR2HSV => Code de conversion d'espace couleur RGB -> HSV
    * @return:
    */
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage (2.42) : cvCvtColor \E[m\n";
    cvCvtColor(m_img, m_imgHSV, CV_BGR2HSV);

    /*** Filtrage des couleurs ***/
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
    /////Exemples/////
    * @param cvScalar(40, 100, 100) : Limite inférieure de code BGR choisi => Jaune
    * @param cvScalar(50, 255, 255) : Limite supérieure de code BGR choisi => Jaune
    *
    * @param cvScalar(35, 100, 100) : Limite inférieure de code BGR choisi => Jaune
    * @param cvScalar(75, 255, 255) : Limite supérieure de code BGR choisi => Jaune
    */
    /////Exemples/////
    //cvInRangeS(m_imgHSV, cvScalar(0,238,238), cvScalar(0,255,255), m_imgThreshed); //3,0,179 //6,2,227 => 28,25,227
    //cvInRangeS(m_imgHSV, cvScalar(170,160,60), cvScalar(180,256,256), m_imgThreshed);
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::traitementImage(2.43) : cvInRangeS \E[m\n";
    cvInRangeS(m_imgHSV, val_min, val_max, m_imgThresholded);


    /*** Mémoire pour les cercles de Hough ***/
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::traitementImage(2.44) : CvMemStorage \E[m\n";
    CvMemStorage* storage = cvCreateMemStorage(0);

    /*** Lissage de l'image ***/
    /*
    * Permet une meilleur détection hough
    * C: void cvSmooth(const CvArr* src, CvArr* dst, int smoothtype=CV_GAUSSIAN, int size1=3, int size2=0, double sigma1=0, double sigma2=0 )
    * @param: m_imgThresholded => Image source
    * @param: m_imgThresholded => Image destination
    * @param: CV_GAUSSIAN => Type de lissage : noyau Gaussien
    * @param: 9 => Le premier paramètre de l'opération de lissage, la largeur de l'ouverture. Doit être un nombre impair positif
    * @param: 9 => Le second paramètre de l'opération de lissage, la hauteur de l'ouverture.
    * les parametres sigma peuvent être omis. Dans ce cas, ils seront calculer à partir de la taille du noyau Gaussien

    * flou gaussien support 1 - ou 3-canal, 8-bits et 32-bits flottants images ponctuelles. Cette méthode peut traiter des images en temps réel.
    */
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::traitementImage(2.45) : cvSmooth \E[m\n";
    cvSmooth( m_imgThresholded, m_imgThresholded, CV_GAUSSIAN, 9, 9 );

    /*** Construction d'un cercle ***/
    /*
    * Détermine un cercle dans une image eb fonction du niveau de gris en utilisant la transformée de hough
    * C: CvSeq* cvHoughCircles(CvArr* image, void* circle_storage, int method, double dp, double min_dist, double param1=100, double param2=100, int min_radius=0, int max_radius=0 )
    *
    * @param: m_imgThresholded => Image source - 8-bit mono-canal, niveaux de gris d'entrée
    * @param: storage => Stockage en mémoire qui va contenir la séquence de sortie de cercles trouvés.
    * @param: CV_HOUGH_GRADIENT => Méthode de détection à utiliser. Actuellement, la seule méthode mise en œuvre est CV_HOUGH_GRADIENT.
    * @param: 2 =>  Rapport inverse de la résolution de l'accumulateur à la résolution de l'image. Ici, dp = 2 : l'accumulateur a une résolution deux fois moins grande en largeur et  hauteur.
    * @param: m_imgThresholded->height/4 => Distance minimale entre les centres des cercles détectés. Si le paramètre est trop petit, plusieurs cercles voisins peuvent être faussement
    *   détectés en plus d'une vraie. Si elle est trop grande, certains milieux peuvent être négligés.
    * @param: 100 => Le premier paramètre spécifique à la méthode CV_HOUGH_GRADIENT: seuil le plus élevé transmis au détecteur de bord de Canny ()
    * @param: 50 =>  Deuxième paramètre spécifique à la méthode CV_HOUGH_GRADIENT: seuil d'accumulateur pour les centres de cercle à l'étape de détection.
    * @param: 10 => Rayon du cercle minimum.
    * @param: 400 => Rayon du cercle maximum.
    *
    * @return: circles => Pointeur sur une structure de séquences dynamiques : CvSeq => séquences denses utilisées pour représenter les tableaux 1D évolutif - Vecteurs, piles, files et files doubles.
    */
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::traitementImage(2.46) : circles \E[m\n";
    CvSeq* circles = cvHoughCircles(m_imgThresholded, storage, CV_HOUGH_GRADIENT, 2,m_imgThresholded->height/4, 100, 50, 2, 600);

    /*** Dessins des cercles affichés dans l'image non traitée ***/
    for (int i = 0; i < circles->total; i++)
    {
        /* Contrôle dans un terminal */
        cout << "\E[32;1m TraitementImage::traitementImage(2.47) : cvCircle \E[m\n";

        float* p = (float*)cvGetSeqElem( circles, i );

        //Coordonnées du centre et rayon du cercle
        printf("Ball! centre X=%f centre Y=%f rayon=%f\n\r",p[0],p[1],p[2] );
        cout << "Ball! centre X= " << p[0] << " centre Y= " << p[1] <<" rayon= " << p[2] << "\n\r";
        m_cercleCentreX = p[0];
        m_cercleCentreY = p[1];
        m_cercleRayon = p[2];
        cout << m_cercleCentreX << " " << m_cercleCentreY << " " << m_cercleRayon << "\n\r";
        /*
        * C: void cvCircle(CvArr* img, CvPoint center, int radius, CvScalar color, int thickness=1, int line_type=8, int shift=0 )
        * @param: m_img => Image sur laquelle les cercles seront déssinés
        * @param: cvRound(p[0] => Abcisse du centre de l'objet
        * @param: cvRound(p[1] => Ordonnée du centre de l'objet
        * @param: cvRound(p[2] et 3 => Rayon du cercle associé
        * @param: CV_RGB(0,255,0) et CV_RGB(255,0,0) => couleur des cercles
        * @param: -1 et 3 => Epaisseur du contour du cercle, si elle est positive. Épaisseur négative signifie que un cercle rempli doit être établi.
        * @param: 8 => Type de la ligne: 8 (ou omis) - ligne 8 connectés / 4 - ligne 4-connexe. / CV_AA - ligne anti-crénelage.
        * @param: 0 => Déplacer - Nombre de bits fractionnaires dans les coordonnées du centre et de la valeur de rayon.
        */
        /* Cercle du point central de l'objet détecté */
        cvCircle( m_img, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,255,0), -1, 8, 0 );
        /* Cercle entourant l'objet détecté */
        cvCircle( m_img, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );

    }
}

                                                        /***************/
                                                        /*** Getters ***/
                                                        /***************/

/***
* Retourne l'image n'ont traitée
* @return: m_img
*/
IplImage* TraitementImage::get_FrameImg()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::get_FrameImg(2.6) : \E[m\n";
    return m_img;
}

/***
* Retourne l'image grisée
* @return: m_imgThresholded
*/
IplImage* TraitementImage::get_ImgThresholded()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::get_ImgThresholded(2.8) : \E[m\n";
    return m_imgThresholded;
}

/***
* Retourne le point de coordonnée X du centre du cercle
* @return: m_cercleCentreX et m_cercleCentreY
*/
float TraitementImage::get_PointCenterCircleX()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::get_PointCenterCircleX(2.9) : \E[m\n";
    return m_cercleCentreX ; //&& m_cercleCentreY;
}

/***
* Retourne le point de coordonnée Y du centre du cercle
* @return: m_cercleCentreY
*/
float TraitementImage::get_PointCenterCircleY()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::get_PointCenterCircleY(2.9) : \E[m\n";
    return m_cercleCentreY ; //&& m_cercleCentreY;
}

/***
* Retourne le point de coordonnée Y du centre du cercle
* @return: m_cercleCentreY
*/
float TraitementImage::get_RadiusCircle()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;1m TraitementImage::get_RadiusCircle(2.9) : \E[m\n";
    return m_cercleRayon ;
}
