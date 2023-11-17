#include <vector>
#include <fstream>
#include <iomanip>
#include "config.h"
#include "helpers.h"

using namespace helpers;
using namespace configs;



namespace format
{
        sClient ConvertLineToRecord(string line)
    {
        vector<string> vSplitedRecord = SplitWords(line,delim);
        sClient record;
        record.accountNum = vSplitedRecord[0];
        record.pinCode = vSplitedRecord[1];
        record.name = vSplitedRecord[2];
        record.phone = vSplitedRecord[3];
        record.accountBalance = stof(vSplitedRecord[4]);
        return record;
    }

    string ConvertRecordToLine(sClient cliData,string delim)
    {
        string line=cliData.accountNum+delim;
        line+=cliData.pinCode+delim;
        line+=cliData.name+delim;
        line+=cliData.phone+delim;
        line+=to_string(cliData.accountBalance);
        return line;
    }

    vector<string> ConvertRecordsToLines(vector<sClient> Data,string delim)
    {
        vector<string> strData;
        
        for (sClient &client : Data)
        {
            strData.push_back(ConvertRecordToLine(client,delim));
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

//declare getData name space to solve curiculer dependancy
namespace getData{
    sClient GetUpdatedClientData();
};

namespace subProcess
{
    short FindClientData(vector<sClient> vData,string accountNum)
    {
        short DataIndex=-1;
        for (short client=0; client < vData.size() ;client++)
        {
            if (vData[client].accountNum==accountNum)
            {
                DataIndex = client;
                break;
            }
            
        }
        return DataIndex;
    }

    void UpdateRecordFromVector(vector<sClient> &vec,short RecordIndex)
    {
        sClient newRecord=getData::GetUpdatedClientData();
        newRecord.accountNum=vec[RecordIndex].accountNum;
        vec[RecordIndex]=newRecord;
    }
    void DeleteRecordFromVector(vector<sClient> &vec,short RecordIndex)
    {
        vec.erase(vec.begin()+RecordIndex);
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
        vector<string> ClientData=GetClientsDataFromFile();
        vector<sClient> FormatedClientData=format::FormatClientsData(ClientData);
        
        return FormatedClientData;

        // return format::FormatClientsData(GetClientsDataFromFile());
        // this commented code above cause a bad_alloc error  
        // visit README.md file in project notes number (3) 


    }

    string ReadPrimaryKey()
    {
        vector<sClient> vData=LoadClientData();
        string accountNumber=ReadString("Enter Account number.\n>> ");
        while (subProcess::FindClientData(vData,accountNumber)!=-1)
        {
            accountNumber=ReadString("Oops ,Client already exist ,Enter Another Account number.\n>> ");
        }
        
        return accountNumber;
    }

    sClient ReadClientData()
    {
        sClient CliData;
        cout << "\n\t\tPlease ,Enter client data.\n\n";
        CliData.accountNum=ReadPrimaryKey();
        CliData.pinCode=ReadString("Enter pin code.\n>> ");
        CliData.name=ReadString("Enter the name.\n>> ");
        CliData.phone=ReadString("Enter phone number.\n>> ");
        CliData.accountBalance=0;

        return CliData;
    }

    sClient GetUpdatedClientData()
    {
        sClient CliData;
        cout << "\n\t\tPlease enter new client data.\n\n";
        CliData.pinCode=ReadString("Enter new pin code.\n>> ");
        CliData.name=ReadString("Enter the new name.\n>> ");
        CliData.phone=ReadString("Enter new phone number.\n>> ");
        CliData.accountBalance=stof(ReadString("Enter new balance.\n>> "));

        return CliData;
    }
} // namespace getData
namespace printData
{
    
    void PrintClientData(sClient Data)
    {

        cout << "\t\t\t\t______Client Data______\n\n";
        cout << "===========================================================\n";
        cout << "Accout Number   : " << Data.accountNum << "\n" ;
        cout << "Pin Code        : " << Data.pinCode << "\n" ;
        cout << "Client Name     : " << Data.name << "\n" ;
        cout << "Phone           : " << Data.phone << "\n" ;
        cout << "Account Balance : " << Data.accountBalance << "\n" ;
        cout << "===========================================================" << endl;
    }
    void PrintSearchingResult(vector<sClient> vData,short ClientIndex)
    {
        

        if(ClientIndex!=-1)
        {
            PrintClientData(vData[ClientIndex]);
        }else{
            cout << "Oops , Client is not here" << endl;
        }
        
    }
} // namespace printData

namespace mainFuncs
{
        

    void AddClients()
    {
        do
        {
            string Data=format::ConvertRecordToLine(getData::ReadClientData(),delim);
            AppendDataToFile(fileName,Data);
            alert("Client has been added successfully.");
        } while (GetBoolResponse("Do you want to add anothr client. (y/n)","y"));
        
    }

    void PrintClientsData()
    {
        vector<sClient> vData = getData::LoadClientData();

        cout << "\n\t\t\t\t\tClient List (" << vData.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

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
        cout << "_________________________________________\n" << endl;
    }
    void SearchingResult()
    {
        string accountNum=ReadString("Enter Accout Number to search\n>> ");
        vector<sClient> vData=getData::LoadClientData();
        short ClientIndex=subProcess::FindClientData(vData,accountNum);

        printData::PrintSearchingResult(vData,ClientIndex);
    }
    // visit README.md file in project notes number (4) 
    void UpdateClient()
    {
        string accountNum=ReadString("Enter Accout Number to update\n>> ");

        vector<sClient> vData=getData::LoadClientData();
        short ClientIndex=subProcess::FindClientData(vData,accountNum);

        printData::PrintSearchingResult(vData,ClientIndex);

        if (ClientIndex!=-1)
        {
            bool continueupdateProcess=GetBoolResponse("Are you sure to update this client. (y/n)\n>> ","y");
            if (continueupdateProcess)
            {
                subProcess::UpdateRecordFromVector(vData,ClientIndex);
                WriteDataOnFile(fileName,format::ConvertRecordsToLines(vData,delim));
                alert("Client updated successfully");
            }
            
        }
    }
    void DeleteClient()
    {
        string accountNum=ReadString("Enter Accout Number to update\n>> ");

        vector<sClient> vData=getData::LoadClientData();
        short ClientIndex=subProcess::FindClientData(vData,accountNum);

        printData::PrintSearchingResult(vData,ClientIndex);

        if (ClientIndex!=-1)
        {
            bool continueupdateProcess=GetBoolResponse("Are you sure to update this client. (y/n)\n>> ","y");
            if (continueupdateProcess)
            {
                subProcess::DeleteRecordFromVector(vData,ClientIndex);
                WriteDataOnFile(fileName,format::ConvertRecordsToLines(vData,delim));
                alert("Client updated successfully");
            }
            
        }
    }
    

} // namespace mainFuncs
