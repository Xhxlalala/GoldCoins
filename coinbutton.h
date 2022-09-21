#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);

    int stat() const;
    void setStat(int stat);
    void setStatWithAnimation(int stat);

    //硬币反转
    void flip();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
private:
    //硬币状态
    int mStat;
    //记录当前帧
    int mFrame;
    //定时器
    QTimer mTimer;
};

#endif // COINBUTTON_H
