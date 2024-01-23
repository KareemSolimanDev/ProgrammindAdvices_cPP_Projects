#include <iostream>
#include <vector>
#include "libs/myOwnString.h"

using namespace std;

int main()
{

    clsString str1("Hi , Kareem");
    str1.clearValue();
    str1.setValue(" Hi, Kareem ");
    
    str1.Trim();
    str1.ReplaceAllWords("Hi","Hello");
    // other functions like that...
    
    vector <string> vec1={"Hello","world","\n"};
    cout << clsString::JoinStr(vec1," ");// to test static function

    cout << str1.getValue();//Hello, Kareem 
    
    return 0;
}