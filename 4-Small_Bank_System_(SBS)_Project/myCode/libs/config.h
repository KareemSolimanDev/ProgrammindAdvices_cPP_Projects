#include <string>
using namespace std;

namespace configs
{
    const string ClientsFileName = "db/Clients_Data.txt";
    const string AdminsFileName = "db/Admins_Data.txt";
    const string delim = "|##|";

    enum enMainChoices
    {
        ShowList = 1,
        Add,
        Search,
        Update,
        Delete,
        Transactions,
        Exit
    };
    enum enTransChoices
    {
        Deposite = 1,
        Withdraw,
        TotalBalances,
        MainMenu
    };

    struct sClient
    {
        string accountNum, pinCode, name, phone;
        float accountBalance;
    };
    struct sAdmin
    {
        string userName, password;
        short permitions;
    };

} // namespace configs
