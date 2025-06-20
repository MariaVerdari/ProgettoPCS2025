#include "Utils.hpp"
#include "PolyhedronMesh.hpp"
#include "UCDUtilities.hpp"
#include <iostream>
#include <fstream>
#include <list>

using namespace std;
using namespace Eigen;
using namespace PolyhedronLibrary;


	
int main(int argc, char *argv[]) //argc è numero di elementi passati incluso il programma: deve essere 5 o 7
{	
	PolyhedronMesh mesh;


	if (argc ==5){ 
	
		int quadrupla[4];
		for (unsigned int i = 0; i < argc-1; i++) { //mi assicuro che tutti gli interi siano validi
			istringstream convert(argv[i+1]);
			string altro;
			if (!(convert >> quadrupla[i])  || !(convert.eof())) { //no numeri con il punto
				cerr << "Errore: l'argomento '" << argv[i + 1] << "' non è un intero valido"<<endl;
				return 1;
			}
		}
		int p = quadrupla[0];
		int q = quadrupla[1];
		int b = quadrupla[2];
		int c = quadrupla[3];

		
		
		
		if (b==c){ // seconda classe
		cout<< "seconda classe b = c"<<endl;
		
			
			if (p == 3){
				
				switch(q) {
					case 3: //tetraedro
						if (!Tetraedro(mesh))
						{
							cerr << "Errore nella formazione del tetraedro"<< endl;
							return 1;
						}
						break;
													
						
						
	
	
	
					case 4: //ottaedro
						if (!Ottaedro(mesh))
						{
							cerr << "Errore nella formazione dell'ottaedro"<< endl;
							return 1;
						}
						break;

						
	
					

					case 5: //icosaedro
						if (!Icosaedro(mesh))
						{
							cerr << "Errore nella formazione dell'icosaedro"<< endl;
							return 1;
						}
						break;
					
					default:
					cerr << "Errore: l'argomento "<< q <<" non è valido: q può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
			
					// ALTRA TRIANGOLAZIONEEEE		

				
				
			
			} else if (q ==3) // duale
			{
				switch(p){
					
					case 4: //ottaedro
					break;
						
	
					

					case 5: //icosaedro
					break;
					
					default:
					cerr << "Errore: l'argomento "<< p <<" non è valido: p può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
			} else { //nessuno dei due casi
			cerr << "Errore: nessuno degli argomenti p e q è pari a 3"<<endl;
			return 1;
				
			}

		
			
		}
		else if (b == 0 || c == 0) { // prima classe
		if (b == 0)
			b = c;
		
			
			if (p == 3){
				
				switch(q) {
					case 3: //tetraedro
						if (!Tetraedro(mesh))
						{
							cerr << "Errore nella formazione del tetraedro"<< endl;
							return 1;
						}
						break;
													
						
						
	
	
	
					case 4: //ottaedro
						if (!Ottaedro(mesh))
						{
							cerr << "Errore nella formazione dell'ottaedro"<< endl;
							return 1;
						}
						break;

						
	
					

					case 5: //icosaedro
						if (!Icosaedro(mesh))
						{
							cerr << "Errore nella formazione dell'icosaedro"<< endl;
							return 1;
						}
						break;
					
					default:
					cerr << "Errore: l'argomento "<< q <<" non è valido: q può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
				if (!Triangolazione(mesh, b)) //triangolazione
							{
								cerr << "Errore nella triangolazione"<< endl;
								return 1;
							}
							

				
				
			
			} else if (q ==3) // duale
			{
				switch(p){
					
					case 4: //ottaedro
					break;
						
	
					

					case 5: //icosaedro
					break;
					
					default:
					cerr << "Errore: l'argomento "<< p <<" non è valido: p può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
			} else { //nessuno dei due casi
			cerr << "Errore: nessuno degli argomenti p e q è pari a 3"<<endl;
			return 1;
				
			}
			
		
		
		
		}
		else {// nessuno dei due casi
			cerr << "Errore: gli argomenti "<< b <<" e "<< c<<", ovvero b e c, sono diversi tra loro e nessuno dei due è pari a 0"<<endl;
			return 1;
		}

	
		
	}
	
	else if (argc == 7){ // cammino medio
	
	
	
		int sestupla[6];
		for (unsigned int i = 0; i < argc -1; i++) { //mi assicuro che tutti gli interi siano validi
			istringstream convert(argv[i+1]);
			if (!(convert >> sestupla[i])  || !(convert.eof())) { 
				cerr << "Errore: l'argomento '" << argv[i + 1] << "' non è un intero valido"<<endl;
				return 1;
			}
		}
		int p = sestupla[0];
		int q = sestupla[1];
		int b = sestupla[2];
		int c = sestupla[3];
		int v1 = sestupla[4];
		int v2 = sestupla[5];
		
		
	

	
	
	}
	
	else{
		cerr << "Errore: l'input può essere una quadrupla oppure una sestupla di numeri interi"<<endl;
		return(1);
	}
		

	
	for ( unsigned int i=0; i < mesh.Cell0DsVisibility.size() ; i++){
		list<unsigned int> lista = {i};
		auto result = (mesh.Cell0DsMarker).insert({mesh.Cell0DsVisibility[i],lista});
		if (!result.second){
			((*(result.first)).second).push_back(i);
		}
	}
	for ( unsigned int i=0; i < mesh.Cell1DsVisibility.size() ; i++){
		list<unsigned int> lista = {i};
		auto result = (mesh.Cell1DsMarker).insert({mesh.Cell1DsVisibility[i],lista});
		if (!result.second){
			((*(result.first)).second).push_back(i);
		}
	}
	for ( unsigned int i=0; i < mesh.Cell2DsVisibility.size() ; i++){
		list<unsigned int> lista = {i};
		auto result = (mesh.Cell2DsMarker).insert({mesh.Cell2DsVisibility[i],lista});
		if (!result.second){
			((*(result.first)).second).push_back(i);
		}
	}
	for ( unsigned int i=0; i < mesh.Cell3DsVisibility.size() ; i++){
		list<unsigned int> lista = {i};
		auto result = (mesh.Cell3DsMarker).insert({mesh.Cell3DsVisibility[i],lista});
		if (!result.second){
			((*(result.first)).second).push_back(i);
		}
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
	
	
	writeCell0Ds(mesh, "Cell0Ds.txt");
    writeCell1Ds(mesh, "Cell1Ds.txt");
    writeCell2Ds(mesh, "Cell2Ds.txt");
    writeCell3Ds(mesh, "Cell3Ds.txt");

    cout << "Output scritto in Cell0Ds.txt, Cell1Ds.txt, Cell2Ds.txt, Cell3Ds.txt\n";


return 0;


}