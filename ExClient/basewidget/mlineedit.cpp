#include "mlineedit.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QPixmap>

//IP地址过滤
IPLineEdit::IPLineEdit(QWidget *parent)
    :QLineEdit(parent)
{
    //"(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})"
    QRegularExpression regex("25[0-5]|2[0-4][0-9]|1?[0-9]{1,2}");
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setSpacing(2);
    hLayout->setContentsMargins(1,1,1,1);

    for(int i = 0;i<4;i++){
        m_lineEdit[i] = new QLineEdit(this);
        m_lineEdit[i]->setStyleSheet("QLineEdit { border: none; padding: 0; margin: 0; }"); // 设置样式表
        m_lineEdit[i]->setMaxLength(3);//设置内容最大长度
        m_lineEdit[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);//设置大小策略
        m_lineEdit[i]->setAlignment(Qt::AlignCenter);//设置对齐方式
        m_lineEdit[i]->installEventFilter(this);//设置事件过滤器
        m_lineEdit[i]->setValidator(new QRegularExpressionValidator(regex,this));//设置正则验证
        hLayout->addWidget(m_lineEdit[i]);
        if(i<3){
            m_labelDot[i] = new QLabel(".");
            m_labelDot[i]->setFixedWidth(2);//设置文字固定占宽
            hLayout->addWidget(m_labelDot[i]);
        }
    }
}

//事件过滤
bool IPLineEdit::eventFilter(QObject *watched, QEvent *event){
    if(this->children().contains(watched) && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
        QLineEdit *pCurEdit = qobject_cast<QLineEdit*>(watched);
        int pLength = pCurEdit->text().length();//当前line文本长度
        switch(keyEvent->key()){
        case Qt::Key_0://按下数字
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
        {
            QString pText = pCurEdit->text();//当前line中文本内容

            if(pCurEdit->selectedText().length()){//处理内容选择时，按键自动删除并填充
                pCurEdit->setText(pCurEdit->text().replace(pCurEdit->selectedText(),QChar(keyEvent->key())));
                return true;//不让事件继续传递，输入的字符已经替换了内容，再传递会重复两次
            }else if((pLength == 3 )||(pLength == 2 && pText.toInt() * 10 > 255)){//定位到下一个
                intoNextIpLineEdit(pCurEdit);
            }else if(pText == '0'){//已经输入0时，直接定位到下一个
                intoNextIpLineEdit(pCurEdit);
                return true;
            }
        }
        break;
        case Qt::Key_Backspace://后退键
        {
            if(pLength ==0 ){//当前edit无数字
                intoPrevIpLineEdit(pCurEdit);
            }else{
                return QLineEdit::eventFilter(watched,event);
            }
        }
        break;
        case Qt::Key_Period://小数点
        {
            if(pLength != 0){
                intoNextIpLineEdit(pCurEdit);
            }else{
                return QLineEdit::eventFilter(watched,event);
            }
        }
        break;
        case Qt::Key_Left://左箭头
        {
            intoPrevIpLineEdit(pCurEdit);
        }
        break;
        case Qt::Key_Right://右箭头
        {
            intoNextIpLineEdit(pCurEdit);
        }
        break;
        default:
            break;
        }
        return QLineEdit::eventFilter(watched,event);

    }else{
        return false;
    }
}

//跳到下一个ip edit
void IPLineEdit::intoNextIpLineEdit(QLineEdit *curEdit){
    int editIndex = getCurEditIndex(curEdit);
    if(editIndex != -1 && editIndex != 3){
        m_lineEdit[editIndex+1]->setFocus();
        m_lineEdit[editIndex+1]->selectAll();
    }
}

//跳到上一个ip edit
void IPLineEdit::intoPrevIpLineEdit(QLineEdit *curEdit){
    int editIndex = getCurEditIndex(curEdit);
    if(editIndex != -1 && editIndex != 0){
        m_lineEdit[editIndex-1]->setFocus();
        m_lineEdit[editIndex-1]->selectAll();
    }
}
//获取当前edit在IP中的索引，-1表示未找到，0，1，2...表示索引位置
int IPLineEdit::getCurEditIndex(QLineEdit *curEdit){
    for(int i=0;i<4;i++){
        if(curEdit == m_lineEdit[i]){
            return i;
        }
    }
    return -1;
}
//显示ip地址到IPLineEdit
void IPLineEdit::setIP(QString val){
    if(!isIPValid(val)){//判断IP地址是否有效
        QMessageBox::warning(this,"IP地址错误","请输入正确的IP地址");
    }else{
        QStringList ipParts = val.split(".");
        for(int i =0;i<4;i++){
            //为每一个lineEdit设置ip
            m_lineEdit[i]->setText(ipParts[i]);
        }
    }

}

//判断IP地址是否正确,true正确，false错误
bool IPLineEdit::isIPValid(const QString &strIP)
{
    QRegularExpression regex("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    if (!regex.match(strIP).hasMatch())
        return false;
    return true;
}
//MAC地址过滤
MACLineEdit::MACLineEdit(QWidget *parent)
    :QLineEdit(parent)
{

}

//输入框添加Icon
IconLineEdit::IconLineEdit(QWidget *parent)
    :QLineEdit(parent)
{
    labelPixmap = new QLabel(this);
    labelPixmap->setMinimumSize(16,16);//Icon尺寸16x16
    labelPixmap->setVisible(false);//没有图片时不显示label
}

//设置Icon
void IconLineEdit::setIcon(QString resPath){
    if(resPath == NULL){
        return;
    }
    QPixmap pix(resPath);
    labelPixmap->setPixmap(pix);//label放入图片
    labelPixmap->setVisible(true);//label可见
    labelPixmap->setGeometry(5,(this->height() - pix.height()) / 2, 16, 16);//放入label
    this->setTextMargins(25, 1, 1, 1);
}


