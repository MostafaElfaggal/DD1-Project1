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
    return vector<Implicant>(PIs.begin(), PIs.end());
}

void QM_ImplicantsTable::computeColumn(int columnIndex)
{
    if (!(0 <= columnIndex && columnIndex < table.size()))
        throw out_of_range("Column index out of range");

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
        for (int i = 0; i < table[columnIndex - 1].size() - 1; i++)
        {
            for (auto j = table[columnIndex - 1][i].begin(); j != table[columnIndex - 1][i].end(); j++)
            {
                for (auto k = table[columnIndex - 1][i + 1].begin(); k != table[columnIndex - 1][i + 1].end(); k++)
                {
                    if (j->isMergable(*k))
                    {
                        Implicant mergedImp = *j + *k;
                        Implicant temp1 = *j, temp2 = *k;

                        temp1.setIsPrime(false);
                        temp2.setIsPrime(false);

                        // TODO: improve the complexity of erase and insert

                        table[columnIndex - 1][i].erase(j);
                        table[columnIndex - 1][i].erase(k);

                        table[columnIndex - 1][i].insert(temp1);
                        table[columnIndex - 1][i].insert(temp2);

                        table[columnIndex][mergedImp.get1sCount()].insert(mergedImp);
                    }
                }
            }
        }
    }
}

void QM_ImplicantsTable::compute(){
    //TODO: to be filled
}