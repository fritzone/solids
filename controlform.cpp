#include "controlform.h"
#include "ui_controlform.h"
#include "icosahedron.h"
#include "autorotator.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include <QDebug>

ControlForm::ControlForm(IcosahedronHolder *pich, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlForm), ich(pich), rotator(nullptr)
{
    ui->setupUi(this);
}

ControlForm::~ControlForm()
{
    delete ui;
}

void ControlForm::stopAutoRotation()
{
    delete rotator;
    rotator = nullptr;
}

void ControlForm::onManualRotation()
{
    if(rotator)
    {
        rotator->stop();
        waitForRotatorFullStop();

        ui->grpAxes->setEnabled(false);
        ich->window()->GetInteractor()->Enable();
    }
}

void ControlForm::onAutomaticRotation()
{
    if(rotator == nullptr)
    {
        QThread* thread = new QThread;
        rotator = new AutoRotator(ich);
        rotator->moveToThread(thread);

        connect(thread, SIGNAL(started()), rotator, SLOT(process()) );
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        connect(rotator, SIGNAL(finished()), thread, SLOT(quit()));
        connect(rotator, SIGNAL(finished()), this, SLOT(stopAutoRotation()));

        thread->start();

        ui->grpAxes->setEnabled(true);
        ich->window()->GetInteractor()->Disable();
    }
}

void ControlForm::onPoints()
{
    setDisplayMode(&vtkProperty::SetRepresentationToPoints);
}

void ControlForm::onWireframe()
{
    setDisplayMode(&vtkProperty::SetRepresentationToWireframe);
}

void ControlForm::onSolid()
{
    setDisplayMode(&vtkProperty::SetRepresentationToSurface);
}

void ControlForm::onOpacityChange(int v)
{
    bool autorot = false;
    if(ui->rdoAutomatic->isChecked())
    {
        if(rotator)
        {
            rotator->stop();
            autorot = true;
        }
    }

    double value = static_cast<double>(v) /
            static_cast<double>(ui->sliderOpacity->maximum());

    ich->actor()->GetProperty()->SetOpacity(value);
    ich->window()->Render();

    if(autorot)
    {
        restartRotation();
    }
}

void ControlForm::onAutoRotX()
{
    if(rotator)
    {
        rotator->toggleX();
    }
}

void ControlForm::onAutoRotY()
{
    if(rotator)
    {
        rotator->toggleY();
    }
}

void ControlForm::onAutoRotZ()
{
    if(rotator)
    {
        rotator->toggleZ();
    }
}

void ControlForm::waitForSomeTime(int ms)
{
#ifdef Q_OS_WIN
    Sleep(uint(ms));
#else
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#endif
}

void ControlForm::stop()
{
    rotator->stop();
    waitForRotatorFullStop();
    ich->window()->Finalize();
}

void ControlForm::waitForRotatorFullStop()
{
    while(rotator != nullptr)
    {
        QCoreApplication::processEvents();
        waitForSomeTime(100);
    }
}

void ControlForm::restartRotation()
{
    waitForRotatorFullStop();
    onAutomaticRotation();
}

void ControlForm::setDisplayMode(ControlForm::set_mode_fun f)
{
    bool autorot = false;
    if(ui->rdoAutomatic->isChecked())
    {
        if(rotator)
        {
            rotator->stop();
            autorot = true;
        }
    }

    ((ich->actor()->GetProperty())->*f)();
    ich->window()->Render();

    if(autorot)
    {
        restartRotation();
    }
}
