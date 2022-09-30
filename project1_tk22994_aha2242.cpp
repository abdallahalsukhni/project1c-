/* 
// File Name: project1_tk22994_aha2242.cpp
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
struct Story {
  int score;
  string title;
  string url;
};

int findMode(const Story* STORY_ARR, const int STORY_ARR_SIZE);
int readInputToArray(Story *storyArr, int *storyArrSizePtr, string fileToBeOpened);

unordered_map<int, vector<Story> > map;

int readInputToArray(Story *storyArr, int *storyArrSizePtr, string fileToBeOpened) {
  ifstream myfile;
  myfile.open(fileToBeOpened);
  if (!myfile) {
    cout << "File does not exist\n";
    return 1;
  }
  myfile >> *storyArrSizePtr;
  string nothing;
  getline(myfile, nothing);
  int i = *storyArrSizePtr;
  // read input data into array
  for (int storyNum = 0; storyNum < i; storyNum++) {
    string url; 
    string title;
    int score;
    getline(myfile, title);
    getline(myfile, url);
    myfile >> score;
    getline(myfile, nothing);
    Story newStory = {score, title, url};
    *(storyArr + storyNum) = newStory;
  }
  myfile.close();
  return 0;
}

int main() {
  string fileToBeOpened;
  cout << "Type the name of the file you would like to open: ";
  cin >> fileToBeOpened;
  cout << "\n";
  int storyArrSize = 0;
  Story *storyArr = new Story[storyArrSize];
  int error = readInputToArray(storyArr, &storyArrSize, fileToBeOpened);
  if (error)
    return 1;

  int trueMode = findMode(storyArr, storyArrSize);

  // if no mode found
  if (trueMode == -1)
    cout << "Mode: No mode was found.\n\n";
  else {
    // finally, print out mode, and each story's title and url in the final mode vector
    cout << "Mode: " << trueMode << "\n\n";
    vector<Story> storiesToBePrinted = map[trueMode];
    for (auto& thisStory : storiesToBePrinted)
      cout << thisStory.title << "\n" << thisStory.url << "\n\n";
  }

  delete[] storyArr;
  return 0;
}

int findMode(const Story* STORY_ARR, const int STORY_ARR_SIZE) {
  // find mode, map int to vector of story
  // for each score, have a vector of stories with that score
  for (int i = 0; i < STORY_ARR_SIZE; i++) {
    Story story = *(STORY_ARR + i);
    if (map.count(story.score) == 0) {
      vector<Story> thisScoreVector;
      thisScoreVector.push_back(story);
      map[story.score] = thisScoreVector;
    } 
    else
      map[story.score].push_back(story);
  }

  // check to see if all modes are the same or not
  int currFreq = -1;
  bool foundDiff = false;
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
	
  vector<int> modeVector;
  int mode = 0;
  int mostFreqSoFar = 0;

  // calculate what the mode is
  for (auto& storyFreq : map) {
    if (storyFreq.second.size() > mostFreqSoFar) {
      mode = storyFreq.first;
      mostFreqSoFar = storyFreq.second.size();
    }
  }

  // if there are multiple modes then add each of them to a list, and find which one occurs first in input file
  for (auto& storyFreq : map) {
    if (storyFreq.second.size() == mostFreqSoFar)
      modeVector.push_back(storyFreq.first);
  }

  int trueMode = -1;
  // find which mode occurs first in input file
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
