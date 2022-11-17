/**************************************************************************************************
* @Copyright (C), 2022-2099, ...Co.,Ltd.
* @File name: StickyNotes
* @Author: ciyeer
* @Version: 1.0
* @Date:  2022-11-17 hh:mm:ss
* @Description:
* @Others:
* @Function List:
*    1.
*    2.
* @History:
**************************************************************************************************/

/***************************************************************
 *  @filename      程序文件的名称
 *  @brief         程序文件的功能
 *  @param index   参数
 *  @date          日期
 *  @return        返回说明
 *  @Sample usage: 函数的使用方法
 **************************************************************/
#include "settingsui.h"
#include "ui_settingsui.h"

SettingsUI::SettingsUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsUI){
    ui->setupUi(this);

    setWindowFlags (Qt::FramelessWindowHint);
    m_pTitleBar = new TitleBar(this);
    m_pCenterWidget = new CenterWidget(this);

    ui->titleLayout->addWidget(m_pTitleBar);
    ui->centerLayout->addWidget(m_pCenterWidget);
    CommonHelper::setStyle(":/res/css/button.css");
}

void SettingsUI::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        mouse_press = true;
        move_point = event->pos();;
    }
}

void SettingsUI::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event)
    mouse_press = false;
}

void SettingsUI::mouseMoveEvent(QMouseEvent *event){
    if(!mouse_press){
        return;
    }
    this->move(event->globalPos() - move_point);
}

SettingsUI::~SettingsUI(){
    delete ui;
}
