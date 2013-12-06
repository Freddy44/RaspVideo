#include "TraitementImage.h"

TraitementImage::TraitementImage()
{
    /* Contrôle dans un terminal :
     *
     * \E[3x;1m ... \E[m : couleur d'affichage (30 < x < 37) => ici vert
     *
     */
    cout << "\E[32;mTraitementImage::constructeur(2.0) :\E[m\n";

    m_hueMin = 0;
    m_hueMax = 0;
    m_SatMin = 0;
    m_SatMax = 0;
    m_ValMin = 0;
    m_ValMax = 0;
}

TraitementImage::~TraitementImage()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::destructeur() :\E[m\n";

    /*
    * C: void cvReleaseImage(IplImage** image)
    * => Désalloue la mémoire associée à l'image créée
    * @param: m_img, m_imgHSV, m_imgThresholded
    */
    cvReleaseImage(&m_img);
    cvReleaseImage(&m_hsv_frame);
    cvReleaseImage(&m_imgThresholded);
}


void TraitementImage::setThresholdedImage(IplImage* img)
{
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::setThresholdedImage(2.1) :\E[m\n";

    m_img = img;
    m_hsv_frame    = cvCreateImage(cvGetSize(m_img), IPL_DEPTH_8U, 3);
    m_imgThresholded   = cvCreateImage(cvGetSize(m_img), IPL_DEPTH_8U, 1);

    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::setThresholdedImage(2.2) : creations images \E[m\n";
}


void TraitementImage::testTracbarCallback()
{

    Mat src_ = (Mat)m_imgThresholded;
    //src = (Mat)src_;
    cout << "\E[30;mmain (0.2) : conversion tracBar \E[m\n";
    Mat dst;
    //int iBrightness  = hueMin;
    src_.convertTo(dst, -1, m_hueMin);

}

void TraitementImage::setHueMin(int hm)
{
    m_hueMin = hm;
}

void TraitementImage::setHueMax(int hM)
{
    m_hueMax = hM;
}

void TraitementImage::setSatMin(int sm)
{
    m_SatMin = sm;
}

void TraitementImage::setSatMax(int sM)
{
    m_SatMax = sM;
}

void TraitementImage::setValMin(int vm)
{
    m_ValMin = vm;
}

void TraitementImage::setValMax(int vM)
{
    m_ValMax = vM;
}

void TraitementImage::traitementImage()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::traitementImage(2.3) : \E[m\n";

    // Detect a red ball<br />
    //CvScalar hsv_min = cvScalar(150, 84, 130, 0);
    //CvScalar hsv_max = cvScalar(358, 256, 255, 0);

    // Detection d'une balle jaune */
    //CvScalar hsv_min = cvScalar(50, 100, 100,0);
    //CvScalar hsv_max = cvScalar(75, 255, 255,0);

    CvScalar hsv_min = cvScalar(m_hueMin, m_SatMin, m_ValMin,0);
    CvScalar hsv_max = cvScalar(m_hueMax, m_SatMax, m_ValMax,0);
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::traitementImage(2.4) : CvScalar \E[m\n";

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

    // Covert color space to HSV as it is much easier to filter colors in the HSV
    cvCvtColor(m_img, m_hsv_frame, CV_BGR2HSV);
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::traitementImage(2.5) : cvCvtColor \E[m\n";

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

    * @param cvScalar(40, 100, 100) : Limite inférieure de code BGR choisi => Jaune
    * @param cvScalar(50, 255, 255) : Limite supérieure de code BGR choisi => Jaune
    *
    * @param cvScalar(35, 100, 100) : Limite inférieure de code BGR choisi => Jaune
    * @param cvScalar(75, 255, 255) : Limite supérieure de code BGR choisi => Jaune
    */
    //cvInRangeS(m_imgHSV, cvScalar(0,238,238), cvScalar(0,255,255), m_imgThreshed); //3,0,179 //6,2,227 => 28,25,227
    //cvInRangeS(m_imgHSV, cvScalar(170,160,60), cvScalar(180,256,256), m_imgThreshed);

    // Filter out colors which are out of range.
    cvInRangeS(m_hsv_frame, hsv_min, hsv_max, m_imgThresholded);
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::traitementImage(2.6) : cvInRangeS \E[m\n";

    // Memory for hough circles<br />
    CvMemStorage* storage = cvCreateMemStorage(0);
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::traitementImage(2.7) : CvMemStorage \E[m\n";

    // hough detector works better with some smoothing of the image<br />
    cvSmooth( m_imgThresholded, m_imgThresholded, CV_GAUSSIAN, 9, 9 );
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::traitementImage(2.8) : cvSmooth \E[m\n";

    CvSeq* circles = cvHoughCircles(m_imgThresholded, storage, CV_HOUGH_GRADIENT, 2,m_imgThresholded->height/4, 100, 50, 10, 400);
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::traitementImage(2.9) : circles \E[m\n";

    for (int i = 0; i < circles->total; i++)
    {

        float* p = (float*)cvGetSeqElem( circles, i );
        //acces au premier pixel
        printf("Ball! x=%f y=%f r=%f\n\r",p[0],p[1],p[2] );

        cvCircle( m_img, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,255,0), -1, 8, 0 );
        cvCircle( m_img, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
        /* Contrôle dans un terminal */
        cout << "\E[32;mTraitementImage::traitementImage(2.10) : cvCircle \E[m\n";
    }
}



IplImage* TraitementImage::get_FrameImg()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::get_FrameImg(2.11) : \E[m\n";
    return m_img;
}

IplImage* TraitementImage::get_Hsv_Frame()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::get_Hsv_Frame(2.10) : \E[m\n";
    return m_hsv_frame;
}

IplImage* TraitementImage::get_ImgThresholded()
{
    /* Contrôle dans un terminal */
    cout << "\E[32;mTraitementImage::get_ImgThresholded(2.10) : \E[m\n";
    return m_imgThresholded;
}




