#include <vector>
#include <set>
#include <unordered_set>
#include "Implicant.h"

#ifndef QM_IMPLICANTSTABLE
#define QM_IMPLICANTSTABLE

typedef set<Implicant> ImplicantGroup_QM_ImplicantsTable;
typedef vector<ImplicantGroup_QM_ImplicantsTable> Column_QM_ImplicantsTable;

class QM_ImplicantsTable
{
private:
    BooleanFunction function;
    vector<Column_QM_ImplicantsTable> table;

public:
    QM_ImplicantsTable(BooleanFunction f);

    Column_QM_ImplicantsTable getColumn(int index) const;

    void computeColumn(int columnIndex);
};

#endif