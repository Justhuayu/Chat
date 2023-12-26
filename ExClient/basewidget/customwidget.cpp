#include "customwidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QMouseEvent>
CustomWidget::CustomWidget(QWidget *parent)
    : QWidget(parent)
{

}

//可移动窗口
CustomMoveWidget::CustomMoveWidget(QWidget *parent)
    :CustomWidget(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);//窗口无边框
    this->setAttribute(Qt::WA_TranslucentBackground);//透明化
    leftMouseIsPress =false;
}

//鼠标移动，移动窗口
void CustomMoveWidget::mouseMoveEvent(QMouseEvent *event){
    if(leftMouseIsPress && (event->buttons() & Qt::LeftButton)){//按压键判断 event->buttons() & Qt::LeftButton
        this->move(event->globalPos() - mousePoint);//global  - 相对位置 = 左上角窗口应该在的位置
        event->accept();
    }
}

//鼠标左键按下，记录窗口坐上角位置
void CustomMoveWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        leftMouseIsPress = true;
        mousePoint = event->pos();//保存当前鼠标相对窗口左上角位置
        event->accept();
    }
}

//鼠标释放
void CustomMoveWidget::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    leftMouseIsPress = false;
}





