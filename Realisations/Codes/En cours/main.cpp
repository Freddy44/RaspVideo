/**********************************
 * main.cpp
 *
 *      Author: Frédéric Gicquel
 *********************************/

/**Fichiers d'entête relatifs au projet**/
#include "Constantes.h"
#include "Camera.h"
#include "TraitementImage.h"
#include "Uart.h"
#include "Tramage.h"

/**Relatifs aux bibliothèques**/
#include <fstream> //Pour les opérations E/S sur des fichiers
#include <iostream> //Pour les opérations d'E/S standard (cout/cin/cerr/clog)
using namespace std;

#include "opencv2/imgproc/imgproc.hpp" //Processus des images
using namespace cv;


/*
* Méthode main()
* Méthode d'entrée du programme
* @param: int argc => compteur sur le nombre de chaines de caractères contenu dans le tableau argv[]
* @param: char *argv[] => pointeur sur le tableau contenant des chaines de caractères
* @return: int => 0 si le programme c'est arreter dans de bonne condition
*/
int main(int argc, char *argv[])
{
    cout << "\E[30;1m ******************************* \E[m\n";
    cout << "\E[30;1m *********** BONJOUR *********** \E[m\n";
    cout << "\E[30;1m ******************************* \E[m\n";

    usleep(500000);

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
    int sendFrame;
    int trame;

    /* */
    // Mat src_;
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

    /*** Lecture des anciennes valeurs de seuils associées aux trackbars ***/
    /***********************************************************************/

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
        fichier >> sendFrame;
        /* Fermeture du fichier */
        fichier.close();
    }
    else
    {
        cerr << "Erreur à l'ouverture : Fichier inexistant !" << endl;
    }

    /*** Création des trackbars destinés aux changements des paramètres de seuils***/
    /*******************************************************************************/

    /* Contrôle dans un terminal */
    cout << "\E[30;1m main (0.3) : création tracBar \E[m\n";
    /* Pour La teinte */
    createTrackbar("Hue_Min", wTitleGray, &hueMin, 250);
    createTrackbar("Hue_Max", wTitleGray, &hueMax, 250);
    /* Pour la saturation (=> intensité) */
    createTrackbar("Sat_Min", wTitleGray, &satMin, 250);
    createTrackbar("Sat_Max", wTitleGray, &satMax, 250);
    /* Pour la brillance de la couleur */
    createTrackbar("Val_Min", wTitleGray, &valMin, 250);
    createTrackbar("Val_Max", wTitleGray, &valMax, 250);

    /* Pour activer l'envoie de trame vers l'ardiuno */
    createTrackbar("Send_Frame", wTitle, &sendFrame, 1);


    /*** Initialisation du port série ***/
    /************************************/
    Uart* portSerie = new Uart();
    int port = portSerie->getPort();
    if (port <0)
    {
        perror("Port configure ");
        return 0;//EXIT_FAILURE;
    }

    /*** Initialisation de la trame ***/
    /**********************************/
    Tramage* frameReceived  = new Tramage();


                                                                /**************************************/
                                                                /*** Boucle principale du programme ***/
                                                                /**************************************/
    while(1)
    {
        /* Contrôle dans un terminal */
        cout << "\E[30;1m main (0.4) : Boucle while \E[m\n";

        /*** Traitements et récupération des images traitées ***/
        /*******************************************************/
        traitement->setTrackImage(camera->getImage());
        traitement->imageProcessing();
        imgCam = traitement->get_ImgCircles();
        imgHsv = traitement->get_ImgThresholded();

        /*** Envoie des données de seuils ***/
        /************************************/
        /* Contrôle dans un terminal */
        cout << "\E[30;1m main (0.42) : Envoie datas luminosites \E[m\n";
        traitement->setHueMin(hueMin);
        traitement->setHueMax(hueMax);
        traitement->setSatMin(satMin);
        traitement->setSatMax(satMax);
        traitement->setValMin(valMin);
        traitement->setValMax(valMax);

        /***Action des trackbars sur l'image ***/
        /***************************************/
        /* Contrôle dans un terminal */
        cout << "\E[30;1m main (0.43) : conversion trackBar \E[m\n";
        src = (Mat)imgHsv;
        Mat dst;
        /* Conversion de l'image source selon les paramètres de seuils */
        src.convertTo(dst, -1, hueMin);
        src.convertTo(dst, -1, hueMax);
        src.convertTo(dst, -1, satMin);
        src.convertTo(dst, -1, satMax);
        src.convertTo(dst, -1, valMin);
        src.convertTo(dst, -1, valMax);
        /* Restitution de l'image après modification */
        imgHsv->imageData = (char *) dst.data;

        /*** Envoie Ordre à l'arduino ***/
        /********************************/
        cout << "CenterCircleX : " << traitement->get_PointCenterCircleX() << " <=> " << "CenterCircleY : " << traitement->get_PointCenterCircleY() << " <=> " << "Radius : " << traitement->get_RadiusCircle() << "\n";

        if (sendFrame == 1)
        {
            trame = 0;

            if ( traitement->get_PointCenterCircleX() && traitement->get_PointCenterCircleY())
            {
                if ((traitement->get_PointCenterCircleX()>=0 && traitement->get_PointCenterCircleX()<315))
                {
                    cout << "le robot doit tourner à gauche" << endl;
                    trame = 1;
                    frameReceived->setCommande(trame);
                    portSerie->send_data(frameReceived->getCommande(),port);
                    usleep(100000);
                    portSerie->read_data(port);
                }
                else if ((traitement->get_PointCenterCircleX()>324 && traitement->get_PointCenterCircleX()<=638))
                {
                    cout << "le robot doit tourner à droite" << endl;
                    trame = 2;
                    frameReceived->setCommande(trame);
                    portSerie->send_data(frameReceived->getCommande(),port);
                    usleep(100000);
                    portSerie->read_data(port);
                }
                else
                {
                    cout << "wait !!!!!" << endl;
                    trame = 3;
                    frameReceived->setCommande(trame);
                    portSerie->send_data(frameReceived->getCommande(),port);
                    usleep(100000);
                    portSerie->read_data(port);
                }
            }

            if (traitement->get_RadiusCircle() >= 15 && traitement->get_RadiusCircle() <= 90)
            {
                cout << "le robot doit avancer" << endl;
                trame = 4;
                frameReceived->setCommande(trame);
                portSerie->send_data(frameReceived->getCommande(),port);
                usleep(100000);
                portSerie->read_data(port);
            }
            else if (traitement->get_RadiusCircle() <= 15 && traitement->get_RadiusCircle() >= 90)
                {
                    cout << "wait !!!!!" << endl;
                    trame = 3;
                    frameReceived->setCommande(trame);
                    portSerie->send_data(frameReceived->getCommande(),port);
                    usleep(100000);
                    portSerie->read_data(port);
                }
            else
            {
                cout << "la camera doit tracker la balle " << endl;
                trame = 5 ;
                frameReceived->setCommande(trame);
                portSerie->send_data(frameReceived->getCommande(),port);
                usleep(100000);
                portSerie->read_data(port);
            }
        }

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
                fichier << (int)sendFrame << endl;
                fichier.close();  // on referme le fichier
            }
            else
            {
                cerr << "Erreur à l'ouverture !" << endl;
            }

            /* Sortie de la boucle */
            break;
        }
    }

    /*****************************/
    /*** Destruction/Fermeture ***/
    /****************************/
    /*** Fermeture du port série ***/
    portSerie->uartClose();
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




