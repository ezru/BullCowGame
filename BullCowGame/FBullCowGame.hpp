//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Israel Goitom on 10/02/2016.
//  Copyright © 2016 Israel Goitom. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>
#include <iostream>

using int32 = int;
using FString = std::string;

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Length_Wrong,
    Not_Lowercase
};


struct FBullCowCount {
    
    int32 Bulls = 0;
    int32 Cows = 0;
};

class FBullCowGame {
public:
    FBullCowGame(); //Constructor
    
    int32 GetMaxTries() const;  // TODO the number of tries shouldbe related to the length of the word
                                // possibly create an equation that calculates based on a statistical model
    
    int32 GetCurrentTry() const;// Keep track of how many tries a player had in a game instance
    FString SetHiddenWord(int);
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const; // TODO make a richer return value

    void Reset(); // TODO make a richer return vlaue

    FBullCowCount SubmitGuess(FString); // This is the powehouse of the game it:
                                        // 1. Counts the number of tries
                                        // 2. It compares the guess word with hidden word and returns the number of
                                            // Bull and Cows
                                        // 3. Determines whether the game is won
    
    
private:
    int32 MyCurrentTries; // keep track of number of tries of a player in a game
    int32 MyMaxTries; // maximum number of tries allowed for a given hidden word, this is set through a dedicated method
    FString MyHiddenWord; // TODO create a list of hidden words: should be a map of words and number of tries for each word
    bool bGameIsWon; // game status win/lose. This is set through th method SubmitGuess.
    
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
};

#endif /* FBullCowGame_hpp */
