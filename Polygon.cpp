#include "Polygon.h"
#include <list>
#include <cassert>
#include <algorithm>
#include <functional>

MyPolygon::MyPolygon()
{
}

MyPolygon::MyPolygon(const vector<Line*> &initLines):lines(initLines)
{
	for (Line *line : initLines) //line的起始点与vertex一一对应
		vertexes.push_back(line->getBeginPoint());
	calculateCenter();
	calculateHandle();
}

MyPolygon::~MyPolygon()
{
	for(Point *p : fillPoints)
		delete p;
	for(Line *line : lines)
		delete line;
}

vector<Point> MyPolygon::getVertexes() const
{
	return vertexes;
}

Point MyPolygon::getCenter() const
{
	return center;
}

Point MyPolygon::getHandlePoint() const
{
	return handle;
}

void MyPolygon::setVertex(int idx, const Point &p)
{
	assert(idx>=0 && idx<vertexes.size());
	vertexes[idx].setPoint(p.getX(), p.getY());
	lines[(idx-1+vertexes.size())%vertexes.size()]->setEndPoint(p);
	lines[idx]->setBeginPoint(p);
	if(!fillPoints.empty())
	{
		Area::clearColor();
		MyPolygon::fillColor();
	}
	calculateCenter();
	calculateHandle();
}

void MyPolygon::setHandlePointByRef(const Point &ref)
{
	double a = handle.getX()-center.getX(), b = handle.getY()-center.getY();
	double c = ref.getX()-center.getX(), d = ref.getY()-center.getY();
	double angle = 180/3.14159265*acos((a*c+b*d)/sqrt((a*a+b*b)*(c*c+d*d)));
	if(b*c>a*d) //逆时针旋转，角度取负
		angle = -angle;
	for(Point &p:vertexes)
		p.rotate(center, angle);
	for(int i=0;i<lines.size();i++)
		lines[i]->setLine(vertexes[i], vertexes[(i+1)%lines.size()]);
	if(!fillPoints.empty())
	{
		Area::clearColor();
		MyPolygon::fillColor();
	}
	handle.rotateToParallel(center, ref, h);
}

void MyPolygon::translate(const Point &offset)
{
	for(Point &p:vertexes)
		p.translate(offset);
	for(Line *line:lines)
		line->translate(offset);
	for(Point *p:fillPoints)
		p->translate(offset);
	calculateCenter();
	calculateHandle();
}

void MyPolygon::rotate(double angle)
{
	for(Point &p:vertexes)
		p.rotate(center, angle);
	for(int i=0;i<lines.size();i++)
		lines[i]->setLine(vertexes[i], vertexes[(i+1)%lines.size()]);
	if(!fillPoints.empty())
	{
		Area::clearColor();
		MyPolygon::fillColor();
	}
}

void MyPolygon::scale(double s)
{
	for(Point &p:vertexes)
		p.scale(center, s, s);
	for(int i=0;i<lines.size();i++)
		lines[i]->setLine(vertexes[i], vertexes[(i+1)%lines.size()]);
	if(!fillPoints.empty())
	{
		Area::clearColor();
		MyPolygon::fillColor();
	}
	calculateHandle();
}

