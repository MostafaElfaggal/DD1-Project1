#include <iostream>
#include "BooleanFunction.h"
#include "SOPString.h"

using namespace std;

int main() {
    string func = "abc + ab'";

    BooleanFunction f(func);
    cout << f.variableCount() << "\n\n";

    vector<booleanValue> terms = f.getTerms();
    for (int i = 0; i < terms.size(); i++)
    {
        booleanValue val = terms[i];
        if (val == ON) {
            cout << i << ": 1\n";
        } else if (val == OFF) {
            cout << i << ": 0\n";
        } else {
            cout << i << ": X\n";
        }
    }
}