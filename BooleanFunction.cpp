#include "BooleanFunction.h"

BooleanFunction::BooleanFunction(int varCount = 0) {
    init(varCount);
}
BooleanFunction::BooleanFunction(int varCount, vector<string> varNames) {
    init(varCount);
    setVariableNames(varNames);
}
BooleanFunction::BooleanFunction(int varCount, vector<int> minterms) {
    init(varCount);
    setTerms(minterms, (booleanValue)ON);
}
BooleanFunction::BooleanFunction(int varCount, vector<int> minterms, vector<int> dontcares) {
    init(varCount);
    setTerms(minterms, (booleanValue)ON);
    setTerms(dontcares, (booleanValue)X);
}
BooleanFunction::BooleanFunction(int varCount, vector<string> varNames, vector<int> minterms) {
    init(varCount);
    setVariableNames(varNames);
    setTerms(minterms, (booleanValue)ON);
}

BooleanFunction::BooleanFunction(int varCount, vector<string> varNames, vector<int> minterms, vector<int> dontcares) {
    init(varCount);
    setVariableNames(varNames);
    setTerms(minterms, (booleanValue)ON);
    setTerms(dontcares, (booleanValue)X);
}
BooleanFunction::BooleanFunction(string sop) {
    SOPToFucntion(sop);
}
BooleanFunction::BooleanFunction(const BooleanFunction& otherFunction) {
    copyFromOtherFunction(otherFunction);
}

void BooleanFunction::copyFromOtherFunction(const BooleanFunction& otherFunction) {
    variables = otherFunction.getVariables();
    terms = otherFunction.getTerms();
    expression = otherFunction.getExpression();
}

void BooleanFunction::init(int varCount) {
    variables = vector<string>(varCount);
    int termsCount = pow(2, variableCount());
    terms = vector<booleanValue>(termsCount);
    
    expression = "";
}

int BooleanFunction::variableCount() const {
    return variables.size();
}

vector<string> BooleanFunction::getVariables() const {
    return variables;
}
string BooleanFunction::getVariableName(int significance) const {
    if (!(significance >= 0 && significance < variableCount())) {
        throw out_of_range("Significance out of range");
    }
    return variables[significance];
}
void BooleanFunction::setVariableName(int significance, string newVarName) {
    // TODO: check for no variable repetition
    // if so raise error

    if (!(significance >= 0 && significance < variableCount())) {
        throw out_of_range("Significance out of range");
    }

    variables[significance] = newVarName;
    functionChanged();
}
void BooleanFunction::setVariableNames(vector<string> newVarNames) {
    for (int i = 0; i < newVarNames.size() && i < variableCount(); i++)
    {
        setVariableName(i, newVarNames[i]);
    }
}

int BooleanFunction::getTermsCount() const {
    return terms.size();
}
booleanValue BooleanFunction::operator[] (int index) const {
    if (!(index >= 0 && index < getTermsCount())) {
        throw out_of_range("Term index out of range");
    }

    return terms[index];
}
vector<booleanValue> BooleanFunction::getTerms() const {
    return terms;
}
void BooleanFunction::setTerm(int index, booleanValue newValue) {
    if (!(index >= 0 && index < getTermsCount())) {
        throw out_of_range("Term index out of range");
    }

    terms[index] = newValue;
    functionChanged();
}
void BooleanFunction::setTerms(vector<int> indcies, booleanValue newValue) {
    for (int i = 0; i < indcies.size(); i++)
    {
        setTerm(indcies[i], newValue);
    }
}

string BooleanFunction::getExpression() const {
    return expression;
}


void BooleanFunction::functionChanged() {
    expression = "";
}

//convert sop string to function, including all validations needed
void BooleanFunction::SOPToFucntion(string sop) {
    SOPString s(sop);
    copyFromOtherFunction(BooleanFunction(s.variableCount(), s.getVariableNames(), s.getMinterms()));
}

// print the truthe table of the function
void BooleanFunction::printTruthTable() const {
    // TODO: to be defined
}

// print the canonical SOP of the function
void BooleanFunction::printSOP() const {
    // TODO: to be defined
}

// print the canonical POS of the function
void BooleanFunction::printPOS() const {
    // TODO: to be defined
}