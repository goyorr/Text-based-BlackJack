#include <thread>
#include<unistd.h> 
#include <iostream>
#include <random>
#include <vector>

char hearts[] = "\xE2\x99\xA5";
char diamonds[] = "\xE2\x99\xA6";
char clubs[] = "\xE2\x99\xA3";
char spades[] = "\xE2\x99\xA0";
char jack[] = "\xE2\x99\xA9";
char queen[] = "\xE2\x99\xA8";
char king[] = "\xE2\x99\xA7";

std::string generateRandomSymbol() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::vector<std::string> cards;

    cards.push_back("♥");
    cards.push_back("♦");
    cards.push_back("♣");
    cards.push_back("♠");

    static std::uniform_int_distribution<int> distribution(0, cards.size() - 1);
    int random_index = distribution(gen);

    return cards[random_index];
}

std::string generateRandomCard() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::vector<std::string> cards;

    cards.push_back("2");
    cards.push_back("3");
    cards.push_back("4");
    cards.push_back("5");
    cards.push_back("6");
    cards.push_back("7");
    cards.push_back("8");
    cards.push_back("9");
    cards.push_back("10");
    cards.push_back("A");
    cards.push_back("K");
    cards.push_back("Q");
    cards.push_back("J");

    static std::uniform_int_distribution<int> distribution(0, cards.size() - 1);
    int random_index = distribution(gen);

    return cards[random_index];
}

std::string generateRandomCar() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::vector<std::string> cards;

    cards.push_back("2");
    cards.push_back("3");
    cards.push_back("4");
    cards.push_back("5");
    cards.push_back("6");
    cards.push_back("7");
    cards.push_back("8");
    cards.push_back("9");
    cards.push_back("10");
    cards.push_back("K");
    cards.push_back("Q");
    cards.push_back("J");

    static std::uniform_int_distribution<int> distribution(0, cards.size() - 1);
    int random_index = distribution(gen);

    return cards[random_index];
}

