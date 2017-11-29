#ifndef POINT_H
#define POINT_H

#include <tuple>
#include <iostream>
using namespace std;

class Point
{
public:
	Point();
	Point(int x, int y);
	~Point();

	int getX() const;
	int getY() const;
	int distanceTo(const Point &p) const;

	void draw(); //需要结合glBegin()和glEnd()使用
	void markDraw(); //被选中的状态
//	void clear(); //暂无用处

	void setPoint(int x, int y);
	bool operator<(const Point &p) const;
	bool operator==(const Point &p) const;
	friend ostream& operator<<(ostream &out, const Point &p); //输出(x,y)坐标
	//Point operator+(const Point &p) const;

private:
	int x; //gl与glut横坐标相同
	int y; //glY,以gl坐标系为准，y轴原点在左下角
};

#endif // !POINT_H