bool MyPolygon::cut(const Point &leftDown, int width, int height)
{
	vector<function<bool(const Point &)>> isOutside; //四条边的判断函数，返回是否在外侧
	isOutside.push_back([leftDown](const Point &p)->bool{ return p.getX()<leftDown.getX(); }); //裁剪窗口左侧
	isOutside.push_back([leftDown, width](const Point &p)->bool{ return p.getX()>leftDown.getX()+width; }); //裁剪窗口右侧
	isOutside.push_back([leftDown](const Point &p)->bool{ return p.getY()<leftDown.getY(); }); //裁剪窗口下侧
	isOutside.push_back([leftDown, height](const Point &p)->bool{ return p.getY()>leftDown.getY()+height; }); //裁剪窗口上侧

	vector<function<Point(const Line *)>> intersect; //返回裁剪窗口四条边与多边形直线的交点
	intersect.push_back([leftDown](const Line *line)->Point{ return line->intersectWithX(leftDown.getX()); }); //与裁剪左边界交点
	intersect.push_back([leftDown, width](const Line *line)->Point{ return line->intersectWithX(leftDown.getX()+width); }); //与裁剪右边界交点
	intersect.push_back([leftDown](const Line *line)->Point{ return line->intersectWithY(leftDown.getY()); }); //与裁剪下边界交点
	intersect.push_back([leftDown, height](const Line *line)->Point{ return line->intersectWithY(leftDown.getY()+height); }); //与裁剪上边界交点

	//用四条边界线分别裁剪
	for(int f=0;f<4;f++)
	{
		vector<Point> vtxs; //本次裁剪得到的新顶点表
		for(int i=0;i<vertexes.size();i++)
		{
			if(isOutside[f](vertexes[i])) //i在外侧
			{
				if(isOutside[f](vertexes[(i+1)%vertexes.size()])) //i+1在外侧
					continue;
				else //i在外侧，i+1在内侧
				{
					vtxs.push_back(intersect[f](lines[i]));
					vtxs.push_back(vertexes[(i+1)%vertexes.size()]);
				}
			}
			else //i在内侧
			{
				if(isOutside[f](vertexes[(i+1)%vertexes.size()])) //i+1在外侧
					vtxs.push_back(intersect[f](lines[i]));
				else //i+1在内侧
					vtxs.push_back(vertexes[(i+1)%vertexes.size()]);
			}
		}
		vertexes = vtxs;
		for(Line *line:lines)
			delete line;
		lines.clear();
		for(int i=0;i<vtxs.size();i++)
			lines.push_back(new Line(vertexes[i], vertexes[(i+1)%vertexes.size()]));
	}
	if(lines.empty())
		return false;
	else
	{
		calculateCenter();
		calculateHandle();
		if(!fillPoints.empty())
		{
			Area::clearColor();
			MyPolygon::fillColor();
		}
		return true;
	}
}

bool MyPolygon::isOn(const Point &p)
{
	for(Line *line:lines)
		if(line->isOn(p))
			return true;
	if(!fillPoints.empty())
	{
		for(Point *pt:fillPoints)
			if(*pt==p)
				return true;
	}
	return false;
}

void MyPolygon::draw()
{
	for(Line *line : lines)
		line->draw();
	Area::fillColor();
}

void MyPolygon::clear()
{	
	Area::clearColor();
	vertexes.erase(vertexes.begin(), vertexes.end());
	for(Line *line : lines)
		delete line;
	lines.erase(lines.begin(), lines.end());
}

void MyPolygon::markDraw()
{
	int minX = vertexes[0].getX();
	int maxX = vertexes[0].getX();
	int minY = vertexes[0].getY();
	int maxY = vertexes[0].getY();
	for(Point v:vertexes)
	{
		minX = min(minX, v.getX());
		maxX = max(maxX, v.getX());
		minY = min(minY, v.getY());
		maxY = max(maxY, v.getY());
	}
	vector<Point> markPoints;
	markPoints.push_back(Point(minX, minY));
	markPoints.push_back(Point(minX, maxY));
	markPoints.push_back(Point(maxX, maxY));
	markPoints.push_back(Point(maxX, minY));
	Area::drawRect(markPoints[0], markPoints[1], markPoints[2], markPoints[3]);
	for(Point p:vertexes)
		p.markDraw();
//	markPoints.push_back(Point((minX+maxX)/2, (minY+maxY)/2)); //矩形中心点
//	markPoints.back().centerMarkDraw();
	center.centerMarkDraw();
	handle.handleDraw(center);
}

struct Edge
{
	Edge() {}
	Edge(double xi, double dx, int ymax)
	{
		this->xi = xi;
		this->dx = dx;
		this->ymax = ymax;
	}
	double xi;
	double dx;
	int ymax;
};

