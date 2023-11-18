#include <string>
using namespace std;

namespace configs
{
    const string fileName="Clients_Data.txt";
    const string delim="|##|";

    enum enMainChoices{ShowList=1,Add,Search,Update,Delete,Transactions,Exit};
    enum enTransChoices{Deposite=1,Withdraw,TotalBalances,MainMenu};

    struct sClient{
        string accountNum,pinCode,name,phone;
        float accountBalance;
    };
} // namespace configs
