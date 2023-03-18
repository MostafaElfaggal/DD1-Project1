#include <vector>
#include <iostream>
#include "BooleanFunction.h"
#include "Implicant.h"

#ifndef QM_PRIMESTABLE
#define QM_PRIMESTABLE

class QM_PrimesTable{
    private:
        BooleanFunction function;
        vector<Implicant> PIs;
        ImplicantGroup_QM_ImplicantsTable EPIs;
        ImplicantGroup_QM_ImplicantsTable NonEPIs;
        vector<int> minterms;
        vector<int> NonEPIMinterms;
        vector<vector<bool>> table;

        void prepareTable();

        bool findEssentials(bool areTrueEssentials=false);
        int searchEssentialinColumn(int index); // returns the index of the essential implicant found
        
        void findNonEssentials();

        void computeDominations();
        void computeRowDominations();
        void computeColumnDominations();

        void simplifyTable();

        void removeColumn(int index);
        void removeRow(int index);

    public:
        QM_PrimesTable(BooleanFunction f, vector<Implicant> pis);
        void compute();
        string printTable();

        vector<Implicant> getEPIs();
        vector<Implicant> getNonEPIs();
        vector<int> getNonEPIMinterms();
};

#endif