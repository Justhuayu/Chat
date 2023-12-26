#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include <QTcpSocket>

/*
    客户端Socket
*/
enum class MessageType;
enum class MessageStatus;
class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = nullptr);
    void setId(const int &id);//设置m_nid
    void checkTcpConnect(QString hostAddress,int port);//检测Tcp是否连接，未连接则连接
    void tcpSendMessage(const MessageType &type,const QJsonValue &dataValue);//tcp发送信息
private:
    QTcpSocket *m_tcpSocket;
    int m_nid;

    void parseTypeLogin(const QJsonObject &dataObj);// 服务端返回 MessageType::Login ，客户端解析

signals:
    void signalMessageStatus(const MessageStatus &status);//发送消息状态信号
    void signalMessageType(const MessageType &type, const QJsonValue &dataVal);//发送消息类型信号
private slots:
    void onConnected();//tcp连接
    void onDisconnected();//tcp断开
    void onReadyRead();//读取信息
};

#endif // CLIENTSOCKET_H
