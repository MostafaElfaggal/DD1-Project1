#include <string>
#include <vector>
#include <set>
#include <map>
#include "BooleanFunction.h"

#include <iostream>

#ifndef SOPSTRING
#define SOPSTRING

using namespace std;

class SOPString {
    private:
        string expression;
        string expression_wo_spaces;
        vector<string> expression_products;

        set<int> minterms;
        vector<int> mintermsVector();

        map<string, int> variables;
        vector<string> variableNames();

        void addVariable(string varName);
        vector<booleanValue> convertProduct(string product);
        bool addProduct(string product);
        void addMinterms(vector<booleanValue> varValues);
        void addMinterms(int minSUM, vector<int> anyValueVariables, int currentVariable); // recurrsive over all possible combinations

        bool isValid();
        bool validateAlphabet();
        bool validateProducts();

        void prepareFunctionData();
    public:
        SOPString(string sop);
        BooleanFunction toFunction();

        void test();
};

#endif