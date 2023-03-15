#include <vector>
#include "BooleanFunction.h"
#include "BooleanValue.h"

#ifndef IMPLICANT
#define IMPLICANT

using namespace std;

class Implicant : public BooleanFunction {
    private:
        vector<booleanValue> coverRepresentation;
        bool isPrime;
        bool isEssential;

        void setCoverVariable(int significance, booleanValue newValue);

        void convertCoverToMinterms();
        void addMinterms(int minSUM, vector<int> anyValueVariables, int currentVariable);

        int compare(const Implicant& otherImplicant) const;
    public:
        Implicant(vector<booleanValue> cover, bool newIsPrime=false, bool newIsEssential=false);
        Implicant(vector<booleanValue> cover, vector<string> variableNames, bool newIsPrime=false, bool newIsEssential=false);
        void init(vector<booleanValue> cover, bool newIsPrime, bool newIsEssential);

        vector<booleanValue> getCover() const;
        string getRepresentationString() const;
        int get1sCount() const;
        bool IsPrime() const;
        bool IsEssential() const;

        void setIsPrime(bool newIsPrime);
        void setIsEssential(bool newIsEssential);

        bool isMergable(const Implicant& otherImplicant) const;
        Implicant operator+(const Implicant& otherImplicant) const;
};

#endif