#include <string>
using namespace std;

namespace configs
{
    const string fileName="Clients_Data.txt";
    const string delim="|##|";

    struct sClient{
        string accountNum,pinCode,name,phone;
        float accountBalance;
    };
} // namespace configs
