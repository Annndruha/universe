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


//____Класс_ПЛАНЕТА____0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
class CreatePlanet
{
public:
	bool life = 0;
	double mass = 1;
	double radius = 1;
	double v_x = 0;
	double v_y = 0;
	double c_x = 0;
	double c_y = 0;

	void SetParametrs(bool l, double m, int r, double vx, double vy, double cx, double cy)
	{
		life = l;
		mass = m;
		radius = r;
		v_x = vx;
		v_y = vy;
		c_x = cx;
		c_y = cy;
	}
};
//____Стартовые_параметры____0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
int main()
{
	const int spawn_limit = 0;
	const int NBR=3;
	Point cor[NBR];

	CreatePlanet P[NBR];//...m...r...vx..vy..cx...cy..
	P[0].SetParametrs(true, 1353, 15, 0, 0, 750, 415);

	P[1].SetParametrs(true, 210, 10, 0, 20, 500, 415);
	P[2].SetParametrs(true, 210, 10, 0, -21, 1000, 415);

	//P[3].SetParametrs(true, 213, 12, 8, 13, 500, 200);

	//P[4].SetParametrs(true, 200, 10, 24, 30, 600, 700);


	const int DELAY = 1;
	const double G = 65;
	const double zone = 100000;
	
	int spawn = 0;

	//Mat background= imread("sky4.jpg");
	Mat background= Mat::zeros(830, 1500, CV_8UC3);
	Mat planets = Mat::zeros(background.rows, background.cols, CV_8UC3);//Стираемый слой для планет
	Mat spin = Mat::zeros(background.rows, background.cols, CV_8UC3);//Нестираемый слой для траектории
	Mat output = Mat::zeros(background.rows, background.cols, CV_8UC3);//Результирующий слой

	Scalar Yellow(0, 255, 255);
	Scalar Grey(100, 100, 100);
	Scalar Red  (0, 0, 255);
	Scalar Green(0, 255, 0);
	Scalar Blue(255, 0, 0);
	Scalar LBlue(255, 170, 66);

	namedWindow("Universe");
	moveWindow("Universe", 200, 50);

while (true)
	{
//____Обработка физики____00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
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
				
					if (r < P[i].radius + P[j].radius)//Обработчик столкновений00000000000000000000000000000000000000000000000000000000000000000000000
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
				double vx = rand() % 25 - 12; cout << "vx= " << vx << endl;
				double vy = rand() % 25- 12; cout << "vy= " << vy << endl;
				double cx = rand() % 1400; cout << "cx= " << cx << endl;
				double cy = rand() % 800; cout << "cy= " << cy << endl << endl << endl;
				P[i].SetParametrs(true, m, r, vx, vy, cx, cy);
				spawn++;
			}
		}
	}

//____Отрисовка траеткории____0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	for (int i = 0; i < NBR; i++)//Смещение планет на новые координаты
	{
		if (P[i].life == true)
		{
			P[i].c_x = P[i].c_x + P[i].v_x;
			P[i].c_y = P[i].c_y + P[i].v_y;
			cor[i].x = P[i].c_x;
			cor[i].y = P[i].c_y;
			circle(planets, cor[i], P[i].radius, Yellow, -1, LINE_AA);//Отрисовка планеты
			circle(spin, cor[i], 1, LBlue, -1, LINE_AA);//Отрисовка следа
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



//____Вывод_____000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
		imshow("Universe", output);
		planets = NULL;
		if (waitKey(DELAY) >= 0) return 0;
	}
	return 0;
}

