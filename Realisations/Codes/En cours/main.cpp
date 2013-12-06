/*
 * main.cpp
 *
 *  Created on: 26 nov. 2013
 *      Author: Frédéric Gicquel
 */


#include "FluxInfo.h"


#include "Constantes.h"
#include "Camera.h"
#include "TraitementImage.h"

#include <fstream>
#include <iostream>
using namespace std;

#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;








/*
* Méthode
*
* @param:
* @return:
*/
int main(int argc, char *argv[])
{
    /* Contrôle dans un terminal */
    cout << "\E[30;1mmain (0) :\E[m\n";



    int hueMin=0;
    int hueMax=0;
    int satMin=0;
    int satMax=0;
    int valMin=0;
    int valMax=0;

    //int lire()
TraitementImage* traitement = new TraitementImage();
    ifstream fichier("dataScalar1.txt"/*, ios::in*/);  // on ouvre le fichier en lecture

    if(fichier)  // si l'ouverture a réussi
    {
        // instructions
        cout << "\E[30;1mmain (1111111) :\E[m\n";

        char caractere;  // notre variable où sera stocké le caractère
        fichier.get(caractere);  // on lit un caractère et on le stocke dans caractere
        hueMin = caractere;
        fichier.get(caractere);
        hueMax = caractere;
        fichier.get(caractere);
        satMin = caractere;
        fichier.get(caractere);
        satMax = caractere;
        fichier.get(caractere);
        valMin = caractere;
        fichier.get(caractere);
        valMax = caractere;

        traitement->setHueMin(hueMin);
        traitement->setHueMax(hueMax);
        traitement->setSatMin(satMin);
        traitement->setSatMax(satMax);
        traitement->setValMin(valMin);
        traitement->setValMax(valMax);

        /*fichier >> hueMin >> endl;
        fichier >> hueMax >> endl;
        fichier >> satMin >> endl;
        fichier >> satMax >> endl;
        fichier >> valMin >> endl;
        fichier >> valMax >> endl;*/

      /*  cout << hueMin<<endl;
        cout << hueMax<<endl;
        cout << satMin<<endl;
        cout << satMax<<endl;
        cout << valMin<<endl;
        cout << valMax<<endl;*/

        /*
        fichier >> hueMin;
        fichier >> hueMax;
        fichier >> satMin;
        fichier >> satMax;
        fichier >> valMin;
        fichier >> valMax;*/
       fichier.close();  // on ferme le fichier
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;



    /* Contrôle dans un terminal */
    cout << "\E[30;main (0.1) : Instanciation \E[m\n";
    Camera* camera = new Camera();
    //TraitementImage* traitement = new TraitementImage();

    Mat src_;// = (Mat)traitement->get_ImgThresholded();
    Mat src ;//= (Mat)src_;
    IplImage* imgCam;
    IplImage* imgHsv;

    /* Contrôle dans un terminal */
    cout << "\E[30;main (0.2) : création fenêtre \E[m\n";
    cvNamedWindow(wTitle,CV_WINDOW_AUTOSIZE);
    cvNamedWindow(wTitleGray,CV_WINDOW_AUTOSIZE);
    namedWindow("TracBars", 1);





    //Create trackbar to change brightness
    cout << "\E[30;main (0.2) : création tracBar \E[m\n";
    //cvGetTrackbarPos("Hue Min", "TracBars");

    createTrackbar("Hue Min", "TracBars", &hueMin, 250);

    createTrackbar("Hue Max", "TracBars", &hueMax, 250);

    createTrackbar("Sat Min", "TracBars", &satMin, 250);

    createTrackbar("Sat Max", "TracBars", &satMax, 250);

    createTrackbar("Val Min", "TracBars", &valMin, 250);

    createTrackbar("Val Max", "TracBars", &valMax, 250);

    while(1)
    {

        /* Contrôle dans un terminal */
        cout << "\E[30;main (0.3) : Boucle while \E[m\n";





        traitement->setThresholdedImage(camera->getFrame());
        traitement->traitementImage();
        imgCam = traitement->get_FrameImg();
        //imgHsv = traitement->get_Hsv_Frame();
        imgHsv = traitement->get_ImgThresholded();

        traitement->setHueMin(hueMin);
        traitement->setHueMax(hueMax);
        traitement->setSatMin(satMin);
        traitement->setSatMax(satMax);
        traitement->setValMin(valMin);
        traitement->setValMax(valMax);

        src = (Mat)imgHsv;
        cout << "\E[30;main (0.2) : conversion tracBar \E[m\n";
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

        /* Contrôle dans un terminal */
        cout << "\E[30;main (0.4) : Display \E[m\n";
        cvShowImage(wTitle, imgCam);
        cvShowImage(wTitleGray, imgHsv);

        //imshow("My Window", 0);

        if( (cvWaitKey(10) & 255) == 27 )
        {
            //int ecrire()
            //déclaration du flux et ouverture du fichier
            ofstream fichier("dataScalar1.txt", ios::out | ios::trunc);
            // si l'ouverture a réussi
            if(fichier)
            {
                fichier << hueMin << endl;
                fichier << hueMax << endl;
                fichier << satMin << endl;
                fichier << satMax << endl;
                fichier << valMin << endl;
                fichier << valMax << endl;
                fichier.close();  // on referme le fichier
            }
            else  // sinon
                cerr << "Erreur à l'ouverture !" << endl;

            //cvSetTrackbarPos("Hue Min", "TracBars", hueMin);

            break;
        }
    }

    cvDestroyAllWindows();

    cvReleaseImage(&imgCam);
    cvReleaseImage(&imgHsv);

    return EXIT_SUCCESS;
    //return 0;
}




