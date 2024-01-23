# (OOP) String_Library_Project

### How it work
<hr>
make object from clsString class and assign value with constructor prameters
and use functions to play with value inside object , use getValue() to get the Value and other functions to do her job.

#### example :

```cpp
clsString str1("Hi , Kareem");

str1.clearValue();
str1.setValue(" Hi, Kareem ");

str1.Trim();
str1.ReplaceAllWords("Hi","Hello");
// other functions like that...

vector <string> vec1={"Hello","world","\n"};
cout << clsString::JoinStr(vec1," ");// to test static function

cout << str1.getValue();//Hello, Kareem 
```

### Project notes
<hr>

1. In this project i use simple OOP paradigm.
2. Every function documented by her name.
3. this project contain 21 function related by string manipulation :
    1. UpperFirstLetters()
    2. LowerFirstLetters()
    3. UpperLetters()
    4. LowerLetters()
    5. InvertStringCase()
    6. CountUpperCase()
    7. CountLowerCase()
    8. CountSpacificChar()
    9. CountVowelLetters()
    10. CountSpratedWords()
    11. SplitWords()
    12. Rtrim()
    13. Ltrim()
    14. Trim()
    15. ReplaceAllWords()
    16. RemovePunctSigns()
    17. getValue()
    18. setValue()
    19. appendValue()
    20. clearValue()
    21. <b>static</b> joinStr()
4. use one static function (for test static functions concept) to call it by class name without object
5. <b>!mportant note :</b> this code on learning vhase and all functions made by me before watching solution.

<b>^_^</b>