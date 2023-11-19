#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace helpers
{
    string repeat(char letter, short Count)
    {
        string word = "";
        for (short i = 0; i < Count; i++)
        {
            word += letter;
        }
        return word;
    }

    void alert(string msg, short Xpadding = 15, short Ypadding = 1)
    {
        short width = (msg.length()) + (Xpadding * 2);

        cout << repeat('=', width) << repeat('\n', Ypadding);
        cout << repeat(' ', Xpadding) << msg << repeat('\n', Ypadding);
        cout << repeat('=', width) << endl;
    }

    void menu(string menuTitle, vector<string> &menuItems)
    {
        short Lmargin = menuTitle.length() + 2;

        cout << menuTitle << " :\n";
        for (short i = 0; i < menuItems.size(); i++)
        {
            cout << repeat(' ', Lmargin) << '[' << i + 1 << ']' << " : " << menuItems[i] << '\n';
        }
        cout << repeat('=', 60) << endl;
    }

    int ReadNumInRange(string msg, int min, int max = INT_MAX)
    {
        int num;
        bool errorMax = false;
        bool errorMin = false;
        do
        {
            if (errorMax)
            {
                cout << "Your number must be lower than : " << max << endl;
            }
            else if (errorMin)
            {
                cout << "Your number must be higher than : " << min << endl;
            }

            cout << msg;
            cin >> num;
            cin.ignore();

            (num < min) ? errorMin = true : errorMax = true;

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

    void AppendDataToFile(string fileName, string Data)
    {
        fstream myFile;
        myFile.open(fileName, ios::app);
        myFile << Data << endl;
        myFile.close();
    }

    bool GetBoolResponse(string msg, string passCase)
    {
        string ans;
        cout << msg;
        cin >> ans;
        cin.ignore();
        return ans == passCase;
    }
    vector<string> SplitWords(string sentence, string delim)
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

    void WriteDataOnFile(string fileName, vector<string> newData)
    {
        fstream File;
        File.open(fileName, ios::out);

        for (string &line : newData)
        {
            File << line << endl;
        }
        File.close();
    }
} // namespace helpers
