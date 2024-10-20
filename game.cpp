#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

class Player
{
public:
    Player(): name(""), num_guesses(0){}
    Player(std::string nm, int ng): name(nm), num_guesses(ng){}
    void setName(std::string nm) {
        name = nm;
    }
    void setNumGuesses(int ng) {
        num_guesses = ng;
    }
    std::string getName() {
        return name;
    }
    int getNumGuesses() {
        return num_guesses;
    }

private:
    std::string name;
    int num_guesses;
};

class LeaderBoard
{
public:
    LeaderBoard(){
        for (int i = 0; i < NUM_LEADERS; ++i) {
            leaders[i] = Player("Empty", 9999); // Placeholder values for leaderboard
        }
    };
    void insertPlayer(Player player) {
        int playerScore = player.getNumGuesses();
        if(playerScore < leaders[4].getNumGuesses()) {
            leaders[4] = player;
            for(int i = NUM_LEADERS - 1; i > 0; i--) {
                if(leaders[i].getNumGuesses() < leaders[i - 1].getNumGuesses()) {
                    Player temp = leaders[i];
                    leaders[i] = leaders[i - 1];
                    leaders[i - 1] = temp;
                }
            }
        }
    }
    void displayLeaderBoard() {
        for(int i = 0; i < NUM_LEADERS; i++) {
            std::cout << leaders[i].getName() << " " << leaders[i].getNumGuesses() << std::endl;
        }
    }
    void readLeaders(std::string fileName) {
        std::fstream MyReadFile(fileName);
        std::string myText;
        int i = 0;
        while (getline (MyReadFile, myText)) {
            // Output the text from the file
            int index = myText.find(' ');
            leaders[i].setName(myText.substr(0, index));
            leaders[i].setNumGuesses(stoi(myText.substr(index,myText.length() - 1)));
            i++;
        }
        MyReadFile.close();
    }

    void writeLeaders(std::string fileName) {
        std::ofstream MyFile(fileName);

        for(int i = 0; i < NUM_LEADERS; i++) {
            MyFile << leaders[i].getName() << " " << leaders[i].getNumGuesses() << std::endl;
        }

        MyFile.close();
    }


private:
    static const int NUM_LEADERS = 5;
    Player leaders[NUM_LEADERS];
};

int main()
{
    LeaderBoard leaderboard;
    leaderboard.readLeaders("/Users/justinlee/Documents/file2.txt");
    std::srand(std::time(0));
    std::cout << "Welcome! Press 'q' to quit or any other key to continue:\n";
    char c;
    bool game_over = false;
    while (!game_over) {
        std::cin >> c;
        if (c == 'q')
        {
            game_over = true;
            std::cout << "Bye Bye!\n";
            leaderboard.writeLeaders("/Users/justinlee/Documents/file2.txt");
            leaderboard.displayLeaderBoard();
        }
        else {
            int count = 0;
            Player current_player;
            std::string input;
            std::cout << "Enter name: ";
            std::cin >> input;
            current_player.setName(input);
            int randNum = std::rand() % 100;
            int squareNum = sqrt(randNum);
            std::cout << "What is the square root of " << randNum << " ?\n";
            int guess = 0;
            while(guess != squareNum) {
                std::cin >> guess;
                count++;
                if(guess < squareNum) {
                    std::cout << "Too low. Guess again\n";
                } else if(guess > squareNum) {
                    std::cout << "Too high. Guess again\n";
                } else {
                    std::cout << "Nice you guess it in " << count << " guesses.\n";
                }
            }
            current_player.setNumGuesses(count);
            leaderboard.insertPlayer(current_player);
            std::cout << "Press 'q' to quit or any other key to continue:\n";
        }
    }
    return 0;
}
