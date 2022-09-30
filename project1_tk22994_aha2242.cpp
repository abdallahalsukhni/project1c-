/* 
// File Name: project1_tk22994_aha2242.cpp
// Authors: Tushar Kohli, Abdallah Al-Sukhni
// Date: 30 Sep 2022
// Assignment Number 1
// CS 105C Spring 2022
// Instructor: Dr. Palacios
// C++ program that will display a list of the top Internet stories on 
// Instagram (hereafter, 'Insta') https://www.instagram.com/ */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// encapsulates popularity SCORE, TITLE and URL of Insta story
struct Story {
  int score;    // popularity SCORE of Insta story
  string title; // TITLE thereof
  string url;   // URL thereof
};

// function prototypes
void readInputToArray(Story *storyArr, const int STORY_ARR_SIZE, ifstream *storyFile);
int findMode(const Story* STORY_ARR, const int STORY_ARR_SIZE, unordered_map<int, vector<Story> > *map);

/*********************************************************** 
// READINPUTTOARRAY: Reads input Insta story data into dynamic array
// :param STORYARR: Ptr to array of `Story` structs
// :param STORYARRSIZE: Size of STORYARR (integer)
// :param STORYFILE: File stream object of our user's Insta story data
***********************************************************/
void readInputToArray(Story *storyArr, const int STORY_ARR_SIZE, ifstream& storyFile) {
  string nothing;   // consumes newline at end of first line (number of stories)
  getline(storyFile, nothing);
  // read input data into array
  for (int storyNum = 0; storyNum < STORY_ARR_SIZE; storyNum++) {
    int score;    // SCORE of story
    string title; // TITLE thereof
    string url;   // stores URL thereof
    getline(storyFile, title);
    getline(storyFile, url);
    storyFile >> score;
    getline(storyFile, nothing);
    Story newStory = {score, title, url}; // struct to hold a new Story
    *(storyArr + storyNum) = newStory;
  }
}

/*********************************************************** 
// MAIN: base of execution
// :return: where there was an error (1) in  or no! (0)
***********************************************************/
int main() {
  string fileToBeOpened;  // file where story data lies
  cout << "Type the name of the file you would like to open: ";
  cin >> fileToBeOpened;
  cout << "\n";
  ifstream storyFile;  // file stream object
  storyFile.open(fileToBeOpened, std::ios_base::in);
  if (!storyFile) {
    cout << "File does not exist\n";
    return 1;
  }
  int storyArrSize = 0; // CONST to hold size of Story array
  storyFile >> storyArrSize;
  Story *storyArr = new Story[storyArrSize];  // dynamically allocate mem
  readInputToArray(storyArr, storyArrSize, storyFile);
  storyFile.close();

  unordered_map<int, vector<Story> > map; // MAP scores to stories with that score
  int trueMode = findMode(storyArr, storyArrSize, &map); // mode of story score data
  
  // if no mode found
  if (trueMode == -1)
    cout << "Mode: No mode was found.\n\n";
  else {
    // finally, print out mode, and each story's title and url in the final mode vector
    cout << "Mode: " << trueMode << "\n\n";
    vector<Story> storiesToBePrinted = map[trueMode]; // stories with SCORE==TRUEMODE
    for (auto& thisStory : storiesToBePrinted)
      cout << thisStory.title << "\n" << thisStory.url << "\n\n";
  }

  delete[] storyArr;  // free memory!!!!
  return 0;
}

/*********************************************************** 
// FINDMODE: find mode, map score to vector of story for each score, have a vector of stories with that score
// :param STORYARR: ptr to array of `Story` structs
// :param STORYARRSIZE: Integer that indicates number of elems in array
// :param MAPPTR: ptr to map from popularity scores to stories with that score 
// :return: TRUEMODE: statistical mode of score data 
***********************************************************/
int findMode(const Story* STORY_ARR, const int STORY_ARR_SIZE, unordered_map<int, vector<Story> > *mapPtr) {
  unordered_map<int, vector<Story> > map = *mapPtr; // maps scores to stories
  for (int i = 0; i < STORY_ARR_SIZE; i++) {
    Story story = *(STORY_ARR + i);   // story at Ith pos in STORY_ARR
    if (map.count(story.score) == 0) {
      vector<Story> thisScoreVector;
      thisScoreVector.push_back(story);
      map[story.score] = thisScoreVector;
    } 
    else
      map[story.score].push_back(story);
  }

  int currFreq = -1;  // check to see if all modes are the same or not
  bool foundDiff = false; // does the data have a mode?
  for (auto& storyFreq : map) {
    if (currFreq == -1)
      currFreq = storyFreq.second.size();
    else if (currFreq != storyFreq.second.size()) {
      foundDiff = true;
      break;
    }
  }
  if (!foundDiff)
    return -1;
	
  int mode = 0;           // our mode!
  int mostFreqSoFar = 0;  // most freqent mode value so far
  // calculate what the mode is
  for (auto& storyFreq : map) {
    if (storyFreq.second.size() > mostFreqSoFar) {
      mode = storyFreq.first;
      mostFreqSoFar = storyFreq.second.size();
    }
  }
  
  // if there are multiple modes then add each of them to a list, and find which one occurs first in input file
  vector<int> modeVector; // vector in question
  for (auto& storyFreq : map) {
    if (storyFreq.second.size() == mostFreqSoFar)
      modeVector.push_back(storyFreq.first);
  }

  int trueMode = -1;  // find which mode occurs first in input file
  for (int spot = 0; spot < STORY_ARR_SIZE; spot++) {
    bool found = false;
    Story story = *(STORY_ARR + spot);
    int modeToBeFound = story.score;
    for (auto& thisMode : modeVector) {
      if (thisMode == modeToBeFound) {
        found = true;
        trueMode = thisMode;
        break;
      }
    }
    if (found)
      break;
  }

  return trueMode;
}
