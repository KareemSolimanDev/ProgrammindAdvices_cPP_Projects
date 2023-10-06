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
    enOpratorType OpratorType;
    char OpratorSymbol;
    enLevel level;
    short CorrectAnswer = 0;
    short UserAnswer = 0;
    char GetOpratorSymbol()
    {
        char symbols[4]={'+','-','*','/'};
        return symbols[int(OpratorType)-1];
    }

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
        {
            system("color 2F");
            return "Passed";
        }
        else
        {
            system("color 4F");
            return "Failed"; 
        }
    }

    string OpratorName()
    {
        string Names[5]={"Plus","Minus","Multiply","Divide","Mix"};
        return Names[(int)level-1];
    }
    string LevelName()
    {
        string Names[4]={"Easy","Mid","Hard","Mixed"};
        return Names[(int)level-1];
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


void CheckOpratorType(stGameResult& GameResult)
{

    if (GameResult.OpratorType==enOpratorType::Mix)
    {
        GameResult.QuestionInfo.OpratorType=(enOpratorType)RandomNumber(1,4);
    }else{
        GameResult.QuestionInfo.OpratorType=GameResult.OpratorType;
    }
}


void CheckLevel(stGameResult& GameResult)
{

    if (GameResult.level==enLevel::Mixed)
    {
        GameResult.QuestionInfo.level=(enLevel)RandomNumber(1,3);
    }else{
        GameResult.QuestionInfo.level=GameResult.level;
    }

}


void PrintQuestionResult(stGameResult& GameResult)
{
    if (GameResult.QuestionInfo.CorrectAnswer == GameResult.QuestionInfo.UserAnswer)
    {
        cout << "Correct answer\n__________" << endl;
        system("color 2F");
        GameResult.CorrectAnswersTimes+=1;
    }
    else
    {
        cout << "Wrong Answer" << endl;
        system("color 4F");

        GameResult.WrongAnswersTimes+=1;
        
        cout << "Correct answer =" << GameResult.QuestionInfo.CorrectAnswer << endl;
    }
}


void PrintFinalResult(stGameResult GameResult)
{
    cout << "\t\t#########################################\n\n";
    cout << "\t\t#########################################\n\n";
    cout << "\t\t==============|++GAME OVER++|============\n\n";
    cout << "\t\t=========================================\n";
    cout << "\t\t\tQuestions count : " << GameResult.QuestionsCount << endl;
    cout << "\t\t\tQuestions Type : " << GameResult.OpratorName() << endl;
    cout << "\t\t\tQuestions Level : " << GameResult.LevelName() << endl;
    cout << "\t\t\tCorrect times: " << GameResult.CorrectAnswersTimes << endl;
    cout << "\t\t\tWrong times : " << GameResult.WrongAnswersTimes << endl;
    cout << "\t\t\tFinal Status: " << GameResult.status() << endl;
    cout << "\t\t=========================================\n";
    cout << "\t\t#########################################\n";
}

void GetQuestionAnswer(stGameResult& GameResult)
{
    int answer;
    int FNum=GameResult.QuestionInfo.FirstNum;
    int LNum=GameResult.QuestionInfo.LastNum;
    
    switch (GameResult.QuestionInfo.OpratorType)
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

void PresentQuestion(stGameResult& GameResult)
{

    cout << "Question [" << GameResult.QuestionInfo.QuestionNumber << "/" << GameResult.QuestionsCount <<"]" << endl;
    cout << GameResult.QuestionInfo.FirstNum << endl;
    cout << GameResult.QuestionInfo.GetOpratorSymbol() << endl;
    cout << GameResult.QuestionInfo.LastNum;
    cout << "\n____" << endl;
}

void GenerateQuestion(stGameResult& GameResult)
{
    CheckLevel(GameResult);
    CheckOpratorType(GameResult);
    int NumsLevel = pow(10, (int)GameResult.QuestionInfo.level);
    GameResult.QuestionInfo.FirstNum= RandomNumber(1, NumsLevel);
    GameResult.QuestionInfo.LastNum= RandomNumber(1, NumsLevel);

    PresentQuestion(GameResult);
    GetQuestionAnswer(GameResult);
    

}

void PlayRound(stGameResult& GameResult)
{
    for (unsigned i = 1; i <= GameResult.QuestionsCount; i++)
    {
        GameResult.QuestionInfo.QuestionNumber=i;
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