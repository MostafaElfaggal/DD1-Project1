#include <vector>
#include "Implicant.h"

#ifndef QM_IMPLICANTSTABLE
#define QM_IMPLICANTSTABLE

using namespace std;

typedef vector<ImplicantGroup_QM_ImplicantsTable> Column_QM_ImplicantsTable;

class QM_ImplicantsTable
{
private:
    BooleanFunction function;
    vector<Column_QM_ImplicantsTable> table;
    ImplicantGroup_QM_ImplicantsTable PIs;

public:
    QM_ImplicantsTable(BooleanFunction f);

    Column_QM_ImplicantsTable getColumn(int index) const;
    vector<Implicant> getPIs();

    void computeColumn(int columnIndex);
    void compute();
};

#endif