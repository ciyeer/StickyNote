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
#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QApplication>
#include <QFile>
#include <QDebug>

class CommonHelper{
public:
    void setStyle(const QString &style){
        QFile qss(style);
        // qDebug() << "CommonHelper";
        if(!qss.open(QFile::ReadOnly)){
            qDebug() << "qss file open failed";
            return;
        }
        qApp->setStyleSheet(qss.readAll()); // QT中自带的单例
        qss.close();
    }
};

#endif // COMMONHELPER_H
