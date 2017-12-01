# PaintWorks

## 已实现的功能

* 直线绘制
* 圆的绘制+填充
* 椭圆绘制
* 多边形绘制+填充
* 已实现基础的UI交互，切换图形绘制模式
* 已实现markDraw，为各Figure提供被选中的虚线矩形框显示
* 已实现**图形编辑**

## 下一步工作

* **图形变换**
  * 平移
  * 旋转
  * 缩放
* **图形裁剪**


## 目前进展

已实现各图形的平移（通过点的平移实现）

已实现各图形的旋转（其中圆的旋转保持不变，椭圆旋转只能转90度）

## 有待改进的bug

* 标签页关闭之后切换图形绘制模式会导致程序崩溃

  应该让QMdiSubWindow在关闭时delete掉GLWidget，可能需要重写QMdiSubWindow的` virtual void	closeEvent(QCloseEvent * closeEvent)` 函数，最好是将相关信号关联到Mainwindow的一个槽函数，省得再写QMdiSubWindow了。