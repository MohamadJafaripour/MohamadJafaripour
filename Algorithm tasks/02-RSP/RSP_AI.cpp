#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

// Define enum first to avoid forward declaration errors
enum Move { ROCK,    PAPER,    SCISSORS,   INVALID };

std::string determineResult(Move, Move);
std::string moveToString(Move);
Move beat(Move);
Move getUserMove(const std::string &);
Move getComputerMove(Move, std::string);

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Move lastUserMove = INVALID;
    std::string lastResult = "none";
    std::string input;

    std::cout << "Welcome to Rock-Paper-Scissors (type 'exit' to quit)\n";

    while (true)
    {
        std::cout << "\nEnter your move: ";
        std::cin >> input;
        if (input == "exit")
            break;

        Move userMove = getUserMove(input);
        if (userMove == INVALID)
        {
            std::cout << "Invalid input. Try rock, paper, or scissors.\n";
            continue;
        }

        Move computerMove = getComputerMove(lastUserMove, lastResult);
        std::string result = determineResult(userMove, computerMove);

        std::cout << "Computer played: " << moveToString(computerMove) << '\n';
        if (result == "tie")
            std::cout << "It's a tie!" << '\n';
        else if (result == "loss")
            std::cout << "Computer wins!" << '\n';
        else
            std::cout << "You win!" << '\n';

        lastUserMove = userMove;
        lastResult = result;
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}

Move getUserMove(const std::string &input)
{
    if (input == "rock")
        return ROCK;
    if (input == "paper")
        return PAPER;
    if (input == "scissors")
        return SCISSORS;
    return INVALID;
}

std::string moveToString(Move m)
{
    switch (m)
    {
    case ROCK:
        return "rock";
    case PAPER:
        return "paper";
    case SCISSORS:
        return "scissors";
    default:
        return "invalid";
    }
}

Move beat(Move m)
{
    switch (m)
    {
    case ROCK:
        return PAPER;
    case PAPER:
        return SCISSORS;
    case SCISSORS:
        return ROCK;
    default:
        return INVALID;
    }
}

std::string determineResult(Move user, Move computer)
{
    if (user == computer)
        return "tie";
    if (beat(user) == computer)
        return "loss"; // computer wins
    return "win";      // user wins
}

Move getComputerMove(Move lastUserMove, std::string lastResult)
{
    if (lastUserMove == ROCK && lastResult == "loss")
    {
        return beat(SCISSORS); // predict user plays scissors → counter with ROCK
    }

    return static_cast<Move>(rand() % 3);
}