/************************************************************************************/
/*									State.cpp								*/
/************************************************************************************/
/* Autorzy:		Marcin Marzy�ski, Daniel Jagielski, Tomasz Kmiecik					*/
/* Kierunek:	III rok Informatyka Stosowana, EAIiE, AGH							*/
/* Data modyfikacji: 10-06-2012														*/
/************************************************************************************/
/*																					*/
/* Klasa przechowuj�ca stan dla maszyny stan�w StateKeeper. Posiada informacj�		*/
/* o powi�zanej ikonce menu dla tego stanu oraz o funkcji, kt�r� nalezy wykona� przy*/
/* aktywacji tego stanu																*/
/************************************************************************************/
#include "State.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

State::State(void)
{
}


State::~State(void)
{
}

//gettery
std::string State::getname() {
	return name;
}

int State::getMainPos() {
	return mainPos;
}


int State::getSubPos() {
	return subPos;
}


//settery
void State::setMainPos(int newvalue) 
{
	mainPos = newvalue;
}


void State::setSubPos(int newvalue) 
{
	 subPos = newvalue;
}


void State::setname(std::string newname)
{
	name = newname;
}

void State::setImg(std::string path)
{
	img = cv::imread(path);
}

cv::Mat State::getImg()
{
	return img;
}
