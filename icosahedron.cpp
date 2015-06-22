#include "icosahedron.h"
#include <vtkPNGReader.h>
#include <vtkLookupTable.h>

IcosahedronHolder::IcosahedronHolder()
{
    // Create a new platonic solidsource object as being an icosahedron
    vtkNew<vtkPlatonicSolidSource> icosahedron;
    icosahedron->SetSolidTypeToIcosahedron();
    icosahedron->Update();

    // Create a color table for the icosahedron the color of it will be Red
    vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
    lut->SetNumberOfTableValues(1);
    lut->SetTableRange(0.0, 1);
    lut->SetTableValue(0.0, 1.0, 0.0, 0.0);
    lut->Build();

    // Mapper
    vtkSmartPointer<vtkPolyDataMapper> icosahedronMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    icosahedronMapper->SetInputConnection(icosahedron->GetOutputPort());
    icosahedronMapper->SetLookupTable(lut);
    icosahedronMapper->SetScalarRange(0.0, 1);

    // Create actor
    icosahedronActor = vtkSmartPointer<vtkActor>::New();
    icosahedronActor->SetMapper(icosahedronMapper);

    // Setup window
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    // Setup renderer
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(icosahedronActor);
    renderer->ResetCamera();

    // Connect renderer to the window
    renderWindow->AddRenderer(renderer);
}
