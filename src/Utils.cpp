#include "Utils.hpp"
#include <string>
#include <vector>
#include <list>
#include <array>
#include "Eigen/Eigen"
#include <cmath>
#include <cassert>
#include <limits>

using namespace std;
using namespace Eigen;
void Normalizzazione(auto& arr) {
	double distanza = sqrt(arr[0]*arr[0]+ arr[1]*arr[1] + arr[2]*arr[2]);
	arr[0] = arr[0]/distanza;
	arr[1] = arr[1]/distanza;
	arr[2] = arr[2]/distanza;
	
}

namespace PolyhedronLibrary
{	
int Duplicato(PolyhedronMesh& mesh, auto& arr){
	double eps = std::numeric_limits<double>::epsilon();
	int a = -1;

	for (unsigned int i =0; i<NumCell0Ds; i++){
		if ((arr[0] - mesh.Cell0DsCoordinates(i,0)) < eps){
			if ((arr[1] - mesh.Cell0DsCoordinates(i,1)) < eps){
				if ((arr[2] - mesh.Cell0DsCoordinates(i,2)) < eps){
					int a = Cell0DsId[i];				
			}
		}	
	}
	
}
return a;
}


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
		faces.push_back(mesh.NumCell2Ds);
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



	bool Ottaedro(PolyhedronMesh& mesh){   // passaggio per riferimento per modificare la mesh

	vector <int> vertices;
	vector <int> edges;
	vector <int> faces;

	// Celle 0Ds
	int exNumCell0Ds = mesh.NumCell0Ds;

	for (unsigned int i = 0; i < 6; i++) {
		mesh.Cell0DsId.push_back(mesh.NumCell0Ds);
		vertices.push_back(mesh.NumCell0Ds);
		mesh.NumCell0Ds++;
	}
	mesh.Cell0DsCoordinates.conservativeResize(mesh.NumCell0Ds,3);
	
	double p1[3]={1,0,0};
	double p2[3]={0,1,0};
	double p3[3]={-1,0,0};
	double p4[3]={0,-1,0};
	double p5[3]={0,0,1};
	double p6[3]={0,0,-1};
	
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
	for (unsigned int i = 0; i<3;i++){
		mesh.Cell0DsCoordinates(exNumCell0Ds +4, i) = p5[i];
	}
	for (unsigned int i = 0; i<3;i++){
		mesh.Cell0DsCoordinates(exNumCell0Ds +5, i) = p6[i];
	}
	// Celle 1Ds
	
	int exNumCell1Ds = mesh.NumCell1Ds;

	for (unsigned int i = 0; i < 12; i++) {
		mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
		edges.push_back(mesh.NumCell1Ds);
		mesh.NumCell1Ds++;
	}
	
	mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
	
	Matrix<int,12,2>matedges;
	matedges <<0,1,
	1,2,
	2,3,
	3,0,
	0,4,
	1,4,
	2,4,
	3,4,
	0,5,
	1,5,
	2,5,
	3,5;

	for (unsigned int i=0;i<12;i++){
		for (unsigned int j=0;j<2;j++){
			mesh.Cell1DsExtrema(exNumCell1Ds+i,j)=matedges(i,j);
		}
	}


	// Celle 2Ds
	
	for (unsigned int i = 0; i < 8; i++) {
		mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
		faces.push_back(mesh.NumCell2Ds);
		mesh.Cell2DsNumVert.push_back(3);
		mesh.Cell2DsNumEdg.push_back(3);
		mesh.NumCell2Ds++;
	}
	
	vector <int> faccia0vert = {0, 1, 4};
	vector <int> faccia0edg = {0, 5, 4};
	mesh.Cell2DsVertices.push_back(faccia0vert);
	mesh.Cell2DsEdges.push_back(faccia0edg);
	vector <int> faccia1vert = {1, 2, 4};
	vector <int> faccia1edg = {1, 6, 5};
	mesh.Cell2DsVertices.push_back(faccia1vert);
	mesh.Cell2DsEdges.push_back(faccia1edg);
	vector <int> faccia2vert = {2, 3, 4};
	vector <int> faccia2edg = {2, 7, 6};
	mesh.Cell2DsVertices.push_back(faccia2vert);
	mesh.Cell2DsEdges.push_back(faccia2edg);
	vector <int> faccia3vert = {3, 0, 4};
	vector <int> faccia3edg = {3, 4, 7};
	mesh.Cell2DsVertices.push_back(faccia3vert);
	mesh.Cell2DsEdges.push_back(faccia3edg);
	vector <int> faccia4vert = {0, 1, 5};
	vector <int> faccia4edg = {0, 9, 8};
	mesh.Cell2DsVertices.push_back(faccia4vert);
	mesh.Cell2DsEdges.push_back(faccia4edg);
	vector <int> faccia5vert = {1, 2, 5};
	vector <int> faccia5edg = {1, 10, 9};
	mesh.Cell2DsVertices.push_back(faccia5vert);
	mesh.Cell2DsEdges.push_back(faccia5edg);
	vector <int> faccia6vert = {2, 3, 5};
	vector <int> faccia6edg = {2, 11, 10};
	mesh.Cell2DsVertices.push_back(faccia6vert);
	mesh.Cell2DsEdges.push_back(faccia6edg);
	vector <int> faccia7vert = {3, 0, 5};
	vector <int> faccia7edg = {3, 8, 11};
	mesh.Cell2DsVertices.push_back(faccia7vert);
	mesh.Cell2DsEdges.push_back(faccia7edg);
	
	// Celle 3Ds
	
	mesh.NumCell3Ds +=1;
	mesh.Cell3DsId.push_back(mesh.NumCell3Ds);
	mesh.Cell3DsNumFaces.push_back(8);
	mesh.Cell3DsNumEdg.push_back(14);
	mesh.Cell3DsNumVert.push_back(6);
	mesh.Cell3DsVertices.push_back(vertices);
	mesh.Cell3DsEdges.push_back(edges);
	mesh.Cell3DsFaces.push_back(faces);	

	return true;
	}



