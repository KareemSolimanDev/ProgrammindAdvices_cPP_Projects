#include <vector>
#include <fstream>
#include <iomanip>
#include "config.h"
#include "helpers.h"

using namespace helpers;
using namespace configs;

// declare some name spaces to solve curiculer dependancy

namespace getData
{
    sClient GetUpdatedClientData();
};
namespace links
{
    void toHome(bool load = true);
    void toTransScreen();
} // namespace links
//=======================================

namespace format
{
    sClient ConvertLineToRecord(string line)
    {
        vector<string> vSplitedRecord = SplitWords(line, delim);
        sClient record;
        record.accountNum = vSplitedRecord[0];
        record.pinCode = vSplitedRecord[1];
        record.name = vSplitedRecord[2];
        record.phone = vSplitedRecord[3];
        record.accountBalance = stof(vSplitedRecord[4]);
        return record;
    }

    string ConvertRecordToLine(sClient cliData, string delim)
    {
        string line = cliData.accountNum + delim;
        line += cliData.pinCode + delim;
        line += cliData.name + delim;
        line += cliData.phone + delim;
        line += to_string(cliData.accountBalance);
        return line;
    }

    vector<string> ConvertRecordsToLines(vector<sClient> Data, string delim)
    {
        vector<string> strData;

        for (sClient &client : Data)
        {
            strData.push_back(ConvertRecordToLine(client, delim));
        }
        return strData;
    }
    vector<sClient> FormatClientsData(vector<string> vData)
    {
        sClient formatedData;
        vector<sClient> vFormatedData;
        for (string &i : vData)
        {
            formatedData = ConvertLineToRecord(i);
            vFormatedData.push_back(formatedData);
        }
        return vFormatedData;
    }
} // namespace format

namespace subProcess
{
    short FindClientData(vector<sClient> vData, string accountNum)
    {
        short DataIndex = -1;
        for (short client = 0; client < vData.size(); client++)
        {
            if (vData[client].accountNum == accountNum)
            {
                DataIndex = client;
                break;
            }
        }
        return DataIndex;
    }

    void UpdateRecordFromVector(vector<sClient> &vec, short RecordIndex)
    {
        sClient newRecord = getData::GetUpdatedClientData();
        newRecord.accountNum = vec[RecordIndex].accountNum;
        vec[RecordIndex] = newRecord;
    }
    void DeleteRecordFromVector(vector<sClient> &vec, short RecordIndex)
    {
        vec.erase(vec.begin() + RecordIndex);
    }

    float CalcTotalBalances(vector<sClient> vData)
    {
        float total = 0;
        for (sClient i : vData)
        {
            total += i.accountBalance;
        }
        return total;
    }
} // namespace subProcess

namespace getData
{
    vector<string> GetClientsDataFromFile()
    {
        fstream File;
        string Data;
        vector<string> vData;
        File.open(fileName, ios::in);
        while (getline(File, Data))
        {
            vData.push_back(Data);
        }
        File.close();
        return vData;
    }

    vector<sClient> LoadClientData()
    {
        vector<string> ClientData = GetClientsDataFromFile();
        vector<sClient> FormatedClientData = format::FormatClientsData(ClientData);

        return FormatedClientData;

        // return format::FormatClientsData(GetClientsDataFromFile());
        // this commented code above cause a bad_alloc error
        // visit README.md file in project notes number (3)
    }

    string ReadPrimaryKey()
    {
        vector<sClient> vData = LoadClientData();
        string accountNumber = ReadString("Enter Account number.\n>> ");
        while (subProcess::FindClientData(vData, accountNumber) != -1)
        {
            accountNumber = ReadString("Oops ,Client already exist ,Enter Another Account number.\n>> ");
        }

        return accountNumber;
    }

    sClient ReadClientData()
    {
        sClient CliData;
        cout << "\n\t\tPlease ,Enter client data.\n\n";
        CliData.accountNum = ReadPrimaryKey();
        CliData.pinCode = ReadString("Enter pin code.\n>> ");
        CliData.name = ReadString("Enter the name.\n>> ");
        CliData.phone = ReadString("Enter phone number.\n>> ");
        CliData.accountBalance = 0;

        return CliData;
    }

