#include <string>
using namespace std;

namespace configs
{

    enum enMainChoices
    {
        ShowList = 1,
        Add,
        Search,
        Update,
        Delete,
        Transactions,
        ManageAdmins,
        Logout,
    };
    enum enTransChoices
    {
        Deposite = 1,
        Withdraw,
        TotalBalances,
        MainMenu,
    };
    enum enManageAdminsChoices
    {
        ShowAdminList = 1,
        AddAdmin,
        SearchAdmin,
        UpdateAdmin,
        DeleteAdmin,
        MainMenuA,
    };
    enum enAdminPermissions
    {
        AllP=-1,
        ShowClientListP = 1,
        AddClientP = 2,
        SearchClientP = 4,
        UpdateClientP = 8,
        DeleteClientP = 16,
        TransactionsP = 32,
        ManageAdminsP = 64,
    };

    struct sClient
    {
        string accountNum, pinCode, name, phone;
        float accountBalance;
    };
    struct sAdmin
    {
        string userName, password;
        short permissions;
    };

    const string ClientsFileName = "db/Clients_Data.txt";
    const string AdminsFileName = "db/Admins_Data.txt";
    const string delim = "|##|";

    sAdmin __CurrentAdmin__;

} // namespace configs
