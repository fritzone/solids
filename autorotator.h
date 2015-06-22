#ifndef AUTOROTATOR_H
#define AUTOROTATOR_H

#include <QObject>

class IcosahedronHolder;

class AutoRotator : public QObject
{
    Q_OBJECT

public:
    AutoRotator(IcosahedronHolder* pich);
    ~AutoRotator() = default;

    bool isAlive() const;
    void stop();

    void toggleX();
    void toggleY();
    void toggleZ();

public slots:
    void process();

signals:
    void finished();

private:
    IcosahedronHolder* ich;
    bool alive;
    int rotX;
    int rotY;
    int rotZ;
};

#endif // AUTOROTATOR_H

