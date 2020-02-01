// ѕрограмма симул€ции движени€ космических тел
// под воздействием гравитационных сил
// ћаракулин ј.
// 2018
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

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
	Star[0].SetParametrs(800, 15, 0, 0, 500, 400);

	Star[1].SetParametrs(40, 5, 15, 0, 500, 100);
	Star[2].SetParametrs(40, 5, -15, 0, 500, 700);

	Star[3].SetParametrs(210, 17, 0, 12, 300, 400);
	Star[4].SetParametrs(210, 17, 0, -12, 700, 400);

	Display window;
	window.start("Universe");
	window.enable_trace = true;
	window.trace_color= LBlue;

	while (true) 
	{
		Engine.step(Star, NBR);
		window.draw_frame(Star, NBR);
		window.show("Universe");
		if (waitKey(2) >= 0) return 0;
		window.clear_draw();
	}
	return 0;
}