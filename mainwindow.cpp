#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),image(nullptr),rendering(false)
{
    ui->setupUi(this);
    world=new World(&setting);
    connect(world,SIGNAL(pixelComplete(int,int,int,QColor)),this,SLOT(setPixelColor(const int&,const int&,const int&,const QColor&)));
    connect(world,SIGNAL(renderComplete()),this,SLOT(renderComplete()));
}

MainWindow::~MainWindow()
{
    if(image)
        delete image;
    delete world;
    delete ui;
}

void MainWindow::setPixelColor(const int& u, const int& v, const int &progress, const QColor& color){
    image->setPixelColor(u,v,color);

    ui->progressBar->setValue(progress);
}

void MainWindow::on_pushButton_renderSetting_clicked()
{
    setting.show();
}

void MainWindow::on_pushButton_start_clicked()
{
    //初始化渲染参数
    if(image){
        delete image;
        ui->label->resize(setting.imageWidth,setting.imageHeight);
    }
    image=new QImage(setting.imageWidth,setting.imageHeight,QImage::Format_RGB888);

    ui->progressBar->setValue(0);
    rendering=true;
    //开始渲染
    world->build();
    world->render_scene();
}

void MainWindow::on_pushButton_saveImage_clicked()
{
    if(image)
        image->save(setting.fileName);
}

void MainWindow::renderComplete()
{
    rendering=false;
    ui->progressBar->setValue(100);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if(rendering){
        ui->label->setPixmap(QPixmap::fromImage(*image));
    }
}


