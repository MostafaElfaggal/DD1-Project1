#include <vector>
#include "BooleanFunction.h"
#include "Implicant.h"


#ifndef QM_PRIMESTABLE
#define QM_PRIMESTABLE

class QM_PrimesTable{
    private:
        BooleanFunction function;
        vector<Implicant> PIs;
        ImplicantGroup_QM_ImplicantsTable EPIs;
        vector<int> minterms;
        vector<vector<bool>> table;

        void findEssentials();
        bool searchEssentialinColumn(int index);
        void findNonEssentials();
        void computeDominations();
        void computeRowDominations();
        void computeColumnDominations();
        void removeColumn(int index);
        void removeRow(int index);

    public:
        QM_PrimesTable(BooleanFunction f, vector<Implicant> pis);
        void compute();

};

#endif