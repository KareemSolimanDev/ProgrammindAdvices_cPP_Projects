#pragma once
#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
    string _Value;

    short Lenght(string value)
    {
        short counter =0;
        for (char &i : value)
        {
            counter++;
        }
        return counter;
    }

    string UpperFirstLetters(string sentence)
        {
            bool isFirst=true;

            for(int i = 0; i < sentence.length(); i++)
            {
                if (sentence[i]!=' '&&isFirst)
                {
                    sentence[i]=toupper(sentence[i]);
                }
                isFirst=(sentence[i]==' '?true:false);
            }
            return sentence;
        }

    string LowerFirstLetters(string sentence)
    {
        bool isFirst=true;

        for(int i = 0; i < sentence.length(); i++)
        {
            if (sentence[i]!=' '&&isFirst)
            {
                sentence[i]=tolower(sentence[i]);
            }
            isFirst=(sentence[i]==' '?true:false);
        }
        return sentence;
    }

    string UpperLetters(string sentence)
    {

        for(int i = 0; i < sentence.length(); i++)
        {
            sentence[i]=toupper(sentence[i]);
        }
        return sentence;
    }

    string LowerLetters(string sentence)
    {

        for(int i = 0; i < sentence.length(); i++)
        {
                sentence[i]=tolower(sentence[i]);
        }
        return sentence;
    }

    char InvertCharCase(char character)
    {
        return isupper(character)?tolower(character):toupper(character);
    }

    string InvertStringCase(string sentence)
    {
        for(int i = 0; i < sentence.length(); i++)
        {
            sentence[i]=InvertCharCase(sentence[i]);
        }
        return sentence;
    }

    short CountUpperCase(string sentence)
    {
        short counter;
        for(char &i : sentence)
        {
                if (isupper(i))
                {
                    counter++;
                }
                
        }
        return counter;
    }

    short CountLowerCase(string sentence)
    {
        short counter;
        for(char &i : sentence)
        {
                if (islower(i))
                {
                    counter++;
                }
                
        }
        return counter;
    }

    short CountSpacificChar(string sentence, char wantedChar, bool CaseSensitive = true)
    {
        short counter;
        for (char &i : sentence)
        {

            if (CaseSensitive)
            {
                if (i == wantedChar)
                {
                    counter++;
                }
            }
            else
            {
                if (tolower(i) == tolower(wantedChar))
                    counter++;
            }
        }

        return counter;
    }

    bool IsVowel(char ch)
    {
        ch=tolower(ch);
        return ch=='a'||ch=='e'||ch=='o'||ch=='u'||ch=='i';
    }

    short CountVowelLetters(string sentence)
    {
        short counter=0;
        for(char &i : sentence)
        {
                if (IsVowel(i))
                {
                    counter++;
                }
                
        }
        return counter;
    }

    short CountSpratedWords(string sentence, string delim)
    {
        string word = "";
        sentence += delim;
        short delimPos = 0;
        short counter=0;

        while((delimPos=sentence.find(delim))!=string::npos)
        {
            word=sentence.substr(0,delimPos);
            if (word!="")
            {
                counter++;
            }
            sentence.erase(0,delimPos+delim.length());
        }
        return counter;
    }

    vector <string> SplitWords(string sentence, string delim)
    {
        vector <string> words={};
        string word="";
        sentence += delim;
        short delimPos = 0;
        

        while((delimPos=sentence.find(delim))!=string::npos)
        {
            word=sentence.substr(0,delimPos);
            if (word!="")
            {
                words.push_back(word);
            }
            sentence.erase(0,delimPos+delim.length());
        }
        return words;
    }

    string Ltrim(string sentence)
    {
        while(sentence[0]==' ')
        {
            sentence.erase(0,1);
        }
        return sentence;
    }

    string Rtrim(string sentence)
    {
        int lastIndex=sentence.length()-1;
        while(sentence[lastIndex]==' ')
        {
            sentence.erase(lastIndex,lastIndex+1);
            lastIndex=sentence.length()-1;
        }
        return sentence;
    }

    string Trim(string sentence)
    {
        return Rtrim(Ltrim(sentence));
    }

    string ReplaceAllWords(string str,string toReplace,string replaceTo)
    {
        short pos=str.find(toReplace);
        while(pos!=string::npos)
        {
            str.replace(pos,toReplace.length(),replaceTo);
            pos=str.find(toReplace);
        }
        return str;
    }

    string RemovePunctSigns(string str)
    {
        for (short i = 0; i < str.length(); i++)
        {
            if (ispunct(str[i]))
            {
                str[i]=char(0);
            }
            
        }
        return str;
    }






public:
    clsString(string value="")
    {
        _Value=value;
    }
    string getValue() {return _Value;}
    void setValue(string value) {_Value=value;}
    void appendValue(string value) {_Value+=" " + value;}
    void clearValue() {_Value=" ";}

    static string JoinStr(vector<string> vec, string delim, bool reverse = false)
    {

        string joinedVec = "";

        if (reverse)
        {
            vector<string>::iterator iter = vec.end();
            while (iter != vec.begin())
            {
                --iter;
                joinedVec += *iter + delim;
            }
        }
        else
        {

            vector<string>::iterator iter = vec.begin();
            while (iter != vec.end())
            {
                joinedVec += *iter + delim;
                ++iter;
            }
        }

        return joinedVec.substr(0, joinedVec.length() - delim.length());
    }


    short Lenght()
    {
        return Lenght(_Value);
    }

    void UpperFirstLetters()
        {
            _Value=UpperFirstLetters(_Value);
        }

    void LowerFirstLetters()
    {
        _Value=LowerFirstLetters(_Value);
    }

    void UpperLetters()
        {
            _Value=UpperLetters(_Value);
        }

    void LowerLetters()
        {
            _Value=LowerLetters(_Value);
        }

    void InvertStringCase()
    {
        _Value = InvertStringCase(_Value);
    }

    short CountUpperCase()
    {
        return CountUpperCase(_Value);
    }

    short CountLowerCase()
    {
        return CountLowerCase(_Value);
    }

    short CountSpacificChar(char wantedChar, bool CaseSensitive = true)
    {
        return CountSpacificChar(_Value,wantedChar,CaseSensitive);
    }

    short CountVowelLetters()
    {
        return CountVowelLetters(_Value);
    }

    short CountSpratedWords(string delim)
    {
        return CountSpratedWords(_Value,delim);
    }

    vector <string> SplitWords(string delim)
    {
        return SplitWords(_Value,delim);
    }

    void Rtrim()
    {
        _Value=Rtrim(_Value);
    }

    void Ltrim()
    {
        _Value=Ltrim(_Value);
    }

    void Trim()
    {
        _Value=Trim(_Value);
    }

    void ReplaceAllWords(string toReplace,string replaceTo)
    {
        _Value = ReplaceAllWords(_Value,toReplace,replaceTo);
    }

    void RemovePunctSigns()
    {
        _Value = RemovePunctSigns(_Value);
    }



};