#include "myhelper.h"
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QIcon>
//设置style
void MyHelper::setStyle(const QString &qssPath){
    QFile file(qssPath);
    if(file.open(QFile::ReadOnly)){//打开qss文件
        qApp->setStyleSheet(file.readAll());//设置qss样式表
        file.close();
    }
}

//设置app图标
void MyHelper::setAppIcon(const QString &iconPath){
    qApp->setWindowIcon(QIcon(QPixmap(iconPath)));
}
