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

int ReadPositiveNumberInRange(int start,int end,string msg)
{
    int num=0;
    do
    {
        cout << msg;
        cin >> num;
    } while (num < start || num > end);
    return num;
}


int RandomNumber(int start, int end) {
    return rand() % (end - start + 1) + start;
}

enChoices GetUserChoice()
{
    short choice=ReadPositiveNumberInRange(1,3,"What is your Choice : 1)Paper 2)Stone 3)Scissor >> ");

    return (enChoices)choice;
}

enChoices GetComputerChoice()
{
    short choice=RandomNumber(1,3);
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
        if (Userchoice==enChoices::Stone&&Computerchoice==enChoices::Scissor)
        {
            winnerPlayer=enWinnerplayer::User;
            PlayerResult.WinCount++;

        }else if (Userchoice==enChoices::Paper&&Computerchoice==enChoices::Stone)
        {
            winnerPlayer=enWinnerplayer::User;
            PlayerResult.WinCount++;

        }else if (Userchoice==enChoices::Scissor&&Computerchoice==enChoices::Paper)
        {
            winnerPlayer=enWinnerplayer::User;
            PlayerResult.WinCount++;

        }else
        {
            winnerPlayer=enWinnerplayer::Computer;
            PlayerResult.LoseCount++;
        }
        
    }

    return winnerPlayer;
}

string GetChoiceName(enChoices choice)
{
    string choiceName[3]={"Paper","Stone","Scissor"};

    return choiceName[choice - 1];
}

string GetWinnerName(enWinnerplayer winnerPlayer)
{
    string winnerPlayerName[3]={"No Winner","You","Computer"};

    return winnerPlayerName[winnerPlayer];
}

void DoStatusAction(enWinnerplayer winnerPlayer)
{
    switch (winnerPlayer)
    {
        case enWinnerplayer::User:
            system("color 2F");
            break;
        case enWinnerplayer::Computer:
            cout << "\a";
            system("color 4F");
            break;
        default:
            system("color 6F");
            break;
    }
    
}

void PrintRoundResult(enChoices Userchoice,enChoices Computerchoice,enWinnerplayer winnerPlayer)
{
    DoStatusAction(winnerPlayer);
    cout << "\n\t\t=========================================\n";
    cout << "\t\t=========================================\n";
    cout << "\t\t\tComputer choice : " << GetChoiceName(Computerchoice) << endl;
    cout << "\t\t\tYour choice : " << GetChoiceName(Userchoice) << endl;
    cout << "\t\t\tWinner : " << GetWinnerName(winnerPlayer) << endl;
    cout << "\t\t=========================================\n";
    cout << "\t\t=========================================\n\n";


}

void PrintGameResult(stPlayerResult PlayerResult)
{
    DoStatusAction(PlayerResult.Winner());
    cout << "\t\t#########################################\n\n";
    cout << "\t\t#########################################\n\n";
    cout << "\t\t==============|++GAME OVER++|============\n\n";
    cout << "\t\t=========================================\n";
    cout << "\t\t\tWon times : " << PlayerResult.WinCount << endl;
    cout << "\t\t\tDraw times: " << PlayerResult.DrawCount << endl;
    cout << "\t\t\tLose times: " << PlayerResult.LoseCount << endl;
    cout << "\t\t\tWinner is: " << GetWinnerName(PlayerResult.Winner()) << endl;
    cout << "\t\t=========================================\n";
    cout << "\t\t#########################################\n";

}

bool YesOrNo(string msg)
{
    char answer;
    cout << msg;
    cin >> answer;
    if (answer=='Y' || answer=='y')
    {
        return true;
    }else
        return false;

}

void ResetScreen()
{
    system("color 0F");
    system("cls");
}

void PlayGame()
{
    bool another_game=false;

    do
    {
        ResetScreen();
        
        short roundCound=ReadPositiveNumberInRange(1,100,"Enter count of rounds from 1 to 100 ?");

        stPlayerResult playerResult;

        for (unsigned i = 1; i <= roundCound ; i++)
        {
            cout << "\t\t============ | Round ( " << i << " ) | ============" << endl;
            enChoices userchoice=GetUserChoice();
            enChoices computerchoice=GetComputerChoice();
            enWinnerplayer winnerPlayer=GetWinner(userchoice,computerchoice,playerResult);

            PrintRoundResult(userchoice,computerchoice,winnerPlayer);
        }

        PrintGameResult(playerResult);

        another_game=YesOrNo("Do you want to play another game Y/N >> ");

    } while (another_game);
    
}

int main()
{
    srand((unsigned) time(NULL));

    PlayGame();

    return 0;
}