#pragma once
#include "PolyhedronMesh.hpp"

using namespace std;

void Normalizzazione(auto& arr);



namespace PolyhedronLibrary {
	void Tetraedro(PolyhedronMesh& mesh);
	void Ottaedro(PolyhedronMesh& mesh);
	void Icosaedro(PolyhedronMesh& mesh);
	void Triangolazione(PolyhedronMesh& mesh, int b);
	void Triangolazione2(PolyhedronMesh& mesh, int b);
	
	int Duplicato(PolyhedronMesh& mesh, auto& arr);
	
	void Duale (PolyhedronMesh& mesh);

	void writeCell0Ds(const PolyhedronMesh& mesh, const string& filename);
	void writeCell1Ds(const PolyhedronMesh& mesh, const string& filename);
	void writeCell2Ds(const PolyhedronMesh& mesh, const string& filename);
	void writeCell3Ds(const PolyhedronMesh& mesh, const string& filename);
	void creaMappa (PolyhedronMesh& mesh);
	void CreaMAMP(PolyhedronMesh& mesh, const int d);
	bool CamminoMinimo(const int v1, const int v2, vector<double>& dist,vector<int>& archi, vector<int>& pred, PolyhedronMesh& mesh);



	
	


}

	