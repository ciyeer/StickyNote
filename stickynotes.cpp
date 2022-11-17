#include "stickynotes.h"
#include <QDebug>
#include "ui_stickynotes.h"
#include <QAction>

StickyNotes::StickyNotes(QWidget *parent)
    : TranslucentWidget(parent),
    ui(new Ui::StickyNotes){
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/res/img/logo/Logo.ico"));
    setSystemTrayMenu();

    // Settings
    connect(this, &TranslucentWidget::sigSendSettings, this, [=](){
        m_pSettingsUi = new SettingsUI;
        m_pSettingsUi->show();
    });

    // onTopHint
    connect(this, &TranslucentWidget::sigSendOnTopHint, this, [=](bool isOn){
        // isOn == true: 置顶, false: 取消置顶
        this->setWindowFlag(Qt::WindowStaysOnTopHint, isOn);
        this->setHidden(false);
        qDebug() << isOn;
    });

    // Display/Hide: true--diaplay, false:--hide
    connect(this, &TranslucentWidget::sigSendisDisplay, this, [=](bool){
        // true:display
        // false:hide
        qDebug() << "display/hide";
    });

    // Exit
    connect(this, &TranslucentWidget::sigSendExitWidget, this, [=](){
        this->close();
    });
}

void StickyNotes::setSystemTrayMenu(){
//    CommonHelper::setStyle(":/css/contextmenu.css");
    //系统托盘
//    m_pSetTimeAction = new QAction(QStringLiteral("设置闹钟"), this);
//    m_pQuitAction = new QAction("退出", this);
//    m_pHideAction = new QAction("隐藏", this);
//    m_pShowAction = new QAction("显示", this);
//    connect(m_pQuitAction,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
//    //connect(m_pSetTimeAction,SIGNAL(triggered(bool)),this,SLOT(setTime()));
//    connect(m_pHideAction,SIGNAL(triggered(bool)),this,SLOT(setHideWidget()));
//    connect(m_pShowAction,SIGNAL(triggered(bool)),this,SLOT(setShowWidget()));

//    m_pMyMenu = new QMenu((QWidget*)QApplication::desktop());
//    m_pMyMenu->addAction(m_pSetTimeAction);
//    m_pMyMenu->addAction(m_pHideAction);
//    m_pMyMenu->addAction(m_pShowAction);
//    m_pMyMenu->addAction(m_pQuitAction);
    //myMenu->addSeparator();

    // 判断系统是否支持托盘图标
    if(!QSystemTrayIcon::isSystemTrayAvailable()){
        return;
    }
    //    隐藏到系统托盘
    m_pSystemTrayIcon = new QSystemTrayIcon(this);
    m_pSystemTrayIcon->setIcon(QIcon(":/res/img/logo/Logo.ico"));
    m_pSystemTrayIcon->setToolTip("便签");
    m_pSystemTrayIcon->showMessage("托盘","托盘管理",QSystemTrayIcon::Information,10000);
    //m_pSystemTrayIcon->setContextMenu(m_pMyMenu);
    m_pSystemTrayIcon->show();
}

StickyNotes::~StickyNotes(){
    delete ui;
    delete m_pSettingsUi;
}
