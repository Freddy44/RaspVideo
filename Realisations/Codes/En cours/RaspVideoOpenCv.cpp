//===========================================================================//
// Include                                                                   //
//===========================================================================//
#include <stdio.h>
#include <iostream>

//#include <cv.h>
//#include <highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"
#include <vector>
#include  <opencv2/opencv.hpp>

//#include <math.h>

using namespace cv;

CvSize size = cvSize(640,480);

/**
* Constante définissant le titre de la fenêtre
*/
const char* wTitle = "RaspVideo";
const char* wTitleGray = "RaspVideo Gray";



//=======================================================//
// Fonction qui charge et retourne une image		 //
// @return image			                 //
//=======================================================//
IplImage* funcImage(const char* filename){
	/**
	* Charge une image depuis un fichier
	* IplImage* cvLoadImage( const char* filename, int flags=CV_LOAD_IMAGE_COLOR );
	* @param filename : nom du fichier
	*/
	IplImage* image = cvLoadImage(filename);

	/**
	* Condition 
	* En cas de problème, image non trouvée, fin de la fonction
	*/
	if(!image){
		printf("L'image est introuvable ou incorrect\n");
		return NULL;
	}

	/**
	* Image retournée
	*/
	return image;
}

//=======================================================//
// Fonction qui charge une video 	                 //
// @return capture					 //
//=======================================================//
CvCapture* funcVideo(){
	/**
	* Constructeur de la cature vidéo:
	* CvCapture* cvCaptureFromFile(int device);
	* CvCapture:
	* Structure de la vidéo capturée ~>capture de flux
	* typedef struct CvCapture CvCapture;
	* Le CvCapture de la structure n'a pas d'interface publique et n'est utilisé que comme un paramètre pour les fonctions de capture vidéo.
	* @param 0 : Device sélectionnée
	*/
	CvCapture* capture = cvCaptureFromCAM(0);//TODO => detruire

	/**
	* Condition 
	* En cas de problème, capture non réalisée, fin de la fonction
	*/
	if( !capture ){
            fprintf( stderr, "ERROR: capture is NULL \n" );
            getchar();
            //break;//TODO
    	}

	/**
	* structure vidéo retournée
	*/
	return capture;
}


//=======================================================//
// Création de la structure de l'image via la récupération// 	
// d'un flux vidéo					 //
// @return frame : trame saisie, décompressée            //
//=======================================================//
IplImage* imgFrame(CvCapture* capture){
	/**
	*IplImage* cvQueryFrame( CvCapture* capture );
	* Fonction cvQueryFrame:
	* Saisis une trame de la caméra, la décompresse et la retourne
	* @param capture => capture du flux video
	* @return frame => la trame decompressée
	*/
	IplImage* frame = cvQueryFrame(capture);//TODO=> detruire??
	return frame;
}

//=======================================================//
// Création d'une image binaire                          //
// où le jaune correspondra au blanc			 //
// et le reste sera noir				 //
// @return image GRAY (niveau de gris)
//=======================================================//
IplImage* GetThresholdedImage(IplImage* img){
	/**
	* Création de l'image à travers la méthode cvCreateImage()
	* IplImage* cvCreateImage(CvSize size, int depth, int channels)
	* @param cvGetSize(img) : CvSize cvGetSize(const CvArr* arr)-> (width, height)
	*/
	IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);

	/**
	* Convertion de l'image BGR (RGB inversé) en HSV:
	* void cvtColor(InputArray src, OutputArray dst, int code, int dstCn=0 )
	* @param img : image source
	* @param imgHSV : image sortante
	* @param CV_BGR2HSV : code de convertion couleur allant du BGR en HSV
	*/
	cvCvtColor(img, imgHSV, CV_BGR2HSV);

	/**
	* Création de l'image qui contiendra l'image GRAY finale 
	*/
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);

	/**
	* Vérification des élements de matrices 
	* Les deux cvScalar vérifient que les valeurs retournées correspondent
	* aux codes de couleurs BGR choisis:
	* void inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst)
	* @param imgHSV : image source mise en GRAY
	* @param cvScalar(40, 100, 100) : Limite inférieure de code BGR choisi => Jaune 
	* @param cvScalar(50, 255, 255) : Limite supérieure de code BGR choisi => Jaune
	* @param imgThreshed : Image du traitement finale
	*/
	cvInRangeS(imgHSV, cvScalar(35, 100, 100), cvScalar(75, 255, 255), imgThreshed);

	/**
	* Libère la mémoire allouée 
	* void cvReleaseImage( IplImage** image );
	* @param &imgHSV : pointeur sur la structure de l'image créée
	*/
	cvReleaseImage(&imgHSV);

	/**
	* Image retournée
	* @return imgThreshed
	*/
	return imgThreshed;
}


