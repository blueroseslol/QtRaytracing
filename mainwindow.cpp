#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),image(nullptr),needUpdate(false)
{
    ui->setupUi(this);
    world=new World(&setting);

    connect(&timer,SIGNAL(timeout()),this,SLOT(updateRenderResult()));
    connect(world,SIGNAL(pixelComplete(int,int,float,QColor)),this,SLOT(setPixelColor(const int&,const int&,const float&,const QColor&)));
    connect(world,SIGNAL(renderComplete()),this,SLOT(renderComplete()));
}

MainWindow::~MainWindow()
{
    if(image)
        delete image;
    delete world;
    delete ui;
}

void MainWindow::setPixelColor(const int& u, const int& v,const float& progress,const QColor& color){
    image->setPixelColor(u,v,color);
    currentProgress=progress;
    needUpdate=true;
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

    //开始渲染
    world->build();
    world->render_scene();
    timer.start(300);
}

void MainWindow::on_pushButton_saveImage_clicked()
{
    if(image)
        image->save(setting.fileName);
}

void MainWindow::renderComplete()
{
    timer.stop();
    ui->label->setPixmap(QPixmap::fromImage(*image));
    ui->progressBar->setValue(100);
}

void MainWindow::updateRenderResult()
{
    if(!needUpdate)
        return;
    ui->label->setPixmap(QPixmap::fromImage(*image));
    ui->progressBar->setValue(currentProgress);
    needUpdate=false;
}
