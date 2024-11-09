#pragma once
#include <string>
using namespace std;

void loadGraphData(const string& filename, int& vertexCount, int& edgeCount, int**& edges);
int** createAdjacencyMatrix(int vertexCount, int edgeCount, int** edges);
void computeDegrees(int** adjMatrix, int vertexCount, int* inDeg, int* outDeg);
bool checkHomogeneity(int* inDeg, int* outDeg, int vertexCount);
void findIsolatedAndHangingVertices(int* inDeg, int* outDeg, int vertexCount, int*& isolated, int*& hanging, int& isolatedCount, int& hangingCount);
void printDegreeInfo(int* inDeg, int* outDeg, int vertexCount, const string& outputFile);
void printIsolatedAndHangingInfo(int* isolated, int isolatedCount, int* hanging, int hangingCount, const string& outputFile);
