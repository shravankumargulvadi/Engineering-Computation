// 24-780 Engineering Computation Assignment 2 - Part 2
// ps02_collision_sgulvadi.cpp : Program to solve different iterations of two ball collision problem, written by Shravan Kumar Gulvadi.
// Date:09/12/2022

#include <iostream>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include<time.h>
#include <map>

using namespace std;

class collision_problem
{ //class initializes all the parameters of the problem and houses methods needed to solve the problem
public:
	//nomenclature followed is same as given in the assignment handout
	float massA, massB, velA1, velB1, velA1_x, velA1_y, velB1_x, velB1_y, thetaA1, thetaB1, coeff_res;
	float velA2,velB2, velA2_x, velA2_y, velB2_x, velB2_y,correctness_threshold = 5;
	//correctness_threshold is the max %ge of error tolerated in the user's answer before declaring it 
	//to be incorrect, rightnow it is set at 5% and can be modified if required
	
	collision_problem()
	{
		//initialize problem parameters
		 srand(time(0));// use current time as random seed
		 //for massA and massB, range 0.5-4 kgs, rand()%36 returns numbers from 0-35 
		 //we divide this by 10 same logic is followed for all random initializations
		 massA = 0.5+(rand() % 36)/10.0;
		 massB = 0.5 + (rand() % 36) / 10.0;
		 //for thetaA1 and thetaB1 , range -60 to 60 degrees,
		 thetaA1 = -60 + (rand() % 121);
		 thetaB1 = -60 + (rand() % 121);
		 //for  velA1 and velB1 , range 0 to 5 m/s,
		 velA1 = (rand() % 51) / 10.0;
		 velB1 =  -(rand() % 51) / 10.0;
		 //coefficient of restitution varies from 0.6-0.9
		 coeff_res = 0.6 + (rand() % 31) / 100.0;
		 

		 //get pi, cos(pi/2)=0, hence:
		 double pi = 2 * acos(0.0);
		 //get x and y components of velocities
		 velA1_x = velA1 * cos(thetaA1*pi/180);
		 velA1_y = velA1 * sin(thetaA1*pi/180);
		 velB1_x = velB1 * cos(thetaB1*pi/180);
		 velB1_y = velB1 * sin(thetaB1*pi/180);
		 

		 cout << "Data: " << endl;

		 // print data
		 cout << "massA (kg) =" << massA << endl;
		 cout << "massB (kg) =" << massB << endl;
		 cout << "thetaA1 (deg) =" << thetaA1 <<endl;
		 cout << "thetaB1 (deg) =" << thetaB1 << endl;
		 cout << "velA1 (m/s) =" << velA1 << endl;
		 cout << "velB1 (m/s) =" << velB1 << endl;
		 cout << "coeff_res (coefficient of restitution) =" << coeff_res << endl;


	}
	void conserve_momentum()
		//from law of conservation of momentum we have massA*velA2_x+massB*velB2_x=massA*velA2_x+massB*velB2_x
		//since RHS is known we represent it by m_1
		// from equation for coefficient of restitution we have velB2_x-velA2_x=coeff_restitution*(velA1_x-velB1_x)
		//since RHS is known we represent it by m_2
	{	// method used to solve the equations: we construct matrix equations A*x=B where A is 2x2 matrix,
		// x is 2x1 matrix of unknowns and B is 2x1 matrix containing m_1 and m_2
		// we calculate x as x=inv(A)*B

		cout << endl << "solution:" << endl;
		float m_1 = massA * velA1_x + massB * velB1_x;
		float m_2 = (velA1_x - velB1_x) * coeff_res;
		velA2_x = 1 / (massA + massB)*(m_1 - m_2 * massB);
		velB2_x = 1 / (massA + massB) * (m_1 + massA * m_2);
		velA2_y = velA1_y;
		velB2_y = velB1_y;
		cout << "velA2_x=" << velA2_x<<std::endl;
		cout << "velA2_y=" << velA2_y<<endl;
		cout << "velB2_x=" << velB2_x << endl;
		cout << "velB2_y=" << velB2_y << endl;


	}
	bool check_correctness(float v_ax_check,float v_bx_check,float v_ay_check,float v_by_check)
	{
		conserve_momentum(); // construct and solve the equations 
		bool correctness=false;
		//calculate the error in user calculated values
		float error_1 = abs((v_ax_check - velA2_x)) / velA2_x * 100, error_2 = abs((v_ay_check - velA2_y)) / velA2_y * 100;
		float error_3 = abs((v_bx_check - velB2_x))/ velB2_x*100, error_4 = abs((v_by_check - velB2_y))/ velB2_y*100;


		// if all errors are within the correctness threshold the answers are considered acceptable other wise the error is printed out
		if (error_1 < correctness_threshold && error_2 < correctness_threshold && error_3 < correctness_threshold && error_4 < correctness_threshold)
		{
			correctness = true;
			cout << endl<< "The given answer is correct!!" << endl;
		}
		else
		{
			cout << endl << "The given answer is incorrect!!" << endl;
			cout << "Error in velA2_x=" << error_1 <<"%"<< endl;
			cout << "Error in velA2_y=" << error_2 << "%" << endl;
			cout << "Error in velB2_x=" << error_3 << "%" << endl;
			cout << "Error in velB2_y=" << error_4 << "%" << endl;

		}
		return correctness;

	}


};
int main()
{
	float velA2_x_check, velB2_x_check, velA_y_check, velB_y_check;
	collision_problem col;
	//request the user for answers and save them

	cout <<endl<< "Enter your calculated values of the 4 velocity components:"<<endl;

	cout << "velA2_x=";
	cin >> velA2_x_check;

	cout << "velA2_y=";
	cin >> velA_y_check;

	cout << "velB2_x=";
	cin >> velB2_x_check;

	cout << "velB2_y=";
	cin >> velB_y_check;

	// verify the correctness of answers
	bool correctness=col.check_correctness(velA2_x_check, velB2_x_check, velA_y_check, velB_y_check);


	return 0;

}