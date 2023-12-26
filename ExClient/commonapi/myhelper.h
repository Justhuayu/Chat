#ifndef MYHELPER_H
#define MYHELPER_H

#include <QObject>

/*
    工具函数
*/

//定义成static 可以直接调用而无需new
class MyHelper
{

public:

    static void setStyle(const QString &qssPath);//设置style
    static void setAppIcon(const QString &iconPath);//设置app图标
};

#endif // MYHELPER_H
