/*********************************************************************
*  @Copyright (C), 2022-2099, ...Co.,Ltd.
*  @Filename:
*  @Author:
*  @Version:
*  @Date:
*  @Description:
*  @Others:
*  @Function List:
*     1.
*     2.
*  @History:
***********************************************************************/
#ifndef SETTINGSUI_H
#define SETTINGSUI_H

#include <QWidget>
#include <QMouseEvent>
#include "titlebar.h"
#include "centerwidget.h"
#include "commonhelper.h"

namespace Ui {
class SettingsUI;
}

class SettingsUI : public QWidget{
    Q_OBJECT

public:
    explicit SettingsUI(QWidget *parent = nullptr);
    ~SettingsUI();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::SettingsUI *ui;
    TitleBar *m_pTitleBar;
    CenterWidget *m_pCenterWidget;
    QPoint move_point; //移动的距离
    bool mouse_press;  //鼠标按下
};

#endif // SETTINGSUI_H
