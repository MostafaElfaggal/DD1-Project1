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
    //TODO: return extract EPIs and Non-EPIs from second table
}