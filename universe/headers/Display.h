#pragma once
//Класс отрисовки графического окна
class display
{
private:
	Mat background = imread("C:/Users/Andrey/source/repos/Annndruha/universe/universe/resources/sky3.jpg");
	Mat trace = Mat::zeros(background.rows, background.cols, CV_8UC3);//Нестираемый слой для траектории
	Mat draw = Mat::zeros(background.rows, background.cols, CV_8UC3);//Стираемый слой для планет
	Mat out = Mat::zeros(background.rows, background.cols, CV_8UC3);//Результирующий слой

	void merge_two_layers(Mat, Mat);
	void draw_trace(CreatePlanet* pointer);
	void draw_planet(CreatePlanet* pointer);
	//void draw_time(double T);
	void merge_layers();

public:
	bool enable_trace = false;
	void start(String window_name);
	void show(String window_name);
	void draw_frame(CreatePlanet* pointer, int N);
	void clear_draw();
};


// Создание именованного окна
void display::start(String window_name)
{
	namedWindow(window_name);
	moveWindow(window_name, 50, 20);
}

// Показ кадра
void display::show(String window_name)
{
	imshow(window_name.c_str(), out);
}

//Функция попиксильного сведения двух слоёв
void display::merge_two_layers(Mat down_layer, Mat up_layer)
{
	for (int i = 0; i < down_layer.rows; i++)
	{
		uchar* ptr_up = (uchar*)(up_layer.data + i * up_layer.step);
		uchar* ptr_down = (uchar*)(down_layer.data + i * down_layer.step);
		for (int j = 0; j < down_layer.cols; j++)
		{
			// Из за плохой поддержки прозрачности в PpenCV, RGB = (0,0,0) используется в качестве прозрачного цвета
			// А чёрный определён как RGB = (1,0,0)
			if ((ptr_up[3 * j + 0] != 0) || (ptr_up[3 * j + 1] != 0) || (ptr_up[3 * j + 2] != 0))
			{
				ptr_down[3 * j + 0] = ptr_up[3 * j + 0];
				ptr_down[3 * j + 1] = ptr_up[3 * j + 1];
				ptr_down[3 * j + 2] = ptr_up[3 * j + 2];
			}
		}
	}
}

//Объединение слоёв графики
void display::merge_layers()
{
	out = background.clone();
	merge_two_layers(out, trace);
	merge_two_layers(out, draw);
};

//Функция отрисовки следа
void display::draw_trace(CreatePlanet* pointer)
{
	CreatePlanet& planet = *pointer;
	circle(trace, Point(planet.c_x, planet.c_y), 2, green, -1, 8);
	
};

//Функция отрисовки снаряда
void display::draw_planet(CreatePlanet* pointer)
{
	CreatePlanet& planet = *pointer;
	circle(draw, Point(planet.c_x, planet.c_y), planet.radius, Yellow, -1, LINE_AA);
};

//Функция отрисовки времени симуляции
//void display::draw_time(double T)
//{
//	String k = std::to_string(T);
//	k = k.substr(0, k.size() - 2);
//	String r = "t= " + k + " c";
//	putText(draw, r, Point(200, 760), FONT_HERSHEY_SIMPLEX, 0.8, black, 2, 8, false);//Номер снаряда
//};

// Отрисовка кадра. time - время симуляции, bullet_number - номер снаряда
void display::draw_frame(CreatePlanet* pointer, int N)
{
	for (int n = 0; n < N; n++)
	{
		CreatePlanet& planet = *(pointer+n);
		if (planet.life == true)
		{
			if (enable_trace) { draw_trace(pointer + n); }
			draw_planet(pointer + n);
		}
	}
	merge_layers();
}

// Очистка слоя draw
void display::clear_draw() {
	draw = NULL;
}