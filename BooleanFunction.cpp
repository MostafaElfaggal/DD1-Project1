#include "BooleanFunction.h"

BooleanFunction::BooleanFunction(int varCount = 0)
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
BooleanFunction::BooleanFunction(int varCount, vector<string> varNames, vector<int> minterms, vector<int> dontcares)
{
    init(varCount);
    setVariableNames(varNames);
    setTerms(minterms, (booleanValue)ON);
    setTerms(dontcares, (booleanValue)X);
}
BooleanFunction::BooleanFunction(string sop)
{
    SOPToFunction(sop);
}

void BooleanFunction::init(int varCount)
{
    variables = vector<string>(varCount);
    int termsCount = pow(2, variableCount());
    terms = vector<booleanValue>(termsCount);

    expression = "";
}

int BooleanFunction::variableCount()
{
    return variables.size();
}

vector<string> BooleanFunction::getVariables()
{
    return variables;
}
string BooleanFunction::getVariableName(int significance)
{
    if (!(significance >= 0 && significance < variableCount()))
    {
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

int BooleanFunction::getTermsCount()
{
    return terms.size();
}
booleanValue BooleanFunction::operator[](int index)
{
    if (!(index >= 0 && index < getTermsCount()))
    {
        throw out_of_range("Term index out of range");
    }

    return terms[index];
}
vector<booleanValue> BooleanFunction::getTerms()
{
    return terms;
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
void BooleanFunction::setTerms(vector<int> indcies, booleanValue newValue)
{
    for (int i = 0; i < indcies.size(); i++)
    {
        setTerm(indcies[i], newValue);
    }
}

void BooleanFunction::functionChanged()
{
    expression = "";
}

// convert sop string to function, including all validations needed
void BooleanFunction::SOPToFunction(string sop)
{
    // TODO:to be defined
}

// print the truth table of the function
void BooleanFunction::printTruthTable()
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
void BooleanFunction::printTruthTableLetters()
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
void BooleanFunction::printSOP()
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
void BooleanFunction::printPOS()
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
string BooleanFunction::DECtoBIN(int n)
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
string BooleanFunction::adjustStr(string s, int l)
{
    if (l > s.length())
        s = string(l-s.length(), '0') + s;

    return s;
}
