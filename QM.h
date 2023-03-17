#include "BooleanFunction.h"
#include "QM_ImplicantsTable.h"
#include "QM_PrimesTable.h"


#ifndef QMALGORITHM
#define QMALGORITHM

class QM {
    private:
        BooleanFunction function;
        vector<Implicant> PIs;
    public:
        QM(BooleanFunction f);
        void implicantsTable();
        void primesTable();
};

#endif