#include <vector>
#include <fstream>
#include <iomanip>
#include "config.h"
#include "helpers.h"

using namespace helpers;
using namespace configs; // to use main variabels in config file without name space

// declare some name spaces to solve curiculer dependancy
namespace getData
{
    sClient GetUpdatedClientData();
    sAdmin GetUpdatedAdminData();
};
namespace links
{
    void toHome(bool load = true);
    void toTransScreen();
    void toAdminScreen();
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

    sAdmin ConvertLineToRecord(string line, bool isAdmin)
    {
        vector<string> vSplitedRecord = SplitWords(line, delim);
        sAdmin record;
        record.userName = vSplitedRecord[0];
        record.password = vSplitedRecord[1];
        record.permissions = stoi(vSplitedRecord[2]);
        return record;
    }

    string ConvertRecordToLine(sAdmin adminData, string delim)
    {
        string line = adminData.userName + delim;
        line += adminData.password + delim;
        line += to_string(adminData.permissions);
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

    vector<string> ConvertRecordsToLines(vector<sAdmin> Data, string delim)
    {
        vector<string> strData;

        for (sAdmin &admin : Data)
        {
            strData.push_back(ConvertRecordToLine(admin, delim));
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

    vector<sAdmin> FormatAdminsData(vector<string> vData)
    {
        sAdmin formatedData;
        vector<sAdmin> vFormatedData;
        for (string &i : vData)
        {
            formatedData = ConvertLineToRecord(i, true);
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
    short FindAdminData(vector<sAdmin> vData, string userName)
    {
        short DataIndex = -1;
        for (short Admin = 0; Admin < vData.size(); Admin++)
        {
            if (vData[Admin].userName == userName)
            {
                DataIndex = Admin;
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

    void UpdateRecordFromVector(vector<sAdmin> &vec, short RecordIndex)
    {
        sAdmin newRecord = getData::GetUpdatedAdminData();
        newRecord.userName = vec[RecordIndex].userName;
        vec[RecordIndex] = newRecord;
    }

    void DeleteRecordFromVector(vector<sClient> &vec, short RecordIndex)
    {
        vec.erase(vec.begin() + RecordIndex);
    }

    void DeleteRecordFromVector(vector<sAdmin> &vec, short RecordIndex)
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
    vector<string> GetDataFromFile(string fileName)
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

    vector<sClient> LoadClientsData()
    {
        vector<string> ClientData = GetDataFromFile(ClientsFileName);
        vector<sClient> FormatedClientData = format::FormatClientsData(ClientData);

        return FormatedClientData;

        // return format::FormatClientsData(GetDataFromFile());
        // this commented code above cause a bad_alloc error
        // visit README.md file in project notes number (3)
    }

    vector<sAdmin> LoadAdminsData()
    {
        vector<string> AdminData = GetDataFromFile(AdminsFileName);
        vector<sAdmin> FormatedAdminData = format::FormatAdminsData(AdminData);

        return FormatedAdminData;
    }

    string ReadAccountNumber()
    {
        vector<sClient> vData = LoadClientsData();
        string accountNumber = ReadString("Enter Account number.\n>> ");
        while (subProcess::FindClientData(vData, accountNumber) != -1)
        {
            accountNumber = ReadString("Oops ,Client already exist ,Enter Another Account number.\n>> ");
        }

        return accountNumber;
    }

    string ReadUserName()
    {
        vector<sAdmin> vData = LoadAdminsData();
        string userName = ReadString("Enter user name.\n>> ");
        while (subProcess::FindAdminData(vData, userName) != -1)
        {
            userName = ReadString("Oops ,Admin already exist ,Enter Another User name.\n>> ");
        }

        return userName;
    }

    sClient ReadClientData()
    {
        sClient CliData;
        cout << "\n\t\tPlease ,Enter client data.\n\n";
        CliData.accountNum = ReadAccountNumber();
        CliData.pinCode = ReadString("Enter pin code.\n>> ");
        CliData.name = ReadString("Enter the name.\n>> ");
        CliData.phone = ReadString("Enter phone number.\n>> ");
        CliData.accountBalance = 0;

        return CliData;
    }

    short ReadPermissions()
    {
        short PerNum = 0;
        if (GetBoolResponse("Do you want to give full access,(y/n)\n>>", "y"))
        {
            PerNum = enAdminPermissions::AllP;
        }
        else
        {
            cout << "Do you want to give access to :\n";
            PerNum |= (GetBoolResponse("Show Client list,(y/n)\n>>", "y") ? enAdminPermissions::ShowClientListP : 0);

            PerNum |= (GetBoolResponse("Add Client,(y/n)\n>>", "y") ? enAdminPermissions::AddClientP : 0);

            PerNum |= (GetBoolResponse("Find Client,(y/n)\n>>", "y") ? enAdminPermissions::SearchClientP : 0);

            PerNum |= (GetBoolResponse("Update Client,(y/n)\n>>", "y") ? enAdminPermissions::UpdateClientP : 0);

            PerNum |= (GetBoolResponse("Delete Client,(y/n)\n>>", "y") ? enAdminPermissions::DeleteClientP : 0);

            PerNum |= (GetBoolResponse("TransActions,(y/n)\n>>", "y") ? enAdminPermissions::TransactionsP : 0);

            PerNum |= (GetBoolResponse("Manage admins,(y/n)\n>>", "y") ? enAdminPermissions::ManageAdminsP : 0);
        }

        return PerNum;
    }

    sAdmin ReadAdminData()
    {
        sAdmin AdminData;
        cout << "\n\t\tPlease ,Enter Admin data.\n\n";
        AdminData.userName = ReadUserName();
        AdminData.password = ReadString("Enter password.\n>> ");
        AdminData.permissions = ReadPermissions();

        return AdminData;
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
    sAdmin GetUpdatedAdminData()
    {
        sAdmin AdminData;
        cout << "\n\t\tPlease enter new Admin data.\n\n";
        AdminData.password = ReadString("Enter new password.\n>> ");
        AdminData.permissions = ReadPermissions();

        return AdminData;
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
    void PrintAdminData(sAdmin Data)
    {
        cout << "\t\t\t\t______Client Data______\n\n";
        cout << "===========================================================\n";
        cout << "User Name   : " << Data.userName << "\n";
        cout << "Password        : " << Data.password << "\n";
        cout << "Permissions     : " << Data.permissions << "\n";
        cout << "===========================================================" << endl;
    }

    void PrintSearchingResult(vector<sAdmin> vData, short ClientIndex)
    {

        if (ClientIndex != -1)
        {
            PrintAdminData(vData[ClientIndex]);
        }
        else
        {
            cout << "Oops , Admin is not here" << endl;
        }
    }
} // namespace printData

namespace SecurityOperations
{
    sAdmin CheckAdminData(string userName, string password)
    {
        /**
         * this function check is porvided data is true or not
         * if true function return admin
         * otherwise function return NULLAdmin={"NULL","NULL",0}
        */
        vector<sAdmin> vData = getData::LoadAdminsData();
        short AdminIndex=subProcess::FindAdminData(vData,userName);
        
        if (AdminIndex!=-1)
        {
            sAdmin Admin=vData[AdminIndex];
            if (Admin.password==password)
                return Admin;
            
        }
        
        return {"NULL", "NULL", 0};
    }

    void Login()
    {
        sAdmin admin;
        bool LoginFailed = false;
        string userName, password;
        do
        {
            system("cls");
            alert("Login Screen.");

            if (LoginFailed)
                cout << "Oops,Data is incorrect!!, please try again\n";

            userName = ReadString("Enter your user name.\n>> ");
            password = ReadString("Enter your password.\n>> ");

            // add returned admin to admin var, check if returned admin is the admin who we want
            LoginFailed = !((admin = CheckAdminData(userName, password)).userName == userName);

        } while (LoginFailed);

        __CurrentAdmin__=admin;

        links::toHome(false);
    }

    bool AccessAllowed(enMainChoices choice)
    {
        // to convert choice to enAdminPermissions(Search=3 but in permition =4 that means pow(2,search-1) )
        enAdminPermissions permission = enAdminPermissions(pow(2, double(choice) - 1));

        if (__CurrentAdmin__.permissions == enAdminPermissions::AllP || ((__CurrentAdmin__.permissions & permission) == permission))
        {
            return true;
        }
        return false;
    }

    void Logout()
    {
        alert("You logged out successfully");
        if (GetBoolResponse("Do you login again?(y/n)\n>> ","y"))
            Login();
        else
            alert("Program Closed");
        
    }
} // namespace SecurityOperations

namespace ClientOprations
{

    void AddClients()
    {
        do
        {
            string Data = format::ConvertRecordToLine(getData::ReadClientData(), delim);
            AppendDataToFile(ClientsFileName, Data);
            alert("Client has been added successfully.");
        } while (GetBoolResponse("Do you want to add anothr client. (y/n)", "y"));
    }

    void PrintClientsData()
    {
        vector<sClient> vData = getData::LoadClientsData();

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
        vector<sClient> vData = getData::LoadClientsData();
        short ClientIndex = subProcess::FindClientData(vData, accountNum);

        printData::PrintSearchingResult(vData, ClientIndex);
    }
    // visit README.md file in project notes number (4)
    void UpdateClient()
    {
        string accountNum = ReadString("Enter Accout Number to update\n>> ");

        vector<sClient> vData = getData::LoadClientsData();
        short ClientIndex = subProcess::FindClientData(vData, accountNum);

        printData::PrintSearchingResult(vData, ClientIndex);

        if (ClientIndex != -1)
        {
            bool continueupdateProcess = GetBoolResponse("Are you sure to update this client. (y/n)\n>> ", "y");
            if (continueupdateProcess)
            {
                subProcess::UpdateRecordFromVector(vData, ClientIndex);
                WriteDataOnFile(ClientsFileName, format::ConvertRecordsToLines(vData, delim));
                alert("Client updated successfully");
            }
        }
    }
    void DeleteClient()
    {
        string accountNum = ReadString("Enter Accout Number to delete\n>> ");

        vector<sClient> vData = getData::LoadClientsData();
        short ClientIndex = subProcess::FindClientData(vData, accountNum);

        printData::PrintSearchingResult(vData, ClientIndex);

        if (ClientIndex != -1)
        {
            bool continuedeleteProcess = GetBoolResponse("Are you sure to delete this client. (y/n)\n>> ", "y");
            if (continuedeleteProcess)
            {
                subProcess::DeleteRecordFromVector(vData, ClientIndex);
                WriteDataOnFile(ClientsFileName, format::ConvertRecordsToLines(vData, delim));
                alert("Client deleted successfully");
            }
        }
    }

} // namespace ClientOprations

namespace AdminOprations
{

    void AddAdmins()
    {
        do
        {
            string Data = format::ConvertRecordToLine(getData::ReadAdminData(), delim);
            AppendDataToFile(AdminsFileName, Data);
            alert("Admin has been added successfully.");
        } while (GetBoolResponse("Do you want to add anothr Admin. (y/n)", "y"));
    }

    void PrintAdminsData()
    {
        vector<sAdmin> vData = getData::LoadAdminsData();

        cout << "\n\t\t\t\t\tAdmin List (" << vData.size() << ") admin(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        cout << "| " << left << setw(10) << "User name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;

        for (sAdmin &admin : vData)
        {
            cout << "| " << setw(10) << left << admin.userName;
            cout << "| " << setw(10) << left << admin.password;
            cout << "| " << setw(12) << left << admin.permissions;
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    }
    void SearchingResult()
    {
        string userName = ReadString("Enter User name to search\n>> ");
        vector<sAdmin> vData = getData::LoadAdminsData();
        short AdminIndex = subProcess::FindAdminData(vData, userName);

        printData::PrintSearchingResult(vData, AdminIndex);
    }
    // visit README.md file in project notes number (4)
    void UpdateAdmin()
    {
        string userName = ReadString("Enter user name to update\n>> ");

        vector<sAdmin> vData = getData::LoadAdminsData();
        short AdminIndex = subProcess::FindAdminData(vData, userName);

        printData::PrintSearchingResult(vData, AdminIndex);

        if (AdminIndex != -1)
        {
            bool continueupdateProcess = GetBoolResponse("Are you sure to update this Admin. (y/n)\n>> ", "y");
            if (continueupdateProcess)
            {
                subProcess::UpdateRecordFromVector(vData, AdminIndex);
                WriteDataOnFile(AdminsFileName, format::ConvertRecordsToLines(vData, delim));
                alert("Admin updated successfully");
            }
        }
    }
    void DeleteAdmin()
    {
        string userName = ReadString("Enter user name to delete\n>> ");

        vector<sAdmin> vData = getData::LoadAdminsData();
        short AdminIndex = subProcess::FindAdminData(vData, userName);

        printData::PrintSearchingResult(vData, AdminIndex);

        if (AdminIndex != -1)
        {
            bool continuedeleteProcess = GetBoolResponse("Are you sure to delete this Admin. (y/n)\n>> ", "y");
            if (continuedeleteProcess)
            {
                subProcess::DeleteRecordFromVector(vData, AdminIndex);
                WriteDataOnFile(AdminsFileName, format::ConvertRecordsToLines(vData, delim));
                alert("Admin deleted successfully");
            }
        }
    }

} // namespace AdminOprations

namespace transactions
{
    float GetTransactionAmount(enTransChoices choice, float accountBalance)
    {
        float Amount;
        if (choice == enTransChoices::Withdraw)
            Amount = ReadNumInRange("Enter your amount to transaction\n>> ", 10, accountBalance);
        else
            Amount = ReadNumInRange("Enter your amount to transaction\n>> ", 10);

        bool confirmProcess = GetBoolResponse("Are you sure to trans this amount (" + to_string(Amount) + "). (y/n)\n>> ", "y");
        return (confirmProcess) ? Amount : 0;
    }

    void TransactionProcess(enTransChoices choise)
    {
        string ProcessTitle = (choise == enTransChoices::Deposite) ? "Deposite" : "Withdraw";
        alert(ProcessTitle + " Screen");

        string accountNum = ReadString("Please ,Enter Client account number to " + ProcessTitle + ".\n>> ");
        vector<sClient> vData = getData::LoadClientsData();
        short ClientIndex = subProcess::FindClientData(vData, accountNum);

        printData::PrintSearchingResult(vData, ClientIndex);

        if (ClientIndex != -1)
        {
            float Amount = GetTransactionAmount(choise, vData[ClientIndex].accountBalance);

            if (Amount)
            {
                vData[ClientIndex].accountBalance += ((choise == enTransChoices::Deposite) ? Amount : -Amount);

                WriteDataOnFile(ClientsFileName, format::ConvertRecordsToLines(vData, delim));
                alert("Done ," + ProcessTitle + " process has been added successfully", 1);
            }
        }
    }

    void TotalBalancesFunc()
    {
        vector<sClient> vData = getData::LoadClientsData();
        ClientOprations::PrintClientsData();
        alert("Total Balances = " + to_string(subProcess::CalcTotalBalances(vData)));
    }
} // namespace transactions

namespace mainScreensFuncs
{
    void CallSuitableProcess(enMainChoices choice);
    void CallSuitableProcess(enManageAdminsChoices choice);
    void CallSuitableTransaction(enTransChoices choise);

    void Home()
    {
        vector<string> menuItems = {"Show All Clients", "Add new client", "Find client", "Update client", "Delete client", "Transactions", "Manage admins", "Logout"};
        system("cls");
        alert("Welcome " + __CurrentAdmin__.userName + " ,Dashboard here");
        menu("Main menu", menuItems);

        enMainChoices choice = (enMainChoices)ReadNumInRange("Please ,Enter your choice from menu : ", 1, menuItems.size() + 1);
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

    void ManageAdminsScreen()
    {
        vector<string> menuItems = {"Show All admins", "Add new admin", "Find admin", "Update admin", "Delete admin", "Main menu"};
        system("cls");
        alert("Manage Admins Screen");
        menu("Admin menu", menuItems);

        enManageAdminsChoices choice = (enManageAdminsChoices)ReadNumInRange("Please ,Enter your choice from menu : ", 1, menuItems.size());
        CallSuitableProcess(choice);
    }

    void CallSuitableProcess(enMainChoices choice)
    {
        system("cls");

        if (SecurityOperations::AccessAllowed(choice) || choice == enMainChoices::Logout)
        {
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
            case enMainChoices::ManageAdmins:
                ManageAdminsScreen();
                break;
            case enMainChoices::Logout:
                SecurityOperations::Logout();
                break;
            default:
                break;
            }
        }
        else
        {
            alert("Oops, Access to this page is denied !!");
            links::toHome();
        }
    }

    void CallSuitableProcess(enManageAdminsChoices choice)
    {
        system("cls");
        switch (choice)
        {
        case enManageAdminsChoices::ShowAdminList:
            AdminOprations::PrintAdminsData();
            links::toAdminScreen();
            break;
        case enManageAdminsChoices::AddAdmin:
            AdminOprations::AddAdmins();
            links::toAdminScreen();
            break;
        case enManageAdminsChoices::SearchAdmin:
            AdminOprations::SearchingResult();
            links::toAdminScreen();
            break;
        case enManageAdminsChoices::UpdateAdmin:
            AdminOprations::UpdateAdmin();
            links::toAdminScreen();
            break;
        case enManageAdminsChoices::DeleteAdmin:
            AdminOprations::DeleteAdmin();
            links::toAdminScreen();
            break;
        case enManageAdminsChoices::MainMenuA:
            links::toHome(false);
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
    void toAdminScreen()
    {
        cout << "We will go to the admin screen ,";
        system("pause");
        mainScreensFuncs::ManageAdminsScreen();
    }


} // namespace links
