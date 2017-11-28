#ifndef FIGURE_H
#define FIGURE_H

//Figure为所有图形的基类，只提供接口，不提供实现
class Figure
{
public:
	virtual void draw()=0;
//	virtual void markDraw()=0;
	virtual void clear()=0;

};

#endif // !FIGURE_H

