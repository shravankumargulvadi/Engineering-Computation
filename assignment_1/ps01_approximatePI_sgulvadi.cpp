// ps01_approximatePI_sgulvadi.cpp : Program to find an approximate value of PI, written by Shravan Kumar Gulvadi.
//

#include <iostream>
#include <cmath>
#include <math.h>


class pi_predict
{ // This class has two implementations for estimating the value of Pi. The first implementation has a nested for loop and can get slower for lower mesh sizes.
 // The second has a single for loop and runs faster than the loopy implementation
public:
    double pi_calculate_loopy(double mesh_size)
    {
        double area = 0;
        
        for (double height = 0; height < 1; height += mesh_size) //iterate through height
        {
            
            for (double width = 0; width < 1; width += mesh_size)// iterate through width
            {
                if (sqrt(pow(width, 2) + pow(height, 2)) > 1) // check if the mesh is outside the circle
                {
                    break;

                }
                area += mesh_size * mesh_size; //add the mesh area

            }
        }
        return area * 4;// total area = 4 x area of quater circle 
    }
    double pi_calculate(double mesh_size)
    {
        double area = 0;
        for (double height = 0; height < 1; height += mesh_size)  //iterate through height
        {
          
            double width = sqrt(1 - pow(height, 2)); //directly calculate the width from distance formula
            double residual = fmod(width, mesh_size); //subtract residual area left out after subtracting 
            width = width - residual; //subtract residual to get the exact width covered by the mesh
            area += width * mesh_size;
        }
        return area*4;// total area = 4 x area of quater circle 
    }

};

int main()
{

    pi_predict pi_cal;
    double pi_true_val = 3.1415926535;
    double pi_est1 = pi_cal.pi_calculate(0.001);
    double pi_est2 = pi_cal.pi_calculate(0.0001);
    double pi_est3 = pi_cal.pi_calculate(0.00001);
    double error_1 = ((pi_true_val - pi_est1) / pi_true_val) * 100;
    double error_2 = ((pi_true_val - pi_est2) / pi_true_val) * 100;
    double error_3 = ((pi_true_val - pi_est3) / pi_true_val) * 100;
    std::cout<<"Pi estimate for mesh size 0.001: "<<pi_est1 <<std::endl<< "error with mesh size 0.001: " << error_1 << "%" << std::endl;
    std::cout << "Pi estimate for mesh size 0.0001: " << pi_est2 <<std::endl<< "error with mesh size 0.0001: " << error_2 <<"%" << std::endl;
    std::cout << "Pi estimate for mesh size 0.00001: " << pi_est3 <<std::endl<< "error with mesh size 0.00001: " << error_3 <<"%" << std::endl;

    return 0;


};
