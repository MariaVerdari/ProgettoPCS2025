#pragma once
#include "PolyhedronMesh.hpp"

using namespace std;

void Normalizzazione(auto& arr);



namespace PolyhedronLibrary {
	bool Tetraedro(PolyhedronMesh& mesh);
	bool Ottaedro(PolyhedronMesh& mesh);
	bool Icosaedro(PolyhedronMesh& mesh);
	bool Triangolazione(PolyhedronMesh& mesh, int b); 
	int Duplicato(PolyhedronMesh& mesh, auto& arr);
	void writeCell0Ds(const PolyhedronMesh& mesh, const string& filename);
	void writeCell1Ds(const PolyhedronMesh& mesh, const string& filename);
	void writeCell2Ds(const PolyhedronMesh& mesh, const string& filename);
	void writeCell3Ds(const PolyhedronMesh& mesh, const string& filename);


}

	