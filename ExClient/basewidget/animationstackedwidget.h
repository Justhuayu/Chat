#ifndef ANIMATIONSTACKEDWIDGET_H
#define ANIMATIONSTACKEDWIDGET_H

#include <QStackedWidget>

/*
    Stacked 动画
*/

class AnimationStackedWidget : public QStackedWidget
{
    Q_OBJECT
    //使用属性进行旋转 QPropertyAnimation
    Q_PROPERTY(int rotate READ getRotate WRITE setRotate NOTIFY rotateChanged FINAL)
public:
    explicit AnimationStackedWidget(QWidget *parent = nullptr);
    ~AnimationStackedWidget();
    enum{LoginPageIndex=0,IpPageIndex=1};

    void animation(int nextPageIndex);//旋转动画

    int getRotate(){
        return m_rotate;
    }

    void setRotate(int val){
        m_rotate = val;
    }

    int getStartVal(){
        return m_startVal;
    }

    void setStartVal(int val){
        m_startVal = val;
    }

    int getEndVal(){
        return m_endVal;
    }

    void setEndVal(int val){
        m_endVal = val;
    }

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void rotateChanged();//rotate值改变时发射信号
private slots:
    void onAnimationChanged();//动画值改变
    void onAnimationFinished();//动画完成时
private:
    int m_rotate;//旋转的角度
    int m_startVal;//旋转开始角度
    int m_endVal;//旋转结束角度

    int m_nextPageIndex ;//旋转后页面索引
    bool is_animating;//旋转锁
};

#endif // ANIMATIONSTACKEDWIDGET_H
