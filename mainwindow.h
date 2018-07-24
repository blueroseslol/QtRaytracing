#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "World.h"
#include "rendersetting.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void setPixelColor(const int &u, const int &v, const float &progress, const QColor &color);

    void renderComplete();

    void on_pushButton_renderSetting_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_saveImage_clicked();

    void updateRenderResult();
private:
    Ui::MainWindow *ui;
    World *world;
    QImage *image;
    RenderSetting setting;
    QTimer timer;
    //TODO:添加渲染时间显示功能

    float currentProgress;
    bool needUpdate;
//    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
