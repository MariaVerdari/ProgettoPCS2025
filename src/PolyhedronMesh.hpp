#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolyhedronLibrary {

struct PolyhedronMesh 
{
	unsigned int NumCell0Ds = 0;
	unsigned int NumCell1Ds = 0;
	unsigned int NumCell2Ds = 0;
	unsigned int NumCell3Ds = 0;

	
	
	vector<int> Cell0DsId;
	Eigen::MatrixXd Cell0DsCoordinates; //  x e y e z 
	map<int, list<unsigned int>> Cell0DsMarker;

	vector<int> Cell0DsVisibility; 
	
	map<int, list<unsigned int>> MappaAdiacenza; //a ogni punto i suoi vicini
	vector<unsigned int> VerticiMA; // vertici di mappa adiacenza
	Eigen::MatrixXd MatricePesi; //  distanze tra vertici

	vector<int> camminov; //vertici cammino
	
	vector<int> Cell1DsId;
	Eigen::MatrixXi Cell1DsExtrema; // origin e end
	map<int, list<unsigned int>> Cell1DsMarker;

	vector<int> Cell1DsVisibility;

	vector<int> camminol; //lati cammino

	
	vector<int> Cell2DsId;
	vector<int> Cell2DsNumVert;
	vector<int> Cell2DsNumEdg;
	vector<vector<int>>	Cell2DsVertices;
	vector<vector<int>>	Cell2DsEdges;
	map<int, list< unsigned int>> Cell2DsMarker;

	vector<int> Cell2DsVisibility;
	
	
	vector<int> Cell3DsId;
	vector<int> Cell3DsNumVert;
	vector<int> Cell3DsNumEdg;
	vector<int> Cell3DsNumFaces;
	vector<vector<int>>	Cell3DsVertices;
	vector<vector<int>>	Cell3DsEdges;
	vector<vector<int>>	Cell3DsFaces;
	map<int,list<unsigned int>> Cell3DsMarker;

	vector<int> Cell3DsVisibility;
};

}

