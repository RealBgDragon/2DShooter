#pragma once
class Projectile
{
public:
	Projectile();
	~Projectile();

	void init(int xpos, int ypos, int size, int max_x, int max_y, char direction, int speed);

	void draw();

	int getX() { return xpos; }
	int getY() { return ypos; }

	void move();

private:
	int xpos;
	int ypos;
	int size;
	int color;
	int max_x;
	int max_y;
	int speed;
	char direction;
};

