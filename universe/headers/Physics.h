#pragma once
std::default_random_engine generator(time(NULL));
int randint_gen(int a, int b)
{
	std::uniform_int_distribution<int> distribution(a, b);
	Sleep(1);
	return distribution(generator);
}
int randdouble_gen(double a, double b)
{
	//std::uniform_int_distribution<double> distribution(a, b);
	std::uniform_real_distribution<double> distribution(a, b);
	Sleep(1);
	return distribution(generator);
}


class CreatePlanet
{
public:
	bool life = true;
	double mass = 1;
	double radius = 1;
	double c_x = 0;
	double c_y = 0;
	double v_x = 0;
	double v_y = 0;
	void SetParametrs(double m, int r, double vx, double vy, double cx, double cy)
	{
		mass = m;
		radius = r;
		v_x = vx;
		v_y = vy;
		c_x = cx;
		c_y = cy;
	}
	CreatePlanet()
	{
		mass = randdouble_gen(100, 400);
		radius = randdouble_gen(5, 20);
		c_x = randint_gen(22, 1254);
		c_y = randint_gen(22, 700);
		v_x = randint_gen(-100, 100);
		v_y = randint_gen(-100, 100);
	}
};

class Physics
{
public:
	double simulation_step_delay = 1;
	double gravity_constant = 65;
	bool enable_collapses = true;
	void step(CreatePlanet* pointer, int NBR);
};
	
// Обработка физики
void Physics::step(CreatePlanet* pointer, int NBR)
{
	for (int i = 0; i < NBR; i++)//Планета для которой считается сумма сил и новая скорость
	{
		CreatePlanet& star1 = *(pointer+i);
		double r = 0;
		double Accel_y = 0;
		double Accel_x = 0;

		for (int j = 0; j < NBR; j++)//Сумматор всех сил, которые действуют на планету со стороны других планет
		{
			CreatePlanet& star2 = *(pointer + j);
			if ((j != i) && (star1.life == true) && (star2.life == true))//Исключение самосилы
			{
				r = sqrt(pow((star2.c_x - star1.c_x), 2) + pow((star2.c_y - star1.c_y), 2));//Расстояние между взаимодействующими планетами
				Accel_x = Accel_x + gravity_constant * star2.mass * (star2.c_x - star1.c_x) / pow(r, 3);//Счетчик силы по х
				Accel_y = Accel_y + gravity_constant * star2.mass * (star2.c_y - star1.c_y) / pow(r, 3);//Счетчик силы по y

				//Обработчик столкновений
				if (enable_collapses && (r < star1.radius + star2.radius))
				{
					Accel_x = 0;
					Accel_y = 0;

					//Скорость новой планеты исходя из суммы импульсов
					star1.v_x = ((star1.v_x * star1.mass + star2.v_x * star2.mass) / (star1.mass + star2.mass));
					star1.v_y = ((star1.v_y * star1.mass + star2.v_y * star2.mass) / (star1.mass + star2.mass));

					//Новая координата в центре масс столкнувшихся
					star1.c_x = ((star1.c_x * star1.mass + star2.c_x * star2.mass) / (star1.mass + star2.mass));
					star1.c_y = ((star1.c_y * star1.mass + star2.c_y * star2.mass) / (star1.mass + star2.mass));

					star1.mass = star1.mass + star2.mass;//Новая масса
					star1.radius = pow(pow(star1.radius, 3) + pow(star2.radius, 3), 1.0/3.0);//Новый объёмный радиус
					star2.life = false;//Уничтожение планеты
				}
			}

		}

		star1.v_x = star1.v_x + Accel_x*simulation_step_delay;
		star1.v_y = star1.v_y + Accel_y* simulation_step_delay;
		star1.c_x = star1.c_x + star1.v_x* simulation_step_delay;
		star1.c_y = star1.c_y + star1.v_y* simulation_step_delay;
	}
}