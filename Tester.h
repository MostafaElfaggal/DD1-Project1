#include <vector>
#include <string>
#include "BooleanFunction.h"

#ifndef TESTER
#define TESTER

using namespace std;

enum ExpectedResults {
    SUCCESS,
    FAILURE
};
template <class T, class R>
struct TestCase {
    T input;
    ExpectedResults expectedResult;
    R ExpectedOutcome;
};
class Tester {
    private:
    public:
        // vector<string> testCases2;
        void testSOPString(vector<TestCase<string, BooleanFunction>> testCases);
};

#endif