#ifndef RENDERSETTING_H
#define RENDERSETTING_H

#include <QWidget>

namespace Ui {
class RenderSetting;
}

class RenderSetting : public QWidget
{
    Q_OBJECT

public:
    explicit RenderSetting(QWidget *parent = 0);
    ~RenderSetting();
    QString fileName;
    int imageWidth;
    int imageHeight;

private slots:
    void on_pushButton_close_clicked();

    void on_lineEdit_fileName_textChanged(const QString &arg1);

    void on_spinBox_imageWidth_valueChanged(const QString &arg1);

    void on_spinBox_imageHeight_valueChanged(const QString &arg1);

private:
    Ui::RenderSetting *ui;
};

#endif // RENDERSETTING_H
