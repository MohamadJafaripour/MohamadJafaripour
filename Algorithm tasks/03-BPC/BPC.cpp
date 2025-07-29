#include <iostream>
#include <string>

const int MAX_SIZE = 1000;

bool isMatching(char open, char close);
bool isBalanced(const std::string &expr);

int main()
{
    std::string input;
    std::cout << "Enter expression: ";
    std::cin >> input;

    if (isBalanced(input))
    {
        std::cout << "Balanced\n";
    }
    else
    {
        std::cout << "Not balanced\n";
    }

    return 0;
}

bool isMatching(char open, char close)
{
    return (open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}');
}

bool isBalanced(const std::string &expr)
{
    char stack[MAX_SIZE];
    int top = -1;

    for (char ch : expr)
    {
        if (ch == '(' || ch == '[' || ch == '{') // if openning char
        {
            if (top >= MAX_SIZE - 1)
                return false; // overflow
            stack[++top] = ch; // put it on top
        }
        else if (ch == ')' || ch == ']' || ch == '}') // if ending char
        {
            if (top < 0)
                return false; // no opnener
            if (!isMatching(stack[top--], ch))
                return false; // no matching opener
        }
    }

    return (top == -1); // all brackets matched
}