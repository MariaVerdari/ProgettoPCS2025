#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolyhedronLibrary {

struct PolyhedronMesh
{
	unsigned int NumCell0Ds;
	unsigned int NumCell1Ds;
	unsigned int NumCell2Ds;
	unsigned int NumCell3Ds;

	
	
	vector<int> Cell0DsId;
	Eigen::MatrixXd Cell0DsCoordinates; //  x e y e z 
	map<int, list<int>> Cell0DsMarker;

	vector<int> Cell0DsVisibility; 
	
	vector<int> Cell1DsId;
	Eigen::MatrixXi Cell1DsExtrema; // origin e end
	map<int, list<int>> Cell1DsMarker;

	vector<int> Cell1DsVisibility;

	
	vector<int> Cell2DsId;
	vector<int> Cell2DsNumVert;
	vector<int> Cell2DsNumEdg;
	vector<vector<int>>	Cell2DsVertices;
	vector<vector<int>>	Cell2DsEdges;
	map<int, list<int>> Cell2DsMarker;

	vector<int> Cell2DsVisibility;
	
	
	vector<int> Cell3DsId;
	vector<int> Cell3DsNumVert;
	vector<int> Cell3DsNumEdg;
	vector<int> Cell3DsNumFaces;
	vector<vector<int>>	Cell3DsVertices;
	vector<vector<int>>	Cell3DsEdges;
	vector<vector<int>>	Cell3DsFaces;
	map<int,list<int>> Cell3DsMarker;

	vector<int> Cell3DsVisibility;

};

}

