#include "SOPString.h"

using namespace std;

SOPString::SOPString(string sop) {
    expression = sop;
    expression_wo_spaces = "";
    expression_products = vector<string>(0);
    if (!isValid()) {
        throw invalid_argument("Invalid SOP string input");
    }

    prepareFunctionData();
}

vector<int> SOPString::mintermsVector() {
    return vector<int>(minterms.begin(), minterms.end());
}
vector<string> SOPString::variableNames() {
    vector<string> variableNamesVector(variables.size());
    
    map<string, int>::iterator it;
    for (it = variables.begin(); it!= variables.end(); it++) {
        variableNamesVector[it->second] = it->first;
    }
    
    return variableNamesVector;
}

void SOPString::addVariable(string varName) {
    if (variables.find(varName) == variables.end())
        variables[varName] = variables.size();
}

bool SOPString::validateAlphabet() {
    // check alphabet
    // remove spaces
    expression_wo_spaces = "";
    for (int i = 0; i < expression.length(); i++)
    {
        char c = expression[i];
        bool isSafe = false;
        bool isSpace = false;
        if (c == 32) { // space
            isSafe = true;
            isSpace = true;
        } else if (c == 39) // '
            isSafe = true;
        else if (c == 43) // +
            isSafe = true;
        // else if (c == 48) // 0
        //     isSafe = true;
        // else if (c == 49) // 1
        //     isSafe = true;
        // else if (c == 40) // (
        //     isSafe = true;
        // else if (c == 41) // )
        //     isSafe = true;
        else if (c >= 97 && c <= 122) { // a-z
            isSafe = true;
            addVariable(string(1, c));
        }
        else if (c >= 65 && c <= 90) { // A-Z
            isSafe = true;
            addVariable(string(1, c));
        }
        else
            isSafe = false;


        if (isSafe && !isSpace)
            expression_wo_spaces += c;
        else if (!isSafe)
            return false;
    }

    return true;
}
bool SOPString::validateProducts() {
    // break at +
    string product = "";
    for (int i = 0; i < expression_wo_spaces.length(); i++)
    {
        char c = expression_wo_spaces[i];
        if (c != 43) // not +
            product += c;
        else {
            if (!addProduct(product)) return false;
            product = "";
        }
    }
    if (!addProduct(product)) return false;
    return true;
}
bool SOPString::isValid() {
    if (!validateAlphabet()) return false;

    if (!validateProducts()) return false;
    
    return true;    
}

vector<booleanValue> SOPString::convertProduct(string product, bool& isZero) {
    vector<booleanValue> varValues(variables.size(), X);
    isZero = false;

    string lastVariable = string(1, product[0]);
    bool isNot = false;
    string currentChar = "";
    product += "."; // to consider the last variable

    for (int i = 1; i < product.length(); i++)
    {
        currentChar = string(1, product[i]);
        if (currentChar == "'") { // not
            isNot = !isNot;
        } else { // variable
            int significance = variables[lastVariable];
            booleanValue newValue = !isNot ? ON : OFF;
            if (varValues[significance] == X)
                varValues[significance] = newValue;
            else if (varValues[significance] != newValue) {
                // a . a' = 0, hence the entire product doesn't affect the minterms
                // return and abort the rest of the process
                isZero = true;
                return vector<booleanValue>(variables.size(), OFF);
            } // else resetting the variable to the same value a.a = a
            lastVariable = currentChar;
        }
    }

    return varValues;
}

bool SOPString::addProduct(string product) {
    bool isSafe = true;
    // check no empty products
    if (product == "") isSafe = false;
    // check no ' starting products
    else if (product[0] == '\'') isSafe = false;

    if (!isSafe) return false;

    
    expression_products.push_back(product);
    return true;
}

void SOPString::addMinterms(vector<booleanValue> varValues) {
    vector<int> anyValueVariables(0); // will contain the dont cares, variables which can take either ON or OFF and the product would hold
    int minSUM = 0;
    int accumalatedPower = 1;
    for (int i = 0; i < varValues.size(); i++)
    {
        if (varValues[i] == ON) {
            minSUM += accumalatedPower;
        } else if (varValues[i] == X) {
            anyValueVariables.push_back(accumalatedPower);
        }

        accumalatedPower *= 2;
    }

    addMinterms(minSUM, anyValueVariables, 0);
}
void SOPString::addMinterms(int minSUM, vector<int> anyValueVariables, int currentVariable) {
    if (currentVariable >= anyValueVariables.size()) {
        minterms.insert(minSUM);
        return;
    }

    addMinterms(minSUM, anyValueVariables, currentVariable+1);
    addMinterms(minSUM + anyValueVariables[currentVariable], anyValueVariables, currentVariable+1);
}


void SOPString::prepareFunctionData() {
    // convert products to function terms

    vector<string> temp = expression_products;
    for (int i = 0; i < expression_products.size(); i++)
    {
        bool isZero = false;
        vector<booleanValue> varValues = convertProduct(expression_products[i], isZero);
        if (!isZero)
            addMinterms(varValues);
    }
}

// BooleanFunction SOPString::toFunction() {
//     return BooleanFunction(variables.size(), variableNames(), mintermsVector(), vector<int>(0));
// }

int SOPString::variableCount() {
    return variables.size();
}
vector<string> SOPString::getVariableNames() {
    return variableNames();
}
vector<int> SOPString::getMinterms() {
    return mintermsVector();
}

void SOPString::test() {
    cout << "expression: " << expression << "\n";
    cout << "expression no spaces: " << expression_wo_spaces << "\n\n";

    for (auto prod : expression_products)
    {
        cout << prod << "\n";
    }

    cout << endl;

    for (auto name : variableNames()) {
        cout << name << "\n";
    }
    cout << endl;
    for (auto term : mintermsVector()) {
        cout << term << "\n";
    }
    cout << endl;
}