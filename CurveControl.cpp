#include "CurveControl.h"

CurveControl::CurveControl()
{
	curIdx = -1;
}

CurveControl::CurveControl(std::vector<Figure *> *figures):FigureControl(figures)
{
	curIdx = -1;
}

CurveControl::CurveControl(int width, int height):FigureControl(width,height)
{
	curIdx = -1;
}

CurveControl::~CurveControl()
{
	for(Curve *curve:curves)
		delete curve;
}

bool CurveControl::setFocus(Figure *fg)
{
	for(int i=0;i<curves.size();i++)
		if(curves[i]==fg)
		{
			curIdx = i;
			return true;
		}
	return false;
}

void CurveControl::onMousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		Point curPoint(event->x(), height-event->y());
		if(!curVtxs.empty()) //正在绘制
		{
			if(curVtxs.size()==3) //最后一个点
			{
				curVtxs.push_back(curPoint);
				curves.push_back(new Curve(curVtxs));
				curIdx = curves.size()-1;
				allFigures->push_back(curves.back());
				curVtxs.clear();
				return;
			}
			else if(curVtxs.size()<3)
			{
				curVtxs.push_back(curPoint);
				return;
			}
		}
		else if(curVtxs.empty() && !curves.empty()) //选中控制点或曲线本身：编辑curves[curIdx]
		{
			//TODO:检查顶点
			vector<Point> vtxs = curves[curIdx]->getVertices();
			for(int i=0;i<vtxs.size();i++)
				if(curPoint.distanceTo(vtxs[i])<=5)
				{
					setCV = i;
					pushForward(curves[curIdx]);
					return;
				}
			if(curPoint.distanceTo(curves[curIdx]->getCenter())<=5)
			{
				setCV = -2;
				pushForward(curves[curIdx]);
				return;
			}
			else if(curPoint.distanceTo(curves[curIdx]->getHandle())<=5)
			{
				setCV = -3;
				pushForward(curves[curIdx]);
				return;
			}
			else if(curves[curIdx]->isOn(curPoint))
			{
				pushForward(curves[curIdx]);
				return;
			}
		}
		//未选中任何点，新建曲线
		curVtxs.push_back(curPoint);
		setCV = -1;
	}
}

void CurveControl::onMouseMoveEvent(QMouseEvent *event)
{
	if(!curves.empty())
	{
		Point curPoint(event->x(), height-event->y());
		if(setCV>=0)
			curves[curIdx]->setVertex(setCV, curPoint);
		else if(setCV==-2)
			curves[curIdx]->translate(curPoint - curves[curIdx]->getCenter());
		else if(setCV==-3)
			curves[curIdx]->setHandlePointByRef(curPoint);
	}
}

void CurveControl::onDraw()
{
	for(Point &v:curVtxs)
		v.draw();
	for(Curve *curve:curves)
		curve->draw();
}

void CurveControl::onMarkDraw()
{
	if(!curVtxs.empty())
	{
		for(Point &p:curVtxs)
			p.markDraw();
	}
	else if(curIdx>=0)
	{
		curves[curIdx]->markDraw();
	}
}

void CurveControl::onScale(double s)
{
	if(curIdx>=0)
		curves[curIdx]->scale(s);
}

void CurveControl::onDelete()
{
	if(curIdx<0)
		return;
	deleteCurve(curIdx);
	curIdx = -1;
}

void CurveControl::onClear()
{
	for(Curve *curve:curves)
	{
		for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();)
		{
			if(curve==*it)
				it = allFigures->erase(it);
			else
				it++;
		}
		delete curve;
	}
	curves.clear();
	curIdx = -1;
}

void CurveControl::deleteCurve(int idx)
{
	if(idx<0)
		return;
	curves.erase(curves.begin()+idx);
	for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();it++)
		if(*it==curves[idx])
		{
			allFigures->erase(it);
			break;
		}
	delete curves[idx];
}

