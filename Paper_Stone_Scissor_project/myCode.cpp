#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

enum enWinnerplayer{Non=0,User=1,Computer=2};
enum enChoices{Paper=1,Stone=2,Scissor=3};


struct stRoundInfo
{
    short roundNumber;
    enChoices userChoice;
    enChoices computerChoice;


    enWinnerplayer Winner()
    {

    enWinnerplayer winnerPlayer;

    if(userChoice==computerChoice)
        winnerPlayer=enWinnerplayer::Non;
    else
    {
        if ((userChoice==enChoices::Paper&&computerChoice==enChoices::Stone)   ||
            (userChoice==enChoices::Stone&&computerChoice==enChoices::Scissor) ||
            (userChoice==enChoices::Scissor&&computerChoice==enChoices::Paper))
        {
            winnerPlayer=enWinnerplayer::User;
        }else
            winnerPlayer=enWinnerplayer::Computer;

    }

    return winnerPlayer;
    }

};

struct stGameResult
{
    short RoundsCount=0;
    short WinCount=0;
    short DrawCount=0;
    short LoseCount=0;

    enWinnerplayer Winner()
    {
        if (WinCount>LoseCount)
            return enWinnerplayer::User;

        else if (WinCount<LoseCount)
            return enWinnerplayer::Computer;

        else{
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

bool IsContinueGame(string msg)
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

void ResetScreen()
{
    system("color 0F");
    system("cls");
}

void DoWonAction(enWinnerplayer winnerPlayer)
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

void PrintRoundResult(stRoundInfo roundInfo)
{
    DoWonAction(roundInfo.Winner());
    cout << "\n\t\t============ | Round ( " << roundInfo.roundNumber << " ) | ============" << endl;
    cout << "\n\t\t=========================================\n";
    cout << "\t\t=========================================\n";
    cout << "\t\t\tYour choice : " << GetChoiceName(roundInfo.userChoice) << endl;
    cout << "\t\t\tComputer choice : " << GetChoiceName(roundInfo.computerChoice) << endl;
    cout << "\t\t\tWinner : " << GetWinnerName(roundInfo.Winner()) << endl;
    cout << "\t\t=========================================\n";
    cout << "\t\t=========================================\n\n";


}

void PrintGameResult(stGameResult GameResult)
{
    DoWonAction(GameResult.Winner());
    cout << "\t\t#########################################\n\n";
    cout << "\t\t#########################################\n\n";
    cout << "\t\t==============|++GAME OVER++|============\n\n";
    cout << "\t\t=========================================\n";
    cout << "\t\t\tRounds count : " << GameResult.RoundsCount << endl;
    cout << "\t\t\tWon times : " << GameResult.WinCount << endl;
    cout << "\t\t\tDraw times: " << GameResult.DrawCount << endl;
    cout << "\t\t\tLose times: " << GameResult.LoseCount << endl;
    cout << "\t\t\tWinner is: " << GetWinnerName(GameResult.Winner()) << endl;
    cout << "\t\t=========================================\n";
    cout << "\t\t#########################################\n";

}


void UpdateWinnerData(enWinnerplayer winner,stGameResult &GameResult)
{
    switch (winner)
    {
    case enWinnerplayer::Non:
        GameResult.DrawCount++;
        break;
    
    case enWinnerplayer::User:
        GameResult.WinCount++;
        break;
    
    case enWinnerplayer::Computer:
        GameResult.LoseCount++;
        break;
    }
}

void PlayRound(short roundsCount,stGameResult &GameResult)
{
    stRoundInfo RoundInfo;
    for (unsigned i = 1; i <= roundsCount ; i++)
    {
        RoundInfo.roundNumber=i;
        RoundInfo.userChoice=GetUserChoice();
        RoundInfo.computerChoice=GetComputerChoice();
        UpdateWinnerData(RoundInfo.Winner(),GameResult);
        PrintRoundResult(RoundInfo);
    }
}

void PlayGame()
{
    do
    {
        ResetScreen();

        short roundsCount=ReadPositiveNumberInRange(1,100,"Enter count of rounds from 1 to 100 ?");

        stGameResult GameResult;

        GameResult.RoundsCount=roundsCount;


        PlayRound(roundsCount,GameResult);
        PrintGameResult(GameResult);

    } while (IsContinueGame("Do you want to play another game Y/N >> "));
    
}

int main()
{
    srand((unsigned) time(NULL));

    PlayGame();

    return 0;
}