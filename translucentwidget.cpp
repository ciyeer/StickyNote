#include "translucentwidget.h"
#include <QMenu>
#include <QFile>
#include <QAction>
#include <QString>
#include <QDebug>
#include <QPen>
#include <QPainter>
#include <QGraphicsBlurEffect>

#define PADDING 3
#define MOVEHEIGHT 29

/*************************************************************************
 *  @brief  m_pAct:右键不同选项
 *  @brief  m_pAct[0]: 设置, m_pAct[1]: 置顶, m_pAct[2]: 显示,
 *  @brief  m_pAct[3]: 隐藏, m_pAct[4]: 退出
 *  @param  none
**************************************************************************/

TranslucentWidget::TranslucentWidget(QWidget *parent, int minWidth,
                                     int minHeight, int alpha)
    : QWidget(parent)
    , m_bisPressed(false)
    , m_pAct(new QAction[10])
    , alpha(alpha){

    ui_initialize(minWidth, minHeight);

    inHead = false;
    inResize = false;
    inBottom = false;
    resizeLocked = false;
    moveLocked = false;
    focus = false;

    // settings
    connect(&m_pAct[0], &QAction::triggered, this, [=](){
        emit sigSendSettings();
    });

    // onTopHint
    connect(&m_pAct[1], &QAction::triggered, this, [=](){
        emit sigSendOnTopHint(true);
    //  if(m_pAct[1].text() == "置顶"){
    //      emit sigSendOnTopHint(true);
    //      m_pAct[1].setText("取消置顶");  // 暂时不起作用
    //  }
    //  else{
    //      emit sigSendOnTopHint(false);
    //      m_pAct[1].setText("置顶");     // 暂时不起作用
    //  }
    });

    // cancel onTopHint
    connect(&m_pAct[2], &QAction::triggered, this, [=](){
        emit sigSendOnTopHint(false);
    });

    // Hide
    connect(&m_pAct[3], &QAction::triggered, this, [=](){
        emit sigSendisDisplay(false);
    });

    // Exit
    connect(&m_pAct[4], &QAction::triggered, this, [=](){
        emit sigSendExitWidget();
    });
}

void TranslucentWidget::ui_initialize(int minWidth, int minHeight){
    // 无边框: FramelessWindowHint
    // 置顶:   WindowStaysOnTopHint
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    CommonHelper().setStyle(":/res/css/contextmenu.css");
    //  阴影
    //  QGraphicsDropShadowEffect *e2 = new QGraphicsDropShadowEffect(this);
    //  e2->setOffset(8,8);
    //  this->setGraphicsEffect(e2);

    // 背景模糊(Effect)
    //  auto blurEffect = new QGraphicsBlurEffect(this);
    //  blurEffect->setBlurRadius(10);
    //  blurEffect->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
    //  this->setGraphicsEffect(blurEffect);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setMinimumWidth(minWidth);
    this->setMinimumHeight(minHeight);
    isLeftPressing = false;
}

void TranslucentWidget::setSmallGeometry(QRect Rect){
    setGeometry(Rect.left()-OVER,Rect.top()-OVER,Rect.width()+2*OVER,
                Rect.height()+2*OVER);
}

QRect TranslucentWidget::smallGeometry(){
    return QRect(geometry().left()+OVER,geometry().top()+OVER,
                 geometry().width()-2*OVER,geometry().height()-2*OVER);
}

QRect TranslucentWidget::smallRect(){
    return QRect(OVER,OVER,smallGeometry().width(),
                 smallGeometry().height());
}

void TranslucentWidget::focusInMyEvent(){
    alpha = 90;
    focus = true;
    repaint();
}

void TranslucentWidget::focusOutMyEvent(){
    alpha = 50;
    focus = false;
    repaint();
}

