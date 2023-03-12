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

// Kirolous
// print the truth table of the function
void BooleanFunction::printTruthTable()
{
    for (int i = variableCount() - 1; i >= 0; i--)
    {
        cout << variables[i];
    }
    cout << " F\n";

    for (int i = 0; i < terms.size(); i++)
    {
        cout << adjustStr(DECtoBIN(i), variableCount()) << " " << terms[i] << endl;
    }
}

// Kirolous
// print the truth table of the function using letters
void BooleanFunction::printTruthTableLetters()
{
    for (int i = 0; i < terms.size(); i++)
    {
        // cout << "TEST";
        int c = 0; // shift caused by the dashes
        string boolExpr = adjustStr(DECtoBIN(i), variableCount());
        for (int j = 0; j < boolExpr.size(); j++)
        {

            if (boolExpr[j] == '1')
            {
                boolExpr.replace(j, 1, variables[variables.size() - j + c - 1]);
            }
            else if (boolExpr[j] == '0')
            {
                string t = (variables[variables.size() - j + c - 1]);
                t.append("\'");
                boolExpr.replace(j, 1, t);
                j++;
                c++;
            }
            else
            {
                boolExpr.replace(j, 1, string(1, 'X'));
            }
        }
        cout << setw(variableCount() + 3) << boolExpr << "  " << terms[i] << endl;
    }
}

// Kirolous
// print the canonical SOP of the function
void BooleanFunction::printSOP()
{
    for (int i = 0; i < terms.size(); i++)
    {
        if (terms[i] == ON)
        {
            int c = 0; // shift caused by the dashes
            string boolExpr = adjustStr(DECtoBIN(i), variableCount());
            for (int j = 0; j < boolExpr.size(); j++)
            {

                if (boolExpr[j] == '1')
                {
                    boolExpr.replace(j, 1, variables[variables.size() - j + c - 1]);
                }
                else if (boolExpr[j] == '0')
                {
                    string t = (variables[variables.size() - j + c - 1]);
                    t.append("\'");
                    boolExpr.replace(j, 1, t);
                    j++;
                    c++;
                }
            }

            if (i == terms.size() - 1)
            {
                cout << "(" << boolExpr << ")";
            }
            else
            {
                cout << "(" << boolExpr << ") + ";
            }
        }
    }
}

// Kirolous
// print the canonical POS of the function
void BooleanFunction::printPOS()
{
    for (int i = 0; i < terms.size(); i++)
    {
        if (terms[i] == OFF)
        {

            int c = 0; // shift caused by the dashes
            string boolExpr = adjustStr(DECtoBIN(i), variableCount());
            for (int j = 0; j < boolExpr.size(); j++)
            {

                if (boolExpr[j] == '1')
                {
                    string t = (variables[variables.size() - j + c - 1]);
                    t.append("\'+");
                    boolExpr.replace(j, 1, t);
                    j++;
                    c += 2;
                }
                else if (boolExpr[j] == '0')
                {
                    string t = (variables[variables.size() - j + c - 1]);
                    t.append("+");

                    boolExpr.replace(j, 1, t);
                    j++;
                    c++;
                }
            }

            boolExpr[boolExpr.size() - 1] = ')'; // replace the extra '+' with a closing bracket
            if ((i == terms.size() - 2))
            {
                cout << "(" << boolExpr;
            }
            else
            {
                cout << "(" << boolExpr << " * ";
            }
        }
    }
}

// Kirolous
// converts decimal to binary
string BooleanFunction::DECtoBIN(int n)
{
    string s;
    while (n)
    {
        if (n & 1)
            s += '1';
        else
            s += '0';

        n >>= 1;
    }
    reverse(s.begin(), s.end());
    return s;
}

// Kirolous
// ensures string length by adding zeros at the beginning
string BooleanFunction::adjustStr(string s, int l)
{
    while (s.size() < l)
    {
        s.insert(0, "0");
    }

    return s;
}
