#include "Utils.hpp"
#include <string>
#include <vector>
#include <list>
#include <array>
#include "Eigen/Eigen"
#include <cmath>
#include <cassert>

using namespace std;

void Normalizzazione(auto& arr) {
	double distanza = sqrt(arr[0]*arr[0]+ arr[1]*arr[1] + arr[2]*arr[2]);
	arr[0] = arr[0]/distanza;
	arr[1] = arr[1]/distanza;
	arr[2] = arr[2]/distanza;
	
}

namespace PolyhedronLibrary
{	
bool Tetraedro(PolyhedronMesh& mesh){   // passaggio per riferimento per modificare la mesh

	vector <int> vertices;
	vector <int> edges;
	vector <int> faces;

	// Celle 0Ds
	int exNumCell0Ds = mesh.NumCell0Ds;

	for (unsigned int i = 0; i < 4; i++) {
		mesh.Cell0DsId.push_back(mesh.NumCell0Ds);
		vertices.push_back(mesh.NumCell0Ds);
		mesh.NumCell0Ds++;
	}
	mesh.Cell0DsCoordinates.conservativeResize(mesh.NumCell0Ds,3);
	
	double p1[3] = {0,0,0};
	double p2[3] = {1,0,0};
	double h1 = sqrt(1-0.5*0.5);
	double p3[3] = {0.5,h1,0};
	double a = (0+1+0.5)/3.0;
	double b = (0+0+h1)/3.0;
	double dist = sqrt(a*a + b*b);
	double h2 = sqrt(1-dist*dist);
	double p4[3] = {a,b,h2};
	double baricentro[3] = {a, b, h2/4.0};
	
	p1[0] -= baricentro[0] ;
	p2[0] -= baricentro[0] ;
	p3[0] -= baricentro[0] ;
	p4[0] -= baricentro[0] ;
	
	p1[1] -= baricentro[1] ;
	p2[1] -= baricentro[1] ;
	p3[1] -= baricentro[1] ;
	p4[1] -= baricentro[1] ;
	
	p1[2] -= baricentro[2] ;
	p2[2] -= baricentro[2] ;
	p3[2] -= baricentro[2] ;
	p4[2] -= baricentro[2] ;
	
	Normalizzazione(p1);
	Normalizzazione(p2);
	Normalizzazione(p3);
	Normalizzazione(p4);

	for (unsigned int i = 0; i<3;i++){
		mesh.Cell0DsCoordinates(exNumCell0Ds, i) = p1[i];
	}
	for (unsigned int i = 0; i<3;i++){
		mesh.Cell0DsCoordinates(exNumCell0Ds +1, i) = p2[i];
	}
	for (unsigned int i = 0; i<3;i++){
		mesh.Cell0DsCoordinates(exNumCell0Ds +2, i) = p3[i];
	}
	for (unsigned int i = 0; i<3;i++){
		mesh.Cell0DsCoordinates(exNumCell0Ds +3, i) = p4[i];
	}
	
	// Celle 1Ds
	
	int exNumCell1Ds = mesh.NumCell1Ds;

	for (unsigned int i = 0; i < 6; i++) {
		mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
		edges.push_back(mesh.NumCell1Ds);
		mesh.NumCell1Ds++;
	}
	
	mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
	unsigned int k = 0;
	for (unsigned int i = 0; i <4; i++) {
		for (unsigned int j = i+1 ; j <4; j++){
			mesh.Cell1DsExtrema(exNumCell1Ds+k, 0) = mesh.Cell0DsId[exNumCell0Ds+i];
			mesh.Cell1DsExtrema(exNumCell1Ds+k, 1) = mesh.Cell0DsId[exNumCell0Ds+j];
			k++;
		}
	}
	assert(k == 6);
	
	// Celle 2Ds
	
	for (unsigned int i = 0; i < 4; i++) {
		mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
		edges.push_back(mesh.NumCell2Ds);
		mesh.Cell2DsNumVert.push_back(3);
		mesh.Cell2DsNumEdg.push_back(3);
		mesh.NumCell2Ds++;
	}
	
	vector <int> faccia0vert = {0, 1, 3};
	vector <int> faccia0edg = {0, 4, 2};
	mesh.Cell2DsVertices.push_back(faccia0vert);
	mesh.Cell2DsEdges.push_back(faccia0edg);
	vector <int> faccia1vert = {0, 1, 2};
	vector <int> faccia1edg = {0, 3, 1};
	mesh.Cell2DsVertices.push_back(faccia1vert);
	mesh.Cell2DsEdges.push_back(faccia1edg);
	vector <int> faccia2vert = {1, 2, 3};
	vector <int> faccia2edg = {3, 5, 4};
	mesh.Cell2DsVertices.push_back(faccia2vert);
	mesh.Cell2DsEdges.push_back(faccia2edg);
	vector <int> faccia3vert = {2, 0, 3};
	vector <int> faccia3edg = {1, 2, 5};
	mesh.Cell2DsVertices.push_back(faccia3vert);
	mesh.Cell2DsEdges.push_back(faccia3edg);
	
	// Celle 3Ds
	
	mesh.NumCell3Ds +=1;
	mesh.Cell3DsId.push_back(mesh.NumCell3Ds);
	mesh.Cell3DsNumFaces.push_back(4);
	mesh.Cell3DsNumEdg.push_back(6);
	mesh.Cell3DsNumVert.push_back(4);
	mesh.Cell3DsVertices.push_back(vertices);
	mesh.Cell3DsEdges.push_back(edges);
	mesh.Cell3DsFaces.push_back(faces);	

	return true;
}
	
	
	
	
	
	
}