#include "rendersetting.h"
#include "ui_rendersetting.h"

RenderSetting::RenderSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderSetting)
{
    ui->setupUi(this);
}

RenderSetting::~RenderSetting()
{
    delete ui;
}
