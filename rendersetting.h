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

private:
    Ui::RenderSetting *ui;
};

#endif // RENDERSETTING_H
