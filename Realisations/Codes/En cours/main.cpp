/**********************************
 * main.cpp
 *
 *      Author: Frédéric Gicquel
 *********************************/


#include "FluxInfo.h"
#include "Constantes.h"
#include "Camera.h"
#include "TraitementImage.h"

#include <fstream>
#include <iostream>
using namespace std;

#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
#include <sqlite3.h>

void callbackButton(int state, void* userdata)
{

    cout <<"test button" << endl;
}

/*
* Méthode
*
* @param:
* @return:
*/
int main(int argc, char *argv[])
{
                        cout << "\E[30;1m ******************************* \E[m\n";
                        cout << "\E[30;1m *********** BONJOUR *********** \E[m\n";
                        cout << "\E[30;1m ******************************* \E[m\n";

                            /***********************************/
                            /*** Initialisation du programme ***/
                            /***********************************/

    /* Contrôle dans un terminal */
    cout << "\E[30;1m main (0) :\E[m\n";

    /*** Déclaration des variables ***/
    /*********************************/

    /* */
    int hueMin;
    int hueMax;
    int satMin;
    int satMax;
    int valMin;
    int valMax;

    /* */
    Mat src_;
    Mat src ;
    IplImage* imgCam;
    IplImage* imgHsv;

    /*** Initialisation ***/
    /**********************/

    /*** Instanciation du traitement de l'image ***/
    TraitementImage* traitement = new TraitementImage();

    /*** Instanciation de la caméra ***/
    /* Contrôle dans un terminal */
    cout << "\E[30;1m main (0.1) : Instanciation Camera\E[m\n";
    Camera* camera = new Camera();

    /*** Instanciation des fenêtres ***/
    /* Contrôle dans un terminal */
    cout << "\E[30;1m main (0.12) : Création Fenêtres \E[m\n";
    cvNamedWindow(wTitle,CV_WINDOW_AUTOSIZE);
    cvNamedWindow(wTitleGray,CV_WINDOW_AUTOSIZE);
    //namedWindow("TracBars", 1);

    /*** Lecture des anciennes valeurs associées aux trackbars ***/
    /************************************************************/

    /*** Ouverture du fichier ***/
    ifstream fichier("DataTrackbar.txt"/*, ios::in*/);
    /*** Lecture du fichier ***/
    if(fichier)  // si l'ouverture a réussi
    {
        /* Contrôle dans un terminal */
        cout << "\E[30;1m main (0.2) : Lecture DataTrackbar\E[m\n";
        /* Lecture des données */
        fichier >> hueMin;
        fichier >> hueMax;
        fichier >> satMin;
        fichier >> satMax;
        fichier >> valMin;
        fichier >> valMax;
        /* Fermeture du fichier */
        fichier.close();
    }else{
            cerr << "Erreur à l'ouverture : Fichier inexistant !" << endl;}

    /*** Création des trackbars destinés aux changements de la luminosité ***/
    /************************************************************************/

    /* Contrôle dans un terminal */
    cout << "\E[30;1m main (0.3) : création tracBar \E[m\n";
    //cvGetTrackbarPos("Hue Min", "TracBars");
    /* Pour La teinte */
    createTrackbar("Hue_Min", wTitleGray, &hueMin, 250);
    createTrackbar("Hue_Max", wTitleGray, &hueMax, 250);
    /* Pour la saturation (=> intensité) */
    createTrackbar("Sat_Min", wTitleGray, &satMin, 250);
    createTrackbar("Sat_Max", wTitleGray, &satMax, 250);
    /* Pour la brillance de la couleur */
    createTrackbar("Val_Min", wTitleGray, &valMin, 250);
    createTrackbar("Val_Max", wTitleGray, &valMax, 250);

    createButton("test",callbackButton,NULL,CV_PUSH_BUTTON,1);


                            /**************************************/
                            /*** Boucle principale du programme ***/
                            /**************************************/
    while(1)
    {
        /* Contrôle dans un terminal */
        cout << "\E[30;1m main (0.4) : Boucle while \E[m\n";

        /*** Traitements et récupération des images traitées ***/
        /*******************************************************/
        traitement->setTrackImage(camera->getFrame());
        traitement->traitementImage();
        imgCam = traitement->get_FrameImg();
        imgHsv = traitement->get_ImgThresholded();

        /*** Envoie des datas de luminosité ***/
        /**************************************/
        /* Contrôle dans un terminal */
        cout << "\E[30;1m main (0.42) : Envoie datas luminosites \E[m\n";
        traitement->setHueMin(hueMin);
        traitement->setHueMax(hueMax);
        traitement->setSatMin(satMin);
        traitement->setSatMax(satMax);
        traitement->setValMin(valMin);
        traitement->setValMax(valMax);

        /*** ***/
        /*******/
        /* Contrôle dans un terminal */
        cout << "\E[30;1m main (0.43) : conversion tracBar \E[m\n";
        src = (Mat)imgHsv;
        Mat dst;
        //int iBrightness  = hueMin;
        src.convertTo(dst, -1, hueMin);
        src.convertTo(dst, -1, hueMax);
        src.convertTo(dst, -1, satMin);
        src.convertTo(dst, -1, satMax);
        src.convertTo(dst, -1, valMin);
        src.convertTo(dst, -1, valMax);

        //IplImage* _imgHsv = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 1);
        imgHsv->imageData = (char *) dst.data;

        /*** Envoie Ordre à l'arduino ***/
        /********************************/
        cout << "CenterCircleX : " << traitement->get_PointCenterCircleX() << " <=> " << "CenterCircleY : " << traitement->get_PointCenterCircleY() << " <=> " << "Radius : " << traitement->get_RadiusCircle() << "\n";

        if ( traitement->get_PointCenterCircleX() && traitement->get_PointCenterCircleY())
        {
            if ((traitement->get_PointCenterCircleX()>=0 && traitement->get_PointCenterCircleX()<319))
            {
                cout << "le robot doit tourner à gauche" << endl;
            }else if ((traitement->get_PointCenterCircleX()>319 && traitement->get_PointCenterCircleX()<=638))
                {
                    cout << "le robot doit tourner à droite" << endl;
                }
            else{ cout << "wait !!!!!" << endl;}

        }

        if (traitement->get_RadiusCircle() >= 15 && traitement->get_RadiusCircle() <= 90)
        {
             cout << "le robot doit avancer" << endl;
        }else {cout << "la camera doit tracker la balle " << endl; }

        /*** Affichage des images traitées ***/
        /*************************************/
        /* Contrôle dans un terminal */
        cout << "\E[30;1m main (0.44) : Display \E[m\n";
        cvShowImage(wTitle, imgCam);
        cvShowImage(wTitleGray, imgHsv);


                             /**********************************/
                             /*** Fermeture de l'application ***/
                             /**********************************/

        /*** Dès que le signal de la touche Escape est reçu ***/
        if( (cvWaitKey(10) & 255) == 27 )
        {
            /* Contrôle dans un terminal */
            cout << "\E[30;1m main (0.5) : Fin programme \E[m\n";

            //cvSetTrackbarPos("Hue Min", "TracBars", hueMin);
            /*** Sauvegarde des données des couleurs tracker ***/
            /***************************************************/

            /* Création et ouverture du fichier */
            ofstream fichier("DataTrackbar.txt", ios::out | ios::trunc);
            /* Si l'ouverture réussie, sauvegarde des datas de luminosité */
            if(fichier)
            {
                /* Contrôle dans un terminal */
                cout << "\E[30;1m main (0.51) : Sauvegarde datas \E[m\n";
                fichier << (int)hueMin << endl;
                fichier << (int)hueMax << endl;
                fichier << (int)satMin << endl;
                fichier << (int)satMax << endl;
                fichier << (int)valMin << endl;
                fichier << (int)valMax << endl;
                fichier.close();  // on referme le fichier
            }else{
                    cerr << "Erreur à l'ouverture !" << endl;}

            /* Sortie de la boucle */
            break;
        }
    }

    /*******************/
    /*** Destruction ***/
    /*******************/
    /*** Des fenêtres */
    cvDestroyAllWindows();
    /*** Des Images */
    cvReleaseImage(&imgCam);
    cvReleaseImage(&imgHsv);

                cout << "\E[30;1m ******************************* \E[m\n";
                cout << "\E[30;1m ********** AU REVOIR ********** \E[m\n";
                cout << "\E[30;1m ******************************* \E[m\n";
    /*** fin du programme ***/
    return EXIT_SUCCESS; // => return 0;
}




