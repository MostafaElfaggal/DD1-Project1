#include <iostream>
#include "BooleanFunction.h"
#include "SOPString.h"
#include "Tester.h"

#include <vector>

using namespace std;

int main() {
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

    BooleanFunction f("aba' + abc");
    f.printTruthTable();
    cout << "\n\n\n";
    f.printTruthTableLetters();
    cout << "\n\n\n";
    f.printSOP();
    cout << "\n\n\n";
    f.printPOS();
    cout << "\n\n\n";
}