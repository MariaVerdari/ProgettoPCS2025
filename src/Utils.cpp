  #include "Utils.hpp"
#include <string>
#include <vector>
#include <list>
#include <array>
#include "Eigen/Eigen"
#include <cmath>
#include <cassert>
#include <limits>
#include <map>
#include <set>
#include<iostream>
#include <fstream>
#include <algorithm>
#include <queue>


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

    for (unsigned int i =0; i<mesh.NumCell0Ds; i++) {
        if(fabs(arr[0] - mesh.Cell0DsCoordinates(i,0)) < eps && fabs(arr[1] - mesh.Cell0DsCoordinates(i,1)) < eps && fabs(arr[2] - mesh.Cell0DsCoordinates(i,2)) < eps){
                    a = mesh.Cell0DsId[i];              
            }
        }   
    
    

return a;
}


void Tetraedro(PolyhedronMesh& mesh){   // passaggio per riferimento per modificare la mesh

    vector <int> vertices;
    vector <int> edges;
    vector <int> faces;

    // Celle 0Ds
    int exNumCell0Ds = mesh.NumCell0Ds;

    for (unsigned int i = 0; i < 4; i++) {
        mesh.Cell0DsId.push_back(mesh.NumCell0Ds);
        vertices.push_back(mesh.NumCell0Ds);
        mesh.Cell0DsVisibility.push_back(0); 
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
        mesh.Cell1DsVisibility.push_back(0);
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
        mesh.Cell2DsVisibility.push_back(0);
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
    
    mesh.Cell3DsId.push_back(mesh.NumCell3Ds);
    mesh.NumCell3Ds +=1;
    mesh.Cell3DsNumFaces.push_back(4);
    mesh.Cell3DsNumEdg.push_back(6);
    mesh.Cell3DsNumVert.push_back(4);
    mesh.Cell3DsVertices.push_back(vertices);
    mesh.Cell3DsEdges.push_back(edges);
    mesh.Cell3DsFaces.push_back(faces); 

    mesh.Cell3DsVisibility.push_back(0);
	creaMappa ( mesh);

}



    void Ottaedro(PolyhedronMesh& mesh){   // passaggio per riferimento per modificare la mesh

    vector <int> vertices;
    vector <int> edges;
    vector <int> faces;

    // Celle 0Ds
    int exNumCell0Ds = mesh.NumCell0Ds;
    for (unsigned int i = 0; i < 6; i++) {
        mesh.Cell0DsId.push_back(mesh.NumCell0Ds);
        vertices.push_back(mesh.NumCell0Ds);
        mesh.Cell0DsVisibility.push_back(0); 
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
        mesh.Cell1DsVisibility.push_back(0); 
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
        mesh.Cell2DsVisibility.push_back(0); 
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
    
    
    mesh.Cell3DsId.push_back(mesh.NumCell3Ds);
    mesh.NumCell3Ds +=1;
    mesh.Cell3DsNumFaces.push_back(8);
    mesh.Cell3DsNumEdg.push_back(12);
    mesh.Cell3DsNumVert.push_back(6);
    mesh.Cell3DsVertices.push_back(vertices);
    mesh.Cell3DsEdges.push_back(edges);
    mesh.Cell3DsFaces.push_back(faces); 

    mesh.Cell3DsVisibility.push_back(0);
	creaMappa ( mesh);

    }



    void Icosaedro(PolyhedronMesh& mesh){   // passaggio per riferimento per modificare la mesh

    vector <int> vertices;
    vector <int> edges;
    vector <int> faces;

    // Celle 0Ds
    int exNumCell0Ds = mesh.NumCell0Ds;

    for (unsigned int i = 0; i < 12; i++) {
        mesh.Cell0DsId.push_back(mesh.NumCell0Ds);
        vertices.push_back(mesh.NumCell0Ds);
        mesh.Cell0DsVisibility.push_back(0); 
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
        mesh.Cell1DsVisibility.push_back(0); 
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

for (unsigned int i=0;i<30;i++){
        for (unsigned int j=0;j<2;j++){
            mesh.Cell1DsExtrema(exNumCell1Ds+i,j)=B(i,j);
        }
    }



    // Celle 2Ds
    
    for (unsigned int i = 0; i < 20; i++) {
        mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
        faces.push_back(mesh.NumCell2Ds);
        mesh.Cell2DsNumVert.push_back(3);
        mesh.Cell2DsNumEdg.push_back(3);
        mesh.Cell2DsVisibility.push_back(0); 
        mesh.NumCell2Ds++;
    }
    
    
    Matrix<int,20,3>C; //facce in tremini dei vertici
    C <<
    0, 1, 8,
    0, 4, 5,
    0, 5, 9,
    0, 4, 8,
    0, 9, 1,
    
    1, 6, 8,
    1, 9, 7,
    1, 6, 7,
    2, 3, 10,
    2, 4, 5,
    
    2, 4, 10,
    2, 5, 11,
    2, 11, 3,
    3, 6, 7,
    3, 6, 10,
    
    3, 7, 11,
    4, 8, 10,
    5, 9, 11,
    6, 8, 10,
    7, 9, 11;






Matrix<int,20,3>D; // facce in termini dei lati
    D<<
  0,  7,  3,
  1, 18,  2,
  2, 21,  4,
  1, 19,  3,
  4,  8,  0, //
  
  5, 24,  7,
  8, 26,  6,
  5, 23,  6,
  9, 16, 12, //
 10, 18, 11,
 
 10, 20, 12,
 11, 22, 13,
 13, 17,  9,
 14, 23, 15,
 14, 25, 16,
 
 15, 27, 17,
 19, 28, 20,
 21, 29, 22,
 24, 28, 25,
 26, 29, 27;


    

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

    // Celle 3Ds
    
    
    mesh.Cell3DsId.push_back(mesh.NumCell3Ds);
    mesh.NumCell3Ds +=1;
    mesh.Cell3DsNumFaces.push_back(20);
    mesh.Cell3DsNumEdg.push_back(30);
    mesh.Cell3DsNumVert.push_back(12);
    mesh.Cell3DsVertices.push_back(vertices);
    mesh.Cell3DsEdges.push_back(edges);
    mesh.Cell3DsFaces.push_back(faces); 

    mesh.Cell3DsVisibility.push_back(0);
	creaMappa ( mesh);

}
    
    
    
void Triangolazione(PolyhedronMesh& mesh, int b){ 
    set <int> verticitr;
    
mesh.Cell3DsId.push_back(mesh.NumCell3Ds);
mesh.NumCell3Ds ++;

mesh.Cell3DsVisibility.push_back(1);

map<vector<int>, int> latiEsistenti;
vector <int> faccetr;

vector<int> facce = mesh.Cell3DsFaces[0];
for (unsigned int numerofaccia=0; numerofaccia<mesh.Cell3DsNumFaces[0]; numerofaccia++) {// ciclo su ogni faccia
int faccia = facce[numerofaccia];
vector<int> latifaccia = mesh.Cell2DsEdges[faccia];
vector<int> verticifaccia= mesh.Cell2DsVertices[faccia];
MatrixXd coordpunti(3,3);


for (unsigned int punto = 0; punto<3; punto++) {
    for (unsigned int coordinata = 0; coordinata < 3; coordinata++) {
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
        double nuovax = (i*coordpunti(0,0)+j*coordpunti(1,0)+k*coordpunti(2,0))/b;
        double nuovay = (i*coordpunti(0,1)+j*coordpunti(1,1)+k*coordpunti(2,1))/b;
        double nuovaz = (i*coordpunti(0,2)+j*coordpunti(1,2)+k*coordpunti(2,2))/b;
        double nuovopunto[3] = {nuovax, nuovay, nuovaz};
        Normalizzazione(nuovopunto);
        
        int a = Duplicato(mesh,nuovopunto);
        if (a == -1) {
            a = mesh.NumCell0Ds;        
            mesh.Cell0DsId.push_back(a);
            mesh.NumCell0Ds++;
            mesh.Cell0DsCoordinates.conservativeResize(mesh.NumCell0Ds,3);
            for (unsigned int ii=0;ii<3;ii++)
               mesh.Cell0DsCoordinates(mesh.NumCell0Ds-1,ii)=nuovopunto[ii];
			mesh.Cell0DsVisibility.push_back(1);
	
		}
		else {
			mesh.Cell0DsVisibility[a]=1;
		}
		rigaGriglia.push_back(a);
		verticitr.insert(a);
    
	}
	griglia.push_back(rigaGriglia);
	
	
}// fine cilco dei vertici
vector <int> v1;
vector <int> v2;
vector <int> v3;
vector <int> v4;
vector <int> v5;

for (unsigned int i = 0; i <b; i++){
    for (unsigned int j = 0; j < b-i; j++){
        int p1 = griglia[i][j];
        int p2 = griglia[i][j+1];
        int p3 = griglia[i+1][j];
        
        if (p1>p2)
            v1 = {p1,p2};
        else
            v1 = {p2,p1};
        
        int v1id;
        auto result = latiEsistenti.insert({v1, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v1id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v1[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v1[1];
            mesh.Cell1DsVisibility.push_back(1);

    
        } else {
            v1id=(*(result.first)).second;
        }
        if (p2>p3)
            v2 = {p2,p3};
        else
            v2 = {p3,p2};
        
        int v2id;
        result = latiEsistenti.insert({v2, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v2id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v2[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v2[1];
            mesh.Cell1DsVisibility.push_back(1);
    
        } else {
            v2id=(*(result.first)).second;
        }
        if (p1>p3)
            v3 = {p1,p3};
        else
            v3 = {p3,p1};
        int v3id;
        result = latiEsistenti.insert({v3, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v3id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v3[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v3[1];
            mesh.Cell1DsVisibility.push_back(1);
    
        } else {
            v3id=(*(result.first)).second;
        }//facce
        mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
        faccetr.push_back(mesh.NumCell2Ds);
        mesh.NumCell2Ds++;
        mesh.Cell2DsNumVert.push_back(3);
        mesh.Cell2DsNumEdg.push_back(3);
        vector <int> abc = {p1,p2,p3};
        mesh.Cell2DsVertices.push_back(abc);
        vector <int> v123 = {v1id,v2id,v3id};
        mesh.Cell2DsEdges.push_back(v123);
        mesh.Cell2DsVisibility.push_back(1);

        if (j!=b-i-1){//antagonista
            int p4 = griglia [i+1][j+1];
            if (p4>p2)
                v4 = {p4,p2};
            else
                v4 = {p2,p4};
            int v4id;
        result = latiEsistenti.insert({v4, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v4id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v4[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v4[1];
            mesh.Cell1DsVisibility.push_back(1);
        } else {
            v4id=(*(result.first)).second;
        }


            if (p4>p3)
                v5 = {p4,p3};
            else
                v5 = {p3,p4};

            int v5id;
        result = latiEsistenti.insert({v5, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v5id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v5[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v5[1];
            mesh.Cell1DsVisibility.push_back(1);
        } else {
            v5id=(*(result.first)).second;
        }//facce antagonista
        mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
        faccetr.push_back(mesh.NumCell2Ds);
        mesh.NumCell2Ds++;
        mesh.Cell2DsNumVert.push_back(3);
        mesh.Cell2DsNumEdg.push_back(3);
        vector <int> bdc = {p2,p4,p3};
        mesh.Cell2DsVertices.push_back(bdc);
        vector <int> v452 = {v4id,v5id,v2id};
        mesh.Cell2DsEdges.push_back(v452);
        mesh.Cell2DsVisibility.push_back(1);

        }//chiude if antagonista
        
    }
}


}// fine ciclo faccia
mesh.Cell3DsFaces.push_back(faccetr);
mesh.Cell3DsNumFaces.push_back(faccetr.size());
vector <int> latitr ;
latitr.reserve(latiEsistenti.size());
for (map <vector<int>, int>::iterator it=latiEsistenti.begin();it!=latiEsistenti.end();it++){
    latitr.push_back((*it).second);
}
mesh.Cell3DsEdges.push_back(latitr);
mesh.Cell3DsNumEdg.push_back(latitr.size());
vector <int> verticitriang;
verticitriang.reserve(verticitr.size());
for (int n:verticitr){
    verticitriang.push_back(n);
}
mesh.Cell3DsVertices.push_back(verticitriang);
mesh.Cell3DsNumVert.push_back(verticitriang.size());
creaMappa(mesh);




}



void Duale (PolyhedronMesh& mesh){
	vector<int> dualvert;
	vector<int> dualedg;
	vector<int> dualfaces;
    list <unsigned int> facce1 = mesh.Cell2DsMarker[1];
	

	
	
    map <int,int> bari;
    for (unsigned int faccia : facce1){ //ciclo sulle facce per il baricentro

        vector<int> verticifaccia1 = mesh.Cell2DsVertices[faccia];

        double nuovax = mesh.Cell0DsCoordinates(verticifaccia1[0],0)+mesh.Cell0DsCoordinates(verticifaccia1[1],0)+mesh.Cell0DsCoordinates(verticifaccia1[2],0);
        double nuovay = mesh.Cell0DsCoordinates(verticifaccia1[0],1)+mesh.Cell0DsCoordinates(verticifaccia1[1],1)+mesh.Cell0DsCoordinates(verticifaccia1[2],1);
        double nuovaz = mesh.Cell0DsCoordinates(verticifaccia1[0],2)+mesh.Cell0DsCoordinates(verticifaccia1[1],2)+mesh.Cell0DsCoordinates(verticifaccia1[2],2);
        nuovax = nuovax/3.0;
        nuovay = nuovay/3.0;
        nuovaz = nuovaz/3.0;
        double baricentro[3]={nuovax, nuovay, nuovaz};
        Normalizzazione (baricentro);
        mesh.Cell0DsId.push_back(mesh.NumCell0Ds);
		dualvert.push_back(mesh.NumCell0Ds);
        bari.insert({faccia,mesh.NumCell0Ds});
        mesh.NumCell0Ds++;
        mesh.Cell0DsVisibility.push_back(2);
        mesh.Cell0DsCoordinates.conservativeResize(mesh.NumCell0Ds,3);
            for (unsigned int j=0;j<3;j++)
               mesh.Cell0DsCoordinates(mesh.NumCell0Ds-1,j)=baricentro[j];
    }

    list <unsigned int> lati1 = mesh.Cell1DsMarker[1];    
    vector<int> latinuovi;
	latinuovi.reserve(lati1.size()) ;
    unsigned int i=0;
    for (unsigned int lato : lati1){ //ciclo sui lati per lati nuovi
        vector<int> faccecondivise;
        faccecondivise.reserve(2);
        for (unsigned int j = 0; j< mesh.Cell2DsEdges.size(); j++){
            if (find(mesh.Cell2DsEdges[j].begin(), mesh.Cell2DsEdges[j].end(), lato) !=mesh.Cell2DsEdges[j].end()){
				assert(mesh.Cell2DsVisibility[j]==1);
                faccecondivise.push_back(j);
            }
        }
        int p1 = bari [faccecondivise[0]];
        int p2 = bari [faccecondivise[1]];
		if (faccecondivise.size() != 2) {
		cerr << "più di due facce condivise " <<faccecondivise.size() << endl;
}

        mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
		dualedg.push_back(mesh.NumCell1Ds);
        latinuovi.push_back(mesh.NumCell1Ds);
        mesh.NumCell1Ds++;
        mesh.Cell1DsVisibility.push_back(2);
        mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
        mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=p1;
        mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=p2;
        i++;
    }

	list <unsigned int> vertici1 = mesh.Cell0DsMarker[1];
	for (unsigned int vertice : vertici1) {   // ciclo sui vertici per creare facce
	    vector<int> latifuturi;
		latifuturi.reserve(6);   //va bene anche per le facce da 4 o 5 lati
		vector<int> puntifuturi;
		puntifuturi.reserve(6);
		unsigned int k = 0;
		
		vector<int> latiaccettabili;
		latiaccettabili.reserve(6);
		for (unsigned int lato : lati1) {// troviamo i lati vecchi a cui il punto appartiene
			if (mesh.Cell1DsExtrema(lato,0)==vertice || mesh.Cell1DsExtrema(lato,1)==vertice) {
				latiaccettabili.push_back(latinuovi[k]);
			}
			k++;
		}
		int latonuovo = latiaccettabili[0]; //prendo il primo lato accettabile
		latifuturi.push_back(latonuovo);
		int id_punto = mesh.Cell1DsExtrema(latonuovo,1);
		puntifuturi.push_back(mesh.Cell1DsExtrema(latonuovo,0));
		int exlato = latonuovo;
		while (id_punto != mesh.Cell1DsExtrema(latonuovo,0)) {
			puntifuturi.push_back(id_punto);
			for (unsigned int id_lato : latiaccettabili) {
				if (mesh.Cell1DsExtrema(id_lato,0)==id_punto || mesh.Cell1DsExtrema(id_lato,1)==id_punto) {
					if (id_lato != exlato) {
						latifuturi.push_back(id_lato);
						exlato = id_lato;
						if (mesh.Cell1DsExtrema(id_lato,0)==id_punto) 
							id_punto = mesh.Cell1DsExtrema(id_lato, 1);
						else
							id_punto = mesh.Cell1DsExtrema(id_lato,0);
					break;
					}
				}
						
			}
		} //fine while

	mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
	dualfaces.push_back(mesh.NumCell2Ds);
	mesh.NumCell2Ds++;
	mesh.Cell2DsNumVert.push_back(puntifuturi.size());
	mesh.Cell2DsNumEdg.push_back(latifuturi.size());
	mesh.Cell2DsVertices.push_back(puntifuturi);
	mesh.Cell2DsEdges.push_back(latifuturi);
	mesh.Cell2DsVisibility.push_back(2);
	}

	mesh.Cell3DsId.push_back(mesh.NumCell3Ds);
	mesh.NumCell3Ds++;
	mesh.Cell3DsNumVert.push_back(dualvert.size());
	
	mesh.Cell3DsNumEdg.push_back(dualedg.size());
	mesh.Cell3DsNumFaces.push_back(dualfaces.size());
	mesh.Cell3DsVertices.push_back(dualvert);
	mesh.Cell3DsEdges.push_back(dualedg);
	mesh.Cell3DsFaces.push_back(dualfaces); 
	mesh.Cell3DsVisibility.push_back(2);

	creaMappa ( mesh);


}


	void writeCell0Ds(const PolyhedronMesh& mesh, const string& filename) {
    ofstream out(filename);
	out << "Id;Marker;X;Y;Z" << endl;
    for (unsigned i = 0; i < mesh.NumCell0Ds; i++) {
        out
          << mesh.Cell0DsId[i] << ";"
		  << mesh.Cell0DsVisibility[i] << ";"
          << mesh.Cell0DsCoordinates(i, 0) << ";"
          << mesh.Cell0DsCoordinates(i, 1) << ";"
          << mesh.Cell0DsCoordinates(i, 2) << endl;
    }
	}
	
	void writeCell1Ds(const PolyhedronMesh& mesh, const string& filename) {
    ofstream out(filename);
    out << "Id;Marker;Origin;End" << endl; 
    for (unsigned i = 0; i < mesh.NumCell1Ds; i++) {
        out
          << mesh.Cell1DsId[i] << ";"
		  << mesh.Cell1DsVisibility[i] << ";"
          << mesh.Cell1DsExtrema(i, 0) << ";"
          << mesh.Cell1DsExtrema(i, 1) << endl;
    }
	}
	
	void writeCell2Ds(const PolyhedronMesh& mesh, const string& filename) {
    ofstream out(filename);
    out << "Id;Marker;NumVertices;Vertices;NumEdges;Edges" << endl;
    for (unsigned i = 0; i < mesh.NumCell2Ds; i++) {
        out
          << mesh.Cell2DsId[i] << ";"
		  << mesh.Cell2DsVisibility[i] << ";"
          << mesh.Cell2DsNumVert[i] << ";";
        for (size_t j = 0; j < mesh.Cell2DsVertices[i].size(); j++) {
			out << " " << mesh.Cell2DsVertices[i][j];
		}
		out<< ";";
		out<< mesh.Cell2DsNumEdg[i] << ";";

		for (size_t j = 0; j < mesh.Cell2DsEdges[i].size(); j++) {
			out << " " << mesh.Cell2DsEdges[i][j];
		}
        out << endl;
    }
	}
	
	void writeCell3Ds(const PolyhedronMesh& mesh, const string& filename) {
    ofstream out(filename);
    out << "Id;Marker;NumVertices;Vertices;NumEdges;Edges;NumFaces;Faces" << endl;
    for (unsigned i = 0; i < mesh.NumCell3Ds; i++) {
        out
          << mesh.Cell3DsId[i] << ";"
		  << mesh.Cell3DsVisibility[i] << ";"
          << mesh.Cell3DsNumVert[i] << ";";
		
		for (size_t j = 0; j < mesh.Cell3DsVertices[i].size(); j++) {
			out << " " << mesh.Cell3DsVertices[i][j];
		} 
		out<< ";" << mesh.Cell3DsNumEdg[i] << ";";

		for (size_t j = 0; j < mesh.Cell3DsEdges[i].size(); j++) {
			out << " " << mesh.Cell3DsEdges[i][j];
		} 
		out<< ";" << mesh.Cell3DsNumFaces[i] << ";";

        for (size_t j = 0; j < mesh.Cell3DsFaces[i].size(); j++) {
			out << " " << mesh.Cell3DsFaces[i][j];
		}
        out << endl;
    }
	}
	
	
	
	void creaMappa (PolyhedronMesh& mesh){
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
	
	}





void Triangolazione2(PolyhedronMesh& mesh, int b){ 
    set <int> verticitr2;

	mesh.Cell3DsId.push_back(mesh.NumCell3Ds);
	mesh.NumCell3Ds ++;

	mesh.Cell3DsVisibility.push_back(1);

	map<vector<int>, int> latiEsistenti;  //per i lati della prima triangolazione, che verranno ignorati
	map<vector<int>, int> latiEsistenti2; //per i lati della seconda triangolazione
	vector <int> faccetr2;

	vector<int> facce = mesh.Cell3DsFaces[0]; //facce di partenza
	
	for (unsigned int numerofaccia=0; numerofaccia<mesh.Cell3DsNumFaces[0]; numerofaccia++) { // ciclo su ogni faccia
	
		int facciaex = facce[numerofaccia];
		vector<int> latifaccia = mesh.Cell2DsEdges[facciaex];
		
		vector<int> verticifaccia= mesh.Cell2DsVertices[facciaex];
		
		map<vector<int>, int> facceSet; //per le facce della seconda triangolazione


		MatrixXd coordpunti(3,3);
		for (unsigned int punto = 0; punto<3; punto++) {
				for (unsigned int coordinata = 0; coordinata < 3; coordinata++) {
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
			double nuovax = (i*coordpunti(0,0)+j*coordpunti(1,0)+k*coordpunti(2,0))/b;
			double nuovay = (i*coordpunti(0,1)+j*coordpunti(1,1)+k*coordpunti(2,1))/b;
			double nuovaz = (i*coordpunti(0,2)+j*coordpunti(1,2)+k*coordpunti(2,2))/b;
			double nuovopunto[3] = {nuovax, nuovay, nuovaz};
			//Normalizzazione(nuovopunto);
        
			int a = Duplicato(mesh,nuovopunto);
			if (a == -1) {
				a = mesh.NumCell0Ds;        
				mesh.Cell0DsId.push_back(a);
				mesh.NumCell0Ds++;
				mesh.Cell0DsCoordinates.conservativeResize(mesh.NumCell0Ds,3);
				for (unsigned int ii=0;ii<3;ii++)
				   mesh.Cell0DsCoordinates(mesh.NumCell0Ds-1,ii)=nuovopunto[ii];
				mesh.Cell0DsVisibility.push_back(1);
			
			} else {
				mesh.Cell0DsVisibility[a]=1;
			}
			rigaGriglia.push_back(a);
			verticitr2.insert(a);
    
        }
        griglia.push_back(rigaGriglia);
        
        
}// fine cilco dei vertici



vector <int> v1;
vector <int> v2;
vector <int> v3;
vector <int> v4;
vector <int> v5;
vector <int> faccetemp;

for (unsigned int i = 0; i <b; i++){
    for (unsigned int j = 0; j < b-i; j++){
        int p1 = griglia[i][j];
        int p2 = griglia[i][j+1];
        int p3 = griglia[i+1][j];
       ;
        if (p1>p2)
            v1 = {p1,p2};  // se i=0 sarà giallo
        else
            v1 = {p2,p1};
        
        int v1id;
        auto result = latiEsistenti.insert({v1, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v1id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v1[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v1[1];
			if (i==0) 
				mesh.Cell1DsVisibility.push_back(10); //con marker 10 saranno i lati da dividere (gialli)
			else
				mesh.Cell1DsVisibility.push_back(11); //con marker 11 saranno da usare per collagare baricentri facce adiacenti

    
        } else {
            v1id=(*(result.first)).second;
        }
        if (p2>p3)
            v2 = {p2,p3};    //se p2 e p3 sono alla fine dei loro vettori, quindi se j=b-i-1 sarà giallo
        else
            v2 = {p3,p2};
        
        int v2id;
        result = latiEsistenti.insert({v2, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v2id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v2[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v2[1];
			if (j==b-i-1)
				mesh.Cell1DsVisibility.push_back(10);
			else
				mesh.Cell1DsVisibility.push_back(11);
		} 
		else {
            v2id=(*(result.first)).second;
        }
        if (p1>p3)
            v3 = {p1,p3};   // sarà giallo se j=0
        else
            v3 = {p3,p1};
        int v3id;
        result = latiEsistenti.insert({v3, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v3id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v3[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v3[1];
			if (j==0)
				mesh.Cell1DsVisibility.push_back(10);
			else
				mesh.Cell1DsVisibility.push_back(11);
    
        } else {
            v3id=(*(result.first)).second;
        }//facce
        mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
		faccetemp.push_back(mesh.NumCell2Ds);
        mesh.NumCell2Ds++;
        mesh.Cell2DsNumVert.push_back(3);
        mesh.Cell2DsNumEdg.push_back(3);
        vector <int> abc = {p1,p2,p3};
        mesh.Cell2DsVertices.push_back(abc);
        vector <int> v123 = {v1id,v2id,v3id};
        mesh.Cell2DsEdges.push_back(v123);
        mesh.Cell2DsVisibility.push_back(10);

        if (j!=b-i-1){//antagonista
            int p4 = griglia [i+1][j+1];
            if (p4>p2)
                v4 = {p4,p2}; // mai giallo
            else
                v4 = {p2,p4};
            int v4id;
        result = latiEsistenti.insert({v4, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v4id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v4[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v4[1];
            mesh.Cell1DsVisibility.push_back(11);
        } else {
            v4id=(*(result.first)).second;
        }


            if (p4>p3)
                v5 = {p4,p3};   //mai giallo
            else
                v5 = {p3,p4};

            int v5id;
        result = latiEsistenti.insert({v5, mesh.NumCell1Ds});
        if (result.second) {
            mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
            v5id = mesh.NumCell1Ds;
            mesh.NumCell1Ds++;
            mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=v5[0];
            mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=v5[1];
            mesh.Cell1DsVisibility.push_back(11);
        } else {
            v5id=(*(result.first)).second;
        }//facce antagonista
        mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
        faccetemp.push_back(mesh.NumCell2Ds);
        mesh.NumCell2Ds++;
        mesh.Cell2DsNumVert.push_back(3);
        mesh.Cell2DsNumEdg.push_back(3);
        vector <int> bdc = {p2,p4,p3};
		
        mesh.Cell2DsVertices.push_back(bdc);
        vector <int> v452 = {v4id,v5id,v2id};
        mesh.Cell2DsEdges.push_back(v452);
        mesh.Cell2DsVisibility.push_back(10);         

        }//chiude if antagonista
        
    }
}	
	int idbari;

	map <int, int> bari; //mappa faccia temp-baricentro
	for (int faccia : faccetemp){ // per creare baricentro
		vector<int> verticifaccia1 = mesh.Cell2DsVertices[faccia];

        double nuovax = mesh.Cell0DsCoordinates(verticifaccia1[0],0)+mesh.Cell0DsCoordinates(verticifaccia1[1],0)+mesh.Cell0DsCoordinates(verticifaccia1[2],0);
        double nuovay = mesh.Cell0DsCoordinates(verticifaccia1[0],1)+mesh.Cell0DsCoordinates(verticifaccia1[1],1)+mesh.Cell0DsCoordinates(verticifaccia1[2],1);
        double nuovaz = mesh.Cell0DsCoordinates(verticifaccia1[0],2)+mesh.Cell0DsCoordinates(verticifaccia1[1],2)+mesh.Cell0DsCoordinates(verticifaccia1[2],2);
        nuovax = nuovax/3.0;
        nuovay = nuovay/3.0;
        nuovaz = nuovaz/3.0;
        double baricentro[3]={nuovax, nuovay, nuovaz};
       //Normalizzazione (baricentro);
		idbari = mesh.NumCell0Ds;
		mesh.Cell0DsId.push_back(idbari);
		verticitr2.insert(idbari); 

        mesh.NumCell0Ds++;
        mesh.Cell0DsVisibility.push_back(1);
        mesh.Cell0DsCoordinates.conservativeResize(mesh.NumCell0Ds,3);
        for (unsigned int j=0;j<3;j++)
            mesh.Cell0DsCoordinates(mesh.NumCell0Ds-1,j)=baricentro[j];
		bari.insert({faccia, idbari});
	}
	
	
	
	for (int faccia : faccetemp) { //ciclo su facce temp
		vector<int> verticifaccia1 = mesh.Cell2DsVertices[faccia];
		vector<int> latifaccia1 = mesh.Cell2DsEdges[faccia];

		idbari = bari[faccia]; //baricentro
		
		
		vector <int> e1;
		int e1id;
		vector <int> e2;
		int e2id;
		vector <int> e3;
		int e3id;
		vector <int> e4;
		int e4id;
		vector <int> e5;
		int e5id;
		
		bool isOutside = false; // senza lati gialli la faccia è dentro
		for (int l : latifaccia1) {
			if (mesh.Cell1DsVisibility[l] == 10) {		//se il lato è giallo lo dividiamo e ne creiamo due nuovi
				//creo il punto medio
				isOutside = true; // senza lati gialli la faccia è dentro

				int origin = mesh.Cell1DsExtrema(l,0);
				int end = mesh.Cell1DsExtrema(l,1);

				double xmedia = (mesh.Cell0DsCoordinates(origin,0)+mesh.Cell0DsCoordinates(end,0))/2.0;
				double ymedia = (mesh.Cell0DsCoordinates(origin,1)+mesh.Cell0DsCoordinates(end,1))/2.0;
				double zmedia =	(mesh.Cell0DsCoordinates(origin,2)+mesh.Cell0DsCoordinates(end,2))/2.0;
				double puntomedio[3] = {xmedia, ymedia, zmedia};
				//Normalizzazione(puntomedio);
				int idpuntomedio;
				int a = Duplicato(mesh,puntomedio);
				if (a == -1) {
					idpuntomedio = mesh.NumCell0Ds;        
					mesh.Cell0DsId.push_back(idpuntomedio);
					mesh.NumCell0Ds++;
					mesh.Cell0DsCoordinates.conservativeResize(mesh.NumCell0Ds,3);
					for (unsigned int j=0;j<3;j++)
					   mesh.Cell0DsCoordinates(mesh.NumCell0Ds-1,j)=puntomedio[j];
					mesh.Cell0DsVisibility.push_back(1);
				
				}
				else {
					mesh.Cell0DsVisibility[a]=1;
					idpuntomedio = a;        

					
				}
				verticitr2.insert(idpuntomedio); //se c'è gia amen
				

				
				//creo i lati con quel punto
				
				
				if (idpuntomedio>origin)
					e1 = {idpuntomedio,origin};
				else
					e1 = {origin,idpuntomedio};
				auto result = latiEsistenti2.insert({e1, mesh.NumCell1Ds});
				if (result.second) {  //se non c'è già
					mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
					e1id = mesh.NumCell1Ds;
					mesh.NumCell1Ds++;
					mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=e1[0];
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=e1[1];
					mesh.Cell1DsVisibility.push_back(1);
				} else {
					e1id=(*(result.first)).second;
					mesh.Cell1DsVisibility[e1id] = 1;
				}
				
				
				if (idpuntomedio>end)
					e2 = {idpuntomedio, end};
				else
					e2 = {end,idpuntomedio};
				result = latiEsistenti2.insert({e2, mesh.NumCell1Ds});
				if (result.second) {  //se non c'è già
					mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
					e2id = mesh.NumCell1Ds;
					mesh.NumCell1Ds++;
					mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=e2[0];
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=e2[1];
					mesh.Cell1DsVisibility.push_back(1);
				} else {
					e2id=(*(result.first)).second;
					mesh.Cell1DsVisibility[e2id] = 1;
				}
				
				
				if (idbari>origin)
					e3 = {idbari, origin};
				else
					e3 = {origin,idbari};
				result = latiEsistenti2.insert({e3, mesh.NumCell1Ds});
				if (result.second) {  //se non c'è già
					mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
					e3id = mesh.NumCell1Ds;
					mesh.NumCell1Ds++;
					mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=e3[0];
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=e3[1];
					mesh.Cell1DsVisibility.push_back(1);
				} else {
					e3id=(*(result.first)).second;
					mesh.Cell1DsVisibility[e3id] = 1;
				}
				
				
				if (idpuntomedio>idbari)
					e4 = {idpuntomedio, idbari};
				else
					e4 = {idbari,idpuntomedio};
				result = latiEsistenti2.insert({e4, mesh.NumCell1Ds});
				if (result.second) {  //se non c'è già
					mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
					e4id = mesh.NumCell1Ds;
					mesh.NumCell1Ds++;
					mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=e4[0];
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=e4[1];
					mesh.Cell1DsVisibility.push_back(1);
				} else {
					e4id=(*(result.first)).second;
					mesh.Cell1DsVisibility[e4id] = 1;
				}
				
				
				if (idbari>end)
					e5 = {idbari, end};
				else
					e5 = {end,idbari};
				result = latiEsistenti2.insert({e5, mesh.NumCell1Ds});
				if (result.second) {  //se non c'è già
					mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
					e5id = mesh.NumCell1Ds;
					mesh.NumCell1Ds++;
					mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=e5[0];
					mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=e5[1];
					mesh.Cell1DsVisibility.push_back(1);
				} else {
					e5id=(*(result.first)).second;
					mesh.Cell1DsVisibility[e5id] = 1;
				}
				
				//facce
				mesh.Cell2DsId.push_back(mesh.NumCell2Ds);   //faccia 1
				faccetr2.push_back(mesh.NumCell2Ds);
				mesh.NumCell2Ds++;
				mesh.Cell2DsNumVert.push_back(3);
				mesh.Cell2DsNumEdg.push_back(3);
				vector <int> abc_2 = {origin,idpuntomedio,idbari};
				mesh.Cell2DsVertices.push_back(abc_2);
				vector <int> v123_2 = {e1id,e4id,e3id};
				mesh.Cell2DsEdges.push_back(v123_2);
				mesh.Cell2DsVisibility.push_back(1);
				
				mesh.Cell2DsId.push_back(mesh.NumCell2Ds);   //faccia 2
				faccetr2.push_back(mesh.NumCell2Ds);
				mesh.NumCell2Ds++;
				mesh.Cell2DsNumVert.push_back(3);
				mesh.Cell2DsNumEdg.push_back(3);
				vector <int> abc_3 = {end,idpuntomedio,idbari};
				mesh.Cell2DsVertices.push_back(abc_3);
				vector <int> v123_3 = {e2id,e4id,e5id};
				mesh.Cell2DsEdges.push_back(v123_3);
				mesh.Cell2DsVisibility.push_back(1);
				
				
				
				
				
			}
		   
	
		
		}
		
		
		if (!isOutside){ // non ha lati gialli
				vector <int> l1;
				int l1id;
				vector <int> l2;
				int l2id;
				vector <int> l3;
				int l3id;
				vector <int> l4;
				int l4id;
				vector <int> l5;
				int l5id;
		
		for (int lato : latifaccia1){ //ciclo sui lati della faccia per faccia vicina
        int facciavicina;
        for (int fac : faccetemp){
            if (find(mesh.Cell2DsEdges[fac].begin(), mesh.Cell2DsEdges[fac].end(), lato) !=mesh.Cell2DsEdges[fac].end()){
				if (fac != faccia){
                facciavicina = fac;
				break;
				}
            }
        }
		
		
		if (idbari>mesh.Cell1DsExtrema(lato,0))
            l1 = {idbari,mesh.Cell1DsExtrema(lato,0)};
        else
            l1 = {mesh.Cell1DsExtrema(lato,0),idbari};
		
		if (idbari>bari[facciavicina])
            l2 = {idbari,bari[facciavicina]};   
        else
            l2 = {bari[facciavicina],idbari};
		
		if (idbari>mesh.Cell1DsExtrema(lato,1))
            l3 = {idbari,mesh.Cell1DsExtrema(lato,1)};
        else
            l3 = {mesh.Cell1DsExtrema(lato,1),idbari};
		
		if (mesh.Cell1DsExtrema(lato,0)>bari[facciavicina])
            l4 = {mesh.Cell1DsExtrema(lato,0),bari[facciavicina]};   
        else
            l4 = {bari[facciavicina],mesh.Cell1DsExtrema(lato,0)};
		
		if (mesh.Cell1DsExtrema(lato,1)>bari[facciavicina])
            l5 = {mesh.Cell1DsExtrema(lato,1), bari[facciavicina]};
        else
            l5 = {bari[facciavicina],mesh.Cell1DsExtrema(lato,1)};
		
		
		
		auto result = latiEsistenti2.insert({l1, mesh.NumCell1Ds});
		if (result.second) {  //se non c'è già
			mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
			l1id = mesh.NumCell1Ds;
			mesh.NumCell1Ds++;
			mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=l1[0];
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=l1[1];
			mesh.Cell1DsVisibility.push_back(1);
		} else {
			l1id=(*(result.first)).second;
			assert (mesh.Cell1DsVisibility[l1id] == 1);
		}
		
		result = latiEsistenti2.insert({l2, mesh.NumCell1Ds});
		if (result.second) {  //se non c'è già
			mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
			l2id = mesh.NumCell1Ds;
			mesh.NumCell1Ds++;
			mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=l2[0];
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=l2[1];
			mesh.Cell1DsVisibility.push_back(1);
		} else {
			l2id=(*(result.first)).second;
			assert (mesh.Cell1DsVisibility[l2id] == 1);
		}
		
		result = latiEsistenti2.insert({l3, mesh.NumCell1Ds});
		if (result.second) {  //se non c'è già
			mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
			l3id = mesh.NumCell1Ds;
			mesh.NumCell1Ds++;
			mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=l3[0];
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=l3[1];
			mesh.Cell1DsVisibility.push_back(1);
		} else {
			l3id=(*(result.first)).second;
			assert (mesh.Cell1DsVisibility[l3id] == 1);
		}
		
		result = latiEsistenti2.insert({l4, mesh.NumCell1Ds});
		if (result.second) {  //se non c'è già
			mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
			l4id = mesh.NumCell1Ds;
			mesh.NumCell1Ds++;
			mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=l4[0];
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=l4[1];
			mesh.Cell1DsVisibility.push_back(1);
		} else {
			l4id=(*(result.first)).second;
			assert (mesh.Cell1DsVisibility[l4id] == 1);
		}
		
		result = latiEsistenti2.insert({l5, mesh.NumCell1Ds});
		if (result.second) {  //se non c'è già
			mesh.Cell1DsId.push_back(mesh.NumCell1Ds);
			l5id = mesh.NumCell1Ds;
			mesh.NumCell1Ds++;
			mesh.Cell1DsExtrema.conservativeResize(mesh.NumCell1Ds,2);
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,0)=l5[0];
			mesh.Cell1DsExtrema(mesh.NumCell1Ds-1,1)=l5[1];
			mesh.Cell1DsVisibility.push_back(1);
		} else {
			l5id=(*(result.first)).second;
			assert (mesh.Cell1DsVisibility[l5id] == 1);
		}
        
		
				//facce
				
				
				int f1;
				vector <int> abc_4 = {idbari,mesh.Cell1DsExtrema(lato,0),bari[facciavicina]};
				std::sort(abc_4.begin(), abc_4.end());  // crescente
				auto resultf = facceSet.insert({abc_4,mesh.NumCell2Ds });
				if (resultf.second) {  //se non c'è già
					mesh.Cell2DsId.push_back(mesh.NumCell2Ds);   //faccia 1
					f1 = mesh.NumCell2Ds;
					faccetr2.push_back(mesh.NumCell2Ds);
					mesh.NumCell2Ds++;
					mesh.Cell2DsVisibility.push_back(1);
					mesh.Cell2DsNumVert.push_back(3);
					mesh.Cell2DsNumEdg.push_back(3);
					mesh.Cell2DsVertices.push_back(abc_4);
					vector <int> v123_4 = {l1id,l4id,l2id};
					mesh.Cell2DsEdges.push_back(v123_4);
				} else {
					f1=(*(resultf.first)).second;
					mesh.Cell2DsVisibility[f1] = 1;
				}

				
				int f2;
				vector <int> abc_5 = {idbari,bari[facciavicina],mesh.Cell1DsExtrema(lato,1)};
				std::sort(abc_5.begin(), abc_5.end());  // crescente
				resultf = facceSet.insert({abc_5,mesh.NumCell2Ds });
				if (resultf.second) {  //se non c'è già
					mesh.Cell2DsId.push_back(mesh.NumCell2Ds);   //faccia 2
					f2 = mesh.NumCell2Ds;
					faccetr2.push_back(mesh.NumCell2Ds);
					mesh.NumCell2Ds++;
					mesh.Cell2DsVisibility.push_back(1);
					mesh.Cell2DsNumVert.push_back(3);
					mesh.Cell2DsNumEdg.push_back(3);
					mesh.Cell2DsVertices.push_back(abc_5);
					vector <int> v123_5 = {l2id,l5id,l3id};
					mesh.Cell2DsEdges.push_back(v123_5);
					
				} else {
					f2=(*(resultf.first)).second;
					mesh.Cell2DsVisibility[f2] = 1;
				}
				
				
				
				
				
				
				
				
			
		
        
	
		
		}
		
		
		
	}
	}

}// fine ciclo faccia
mesh.Cell3DsFaces.push_back(faccetr2);
mesh.Cell3DsNumFaces.push_back(faccetr2.size());
vector <int> latitr2;   
latitr2.reserve(latiEsistenti2.size());
for (map <vector<int>, int>::iterator it=latiEsistenti2.begin();it!=latiEsistenti2.end();it++){
    latitr2.push_back((*it).second);
}
mesh.Cell3DsEdges.push_back(latitr2);
mesh.Cell3DsNumEdg.push_back(latitr2.size());
vector <int> verticitriang;
verticitriang.reserve(verticitr2.size());
for (int n:verticitr2){
    verticitriang.push_back(n);
	
	double punto[3] = {mesh.Cell0DsCoordinates(n,0),mesh.Cell0DsCoordinates(n,1),mesh.Cell0DsCoordinates(n,2)};
	Normalizzazione(punto);
	for (int j = 0; j<3;j++){
		mesh.Cell0DsCoordinates(n,j) = punto[j];
	}
}
mesh.Cell3DsVertices.push_back(verticitriang);
mesh.Cell3DsNumVert.push_back(verticitriang.size());
creaMappa ( mesh);



}









bool CamminoMinimo(const int v1, const int v2, vector<double>& dist,vector<int>& archi, vector<int>& pred, PolyhedronMesh& mesh){ // come Dijkstra ma si ferma a v2, pesi positivi, grafo non orientati
	double inf = std::numeric_limits<double>::infinity();

	int n = mesh.MappaAdiacenza.size();
	
	pred.resize(n); //vector dei predecessori
	dist.resize(n);  //vector delle distanze
	archi.resize(n);
	for (int i = 0; i<n; i++){
		pred[i] =-1;
		archi[i] =-1;
		dist[i]= inf;
	}
	auto itpos = std::find(mesh.VerticiMA.begin(), mesh.VerticiMA.end(), v1); //pos di v1 
	int pos = itpos - mesh.VerticiMA.begin();
	pred[pos] = v1;
	dist[pos] = 0;
	archi[pos] =0;

	    
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq; // priority queue ordinata in modo crescente
	for (int i = 0; i<n; i++){
		pq.push({dist[i],mesh.VerticiMA[i]});
	} 
	while (!pq.empty()){
		auto coppia = pq.top();  //  primo elemento 
		int u = coppia.second; //primo vertice
		double uu = coppia.first; //prima distanza

		pq.pop(); //dequeue primo elemento


		auto itposu = std::find(mesh.VerticiMA.begin(), mesh.VerticiMA.end(), u); //pos di u
		int posu = itposu - mesh.VerticiMA.begin();
		if (uu > dist[posu]) {
			continue; //skippo perchè è valore vecchio
		}

		if (u == v2){
			return true; //esce
		}
		

		list<unsigned int> vicini = mesh.MappaAdiacenza[u];
		for (unsigned int vic : vicini){
			auto itposvic = std::find(mesh.VerticiMA.begin(), mesh.VerticiMA.end(), vic); //pos di vic
			int posvic = itposvic - mesh.VerticiMA.begin();

			if (dist[posvic] > dist[posu] + mesh.MatricePesi(posu, posvic)){
			pred[posvic] = u;
			dist[posvic] = dist[posu] + mesh.MatricePesi(posu, posvic);
			pq.push({dist[posvic], vic}); //metto valore nuovo
			archi[posvic] = archi[posu] + 1;  // aggiorno archi

			}

		
			
		}
		
		
	}


	


	return false; 
}



void CreaMAMP(PolyhedronMesh& mesh, const int d){ 
	double inf = std::numeric_limits<double>::infinity();

	list<unsigned int> verticiDef = mesh.Cell0DsMarker[d]; // vertici su cui ciclo
	int n = verticiDef.size(); // numero vertici

	vector<unsigned int> verticiDefv;
	verticiDefv.reserve(n);
	list<unsigned int> latiDef =  mesh.Cell1DsMarker[d];
	mesh.MatricePesi.resize(n,n); //tanto è vuota
	for (unsigned int v: verticiDef){
		verticiDefv.push_back(v);
		list<unsigned int> vicini;
		for (unsigned int lato : latiDef) {// troviamo i lati a cui il punto appartiene
			if (mesh.Cell1DsExtrema(lato,0)==v){
				vicini.push_back(mesh.Cell1DsExtrema(lato,1));
				
			}
			
			else if (mesh.Cell1DsExtrema(lato,1)==v) 	{
				vicini.push_back(mesh.Cell1DsExtrema(lato,0));
			}

	}
	mesh.MappaAdiacenza.insert({v,vicini});
	}// chiudo for vertici
	mesh.VerticiMA = verticiDefv;

	
	for (unsigned int i = 0; i<n; i++ ){
		mesh.MatricePesi(i,i) = 0; //diagonale
		int v1 =verticiDefv[i];
			for (unsigned int j = i +1; j<n; j++ ){ // è simmetrica
				int v2 =verticiDefv[j];
				if (std::find(mesh.MappaAdiacenza[v1].begin(), mesh.MappaAdiacenza[v1].end(), v2) != mesh.MappaAdiacenza[v1].end()) {
					double distanza = sqrt((mesh.Cell0DsCoordinates(v1,0)-mesh.Cell0DsCoordinates(v2,0))*(mesh.Cell0DsCoordinates(v1,0)-mesh.Cell0DsCoordinates(v2,0)) + (mesh.Cell0DsCoordinates(v1,1)-mesh.Cell0DsCoordinates(v2,1))*(mesh.Cell0DsCoordinates(v1,1)-mesh.Cell0DsCoordinates(v2,1)) + (mesh.Cell0DsCoordinates(v1,2)-mesh.Cell0DsCoordinates(v2,2))*(mesh.Cell0DsCoordinates(v1,2)-mesh.Cell0DsCoordinates(v2,2)));
					mesh.MatricePesi(i,j) = distanza; 
					mesh.MatricePesi(j,i) = distanza; 
		} else{
			mesh.MatricePesi(i,j) = inf; 
			mesh.MatricePesi(j,i) = inf; 
		}


	}

}
}




} // fine polyhedron library