#include "stickynotes.h"
#include "settingsui.h"
#include <QApplication>

int main(int argc, char *argv[]){
    // 解决Qt在Retina屏幕上图片模糊问题
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    // 解决Qt在Retina屏幕上显示问题
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    StickyNotes w;
    w.show();
    return a.exec();
}
