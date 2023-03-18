#include <iostream>
#include "BooleanFunction.h"
#include "SOPString.h"
#include "QM.h"
#include "Tester.h"

#include <vector>

using namespace std;

void outputForFunction(BooleanFunction f) {
    cout << "Minterms: ";
    for (auto i : f.getMinterms()) {
        cout << i << ", ";
    }
    cout << endl;

    cout << "Truthtable:-\n";
    f.printTruthTable();
    cout << "\n\n\n";

    cout << "Letter Truthtable:-\n";
    f.printTruthTableLetters();
    cout << "\n\n\n";

    cout << "Canonical SOP: ";
    f.printSOP();
    cout << "\n\n\n";

    cout << "Canonical POS: ";
    f.printPOS();
    cout << "\n\n\n";

    QM qm(f);
    string expression_before_simplification = f.getExpression();
    string expression = qm.findSimplifiedString();

    cout << "Prime Implicants:\n";
    qm.printPIs();
    cout << "\n\n";

    cout << "Essential Prime Implicants:\n";
    qm.printEPIs();
    cout << "\n\n";

    cout << "Minterms not covered by Essentials: ";
    qm.printNonEPIMinterms();
    cout << "\n\n";

    if (expression_before_simplification == "")
        cout << "Before Simplification: No expression provided\n\n";
    else
        cout << "Before Simplification(could be empty if not defined): " << expression_before_simplification << "\n\n";
    cout << "Simplified Expression(QM): " << expression << "\n\n";
}

void customCase() {
    string s;
    cout << "SOP String: ";
    getline(cin, s);
    cout << s << endl;

    BooleanFunction f(s);
    outputForFunction(f);
}

void predefinedCases() {
    Tester t;
    BooleanFunction NullFunction(0);

    vector<TestCase<string, BooleanFunction>> testCases = {
        {"abc + ab'", SUCCESS, BooleanFunction(3, {"a", "b", "c"}, {1, 5, 7}, {})}, // 1 5 7
        {"a'", SUCCESS, BooleanFunction(1, {"a"}, {0}, {})},
        {"''a+c", FAILURE, NullFunction},
        {"ab'", SUCCESS, BooleanFunction(2, {"a", "b"}, {1}, {})},
        {"ABCDEFGHI", SUCCESS, BooleanFunction(9, {"A", "B", "C", "D", "E", "F", "G", "H", "I"}, {511}, {})},
        {"A''bc+u", SUCCESS, BooleanFunction(4, {"A", "b", "c", "u"}, {7, 8, 9, 10, 11, 12, 13, 14, 15}, {})},
        {"'A+bc", FAILURE, NullFunction},
        {"A+1", FAILURE, NullFunction},
        {"l+u++i", FAILURE, NullFunction},
        {"e+(q+z)", FAILURE, NullFunction},
        {"e+q+z", SUCCESS, BooleanFunction(3, {"e", "q", "z"}, {1, 2, 3, 4, 5, 6, 7}, {})},
        {"o", SUCCESS, BooleanFunction(1, {"o"}, {1}, {})},
        {"(A+f))", FAILURE, NullFunction},
        {"abc'''''' + ab'", SUCCESS, BooleanFunction(3, {"a", "b", "c"}, {1, 5, 7}, {})},
        {"a'+b'+c'", SUCCESS, BooleanFunction(3, {"a", "b", "c"}, {0, 1, 2, 3, 4, 5, 6}, {})},
        {"a'''''   +    b+c", SUCCESS, BooleanFunction(3, {"a", "b", "c"}, {0, 2, 3, 4, 5, 6, 7}, {})},
        {"a'' + b'+'c", FAILURE, NullFunction},
        {"a-b+c", FAILURE, NullFunction},
        {"A+A", SUCCESS, BooleanFunction(1, {"A"}, {1}, {})},
        {"A+A+B+B+C+C", SUCCESS, BooleanFunction(3, {"A", "B", "C"}, {1, 2, 3, 4, 5, 6, 7}, {})},
        {"aba' + abc", SUCCESS, BooleanFunction(3, {"a", "b", "c"}, {7}, {})}
    };
    t.testSOPString(testCases);

    vector<BooleanFunction> functions;
    functions.push_back(BooleanFunction("A + AB + ABC +ABCD  + ABCDE +   ACEDFB"));
    functions.push_back(BooleanFunction(4, {"D", "C", "B", "A"}, {4,5,6,8,9,10,13}, {0,7,15}));
    functions.push_back(BooleanFunction(4, {"D", "C", "B", "A"}, {0,2,5,6,7,8,10,12,13,14,15}));
    functions.push_back(BooleanFunction("B + CD + ABD' + A'B'CD'"));
    functions.push_back(BooleanFunction(3, {"C", "B", "A"}, {1,3,5,6,7}));
    functions.push_back(BooleanFunction(5, {"E", "D", "C", "B", "A"}, {0, 2, 3, 5, 7, 9, 11, 13, 14, 16, 18, 24, 26, 28, 30}));
    functions.push_back(BooleanFunction("AC + AB' + A'BC + A'B'C' + ACA'B"));
    functions.push_back(BooleanFunction("A'B' + C' + D' + E'"));
    functions.push_back(BooleanFunction("XZ + ZX' + ZXY"));
    functions.push_back(BooleanFunction(10, {"J", "I", "H", "G", "F", "E", "D", "C", "B", "A"}, {0, 2, 3, 5, 7, 9, 11, 13, 14, 16, 18, 24, 26, 28, 30, 119, 140, 234, 407, 603, 599, 624, 813, 901}, {1020, 1, 50, 999, 142}));

    for (int i = 0; i < functions.size(); i++)
    {
        outputForFunction(functions[i]);
        cout << "Continue: ";
        string continueString;
        getline(cin, continueString);
    }
    
}

int main() {
    string choice;
    cout << "Run a custom test case / Run the pre-defined test cases:-(c/p) ";
    getline(cin, choice);
    if (choice == "c") {
        customCase();
    } else {
        // assume pre-defined
        predefinedCases();
    }
}