#include "maindwidget.h"
#include "icosahedron.h"
#include "controlform.h"

#include <QDebug>

MaindWidget::MaindWidget(IcosahedronHolder* mich, QWidget *parent) : QWidget(parent),
    mainWidget(new QWidget), vtkWidget(new QVTKWidget), ich(mich)
{
    controls = new ControlForm(ich);

    vtkWidgetHolderLayout = new QHBoxLayout();
    mainFormLayout = new QHBoxLayout(mainWidget);

    mainFormLayout->addLayout(vtkWidgetHolderLayout);

    controls->resize(200, 600);
    mainWidget->resize(640,480);

    vtkWidget->SetRenderWindow(ich->window());

    mainFormLayout->addWidget(vtkWidget);
    mainFormLayout->addWidget(controls);

    vtkWidget->show();
    controls->show();

    mainWidget->show();
}

void MaindWidget::onQuit()
{
    // If we don't shut down nicely the VTK stuff and the Qt threads
    // we get ugly printouts from the nouveu driver and sometimes even
    // a crash can happen
    controls->stop();
}

