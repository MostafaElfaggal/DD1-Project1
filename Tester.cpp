#include "Tester.h"
#include "BooleanFunction.h"

void Tester::testSOPString(vector<TestCase<string, BooleanFunction>> testCases) {
    // testing if string will pass or fail

    for(int i=0; i<testCases.size();i++){
        try {
            BooleanFunction f(testCases[i].input);
            // valid string

            if (testCases[i].expectedResult == FAILURE)
                cout << "Error found in Test case "<<i+1<<"\n";

            // consider expected function output
            if (f != testCases[i].ExpectedOutcome)
                cout << "Non matching outcomes in Test case "<<i+1<<"\n";
        } catch (invalid_argument) {
            // invalid string

            if (testCases[i].expectedResult == SUCCESS)
                cout << "Error found in Test case "<<i+1<<"\n";
        }
        // catch (...) {
        //     // some other unforseen error
        // }
    }
}