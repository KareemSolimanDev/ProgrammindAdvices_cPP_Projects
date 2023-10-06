#include <cstdlib>
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

enum enOpratorType
{
    Plus = 1,
    Minus,
    Multiply,
    Devide,
    Mix
};
enum enLevel
{
    Easy = 1,
    Mid,
    Hard,
    Mixed
};

struct stQuestionInfo
{
    short QuestionNumber;
    short FirstNum = 0;
    short LastNum = 0;
    char Oprator;
    enLevel Level;
    short CorrectAnswer = 0;
    short UserAnswer = 0;
};

struct stGameResult
{
    short QuestionsCount = 0;
    stQuestionInfo QuestionInfo; 
    enOpratorType OpratorType;
    enLevel level;
    short CorrectAnswersTimes = 0;
    short WrongAnswersTimes = 0;

    string status()
    {
        if (CorrectAnswersTimes >= WrongAnswersTimes)
            return "Passed";
        else
            return "Failed";
    }
};

int ReadPositiveNumberInRange(int start, int end, string msg)
{
    int num = 0;
    do
    {
        cout << msg;
        cin >> num;
    } while (num < start || num > end);
    return num;
}

int ReadNumber(string msg)
{
    int num = 0;
    cout << msg;
    cin >> num;
    return num;
}

int RandomNumber(int start, int end)
{
    return rand() % (end - start + 1) + start;
}

bool IsContinueGame(string msg)
{
    char answer;
    cout << msg;
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        return true;
    }
    else
        return false;
}

void ResetScreen()
{
    system("color 0F");
    system("cls");
}


enOpratorType CheckOpratorType(enOpratorType OpratorType)
{

    if (OpratorType==enOpratorType::Mix)
    {
        OpratorType=(enOpratorType)RandomNumber(1,4);
    }
    return OpratorType;
}


enLevel CheckLevelType(enLevel Level)
{

    if (Level==enLevel::Mixed)
    {
        Level=(enLevel)RandomNumber(1,3);
    }
    return Level;
}




void PrintQuestionResult(stGameResult& GameResult)
{
    if (GameResult.QuestionInfo.CorrectAnswer == GameResult.QuestionInfo.UserAnswer)
    {
        cout << "passed" << endl;
        GameResult.CorrectAnswersTimes+=1;
    }
    else
    {
        cout << "failed" << endl;
        GameResult.WrongAnswersTimes+=1;
        
        cout << "Correct answer =" << GameResult.QuestionInfo.CorrectAnswer << endl;
    }
}


void PrintFinalResult(stGameResult GameResult)
{
    if (GameResult.CorrectAnswersTimes >= GameResult.WrongAnswersTimes)
    {
        cout << "your finally passed" << endl;
    }
    else
        cout << "your finally failed" << endl;
}

void GetQuestionAnswer(stGameResult& GameResult)
{
    int answer;
    int FNum=GameResult.QuestionInfo.FirstNum;
    int LNum=GameResult.QuestionInfo.LastNum;

    switch (GameResult.OpratorType)
    {
    case enOpratorType::Plus:
        answer = FNum + LNum;
        break;

    case enOpratorType::Minus:
        answer = FNum - LNum;
        break;

    case enOpratorType::Multiply:
        answer = FNum * LNum;
        break;

    case enOpratorType::Devide:
        answer = FNum / LNum;
        break;

    default:
        break;
    }
    GameResult.QuestionInfo.CorrectAnswer=answer;
}
void GetOpratorSymbol(stGameResult& GameResult)
{
    char symbols[4]={'+','-','*','/'};
    GameResult.QuestionInfo.Oprator=symbols[int(GameResult.OpratorType)-1];
}
void PresentQuestion(stGameResult GameResult)
{
    GetOpratorSymbol(GameResult);
    cout << GameResult.QuestionInfo.FirstNum << endl;
    cout << GameResult.QuestionInfo.Oprator << endl;
    cout << GameResult.QuestionInfo.LastNum;
    cout << "\n____" << endl;
}
void GenerateQuestion(stGameResult GameResult)
{

    int NumsLevel = pow(10, (int)CheckLevelType(GameResult.level));
    GameResult.QuestionInfo.FirstNum= RandomNumber(1, NumsLevel);
    GameResult.QuestionInfo.LastNum= RandomNumber(1, NumsLevel);

    PresentQuestion(GameResult);
    GetQuestionAnswer(GameResult);
    

}

void PlayRound(stGameResult& GameResult)
{
    for (unsigned i = 1; i <= GameResult.QuestionsCount; i++)
    {
        GenerateQuestion(GameResult);
        GameResult.QuestionInfo.UserAnswer = ReadNumber("Enter Result >>");
        PrintQuestionResult(GameResult);
    }
}

void GetDataFromUser(stGameResult& GameResult)
{

    

    GameResult.QuestionsCount = ReadPositiveNumberInRange(1, 100, "Enter count of questions from 1 to 100 ?");

    GameResult.OpratorType = (enOpratorType)ReadPositiveNumberInRange(1, 5, "Enter question oprator 1)plus(+) , 2)minus(-) , 3)multiply(*) , 4)divide(/) , 5)Mixed\n>>>");

    GameResult.level = (enLevel)ReadPositiveNumberInRange(1, 4, "Enter your level 1)easy , 2)midium , 3)hard , 4)Mixed\n>>>");

    

}

void StartGame()
{
    do
    {

        stGameResult GameResult;
        ResetScreen();

        GetDataFromUser(GameResult);

        PlayRound(GameResult);

        PrintFinalResult(GameResult);

    } while (IsContinueGame("Do you want to play another game Y/N >> "));
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}


// void DoWonAction(enWinnerplayer winnerPlayer)
// {
//     switch (winnerPlayer)
//     {
//         case enWinnerplayer::User:
//             system("color 2F");
//             break;
//         case enWinnerplayer::Computer:
//             cout << "\a";
//             system("color 4F");
//             break;
//         default:
//             system("color 6F");
//             break;
//     }

// }


// void PrintGameResult(stGameResult GameResult)
// {
//     DoWonAction(GameResult.Winner());
//     cout << "\t\t#########################################\n\n";
//     cout << "\t\t#########################################\n\n";
//     cout << "\t\t==============|++GAME OVER++|============\n\n";
//     cout << "\t\t=========================================\n";
//     cout << "\t\t\tRounds count : " << GameResult.RoundsCount << endl;
//     cout << "\t\t\tWon times : " << GameResult.WinCount << endl;
//     cout << "\t\t\tDraw times: " << GameResult.DrawCount << endl;
//     cout << "\t\t\tLose times: " << GameResult.LoseCount << endl;
//     cout << "\t\t\tWinner is: " << GetWinnerName(GameResult.Winner()) << endl;
//     cout << "\t\t=========================================\n";
//     cout << "\t\t#########################################\n";

// }


