#ifndef UNIT_H
#define UNIT_H

#endif // UNIT_H
/*
    协议相关
*/

//消息类型枚举
enum class MessageType{
    Unknow,
    Register            = 0x10,     // 用户注册  (10进制16)
    Login,                          // 用户登录 ***
    Logout,                         // 用户注销

    UserOnLine          = 0x15,     // 用户上线通知
    UserOffLine,                    // 用户下线通知
    UpdateHeadPic,                  // 用户更新头像

    AddFriend           = 0x20,     // 添加好友
    AddGroup,                       // 添加群组

    AddFriendRequist,               // 添加好友确认通知
    AddGroupRequist,                // 添加群组确认通知

    CreateGroup         = 0x25,     // 创建群组

    GetMyFriends        = 0x30,     // 上线获取我的好友的状态
    GetMyGroups,                    // 获取我的群组信息

    RefreshFriends      = 0x35,     // 刷新好友状态
    RefreshGroups,                  // 刷新群组成员状态

    SendMsg             = 0x40,     // 发送消息
    SendGroupMsg,                   // 发送群组消息
    SendFile,                       // 发送文件
    SendPicture,                    // 发送图片
    SendFace,                       // 发送表情

    ChangePasswd        = 0x50,     // 修改密码

    DeleteFriend        = 0x55,     // 删除好友
    DeleteGroup,                    // 退出群组

    SendFileOk          = 0x60,     // 文件发送完成状态

    GetFile             = 0x65,     // 获取文件（到服务器下载文件）
    GetPicture,                     // 图片下载

};

//消息状态
enum class MessageStatus{
    ConnectedHost = 0x01, // 连接到主机 ***
    DisConnectedHost,

    LoginSuccess,       // 登录成功 ***
    LoginPasswdError,   //  用户名或密码错误 ***
    LoginRepeat,        // 重复登录 ***

    OnLine,
    OffLine,

    RegisterOk,
    RegisterFailed,

    AddFriendOk,
    AddFriendFailed,
};
