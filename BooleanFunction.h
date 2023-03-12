#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include <stdexcept>
#include <math.h>

#ifndef BOOLEANFUNCTION
#define BOOLEANFUNCTION

using namespace std;

enum booleanValue
{
    OFF,
    ON,
    X
};

class BooleanFunction
{

private:
    vector<string> variables;

    vector<booleanValue> terms; // space vs time complexity, T(1) S(2^n): n number of variables

    string expression;

public:
    BooleanFunction();
    BooleanFunction(int varCount);
    BooleanFunction(int varCount, vector<string> varNames);
    BooleanFunction(int varCount, vector<int> minterms);
    BooleanFunction(int varCount, vector<int> minterms, vector<int> dontcares);
    BooleanFunction(int varCount, vector<string> varNames, vector<int> minterms, vector<int> dontcares);
    BooleanFunction(string sop);
    void init(int varCount);

    int variableCount();
    vector<string> getVariables();
    string getVariableName(int significance);
    void setVariableName(int significance, string newVarName);
    void setVariableNames(vector<string> newVarNames);

    int getTermsCount();
    booleanValue operator[](int index);
    vector<booleanValue> getTerms();
    void setTerm(int index, booleanValue newValue);
    void setTerms(vector<int> indicies, booleanValue newValue);

    void functionChanged();

    void SOPToFunction(string sop);

    void printTruthTable();        // Kirolous
    void printTruthTableLetters(); // Kirolous
    void printSOP();               // Kirolous
    void printPOS();               // Kirolous

    string DECtoBIN(int n);            // Kirolous
    string adjustStr(string s, int l); // Kirolous
};

#endif