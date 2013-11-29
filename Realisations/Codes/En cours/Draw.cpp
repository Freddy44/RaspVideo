/*
 * Draw.cpp
 *
 *      Author: Frédéric Gicquel
 *
 */
#include "Draw.h"

/* Constructeur */
Draw::Draw()
{
    /* Contrôle dans un terminal :
     *
     * \E[3x;1m ... \E[m : couleur d'affichage (30 < x < 37) => ici jaune
     *
     */
    cout << "\E[33;1mDraw::constructeur(0) :\E[m\n";
}

/* Destructeur */
Draw::~Draw()
{
    /* Contrôle dans un terminal */
    cout << "\E[33;1mDraw::Destructeur() :\n";

    /*
    * C: void cvReleaseMat(CvMat** mat)
    */
}

/*
* Méthode setDraw(IplImage* img,IplImage* imgDrawGray)
* => Associe des pointeurs sur les images reçus et <caster>
* @param: img => Image numérisée
* @param: imgDrawGray => Image grisée
* @return:
*/
void Draw::setDraw(IplImage* img,IplImage* imgDrawGray)
{
    /* Contrôle dans un terminal */
    cout << "\E[33;1mDraw::setDraw(1.0) :\E[m\n";

    /*
    * Cast de la classe IplImage en classe Mat
    * Classe Mat => matrice
    * C++: Mat::Mat(const Mat& m)
    * Fournit des opérateurs d'affectation de la matrice
    * @param: img => Image numérisé reçue
    * @return: imgDraw => Matice de l'image
    */
    Mat imgDraw(img);
    /* Idem */
    Mat imgDrawG(imgDrawGray);

    /* Association de pointeurs sur les matrices précédement définies */
    m_imgDraw = imgDraw;
    /* Idem */
    m_imgDrawGray = imgDrawG;

    /* Contrôle dans un terminal */
    cout << "\E[33;1mDraw::setDraw(1.1) :\E[m\n";
}

/*
* Méthode getPerimeterCircle()
* => Renvoie le résultat de la méthode perimeterCircle()
* @param:
* @return:
*/
void Draw::getPerimeterCircle()
{
    /* Contrôle dans un terminal */
    cout << "\E[33;1msetPerimeterCircle(2.6.0) :\E[m\n";
    perimeterCircle();
}

/*
* Méthode perimeterCircle()
* => Détermine un cercle autour d'un objet circulaire de couleur jaune
*
* @param:
* @return:
*/
void Draw::perimeterCircle()
{
    /* Contrôle dans un terminal */
    cout << "\E[33;1mDraw::perimeterCircle(2.0) :\E[m\n";
    cout << "\E[33;1mDraw::perimeterCircle(2.1)GaussianBlur :\E[m\n";

    /*
    * Brouillage de l'image à travers un filtre gaussien
    * => élaboré pour ne pas donner d'excédant à la fonction échelon tout en minimisant
    *       le temps de montée et descente
    * => En numérique le filtre est représenté mathématiquement par une matrice
    * C++: void GaussianBlur(InputArray src, OutputArray dst, Size ksize,
    *           double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT )
    *
    * @param: m_imgDrawGray => Image d'entrée, niveau de gris.
    *       Les canaux étant traitées indépendament, leurs est sans importance
    *       La profondeur doit être CV_8U, CV_16U, CV_16S, CV_32F ou CV_64F.
    * @param: m_imgDrawGray => Image de sortie de même taile et type que la source
    * @param: Size(9, 9) => Taile du noyau Gaussien
    *       .width et .height peuvent différer mais tous deux doivent être positif et impair
    *       si les deux sont à 0, ils sont claculés à partie de sigma
    * @param: 1 => sigmaX écart-type du noyau gaussien dans la direction X
    * @param: 1 => sigmaY écart-type du noyau gaussien dans la direction Y
    * @return:
    */
    GaussianBlur( m_imgDrawGray, m_imgDrawGray, Size(9, 9), 1, 1 );

    /* Déclaration d'un pointeur sur un tableau dynamique de vecteur ?????*/
    /* Vecteur conenant des sequences qui encapsule des tableaux dynamiques */
    vector<Vec3f> circles;

    /* Contrôle dans un terminal */
    cout << "\E[33;1mDraw::perimeterCircle(2.2)HoughCircles :\E[m\n";

    /*
    * Défine des cercles dans une image en niveau de gris à travers la transformée de Hough
    * C++: void HoughCircles(InputArray image, OutputArray circles, int method, double dp,
    *       double minDist, double param1=100, double param2=100, int minRadius=0, int maxRadius=0 )
    * @param: m_imgDrawGray => Image source, niveau de gris (8 bit_mono canal)
    * @param: circles => Vecteur de sortie des cercles trouvés,
    *       codé comme un vecteur de 3 éléments flottants (x, y, rayon)
    * @param: CV_HOUGH_GRADIENT => Seule méthode de détection mise en oeuvre (21HT => ?????)//TODO
    * @param: 2 => dp : Rapport inverse de la résolution de l'accumuateur à la résolution de l'image
    *       2 => l'accumulateur est deux fois moins grand en largeur et hauteur //???????
    * @param:  m_imgDrawGray.rows/4 => Distance minimum entre les centres des cercles détectés
    *       rows -> Crée un en-tête de matrice pour la matrice ligne spécifiée.
    * @param: 200 => Seuil maximun transmis au détecteur des bords selon la méthode canny() (-> premier paramètre spécifique à la méthode)
    * @param: 100 => Seuil d'accumulateur à l'étape de détection des centres de cercle (-> second paramètre spécifique à la méthode)
    ??????????????????????????=> rayon min et max du cercle ????????????????????????????
    * @return:
    */
    HoughCircles(m_imgDrawGray, circles, CV_HOUGH_GRADIENT,2,  m_imgDrawGray.rows/4, 200, 100 );

    /* Boucle de construction du cercle à dessiner */
    for( size_t i = 0; i < circles.size(); i++ )
    {
        /* Contrôle dans un terminal */
        cout << "\E[33;1mDraw::perimeterCircle(2.4)center, radius :\E[m\n";

        /*
        * Définission d'un point du cercle construit par la méthode HoughCircles
        * C: CvPoint cvPoint(int x, int y)
        * C: int cvRound(double value)
        * @param: cvRound(circles[i][0]) =>
        * @param: circles[i][0] =>
        * @param: cvRound(circles[i][0]) =>
        * @param: circles[i][1] =>
        * @return:
        */
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

        /*
        * Définission d'un point du cercle construit par la méthode HoughCircles
        * C: CvPoint cvPoint(int x, int y)
        * C: int cvRound(double value)
        * @param: cvRound(circles[i][2]) =>
        * @param: circles[i][2] =>
        * @return:
        */
        int radius = cvRound(circles[i][2]);

        /* Contrôle dans un terminal */
        cout << "\E[33;1mDraw::perimeterCircle(2.5)circles :\E[m\n";

        /*
        * Associe la ligne exterieure d'un cercle selon les éléments précédents
        *
        * @param: m_imgDraw =>
        * @param: center =>
        * @param: radius =>
        * @param:  Scalar(209, 182, 6) =>
        * @param: 3
        * @param: 8
        * @param: 0
        * @return:
        */
        circle( m_imgDraw, center, radius, Scalar(209, 182, 6), 3, 8, 0 );//Scalar(0,0,255)

        //cout << "\E[33;1m"<< radius  <<"\E[m\n"<<endl;
        //cout << "\E[33;1m"<< center  <<"\E[m\n"<<endl;
    }
}
