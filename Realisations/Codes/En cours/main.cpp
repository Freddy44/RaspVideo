/*
 * main.cpp
 *
 *  Created on: 26 nov. 2013
 *      Author: Frédéric Gicquel
 */


#include "FluxInfo.h"

#include <iostream>
#include "Constantes.h"
#include "Camera.h"
#include "ThreshedImage.h"
#include "Draw.h"

#include "VideoThread.h"
#include <iostream>
using namespace std;

/*
* Méthode
*
* @param:
* @return:
*/
int main(int argc, char *argv[])
{
    //FluxInfo* info = new FluxInfo();
    //info->fluxOpen();
    //info->fluxWrite();*/
    //info->memory_usage();

    //VideoThread* test_pthread = new VideoThread();
    Camera* camera = new Camera();
    ThreshedImage* threshedImage = new ThreshedImage();
    Draw* draw = new Draw();

    IplImage* imgCam;
    IplImage* imgThresh;

    cvNamedWindow(wTitle,CV_WINDOW_AUTOSIZE);
    cvNamedWindow(wTitleGray,CV_WINDOW_AUTOSIZE);

    while(1)
    {

        imgCam = camera->getFrame();

        threshedImage->setThresholdedImage(imgCam);
        imgThresh = threshedImage->getThresholdedImage();

        draw->setDraw(imgCam,imgThresh);
        draw->getPerimeterCircle();

        cvShowImage(wTitle, imgCam);
        cvShowImage(wTitleGray, imgThresh);

        //test_pthread->startThread(0);
        //test_pthread->stopThread(0);
        //test_pthread->startThread(0);
        //test_pthread->wait2(0);
        //test_pthread->startThread(0);
        //test_pthread->wait2(0);

        if( (cvWaitKey(10) & 255) == 27 )
        {
            break;
        }
    }

    cvDestroyAllWindows();

    cvReleaseImage(&imgCam);
    cvReleaseImage(&imgThresh);
    //info->fluxClose();
    return 0;
}
