#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "mlineedit.h"
#include "myhelper.h"
#include "myapp.h"
#include "unit.h"
#include "animationstackedwidget.h"
#include "clientsocket.h"
#include "mainwindow.h"

#include <QFile>
#include <QJsonObject>
#include <QMessageBox>
#include <QTime>
LoginWidget::LoginWidget(QWidget *parent) :
    CustomMoveWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    //初始化Ui界面
    initGlobal();
    //初始化Socket
    initSocket();

    //设置当前页面为登陆页
    ui->stackedWidget->setCurrentIndex(AnimationStackedWidget::LoginPageIndex);

    //设置IP地址
    ui->lineEditHostAddr->setIP("127.0.0.1");

    //为user和passwd输入框设置Icon
    ui->lineEditUser->setIcon(":/common/resource/common/ic_user.png");
    ui->lineEditPasswd->setIcon(":/common/resource/common/ic_lock.png");

}

LoginWidget::~LoginWidget()
{
    delete ui;
}

//初始化全局
void LoginWidget::initGlobal(){
    //设置全局样式表
    MyHelper::setStyle(":/qss/resource/qss/default.css");
    //设置app图标
    MyHelper::setAppIcon(":/background/resource/background/app.png");
}

//初始化Socket
void LoginWidget::initSocket(){
    ui->labelWinTitle->setText("未连接服务器");//连接前初始化winTiltle
    loginSocket = new ClientSocket;
    loginSocket->checkTcpConnect(MyApp::m_strHostAddr,MyApp::m_nMsgPort);//连接tcp
    connect(loginSocket,SIGNAL(signalMessageStatus(MessageStatus)),this,SLOT(onMessageStatus(MessageStatus)));//消息状态信号槽
    connect(loginSocket,SIGNAL(signalMessageType(MessageType)),this,SLOT(onMessageType(MessageType,QJsonValue)));//消息类型信号槽
}

//点击从登陆界面旋转到IP设置界面
void LoginWidget::on_btnWinMenu_clicked()
{
    ui->stackedWidget->setStartVal(ROTATESTART);
    ui->stackedWidget->setEndVal(ROTATEEND);
    ui->stackedWidget->animation(AnimationStackedWidget::IpPageIndex);
}

//点击从IP设置界面旋转到登陆界面
void LoginWidget::on_btnCancel_clicked()
{
    ui->stackedWidget->setStartVal(ROTATESTART);
    ui->stackedWidget->setEndVal(-1*ROTATEEND);
    ui->stackedWidget->animation(AnimationStackedWidget::LoginPageIndex);
}


//消息状态槽函数
void LoginWidget::onMessageStatus(const MessageStatus &status)
{
//    MessageStatus statusType = static_cast<MessageStatus>(type);
    switch(status){
    case MessageStatus::ConnectedHost://连接服务器成功
    {
        ui->labelWinTitle->setText("成功连接服务器");
    }
    break;
    case MessageStatus::LoginPasswdError://用户名或密码错误
    {
        QMessageBox::warning(this,"警告","用户名或密码错误");
    }
    break;
    case MessageStatus::LoginRepeat:{//用户已登陆登录
        QMessageBox::warning(this,"警告","用户已登陆");
    }
    break;
    case MessageStatus::LoginSuccess://登陆成功
    {
        this->close();//释放 loginWidget
        //跳转mainwindow
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
    }
    break;
    default:
        break;
    }
}

//点击登陆按钮
void LoginWidget::on_btnLogin_clicked()
{
    QJsonObject json;
    json.insert("name",ui->lineEditUser->text());
    json.insert("passwd",ui->lineEditPasswd->text());
    loginSocket->tcpSendMessage(MessageType::Login,json);
}

