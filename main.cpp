/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Tim
 *
 * Created on 8 June 2018, 8:25 AM
 */

#include <cstdlib>
#include <iostream>
#include <list>
using namespace std;


/*
 * Code to determine efficiency
 */
long compares; // for counting compares
long swaps; // for counting swaps


/*
 * 
 */
void insertValue(list<int>& minVal, list<int>& maxVal, int value, int& median);
bool startList(list<int>& minVal, list<int>& maxVal, int value, int& median);
void maxValInsert(list<int>& maxVal, int value, int& median);
void minValInsert(list<int>& minVal, int value, int& median);
void balanceLists(list<int>& minValRight, list<int>& maxValLeft);

/*
 *  
 */

int main(int argc, char** argv) {
    int value;
    int median;
    list<int> minValRight;
    list<int> maxValLeft;
    int size = 50000; // number of items to add

    // create a random numbers
        for (int i = 0; i < size; ++i) {
            value = rand() % size;

//    while ((cin >> value)) {
//        if (value == 000)break; // exit loop
        insertValue(minValRight, maxValLeft, value, median);
        // ensure lists stay within size 1 of each other


       // cout<< "Value In: " <<value<< "   Median: " << median << endl;
        //        cout << "Left Size: " << maxValLeft.size() << endl;
        //        cout << "Right Size: " << minValRight.size() << endl;
        balanceLists(minValRight, maxValLeft);
    }

    // uncomment for performance stats
    cout << "Items:   " << size << endl;
    cout << "Swaps:     " << swaps << endl;
    cout << "Compares:  " << compares << endl;

    return 0;
}

void balanceLists(list<int>& minValRight, list<int>& maxValLeft) {
    // compare list lengths to ensure not greater than 1 different in size
    int right = minValRight.size();
    int left = maxValLeft.size();
    list<int>::iterator foundPos;
    list<int>::iterator pos;

    if (left - right > 1) { // left too heavy.
        ++compares;
        //Move Left front to right front 
        //        cout << "Before Left " << maxValLeft.front() << endl;
        //        cout << "Before Right " << minValRight.front() << endl;
        minValRight.splice(minValRight.begin(), maxValLeft, maxValLeft.begin());
        //        cout << "Splice Left " << maxValLeft.front() << endl;
        //        cout << "Splice Right " << minValRight.front() << endl;
        ++swaps;
        // and move largest value in left to front

        int maxValue = maxValLeft.front();
        for (pos = maxValLeft.begin(); pos != maxValLeft.end(); pos++) {
            // iterate through the list
            foundPos = maxValLeft.begin();
            if (*pos > maxValue) {
                ++compares;
                maxValue = *pos;
                foundPos = pos;

            }

        }
        //        cout << "After Left " << maxValLeft.front() << endl;
        //        cout << "After Right " << minValRight.front() << endl;

        if (*foundPos != maxValLeft.front()) {
            // swap max to front
            int temp = maxValLeft.front();
            maxValLeft.front() = *foundPos;
            *foundPos = maxValLeft.front();
            ++swaps;
        }
    } else if (right - left > 1) { // right too heavy. 
        ++compares;
        //Move right front to left front 
        //        cout << "Before Right " << maxValLeft.front() << endl;
        //        cout << "Before Right " << minValRight.front() << endl;
        maxValLeft.splice(maxValLeft.begin(), maxValLeft, minValRight.begin());
        ++swaps;
        // and move smallest value in right to front
        int minValue = minValRight.front();
        for (pos = minValRight.begin(); pos != minValRight.end(); pos++) {
            // iterate through the list
            foundPos = minValRight.begin();
            if (*pos < minValue) {
                ++compares;
                minValue = *pos;
                foundPos = pos;
                ++swaps;

            }

        }

        if (*foundPos != minValRight.front()) {
            // swap max to front
            int temp = minValRight.front();
            minValRight.front() = *foundPos;
            *foundPos = minValRight.front();
            ++swaps;
        }
//        cout << "After Left " << maxValLeft.front() << endl;
//        cout << "After Right " << minValRight.front() << endl;

    }



    return;
}

void insertValue(list<int>& minValRight, list<int>& maxValLeft, int value, int& median) {
    // if minVal or maxVal empty because its a new dataset
    if (startList(minValRight, maxValLeft, value, median)) {
        return;
    }
    // if value<median insert into MaxVal
    if (value < median) {
        ++compares;
        maxValInsert(maxValLeft, value, median);
    }// if value>median insert into MinVal
    else if (value > median) {
        ++compares;
        minValInsert(minValRight, value, median);
    }// if value == median add to shorter list
    else { // put in smaller list
        ++compares;
        if (maxValLeft.size() < minValRight.size()) {
            maxValInsert(maxValLeft, value, median);
        } else {
            minValInsert(minValRight, value, median);
        }
    }
    return;
}

void maxValInsert(list<int>& maxValLeft, int value, int& median) {
    // If greater than first, insert it at the start of the list.
    if (value > maxValLeft.front()) {
        maxValLeft.push_front(value);
    }// If less or equal to first than insert it at the end of the list.
    else {
        maxValLeft.push_back(value);
    }
    median = maxValLeft.front();
    ++compares;
    return;
}

void minValInsert(list<int>& minValRight, int value, int& median) {
    // If greater than first, insert it at the end of the list.
    if (value > minValRight.front()) {
        minValRight.push_back(value);
    }// If less or equal to first than insert it at the start of the list.
    else {
        minValRight.push_front(value);
    }
    median = minValRight.front();
    ++compares;
    return;
}

bool startList(list<int>& minValRight, list<int>& maxValLeft, int value, int& median) {
    // check if both lists have had initial values added
    if (minValRight.empty()) {
        // insert the value
        minValRight.push_front(value);
        // set the median to the minVal
        median = value;
        return true;
    }

    if (maxValLeft.empty()) {
        // Swap minVal if maxVal is greater than minVal
        if (value > minValRight.front()) {
            ++compares;
            int temp;
            temp = minValRight.front();
            minValRight.front() = value;
            maxValLeft.push_front(temp);
            // set the median to the minVal
            median = value;
            ++swaps; // count of swaps for performance stats
            return true;
        } else {// insert the value in maxVal
            maxValLeft.push_front(value);
            // set the median to the minVal
            median = minValRight.front();
            return true;
        }
    }
    return false;
}
