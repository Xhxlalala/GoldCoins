#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include<QPainter>

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    init();
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::init()
{
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QIcon(":/res/Title.png"));
    this->setFixedSize(320,588);
}

void MyMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pixmap(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
