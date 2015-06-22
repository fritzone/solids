#ifndef CONTROLFORM_H
#define CONTROLFORM_H

#include <QWidget>
#include <QThread>

#include <vtkProperty.h>

namespace Ui {
class ControlForm;
}

class IcosahedronHolder;
class AutoRotator;

class ControlForm : public QWidget
{
    Q_OBJECT

    typedef void (vtkProperty::*set_mode_fun)(void);

public:
    explicit ControlForm(IcosahedronHolder* pich, QWidget *parent = 0);
    ~ControlForm();

    static void waitForSomeTime(int);

    void stop();

public slots:

    // rotator thread slot
    void stopAutoRotation();

    // rotation slots
    void onManualRotation();
    void onAutomaticRotation();

    // Representation flags
    void onPoints();
    void onWireframe();
    void onSolid();

    // Opacity
    void onOpacityChange(int);

    // auto rotation axes slots
    void onAutoRotX();
    void onAutoRotY();
    void onAutoRotZ();

private:

    void restartRotation();
    void setDisplayMode(set_mode_fun);
    void waitForRotatorFullStop();


private:
    Ui::ControlForm *ui;
    IcosahedronHolder* ich;
    AutoRotator* rotator;
};

#endif // CONTROLFORM_H

