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
    void renderComplete();

    void on_pushButton_renderSetting_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_saveImage_clicked();

    void updateRenderResult();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    World *world;
    RenderSetting setting;
    QTimer timer;
    QTimer renderTimer;
    float currentProgress;
    //TODO:添加渲染时间显示功能
//    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
