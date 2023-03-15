#include "QM_ImplicantsTable.h"

QM_ImplicantsTable::QM_ImplicantsTable(BooleanFunction f) : vector<QM_ImplicantsTable_Column>(f.variableCount()+1, QM_ImplicantsTable_Column(f.variableCount()+1)) {
    function = f;
}

QM_ImplicantsTable_Column QM_ImplicantsTable::getColumn(int index) const {
    return (*this)[index];
}

void QM_ImplicantsTable::computeColumn(int columnIndex) {
    if (!(0<=columnIndex && columnIndex < size()))
        throw out_of_range("Column index out of range");

    if (columnIndex == 0) {
        // break down the function to the implicants
    } else {
        // compute the column using the previous one
    }
}
