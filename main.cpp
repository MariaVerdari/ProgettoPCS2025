#include "Utils.hpp"
#include "PolyhedronMesh.hpp"
#include "UCDUtilities.hpp"
#include <iostream>

using namespace std;
using namespace Eigen;
using namespace PolyhedronLibrary;

int main() {
    PolyhedronMesh mesh;
    if (!Ottaedro(mesh))
    {
        cerr << "errore"<< endl;
        return 1;
    }
	
if (!Triangolazione(mesh, 4))
	{
        cerr << "errore triangolazione"<< endl;
        return 1;
    }
	

/*
for (unsigned int i=0; i<mesh.NumCell0Ds; i++){
	for (unsigned int j=0; j<3; j++) {
		cout<< mesh.Cell0DsCoordinates(i,j)<<" ";
	}
	cout<<endl;
}

for (unsigned int i=0; i<mesh.NumCell1Ds; i++){
	for (unsigned int j=0; j<2; j++) {
		cout<< mesh.Cell1DsExtrema(i,j)<<" ";
	}
	cout<<endl;
}

for (auto& el : mesh.Cell2DsVertices){
	for (auto n :el) {
		cout<< n<<" ";
	}
	cout<<endl;
}
cout<<mesh.NumCell0Ds;
*/


/// Per visualizzare online le mesh:
    /// 1. Convertire i file .inp in file .vtu con https://meshconverter.it/it
    /// 2. Caricare il file .vtu su https://kitware.github.io/glance/app/

    Gedim::UCDUtilities utilities;
    {
        vector<Gedim::UCDProperty<double>> cell0Ds_properties(1);

        cell0Ds_properties[0].Label = "Marker";
        cell0Ds_properties[0].UnitLabel = "-";
        cell0Ds_properties[0].NumComponents = 1;

        vector<double> cell0Ds_marker(mesh.NumCell0Ds, 0.0);
        for(const auto &m : mesh.Cell0DsMarker)
            for(const unsigned int id: m.second)
                cell0Ds_marker.at(id) = m.first;

        cell0Ds_properties[0].Data = cell0Ds_marker.data();

        utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates.transpose(),
                               {});
    }

    {

        vector<Gedim::UCDProperty<double>> cell1Ds_properties(1);

        cell1Ds_properties[0].Label = "Marker";
        cell1Ds_properties[0].UnitLabel = "-";
        cell1Ds_properties[0].NumComponents = 1;

        vector<double> cell1Ds_marker(mesh.NumCell1Ds, 0.0);
        for(const auto &m : mesh.Cell1DsMarker)
            for(const unsigned int id: m.second)
                cell1Ds_marker.at(id) = m.first;

        cell1Ds_properties[0].Data = cell1Ds_marker.data();

        utilities.ExportSegments("./Cell1Ds.inp",
                                 mesh.Cell0DsCoordinates.transpose(),
                                 mesh.Cell1DsExtrema.transpose(),
                                 {},
									 {});
    }


return 0;


}