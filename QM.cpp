#include "QM.h"

QM::QM(BooleanFunction f) {
    function = f;
}
void QM::implicantsTable(){
    QM_ImplicantsTable firstTable(function);
    firstTable.compute();
    PIs = firstTable.getPIs();
}

void QM::primesTable(){
    QM_PrimesTable secondTable(function, PIs);
    secondTable.compute();
    EPIs = secondTable.getEPIs();
    NonEPIs = secondTable.getNonEPIs();
}

string QM::findSimplifiedString() {
    implicantsTable();
    primesTable();

    string simplified;
    vector<Implicant> totalImplicants(EPIs.begin(), EPIs.end());
    totalImplicants.insert(totalImplicants.end(), NonEPIs.begin(), NonEPIs.end());

    for (int i = 0; i < totalImplicants.size(); i++)
    {
        if (i == 0)
            simplified += totalImplicants[i].toString();
        else
            simplified += " + " + totalImplicants[i].toString();
    }
    

    function.setExpression(simplified);
    return simplified;
}

BooleanFunction QM::getFunction() {
    return function;
}