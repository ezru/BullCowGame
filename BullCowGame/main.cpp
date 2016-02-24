//
//  main.cpp
//  BullCowGame
//
//  Created by Israel Goitom on 08/02/2016.
//  Copyright © 2016 Israel Goitom. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// Making the code unreal engine friendly
using int32 = int;
using FText = std::string;

// prototyping because functions are outside class
void PrintIntro();
FText GetValidGuess();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();

// instantiating a new game globally becuase the same instance will be used
FBullCowGame BCGame;

int main(int32 argc, const char * argv[]) {
    
    bool Response = false; // variable for ending or continuing the game
    
    do {
        PlayGame();
        Response = AskToPlayAgain();
    }
    while (Response == true);


    return 0; // exit programm
}

// Splash game introduction
void PrintIntro () {
    int32 GameLevel;
    std::cout << "\n Welcome to Bulls and Cows, a fun word game!\n\n";
    std::cout << "                     }    {           ____ \n";
    std::cout << "                     (o  o)          (o  o) \n";
    std::cout << "     /----------------\\  /            \\  /----------------\\   \n";
    std::cout << "    / |               | O               O |              | \\  \n";
    std::cout << "   /  |               |                   |              |  \\ \n";
    std::cout << "  *   |_______________|                   |______________|   * \n";
    std::cout << "       |   ;         |                      |        YY |      \n";
    std::cout << "       |             |                      |           |      \n";
    std::cout << "       ^             ^                      ^           ^      \n\n";
    std::cout << "1. I am useless at this. \n";
    std::cout << "2. I can hold my weight on two feet.\n";
    std::cout << "3. I am good at this game hit me. \n";
    std::cout << "4. Nothing I can't do. \n\n";
    
    bool CorrectLevel = false;
    do {
        std::cout << "Please choose your level: ";
        std::cin >> GameLevel;
        std::cin.ignore();
        if (std::cin.fail()){
            CorrectLevel = false;
            std::cin.ignore();
            std::cout << "The value you entered is incorrect, please choose one of the listed numbers\n\n";
        }else {
            CorrectLevel = true;
        }
    } while (CorrectLevel == false);
    
    BCGame.SetHiddenWord(GameLevel);
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout <<" letter isogram I am thinking of? \n";
    std::cout << std::endl;
    
    return;
}

void PlayGame() {
    
    BCGame.Reset(); // make sure a clean game is started everytime
    
    PrintIntro();
    
    int32 MaxTries = BCGame.GetMaxTries();  // Number of tries a player is allowed
    
    std::cout << MaxTries;
    
    FBullCowCount BullsAndCows; // return how many Bulls and Cows the player has achieved
    
    // loop for the number of tries the player has
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        
        FText Guess = GetValidGuess(); // get a guess from the user
        
        BullsAndCows = BCGame.SubmitGuess(Guess); // keep count of guess and check bulls and cows on the word
        std::cout << "Bulls: " << BullsAndCows.Bulls;
        std::cout << " Cows: " << BullsAndCows.Cows << "\n\n";
        
    }
    
    PrintGameSummary();
    return;
}

// loop until you get valid guess from the user
FText GetValidGuess(){
    
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    
    do {
        // get input from the user
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << ". Enter your Guess: ";
        std::getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess); // make sure that the guess word does not cause run time error
        switch (Status) {
            case EGuessStatus::Length_Wrong:
                std::cout << "Please enter " << BCGame.GetHiddenWordLength() << " letter word \n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters. \n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter your guess all in lowercase. \n\n";
            default:
                break;
        }
    }while (Status != EGuessStatus::OK);
    
    return Guess;
}

bool AskToPlayAgain() {
    std::cout << "Do you want to play again? (y/n): ";
    FText Response = "";
    std::getline(std::cin, Response);
    std::cout << std::endl;
    
    return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "Well done! you have won this sad game! \n\n";
    } else {
        std::cout << "Well shit happens, this time that shit is you! \n\n";
    }
}




