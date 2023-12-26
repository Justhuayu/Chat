#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#define ROTATESTART 0//旋转开始值
#define ROTATEEND 180//旋转结束值
#include "customwidget.h"

#include <QWidget>

/*
    登陆界面相关
*/
enum class MessageStatus;
enum class MessageType;
class AnimationStackedWidget;
class ClientSocket;

namespace Ui {
class LoginWidget;
}

class LoginWidget : public CustomMoveWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_btnWinMenu_clicked();//设置ip按钮
    void on_btnCancel_clicked();//取消IP设置按钮
    void on_btnLogin_clicked();//登陆按钮

    void onMessageStatus(const MessageStatus &status);//消息状态槽函数

private:
    Ui::LoginWidget *ui;
    AnimationStackedWidget *animation;
    ClientSocket *loginSocket;

    void initGlobal();//初始化全局
    void initSocket();//初始化socket
};

#endif // LOGINWIDGET_H
