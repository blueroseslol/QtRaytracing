#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "World.h"
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    World *world=new World;
    world->build();
    QImage *image;
    image=world->render_scene();
    ui->label->setPixmap(QPixmap::fromImage(*image));

}

MainWindow::~MainWindow()
{
    delete ui;
}
