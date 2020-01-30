#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

#include "../headers/Planet.h"
#include "../headers/Colors.h"


int main()
{
	const int spawn_limit = 5;
	const int NBR=3;
	Point cor[NBR];

	CreatePlanet P[NBR];//...m...r...vx..vy..cx...cy..
	P[0].SetParametrs(true, 900, 15, 0, 0, 550, 415);
	P[1].SetParametrs(true, 210, 10, 0, 15, 300, 415);
	P[2].SetParametrs(true, 210, 10, 0, -15, 800, 415);



	const int DELAY = 1;
	const double G = 65;
	const double zone = 100000;
	
	int spawn = 4;

	Mat background= imread("C:/Users/Andrey/source/repos/Annndruha/universe/universe/resources/sky3.jpg");
	Mat background_2= Mat::zeros(700, 1200, CV_8UC3);
	Mat planets = Mat::zeros(background.rows, background.cols, CV_8UC3);//Стираемый слой для планет
	Mat spin = Mat::zeros(background.rows, background.cols, CV_8UC3);//Нестираемый слой для траектории
	Mat output = Mat::zeros(background.rows, background.cols, CV_8UC3);//Результирующий слой



	namedWindow("Universe");
	moveWindow("Universe", 200, 50);

while (true)
	{
// Обработка физики
	for (int i = 0; i < NBR; i++)//Планета для которой считается сумма сил и новая скорость
	{
		if ((P[i].life == true) && (P[i].c_x>-zone) && (P[i].c_x <1600 + zone) && (P[i].c_y>-zone) && (P[i].c_y <800 + zone))
		{

			double r = 0;
			double F_y = 0;
			double F_x = 0;

			for (int j = 0; j < NBR; j++)//Сумматор всех сил, которые действуют на планету со стороны других планет
			{
				if ((j != i) && (P[i].life == true) && (P[j].life == true))//Исключение самосилы
				{
					r = sqrt(pow((P[j].c_x - P[i].c_x), 2) + pow((P[j].c_y - P[i].c_y), 2));//Расстояние между взаимодействующими планетами
					F_x = F_x + G*P[j].mass*(P[j].c_x - P[i].c_x) / pow(r, 3);//Счетчик силы по х
					F_y = F_y + G*P[j].mass*(P[j].c_y - P[i].c_y) / pow(r, 3);//Счетчик силы по y
				
					if (r < P[i].radius + P[j].radius)//Обработчик столкновений
					{
							F_x = 0;
							F_y = 0;
							P[i].v_x = ((P[i].v_x*P[i].mass + P[j].v_x*P[j].mass) / (P[i].mass + P[j].mass));//Скорость новой планеты исходя из суммы импульсов
							P[i].v_y = ((P[i].v_y*P[i].mass + P[j].v_y*P[j].mass) / (P[i].mass + P[j].mass));


							P[i].c_x = ((P[i].c_x*P[i].mass + P[j].c_x*P[j].mass) / (P[i].mass + P[j].mass));//Новая координата в центре масс столкнувшихся
							P[i].c_y = ((P[i].c_y*P[i].mass + P[j].c_y*P[j].mass) / (P[i].mass + P[j].mass));

							P[i].mass = P[i].mass + P[j].mass;//Новая масса
							P[i].radius = pow(pow(P[i].radius, 3) + pow(P[j].radius, 3), 0.33333);//Новый объямный радиус
							P[j].life = false;//Уничтожение планеты
					}
				}

			}

			P[i].v_x = P[i].v_x + F_x;
			P[i].v_y = P[i].v_y + F_y;
		}
		else
		{
			if (spawn < spawn_limit) {//Автоматический спавн новых планет с рандомными параметрами
				srand(rand());
				double m = rand() % 100; cout << "m= " << m << endl;
				double r = 6 + m / 4; cout << "r= " << r << endl;
				double vx = int(rand() % 25) - 12; cout << "vx= " << vx << endl;
				double vy = int(rand() % 25)- 12; cout << "vy= " << vy << endl;
				double cx = rand() % 1400; cout << "cx= " << cx << endl;
				double cy = rand() % 800; cout << "cy= " << cy << endl << endl << endl;
				P[i].SetParametrs(true, m, r, vx, vy, cx, cy);
				spawn++;
			}
		}
	}

// Отрисовка траеткории
	for (int i = 0; i < NBR; i++)//Смещение планет на новые координаты
	{
		if (P[i].life == true)
		{
			P[i].c_x = P[i].c_x + P[i].v_x;
			P[i].c_y = P[i].c_y + P[i].v_y;
			cor[i].x = P[i].c_x;
			cor[i].y = P[i].c_y;
			circle(planets, cor[i], P[i].radius, Yellow, -1, LINE_AA);//Отрисовка планеты
			//circle(spin, cor[i], 1, LBlue, -1, LINE_AA);//Отрисовка следа
		}
	}

	for (int i = 0; i < background.rows; i++)
	{
		uchar* ptr = (uchar*)(background.data + i * background.step);
		uchar* ptr_draw = (uchar*)(spin.data + i * spin.step);
		uchar* ptr_out = (uchar*)(background.data + i * background.step);
		for (int j = 0; j < background.cols; j++)
		{
			if ((ptr_draw[3 * j + 0] != 0) || (ptr_draw[3 * j + 1] != 0) || (ptr_draw[3 * j + 2] != 0))
			{
				ptr_out[3 * j + 0] = ptr_draw[3 * j + 0];
				ptr_out[3 * j + 1] = ptr_draw[3 * j + 1];
				ptr_out[3 * j + 2] = ptr_draw[3 * j + 2];
			}
			else
			{
				ptr_out[3 * j + 0] = ptr[3 * j + 0];
				ptr_out[3 * j + 1] = ptr[3 * j + 1];
				ptr_out[3 * j + 2] = ptr[3 * j + 2];
			}
		}
	}

	for (int i = 0; i < background.rows; i++)
	{
		uchar* ptr = (uchar*)(background.data + i * background.step);
		uchar* ptr_draw = (uchar*)(planets.data + i * planets.step);
		uchar* ptr_out = (uchar*)(output.data + i * output.step);
		for (int j = 0; j < background.cols; j++)
		{
			if ((ptr_draw[3 * j + 0] != 0) || (ptr_draw[3 * j + 1] != 0) || (ptr_draw[3 * j + 2] != 0))
			{
				ptr_out[3 * j + 0] = ptr_draw[3 * j + 0];
				ptr_out[3 * j + 1] = ptr_draw[3 * j + 1];
				ptr_out[3 * j + 2] = ptr_draw[3 * j + 2];
			}
			else
			{
				ptr_out[3 * j + 0] = ptr[3 * j + 0];
				ptr_out[3 * j + 1] = ptr[3 * j + 1];
				ptr_out[3 * j + 2] = ptr[3 * j + 2];
			}
		}
	}


	// Вывод на экран
	imshow("Universe", output);
	planets = NULL;
	if (waitKey(DELAY) >= 0) return 0;
	}
	return 0;
}