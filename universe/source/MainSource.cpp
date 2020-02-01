
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

//#include <math.h>
#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <random>

//using namespace std;
#include "../headers/Colors.h"
#include "../headers/Physics.h"
#include "../headers/Display.h"


int main(){

	Physics Engine;
	Engine.enable_collapses = true;
	Engine.gravity_constant = 64;
	Engine.simulation_step_delay = 0.2;

	const int NBR = 6;
	CreatePlanet Star[NBR];//m...r...vx..vy..cx...cy
	Star[0].SetParametrs(400, 15, 0, 0, 550, 415);
	Star[1].SetParametrs(210, 20, 0, 10, 300, 415);
	Star[2].SetParametrs(210, 20, 0, -10, 800, 415);

	display window;
	window.start("Universe");
	window.enable_trace = true;

	while (true) 
	{
		Engine.step(Star, NBR);
		window.draw_frame(Star, NBR);
		window.show("Universe");
		if (waitKey(1) >= 0) return 0;
		window.clear_draw();
	}
	return 0;
}