void    BlackJack()
{
    static int chips = 2500;
    static int bet = 50;
    std::string ch;

    if (!chips) {
        std::cout << "\x1b[31mYou have no chips left.\x1b[0m\n\n";
        exit (0);
    }
    if (chips < bet) {
        std::cout << "\x1b[31mYou don't have enough chips to play with.\nTry adding chips or chnage your bet:\x1b[0m ";
        std::cin >> ch;

        if (!ch.compare("bet")) {
            std::cout << "\nHow much would you like to bet: ";
            std::cin >> bet;
            if (bet > chips)
                std::cout << "\nYou don't have enough chips to bet that much.\n";
            std::cout << "\n";
            return;
        }
        else if (!ch.compare("add")) {
            int num;
            std::cout << "\nHow much would you like to add: ";
            std::cin >> num;
            std::cout << "\n";
            chips += num;
            return ;
        }
        else 
            return ;
    }
    bool ACE = false;
    int num = 0;
    std::string choice;
    int Plcount = 0;
    int rand = 0;
    int Dlcount = 0;
    std::string Dsym;
    std::chrono::milliseconds sleepDuration(70);

    for (char letter : "\x1b[1;32m\x1b[DDealing cards....\x1b[0m\x1b[0m") {
        std::this_thread::sleep_for(sleepDuration);
        std::cout << letter << std::flush;
    }

    std::cout << "\n\nbet: $" << bet << " chips left: " << chips - bet << "\n\x1b[34mYour cards    : \x1b[0m";
    chips -= bet;
    std::string randstring = generateRandomCard();
    if (std::isdigit(randstring[0]))
        Plcount += std::stoi(randstring);
    else if (randstring[0] == 'A') {
        Plcount += 11;
        ACE = true;
    }
    else
        Plcount += 10;
    std::cout << randstring << generateRandomSymbol() << " ";

    randstring = generateRandomCard();
    if (std::isdigit(randstring[0]))
        Plcount += std::stoi(randstring);
    else if (randstring[0] == 'A') {
        if (ACE) {
            Plcount -= 10;
            Plcount += 1;
            ACE = false;
        }
        else {
            Plcount += 11;
            ACE = true;
        }
    }
    else
        Plcount += 10;
    std::cout << randstring << generateRandomSymbol() << "\n";
    if (Plcount == 21) {
        std::cout << "\n\x1b[32m\x1b[1;34mBlackJack!\x1b[0m\x1b[0m\n\n";
        chips += bet * 2.5;
        return;
    }

    std::cout << "\x1b[33mDealer's cards: \x1b[0m";
    std::string Drandstring = generateRandomCar();
    if (std::isdigit(Drandstring[0]))
        Dlcount += std::stoi(Drandstring);
    else
        Dlcount += 10;
    Dsym = generateRandomSymbol();
    std::cout << Drandstring << Dsym << " X?\n";

    while (1) {
        std::cout << "\nHit or Stand: ";
        std::cin >> choice;

        if (std::cin.eof()) {
            std::cout << "\nExiting the game.\n";
            exit(0);
        }
        if (!choice.compare("hit") || !choice.compare("h")) {
            std::string randstring = generateRandomCard();
            if (std::isdigit(randstring[0])) {
                Plcount += std::stoi(randstring);
                if (ACE && Plcount > 21) {
                    Plcount -= 10;
                    ACE = false;
                }
            }
            else if (randstring[0] == 'A') {
                Plcount += 11;
                if (Plcount > 21)
                    Plcount -= 10;
                else
                    ACE = true;
            }
            else {
                Plcount += 10;
                if (ACE) {
                    Plcount -= 10;
                    ACE = false;
                }
            }
            std::cout << "\x1b[34m" << randstring << generateRandomSymbol() << " you have: \x1b[0m" << Plcount  << "\n";
            if (Plcount == 21) {
                std::cout << "\n\x1b[32mYou win!\x1b[0m\n\n";
                chips += bet * 2;
                return;
            }
            else if (Plcount > 21) {
                int random_num = std::rand() % 3;

                if (random_num == 0)
                    std::cout << "\n\x1b[31mbust!\x1b[0m\n\n";
                else if (random_num == 1)
                    std::cout << "\n\x1b[31mand a bust!\x1b[0m\n\n";
                else
                    std::cout << "\n\x1b[31mtoo many!\x1b[0m\n\n";
                return;
            }
        }
        else if (!choice.compare("stand") || !choice.compare("s")) {
            std::cout << "\n\x1b[33mDealer's cards: \x1b[0m" << Drandstring << Dsym << " " << std::flush;
            Drandstring = generateRandomCar();
            if (std::isdigit(Drandstring[0]))
                Dlcount += std::stoi(Drandstring);
            else if (randstring[0] == 'A') {
                Dlcount += 10;
                if (Dlcount > 21)
                    Dlcount -= 9;
            }
            else
                Dlcount += 10;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << Drandstring << generateRandomSymbol() << " " << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            while (Dlcount < 17) {
                Drandstring = generateRandomCar();
                if (std::isdigit(Drandstring[0]))
                    Dlcount += std::stoi(Drandstring);
                else if (Drandstring[0] == 'A') {
                    Dlcount += 10;
                    if (Dlcount > 21)
                        Dlcount -= 9;
                }
                else
                    Dlcount += 10;
                std::cout << Drandstring << generateRandomSymbol() << " " << std::flush;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            std::cout << "\nDealer has: " << Dlcount;
            if (Dlcount > 21) {
                std::cout << "\n\x1b[32mYou win!\x1b[0m\n\n";
                chips += bet * 2;
                return;
            }
            else if (Dlcount > Plcount) {
                std::cout << "\n\x1b[31mYou lost!\x1b[0m\n\n";
                return;
            }
            else if (Dlcount == Plcount) {
                std::cout << "\n\x1b[33mPush!\x1b[0m\n\n";
                chips += bet;
                return;
            }
            else {
                std::cout << "\n\x1b[32mYou win!\x1b[0m\n\n";
                chips += bet * 2;
                return;
            }
        }
        else if (!choice.compare("count"))
            std::cout << "\x1b[34mYou have: \x1b[0m" << Plcount;
        else if (!choice.compare("quit"))
            exit (0);
        else if (!choice.compare("help"))
            std::cout << "\nCommands:\nType \"hit\" to get another card.\nType \"stand\" to keep your current hand.\nType \"add\" to increse chips amount.\nType \"bet\" to chnage amount to play with.\nType \"count\" to see your card count.\nType \"help\" for commands.\nType \"clear\" to clean the window.\nType \"quit\" to exit the game." << std::endl;
        else if (!choice.compare("clear"))
            system("clear");
        else if (!choice.compare("bet")) {
            std::cout << "\nHow much would you like to bet: ";
            int tmp_bet = bet;
            chips += bet;
            std::cin >> bet;
            if (bet > chips) {
                std::cout << "\nYou don't have enough chips to bet that much.\n";
                bet = tmp_bet;
            }
            std::cout << "\n";
            return;
        }
        else if (!choice.compare("add")) {
            std::cout << "\nHow much would you like to add: ";
            std::cin >> num;
            std::cout << "\n";
            chips += num;
            chips += bet;
            return ;
        }
        else
            continue;
    }
}

int main() {
    system("clear");

    std::cout << "\x1b[1;32m\x1b[1mWelcome to Text-Based Blackjack!\n\n";
    std::cout << "Try your luck and test your skills in this classic card game. Get as close to 21 as possible without going over, and beat the dealer to win!\n\n";
    std::cout << "Commands:\n";
    std::cout << "Type \"hit\" to get another card.\n";
    std::cout << "Type \"stand\" to keep your current hand.\n";
    std::cout << "Type \"add\" to change chips amount.\n";
    std::cout << "Type \"bet\" to chnage amount to play with.\n";
    std::cout << "Type \"count\" to see your card count.\n";
    std::cout << "Type \"help\" for commands.\n";
    std::cout << "Type \"clear\" to clean the window.\n";
    std::cout << "Type \"quit\" to exit the game.\n\n";
    std::cout << "Good luck.\x1b[0m\x1b[0m\n" << std::endl;

    while (1)
        BlackJack();
}
