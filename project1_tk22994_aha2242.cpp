/* 
// File Name: project1_tk22994.aha2242.cpp
// Authors: Tushar Kohli, Abdallah Al-Sukhni
// Date: 25 Sep 2022
// Assignment Number 1
// CS 105C Spring 2022
// Instructor: Dr. Palacios
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;


// C++ program that will display a list of the 
// top Internet stories on Instagram
struct Story{
    int score;
    string title;
    string url;
};


int main() {
    string fileToBeOpened;
    cout << "type the name of the file you would like to open: ";
    cin >> fileToBeOpened;
    ifstream myfile; 
    myfile.open(fileToBeOpened);
    if(!myfile) {
        cout << "file does not exist";
    }
    int storyArrSize;
    myfile >> storyArrSize;
    string nothing;
    getline(myfile, nothing);
    Story *storyArr = nullptr;
    storyArr = new Story[storyArrSize];
    // read input data into array
    for(int storyNum = 0; storyNum < storyArrSize; storyNum++) {
        string url;
        string title;
        int score;
        std::getline(myfile, title);
        std::getline(myfile, url);
        myfile >> score;
        getline(myfile, nothing);
        Story newStory = {score, title, url};
        *(storyArr + storyNum) = newStory;
    }

   // find mode, map int to vector of story
    // for each score, have a list of vectors with that score
    unordered_map<int, vector<Story>> map;
    for(int i = 0; i < storyArrSize; i++) {
        Story story = *(storyArr + i);
        if(map.count(story.score) == 0) {
            vector<Story> thisScoreVector;
            thisScoreVector.push_back(story);
            map[story.score] = thisScoreVector;
        } else {
            map[story.score].push_back(story);
        }
    }
    vector<Story> modeVector;
    int currFreq = -1;
    bool foundDiff = false;
    // then iterate through map and find frequency with vector size that is the highest, that will be our mode frequency
    // no mode if all frequencies are the same(return -1)
    // have a vector that points to the current highest frequency's story vector, and return those stats
    // for(int freq : map) {
    //     if(currFreq == -1) {
    //         currFreq = freq;
    //     } else if(currFreq != freq) {
    //         foundDiff = true;
    //         break;
    //     }
    // }
    // if(!foundDiff) {
    //     cout << -1;
    // }

    // finally, print out mode, and each story's title and url in the final mode vector
    return 0;
}