    sClient GetUpdatedClientData()
    {
        sClient CliData;
        cout << "\n\t\tPlease enter new client data.\n\n";
        CliData.pinCode = ReadString("Enter new pin code.\n>> ");
        CliData.name = ReadString("Enter the new name.\n>> ");
        CliData.phone = ReadString("Enter new phone number.\n>> ");
        CliData.accountBalance = stof(ReadString("Enter new balance.\n>> "));

        return CliData;
    }
} // namespace getData

namespace printData
{

    void PrintClientData(sClient Data)
    {

        cout << "\t\t\t\t______Client Data______\n\n";
        cout << "===========================================================\n";
        cout << "Accout Number   : " << Data.accountNum << "\n";
        cout << "Pin Code        : " << Data.pinCode << "\n";
        cout << "Client Name     : " << Data.name << "\n";
        cout << "Phone           : " << Data.phone << "\n";
        cout << "Account Balance : " << Data.accountBalance << "\n";
        cout << "===========================================================" << endl;
    }
    void PrintSearchingResult(vector<sClient> vData, short ClientIndex)
    {

        if (ClientIndex != -1)
        {
            PrintClientData(vData[ClientIndex]);
        }
        else
        {
            cout << "Oops , Client is not here" << endl;
        }
    }
} // namespace printData

namespace ClientOprations
{

    void AddClients()
    {
        do
        {
            string Data = format::ConvertRecordToLine(getData::ReadClientData(), delim);
            AppendDataToFile(fileName, Data);
            alert("Client has been added successfully.");
        } while (GetBoolResponse("Do you want to add anothr client. (y/n)", "y"));
    }

    void PrintClientsData()
    {
        vector<sClient> vData = getData::LoadClientData();

        cout << "\n\t\t\t\t\tClient List (" << vData.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;

        if (vData.size() == 0)
        {
            cout << "\t\tOops ,There are no clients in the system!!\n";
        }

        for (sClient &Client : vData)
        {
            cout << "| " << setw(15) << left << Client.accountNum;
            cout << "| " << setw(10) << left << Client.pinCode;
            cout << "| " << setw(40) << left << Client.name;
            cout << "| " << setw(12) << left << Client.phone;
            cout << "| " << setw(12) << left << Client.accountBalance;
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    }
    void SearchingResult()
    {
        string accountNum = ReadString("Enter Accout Number to search\n>> ");
        vector<sClient> vData = getData::LoadClientData();
        short ClientIndex = subProcess::FindClientData(vData, accountNum);

        printData::PrintSearchingResult(vData, ClientIndex);
    }
    // visit README.md file in project notes number (4)
    void UpdateClient()
    {
        string accountNum = ReadString("Enter Accout Number to update\n>> ");

        vector<sClient> vData = getData::LoadClientData();
        short ClientIndex = subProcess::FindClientData(vData, accountNum);

        printData::PrintSearchingResult(vData, ClientIndex);

        if (ClientIndex != -1)
        {
            bool continueupdateProcess = GetBoolResponse("Are you sure to update this client. (y/n)\n>> ", "y");
            if (continueupdateProcess)
            {
                subProcess::UpdateRecordFromVector(vData, ClientIndex);
                WriteDataOnFile(fileName, format::ConvertRecordsToLines(vData, delim));
                alert("Client updated successfully");
            }
        }
    }
    void DeleteClient()
    {
        string accountNum = ReadString("Enter Accout Number to delete\n>> ");

        vector<sClient> vData = getData::LoadClientData();
        short ClientIndex = subProcess::FindClientData(vData, accountNum);

        printData::PrintSearchingResult(vData, ClientIndex);

        if (ClientIndex != -1)
        {
            bool continuedeleteProcess = GetBoolResponse("Are you sure to delete this client. (y/n)\n>> ", "y");
            if (continuedeleteProcess)
            {
                subProcess::DeleteRecordFromVector(vData, ClientIndex);
                WriteDataOnFile(fileName, format::ConvertRecordsToLines(vData, delim));
                alert("Client deleted successfully");
            }
        }
    }

} // namespace ClientOprations

namespace transactions
{
    unsigned GetTransactionAmount()
    {
        unsigned Amount = ReadNumInRange("Enter your amount to transaction\n>> ", 10);
        bool confirmProcess = GetBoolResponse("Are you sure to trans this amount (" + to_string(Amount) + "). (y/n)\n>> ", "y");
        return (confirmProcess) ? Amount : 0;
    }

