#include "BooleanFunction.h"
#include "QM_ImplicantsTable.h"
#include "QM_PrimesTable.h"


#ifndef QMALGORITHM
#define QMALGORITHM

class QM {
    private:
        BooleanFunction function;
        vector<Implicant> PIs;
        vector<Implicant> EPIs;
        vector<Implicant> NonEPIs;

        vector<int> NonEPIMinterms;

        void implicantsTable();
        void primesTable();
    public:
        QM(BooleanFunction f);
        string findSimplifiedString();
        BooleanFunction getFunction();

        void printPIs(); // show minterms and binary representation
        void printEPIs(); // show products of each
        void printNonEPIMinterms(); // print minterms that are non EPI
};

#endif