
// 24-780 Engineering Computation Assignment 2 - Part 1
// ps02_dice_sgulvadi.cpp : Program to model Monte Carlo simulation of two dice, written by Shravan Kumar Gulvadi.
// Date:09/12/2022
#include <iostream>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <map>
#include<iomanip>

using namespace std;


// function to model the action of a dice being thrown 
int roll_dice()
{
	int num = rand()%7;// restric the random number to be within 0-6
	if (num == 0) // since 0 is invalid rethrow the dice
	{
		num = roll_dice();
	}
	return num;
}
void visualize(int count,int num)
{
	cout <<std::setfill('0')<<std::setw(2)<< count << " " << ":"; //Print the corresponding number before drawing the histogram 

	for (int i = 0; i < num; i++)
	{
		cout << "*"; // repeatedly print asterisk to make the histogram
	}
	cout << endl;
}


int main()
{

	// make a map to collect the number of times we get each value after adding 
	//the two resultant values from the dice throws
	map<int, int> counts;
	int  count;
	int num_sim;//number of simulations
	cout << "Enter the number of Monte Carlo Simulation to run: ";
	cin >> num_sim;
	for (int i = 2; i <= 12; i++)
	{//initialize all counts to zero
		counts[i] = 0;
	}

	for (int i = 0; i < num_sim; i++)
	{
		count = roll_dice() + roll_dice(); //throw dice successively
		counts[count] += 1;//increment count
	}
	cout << "Each '*' represents 1%"<<endl;
	for (int i = 2; i <= 12; i++)
	{
		//calculate the percentage of each value to the total number of simulations
		int percentage = (float(counts[i]) / float(num_sim)) * 100; 
		//visualize results
		visualize(i, percentage);
	}
	return 0;


}