void MyPolygon::fillColor()
{
	int minGlY = vertexes[0].getY();
	int maxGlY = vertexes[0].getY();
	for (Point v : vertexes)
	{
		minGlY = min(minGlY, v.getY());
		maxGlY = max(maxGlY, v.getY());
	}

	//此算法依赖于：各直线根据绘制顺序排列，且首尾相接（即lines[i]的尾点=lines[i+1]的起点）
	//依赖来源：adjBegin与adjEnd的计算
	//考虑了水平线及左右侧顶点的问题
	vector<vector<Edge>> net(maxGlY - minGlY + 1); //有序边表
	for (int i=0;i<lines.size();i++)
		if (lines[i]->getBeginPoint().getY() != lines[i]->getEndPoint().getY()) //不考虑水平线
		{
			Point adjBegin(lines[(i - 1 + lines.size()) % lines.size()]->getBeginPoint()); //起点另一侧的邻点
			Point begin(lines[i]->getBeginPoint());
			Point end(lines[i]->getEndPoint());
			Point adjEnd(lines[(i + 1) % lines.size()]->getEndPoint()); //终点另一侧的邻点

			Edge e;
			e.dx = double(end.getX() - begin.getX()) / double(end.getY() - begin.getY());
			if (begin.getY() < end.getY()) //begin在下方
			{
				e.xi = begin.getX(); 
				if (end.getY() <= adjEnd.getY()) //begin<end<adjEnd：end为左右侧的点，从下往上绘制到交点下面的位置，即[down,up)，保留下面的点，不保留上面的点
					e.ymax = end.getY() - 1;
				else //begin<end, adjEnd<end：end为上下侧的点，绘制到顶即可，即[down,up]
					e.ymax = end.getY();
				net[begin.getY() - minGlY].push_back(e);
			}
			else //end在下方
			{
				e.xi = end.getX();
				if (begin.getY() <= adjBegin.getY()) //end<begin<adjBegin：begin为左右侧的点，从下往上绘制到交点，即[down,up)
					e.ymax = begin.getY() - 1;
				else //end<begin, adjBegin<begin：begin为上下侧的点，绘制到顶即可，即[down,up]
					e.ymax = begin.getY();
				net[end.getY() - minGlY].push_back(e);
			}
		}

	vector<vector<Edge>> aet(maxGlY - minGlY + 1); //活化边表
	for (int i = minGlY; i <= maxGlY; i++) //使用有序边表填活化边表
	{
		for (int j = minGlY; j <= i; j++)
			for (Edge e : net[j - minGlY])
				if (e.ymax >= i)
					aet[i - minGlY].push_back(Edge(e.xi + (i - j)*e.dx, e.dx, e.ymax));
		sort(aet[i - minGlY].begin(), aet[i - minGlY].end(), [](Edge x, Edge y)->bool {return x.xi < y.xi; });
	}

	vector<vector<pair<Point*, Point*>>> outline(maxGlY - minGlY + 1); //各行填充范围
	for (int i = 0; i < aet.size(); i++)
		for (vector<Edge>::iterator e = aet[i].begin(); e != aet[i].end() && e + 1 != aet[i].end(); e+=2)
			outline[i].push_back(
				make_pair(new Point((int)(e->xi + 0.5), i + minGlY),
					new Point(int((e + 1)->xi + 0.5), i + minGlY)));

	for (vector<pair<Point*, Point*> > line : outline)
		for (pair<Point*, Point*> pr : line)
			for (int i = pr.first->getX() + 1; i < pr.second->getX(); i++)
				fillPoints.push_back(new Point(i, pr.first->getY()));
}

const int MyPolygon::h = 30; //handle长度
void MyPolygon::calculateHandle()
{
	int minX = vertexes[0].getX();
	int maxX = vertexes[0].getX();
	int minY = vertexes[0].getY();
	int maxY = vertexes[0].getY();
	for(Point v:vertexes)
	{
		minX = min(minX, v.getX());
		maxX = max(maxX, v.getX());
		minY = min(minY, v.getY());
		maxY = max(maxY, v.getY());
	}
	int rx = (maxX-minX)/2, ry = (maxY-minY)/2;
	double tmp = sqrt(rx*rx+ry*ry);
	handle.setPoint(minX+rx+int(h*rx/tmp+0.5), minY+ry+int(h*ry/tmp+0.5));
}

void MyPolygon::calculateCenter()
{
	int minX = vertexes[0].getX();
	int maxX = vertexes[0].getX();
	int minY = vertexes[0].getY();
	int maxY = vertexes[0].getY();
	for(Point v:vertexes)
	{
		minX = min(minX, v.getX());
		maxX = max(maxX, v.getX());
		minY = min(minY, v.getY());
		maxY = max(maxY, v.getY());
	}
	int rx = (maxX-minX)/2, ry = (maxY-minY)/2;
	center.setPoint(minX+rx, minY+ry);
}