//=======================================================//
// Méthode de définition d'un point à un moment t        //
// @return pointXY					 //
//=======================================================//
CvPoint calculPoint(IplImage* img){
	/**
	* Constante définissant les coordonnées X et Y d'un point
	*/
	static int posX = 0;
        static int posY = 0;

	/**
	* Constructeur d'un point
	* CvPoint cvPoint(int x, int y)
	*/
	CvPoint pointXY= cvPoint(posX,posY); 
	/**
	* Constructeur de la structure de l'image Gray à travers la méthode GetThresholdedImage()
	* @param img : image captée
	*/
	IplImage* imgYellowThresh = GetThresholdedImage(img);

	/*
	* Calcul de la position estimer par le point à un moment donnée
	* CvMoments* moments => Moments de sortie
	* Calcule tous les moments jusqu'au troisième ordre d'une forme polygonale ou pixellisée
	* void cvMoments(const CvArr* arr, CvMoments* moments, int binary=0 )
	*/
        CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
        cvMoments(imgYellowThresh, moments, 1);

        double moment10 = cvGetSpatialMoment(moments, 1, 0);
        double moment01 = cvGetSpatialMoment(moments, 0, 1);
        double area = cvGetCentralMoment(moments, 0, 0);
	
        posX = moment10/area;
        posY = moment01/area;

	/**
	* Libère la mémoire allouée 
	* void cvReleaseImage( IplImage** image );
	* @param &imgYellowThresh : pointeur sur la structure de l'image créée
	*/
	cvReleaseImage(&imgYellowThresh);

	/**
	* Libère la mémoire allouée 
	* void cvReleaseImage( IplImage** image );
	* @param moments : pointeur sur la structure de l'image créée
	*/
	delete moments;
	
	/**
	* Retourne le point déterminé à un moment t
	* @return pointXY 
	*/
	return pointXY;
}


//=======================================================//
// Méthode qui dessine un cercle et suit un objet	 //
//			selon sa position                //
//=======================================================//
void drawCercle(IplImage* frame){
	/**
	* Check le succès de l'arrivée d'une trame de l'image 
	* En cas de problème, fin de la fonction
	*/
	if( !frame ){
            fprintf( stderr, "ERROR: capture is NULL \n" );
            getchar();
            //break;//TODO
    	}

	/**
	* Constante définissant les point X et Y d'un point
	*/
	static int posX = 0;
        static int posY = 0;
	int lastPointX = posX;
	int lastPointY = posY;

	/**
	* Constructeur de la structure de l'image via la méthode imgFrame()
	* @param capture : Capture du flux vidéo
	*/
	IplImage* imgYellowThresh = GetThresholdedImage(frame);

	/*
	* Calcul de la position estimer par le point à un moment donnée
	* CvMoments* moments => Moments de sortie
	* Calcule tous les moments jusqu'au troisième ordre d'une forme polygonale ou pixellisée
	* void cvMoments(const CvArr* arr, CvMoments* moments, int binary=0 )
	*/
        CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
        cvMoments(imgYellowThresh, moments, 1);

        double moment10 = cvGetSpatialMoment(moments, 1, 0);
        double moment01 = cvGetSpatialMoment(moments, 0, 1);
        double area = cvGetCentralMoment(moments, 0, 0);

	//dernières et actuelles positions de la sphère
	posX = moment10/area;
        posY = moment01/area;

	/**
	* Condition //TODO
	* 
	*/	
	if (lastPointX >0 && lastPointY >0 && posX > 0 && posY > 0){
		/**
		* Dessine un simple cercle selon le centre et le rayon donné
		* cvCircle Method (img (IntPtr), center (Point),radius (Int32), color (MCvScalar),thickness (Int32), lineType (LINE_TYPE), shift (Int32))
		* @param frame : Image sur laquelle le cercle sera dessiné
		* @param cvPoint(100,100) : Initialise les coordonnées du centre dans l'image
		* @param 20 : Rayon 
		* @param CV_RGB(209, 182, 6) : Couleur RGB du cercle
		* @param 3 : épaisseur du cercle en pixels
		* [option]@param thickness : épaisseur du cercle
		* [option]@param lineType : Type de ligne pour dessiner
		*/	
		cvCircle(frame, cvPoint(posX,posY), 20, CV_RGB(209, 182, 6), 3,8,0);
		
	/**
	* Libère la mémoire allouée 
	* void cvReleaseImage( IplImage** image );
	* @param &imgYellowThresh : pointeur sur la structure de l'image créée
	*/
	cvReleaseImage(&imgYellowThresh);

	/**
	* Libère la mémoire allouée 
	* @param moments : pointeur sur la structure de l'image créée
	*/
	delete moments;
	}
}



