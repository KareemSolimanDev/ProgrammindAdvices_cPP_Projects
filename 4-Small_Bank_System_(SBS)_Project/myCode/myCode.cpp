#include <iostream>
#include "libs/mainFuncs.h"

using namespace std;
using namespace mainFuncs;


enum enChoices{ShowList=1,Add,Search,Update,Delete,Exit};

void Home();
void toHome();
void CallSuitableProcess(enChoices choice);

// ===============================================
// ===============|__start_main__|================
// ===============================================

int main()
{

    Home();

    return 0;
}

// ===============================================
// ===============|__end_main__|==================
// ===============================================

void Home()
{
    vector<string> menuItems={"Show All Clients" ,"Add new client" ,"Find client" ,"Update client" ,"Delete client" ,"Exit"};
    system("cls");
    alert("Welcome Admin ,Dashboard here");
    menu(menuItems,1);

    enChoices choice=(enChoices) ReadNumInRange("Please ,Enter your choice from menu : ",1,menuItems.size());
    CallSuitableProcess(choice);
}

void toHome()
{
    cout << "We will go to the Home ,";
    system("pause");
    Home();
}

void CallSuitableProcess(enChoices choice)
{

    system("cls");
    switch (choice)
    {
    case enChoices::ShowList :
        PrintClientsData();
        toHome();
        break;
    case enChoices::Add :
        AddClients();
        toHome();
        break;
    case enChoices::Search :
        SearchingResult();
        toHome();
        break;
    case enChoices::Update :
        UpdateClient();
        toHome();
        break;
    case enChoices::Delete :
        DeleteClient();
        toHome();
        break;
    case enChoices::Exit :
        alert("Program Closed successfully");
        break;
    
    default:
        break;
    }
}

