#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

class NumberGuessingGame
{
	private:
	int hiddenNum;
	int attempts;
	int maxAttempts;
	std::string playerName;
	public:
	int generateNum(int min, int max)
	{
		return (std::rand() % (max - min + 1) + min);
	}

	NumberGuessingGame(std::string name, int min, int max) : playerName(name), attempts(0)
	{
		std::srand(std::time(0));
		hiddenNum = generateNum(min, max);
		maxAttempts = static_cast<int>((max - min) * 1.5);
	}
	NumberGuessingGame(std::string name, int maxAttempts) : playerName(name), attempts(0), maxAttempts(maxAttempts)
	{
		std::srand(std::time(0));
		hiddenNum = generateNum(1, 100);
	}

	void play()
	{
		std::cout << "Welcome, " << playerName << ", to the Number Guessing Game\n";
		std::cout << "You have " << maxAttempts << " attempts to guess the number\n";
		int guess;
		do
		{
			std::string userInput;
			std::cout << "Enter your guess (or 'stop' to end the game): ";
			std::cin >> userInput;

			if (userInput == "stop")
			{
				std::cout << "Game stopped by the player.\n";
				return;
			}
			try
			{
				guess = std::stoi(userInput);
			}
			catch (const std::invalid_argument&)
			{
				std::cerr << "Invalid input. Please enter a valid number or 'stop'.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			attempts++;
			if (guess == hiddenNum)
				std::cout << "Congratulations, " << playerName << "! You guessed the correct number in " << attempts << " attempts.\n";
			else if (guess < hiddenNum)
				std::cout << "Too low! Try again.\n";
			else
				std::cout << "Too high! Try again.\n";
		}
		while (attempts < maxAttempts && guess != hiddenNum);
		if (attempts >= maxAttempts)
		{
			std::cout << "Sorry, " << playerName << ", you've reached the maximum number of attempts. The correct number was: " << hiddenNum << "\n";
		}
	}
};
int main()
{
	std::string playerName;
	int min, max;
	int chose = 0;

	std::cout << "Welcome to the Number Guessing game!\n";
	std::cout << "The rules are simple! Just guess the number!\n";

	std::cout << "Enter your name: ";
	std::getline(std::cin, playerName);

	std::cout << "The game generates a random number between 1 and 100. Do you want to change the range?\n Yes - 1, No - 0, Stop game - stop \n ";
	std::string userInput;
	std::getline(std::cin, userInput);

	while (userInput != "1" && userInput != "0" && userInput != "stop")
	{
		std::cerr << "Enter 1 or 0 ('stop' to end the game): ";
		std::cin >> userInput;
		if (userInput == "stop")
		{
			std::cout << "Game stopped by the player.\n";
			return 0;
        }
		try
		{
			chose = std::stoi(userInput);
		}
		catch (const std::invalid_argument&)
		{
			std::cout << "Invalid input. Please enter a valid number or 'stop'.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	}
	if (userInput == "1")
	{
		std::cout << "Enter the minimum value for the range: ";
		std::cin >> min;

		std::cout << "Enter the maximum value for the range: ";
		std::cin >> max;

		while (min >= max)
		{
			std::cerr << "Invalid range. Minimum value is greater than maximum value.\n";
			std::cout << "Enter the minimum value for the range: ";
			std::cin >> min;
			std::cout << "Enter the maximum value for the range: ";
			std::cin >> max;
		}
		NumberGuessingGame game(playerName, min, max);
		game.play();
	}
	else if (userInput == "0")
	{
		int maxAttempts;
		std::cout << "Enter the maximum number of attempts: ";
		std::cin >> maxAttempts;

		NumberGuessingGame game(playerName, maxAttempts);
		game.play();
	}
	return (0);
}
