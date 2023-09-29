#include <iostream>

using namespace std;

enum enWorkStatus{Remotly=1,PartTime=2,FullTime=3};

struct Address
{
    string Country;
    string City;
    string Street;
    unsigned short BlockNum;

};

struct ContactInfo
{
    string Phone;
    string Email;
    Address Address;

};

struct User
{
    string Name;
    char Gender;
    int WorkStatus;
    unsigned short Age;
    unsigned short MonthlySalary;
    bool Married;
    ContactInfo ContactInfo;
};


int CalcYearlySalary(unsigned short monthlySalary,int WorkStatus)
{

    switch (WorkStatus)
    {

    case Remotly:
        monthlySalary+=100;
        break;

    case PartTime:
        monthlySalary+=200;
        break;

    case FullTime:
        monthlySalary+=300;
        break;

    default:
        monthlySalary=0;
        break;

    }

    return monthlySalary*12;
}

void ReadData(User &user)
{

    cout << "Enter your name :";
    getline(cin,user.Name);
    cout << "Enter your age :";
    cin >> user.Age;
    cout << "Enter your work status \n(1)remotly  \n(2)part time \n(3)full time\n:";
    cin >> user.WorkStatus;
    cout << "Enter your city :";
    cin >> user.ContactInfo.Address.City;
    cout << "Enter your country :";
    cin >> user.ContactInfo.Address.Country;
    cout << "Enter your street name :";
    cin >> user.ContactInfo.Address.Street;
    cout << "Enter your Block number :";
    cin >> user.ContactInfo.Address.BlockNum;
    cout << "Enter your monthly salary :";
    cin >> user.MonthlySalary;
    cout << "Enter your email :";
    cin >> user.ContactInfo.Email;
    cout << "Enter your phone number :";
    cin >> user.ContactInfo.Phone;
    cout << "Enter your Gender (female:f, male:m):";
    cin >> user.Gender;
    cout << "Enter your Married (true:1, false:0) :";
    cin >> user.Married;
    cin.ignore();

}

void PrintData(User user)
{


    cout << "##########__Data__###########" << endl;
    cout << "Name : " << user.Name << endl;
    cout << "Age : " << user.Age << endl;
    cout << "Work status : " << user.WorkStatus<< endl;
    cout << "Address :" << endl;
    cout << "\tCountry : " << user.ContactInfo.Address.Country << endl;
    cout << "\tCity : " << user.ContactInfo.Address.City << endl;
    cout << "\tStreet : " << user.ContactInfo.Address.Street << endl;
    cout << "\tBlock number : " << user.ContactInfo.Address.BlockNum << endl;
    cout << "Contact Info : " <<  endl;
    cout << "\tPhone : " << user.ContactInfo.Phone << endl;
    cout << "\tEmail : " << user.ContactInfo.Email << endl;
    cout << "MonthlySalary : " << user.MonthlySalary << endl;
    cout << "YearlySalary : " << CalcYearlySalary(user.MonthlySalary,user.WorkStatus) << endl;
    cout << "Gender : " << user.Gender << endl;
    cout << "Married : " << user.Married << endl;
    cout << "#############################\n";
}

void ReadAllData(User user[],unsigned short length)
{

    for(unsigned short i=0;i<length;i++)
    {
        cout << "enter person "<< i+1<<endl;
        ReadData(user[i]);
    }


}

void PrintAllData(User user[],unsigned short length)
{
    for(unsigned short i=0;i<length;i++)
    {
        cout << "Person "<< i+1 << " Data"<<endl;
        PrintData(user[i]);
    }
}

void GetNumberOfRequests(unsigned short &numberOfPersons)
{

    cout << "Enter number of persons you want to add : ";
    cin >> numberOfPersons;
    cin.ignore();
}

int main()
{
    unsigned short numberOfPersons;
    GetNumberOfRequests(numberOfPersons);

    User user[numberOfPersons];

    ReadAllData(user,numberOfPersons);
    PrintAllData(user,numberOfPersons);
    return 0;
}