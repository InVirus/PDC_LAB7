#include <iostream>
#include <fstream>
#include "Windows.h"

using namespace std;

void loadGraphData(const string& filename, int& vertexCount, int& edgeCount, int**& edges) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Помилка при відкритті файлу" << endl;
        return;
    }

    inputFile >> vertexCount >> edgeCount;

    edges = new int* [edgeCount];
    for (int i = 0; i < edgeCount; ++i) {
        edges[i] = new int[2];
        inputFile >> edges[i][0] >> edges[i][1];
    }

    inputFile.close();
}

int** createAdjacencyMatrix(int vertexCount, int edgeCount, int** edges) {
    int** adjMatrix = new int* [vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        adjMatrix[i] = new int[vertexCount]();
    }

    for (int i = 0; i < edgeCount; ++i) {
        int v = edges[i][0] - 1;
        int u = edges[i][1] - 1;
        adjMatrix[v][u] = 1;
    }

    return adjMatrix;
}

void computeDegrees(int** adjMatrix, int vertexCount, int* inDeg, int* outDeg) {
    for (int i = 0; i < vertexCount; ++i) {
        inDeg[i] = 0;
        outDeg[i] = 0;
    }

    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            if (adjMatrix[i][j] == 1) {
                outDeg[i]++;
                inDeg[j]++;
            }
        }
    }
}

bool checkHomogeneity(int* inDeg, int* outDeg, int vertexCount) {
    int degreeSum = inDeg[0] + outDeg[0];
    for (int i = 1; i < vertexCount; ++i) {
        if (inDeg[i] + outDeg[i] != degreeSum) {
            return false;
        }
    }
    return true;
}

void findIsolatedAndHangingVertices(int* inDeg, int* outDeg, int vertexCount, int*& isolated, int*& hanging, int& isolatedCount, int& hangingCount) {
    isolatedCount = 0;
    hangingCount = 0;

    for (int i = 0; i < vertexCount; ++i) {
        if (inDeg[i] == 0 && outDeg[i] == 0) {
            isolated[isolatedCount++] = i + 1;
        }
        else if (inDeg[i] + outDeg[i] == 1) {
            hanging[hangingCount++] = i + 1;
        }
    }
}

void printDegreeInfo(int* inDeg, int* outDeg, int vertexCount, const string& outputFile) {
    ofstream outFile(outputFile, ios::app);
    cout << "Степені вершин:\n";
    outFile << "Степені вершин:\n";
    for (int i = 0; i < vertexCount; ++i) {
        cout << "Вершина " << i + 1 << ": Вхідна ступінь = " << inDeg[i] << ", Вихідна ступінь = " << outDeg[i] << endl;
        outFile << "Вершина " << i + 1 << ": Вхідна ступінь = " << inDeg[i] << ", Вихідна ступінь = " << outDeg[i] << endl;
    }
    cout << endl;
    outFile << endl;
    outFile.close();
}

void printIsolatedAndHangingInfo(int* isolated, int isolatedCount, int* hanging, int hangingCount, const string& outputFile) {
    ofstream outFile(outputFile, ios::app);

    cout << "Ізольовані вершини: ";
    outFile << "Ізольовані вершини: ";
    for (int i = 0; i < isolatedCount; ++i) {
        cout << isolated[i];
        outFile << isolated[i];
        if (i < isolatedCount - 1) {
            cout << ", ";
            outFile << ", ";
        }
    }
    cout << endl;
    outFile << endl;

    cout << "Висіючі вершини: ";
    outFile << "Висіючі вершини: ";
    for (int i = 0; i < hangingCount; ++i) {
        cout << hanging[i];
        outFile << hanging[i];
        if (i < hangingCount - 1) {
            cout << ", ";
            outFile << ", ";
        }
    }
    cout << endl;
    outFile << endl;

    outFile.close();
}

int main() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);
    int vertexCount, edgeCount;
    int** edges = nullptr;
    string inputFile, outputFile;

    cout << "Введіть ім'я файлу з вхідними даними: ";
    cin >> inputFile;
    cout << "Введіть ім'я файлу для виведення: ";
    cin >> outputFile;

    loadGraphData(inputFile, vertexCount, edgeCount, edges);

    int** adjMatrix = createAdjacencyMatrix(vertexCount, edgeCount, edges);

    int* inDeg = new int[vertexCount];
    int* outDeg = new int[vertexCount];
    computeDegrees(adjMatrix, vertexCount, inDeg, outDeg);
    printDegreeInfo(inDeg, outDeg, vertexCount, outputFile);

    if (checkHomogeneity(inDeg, outDeg, vertexCount)) {
        cout << "Граф однорідний. Ступінь однорідності: " << inDeg[0] + outDeg[0] << endl;
        ofstream outFile(outputFile, ios::app);
        outFile << "Граф однорідний. Ступінь однорідності: " << inDeg[0] + outDeg[0] << endl;
        outFile.close();
    }
    else {
        cout << "Граф не однорідний." << endl;
        ofstream outFile(outputFile, ios::app);
        outFile << "Граф не однорідний." << endl;
        outFile.close();
    }

    int* isolated = new int[vertexCount];
    int* hanging = new int[vertexCount];
    int isolatedCount = 0, hangingCount = 0;
    findIsolatedAndHangingVertices(inDeg, outDeg, vertexCount, isolated, hanging, isolatedCount, hangingCount);
    printIsolatedAndHangingInfo(isolated, isolatedCount, hanging, hangingCount, outputFile);

    for (int i = 0; i < edgeCount; ++i) {
        delete[] edges[i];
    }
    delete[] edges;

    for (int i = 0; i < vertexCount; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;

    delete[] inDeg;
    delete[] outDeg;
    delete[] isolated;
    delete[] hanging;

    return 0;
}
