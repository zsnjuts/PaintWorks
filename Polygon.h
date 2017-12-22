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
	Point getHandlePoint() const;
	void setVertex(int idx, const Point &p); //设置索引为idx的顶点位置
	void setHandlePointByRef(const Point &ref); //ref(参考点)为当前鼠标位置，只需设置handle点，center点与ref点共线即可

	void translate(const Point &offset); //平移
	void rotate(double angle); //绕center旋转
	void scale(double s); //缩放

	bool cut(const Point &leftDown, int width, int height); //根据矩形窗口裁剪，若不在窗口中则返回false
	bool isOn(const Point &p);

	void draw(); //轮廓+填充
	void clear(); //清空轮廓点+清空填充点
	void markDraw(); //绘制除draw以外的标记：矩形框+标记点
	void fillColor();

private:
	vector<Point> vertexes;
	vector<Line*> lines;

	//下面参数为handle相关，在calculateHandle()函数中更新，其中center也会在其他地方用到
	Point center; //矩形中心点
	Point handle; //handle点
	const static int h; //handle长度，初始化为30
	void calculateHandle(); //非旋转操作后更新handle
	void calculateCenter(); //非旋转操作后更新center
};

#endif // !POLYGON_H

