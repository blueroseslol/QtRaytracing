#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),currentProgress(0)
{
    ui->setupUi(this);
    world=new World(&setting);

    connect(&timer,SIGNAL(timeout()),this,SLOT(updateRenderResult()));
    connect(&renderTimer,&QTimer::timeout,[this]{
        ui->timeEdit_renderTime->setTime( ui->timeEdit_renderTime->time().addSecs(1));
    });
    connect(world,SIGNAL(renderComplete()),this,SLOT(renderComplete()));

}

MainWindow::~MainWindow()
{
    delete world;
    delete ui;
}

void MainWindow::on_pushButton_renderSetting_clicked()
{
    setting.show();
}

void MainWindow::on_pushButton_start_clicked()
{
    //初始化渲染参数
    ui->label->resize(setting.imageWidth,setting.imageHeight);
    ui->label->clear();
    ui->progressBar->setValue(0);
    ui->timeEdit_renderTime->setTime(QTime(0,0));

    //开始渲染
    world->build();
    world->render_scene();
    timer.start(200);
    renderTimer.start(1000);
}

void MainWindow::on_pushButton_saveImage_clicked()
{
    if(world->image){
        QFileDialog::getSaveFileName(this,
              QString::fromLocal8Bit("保存渲染结果"), "", QString::fromLocal8Bit("图片文件 (*.png *.jpg *.bmp)"));
            world->image->save(setting.fileName);
    }
}

void MainWindow::renderComplete()
{
    timer.stop();
    renderTimer.stop();
    ui->label->setPixmap(QPixmap::fromImage(*world->image));
    ui->progressBar->setValue(100);
}

void MainWindow::updateRenderResult()
{
    ui->label->setPixmap(QPixmap::fromImage(*world->image));
    ui->progressBar->setValue(world->progress);
    //根据已经渲染的时间与总体像素的比值来调整更新间隔
    timer.setInterval((ui->timeEdit_renderTime->time().minute()+1)*1000*1000/(setting.imageHeight*setting.imageWidth)*100);
}

void MainWindow::on_pushButton_clicked()
{
    world->terminate=true;
}