    void TransactionProcess(enTransChoices choise)
    {
        string ProcessTitle = (choise == enTransChoices::Deposite) ? "Deposite" : "Withdraw";
        alert(ProcessTitle + " Screen");

        string accountNum = ReadString("Please ,Enter Client account number to " + ProcessTitle + ".\n>> ");
        vector<sClient> vData = getData::LoadClientData();
        short ClientIndex = subProcess::FindClientData(vData, accountNum);

        printData::PrintSearchingResult(vData, ClientIndex);

        if (ClientIndex != -1)
        {
            unsigned Amount = GetTransactionAmount();

            if (Amount)
            {
                vData[ClientIndex].accountBalance += (choise == enTransChoices::Deposite) ? Amount : -Amount;

                WriteDataOnFile(fileName, format::ConvertRecordsToLines(vData, delim));
                alert("Done ," + ProcessTitle + " process has been added successfully", 1);
            }
        }
    }

    void TotalBalancesFunc()
    {
        vector<sClient> vData = getData::LoadClientData();
        ClientOprations::PrintClientsData();
        alert("Total Balances = " + to_string(subProcess::CalcTotalBalances(vData)));
    }
} // namespace transactions

namespace mainScreensFuncs
{
    void CallSuitableProcess(enMainChoices choice);
    void CallSuitableTransaction(enTransChoices choise);

    void Home()
    {
        vector<string> menuItems = {"Show All Clients", "Add new client", "Find client", "Update client", "Delete client", "Transactions", "Exit"};
        system("cls");
        alert("Welcome Admin ,Dashboard here");
        menu("Main menu", menuItems);

        enMainChoices choice = (enMainChoices)ReadNumInRange("Please ,Enter your choice from menu : ", 1, menuItems.size());
        CallSuitableProcess(choice);
    }

    void TransactionsScreen()
    {
        vector<string> menuItems = {"Deposite", "Withdraw", "Total balances", "Main menu"};
        system("cls");
        alert("Transactions screen.");
        menu("Transactions menu", menuItems);
        enTransChoices choice = (enTransChoices)ReadNumInRange("Please ,Enter your choice from menu : ", 1, menuItems.size());
        CallSuitableTransaction(choice);
    }

    void CallSuitableProcess(enMainChoices choice)
    {
        system("cls");
        switch (choice)
        {
        case enMainChoices::ShowList:
            ClientOprations::PrintClientsData();
            links::toHome();
            break;
        case enMainChoices::Add:
            ClientOprations::AddClients();
            links::toHome();
            break;
        case enMainChoices::Search:
            ClientOprations::SearchingResult();
            links::toHome();
            break;
        case enMainChoices::Update:
            ClientOprations::UpdateClient();
            links::toHome();
            break;
        case enMainChoices::Delete:
            ClientOprations::DeleteClient();
            links::toHome();
            break;
        case enMainChoices::Transactions:
            TransactionsScreen();
            break;
        case enMainChoices::Exit:
            alert("Program Closed successfully");
            break;

        default:
            break;
        }
    }

    void CallSuitableTransaction(enTransChoices choise)
    {
        system("cls");
        switch (choise)
        {
        case enTransChoices::Deposite:
        case enTransChoices::Withdraw:
            transactions::TransactionProcess(choise);
            links::toTransScreen();
            break;
        case enTransChoices::TotalBalances:
            transactions::TotalBalancesFunc();
            links::toTransScreen();
            break;

        case enTransChoices::MainMenu:
            links::toHome(false);
            break;

        default:
            break;
        }
    }

} // namespace mainScreensFuncs

namespace links
{
    void toHome(bool load)
    {
        if (load)
        {
            cout << "We will go to the Home ,";
            system("pause");
        }

        mainScreensFuncs::Home();
    }
    void toTransScreen()
    {
        cout << "We will go to the transactions screen ,";
        system("pause");
        mainScreensFuncs::TransactionsScreen();
    }

} // namespace links