	bool Icosaedro(PolyhedronMesh& mesh){   // passaggio per riferimento per modificare la mesh

	vector <int> vertices;
	vector <int> edges;
	vector <int> faces;

	// Celle 0Ds
	int exNumCell0Ds = mesh.NumCell0Ds;

	for (unsigned int i = 0; i < 12; i++) {
		mesh.Cell0DsId.push_back(mesh.NumCell0Ds);
		vertices.push_back(mesh.NumCell0Ds);
		mesh.NumCell0Ds++;
	}
	mesh.Cell0DsCoordinates.conservativeResize(mesh.NumCell0Ds,3);
	
	double phi=(1+sqrt(5.0))/2.0;
	Matrix<double,12,3>A;
	A<<0,1,phi,
	0,-1,phi,
	0,1,-phi,
	0,-1,-phi,
	1,phi,0,
	-1,phi,0,
	1,-phi,0,
	-1,-phi,0,
	phi,0,1,
	-phi,0,1,
	phi,0,-1,
	-phi,0,-1;

	double norma=sqrt(1.0+phi*phi);

	for (unsigned int i=0; i<12;i++){
		for (unsigned int j=0;j<3;j++){
			mesh.Cell0DsCoordinates(exNumCell0Ds+i,j)=A(i,j)/norma;
		}
	}

	
	// Celle 1Ds
	
	int exNumCell1Ds = mesh.NumCell1Ds;

	for (unsigned int i = 0; i < 30; i++) {
		mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
		edges.push_back(mesh.NumCell1Ds);
		mesh.NumCell1Ds++;
	}
	
	mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
	Eigen::MatrixXi B(30, 2);
B << 
  0, 1,
  0, 4,
  0, 5,
  0, 8,
  0, 9,
  1, 6,
  1, 7,
  1, 8,
  1, 9,
  2, 3,
  2, 4,
  2, 5,
  2,10,
  2,11,
  3, 6,
  3, 7,
  3,10,
  3,11,
  4, 5,
  4, 8,
  4,10,
  5, 9,
  5,11,
  6, 7,
  6, 8,
  6,10,
  7, 9,
  7,11,
  8,10,
  9,11;


 /*	check lunghezze
	for (unsigned int i=0;i<30;i++){
		for (unsigned int j=0;j<2;j++){
			mesh.Cell1DsExtrema(exNumCell1Ds+i,j)=B(i,j);
		}
		int b1= B(i,0);
		int b2 = B(i,1);
		double q=mesh.Cell0DsCoordinates(b1,0);
				double r=mesh.Cell0DsCoordinates(b2,0);
		double s=mesh.Cell0DsCoordinates(b1,1);
		double t=mesh.Cell0DsCoordinates(b2,1);
		double u=mesh.Cell0DsCoordinates(b1,2);
		double v=mesh.Cell0DsCoordinates(b2,2);

		
		cout<<i<<" "<<(q- r)*(q-r)+(s- t)*(s-t)+(u-v)*(u-v)	<<endl	;
	
	}
	
	*/

	// Celle 2Ds
	
	for (unsigned int i = 0; i < 20; i++) {
		mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
		faces.push_back(mesh.NumCell2Ds);
		mesh.Cell2DsNumVert.push_back(3);
		mesh.Cell2DsNumEdg.push_back(3);
		mesh.NumCell2Ds++;
	}
	
	
	//CONTROLLARE
	Matrix<int,20,3>C; //vertici
	C<<0, 1, 8,
    0, 4, 5,
    0, 5, 9,
    0, 8, 4,
    0, 9, 1,
    1, 6, 8,
    1, 7, 6,
    1, 9, 7,
    2, 3,10,
    2, 4, 5,
    2, 5,11,
    2,10, 4,
    2,11, 3,
    3, 6, 7,
    3,10, 6,
    3,11, 7,
    4, 8,10,
    5, 9,11,
    6, 8,10,
    7, 9,11;

	Matrix<int,20,3>D; //lati
	D<<0,  7,  3,   
	1,  2, 18,   
	2,  4, 28,  
	1,  3, 16,   
	0,  4,  8,   
	5,  7, 22,   
	5,  6, 21,   
	6,  8, 24,   
	9, 12, 16,   
	10, 11, 18,   
	11, 13, 20,   
	10, 12, 19,  
	13,  9, 17,   
	14, 15, 21,   
	14, 16, 23,   
	15, 17, 25,  
	3, 19, 27,   
	2,  4, 28,   
	22, 23, 27,   
	24, 25, 28;   
	
	for (unsigned int i=0;i<20;i++){
		vector<int> facciaedge;
		vector<int> facciavert;
		for (unsigned int j=0;j<3;j++){
			facciaedge.push_back(D(i,j));
			facciavert.push_back(C(i,j));
		}
		mesh.Cell2DsVertices.push_back(facciavert);
		mesh.Cell2DsEdges.push_back(facciaedge);
	}

	//CONTROLLARE
	// Celle 3Ds
	
	mesh.NumCell3Ds +=1;
	mesh.Cell3DsId.push_back(mesh.NumCell3Ds);
	mesh.Cell3DsNumFaces.push_back(20);
	mesh.Cell3DsNumEdg.push_back(30);
	mesh.Cell3DsNumVert.push_back(12);
	mesh.Cell3DsVertices.push_back(vertices);
	mesh.Cell3DsEdges.push_back(edges);
	mesh.Cell3DsFaces.push_back(faces);	

	return true;
}
	
	
	
bool Triangolazione(PolyhedronMesh& mesh, int b){ 
	
mesh.Cell2DsId.push_back(mesh.NumCell3Ds);
mesh.NumCell3Ds ++;

map<vector<int>, int> latiEsistenti;



	
int exNumCell0Ds = mesh.NumCell0Ds;
vector<int> facce = mesh.Cell3DsFaces[0];
for (unsigned int numerofaccia=0; numerofaccia<mesh.Cell3DsNumFaces[0],; i++) {// ciclo su ogni faccia
int faccia = facce[numerofaccia];
vector<int> latifaccia = mesh.Cell2DsEdges[faccia];
vector<int> verticifaccia= mesh.Cell2DsVertices[faccia];
Eigen::MatrixXd coordpunti;
for (unsigned int punto = 0; punto<3,; j++) {
	for (unsigned int coordinata = 0; coordinata < 3; coordinata ++) {
		coordpunti(punto, coordinata) = mesh.Cell0DsCoordinates(verticifaccia[punto], coordinata);
		}
}
vector<vector<int>> griglia;
griglia.reserve(b+1);

for (unsigned int i = 0; i<=b; i++) {
	vector<int> rigaGriglia;
	rigaGriglia.reserve(b-i+1);
	for (unsigned int j=0; j<=b-i; j++) {
		unsigned int k = b-i-j;
		double nuovax = (i*coordpunti[1,1]+j*coordpunti[2,1]+k*coordpunti[3,1])/b;
		double nuovay = (i*coordpunti[1,2]+j*coordpunti[2,2]+k*coordpunti[3,2])/b;
		double nuovaz = (i*coordpunti[1,3]+j*coordpunti[2,3]+k*coordpunti[3,3])/b;
		int nuovopunto[3] = {nuovax, nuovay, nuovaz};
		Normalizzazione(nuovopunto);
		
		int a = Duplicato(mesh,nuovopunto);
		if (a == -1) {
			a = mesh.NumCell0Ds;		
			mesh.Cell0DsId.push_back(a);
			mesh.NumCell0Ds++;
			mesh.Cell0DsCoordinates.conservativeResize(mesh.NumCell0Ds,3);
			for (unsigned int j=0;j<3;j++)
			mesh.Cell0DsCoordinates(NumCell0Ds-1,j)=nuovopunto[j];
		
	}
	rigaGriglia.push_back(a);
	
		}
		griglia.push_back(rigaGriglia);
		
		
}// fine cilco dei vertici

for (unsigned int i = 0; i <b; i++){
	for (unsigned int j = 0; j < b-i; j++){
		int a = griglia[i][j];
		int b = griglia[i][j+1];
		int c = griglia[i+1][j];
		
		if (a>b)
			vector<int> v1 = {a,b};
		else
			vector<int> v1 = {b,a};
		

		auto result = latiEsistenti.insert({v1, mesh.NumCell1Ds});
if (result.second) {
	mesh.NumCell1Ds++;
	
} else {
    std::cout << "Chiave già presente\n";
}
		
		
		
	}
}






}// fine ciclo faccia
}

}
	}
	
	
	
	
}