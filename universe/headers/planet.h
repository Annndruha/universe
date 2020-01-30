#pragma once

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