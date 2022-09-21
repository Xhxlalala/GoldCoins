#include "coinbutton.h"
#include <QPainter>

CoinButton::CoinButton(QWidget *parent) : QPushButton(parent)
{
    //初始状态设置
    this->setStat(0);
    //设置按钮不规则样式，去掉边框
    this->setStyleSheet("QPushButton{border:0px;}");

    connect(&this->mTimer,&QTimer::timeout,[=](){
        if(this->mStat)
        {
            this->mFrame--;
        }
        else
        {
            this->mFrame++;
        }

        QString frameName = QString(":/res/Coin000%1.png").arg(this->mFrame);
        this->setIcon(QIcon(frameName));
        if(this->mFrame==8 || this->mFrame==1)
        {
            this->mTimer.stop();
        }
    });
}

int CoinButton::stat() const
{
    return mStat;
}

void CoinButton::setStat(int stat)
{
    mStat = stat;
    if(this->mStat)
    {
        this->setIcon(QIcon(":/res/Coin0001.png"));
    }
    else
    {
        this->setIcon(QIcon(":/res/Coin0008.png"));
    }
    this->setIconSize(this->size());
}

void CoinButton::setStatWithAnimation(int stat)
{
    this->mStat = stat;
    if(this->mStat) //银币反金币
    {
        this->mFrame = 8;
    }
    else //金币反银币
    {
        this->mFrame = 1;
    }
    this->mTimer.start(30);
}

void CoinButton::flip()
{
//    this->setStat(!this->stat());
    this->setStatWithAnimation(!this->stat());
}

void CoinButton::paintEvent(QPaintEvent *event)
{
    //绘制按钮图片
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/res/BoardNode.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    QPushButton::paintEvent(event);
}
