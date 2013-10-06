/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name: 朱璁
 * Student ID: 5120379073
 * This file is the starter project for the word ladder problem.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include "map.h"
using namespace std;

Lexicon english("EnglishWords.dat");

//print ladder
void PrintLadder(Vector<string> ladder){
    foreach(string word in ladder){
        cout<<word<<" ";
    }
    cout<<endl;
}

// find every word in the lexicon that differs by one word
Vector<string> next_words(string word){
    Vector<string> next_words;
    for (int i = 0; i < word.length(); i++) {
        char self = word[i];
        for (int j = 0; j < 26; j++) {
            if (char(j + 'a') != self){
                word[i] = char(j + 'a');
                if (english.contains(word)){
                    next_words.add(word);
                }
            }
        }
    }
    
    return next_words;
}

//check if the word has been used in the ladder
bool isUsed(string word, Vector<string> ladder){
    for (int i = 0; i < ladder.size(); i++) {
        if (word == ladder[i]){
            return 1;
        }
    }
    return 0;
}

// the implement of wordladder function
void DoWordLadder(string start_word, string dest_word){
    Queue< Vector<string> > queue; // creat an empty queue
    
    Vector<string> ladder;
    ladder.add(start_word);
    queue.enqueue(ladder);
    
    while (!queue.isEmpty()) {
        Vector<string> first = queue.dequeue();
        if (first[first.size() - 1] == dest_word) {
            PrintLadder(first);
            return;
        }
        foreach (string word in next_words(first[first.size() - 1 ])){
            if (!isUsed(word, first)) {
                Vector<string> temp = first;
                temp.add(word);
                queue.enqueue(temp);
            }
        }
    }
    cout<<"No Ladder found!"<<endl;
    return;
}

int main()
{
    
    //ask for the start word and destination word
    while (true) {
        string start_word = getLine("Enter start word (RETURN to quit): ");
        if (start_word == "") {
            break;
        }
        string dest_word = getLine("Enter destination word (RETURN to quit): ");
        DoWordLadder(start_word, dest_word);
    }
    
    return 0;
}
