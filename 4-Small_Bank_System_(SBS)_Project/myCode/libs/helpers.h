#include <iostream>
#include <vector>

using namespace std;



namespace helpers
{
    string tabs(short tabsCount)
    {
        string tabs="";
        for (short i = 0; i < tabsCount; i++)
        {
            tabs += '\t';
        }
        return tabs;
    }
    
    void alert(string msg,short marginLeft=2)
    {
        cout << "===========================================================\n";
        cout << tabs(marginLeft) << msg << "\n";
        cout << "===========================================================" << endl;
    }

    void menu(vector<string> &menuItems,short marginLeft=2)
    {
        for (short i = 0; i < menuItems.size(); i++)
        {
            cout << tabs(marginLeft) << '[' << i+1 << ']' << " : " << menuItems[i] << '\n';
        }
        cout << "===========================================================" << endl;

    }

    int ReadNumInRange(string msg,int min,int max)
    {
        int num=min-1;
        do
        {
            cout << msg;
            cin >> num;
            cin.ignore();
        } while (num < min || num > max);

        return num;
    }
    string ReadString(string msg)
    {
        string stringInput;
        cout << msg;
        getline(cin, stringInput);
        return stringInput;
    }

    void AppendDataToFile(string fileName,string Data)
    {
        fstream myFile;
        myFile.open(fileName,ios::app);
        myFile << Data << endl;
        myFile.close();
    }

    bool GetBoolResponse(string msg,string passCase)
    {
        string ans;
        cout << msg;
        cin  >> ans;
        cin.ignore();
        return ans == passCase;
    }
    vector<string> SplitWords(string sentence,string delim)
    {
        vector<string> words = {};
        string word = "";
        sentence += delim;
        short delimPos = 0;

        while ((delimPos = sentence.find(delim)) != string::npos)
        {
            word = sentence.substr(0, delimPos);
            if (word != "")
            {
                words.push_back(word);
            }
            sentence.erase(0, delimPos + delim.length());
        }
        return words;
    }
    
    void WriteDataOnFile(string fileName,vector<string> newData)
    {
        fstream File;
        File.open(fileName,ios::out);
        
        for (string &line : newData)
        {
            File << line << endl;
        }
        File.close();

    }
} // namespace helpers


