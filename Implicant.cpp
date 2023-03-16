#include "Implicant.h"

Implicant::Implicant(vector<booleanValue> cover, bool newIsPrime, bool newIsEssential) : BooleanFunction(cover.size(), vector<string>(cover.size(), "")) {
    init(cover, newIsPrime, newIsEssential);
}
Implicant::Implicant(vector<booleanValue> cover, vector<string> variableNames, bool newIsPrime, bool newIsEssential) : BooleanFunction(cover.size(), variableNames) {
    init(cover, newIsPrime, newIsEssential);
}
void Implicant::init(vector<booleanValue> cover, bool newIsPrime, bool newIsEssential) {
    coverRepresentation = cover;
    isPrime = newIsPrime;
    isEssential = newIsEssential;

    convertCoverToMinterms();
}

void Implicant::convertCoverToMinterms() {
    setAllTerms(OFF);

    vector<booleanValue> varValues = getCover();
    vector<int> anyValueVariables(0); // will contain the dont cares, variables which can take either ON or OFF and the product would hold
    int minSUM = 0;
    int accumalatedPower = 1;
    for (int i = 0; i < varValues.size(); i++)
    {
        if (varValues[i] == ON) {
            minSUM += accumalatedPower;
        } else if (varValues[i] == X) {
            anyValueVariables.push_back(accumalatedPower);
        }

        accumalatedPower *= 2;
    }

    addMinterms(minSUM, anyValueVariables, 0);
}
void Implicant::addMinterms(int minSUM, vector<int> anyValueVariables, int currentVariable) {
    if (currentVariable >= anyValueVariables.size()) {
        setTerm(minSUM, ON);
        return;
    }

    addMinterms(minSUM, anyValueVariables, currentVariable+1);
    addMinterms(minSUM + anyValueVariables[currentVariable], anyValueVariables, currentVariable+1);
}

vector<booleanValue> Implicant::getCover() const {
    return coverRepresentation;
}

string Implicant::getRepresentationString() const {
    string coverString = "";
    vector<booleanValue> coverVector = getCover();
    for (int i = 0; i < coverVector.size(); i++)
    {
        if (coverVector[i] == OFF) {
            coverString += "0";
        } else if (coverVector[i] == ON) {
            coverString += "1";
        } else if (coverVector[i] == X) {
            coverString += "-";
        }
    }

    return coverString;    
}


int Implicant::get1sCount() const {
    int count = 0;
    for (booleanValue val : getCover())
        if (val == ON) count++;
    
    return count;
}

bool Implicant::IsPrime() const {
    return isPrime;
}

bool Implicant::IsEssential() const {
    return isEssential;
}

void Implicant::setIsPrime(bool newIsPrime) {
    isPrime = newIsPrime;
}

void Implicant::setIsEssential(bool newIsEssential) {
    isEssential = newIsEssential;
}

void Implicant::setCoverVariable(int significance, booleanValue newValue) {
    if (!(0 <= significance && significance >= variableCount()))
        throw out_of_range("Variable Significance out of range");

    coverRepresentation[significance] = newValue;
}

bool Implicant::isMergable(const Implicant& otherImplicant) const {
    return compare(otherImplicant) != -1;
}

int Implicant::compare(const Implicant& otherImplicant) const {
    if (variableCount() != otherImplicant.variableCount()) return -1;

    int diffInOnes = get1sCount() - otherImplicant.get1sCount();
    if (!(diffInOnes == 1 || diffInOnes == -1)) return -1;

    int diffIndex = -1;
    vector<booleanValue> myCover = getCover(), otherCover = otherImplicant.getCover();
    for (int i = 0; i < myCover.size(); i++)
    {
        if (myCover[i] == otherCover[i]) continue;// if the 2 bits are identical no more comparison needed

        if (myCover[i] == X || otherCover[i] == X) return -1; // the bits are different and one of them is a -, thus no match

        if (diffIndex == -1)
            diffIndex = i; // first bit difference found
        else
            return -1; // more than one difference found
    }
    
    return diffIndex;
}
Implicant Implicant::operator+(const Implicant& otherImplicant) const {
    int index = compare(otherImplicant);
    if (index == -1)
        throw invalid_argument("Implicant operands are non-compatible for merging");

    // create an implicant diff in index to be -
    vector<booleanValue> newCover = getCover();
    newCover[index] = X;
    return Implicant(newCover, getVariables());
}

bool Implicant::operator==(const Implicant& otherImplicant) const {
    vector<booleanValue> myCover = getCover(), otherCover = otherImplicant.getCover();
    if (myCover.size() != otherCover.size()) return false;

    for (int i = 0; i < myCover.size(); i++)
    {
        if (myCover[i] != otherCover[i]) return false;
    }

    return true;    
}
bool Implicant::operator!=(const Implicant& otherImplicant) const {
    return !((*this)==otherImplicant);
}