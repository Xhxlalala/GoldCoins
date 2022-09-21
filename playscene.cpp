#include <QPainter>
#include <QMenuBar>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>
#include "playscene.h"
#include "mypushbutton.h"
#include "coinbutton.h"
#include "dataconfig.h"

PlayScene::PlayScene(int level, QWidget *parent) : MyMainWindow(parent)
{
    mHasWin = false;
    //返回按钮
    MyPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btnBack->resize(72,32);

    connect(btnBack,&QPushButton::clicked,this,&PlayScene::backBtnClicked);
    btnBack->move(this->width() - btnBack->width(),this->height()-btnBack->height());

    //添加level提示
    QLabel *label = new QLabel(this);
    label->setText(QString("Level: %1").arg(level));
    label->resize(150,50);
    label->setFont(QFont("华文新魏",20));
    //移动到左下角
    label->move(30,this->height()-label->height());

    const int colWidth = 50;
    const int rowHeight = 50;
    // x,y偏移
    const int xOffset = 57;
    const int yOffset = 200;

    //取出第几关的二维数组数据
    dataConfig data;
    QVector <QVector <int > > dataArray = data.mData[level];

    //16个硬币按钮
    for(int row = 0; row < 4; ++row) {
        for(int col = 0; col < 4; ++col) {
            CoinButton *btn = new CoinButton(this);
            mCoins[row][col] = btn;
            int x = col * colWidth + xOffset;
            int y = row * rowHeight + yOffset;
            btn->setGeometry(x,y,50,50);
            btn->setStat(dataArray[row][col]);
            //每次点击状态置反
            connect(btn,&CoinButton::clicked,[=](){
                this->flip(row,col);
            });
        }
    }
}

void PlayScene::flip(int row, int col)
{
    if(mHasWin)
    {
        return;
    }
    this->mCoins[row][col]->flip();

    QSound::play(":/res/ConFlipSound.wav");
    // 反转上下左右的硬币
    QTimer::singleShot(250,[=](){
        if(row + 1 < 4) this->mCoins[row+1][col]->flip();
        if(row - 1 >= 0) this->mCoins[row-1][col]->flip();
        if(col - 1 >= 0) this->mCoins[row][col-1]->flip();
        if(col + 1 < 4) this->mCoins[row][col+1]->flip();
        //判断游戏是否胜利
        this->judgeWin();
    });
}

void PlayScene::judgeWin()
{
    for(int row = 0; row < 4; ++row) {
        for(int col = 0; col < 4; ++col) {
            //只要还有一个银币游戏就继续
            if(!this->mCoins[row][col]->stat()) {
                return;
            }
        }
    }
    //全部为金币游戏结束
    //QMessageBox::information(this,"恭喜","你已经胜利了");
    mHasWin = true;
    QSound::play(":/res/LevelWinSound.wav");
    //播放胜利动画
    QLabel *labelWin = new QLabel(this);
    QPixmap pix = QPixmap(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->show();
    labelWin->move((this->width()-labelWin->width())/2,0);

    QPropertyAnimation *animation = new QPropertyAnimation(labelWin,"geometry",this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+100,labelWin->width(),labelWin->height()));
    animation->setDuration(1000);
    //设置动画运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.translate(0,this->menuBar()->height());
    // 绘制背景图
    QPixmap pixmap(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    // 绘制logo
    pixmap.load(":/res/Title.png");
    pixmap = pixmap.scaled(pixmap.width()/2,pixmap.height()/2);
    painter.drawPixmap(0,0,pixmap);
}

