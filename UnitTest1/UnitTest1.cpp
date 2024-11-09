#include "pch.h"
#include "CppUnitTest.h"
#include "../PDC_LAB_7/source.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestReadGraph)
        {
            std::ofstream testInput("testInput.txt");
            testInput << "3 3\n1 2\n2 3\n3 1\n";
            testInput.close();

            int n, m;
            int** edges = nullptr;

            loadGraphData("testInput.txt", n, m, edges);

            Assert::AreEqual(3, n);
            Assert::AreEqual(3, m);
            Assert::AreEqual(1, edges[0][0]);
            Assert::AreEqual(2, edges[0][1]);
            Assert::AreEqual(2, edges[1][0]);
            Assert::AreEqual(3, edges[1][1]);
            Assert::AreEqual(3, edges[2][0]);
            Assert::AreEqual(1, edges[2][1]);

            for (int i = 0; i < m; ++i) {
                delete[] edges[i];
            }
            delete[] edges;
        }

        TEST_METHOD(TestCreateAdjacencyMatrix)
        {
            int n = 3, m = 3;
            int** edges = new int* [m];
            edges[0] = new int[2] {1, 2};
            edges[1] = new int[2] {2, 3};
            edges[2] = new int[2] {3, 1};

            int** adjacencyMatrix = createAdjacencyMatrix(n, m, edges);

            Assert::AreEqual(1, adjacencyMatrix[0][1]); 
            Assert::AreEqual(0, adjacencyMatrix[0][2]); 
            Assert::AreEqual(1, adjacencyMatrix[1][2]); 
            Assert::AreEqual(1, adjacencyMatrix[2][0]); 

            for (int i = 0; i < n; ++i) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;

            for (int i = 0; i < m; ++i) {
                delete[] edges[i];
            }
            delete[] edges;
        }

        TEST_METHOD(TestcomputeDegrees)
        {
            int n = 3;
            int** adjacencyMatrix = new int* [n];
            for (int i = 0; i < n; ++i) {
                adjacencyMatrix[i] = new int[n] {0};
            }

            adjacencyMatrix[0][1] = 1; 
            adjacencyMatrix[1][2] = 1; 
            adjacencyMatrix[2][0] = 1; 

            int* inDegree = new int[n];
            int* outDegree = new int[n];
            computeDegrees(adjacencyMatrix, n, inDegree, outDegree);

            Assert::AreEqual(1, inDegree[0]);
            Assert::AreEqual(1, inDegree[1]);
            Assert::AreEqual(1, inDegree[2]);
            Assert::AreEqual(1, outDegree[0]);
            Assert::AreEqual(1, outDegree[1]);
            Assert::AreEqual(1, outDegree[2]);

            delete[] inDegree;
            delete[] outDegree;
            for (int i = 0; i < n; ++i) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;
        }

        TEST_METHOD(TestcheckHomogeneity)
        {
            int n = 3;
            int inDegree[3] = { 1, 1, 1 };
            int outDegree[3] = { 1, 1, 1 };

            Assert::IsTrue(checkHomogeneity(inDegree, outDegree, n));

            inDegree[2] = 2;
            Assert::IsFalse(checkHomogeneity(inDegree, outDegree, n));
        }
    };
}
