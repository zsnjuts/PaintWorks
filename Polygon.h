#ifndef POLYGON_H
#define POLYGON_H

#include "Line.h"
#include "Area.h"
#include "CompFigure.h"
#include <vector>
using namespace std;

class MyPolygon:public CompFigure, public Area
{
public:
	MyPolygon();
	MyPolygon(const vector<Line*> &initLines);

	void draw(); //轮廓+填充
	void clear(); //清空轮廓点+清空填充点

	void fillColor();

	//MyPolygon与其他Figure类不同，MyPolygon在绘制完成时才最终确定，所以无法将计算各点与绘制分离开
private:
	vector<Point*> vertexes;
	vector<Line*> lines;
};

#endif // !POLYGON_H

