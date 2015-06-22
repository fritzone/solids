#ifndef ICOSAHEDRON
#define ICOSAHEDRON

#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkImageViewer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkPlatonicSolidSource.h>
#include <QVTKWidget.h>
#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkObjectFactory.h>

#include <QObject>

class IcosahedronHolder : public QObject
{
    Q_OBJECT
public:
    IcosahedronHolder();

    vtkSmartPointer<vtkActor>& actor()
    {
        return icosahedronActor;
    }

    vtkSmartPointer<vtkRenderWindow>& window()
    {
        return renderWindow;
    }

private:

    vtkSmartPointer<vtkActor> icosahedronActor;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
};

#endif // ICOSAHEDRON

