#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "World.h"
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
private:
    Ui::MainWindow *ui;
    World *world;
    QImage *image;
};

#endif // MAINWINDOW_H
