#include "SOPString.h"

using namespace std;

SOPString::SOPString(string sop = "1") {
    expression = sop;
    expression_wo_spaces = "";
    expression_products = vector<string>(0);
    // if (!isValid()) {
    //     throw 
    // }
}

bool SOPString::validateAlphabet() {
    // check alphabet
    // remove spaces
    expression_wo_spaces = "";
    for (int i = 0; i < expression.length(); i++)
    {
        char c = expression[i];
        bool isSafe = false;
        bool isSpace = false;
        if (c == 32) { // space
            isSafe = true;
            isSpace = true;
        } else if (c == 39) // '
            isSafe = true;
        else if (c == 43) // +
            isSafe = true;
        else if (c == 48) // 0
            isSafe = true;
        else if (c == 49) // 1
            isSafe = true;
        else if (c >= 97 && c <= 122) { // a-z
            isSafe = true;
            variables["" + c] = variables.size(); // 2^n is an option
        }
        // else if (c >= 65 && c <= 90) { // A-Z
        //     isSafe = true;
        //     variables["" + c] = variables.size(); // 2^n is an option
        // }
        else
            isSafe = false;


        if (isSafe && !isSpace)
            expression_wo_spaces += c;
        else if (!isSafe)
            return false;
    }

    return true;
}
bool SOPString::validateProducts() {
    // break at +
    string product = "";
    for (int i = 0; i < expression_wo_spaces.length(); i++)
    {
        char c = expression[i];
        if (c != 43) // not +
            product += c;
        else {
            bool isSafe = true;
            // check no empty products
            if (product == "") isSafe = false;
            // check no ' starting products
            else if (product[0] == '\'') isSafe = false;

            if (isSafe)
                expression_products.push_back(product);
            else
                return false;
        }
    }
    return true;
}
bool SOPString::isValid() {
    if (!validateAlphabet()) return false;

    if (!validateProducts()) return false;
    
    return true;    
}

BooleanFunction SOPString::toFunction() {

    // convert products to function terms
}