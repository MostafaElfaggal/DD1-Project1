#include "QM_PrimesTable.h"


QM_PrimesTable::QM_PrimesTable(BooleanFunction f, vector<Implicant> pis){
    function = f;
    PIs = pis;
    minterms = function.getMinterms();
    table = vector<vector<bool>> (function.variableCount(), vector<bool>(PIs.size(), false));
}

void QM_PrimesTable::findEssentials(){
    for(int i=0; i< table.size();i++){
        if(searchEssentialinColumn(i)){
            EPIs.insert();
            removeColumn(i);
            removeRow(i);
            i--;
        }
    }
}

bool QM_PrimesTable::searchEssentialinColumn(int index){
    int count=0;
    for(int i=0; i<table[index].size();i++){
        if(table[index][i])
            count++;
    }
    return (count==1);
}

void QM_PrimesTable::findNonEssentials(){

}

void QM_PrimesTable::computeDominations(){
    computeColumnDominations();
    computeRowDominations();
}

void QM_PrimesTable::computeRowDominations(){

}

void QM_PrimesTable::computeColumnDominations(){

}

void QM_PrimesTable::removeColumn(int index){
    
}
void QM_PrimesTable::removeRow(int index){

}

void QM_PrimesTable::compute(){
    findEssentials();
    findNonEssentials();
}