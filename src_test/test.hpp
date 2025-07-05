#pragma once

#include <iostream>
#include <gtest/gtest.h>
#include "PolyhedronMesh.hpp"
#include "Utils.hpp"



extern bool q3;  // è definita nel main_test.cpp
extern bool q4;  // è definita nel main_test.cpp
extern bool q5;  // è definita nel main_test.cpp
extern bool p4;  
extern bool p5;
extern int b;  
extern int c; 



namespace PolyhedronLibrary {
	PolyhedronMesh mesh;


	
// q = 3
TEST(TestVertices, Vertices3)
{
	if (!q3) GTEST_SKIP();

	int T = b*b +b*c+ c*c;
	int expV = 2*T +2;
	
	Tetraedro(mesh);
	Triangolazione(mesh, b);

    EXPECT_EQ(mesh.Cell0DsMarker[1].size(), expV); //input output
}
	

TEST(TestEdges, Edges3)
{
	if (!q3) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expE = 6*T;
	


    EXPECT_EQ(mesh.Cell1DsMarker[1].size(), expE);

    
}

TEST(TestFaces, Faces3)
{
	if (!q3) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expF = 4*T;
	

    EXPECT_EQ(mesh.Cell2DsMarker[1].size(), expF);
}

//valenza

TEST(TestVal, Val3)
{
	if (!q3) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expVal1 = 4; //quanti vertici hanno valenza 3
	int expVal2 = 2*(T-1);//quanti vertici hanno valenza 6
	int Val1=0;
	int Val2=0;
	map<int, int> valenze; //vertice, lista facce
	for (int faccia:mesh.Cell2DsMarker[1]){
		for (int vert:mesh.Cell2DsVertices[faccia]){	
			valenze[vert]+=1;		
		}
	}
	for (auto coppia:valenze){
		if (coppia.second == 3)
			Val1++;
		else if (coppia.second == 6)
			Val2++;
	}

	
    EXPECT_EQ(Val1, expVal1);
    EXPECT_EQ(Val2, expVal2);

}

//q = 4
	
	PolyhedronMesh mesh4;

TEST(TestVertices, Vertices4)
{
	if (!q4) GTEST_SKIP();

	int T = b*b +b*c+ c*c;
	int expV = 4*T +2;
	
	 Ottaedro(mesh4);
	 Triangolazione(mesh4, b);

    EXPECT_EQ(mesh4.Cell0DsMarker[1].size(), expV); //input output
}

TEST(TestEdges, Edges4)
{
	if (!q4) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expE = 12*T;
	


    EXPECT_EQ(mesh4.Cell1DsMarker[1].size(), expE);

    
}

TEST(TestFaces, Faces4)
{
	if (!q4) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expF = 8*T;
	
    EXPECT_EQ(mesh4.Cell2DsMarker[1].size(), expF);

    
}


TEST(TestVal, Val4)
{
	if (!q4) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expVal1 = 6; //quanti vertici hanno valenza 4
	int expVal2 = 4*(T-1);//quanti vertici hanno valenza 6
	int Val1=0;
	int Val2=0;
	map<int, int> valenze; //vertice, lista facce
	for (int faccia:mesh4.Cell2DsMarker[1]){
		for (int vert:mesh4.Cell2DsVertices[faccia]){	
			valenze[vert]+=1;		
		}
	}
	for (auto coppia:valenze){
		if (coppia.second == 4)
			Val1++;
		else if (coppia.second == 6)
			Val2++;
	}

	
    EXPECT_EQ(Val1, expVal1);
    EXPECT_EQ(Val2, expVal2);

}


//q = 5
	PolyhedronMesh mesh5;

TEST(TestVertices, Vertices5)
{
	if (!q5) GTEST_SKIP();

	int T = b*b +b*c+ c*c;
	int expV = 10*T +2;
	
	 Icosaedro(mesh5);
	 Triangolazione(mesh5, b);

    EXPECT_EQ(mesh5.Cell0DsMarker[1].size(), expV); //input output
}

TEST(TestEdges, Edges5)
{
	if (!q5) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expE = 30*T;
	
	
    EXPECT_EQ(mesh5.Cell1DsMarker[1].size(), expE);

    
}

TEST(TestFaces, Faces5)
{
	if (!q5) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expF = 20*T;
	

    EXPECT_EQ(mesh5.Cell2DsMarker[1].size(), expF);

}



TEST(TestVal, Val5)
{
	if (!q5) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expVal1 = 12; //quanti vertici hanno valenza 5
	int expVal2 = 10*(T-1);//quanti vertici hanno valenza 6
	int Val1=0;
	int Val2=0;
	map<int, int> valenze; //vertice, lista facce
	for (int faccia:mesh5.Cell2DsMarker[1]){
		for (int vert:mesh5.Cell2DsVertices[faccia]){	
			valenze[vert]+=1;		
		}
	}
	for (auto coppia:valenze){
		if (coppia.second == 5)
			Val1++;
		else if (coppia.second == 6)
			Val2++;
	}

	
    EXPECT_EQ(Val1, expVal1);
    EXPECT_EQ(Val2, expVal2);

}


//DUALI

//p = 4

