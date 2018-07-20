#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    world=new World;
    image=new QImage(200,100,QImage::Format_RGB888);

    connect(world,SIGNAL(pixelComplete(int,int,QColor)),this,SLOT(setPixelColor(const int&,const int&,const QColor&)));

    world->build();
    world->render_scene();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPixelColor(const int& u,const int& v, const QColor& color){
    image->setPixelColor(u,v,color);
    ui->label->setPixmap(QPixmap::fromImage(*image));
}
