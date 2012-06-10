/************************************************************************************/
/*									Assistive.cpp									*/
/************************************************************************************/
/* Autorzy:		Marcin Marzy�ski, Daniel Jagielski, Tomasz Kmiecik					*/
/* Kierunek:	III rok Informatyka Stosowana, EAIiE, AGH							*/
/* Data modyfikacji: 10-06-2012														*/
/************************************************************************************/
/*																					*/
/* G��wna klasa aplikacji, jednocze�nie jej kontroler.								*/
/* Inicjalizuje wszystkie obiekty, w tym okna aplikacji. Nast�pnie odczytuje kolejne*/
/* ramki z filmu i przekazuje je do obiektu VideoProcessor, kt�ry odpowiedzialny	*/
/* jest za �ledzenie obiekt�w na ekranie i rozpoznawanie wykonywanych przez nie		*/
/* gest�w.																			*/
/************************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <ctype.h>

#include "VideoProcessor.hpp"
#include "StateKeeper.hpp"

using namespace cv;
using namespace std;

const static String PREVIEW_WINDOW_ID = "Preview";
const static String MENU_WINDOW_ID = "Menu";
Rect selection;
Point origin;
bool selectObject = false;
Mat image;

int main(int argc, char* argv[])
{
	//inicjalizacja video
	VideoCapture videoInput;
	videoInput.open("D:/projekt_interfejsy/marcin/gest.avi");

	if(!videoInput.isOpened())
	{
		cout << "***Could not initialize capturing...***\n";
		std::system("pause");
        return 0;
	}

	//utworzenie okienek
	cv::namedWindow(PREVIEW_WINDOW_ID);
	cv::namedWindow(MENU_WINDOW_ID);

	VideoProcessor videoProcessor;
	StateKeeper stateKeeper;
	cout << stateKeeper.getMainPos() << ":" << stateKeeper.getSubPos() << endl;

	//p�tla odczytywania klatek i wysy�ania ich do przetwarzania
	for(;;)
	{
		Mat frame;
		videoInput >> frame;
		if(frame.empty()) {
			cout << "Escaping loop \n";
			break;
		}

		frame.copyTo(image);
		
		videoProcessor.processFrame(image);
		if(videoProcessor.isGestureReady())
		{
			Gesture gesture = videoProcessor.getGesture();
			cout << "GESTURE FOUND " << gesture.type << endl;
			switch(gesture.type)
			{
			case Gesture::GESTURE_RHAND_LEFT:
				cout << "Keeper: Moving back";
				stateKeeper.moveBackwards();
				cout << stateKeeper.getMainPos() << ":" << stateKeeper.getSubPos() << endl;
				break;
			case Gesture::GESTURE_RHAND_RIGHT:
				cout << "Keeper: Moving forward" << endl;
				stateKeeper.moveForward();
				cout << stateKeeper.getMainPos() << ":" << stateKeeper.getSubPos() << endl;
				break;
			default:
				cout << "Unknown" << endl;
			}
		}

		if(videoProcessor.isLeftGestureReady())
		{
			Gesture gesture = videoProcessor.getLeftGesture();
			cout << "GESTURE FOUND " << gesture.type << endl;
			State* state = stateKeeper.GetState();
			switch(gesture.type)
			{
			case Gesture::GESTURE_LHAND_MOVE:
				if(state->getSubPos() == 1)
				{
					cout << "Keeper: Moving up" << endl;
					stateKeeper.moveUp();
				}
				else if(state->getSubPos() == 0)
				{
					cout << "Keeper: Moving down" << endl;
					stateKeeper.moveDown();
				}
				else
				{
					cout << "Keeper: Executing action" << endl;
					stateKeeper.GetState()->func();
				}
				break;
			default:
				cout << "Unknown" << endl;
				break;
			}
		}

		//wyswietlenie stanu menu
		imshow(MENU_WINDOW_ID, stateKeeper.GetState()->getImg());

		//rysowanie podgladu i markerow na ramce
		ellipse( image, videoProcessor.getTrackBox(), Scalar(0,0,255), 3, CV_AA );
		rectangle(image, videoProcessor.getSelection(), Scalar(255, 0, 0), 3, CV_AA);
		rectangle(image, videoProcessor.getLeftSelection(), Scalar(0, 255, 0), 3, CV_AA);
		imshow(PREVIEW_WINDOW_ID, image);
		char c = (char)waitKey(5);
		if(c == 27)
			break;
	}
	
	system("pause");
	return 0;
}
