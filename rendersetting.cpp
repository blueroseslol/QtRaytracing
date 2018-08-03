#include "rendersetting.h"
#include "ui_rendersetting.h"
#include <QSettings>
//#include <QFile>
#include <QDebug>
#include "Sampler/jittered.h"
#include "Sampler/regular.h"
RenderSetting::RenderSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderSetting),
    imageWidth(500),imageHeight(500),fileName("result.png"),backergroundColor(RGBColor()),
    samplerPtr(nullptr)
{
    ui->setupUi(this);
//    QSettings config("RenderSetting.ini",QSettings::NativeFormat);
//    imageWidth=config.value("Globel/ImageWidth").toString().toInt();
//    imageHeight=config.value("Globel/ImageHeight").toString().toInt();
//    fileName=config.value("Globel/FileName").toString();
    ui->lineEdit_fileName->setText(fileName);
    ui->spinBox_imageWidth->setValue(imageWidth);
    ui->spinBox_imageHeight->setValue(imageHeight);

    ui->tab->setLayout(ui->formLayout_global);
}

RenderSetting::~RenderSetting()
{
    delete ui;
}

void RenderSetting::on_pushButton_close_clicked()
{
    this->close();
}

void RenderSetting::on_lineEdit_fileName_textChanged(const QString &arg1)
{
    this->fileName=arg1;
//    QSettings config("RenderSetting.ini",QSettings::IniFormat);
//    config.setValue("Globel/FileName",arg1);
}

void RenderSetting::on_spinBox_imageWidth_valueChanged(const QString &arg1)
{
    this->imageWidth=int(arg1.toInt());
//    QSettings config("RenderSetting.ini",QSettings::IniFormat);
//    config.setValue("Globel/ImageWidth",arg1);
}

void RenderSetting::on_spinBox_imageHeight_valueChanged(const QString &arg1)
{
    this->imageHeight=int(arg1.toInt());
//    QSettings config("RenderSetting.ini",QSettings::NativeFormat);
//    config.setValue("Globel/ImageHeight",arg1);
}

void RenderSetting::setSampler(Sampler *sp)
{
    if(samplerPtr){
        delete samplerPtr;
        samplerPtr=nullptr;
    }
    numSamples=sp->getNumSamples();
    samplerPtr=sp;
}

void RenderSetting::setSamples(const int n)
{
    numSamples=n;
    if(samplerPtr){
        delete samplerPtr;
        samplerPtr=nullptr;
    }

    if(numSamples>1){
        samplerPtr=new Jittered(n);
    }else{
//        samplerPtr=new Regular(0);
    }
}
