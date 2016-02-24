//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Israel Goitom on 10/02/2016.
//  Copyright © 2016 Israel Goitom. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMAP std::map;

FBullCowGame::FBullCowGame(){ Reset(); }

void FBullCowGame::Reset() { //TODO make this more robust
    
    MyMaxTries = 0;
    MyHiddenWord = "";
    MyCurrentTries = 1;
    bGameIsWon = false;
    
    return;
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTries; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}

FString FBullCowGame::SetHiddenWord(int level) {
    
    std::map<int, FString> myWord;
    
    myWord [1] = "ant";
    myWord [2] = "road";
    myWord [3] = "among";
    myWord [4] = "ransom";
        
    std::map  <FString, int> DifficultyLevel;
    DifficultyLevel ["ant"] = 2;
    DifficultyLevel ["road"] = 4;
    DifficultyLevel ["among"] = 6;
    DifficultyLevel ["ransom"] = 8;
    
    MyHiddenWord = myWord[level];
    MyMaxTries = DifficultyLevel[myWord[level]];
    
    return myWord[1];
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
        
    if (!IsIsogram(Guess)) { // if Guess is not isogram
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowerCase(Guess)) { // if Guess is not lower case
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) { // if the guess word length is wrong
        return EGuessStatus::Length_Wrong;
    }
    else { // All is good
        return EGuessStatus::OK;
    }
}

// keep count of player's guess and check for Bulls and Cows in the guessed word
FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
    
    // increment turn by one
    MyCurrentTries++;
    
    // create return variable
    FBullCowCount BullCowCount;
    
    // loop through all letters in the guess
    int32 HiddenWordLength = GetHiddenWordLength();
    for (int32 HWCount = 0; HWCount < HiddenWordLength; HWCount++) { // HWCount = Hidden Word Count
        
        // compare letters against the hidden word
        for (int32 GWCount = 0; GWCount < HiddenWordLength; GWCount++) { // GWCount = Guess Word Count
            if (MyHiddenWord[HWCount] == Guess[GWCount]) { // if the a letter from the guessed word matches that of the hidden word
                if (HWCount == GWCount) { // increment Bulls if it is on the same place
                    BullCowCount.Bulls++;
                }else { //else increment Cows
                    BullCowCount.Cows++;
                }
            }
        }
    }
    
    if (BullCowCount.Bulls == GetHiddenWordLength()) {
        bGameIsWon = true;
    } else {
        bGameIsWon = false;
    }
   
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    
    if (Word.length() <= 1) { return true; }
    
    std::map <char, bool> LetterSeen;   //create a hash table of the alpabets
    
    for (auto Letter : Word){ //loop throgh each letters of the guess word
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) { // Has letter been seen before
            return false;
        } else { // if letter has not been seen then create an entry
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const {
    
    for (auto Letter : Word) {
        if (!islower(Letter)) {
            return false;
        }
    }
    
    return true;
}