void TranslucentWidget::contextMenuEvent(QContextMenuEvent *event){
    Q_UNUSED(event)
    m_pMenu1 = new QMenu(this);
    m_pMenu1->setFixedWidth(100);
    m_pMenu1->addAction(new QAction("200%"));
    m_pMenu1->addAction(new QAction("175%"));
    m_pMenu1->addAction(new QAction("150%"));
    m_pMenu1->addAction(new QAction("125%"));
    m_pMenu1->addAction(new QAction("100%"));

    m_pAct[0].setText(QStringLiteral("设置"));
    m_pAct[0].setIcon(QIcon(":/res/img/tools/settings.png"));
    m_pAct[1].setText(QStringLiteral("置顶"));
    m_pAct[1].setIcon(QIcon(":/res/img/tools/lock.png"));
    m_pAct[2].setText(QStringLiteral("取消置顶"));
    m_pAct[2].setIcon(QIcon(":/res/img/tools/unlock.png"));
    m_pAct[3].setText(QStringLiteral("显示"));
    m_pAct[3].setIcon(QIcon(":/res/img/logo/Logo.png"));
    m_pAct[3].setMenu(m_pMenu1);
    m_pAct[4].setText(QStringLiteral("退出"));
    m_pAct[4].setIcon(QIcon(":/res/img/tools/exit.png"));

    m_pMenu2 = new QMenu(this);
    m_pMenu2->setFixedWidth(180);
    m_pMenu2->addAction(&m_pAct[0]);
    m_pMenu2->addAction(&m_pAct[1]);
    m_pMenu2->addSeparator();
    m_pMenu2->addAction(&m_pAct[2]);
    m_pMenu2->addAction(&m_pAct[3]);
    m_pMenu2->addAction(&m_pAct[4]);
    m_pMenu2->exec(QCursor::pos());
}

void TranslucentWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    emit paintAdd();

    QPen pen;
    pen.setColor(QColor(255,255,255,30));

    QBrush brush;
    brush.setColor(QColor(0,0,0,alpha));
    brush.setStyle(Qt::SolidPattern);

    QPainter painter(this);
    painter.setPen(QPen(QColor(0,0,0,0)));
    painter.setBrush(QBrush(QColor(0,0,0,1)));
    painter.drawRect(this->rect());
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(this->smallRect());

    if (!inResize || resizeLocked) {
        return;
    }
    int H = smallGeometry().height();
    int W = smallGeometry().width();
    painter.setBrush(QColor(255,255,255,255));
    painter.setPen(QColor(0,0,0,0));
    painter.drawRect(4+OVER,H-10+OVER,2,2);
    painter.drawRect(4+OVER,H-5+OVER,2,2);
    painter.drawRect(10+OVER,H-5+OVER,2,2);
    painter.drawRect(W-6+OVER,H-10+OVER,2,2);
    painter.drawRect(W-6+OVER,H-5+OVER,2,2);
    painter.drawRect(W-11+OVER,H-5+OVER,2,2);
    int x = 1.0*W/2;
    painter.drawRect(x+OVER,H-4+OVER,2,2);
    painter.drawRect(x+6+OVER,H-4+OVER,2,2);
    painter.drawRect(x-6+OVER,H-4+OVER,2,2);
}

/*********************************************************************
 *  @function   region
 *  @brief      确定便签范围
 *  @param      currentGlobalPoint
 *  @return     none
 *  @Sample usage    全局坐标点
**********************************************************************/
void TranslucentWidget::region(const QPoint &currentGlobalPoint){
    QRect rect = this->smallGeometry();
    int top = rect.top();
    int bottom = rect.bottom();
    int left = rect.left();
    int right = rect.right();

    int x = currentGlobalPoint.x();
    int y = currentGlobalPoint.y();
    dir = DEFAULT;
    if (y <= top + MOVEHEIGHT && y>= top && x >= left && x <= right) {
        if (!inHead) {
            inHead = true,emit enterHead();
        }
    }
    else if (inHead) {
        inHead = false, emit leaveHead();
    }
    if (!resizeLocked) {
        if (y >= bottom - PADDING && y<= bottom
                && x >= left && x <= right) {
            if (!inBottom) {
                inBottom = true, emit enterBottom();
            }
        }
        else if (inBottom) {
            inBottom = false, emit leaveBottom();
        }
        if (x >= left && x <= left + PADDING && y >= top
                && y <= top + PADDING) {
            dir = TOP_LEFT;
            this->setCursor(Qt::SizeFDiagCursor);
        }
        else if (x >= right - PADDING && x <= right
                 && y >= top && y <= top + PADDING) {
            dir = TOP_RIGHT;
            this->setCursor(Qt::SizeBDiagCursor);
        }
        else if (x >= left && x <= left + PADDING
                 && y >= bottom - PADDING && y <= bottom) {
            dir = BOTTOM_LEFT;
            this->setCursor(Qt::SizeBDiagCursor);
        }
        else if (x >= right - PADDING && x <= right
                 && y >= bottom - PADDING && y <= bottom) {
            dir = BOTTOM_RIGHT;
            this->setCursor(Qt::SizeFDiagCursor);
        }
        else if (x >= left&& x <= left + PADDING
                 && y >= top&& y <= bottom) {
            dir = LEFT;
            this->setCursor(Qt::SizeHorCursor);
        }
        else if (x >= right - PADDING && x <= right
                 && y >= top&& y <= bottom) {
            dir = RIGHT;
            this->setCursor(Qt::SizeHorCursor);
        }
        else if (y >= top && y <= top + PADDING
                 && x >= left && x <= right) {
            dir = TOP;
            this->setCursor(Qt::SizeVerCursor);
        }
        else if (y >= bottom - PADDING && y <= bottom
                 && x >= left && x <= right) {
            dir = BOTTOM;
            this->setCursor(Qt::SizeVerCursor);
        }
    }
    if (dir != DEFAULT && !inResize) {
        inResize = true, emit enterResize();
    }
    else if (dir == DEFAULT && inResize) {
        inResize = false, emit leaveResize();
    }
    if (dir == DEFAULT && y <= top + MOVEHEIGHT && y >= top) {
        dir = MOVE;
        this->setCursor(Qt::ArrowCursor);
    }
    else if (dir == DEFAULT) {
        this->setCursor(Qt::ArrowCursor);
    }
}