//=======================================================//
// Méthode qui dessine un cercle autour de l'objet	 //
//	et suit un objet selon sa position               //
//=======================================================//

void contourCercle(IplImage* img){
	int thresh = 100;//=>
	//int max_thresh = 255;
	RNG rng(12345);
	//Mat src(img);
	Mat src_Gray(GetThresholdedImage(img));//=>
	//blur de l'image gray
	blur( src_Gray, src_Gray, Size(3,3) );//==>
	
	Mat canny_output;
  	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;
	
	/// Detect edges using canny
  	Canny( src_Gray, canny_output, thresh, thresh*2, 3 );
  	/// Find contours CV_RETR_TREE
  	findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  	/// Draw contours /CV_FILLED
  	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  	for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, Point() );
     }
	imshow( "Contours", drawing );
	//return drawing;
	
}

//=======================================================//
// Méthode HOUGHCircles qui dessine un cercle autour de l'objet	 //
//	et suit un objet selon sa position               //
//=======================================================//

void contourCercle2(IplImage* img){
	Mat src(img);
	Mat src_Gray(GetThresholdedImage(img));//=>
	// smooth it, otherwise a lot of false circles may be detected
//http://docs.opencv.org/modules/imgproc/doc/filtering.html?highlight=gaussianblur#gaussianblur
	GaussianBlur( src_Gray, src_Gray, Size(9, 9), 1, 1 );
	vector<Vec3f> circles;
//http://docs.opencv.org/search.html?q=HoughCircles&check_keywords=yes&area=default
//HoughCircles(src_Gray, circles, CV_HOUGH_GRADIENT,2, src_Gray.rows/4, 200, 100 );
    	HoughCircles(src_Gray, circles, CV_HOUGH_GRADIENT,2,  src_Gray.rows/4, 200, 100 );
	for( size_t i = 0; i < circles.size(); i++ )
    	{
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
	// draw the circle outline
         circle( src, center, radius, Scalar(209, 182, 6), 3, 8, 0 );//Scalar(0,0,255)
    }

}

//=======================================================//
// Affiche une image                                     //
//=======================================================//
void DisplayImage(IplImage* img, const char* wTitle){//, int time
	/**
	* Boucle infinie permettant d'afficher l'image dans une fenêtre
	* en attendant une action de l'utilisateur
	*/
	while(1){
		/**
		* Création d'une fenêtre:
		* void namedWindow(const string& winname, int flags=WINDOW_AUTOSIZE )
		* @param wTitle: Titre de la fenêtre
		* @param CV_WINDOW_AUTOSIZE: flag sur la fenêtre 
		* => Ajuste automatiquement les dimension de la fenêtre en fonction de l'image reçue
		* => n'autorise plus la redéfinition manuelle de cette dernière
		*/
		cvNamedWindow(wTitle,CV_WINDOW_AUTOSIZE);

		/**
		* Montre l'image dans une fenêtre spécifiée
		* void cvShowImage( const char* name, const CvArr* image );
		* @param wTitle : Fenêtre spécifiée
		* @param image : Image a montrer
		*/
		cvShowImage(wTitle, img);

		/**
		* Condition de fin de boucle : Attente pression de la touche esc
		* int cvWaitKey( int delay=0 );
		* @param 10 : en ms
		* @param 27 : code ASCII de la touche esc
		*/
		if( (cvWaitKey(10) & 255) == 27 ){break;}
	}

	/**
	* Destruction de la fenêtre
	* void cvDestroyWindow( const char* name );
	* @param wTitle : nom de la fenêtre à detruire
	*/
	cvDestroyWindow(wTitle);
}