	PolyhedronMesh mesh6;

TEST(TestVertices, Vertices4d)
{
	if (!p4) GTEST_SKIP();

	int T = b*b +b*c+ c*c;
	int expV = 4*T +2;
	
	 Ottaedro(mesh6);
	 Triangolazione(mesh6, b);
	 Duale(mesh6);


    EXPECT_EQ(mesh6.Cell2DsMarker[2].size(), expV); //facce come punti del primale
}

TEST(TestEdges, Edges4d)
{
	if (!p4) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expE = 12*T;
	
	
    EXPECT_EQ(mesh6.Cell1DsMarker[2].size(), expE); //lati in ugual numero

    
}

TEST(TestFaces, Faces4d)
{
	if (!p4) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expF = 8*T;
	

    EXPECT_EQ(mesh6.Cell0DsMarker[2].size(), expF); //punti quante facce del primale

    
}


TEST(TestVal, Val4d)
{
	if (!p4) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expVal1 = 6; //quante facce hanno 4 vertici
	int expVal2 = 4*(T-1);//quante facce hanno 6 vertici
	int Val1=0;
	int Val2=0;
	map<int, int> valenze; //vertice, lista facce
	for (int faccia:mesh6.Cell2DsMarker[2]){
		if (mesh6.Cell2DsNumVert[faccia]== 4)
			Val1++;
		else if (mesh6.Cell2DsNumVert[faccia] == 6)
			Val2++;
	}

	
    EXPECT_EQ(Val1, expVal1);
    EXPECT_EQ(Val2, expVal2);

}


//p = 5

	PolyhedronMesh mesh7;

TEST(TestVertices, Vertices5d)
{
	if (!p5) GTEST_SKIP();

	int T = b*b +b*c+ c*c;
	int expV = 10*T +2;
	
	 Icosaedro(mesh7);
	 Triangolazione(mesh7, b);
	 Duale(mesh7);

    EXPECT_EQ(mesh7.Cell2DsMarker[2].size(), expV); //facce come punti del primale
}

TEST(TestEdges, Edges5d)
{
	if (!p5) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expE = 30*T;
	
	
    EXPECT_EQ(mesh7.Cell1DsMarker[2].size(), expE); //lati in ugual numero

    
}

TEST(TestFaces, Faces5d)
{
	if (!p5) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expF = 20*T;
	

    EXPECT_EQ(mesh7.Cell0DsMarker[2].size(), expF); //punti quante facce del primale

    
}


TEST(TestVal, Val5d)
{
	if (!p5) GTEST_SKIP();
	int T = b*b +b*c+ c*c;
	int expVal1 = 12; //quante facce hanno 5 vertici
	int expVal2 = 10*(T-1);//quante facce hanno 6 vertici
	int Val1=0;
	int Val2=0;
	map<int, int> valenze; //vertice, lista facce
	for (int faccia:mesh7.Cell2DsMarker[2]){
		if (mesh7.Cell2DsNumVert[faccia]== 5)
			Val1++;
		else if (mesh7.Cell2DsNumVert[faccia] == 6)
			Val2++;
	}

	
    EXPECT_EQ(Val1, expVal1);
    EXPECT_EQ(Val2, expVal2);

}


}
 