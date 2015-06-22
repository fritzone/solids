#include "autorotator.h"
#include "controlform.h"
#include "icosahedron.h"

AutoRotator::AutoRotator(IcosahedronHolder *pich) : ich(pich), alive(true),
    rotX(1), rotY(1), rotZ(1)
{
}

void AutoRotator::process()
{
    while(alive)
    {
        ich->actor()->RotateX(rotX);
        ich->actor()->RotateY(rotY);
        ich->actor()->RotateZ(rotZ);
        ich->window()->Render();

        ControlForm::waitForSomeTime(10);
    }

    emit finished();
}
bool AutoRotator::isAlive() const
{
    return alive;
}

void AutoRotator::stop()
{
    alive = false;

    thread()->quit();
}

void AutoRotator::toggleX()
{
    rotX = !rotX;
}

void AutoRotator::toggleY()
{
    rotY = !rotY;
}

void AutoRotator::toggleZ()
{
    rotZ = !rotZ;
}

