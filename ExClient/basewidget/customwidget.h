#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

/*
    一些自定义的widget
*/

#include <QWidget>
class QPoint;
class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);


signals:

};

/*
    可移动窗口的 widget
*/


//重写事件mousePressEvent、mouseReleaseEvent、mouseMoveEvent
class CustomMoveWidget:public CustomWidget{

public:
    explicit CustomMoveWidget(QWidget *parent = 0);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);//鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放事件
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件

private:
    bool leftMouseIsPress;//鼠标左键是否按下
    QPoint mousePoint;//鼠标相对窗口坐标
};

#endif // CUSTOMWIDGET_H
