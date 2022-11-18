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
    CommonHelper().setStyle(":/res/css/button.css");
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
