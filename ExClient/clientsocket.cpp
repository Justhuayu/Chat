#include "clientsocket.h"
#include "unit.h"
#include "myapp.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

ClientSocket::ClientSocket(QObject *parent)
    : QObject{parent}
{
    m_nid = -1;
    m_tcpSocket = new QTcpSocket;

    connect(m_tcpSocket,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(m_tcpSocket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}
void ClientSocket::setId(const int &id){
    m_nid = id;
}

//tcp连接
void ClientSocket::onConnected()
{
    qDebug()<<"has connected";
    emit signalMessageStatus(MessageStatus::ConnectedHost);//tcp连接成功信号
}
//tcp断开
void ClientSocket::onDisconnected()
{
    m_tcpSocket->abort();//硬断开tcp所有连接
}


//检测Tcp是否连接，未连接则连接
void ClientSocket::checkTcpConnect(QString hostAddress,int port)
{
    if(m_tcpSocket->state() != QTcpSocket::ConnectedState){
        m_tcpSocket->connectToHost(hostAddress,port);
    }
}

//tcp发送信息
void ClientSocket::tcpSendMessage(const MessageType &type,const QJsonValue &dataValue)
{
    //连接服务器
    if(!m_tcpSocket->isOpen()){
        m_tcpSocket->connectToHost(MyApp::m_strHostAddr,MyApp::m_nMsgPort);
        m_tcpSocket->waitForConnected(1000);
    }
    //超时未连接
    if(m_tcpSocket->state() != QTcpSocket::ConnectedState){
        qDebug()<<"发送消息失败，连接服务器失败";
        qDebug()<<static_cast<quint8>(type)<<dataValue;
        return;
    }
    //创建 Json 对象
    QJsonObject jsonObject;
    jsonObject.insert("from",m_nid);
    jsonObject.insert("type",static_cast<quint8>(type));
    jsonObject.insert("data",dataValue);

    //构建 Json 文档， Json 文档是字节流形式
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObject);
    m_tcpSocket->write(jsonDoc.toJson(QJsonDocument::Compact));
    qDebug()<<"m_tcpSocket->write: "<<jsonDoc.toJson(QJsonDocument::Compact);
}

//tcp读信息
void ClientSocket::onReadyRead()
{
    QByteArray recByte = m_tcpSocket->readAll();
    QJsonDocument recJsonDoc(QJsonDocument::fromJson(recByte));
    if(!recJsonDoc.isNull()){
        if(recJsonDoc.isObject()){
            QJsonObject jsonObj = recJsonDoc.object();
            qDebug()<<jsonObj;
            MessageType type = static_cast<MessageType>(jsonObj.value("type").toInt());
            QJsonValue dataValue = jsonObj.value("data");
            QJsonObject dataObj;
            if(dataValue.isObject()){
                dataObj = dataValue.toObject();
            }
            int from = jsonObj.value("from").toInt();
            qDebug()<<"收到来自id："<<from<<" 的消息。";
            switch(type){
            case MessageType::Login:{
                parseTypeLogin(dataObj);
            }
            break;
            default:
                break;
            }
        }
    }

}

// 服务端返回 MessageType::Login ，客户端解析
void ClientSocket::parseTypeLogin(const QJsonObject &dataObj)
{
    qDebug()<<"parseTypeLogin";
    qDebug()<<dataObj;
    int code = dataObj.value("code").toInt();
    QString head = dataObj.value("head").toString();//用于设置头像
    int id = dataObj.value("id").toInt();//用于设置id
    QString msg = dataObj.value("msg").toString();
    if(code == -1){//用户名或密码错误
        emit signalMessageStatus(MessageStatus::LoginPasswdError);
    }else if(code == -2){//用户已在线
        emit signalMessageStatus(MessageStatus::LoginRepeat);
    }else if(code == 0 && msg == "ok"){
        emit signalMessageStatus(MessageStatus::LoginSuccess);
    }

    this->setId(id);
}

