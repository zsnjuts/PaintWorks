#ifndef POLYGON_H
#define POLYGON_H

#include "Line.h"
#include "Area.h"
#include "Figure.h"
#include <vector>
using namespace std;

class MyPolygon:public Figure, public Area
{
public:
	MyPolygon();
	MyPolygon(const vector<Line*> &initLines);
	~MyPolygon();

	vector<Point> getVertexes() const;
	Point getCenter() const;
	void setVertex(int idx, const Point &p); //设置索引为idx的顶点位置

	void translate(const Point &offset); //平移
	void rotate(double angle); //旋转
	void scale(double s); //缩放

	void draw(); //轮廓+填充
	void clear(); //清空轮廓点+清空填充点
	void markDraw(); //绘制除draw以外的标记：矩形框+标记点
	void fillColor();

private:
	vector<Point*> vertexes;
	vector<Line*> lines;
};

#endif // !POLYGON_H

