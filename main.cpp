#include "Utils.hpp"
#include "PolyhedronMesh.hpp"
#include "UCDUtilities.hpp"
#include <iostream>

using namespace std;
using namespace Eigen;
using namespace PolyhedronLibrary;

int main() {
    PolyhedronMesh mesh;
    if (!Tetraedro(mesh))
    {
        cerr << "errore"<< endl;
        return 1;
    }

for (unsigned int i=0; i<mesh.NumCell0Ds; i++){
	for (unsigned int j=0; j<3; j++) {
		cout<< mesh.Cell0DsCoordinates(i,j)<<" ";
	}
	cout<<endl;
}
return 0;


}