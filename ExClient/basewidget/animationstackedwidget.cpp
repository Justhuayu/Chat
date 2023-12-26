#include "animationstackedwidget.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QDebug>
AnimationStackedWidget::AnimationStackedWidget(QWidget *parent)
    :QStackedWidget(parent)
{
    m_nextPageIndex = 0 ;//旋转后页面索引
    is_animating = false;//旋转锁
}

AnimationStackedWidget::~AnimationStackedWidget(){


}

//绘制旋转时每一帧
void AnimationStackedWidget::paintEvent(QPaintEvent *event){
    if(is_animating){
        QPainter p(this);
        if(m_rotate > 0 && m_rotate <= 90){
            //设置当前页面大小画布
            QPixmap pixmap(currentWidget()->size());
            //渲染当前页面内容到pixmap上
            currentWidget()->render(&pixmap);
            //旋转
            QTransform transform;
            //设置旋转点
            transform.translate(width()/2,0);
            //绕Y轴旋转m_rotate度
            transform.rotate(m_rotate,Qt::YAxis);
            //painter绘制旋转页面
            p.setTransform(transform);
            p.drawPixmap(-1*width()/2,0,pixmap);
        }else if(m_rotate > 90 && m_rotate <= 180){
            //设置下一页页面大小画布
            QPixmap pixmap(widget(m_nextPageIndex)->size());
            //渲染下一页内容到pixmap上
            widget(m_nextPageIndex)->render(&pixmap);
            //旋转
            QTransform transform;
            //设置旋转点
            transform.translate(width()/2,0);
            //绕Y轴旋转m_rotate度
            transform.rotate(180+m_rotate,Qt::YAxis);
            //painter绘制旋转页面
            p.setTransform(transform);
            p.drawPixmap(-1*width()/2,0,pixmap);
        }else if(m_rotate < 0 && m_rotate >= -90){
            //设置当前页面大小画布
            QPixmap pixmap(currentWidget()->size());
            //渲染当前页面内容到pixmap上
            currentWidget()->render(&pixmap);
            //旋转
            QTransform transform;
            //设置旋转点
            transform.translate(width()/2,0);
            //绕Y轴旋转m_rotate度
            transform.rotate(m_rotate,Qt::YAxis);
            //painter绘制旋转页面
            p.setTransform(transform);
            p.drawPixmap(-1*width()/2,0,pixmap);

        }else if(m_rotate < -90 && m_rotate >= -180){
            //设置下一页页面大小画布
            QPixmap pixmap(widget(m_nextPageIndex)->size());
            //渲染下一页内容到pixmap上
            widget(m_nextPageIndex)->render(&pixmap);

            //旋转
            QTransform transform;
            //设置旋转点
            transform.translate(width()/2,0);
            //绕Y轴旋转m_rotate度
            transform.rotate(m_rotate+180,Qt::YAxis);
            //painter绘制旋转页面
            p.setTransform(transform);
            p.drawPixmap(-1*width()/2,0,pixmap);
        }

    }else{
        QWidget::paintEvent(event);
    }
}

//旋转动画
//nextPageIndex 0 or 1 旋转完成时界面索引
void AnimationStackedWidget::animation(int nextPageIndex){
    if(is_animating){
        return;
    }
    m_nextPageIndex = nextPageIndex;

    //设置旋转完后页面尺寸
    int offsetX = frameRect().width();
    int offsetY = frameRect().height();
    widget(nextPageIndex)->setGeometry(0,0,offsetX,offsetY);

    QPropertyAnimation *animation = new QPropertyAnimation(this,"rotate");
    animation->setDuration(700);//设置动画时间
    animation->setStartValue(m_startVal);//设置开始值
    animation->setEasingCurve(QEasingCurve::Linear);//设置动画曲线
    animation->setEndValue(m_endVal);//设置结束值
    //动画值改变时信号槽
    connect(animation,SIGNAL(valueChanged(QVariant)),this,SLOT(onAnimationChanged()));
    //动画完成时信号槽
    connect(animation,SIGNAL(finished()),this,SLOT(onAnimationFinished()));

    currentWidget()->hide();
    is_animating = true;
    animation->start();
}
//动画值改变
void AnimationStackedWidget::onAnimationChanged(){
    this->repaint();//重画当前帧，运行paintEvent函数
}

//动画完成时
void AnimationStackedWidget::onAnimationFinished(){
    is_animating = false;

    //设置当前页面
    widget(m_nextPageIndex)->show();
    widget(m_nextPageIndex)->raise();

    setCurrentWidget(widget(m_nextPageIndex));
    repaint();
}