//=======================================================//
// Affiche une video                                     //
//=======================================================//
void DisplayVideo(CvCapture* capture){//, int time
	/**
	* Création d'une fenêtre:
	* void namedWindow(const string& winname, int flags=WINDOW_AUTOSIZE )
	* @param wTitle: Titre de la fenêtre
	* @param CV_WINDOW_AUTOSIZE: flag sur la fenêtre 
	* => Ajuste automatiquement les dimension de la fenêtre en fonction de l'image reçue
	* => n'autorise plus la redéfinition manuelle de cette dernière
	*/
	cvNamedWindow(wTitle,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(wTitleGray,CV_WINDOW_AUTOSIZE);
	
	IplImage* img;
	
	
	/**
	* Boucle infinie permettant d'afficher l'image dans une fenêtre
	* en attendant une action de l'utilisateur
	*/
	while(1){
		/**
		* Constructeur de la structure de l'image via la méthode imgFrame()
		* @param capture : Capture du flux vidéo
		*/
		img = imgFrame(capture);//TODO=> detruire

		/**
		* Condition:
		* Check le succès de l'arrivée d'une image
		* En cas de problème, fin de la fonction
		*/
        	if( !img ){
                	fprintf( stderr, "ERROR: frame is null...\n" );
                	getchar();
                	//break;//TODO
		}

		/**
		* Appel de la méthode drawCercle
		* @param img : image créée plus haut
		*/
		//drawCercle(img);
		
		//contourCercle( img);
		contourCercle2(img);
		/**
		* Montre l'image dans une fenêtre spécifiée
		* void cvShowImage( const char* name, const CvArr* image );
		* Première:
		* @param wTitle : Titre fenêtre Flux "sans traitement d'image)
		* @param img : Image a montrer
		* Seconde:
		* @param wTitleGray : Titre fenêtre de traitement Gray
		* @param GetThresholdedImage(img) : Appel de la méthode de traitement Gray
		*/
		cvShowImage(wTitle, img);
		cvShowImage(wTitleGray, GetThresholdedImage(img));
		
		/**
		* Condition de fin de boucle : Attente pression de la touche esc
		* int cvWaitKey( int delay=0 );
		* @param 10 : en ms
		* @param 27 : code ASCII de la touche esc
		*/
		if( (cvWaitKey(10) & 255) == 27 ){break;}
		
	}

	/**
	* Destruction de la fenêtre
	* void cvDestroyWindow( const char* name );
	* @param wTitle : nom de la fenêtre à detruire
	*/
	cvDestroyAllWindows();

	/**
	* Libère la structure de CvCapture => libère la mémoire allouée 
	* void cvReleaseCapture( CvCapture** capture );
	* @param &capture : pointeur sur la structure de la vidéo captée
	*/
	cvReleaseCapture(&capture);

	/**
	* Libère la mémoire allouée 
	* void cvReleaseImage( IplImage** image );
	* @param &img : pointeur sur la structure de l'image créée
	*/
	cvReleaseImage(&img);
}





//=======================================================//
// Fonction d'entrée du programme                        //
//=======================================================//
int main(int argc, char* argv[])
{
	
/*Test sur une image */
	/*
	* Constructeur Définissant l'image sur laquelle on désire travailler
	* par appel de la fonction funcImage()
	*@param "lena_std.tif" : Image choisie
	*/ 
	//IplImage* image = funcImage("lena_std.tif");

	/**
	* Condition:
	* Check le succès du fait d'avoir l'image
	* En cas de problème, fin de la fonction
	*/	
	/*if(!image){
		printf("Impossible de trouver l'image");
		return 0;
	}*/

	/**
	* Affiche le résultat d'affichage
	*/
	//DisplayImage(image, "Image");

	/**
	* Libère la mémoire allouée 
	* void cvReleaseImage( IplImage** image );
	* @param &image : pointeur sur la structure de l'image créée
	*/
	//cvReleaseImage(&image);

	/* Résultat pour une vidéo */
	DisplayVideo(funcVideo());
	
	/**
	* Libère la mémoire allouée 
	* void cvReleaseImage( IplImage** image );
	* @param &image : pointeur sur la structure de l'image créée
	*/
	//cvReleaseImage(&imgFrame());
	
	cvDestroyAllWindows();
	

	return 0;
}
