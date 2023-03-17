#include "BooleanFunction.h"

BooleanFunction::BooleanFunction(int varCount)
{
    init(varCount);
}
BooleanFunction::BooleanFunction(int varCount, vector<string> varNames)
{
    init(varCount);
    setVariableNames(varNames);
}
BooleanFunction::BooleanFunction(int varCount, vector<int> minterms)
{
    init(varCount);
    setTerms(minterms, (booleanValue)ON);
}
BooleanFunction::BooleanFunction(int varCount, vector<int> minterms, vector<int> dontcares)
{
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
BooleanFunction::BooleanFunction(string sop)
{
    SOPToFunction(sop);
}
BooleanFunction::BooleanFunction(const BooleanFunction& otherFunction) {
    copyFromOtherFunction(otherFunction);
}

void BooleanFunction::copyFromOtherFunction(const BooleanFunction& otherFunction) {
    variables = otherFunction.getVariables();
    terms = otherFunction.getTerms();
    expression = otherFunction.getExpression();
}

void BooleanFunction::init(int varCount)
{
    variables = vector<string>(varCount);
    int termsCount = pow(2, variableCount());
    terms = vector<booleanValue>(termsCount);

    expression = "";
}

bool BooleanFunction::operator==(const BooleanFunction& otherFunc) {
    // variables
    vector<string> myNames = getVariables(), otherNames = otherFunc.getVariables();
    if (myNames.size() != otherNames.size()) return false;
    for (int i = 0; i < myNames.size(); i++)
    {
        if (myNames[i] != otherNames[i]) return false;
    }
    
    // terms
    vector<booleanValue> myTerms = getTerms(), otherTerms = otherFunc.getTerms();
    if (myTerms.size() != otherTerms.size()) return false;
    for (int i = 0; i < myTerms.size(); i++)
    {
        if (myTerms[i] != otherTerms[i]) return false;
    }

    // ignore equality of expression

    return true;
}
bool BooleanFunction::operator!=(const BooleanFunction& otherFunc) {
    return (!(*this == otherFunc));
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
void BooleanFunction::setVariableName(int significance, string newVarName)
{
    // TODO: check for no variable repetition
    // if so raise error

    if (!(significance >= 0 && significance < variableCount()))
    {
        throw out_of_range("Significance out of range");
    }

    variables[significance] = newVarName;
    functionChanged();
}
void BooleanFunction::setVariableNames(vector<string> newVarNames)
{
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

vector<int> BooleanFunction::getMinterms() const{
    vector<booleanValue> terms = getTerms();
    vector<int> minterms;

    for(int i=0; i<terms.size();i++){
        if(term[i]==ON)
            minterms.push_back(i);
    }
    return minterms;
}

void BooleanFunction::setTerm(int index, booleanValue newValue)
{
    if (!(index >= 0 && index < getTermsCount()))
    {
        throw out_of_range("Term index out of range");
    }

    terms[index] = newValue;
    functionChanged();
}
void BooleanFunction::setTerms(vector<int> indices, booleanValue newValue)
{
    for (int i = 0; i < indices.size(); i++)
    {
        setTerm(indices[i], newValue);
    }
}
void BooleanFunction::setAllTerms(booleanValue newValue) {
    for (int i = 0; i < terms.size(); i++)
    {
        setTerm(i, newValue);
    }
}

string BooleanFunction::getExpression() const {
    return expression;
}

void BooleanFunction::functionChanged()
{
    expression = "";
}

//convert sop string to function, including all validations needed
void BooleanFunction::SOPToFunction(string sop) {
    SOPString s(sop);
    copyFromOtherFunction(BooleanFunction(s.variableCount(), s.getVariableNames(), s.getMinterms()));
}

// print the truth table of the function
void BooleanFunction::printTruthTable() const
{
    for (int i = variableCount() - 1; i >= 0; i--)
    {
        cout << variables[i] << "\t";
    }
    cout << "\tF\n\n";

    string val;

    for (int i = 0; i < terms.size(); i++)
    {
        if (terms[i] == OFF) val = "0";
        else if (terms[i] == ON) val = "1";
        else val = "X";
        
        string binaryNum = adjustStr(DECtoBIN(i), variableCount()); // TODO: to be adjusted and cleaned
        string formatedBinaryNum = "";
        formatedBinaryNum += binaryNum[0];
        for (int i = 1; i < binaryNum.length(); i++)
        {
            formatedBinaryNum += "\t";
            formatedBinaryNum += binaryNum[i];
        }
        
        cout << formatedBinaryNum << "\t\t" << val << endl;
    }
}

// print the truth table of the function using letters
void BooleanFunction::printTruthTableLetters() const
{
    for (int i = 0; i < terms.size(); i++)
    {
        string boolExpr = adjustStr(DECtoBIN(i), variableCount());
        string letterExpr = "";
        for (int j = 0; j < boolExpr.size(); j++)
        {

            if (boolExpr[j] == '1')
            {
                letterExpr += variables[variables.size() - j -1];
                letterExpr += " ";
            }
            else if (boolExpr[j] == '0')
            {
                letterExpr += variables[variables.size() - j - 1];
                letterExpr += "\'";
            }
        }
        string stringVal;
        if (terms[i] == OFF)
            stringVal = "0";
        else if (terms[i] == ON)
            stringVal = "1";
        else if (terms[i] == X)
            stringVal = "X";

        cout << letterExpr << "\t" << stringVal << "\n";
    }
}

// print the canonical SOP of the function
void BooleanFunction::printSOP() const
{
    int productTermCount = 0;
    for (int i = 0; i < terms.size(); i++)
    {
        if (terms[i] != ON) continue;

        string boolExpr = adjustStr(DECtoBIN(i), variableCount());
        string letterExpr = "";
        for (int j = 0; j < boolExpr.size(); j++)
        {

            if (boolExpr[j] == '1')
            {
                letterExpr += variables[variables.size() - j -1];
            }
            else if (boolExpr[j] == '0')
            {
                letterExpr += variables[variables.size() - j - 1];
                letterExpr += "\'";
            }
        }

        if (productTermCount == 0)
            cout << "(" << letterExpr << ")";
        else
            cout << " + (" << letterExpr << ")";

        productTermCount++;
    }
}

// print the canonical POS of the function
void BooleanFunction::printPOS() const
{
    int sumTermCount = 0;
    for (int i = 0; i < terms.size(); i++)
    {
        if (terms[i] != OFF) continue;

        string boolExpr = adjustStr(DECtoBIN(i), variableCount());
        string letterExpr = "";
        for (int j = 0; j < boolExpr.size(); j++)
        {
            if (j != 0) letterExpr += "+";

            if (boolExpr[j] == '1')
            {
                letterExpr += variables[variables.size() - j -1];
                letterExpr += "\'"; // we not every term in Maxterms
            }
            else if (boolExpr[j] == '0')
            {
                letterExpr += variables[variables.size() - j - 1];
            }
        }

        if (sumTermCount == 0)
        {
            cout << "(" << letterExpr << ")";
        }
        else
        {
            cout << " * (" << letterExpr << ")";
        }

        sumTermCount++;
    }
}

// converts decimal to binary
string BooleanFunction::DECtoBIN(int n) const
{
    string s;
    while (n)
    {
        if (n & 1) // checks if the last bit is 1 or 0, equivalent to %2
            s = "1" + s;
        else
            s = "0" + s;

        n >>= 1; // shifting right once, equivalent to n /= 2
    }
    return s;
}

// ensures string length by adding zeros at the beginning
string BooleanFunction::adjustStr(string s, int l) const
{
    if (l > s.length())
        s = string(l-s.length(), '0') + s;

    return s;
}
