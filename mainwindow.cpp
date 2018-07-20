#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),image(nullptr)
{
    ui->setupUi(this);
    world=new World(&setting);
    connect(world,SIGNAL(pixelComplete(int,int,QColor)),this,SLOT(setPixelColor(const int&,const int&,const QColor&)));
}

MainWindow::~MainWindow()
{
    if(image)
        delete image;
    delete world;
    delete ui;
}

void MainWindow::setPixelColor(const int& u,const int& v, const QColor& color){
    image->setPixelColor(u,v,color);

    currentRenderPixelNum+=1;
    ui->progressBar->setValue(currentRenderPixelNum/allPixelNum*100);
    if(currentRenderPixelNum%setting.imageWidth==0){
        ui->label->setPixmap(QPixmap::fromImage(*image));
    }
}

void MainWindow::on_pushButton_renderSetting_clicked()
{
    setting.show();
}

void MainWindow::on_pushButton_start_clicked()
{

    if(image){
        delete image;
        ui->label->resize(setting.imageWidth,setting.imageHeight);
    }
    image=new QImage(setting.imageWidth,setting.imageHeight,QImage::Format_RGB888);

    currentRenderPixelNum=0;
    allPixelNum=setting.imageWidth*setting.imageHeight;
    ui->progressBar->setValue(0);

    world->build();
    world->render_scene();
}

void MainWindow::on_pushButton_saveImage_clicked()
{
    if(image)
        image->save(setting.fileName);
}
