/*****************************************************************************************************************
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
*****************************************************************************************************************/
#ifndef TRANSLUCENTWIDGET_H
#define TRANSLUCENTWIDGET_H

#define OVER 5

#include <QWidget>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QPoint>
#include <QRect>
#include <QCursor>
#include <QMenu>
#include "commonhelper.h"

// 拖拽方向(8个方向)
enum edgeDirtion {
    TOP_LEFT, TOP_RIGHT,
    BOTTOM_LEFT, BOTTOM_RIGHT,
    TOP, BOTTOM,
    LEFT, RIGHT,
    MOVE, DEFAULT
};

/*****************************************************************************************************************
 *  @classname
 *  @brief
 *  @member function List
 *  @Sample usage
*****************************************************************************************************************/
class TranslucentWidget : public QWidget{
    Q_OBJECT

public:
    TranslucentWidget(QWidget *parent = nullptr, int minWidth = 300+2*OVER, int minHeight = 300+2*OVER, int alpha = 50);
    ~TranslucentWidget();
    void setSmallGeometry(QRect Rect);
    QRect smallGeometry();
    QRect smallRect();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *) override;
    virtual void paintEvent(QPaintEvent *event) override;

    void focusInMyEvent();
    void focusOutMyEvent();

protected:
    void ui_initialize(int minWidth, int minHeight);
    void region(const QPoint &currentGlobalPoint);

private:
    bool m_bisPressed;
    QPoint  m_point;     // 鼠标点击的坐标
    QAction *m_pAct;
    QMenu *m_pMenu1, *m_pMenu2;

    edgeDirtion dir;
    bool isLeftPressing, resizeLocked, moveLocked,
         inBottom, inHead, inResize, focus;
    QPoint m_movePoint;
    int alpha;

signals:
    void paintAdd();
    void enterBottom();
    void leaveBottom();
    void enterHead();
    void leaveHead();
    void enterResize();
    void leaveResize();
    void tryLockedMove();

    // 发射设置信号
    void sigSendSettings();
    // 发射置顶/取消置顶信号
    void sigSendOnTopHint(bool);
    // 发射显示/隐藏信号
    void sigSendisDisplay(bool);
    // 发射退出信号
    void sigSendExitWidget();
};

#endif // TRANSLUCENTWIDGET_H

