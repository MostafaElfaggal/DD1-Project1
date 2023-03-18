#include "QM_PrimesTable.h"


QM_PrimesTable::QM_PrimesTable(BooleanFunction f, vector<Implicant> pis) {
    function = f;
    PIs = pis;
    minterms = function.getMinterms();
    table = vector<vector<bool>> (minterms.size(), vector<bool>(PIs.size(), false));
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

bool QM_PrimesTable::findEssentials(bool areTrueEssentials) {
    bool foundAnEssential = false;
    for(int i = 0; i < minterms.size(); i++){
        int essentialIndex = searchEssentialinColumn(i);
        if (essentialIndex != -1) {
            foundAnEssential = true;
            if (areTrueEssentials) {
                PIs[essentialIndex].setIsEssential(true);
                EPIs.insert(PIs[essentialIndex]);
            } else {
                PIs[essentialIndex].setIsEssential(false);
                NonEPIs.insert(PIs[essentialIndex]);
            }

            removeColumn(i);

            for (int j = minterms.size() - 1; j >= 0; j--)
            {
                if (table[j][essentialIndex]) {
                    removeColumn(j);

                    if (j <= i)
                        i--;
                }
            }
            
            removeRow(essentialIndex);
            i--;

            simplifyTable();
        }
    }
    return foundAnEssential;
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
    while (table.size() > 0) {
        computeDominations();
        bool foundAnEssential = findEssentials(false);

        if (!foundAnEssential) {
            // choosing a random Implicant to fill the requirements before the next loop
            PIs[0].setIsEssential(true);
            NonEPIs.insert(PIs[0]);

            for (int j = table.size() - 1; j >= 0; j--)
            {
                if (table[j][0]) {
                    removeColumn(j);
                }
            }
            
            removeRow(0);
        }
    }
}

void QM_PrimesTable::computeDominations() {
    computeColumnDominations();
    computeRowDominations();
    simplifyTable();
}

void QM_PrimesTable::computeRowDominations() {
    // i and j are indcies of rows
    if (PIs.size() <= 1) return; // no possible dominations

    for (int i = 0; i < (PIs.size()-1); i++)
    {
        for (int j = i+1; j < PIs.size(); j++)
        {
            bool isIdominatedByJ = true;
            bool isJdominatedByI = true;
            for (int k = 0; k < minterms.size(); k++)
            {
                if ((table[k][i] && table[k][i] != table[k][j])) {
                    isIdominatedByJ = false;
                }

                if ((table[k][j] && table[k][j] != table[k][i])) {
                    isJdominatedByI = false;
                }
            }
            
            if (isIdominatedByJ) {
                removeRow(i);
            } else if (isJdominatedByI) {
                removeRow(j);
            }
        }
    }
}

void QM_PrimesTable::computeColumnDominations() {
    // i and j are indcies of columns
    if (minterms.size() <= 1) return; // no possible dominations

    for (int i = 0; i < (minterms.size()-1); i++)
    {
        for (int j = i+1; j < minterms.size(); j++)
        {
            bool isIdominatedByJ = true;
            bool isJdominatedByI = true;
            for (int k = 0; k < PIs.size(); k++)
            {
                if (!(table[i][k] && table[i][k] == table[j][k])) {
                    isIdominatedByJ = false;
                }

                if (!(table[j][k] && table[j][k] == table[i][k])) {
                    isJdominatedByI = false;
                }
            }
            
            if (isIdominatedByJ) {
                removeColumn(j);
            } else if (isJdominatedByI) {
                removeColumn(i);
            }
        }
    }
}

void QM_PrimesTable::simplifyTable() {
    // remove not needed columns

    for (int i = minterms.size()-1; i >= 0; i--)
    {
        bool isEmpty = true;
        for (int j = 0; j < PIs.size(); j++)
        {
            if (table[i][j]) isEmpty = false;
        }

        if (isEmpty)
            removeColumn(i);
    }
    

    // remove not needed rows
    for (int i = PIs.size()-1; i >= 0; i--)
    {
        bool isEmpty = true;
        for (int j = 0; j < minterms.size(); j++)
        {
            if (table[j][i]) isEmpty = false;
        }

        if (isEmpty)
            removeRow(i);
    }
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
    findEssentials(true);

    NonEPIMinterms = minterms;

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

vector<Implicant> QM_PrimesTable::getEPIs() {
    vector<Implicant> EPIsVector;
    for (auto imp : EPIs)
    {
        EPIsVector.push_back(imp);
    }

    return EPIsVector;    
}

vector<Implicant> QM_PrimesTable::getNonEPIs() {
    vector<Implicant> NonEPIsVector;
    for (auto imp : NonEPIs)
    {
        NonEPIsVector.push_back(imp);
    }

    return NonEPIsVector; 
}

vector<int> QM_PrimesTable::getNonEPIMinterms() {
    return NonEPIMinterms;
}