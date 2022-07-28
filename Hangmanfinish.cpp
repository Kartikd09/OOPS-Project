#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class hangman
{
protected:
    // string array[10] = {"india", "ukraine", "france", "greenland", "iceland", "japan", "algeria", "albania", "malta", "uganda"};
    // static int N = 42;
    string array[42];

public:
    string chooseWord();

    // void filehandle();
    void displayDashes(char guessWord[], int length);
    void displayWord(string word, int length);
    int guesscheck(string selectword, char guessWord[], char letter);
    void displayMan(int remainingGuess);
};

// void hangman::filehandle()
// {
//     string words;
//     ifstream fin;
//     fin.open("WordFile.txt");
//     while (fin)
//     {
//         fin >> words;
//         getline(fin,words);
// cout << words;
//         for (int i = 0; i < 42; i++)
//         {
//             array[i] = words;
//         }

//     }

// }

string hangman ::chooseWord()
{
    srand(time(NULL));
    // int random = rand() % 42;
    // string word = array[random];
    // return word;
    int random = rand() % 42;
    int store = random;
    int it = 0;
    ifstream fin("WordList.txt");
    if (!fin)
    {
        cout << "Error in opening file" << endl;
    }
    string temp;
    while (!fin.eof())
    {
        getline(fin, temp);
        if (it == store)
        {
            fin.close();
            return temp;
        }
        it++;
    }
}

void hangman::displayDashes(char guessword[], int length)
{
    for (int i = 0; i < length; i++)
    {
        guessword[i] = '_';
        guessword[length] = '\0'; //! see later to remove this excess statement
    }
}

void hangman::displayWord(string word, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << word[i];
    }

    cout << endl;
}

void hangman ::displayMan(int remainingGuess)
{

    string part[4];
    switch (remainingGuess)
    {
    case 0:
        part[3] = "|";
    case 1:
        part[2] = "/|\\";
    case 2:
        part[1] = "/|\\";
    case 3:
        part[0] = "( )";
        break;
    }

    cout << "--------------\n";
    cout << "  |       " << part[3] << endl;
    cout << "  |       " << part[3] << endl;
    cout << "  |      " << part[0] << endl;
    cout << "  |      " << part[1] << endl;
    cout << "  |      " << part[2] << endl;
    cout << "  |\n";
    cout << "  |\n";
    cout << "--------------\n";
}

int hangman::guesscheck(string selectword, char guessWord[], char letter)
{
    int counter = 0;
    for (int i = 0; i < selectword.length(); i++)
    {
        if (selectword[i] == letter)
        {
            if (guessWord[i] == selectword[i])
            {
                counter = 1;
            }
            else
            {
                guessWord[i] = selectword[i];
                counter = 2;
            }
        }
    }

    return counter;
}

void displayGameDetails()
{
    cout << endl;
    cout << "        .---------------------------------------------------------------------------.\n"
            "        |   o     o      o     o      o    o o o    o       o      o     o      o   |\n"
            "        |   o     o    o   o   o o    o   o         o o   o o    o   o   o o    o   |\n"
            "        |   o     o   o     o  o  o   o   o         o   o   o   o     o  o  o   o   |\n"
            "        |   ooooooo   ooooooo  o   o  o   o   ooo   o       o   ooooooo  o   o  o   |\n"
            "        |   o     o   o     o  o    o o   o     o   o       o   o     o  o    o o   |\n"
            "        |   o     o   o     o  o     oo    o   o    o       o   o     o  o     oo   |\n"
            "        |   o     o   o     o  o      o     ooo     o       o   o     o  o      o   |\n"
            "        .---------------------------------------------------------------------------.\n";
}

int main()
{
    hangman obj;
    // obj.filehandle();
    int tries = 5;
    int remainingTries = 5;
    char guess;
    displayGameDetails();
    cout << endl;
    string selectword = obj.chooseWord();
    int wordlength = selectword.length();

    char guessword[wordlength];

    obj.displayDashes(guessword, wordlength);
    cout << "Guess the given word :-" << endl;
    obj.displayWord(guessword, wordlength);

    cout << endl;
    while (remainingTries > 0)
    {
        cout << "Enter a Letter to guess :- ";
        cin >> guess;

        int check = obj.guesscheck(selectword, guessword, guess);

        if (check == 0)
        {
            cout << "OOPS!! This letter is not correct" << endl;
            remainingTries--;
            obj.displayMan(remainingTries);
        }

        if (check == 1)
        {
            cout << "You have already guessed this letter" << endl;
        }

        if (check == 2)
        {
            cout << "YAY!! You guessed the correct letter" << endl;
        }

        cout << "You have " << remainingTries << " tries left" << endl;

        cout << "Guess the word :-" << endl;

        obj.displayWord(guessword, wordlength);

        if (guessword == selectword)
        {
            cout << "You Guesses The word and Won!!" << endl;
            return 0;
        }
    }

    if (guessword != selectword)
    {
        cout << "You Lost!!" << endl;
        cout << "The word was :- " << selectword;
    }

    // selectword = obj.chooseWord();
    // wordlength = selectword.length();
    // selectword = obj.chooseWord();
    // cout << selectword;
    return 0;
}
