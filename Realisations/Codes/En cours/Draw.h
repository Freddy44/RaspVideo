/*
 * Draw.h
 *
 *      Author: Frédéric Gicquel
 *
 *  Classe qui déssine une forme selon un objet
 *  @return:
 *
 */
#ifndef DRAW_H
#define DRAW_H

#include <iostream>
using namespace std;


#include  <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
using namespace cv;

class Draw
{
public:
    /* Constructeur */
    Draw();

    /* Destructeur */
    virtual ~Draw();

    /* Setter */
    void setDraw(IplImage*,IplImage*);

    /* Getter */
    void getPerimeterCircle();

protected:

private:
    /* Attributs */
    Mat m_imgDrawGray;
    Mat m_imgDraw;

    /* Méthodes */
    void perimeterCircle();
};

#endif // DRAW_H
