#ifndef STICKYNOTES_H
#define STICKYNOTES_H

#include <QWidget>
#include <QSystemTrayIcon>
#include "translucentwidget.h"
#include "settingsui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StickyNotes; }
QT_END_NAMESPACE

// 分页类型
enum pageType{ToDo, Done};

class StickyNotes : public TranslucentWidget{
    Q_OBJECT

public:
    explicit StickyNotes(QWidget *parent = nullptr);
    ~StickyNotes();

    // 托盘菜单
    void setSystemTrayMenu();

private:
    Ui::StickyNotes *ui;
    SettingsUI *m_pSettingsUi;
    QSystemTrayIcon *m_pSystemTrayIcon;
};
#endif // STICKYNOTES_H
