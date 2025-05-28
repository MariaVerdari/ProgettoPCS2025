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



}

	