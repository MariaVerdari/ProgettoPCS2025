#pragma once

#include <iostream>
#include <gtest/gtest.h>
#include "PolyhedronMesh.hpp"
#include "Utils.hpp"



extern bool q3;  // è definita nel main_test.cpp
extern bool q4;  // è definita nel main_test.cpp
extern bool q5;  // è definita nel main_test.cpp
extern int b;  // è definita nel main_test.cpp
extern int c;  // è definita nel main_test.cpp



namespace PolyhedronLibrary {
	bool a;
	PolyhedronMesh mesh;


	
// q = 3
TEST(TestVertices, Vertices3)
{
	if (!q3) GTEST_SKIP();

	int T = b*b +b*c+ c*c;
	int expV = 2*T +2;
	
	a =Tetraedro(mesh);
	a =Triangolazione(mesh, b);

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

//q = 4
	
	PolyhedronMesh mesh4;

TEST(TestVertices, Vertices4)
{
	if (!q4) GTEST_SKIP();

	int T = b*b +b*c+ c*c;
	int expV = 4*T +2;
	
	 a =Ottaedro(mesh4);
	 a =Triangolazione(mesh4, b);

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



//q = 5
	PolyhedronMesh mesh5;

TEST(TestVertices, Vertices5)
{
	if (!q5) GTEST_SKIP();

	int T = b*b +b*c+ c*c;
	int expV = 10*T +2;
	
	 a =Icosaedro(mesh5);
	 a =Triangolazione(mesh5, b);

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



//valenza


}
 