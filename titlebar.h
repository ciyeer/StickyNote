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
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

namespace Ui {
    class TitleBar;
}

class TitleBar : public QWidget{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

private slots:
    void on_closeButton_clicked();

private:
    Ui::TitleBar *ui;
};

#endif // TITLEBAR_H
