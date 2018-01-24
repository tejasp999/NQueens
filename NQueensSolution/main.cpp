//
//  main.cpp
//  NQueensSolution
//
//  Created by Teja PV on 10/29/17.
//  Copyright © 2017 Teja PV. All rights reserved.
//
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

class NQueen {
public:
    int N;
    int* Position;
    int startH;
    int cBestH;
    int* cBestP;
    int limit;
    int stateChanges;
    int HScount;
    int totalRestarts = 0,totalStateChanges = 0;
    //Return number of attacking pairs
    int CalHeuristic(int state[]) {
        int pcnt = 0;
        for (int i = 0; i < N; i++) {
            //row
            for(int j = i + 1; j < N; j++) {
                if( state[i] == state[j] ) {
                    pcnt++;
                }
            }
            //down right diag
            for(int j = i + 1; j < N; j++) {
                if( (state[i] + j - i) == state[j] ) {
                    pcnt++;
                }
            }
            // up right diag
            for(int j = i + 1; j < N; j++) {
                if( (state[i] - (j - i)) == state[j] ) {
                    pcnt++;
                }
            }
        }
        return pcnt;
    }
    //Update the State of the Queens after making a move
    void CopyState(int NewState[], int OldState[]) {
        for(int i = 0; i < N; i++) {
            NewState[i] = OldState[i];
        }
    }
    //Find the Best Successor by finding Minimum Number of Attacking pairs and set queen at the point
    int FindBestSuccessor(int currentH, int* state, int* nextBest) {
        int min_h = N*N;
        int minState[N];
        for (int i = 0; i < N; i++) {
            int newState[N];
            CopyState(newState, state);
            for (int j = 0; j < N; j++) {
                if(Position[i] != j) {
                    newState[i] = j;
                    int H = CalHeuristic(newState);
                    if( H < min_h) {
                        minState[i] = j;
                        min_h = H;
                        CopyState(minState, newState);
                    }
                }
            }
        }
        if(min_h != currentH) {
            CopyState(nextBest,minState);
        }
        return min_h;
    }
    //The hill climb search
    void SolveNQueenHillClimb() {
        int* nextBest = new int[N];
        totalStateChanges++;
        int nBestH = cBestH;
        nBestH = FindBestSuccessor(cBestH, cBestP, nextBest);
        if(nBestH < cBestH) {
            if(nBestH == cBestH) {
                HScount++;
                totalRestarts++;
            } else {
                HScount = 0;
            }
            cBestH = nBestH;
            CopyState(cBestP, nextBest);
            SolveNQueenHillClimb();
        } else {
            return;
        }
    }

public:
    //Initialize NQueen Object
    NQueen(int N) {
        this->N = N;
        Position = new int[N];
        cBestP = new int[N];
        for(int i = 0 ; i < N ; i++) {
            Position[i] = 0;
            cBestP[i] = 0;
        }
        limit = 20;
        HScount = 0;
    }
    /* algo = 1 --> caluclates only one random value. rest will depend on it
     algo = 2 --> randomises all values.
     
     */
    void CreateRandomBoard(int state[], int algo) {
        
        time_t seconds;
        time(&seconds);
        srand((unsigned int) seconds);
        int rnd = 0;
        
        if(algo == 1) {
            
            rnd = rand() % N;
            for(int i = 0 ; i < N ; i++) {
                state[i] = rnd;
                rnd = (rnd + 2) % N;
            }
        }
        else if (algo == 2) {
            for(int i = 0; i < N; i ++) {
                rnd = rand() % N;
                state[i] = rnd;
            }
        }
        
    }
    //Solve the N Queen initial state
    void SolveNQueen() {
        CreateRandomBoard(Position, 1);
        startH = CalHeuristic(Position);
        cBestH = startH;
        CopyState(cBestP, Position);
        int count = 0;
        while(cBestH != 0) {
            if(count > 1 && count < 25) {
                CreateRandomBoard(Position, 1);
            } else {
                CreateRandomBoard(Position, 2);
            }
            cBestH = CalHeuristic(Position);
            CopyState(cBestP, Position);
            SolveNQueenHillClimb();
            count++;
        }
        cout << "Final State..." << endl;
        cout << "heuristic: " << cBestH << endl;
        cout << "retry count: " << count << endl;
        cout << "state change count: " << HScount << endl;
        DisplayBoard(cBestP);
    }

    //Used to Display the Board in Console
    void DisplayBoard(int state[]) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(i == state[j]) {
                    cout << "Q ";
                } else {
                    cout << "* ";
                }
            }
            cout << endl;
        }
    }

};


int main() {
    int size = 0;
    cout << "Enter number of queens" << endl;
    cin >> size;
    NQueen* queen = new NQueen(size);
    cout << "Hill Climb Started" << endl;
    queen->SolveNQueen();

}


