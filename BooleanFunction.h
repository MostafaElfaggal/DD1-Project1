#include "BooleanValue.h"

#include <string>
#include <vector>

#include <stdexcept>
#include <math.h>

#include "SOPString.h"

#ifndef BOOLEANFUNCTION
#define BOOLEANFUNCTION

using namespace std;

class BooleanFunction {

    private:
        vector<string> variables;

        vector<booleanValue> terms; // space vs time complexity, T(1) S(2^n): n number of variables
        
        string expression;

        void copyFromOtherFunction(const BooleanFunction& otherFunction);
    public:
        BooleanFunction();
        BooleanFunction(int varCount);
        BooleanFunction(int varCount, vector<string> varNames);
        BooleanFunction(int varCount, vector<int> minterms);
        BooleanFunction(int varCount, vector<int> minterms, vector<int> dontcares);
        BooleanFunction(int varCount, vector<string> varNames, vector<int> minterms);
        BooleanFunction(int varCount, vector<string> varNames, vector<int> minterms, vector<int> dontcares);
        BooleanFunction(string sop);
        BooleanFunction(const BooleanFunction& otherFucntion);
        void init(int varCount);

        bool operator==(const BooleanFunction& otherFunc);
        bool operator!=(const BooleanFunction& otherFunc);

        int variableCount() const;
        vector<string> getVariables() const;
        string getVariableName(int significance) const;
        void setVariableName(int significance, string newVarName);
        void setVariableNames(vector<string> newVarNames);

        int getTermsCount() const;
        booleanValue operator[] (int index) const;
        vector<booleanValue> getTerms() const;
        void setTerm(int index, booleanValue newValue);
        void setTerms(vector<int> indcies, booleanValue newValue);

        string getExpression() const;

        void functionChanged();

        void SOPToFucntion(string sop);

        void printTruthTable() const;
        void printSOP() const;
        void printPOS() const;
};

#endif