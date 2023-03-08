#include <string>
#include <vector>
#include <map>
#include "BooleanFunction.h"

using namespace std;

class SOPString {
    private:
        string expression;
        string expression_wo_spaces;
        vector<string> expression_products;

        map<string, int> variables;

        bool isValid();
        bool validateAlphabet();
        bool validateProducts();
    public:
        SOPString(string sop = "1");
        BooleanFunction toFunction();
};