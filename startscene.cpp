#include "startscene.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

StartScene::StartScene(QWidget *parent) : MyMainWindow(parent)
{
    this->setWindowTitle("开始场景");

    MyPushButton *btnStart = new MyPushButton(":/res/MenuSceneStartButton.png",":/res/MenuSceneStartButton.png",this);
    btnStart->resize(114,114);
    // 按钮水平居中，垂直方向在3/4位置
    btnStart->move((this->width()-btnStart->width())/2,
                   this->height()*3/4-btnStart->height()/2);

    connect(&this->mSelectScene,SelectScene::backBtnClicked,[=](){
        QSound::play(":/res/TapButtonSound.wav");
        this->show();
        this->mSelectScene.hide();
        this->move(mSelectScene.pos());
    });
    connect(btnStart,&MyPushButton::clicked,[=](){
        QSound::play(":/res/TapButtonSound.wav");
        btnStart->setEnabled(false);
        btnStart->moveDown();
        //要等待之前的动画播放完再调用下一个动画
        QTimer::singleShot(150,[=](){
            btnStart->moveUp();
        });
        QTimer::singleShot(300,[=](){
            //动画全部完成按钮重新可用
            btnStart->setEnabled(true);
            //场景转换
            this->hide();
            this->mSelectScene.show();
            this->mSelectScene.move(this->pos());
        });
    });
}
