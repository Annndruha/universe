// ѕрограмма симул€ции движени€ космических тел
// под воздействием гравитационных сил
// ћаракулин ј.
// 2018
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <time.h>
#include <windows.h>
#include <random>

#include "headers/Colors.h"
#include "headers/Physics.h"
#include "headers/Display.h"


int main(){

	Physics Engine;
	Engine.enable_collapses = true;
	Engine.gravity_constant = 64;
	Engine.simulation_step_delay = 0.2;

	const int NBR = 5; // ≈сли поставите больше, дл€ остальных тел будут установлены случайные начальные параметы
	CreatePlanet Star[NBR];
	//...................m...r...vx..vy..cx...cy
	Star[0].SetParametrs(800, 20, 0, 0, 600, 350);

	Star[1].SetParametrs(8, 5, 0, 11, 250, 350);
	Star[2].SetParametrs(8, 5, 0, -11, 950, 350);

	Star[3].SetParametrs(50, 10, 0, -18, 750, 350);
	Star[4].SetParametrs(50, 10, 0, 18, 450, 350);

	Display window;
	window.start("Universe");
	window.enable_trace = true;
	window.trace_color= LBlue;

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