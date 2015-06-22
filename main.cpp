#include <QApplication>
#include <QtGui/QHBoxLayout>

#include "controlform.h"
#include "icosahedron.h"
#include "maindwidget.h"

// Need this for XInitThreads
#ifdef Q_OS_LINUX
#include <X11/Xlib.h>
#endif

int main(int argc, char** argv)
{
    // Since this is (will be) a multithreaded application doing graphics
    // we need to ask X11 to be cooperant when it comes about rendering
#ifdef Q_OS_LINUX
    XInitThreads();
#endif

    QApplication app(argc, argv);

    // The icosahedron and its helping structures
    IcosahedronHolder* ich = new IcosahedronHolder;

    MaindWidget mainWidget(ich);

    QObject::connect(&app, SIGNAL(aboutToQuit()), &mainWidget, SLOT(onQuit()));

    app.exec();

    return EXIT_SUCCESS;
}
