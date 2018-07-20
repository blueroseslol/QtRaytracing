#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
public slots:
    void setPixelColor(const int &u, const int &v, const QColor &color);
private slots:


    void on_pushButton_renderSetting_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_saveImage_clicked();

private:
    Ui::MainWindow *ui;
    World *world;
    QImage *image;
    RenderSetting setting;

    int currentRenderPixelNum;
    int allPixelNum;
};

#endif // MAINWINDOW_H
