#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <tuple>
#include <vector>
#include "Compete.h"

using namespace std;

unsigned long timeA;
unsigned long timeB;

void determineResult(int res, int& aWin, int& bWin, int& tie){
	switch(res){
		case 0:
			tie++;	//平局
			cout << "A and B tied" << endl;
			break;
		case 1:
			aWin++;	//A赢
			cout << "A - won" << endl;
			break;
		case 2:
			bWin++;	//B赢
			cout << "B - won" << endl;
			break;
		case 3:
			bWin++;	//A出错,算B赢
			cout << "A - bug occurred" << endl;
			break;
		case 4:
			bWin++;	//A给出非法落子,算B赢
			cout << "A - made illegal step" << endl;
			break;
		case 5:
			aWin++;	//B出错,算A赢
			cout << "B - bug occurred" << endl;
			break;
		case 6:
			aWin++;	//B给出非法落子,算A赢
			cout << "B - made illegal step" << endl;
			break;
		case 7:
			bWin++;	//A超时,算B赢
			cout << "A - timed out" << endl;
			break;
		case 8:
			aWin++;	//B超时,算A赢
			cout << "B - timed out" << endl;
			break;
		case -1:
			cout << "Load File A Error" << endl;
			break;
		case -2:
			cout << "Load File B Error" << endl;
			break;
		case -3:
			cout << "Function Interface Error in A" << endl;
			break;
		case -4:
			cout << "Function Interface Error in B" << endl;
			break;
		default:
			cout << "Platform Error" << endl;
			break;
	}
}

std::tuple<int, int> test(char* A, char* B, int times)
{
	int res;
    
	int aWin = 0, bWin = 0, tie = 0;
	int numRounds = times;
	
	for(int i = 0; i < numRounds; i++){
		cout << "Round " << i << ":" << endl;
		
		Data* data = new Data();
        
		cout << "A first:" << endl;
		timeA = 0;
		timeB = 0;
		//data->reset();
		res = compete(A, B, true, data);
		determineResult(res, aWin, bWin, tie);
		
		cout << "B first:" << endl;
		timeA = 0;
		timeB = 0;
		data->reset();
		res = compete(A, B, false, data);
		determineResult(res, aWin, bWin, tie);
		cout << endl;
        
		delete data;
	}
	
	double rioAWin = (1.0 * aWin) / (2.0 * numRounds);
	double rioBWin = (1.0 * bWin) / (2.0 * numRounds);
	double rioTie = (1.0 * tie) / (2.0 * numRounds);
	
	cout << "Stat:" << endl;
	cout << "ratio of A wins : " << rioAWin << endl;
	cout << "ratio of B wins : " << rioBWin << endl;
	cout << "ratio of Tie : " << rioTie << endl;
	cout << endl;
	cout << "ratio of (A wins + tie) : " << rioAWin + rioTie << endl;
	cout << "ratio of (B wins + tie) : " << rioBWin + rioTie << endl;
	
	return std::make_tuple(aWin, tie);
}

// add this as real main function
int main(int argc, char** argv)
{
	if (argc != 3) {
		printf("Usage: %s <times per each opponent> -all|-ten|<number>\n", argv[0]);
		return 1;
	}

	// change to your dylib file
	char my[250] = "/Users/paul/Library/Developer/Xcode/DerivedData/Strategy-bqxcsdslnyfwvedvvimcxhevcnzf/Build/Products/Release/libStrategy.dylib";
	std::vector<char*> opponents;
	if (strcmp(argv[2], "-all") == 0) {
		for (int i = 2; i <= 100; i += 2) {
			char* buf = new char[250];
			sprintf(buf, "../Testcases/%d.dylib", i);
			opponents.push_back(buf);
		}
	} else if (strcmp(argv[2], "-ten") == 0) {
		for (int i = 10; i <= 100; i += 10) {
			char* buf = new char[250];
			sprintf(buf, "../Testcases/%d.dylib", i);
			opponents.push_back(buf);
		}
	} else {
		char* buf = new char[250];
		sprintf(buf, "../Testcases/%s.dylib", argv[2]);
		opponents.push_back(buf);
	}

	int times = atoi(argv[1]);
	std::vector<int> wins, ties;
	int win, tie;
	for (auto opponent : opponents) {
		printf("# Current opponent: %s\n", opponent);
		std::tie(win, tie) = test(my, opponent, times);
		wins.push_back(win);
		ties.push_back(tie);
	}

	printf("\n# All wins: [ ");
	for (const auto& win : wins) {
		printf("%d ", win);
	}
	printf("]\n");

	printf("# Summary\n");
	int maxWin = 0, minWin = 10000;
	int sumWin = 0, sumTie = 0;
	for (const auto& win : wins) {
		sumWin += win;
		if (win > maxWin) {
			maxWin = win;
		}
		if (win < minWin) {
			minWin = win;
		}
	}

	for (const auto& tie : ties) {
		sumTie += tie;
	}

	printf("Total games: %d\n", times * 2 * opponents.size());
	printf("Total wins: %d (max: %d, min: %d, ratio: %.2f)\n", sumWin, maxWin, minWin, 100 * sumWin / float(times * 2 * opponents.size()));
	printf("Total ties: %d\n", sumTie);

	return 0;
}
