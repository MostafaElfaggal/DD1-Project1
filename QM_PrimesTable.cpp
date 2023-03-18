#include "QM_PrimesTable.h"


QM_PrimesTable::QM_PrimesTable(BooleanFunction f, vector<Implicant> pis) {
    function = f;
    PIs = pis;
    minterms = function.getMinterms();
    table = vector<vector<bool>> (function.variableCount(), vector<bool>(PIs.size(), false));
    prepareTable();
}

void QM_PrimesTable::prepareTable() {
    for (int i = 0; i < PIs.size(); i++)
    {
        vector<int> PIMinterms = PIs[i].getMinterms();
        for (int j = 0, k = 0; j < minterms.size() && k < PIMinterms.size();)
        {
            if (PIMinterms[k] == minterms[j]) {
                table[j][i] = true;
                k++;
                j++;
            } else if (PIMinterms[k] < minterms[j]) k++;
            else j++;
        }
    }
}

void QM_PrimesTable::findEssentials() {
    for(int i = 0; i < table.size(); i++){
        int essentialIndex = searchEssentialinColumn(i);
        if (essentialIndex != -1) {
            EPIs.insert(PIs[essentialIndex]);
            removeColumn(i);

            for (int j = table.size() - 1; j >= 0; j--)
            {
                if (table[j][essentialIndex]) {
                    removeColumn(j);

                    if (j <= i)
                        i--;
                }
            }
            
            removeRow(essentialIndex);
            i--;
        }
    }
}

int QM_PrimesTable::searchEssentialinColumn(int index) {
    int essentialIndex = -1;
    for(int i = 0; i < table[index].size(); i++){
        if(table[index][i]) {
            if (essentialIndex == -1)
                essentialIndex = i;
            else
                return -1;
        }
    }

    return essentialIndex;
}

void QM_PrimesTable::findNonEssentials() {

}

void QM_PrimesTable::computeDominations() {
    computeColumnDominations();
    computeRowDominations();
}

void QM_PrimesTable::computeRowDominations() {

}

void QM_PrimesTable::computeColumnDominations() {

}

void QM_PrimesTable::removeColumn(int index) {
    if (!(index >= 0 && index < minterms.size())) return;

    table.erase(table.begin() + index);
    minterms.erase(minterms.begin() + index);
}
void QM_PrimesTable::removeRow(int index) {
    if (!(index >= 0 && index < PIs.size())) return;

    for (int i = 0; i < table.size(); i++)
    {
        table[i].erase(table[i].begin() + index);
    }
    

    PIs.erase(PIs.begin() + index);
}

void QM_PrimesTable::compute() {
    // TODO: remove prints
    cout << printTable() << "\n\n";

    findEssentials();
    cout << printTable();
    
    findNonEssentials();
}

string QM_PrimesTable::printTable() {
    string res;
    res += "\t";
    for (int i = 0; i < minterms.size(); i++)
    {
        res += "\t" + minterms[i];
    }
    res += "\n\n";
    
    for (int i = 0; i < PIs.size(); i++)
    {
        res += PIs[i].print() + "\t";
        for (int j = 0; j < minterms.size(); j++)
        {
            if (table[j][i])
                res += "\tX";
        }
        res += "\n";        
    }

    return res;
}