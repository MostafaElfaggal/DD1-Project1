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
    // return vector<const Implicant&>(PIs.begin(), PIs.end());
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
            for (auto constImp1 = table[columnIndex - 1][i].begin(); constImp1 != table[columnIndex - 1][i].end(); constImp1++)
            {
                for (auto constImp2 = table[columnIndex - 1][i + 1].begin(); constImp2 != table[columnIndex - 1][i + 1].end(); constImp2++)
                {
                    if (constImp1->isMergable(*constImp2))
                    {
                        Implicant mergedImp = *constImp1 + *constImp2;
                        Implicant nonConstImp1 = *constImp1, nonConstImp2 = *constImp2;

                        nonConstImp1.setIsPrime(false);
                        nonConstImp2.setIsPrime(false);

                        table[columnIndex - 1][i].erase(constImp1);
                        table[columnIndex - 1][i+1].erase(constImp2);

                        table[columnIndex - 1][i].insert(nonConstImp1);
                        table[columnIndex - 1][i+1].insert(nonConstImp2);

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