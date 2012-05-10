#include "VideoProcessor.hpp"
#include <iostream>

using namespace cv;

VideoProcessor::VideoProcessor(void)
{
	mFirstFrame = true;

	mMovementDirection = vpDirection::DIR_FIX_POS;

	//TODO: wykrywa� automatycznie interesujacy obszar selection
	mSelection.x = 319;
	mSelection.y = 303;
	mSelection.width = 44;
	mSelection.height = 44;
}


VideoProcessor::~VideoProcessor(void)
{
}

void VideoProcessor::processFrame(Mat image)
{
	//Mat hsv, hue, mask;
	//TODO: przenie�� to do jakiego� configa
	int vmin = 10, vmax = 256, smin = 30, hsize = 16;
	int minDelta = 50;

	float hranges[] = {0,180};
    const float* phranges = hranges;

	//konwersja kolor�w z RGB do HSV
	cvtColor(image, hsv, CV_BGR2HSV);

	inRange(hsv, Scalar(0, smin, MIN(vmin,vmax)),
                    Scalar(180, 256, MAX(vmin, vmax)), mask);

	int ch[] = {0, 0};
	hue.create(hsv.size(), hsv.depth());
	mixChannels(&hsv, 1, &hue, 1, ch, 1);

	if(mFirstFrame)
	{
		//obliczenie histogramu �ledzonego obszaru
		Mat roi(hue, mSelection), maskroi(mask, mSelection);
        calcHist(&roi, 1, 0, maskroi, mHist, 1, &hsize, &phranges);
		normalize(mHist, mHist, 0, 255, CV_MINMAX);
		mFirstFrame = false;
		trackWindow = mSelection;
	}

	calcBackProject(&hue, 1, 0, mHist, backproj, &phranges);
    backproj &= mask;
    mTrackBox = CamShift(backproj, trackWindow,
                        TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));

	mGestureReady = false;

	//jezeli jeszcze nie zapamietano polozenia srodka to teraz zapamietuje
	if(!mFixedTrackBox.size.width)
	{
		mFixedTrackBox = mTrackBox;
	}

	int delta = mFixedTrackBox.center.y - mTrackBox.center.y;
	if(delta >= minDelta)
	{
		//gest lewy
		if(mGesture.type != Gesture::GESTURE_RHAND_LEFT)
		{
			mGesture.type = Gesture::GESTURE_RHAND_LEFT;
			mGestureReady = true;
		}
	}
	else if((-1*delta) >= minDelta)
	{
		//gest prawy
		if(mGesture.type != Gesture::GESTURE_RHAND_RIGHT)
		{
			mGesture.type = Gesture::GESTURE_RHAND_RIGHT;
			mGestureReady = true;
		}
	}
	else 
	{
		mGesture.type = Gesture::GESTURE_UNKNOWN;
	}

	/*
	//je�eli obiekt jest w spoczynku zapami�tuje jego po�o�enie jako po�o�enie odniesienia
	if(mMovementDirection == DIR_FIX_POS)
	{
		std::cout << "Setting fixed track box" << std::endl;
		mFixedTrackBox = mTrackBox;
		mMovementDirection = DIR_NONE;
	}

	int delta = mFixedTrackBox.center.y - mTrackBox.center.y;
	std::cout << "Delta = " << delta << std::endl;
	if(abs(delta) >= minDelta)
	{
		if(delta > 0)
		{
			//r�ka w lewo
			if(mMovementDirection == DIR_RIGHT)
			{
				mGesture.type = Gesture::GESTURE_RHAND_RIGHT;
				mMovementDirection = DIR_FIX_POS;
				mGestureReady = true;
			}
			else
			{
				mMovementDirection = DIR_LEFT;
			}
		} 
		else 
		{
			//r�ka w prawo
			if(mMovementDirection == DIR_LEFT)
			{
				mGesture.type = Gesture::GESTURE_RHAND_LEFT;
				mMovementDirection = DIR_FIX_POS;
				mGestureReady = true;
			}
			else
			{
				mMovementDirection = DIR_RIGHT;
			}
		}
	}

	if(abs(abs(mLastDelta) - abs(delta)) >= deltaToFix)
	{
		mMovementDirection = DIR_FIX_POS;
	}

	mLastDelta = delta;
	*/
}

/**
* Pobiera ostatnie wykryte po�o�enie �ledzonego obszaru
*/
RotatedRect VideoProcessor::getTrackBox()
{
	return mTrackBox;
}

Rect VideoProcessor::getSelection()
{
	return mSelection;
}

bool VideoProcessor::isGestureReady()
{
	return mGestureReady;
}

Gesture VideoProcessor::getGesture()
{
	return mGesture;
}