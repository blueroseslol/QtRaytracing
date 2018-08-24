#ifndef RENDERSETTING_H
#define RENDERSETTING_H

#include <QWidget>
#include "Utilities/RGBColor.h"

class Sampler;
namespace Ui {
class RenderSetting;
}

class RenderSetting : public QWidget
{
    Q_OBJECT

public:
    explicit RenderSetting(QWidget *parent = 0);
    ~RenderSetting();
    RGBColor backergroundColor;
    int imageWidth;
    int imageHeight;
    int numSamples;
    Sampler *samplerPtr;

    void setSampler(Sampler *sp);

    void setSamples(const int n);
private slots:
    void on_pushButton_close_clicked();

//    void on_lineEdit_fileName_textChanged(const QString &arg1);

    void on_spinBox_imageWidth_valueChanged(const QString &arg1);

    void on_spinBox_imageHeight_valueChanged(const QString &arg1);

private:
    Ui::RenderSetting *ui;
};

#endif // RENDERSETTING_H
