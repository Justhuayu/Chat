#ifndef MYAPP_H
#define MYAPP_H
#include <QString>

class MyApp
{
public:

    //=======================系统配置部分=========================//
    static QString m_strAppPath;         // 应用程序路径
    static QString m_strDataPath;        // 数据保存路径
    static QString m_strRecvPath;        // 接收目录
    static QString m_strDatabasePath;    // 数据库目录
    static QString m_strConfPath;        // 配置目录
    static QString m_strSoundPath;       // 音频目录
    static QString m_strRecordPath;      // 录音目录

    static QString m_strFacePath;        // 配置目录
    static QString m_strHeadPath;        // 配置目录

    static QString m_strIniFile;         // 配置文件

    static QString m_strHostAddr;       // 服务器地址配置 ***
    static int     m_nMsgPort;          // 聊天消息服务器端口配置 ***
    static int     m_nFilePort;          // 文件转发服务器端口配置
    static int     m_nGroupPort;        // 群组聊天窗口

    static QString m_strUserName;       // 用户名
    static QString m_strPassword;       // 用户密码
    static QString m_strHeadFile;       // 头像文件

    static int     m_nId;

    static int     m_nWinX;
    static int     m_nWinY;

};

#endif // MYAPP_H
