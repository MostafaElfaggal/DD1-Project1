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
    NonEPIMinterms = secondTable.getNonEPIMinterms();
}

string QM::findSimplifiedString() {
    implicantsTable();
    primesTable();

    string simplified;
    vector<Implicant> totalImplicants(EPIs.begin(), EPIs.end());
    totalImplicants.insert(totalImplicants.end(), NonEPIs.begin(), NonEPIs.end());

    if (totalImplicants.size() == 0) {
        function.setExpression("0");
        return "0";
    }

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

void QM::printPIs() {
    for (int i = 0; i < PIs.size(); i++)
    {
        cout << PIs[i].getRepresentationString() << ": ";
        for (auto i : PIs[i].getMinterms())
        {
            cout << i << ", ";
        }
        cout << "\n";        
    }
}

void QM::printEPIs() {
    for (int i = 0; i < EPIs.size(); i++)
    {
        cout << EPIs[i].toString() << " ";
    }
    cout << "\n";
}

void QM::printNonEPIMinterms() {
    for (auto i : NonEPIMinterms)
    {
        cout << i << " ";
    }
    cout << "\n";
}