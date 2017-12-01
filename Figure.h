#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"

//Figure为所有图形的基类，只提供接口，不提供实现
class Figure
{
public:
	virtual void draw()=0; //绘制图形本身
	virtual void markDraw()=0; //绘制除draw以外的标记：标记点(+矩形框)
	virtual void clear()=0; //清除图形中的点并释放空间

	virtual void translate(const Point &offset)=0; //平移

};

#endif // !FIGURE_H

