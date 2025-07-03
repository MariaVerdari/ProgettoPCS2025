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
	int d = 0; // prendo un numero d che mi dice quali sono quelli definitivi 


	if (argc == 5 || argc == 7){
		int quadrupla[4];
		for (unsigned int i = 0; i < 4; i++) { //mi assicuro che tutti gli interi siano validi
			istringstream convert(argv[i+1]);
			if (!(convert >> quadrupla[i])  || !(convert.eof())) { //no numeri con il punto
				cerr << "Errore: l'argomento '" << argv[i + 1] << "' non è un intero valido"<<endl;
				return 1;
			}
		}
		int p = quadrupla[0];
		int q = quadrupla[1];
		int b = quadrupla[2];
		int c = quadrupla[3];
		
		
		bool Cammino = false;
		if (argc == 7)
			Cammino = true;

			

		
		if (b==c){ // seconda classe
		
			
			if (p == 3){
				d = 1;
				
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
							
					if (!Triangolazione2(mesh, b)) //triangolazione 2
											{
												cerr << "Errore nella triangolazione"<< endl;
												return 1;
											}
											

								
				
			
			} else if (q ==3) // duale seconda classe
			{	d = 2;
				switch(p){
					
					case 4: //ottaedro
					if (!Ottaedro(mesh))
						{
							cerr << "Errore nella formazione dell'icosaedro"<< endl;
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
					cerr << "Errore: l'argomento "<< p <<" non è valido: p può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
				
				
				if (!Triangolazione2(mesh, b)) //triangolazione 2
														{
															cerr << "Errore nella triangolazione"<< endl;
															return 1;
														}
																		
				if (!Duale(mesh)) //duale
				{
					cerr << "Errore nella dualizzazione"<< endl;
					return 1;
				}
							
			} else { //nessuno dei due casi
			cerr << "Errore: nessuno degli argomenti p e q è pari a 3"<<endl;
			return 1;
				
			}

		
			
		}
		else if (b == 0 || c == 0) { // prima classe
		if (b == 0){
			b = c;
			c = 0;}
		
			
			if (p == 3){
				d = 1;
				
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
			{ d = 2;
				switch(p){
					
					case 4: //ottaedro
						if (!Ottaedro(mesh))
						{
							cerr << "Errore nella formazione dell'ottaedro"<< endl;
							return 1;
						}
						break;
					break;
						
	
					

					case 5: //icosaedro
						if (!Icosaedro(mesh))
						{
							cerr << "Errore nella formazione dell'ottaedro"<< endl;
							return 1;
						}
						break;
					break;
					
					default:
					cerr << "Errore: l'argomento "<< p <<" non è valido: p può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
				
				if (!Triangolazione(mesh, b)) //triangolazione
							{
								cerr << "Errore nella triangolazione"<< endl;
								return 1;
							}
				if (!Duale(mesh)) //duale
				{
					cerr << "Errore nella dualizzazione"<< endl;
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

	
		
	
if (Cammino){
			int v1;
			int v2;
			

			
			list<unsigned int> verticiValidi = mesh.Cell0DsMarker[d];

			istringstream convert(argv[5]);
			if (!(convert >> v1)  || !(convert.eof())) { //no numeri con il punto
				cerr << "Errore: l'argomento '" << argv[5] << "' non è un intero valido"<<endl;
				return 1;
			} else if (std::find(verticiValidi.begin(), verticiValidi.end(), v1) == verticiValidi.end()) {
				cerr << "Errore: il vertice '" << argv[5] << "' non è un vertice valido"<<endl;
				return 1;
				
			}
			
			istringstream convert1(argv[6]);
			if (!(convert1 >> v2)  || !(convert1.eof())) { //no numeri con il punto
				cerr << "Errore: l'argomento '" << argv[6] << "' non è un intero valido"<<endl;
				return 1;
			} else if (std::find(verticiValidi.begin(), verticiValidi.end(), v2) == verticiValidi.end()) {
				cerr << "Errore: il vertice '" << argv[6] << "' non è un vertice valido"<<endl;
				return 1;
				
			}
			
		double inf = std::numeric_limits<double>::infinity();
		vector<int> archi;
		vector<double> dist;
		vector<int> pred;
		CreaMAMP(mesh, d); // chiamo funzione per fare lista adiacenza e matrice pesi 
		if (!CamminoMinimo(v1,  v2,  dist, archi, pred, mesh)){
			cerr << "Errore: cammino minimo non trovato"<<endl;
			return 1;
		}
		auto itpos_v2 = std::find(mesh.VerticiMA.begin(), mesh.VerticiMA.end(), v2); //pos di v2
		int pos_v2= itpos_v2- mesh.VerticiMA.begin(); 
		cout<<"Il cammino minimo tra i vertici " << v1<< " e " <<v2<< " ha "<< archi[pos_v2]<<" lati e la somma delle loro lunghezze è "<< dist[pos_v2]<< endl;
		
		int corrente = v2;
		while (corrente != v1) {
			mesh.camminov.push_back(corrente);
			auto itposc = std::find(mesh.VerticiMA.begin(), mesh.VerticiMA.end(), corrente);

			int posc = itposc - mesh.VerticiMA.begin();
			corrente = pred[posc];
			

    }

    mesh.camminov.push_back(v1);
	int m = mesh.camminov.size();
	for (int i = 0; i< m-1; i++){
		int a =mesh.camminov[i];
		int b =mesh.camminov[i+1]; 
		for (unsigned int lato:mesh.Cell1DsMarker[d]){
			if ((mesh.Cell1DsExtrema(lato,0) == a && mesh.Cell1DsExtrema(lato,1) == b) || (mesh.Cell1DsExtrema(lato,1) == a && mesh.Cell1DsExtrema(lato,0) == b)){
				mesh.camminol.push_back(lato);
			}
		}

	}
		

		} // fine cammino
		

	}

	
	else{
		cerr << "Errore: l'input può essere una quadrupla oppure una sestupla di numeri interi"<<endl;
		return(1);
	}
		


    Gedim::UCDUtilities utilities;
    {
        vector<Gedim::UCDProperty<double>> cell0Ds_properties(2);

        cell0Ds_properties[0].Label = "Marker";
        cell0Ds_properties[0].UnitLabel = "-";
        cell0Ds_properties[0].NumComponents = 1;

        vector<double> cell0Ds_marker(mesh.NumCell0Ds, 0.0);
        for(const auto &m : mesh.Cell0DsMarker)
            for(const unsigned int id: m.second)
                cell0Ds_marker.at(id) = m.first;
			
		cell0Ds_properties[0].Data = cell0Ds_marker.data();

		vector<double> cell0Ds_cammino(mesh.NumCell0Ds, 0.0);

		for (int v : mesh.camminov) {
			cell0Ds_cammino[v] = 1.0;
		}

		
		cell0Ds_properties[1].Label = "ShortPath";
        cell0Ds_properties[1].UnitLabel = "-";
        cell0Ds_properties[1].NumComponents = 1;

		cell0Ds_properties[1].Data = cell0Ds_cammino.data();
		

		


        utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates.transpose(),
                               cell0Ds_properties);
    }

    {

        vector<Gedim::UCDProperty<double>> cell1Ds_properties(2);

        cell1Ds_properties[0].Label = "Marker";
        cell1Ds_properties[0].UnitLabel = "-";
        cell1Ds_properties[0].NumComponents = 1;

        vector<double> cell1Ds_marker(mesh.NumCell1Ds, 0.0);
        for(const auto &m : mesh.Cell1DsMarker)
            for(const unsigned int id: m.second)
                cell1Ds_marker.at(id) = m.first;

        cell1Ds_properties[0].Data = cell1Ds_marker.data();
		
		vector<double> cell1Ds_cammino(mesh.NumCell1Ds, 0.0);

		
		for (int e : mesh.camminol) {
			cell1Ds_cammino[e] = 1.0;
		}
		
		
		cell1Ds_properties[1].Label = "ShortPath";
        cell1Ds_properties[1].UnitLabel = "-";
        cell1Ds_properties[1].NumComponents = 1;

		cell1Ds_properties[1].Data = cell1Ds_cammino.data();



        utilities.ExportSegments("./Cell1Ds.inp",
                                 mesh.Cell0DsCoordinates.transpose(),
                                 mesh.Cell1DsExtrema.transpose(),
                                 {},
									 cell1Ds_properties);
    }
	
	
	writeCell0Ds(mesh, "Cell0Ds.txt");
    writeCell1Ds(mesh, "Cell1Ds.txt");
    writeCell2Ds(mesh, "Cell2Ds.txt");
    writeCell3Ds(mesh, "Cell3Ds.txt");

    cout << "Output scritto in Cell0Ds.txt, Cell1Ds.txt, Cell2Ds.txt, Cell3Ds.txt\n";


return 0;


}