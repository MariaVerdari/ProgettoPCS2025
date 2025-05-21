#include "Utils.hpp"
#include "PolyhedronMesh.hpp"
#include "UCDUtilities.hpp"
#include <iostream>

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main [
    PolyhedronMesh mesh;
    if (!Tetraedro(mesh))
    {
        cerr << "errore"<< endl;
        return 1;
    }

return 0;


]