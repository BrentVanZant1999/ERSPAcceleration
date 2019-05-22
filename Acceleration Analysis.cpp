// Acceleration Analysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map> 
#include <math.h>
#define M_PI 3.14159265358979323846
#include <cmath> 
#include <algorithm>   
using namespace std;

const int NUM_FILES = 5;
string FILENAMES[5] = { "4-7-19","4-7-19-1554664", "4-7-19evening", "4-7-19evening2", "4-8-19" };
double standardX = 0;
double standardY = 3;
double standardZ = 9.2;
double smaCalc(vector<double> inputVec) {
	double sma = 0;
	double sum = 0;
	for (int z = 0; z < inputVec.size(); z++) {
		sum += inputVec[z]; 
	}
	sma = sum / inputVec.size();
	return sma; 
}

double maxCalc(vector<double> inputVec) {
	double max = inputVec[0];
	for (int z = 0; z < inputVec.size(); z++) {
		if (inputVec[z] > max) {
			max = inputVec[z];
		}
	}
	return max;
}

double minCalc(vector<double> inputVec) {
	double min = inputVec[0];
	for (int z = 0; z < inputVec.size(); z++) {
		if (inputVec[z] < min) {
			min = inputVec[z];
		}
	}
	return min;
}

void readAndExtract(string input) {
	string currentFileName = input + ".txt";
	ifstream data(currentFileName);
	string curLine;

	vector<string> collectedTime;
	vector<string> collectedX;
	vector<string> collectedY;
	vector<string> collectedZ;

	//data gathering
	while (getline(data, curLine))
	{
		stringstream lineStream(curLine);

		string cell;
		int colAtCounter = 0;
		while (getline(lineStream, cell, ','))
		{
			if (colAtCounter == 1) {
				collectedTime.push_back(cell);
			}
			else if (colAtCounter == 2) {
				collectedX.push_back(cell);
			}
			else if (colAtCounter == 3) {
				collectedY.push_back(cell);
			}
			else if (colAtCounter == 4) {
				collectedZ.push_back(cell);
			}
			colAtCounter++;
		}
	}
	data.close();

	vector<double> longsOfTime;
	vector<double> doublesX;
	vector<double> doublesY;
	vector<double> doublesZ;

	for (unsigned int i = 0; i < collectedTime.size(); i++) {
		double time;
		double xNum;
		double yNum;
		double zNum;
		string num;
		num = collectedTime[i];
		if (num == "") {
			longsOfTime.push_back(0);
		}
		else {
			time = atof(num.c_str());
			longsOfTime.push_back(time);
		}

		num = collectedX[i];
		if (num == "") {
			doublesX.push_back(standardX);
		}
		else {
			xNum = atof(num.c_str());
			doublesX.push_back(xNum);
		}
		num = collectedY[i];
		if (num == "") {
			doublesY.push_back(standardY);
		}
		else {
			yNum = atof(num.c_str());
			doublesY.push_back(yNum);
		}
		num = collectedZ[i];
		if (num == "") {
			doublesZ.push_back(standardZ);
		}
		else {
			zNum = atof(num.c_str());
			doublesZ.push_back(zNum);
		}
	}
	//sma analysis 

	vector<double> smaXTwenty; 
	vector<double> smaYTwenty;
	vector<double> smaZTwenty;

	vector<double> smaXHund;
	vector<double> smaYHund;
	vector<double> smaZHund;

	vector<double> valsTwentyX;
	vector<double> valsTwentyY;
	vector<double> valsTwentyZ;

	vector<double> valsHundredX;
	vector<double> valsHundredY;
	vector<double> valsHundredZ;
	
	for (unsigned int i = 0; i < collectedTime.size(); i++) {
	

		if (valsTwentyX.size() < 20) {
			valsTwentyX.push_back(doublesX[i]);
			valsTwentyY.push_back(doublesY[i]);
			valsTwentyZ.push_back(doublesZ[i]);
		}
		else {
			valsTwentyX.erase(valsTwentyX.begin());
			valsTwentyY.erase(valsTwentyY.begin());
			valsTwentyZ.erase(valsTwentyZ.begin());
			valsTwentyX.push_back(doublesX[i]);
			valsTwentyY.push_back(doublesY[i]);
			valsTwentyZ.push_back(doublesZ[i]);
		}

		if (valsHundredX.size() < 100) {
			valsHundredX.push_back(doublesX[i]);
			valsHundredY.push_back(doublesY[i]);
			valsHundredZ.push_back(doublesZ[i]);
		}
		else {
			valsHundredX.erase(valsHundredX.begin());
			valsHundredY.erase(valsHundredY.begin());
			valsHundredZ.erase(valsHundredZ.begin());
			valsHundredX.push_back(doublesX[i]);
			valsHundredY.push_back(doublesY[i]);
			valsHundredZ.push_back(doublesZ[i]);
		}

		smaXTwenty.push_back(smaCalc(valsTwentyX));
		smaYTwenty.push_back(smaCalc(valsTwentyY));
		smaZTwenty.push_back(smaCalc(valsTwentyZ));

		smaXHund.push_back(smaCalc(valsHundredX));
		smaYHund.push_back(smaCalc(valsHundredY));
		smaZHund.push_back(smaCalc(valsHundredZ));
	}

	vector<double> valsMinHundredX;
	vector<double> valsMinHundredY;
	vector<double> valsMinHundredZ;

	vector<double> valsMaxHundredX;
	vector<double> valsMaxHundredY;
	vector<double> valsMaxHundredZ;

	for ( int i = 0; i < collectedTime.size(); i++) {

		
			vector<double> valXHundred;
			vector<double> valYHundred;
			vector<double> valZHundred;

			for (int j = i - 50; j < i + 50; j++) {
				if (j >= 0) {
					if (j < doublesX.size()) {
						valXHundred.push_back(doublesX[j]);
						valYHundred.push_back(doublesY[j]);
						valZHundred.push_back(doublesZ[j]);
					}
				
				}
			}
			valsMaxHundredX.push_back(maxCalc(valXHundred));
			valsMaxHundredY.push_back(maxCalc(valYHundred));
			valsMaxHundredZ.push_back(maxCalc(valZHundred));

			valsMinHundredX.push_back(minCalc(valXHundred));
			valsMinHundredY.push_back(minCalc(valYHundred));
			valsMinHundredZ.push_back(minCalc(valZHundred));
	}

	// min max 
	//print file 
	string display;
	std::ofstream outputFile;
	outputFile.open(input + ".csv");
	outputFile << "Time,xAcceleration,yAcceleration,zAcceleration,xSMA(2.5 seconds),xSMA(10 seconds),ySMA(2.5 seconds),ySMA(10 seconds),zSMA(2.5 seconds),zSMA(10 seconds),minX(10 seconds),maxX(10 seconds),minY(10 seconds),maxY(10 seconds),minZ(10 seconds),maxZ(10 seconds)" << endl;
	for (unsigned int i = 0; i < collectedTime.size(); i++) {
		string display;
		outputFile << collectedTime[i] << "," << doublesX[i] << "," << doublesY[i] << "," <<  doublesZ[i] << "," << smaXTwenty[i] << "," << smaXHund[i] << "," << smaYTwenty[i] << "," << smaYHund[i] << "," << smaZTwenty[i] << "," << smaZHund[i] << "," << valsMinHundredX[i] <<  "," << valsMaxHundredX[i] << "," << valsMinHundredY[i] << "," << valsMaxHundredY[i]  <<  "," << valsMinHundredZ[i] << "," << valsMaxHundredZ[i] <<endl;
	}
}


int main()
{
	for (int q = 0; q < NUM_FILES; q++) {
		readAndExtract(FILENAMES[q]);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
