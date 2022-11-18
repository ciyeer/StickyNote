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
#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>

namespace Ui {
    class CenterWidget;
}

class CenterWidget : public QWidget{
    Q_OBJECT

public:
    explicit CenterWidget(QWidget *parent = nullptr);
    ~CenterWidget();

private:   
    Ui::CenterWidget *ui;
};

#endif // CENTERWIDGET_H
