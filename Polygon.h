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

	void draw(); //轮廓+填充
	void clear(); //清空轮廓点+清空填充点
	void markDraw(); //绘制除draw以外的标记：矩形框+标记点

	void fillColor();

	//MyPolygon与其他Figure类不同，MyPolygon在绘制完成时才最终确定，所以无法将计算各点与绘制分离开
private:
	vector<Point*> vertexes;
	vector<Line*> lines;
};

#endif // !POLYGON_H

