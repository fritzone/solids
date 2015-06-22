#ifndef MAINDWIDGET_H
#define MAINDWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVTKWidget.h>

#include "controlform.h"

class IcosahedronHolder;

class MaindWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MaindWidget(IcosahedronHolder *ich, QWidget *parent = 0);
    ~MaindWidget() = default;

public slots:

    void onQuit();

private:

    QWidget* mainWidget;
    QVTKWidget* vtkWidget;
    ControlForm* controls;

    QHBoxLayout *vtkWidgetHolderLayout;
    QHBoxLayout *mainFormLayout;

    IcosahedronHolder* ich;
};

#endif // MAINDWIDGET_H
