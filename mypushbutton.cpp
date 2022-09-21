#include "mypushbutton.h"
#include <QPainter>
#include <QPropertyAnimation> //动画
#include <QDebug>

MyPushButton::MyPushButton(QString normalImag,QString pressedImg,QWidget *parent)
    : QPushButton(parent)
    , mNormalImg(normalImag)
    , mPressedImg(pressedImg)
{
    mStat = Normal;
}

void MyPushButton::moveDown()
{
    //位置大小属性发生变化
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::moveUp()
{
    //位置大小属性发生变化
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::paintEvent(QPaintEvent *ev)
{
    //绘制按钮图片
    QPainter painter(this);
    QPixmap pixmap;
    if(mStat == Normal)
        pixmap.load(mNormalImg);
    if(mStat == Pressed)
        pixmap.load(mPressedImg);
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    //绘制按钮的文字
    //qDebug() << this->text();
    painter.drawText(0,0,this->width(),this->height(),
                     Qt::AlignHCenter|Qt::AlignVCenter,this->text());
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    this->mStat = Pressed;
    update();
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->mStat = Normal;
    update();
    QPushButton::mouseReleaseEvent(e);
}
