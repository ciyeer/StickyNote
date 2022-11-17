#include "centerwidget.h"
#include "ui_centerwidget.h"
#include <QPushButton>
#include <QDir>
#include "commonhelper.h"

CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterWidget){
    ui->setupUi(this);
}

CenterWidget::~CenterWidget(){
    delete ui;
}
