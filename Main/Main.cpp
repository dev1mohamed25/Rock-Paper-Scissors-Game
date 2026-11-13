
#include <iostream>
#include <cstdlib> 
using namespace std;
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };
struct strRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRound = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomeNumber(int from, int To)
{
    int Randomenumber = rand() % (To - from + 1) + from;
    return Randomenumber;
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player","Computer","No Winner" };
    return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(strRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoice[3] = { "Stone","Paper","Scissors" };
    return arrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner) {
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }
}

void PrintRoundResult(strRoundInfo RoundInfo)
{
    cout << "\n------------------Round [" << RoundInfo.RoundNumber << "]--------------\n\n";
    cout << "Player Choice :" << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice :" << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner :" << RoundInfo.WinnerName << "\n";

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (ComputerWinTimes > PlayerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults  FileGameResult(int GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.GameRound = GameRounds;
    GameResults.PlayerWinTimes = PlayerWinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

enGameChoice ReadPlayerChoice()
{
    short Choice = 1;
    do
    {
        cout << "\n\n Your choice : [1]:Stoner,[2]:paper,[3]:Scissors ?";
        cin >> Choice;

    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomeNumber(1, 3);
}

stGameResults PlayGame(short HowManyRounds)
{
    strRoundInfo RoundInfo;
    short PlayerWinTimes = 0, coputerWinTimes = 0, DrawTimes = 0;
    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound[" << GameRound << "] begins :\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);


        if (RoundInfo.Winner == enWinner::Player)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            coputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
    }
    return FileGameResult(HowManyRounds, PlayerWinTimes, coputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;

    }
    return t;
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "---------------------------------------------------\n\n";
    cout << Tabs(2) << "              +++ G a m e O v e r +++\n\n";
    cout << Tabs(2) << "----------------------------------------------------\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "-------------------[Game Results]--------------------\n\n";
    cout << Tabs(2) << "Game Rounds          :" << GameResults.GameRound << endl;
    cout << Tabs(2) << "Player Won Times     :" << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer Won Times   :" << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw Times           :" << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Fainal Winner        :" << GameResults.WinnerName << endl;
    cout << Tabs(2) << "---------------------------------------------------------------\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRounds()
{
    short GameRounds = 1;
    do
    {
        cout << "How many round 1 to 10 :\n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);
    return GameRounds;
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}
void StartGame()
{
    char PlayeAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);
        cout << endl << Tabs(3) << "Do you Want to play again? Y/N? ";
        cin >> PlayeAgain;
    } while (PlayeAgain == 'Y' || PlayeAgain == 'y');

}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
