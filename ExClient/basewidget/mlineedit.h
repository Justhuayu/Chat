#ifndef MLINEEDIT_H
#define MLINEEDIT_H

#include <QLineEdit>

/*
    一些lineEdit
*/

class QLabel;

//IP地址过滤
class IPLineEdit : public QLineEdit
{
public:
    IPLineEdit(QWidget *parent = nullptr);
    void setIP(QString val);//设置IP地址
private:
    QLineEdit *m_lineEdit[4];//ip地址LineEdit
    QLabel *m_labelDot[3];//ip地址点

    bool isIPValid(const QString &strIP);//判断IP地址是否正确,true正确，false错误
    int getCurEditIndex(QLineEdit *curEdit);//获取当前edit在IP中的索引，-1表示未找到，0，1，2...表示索引位置
    void intoNextIpLineEdit(QLineEdit *curEdit);//跳到下一个ip edit
    void intoPrevIpLineEdit(QLineEdit *curEdit);//跳到上一个ip edit

    bool eventFilter(QObject *watched, QEvent *event);//事件过滤
};



//MAC地址过滤，暂时未用
class MACLineEdit : public QLineEdit
{
public:
    MACLineEdit(QWidget *parent = nullptr);

};


//输入框添加Icon
class IconLineEdit : public QLineEdit
{
public:
    IconLineEdit(QWidget *parent = nullptr);
    void setIcon(QString resPath);//设置Icon
private:
    QLabel *labelPixmap;//存放Icon 的 label

};
#endif // MLINEEDIT_H
