#include "QM_ImplicantsTable.h"

QM_ImplicantsTable::QM_ImplicantsTable(BooleanFunction f) : table(f.variableCount() + 1, Column_QM_ImplicantsTable(f.variableCount() + 1))
{
    function = f;
}

Column_QM_ImplicantsTable QM_ImplicantsTable::getColumn(int index) const
{
    return table[index];
}

vector<Implicant> QM_ImplicantsTable::getPIs(){
    vector<Implicant> PIsVector;
    for (auto imp : PIs)
    {
        PIsVector.push_back(imp);
    }
    
    return PIsVector;
}

void QM_ImplicantsTable::computeColumn(int columnIndex)
{
    if (!(0 <= columnIndex && columnIndex < table.size()))
        throw out_of_range("Column index out of range");

    
    // TODO: use unordered sets, extract PIs by the pointer idea

    if (columnIndex == 0)
    {
        // break down the function to the implicants

        vector<booleanValue> terms = function.getTerms();

        for (int i = 0; i < terms.size(); i++)
        {
            if (terms[i] == ON || terms[i] == X)
            {
                // implicant(term)
                Implicant imp(i, function.getVariables(), true, false);
                PIs.insert(imp);

                table[columnIndex][imp.get1sCount()].insert(imp);
            }
        }
    }
    // compute the column using the previous one
    else
    {
        // O(n^3)
        for (int i = 0; i < table[columnIndex - 1].size() - 1; i++)
        {
            for (auto constImp1 : table[columnIndex - 1][i])
            {
                for (auto constImp2 : table[columnIndex - 1][i + 1])
                {
                    if (constImp1.isMergable(constImp2))
                    {
                        Implicant mergedImp = constImp1 + constImp2;

                        PIs.erase(constImp1);
                        PIs.erase(constImp2);

                        constImp1.setIsPrime(false);
                        constImp2.setIsPrime(false);

                        PIs.insert(mergedImp);
                        table[columnIndex][i].insert(mergedImp);
                    }
                }
            }
        }
    }
}

void QM_ImplicantsTable::compute(){
    for (int i = 0; i < table.size(); i++)
    {
        computeColumn(i);
    }
}