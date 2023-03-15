#include <vector>
#include <set>
#include "Implicant.h"

#ifndef QM_IMPLICANTSTABLE
#define QM_IMPLICANTSTABLE

typedef vector<set<Implicant>> QM_ImplicantsTable_Column;

class QM_ImplicantsTable : public vector<QM_ImplicantsTable_Column> {
    private:
        BooleanFunction function;
    public:
        QM_ImplicantsTable(BooleanFunction f);

        QM_ImplicantsTable_Column getColumn(int index) const;

        void computeColumn(int columnIndex);
};

#endif