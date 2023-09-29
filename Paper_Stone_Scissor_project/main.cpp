#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;
enum enWinnerplayer{Non=0,User=1,Computer=2};
enum enChoices{Paper=1,Stone=2,Scissor=3};


struct stPlayerResult
{
    int WinCount=0;
    int DrawCount=0;
    int LoseCount=0;
    enWinnerplayer Winner()
    {
        if (WinCount>LoseCount)
        {
            return enWinnerplayer::User;
        }else if (WinCount<LoseCount)
        {
            return enWinnerplayer::Computer;
        }else{
            return enWinnerplayer::Non;
        }
        
    }
};

unsigned ReadPositiveNumber(string msg)
{
    int num=0;
    do
    {
        cout << msg << endl;
        cout << ">>>";
        cin >> num;
    } while (num<=0);
    return num;
}

enChoices GetUserChoice()
{
    short choice;
    do
    {
        cout << "What is your Choice ? must be :\n1)Paper\n2)Stone\n3)Scissor" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 3);
    
    return (enChoices)choice;
}

enChoices GetComputerChoice()
{
    short choice=rand()%3+1;
    return (enChoices)choice;
}

enWinnerplayer GetWinner(enChoices Userchoice,enChoices Computerchoice,stPlayerResult &PlayerResult)
{
    enWinnerplayer winnerPlayer;
    if(Userchoice==Computerchoice)
    {
        winnerPlayer=enWinnerplayer::Non;
        PlayerResult.DrawCount++;
    }else
    {
        if (Userchoice==enChoices::Paper&&Computerchoice==enChoices::Scissor)
        {
            winnerPlayer=enWinnerplayer::Computer;
            PlayerResult.LoseCount++;
        }
        if (Userchoice==enChoices::Stone&&Computerchoice==enChoices::Scissor)
        {
            winnerPlayer=enWinnerplayer::User;
            PlayerResult.WinCount++;
        }
        if (Userchoice==enChoices::Paper&&Computerchoice==enChoices::Stone)
        {
            winnerPlayer=enWinnerplayer::User;
            PlayerResult.WinCount++;
        }
        if (Userchoice==enChoices::Scissor&&Computerchoice==enChoices::Stone)
        {
            winnerPlayer=enWinnerplayer::Computer;
            PlayerResult.LoseCount++;
        }
        if (Userchoice==enChoices::Stone&&Computerchoice==enChoices::Paper)
        {
            winnerPlayer=enWinnerplayer::Computer;
            PlayerResult.LoseCount++;
        }
        if (Userchoice==enChoices::Scissor&&Computerchoice==enChoices::Paper)
        {
            winnerPlayer=enWinnerplayer::User;
            PlayerResult.WinCount++;
        }
        
    }
    return winnerPlayer;
}

string GetChoiceName(enChoices choice)
{
    string choiceName;

    if (choice==enChoices::Paper)
    {
        choiceName="Paper";

    }else if (choice==enChoices::Stone)
    {
        choiceName="Stone";

    }else if (choice==enChoices::Scissor)
    {
        choiceName="Scissor";
    }

    return choiceName;
}

string GetWinnerName(enWinnerplayer winnerPlayer)
{
    string winnerPlayerName;

    if (winnerPlayer==enWinnerplayer::Non)
    {
        winnerPlayerName="No Winner";

    }else if (winnerPlayer==enWinnerplayer::User)
    {
        winnerPlayerName="You";

    }else if (winnerPlayer==enWinnerplayer::Computer)
    {
        winnerPlayerName="Computer";
    }

    return winnerPlayerName;
}
void DoStatusAction(enWinnerplayer winnerPlayer)
{
    if (winnerPlayer==enWinnerplayer::User)
    {
        system("color 2F");
    }else if(winnerPlayer==enWinnerplayer::Computer)
    {
        cout << "\a";
        system("color 4F");
    }else
    {
        system("color 6F");
    }
    
}
void PrintRoundResult(enChoices Userchoice,enChoices Computerchoice,enWinnerplayer winnerPlayer)
{
    DoStatusAction(winnerPlayer);
    cout << "Computer choice : " << GetChoiceName(Computerchoice) << endl;
    cout << "Your choice : " << GetChoiceName(Userchoice) << endl;
    cout << "Winner : " << GetWinnerName(winnerPlayer) << endl;

}

void PrintGameResult(stPlayerResult PlayerResult)
{
    DoStatusAction(PlayerResult.Winner());
    cout << "==========================================\n";
    cout << "==========================================\n";
    cout << "Won times : " << PlayerResult.WinCount << endl;
    cout << "Draw times: " << PlayerResult.DrawCount << endl;
    cout << "Lose times: " << PlayerResult.LoseCount << endl;
    cout << "Winner is: " << GetWinnerName(PlayerResult.Winner()) << endl;
    cout << "==========================================\n";
    cout << "==========================================\n";

}
void PlayGame(int roundCount)
{
    stPlayerResult playerResult;
    for (unsigned i = 1; i <= roundCount ; i++)
    {
        cout << "\t\t ============ | Round ( " << i << " ) | ============" << endl;
        enChoices userchoice=GetUserChoice();
        enChoices computerchoice=GetComputerChoice();
        enWinnerplayer winnerPlayer=GetWinner(userchoice,computerchoice,playerResult);
        PrintRoundResult(userchoice,computerchoice,winnerPlayer);
    }
    PrintGameResult(playerResult);
}

int main()
{
    int key;
    srand((unsigned) time(NULL));
    unsigned roundCound=ReadPositiveNumber("Enter count of rounds ?");
    PlayGame(roundCound);
    cin >> key;
    return 0;
}