void TranslucentWidget::mousePressEvent(QMouseEvent *event){
    // event->globalPos() 鼠标按下时，鼠标相对于整个屏幕位置
    // this->pos() 鼠标按下时，窗口相对于整个屏幕位置
    // event->globalPos() - this->pos() 鼠标相对于窗口的位置
    if (event != nullptr && event->button() == Qt::LeftButton)
        isLeftPressing = true;
    m_movePoint = event->globalPos() - this->geometry().topLeft();
    if (!focus && smallGeometry().contains(event->globalPos())){
        emit focusInMyEvent();
    }
    else{
        emit focusOutMyEvent();
    }
}

void TranslucentWidget::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isLeftPressing = false;
}

void TranslucentWidget::mouseMoveEvent(QMouseEvent *event){
    QPoint globalPoint = event->globalPos();
    int minH = minimumHeight()-2*OVER, minW = minimumWidth()-2*OVER;

    if (focus && !smallGeometry().contains(event->globalPos())) {
        emit focusOutMyEvent();
    }
    if (!isLeftPressing) {
        region(globalPoint);
        return;
    }
    QRect newRect = this->smallGeometry();
    if (dir != MOVE) {
        switch (dir) {
        case TOP_LEFT:
            if (newRect.bottom() - globalPoint.y() > minH &&
                    newRect.right() - globalPoint.x() > minW) {
                newRect.setTopLeft(globalPoint);
            }
            else if (newRect.bottom() - globalPoint.y() > minH) {
                newRect.setTop(globalPoint.y());
            }
            else if (newRect.right() - globalPoint.x() > minW) {
                newRect.setLeft(globalPoint.x());
            }
            break;
        case TOP_RIGHT:
            if (newRect.bottom() - globalPoint.y() <= minH) {
                newRect.setRight(globalPoint.x());
            }
            else {
                newRect.setTopRight(globalPoint);
            }
            break;
        case BOTTOM_LEFT:
            if (newRect.right() - globalPoint.x() <= minW){
                newRect.setBottom(globalPoint.y());
            }
            else {
                newRect.setBottomLeft(globalPoint);
            }
            break;
        case BOTTOM_RIGHT:
            newRect.setBottomRight(globalPoint);
            break;
        case TOP:
            if (newRect.bottom() - globalPoint.y() > minH) {
                newRect.setTop(globalPoint.y());
            }
            break;
        case BOTTOM:
            newRect.setBottom(globalPoint.y());
            break;
        case LEFT:
            if (newRect.right() - globalPoint.x() > minW) {
                newRect.setLeft(globalPoint.x());
            }
            break;
        case RIGHT:
            newRect.setRight(globalPoint.x());
            break;
        default:
            break;
        }
        this->setSmallGeometry(newRect);
    }
    //else if (dir != DEFAULT) {
    if (!moveLocked)
        // 通过事件event->globalPos()知道鼠标坐标
        // 鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
        move(globalPoint - m_movePoint);
    else
        emit tryLockedMove();
    //}
}

TranslucentWidget::~TranslucentWidget() {
    delete [] m_pAct;
}

