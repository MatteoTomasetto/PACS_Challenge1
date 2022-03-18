/*!
 * This program computes the solution of the Cauchy problem {dy(t)/dt = f(t,y)
 *                                                          {y(t0)=u0
 *
 * myfun --> RHS of the Cauchy problem f(t,y);
 *
 * N  --> number of time steps;
 * t0 --> initial time;
 * T  --> final time;
 * u0 --> initial solution;
 * u  --> vector of the solution for each time step;
 * t  --> vector of the corresponding time instants;
 * theta --> parameter of the theta-method to approxiamte the time derivative in the Cauchy problem;
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "GetPot"
#include "cauchy_utilities.hpp"


// RHS of the Cauchy problem
double myfun(const double &t, const double &y)
{
	return -t * std::exp(-y);
}


// Exact solution of the problem
double exact_solution(const double &t, const double &t0, const double &u0)
{
	return std::log(std::exp(u0) + t0*t0/2. - t*t/2.);
}


int main(int argc, char **argv)
{

	GetPot cl(argc, argv);

	// Import the following constant parameters from command line
	const unsigned int 	N = cl("N", 100);
	const double 		theta = cl("theta", 1);
	const double 		u0 = cl("u0", 0.0);
	const double 		t0 = cl("t0", 0.0);
	const double 		T = cl("T", 1.0);

	// Check if theta is out of range
	if(theta < 0.0 || theta > 1.0)
	{
		std::cerr << "ERROR: theta out of range" << std::endl;
		return 1;
	}

	// Check if t0 is greater or equal than T
	if(t0 >= T)
	{
		std::cerr << "ERROR: t0 >= T" << std::endl;
		return 1;
	}

	// Vectors for the solution
	std::vector<double> u;
	std::vector<double> t;
	std::vector<double> u_ex;

	// Reserve space to avoid reallocations
	u.reserve(N);
	t.reserve(N);
	u_ex.reserve(N);

	// Solve the problem
	int check = solver_Cauchy(myfun, u0, N, t0, T, t, u, theta);

	// Compute the exact solution in the time instants
	for (int i = 0; i < t.size(); ++i)
	{
		u_ex.push_back(exact_solution(t[i], t0, u0));
	}

	// Save the results in a file called "result.dat"
	if(check == 0)
	{
		std::cout << "Solution found!" << std::endl;
		std::cout << "Saving the solution in result.dat" << std::endl;
	}

	else
	{
		std::cout << "Saving the solution in result.dat until divergent step" << std::endl;
	}

	std::ofstream file("result.dat");

	file << "#time instant\tcomputed solution\texact solution" << std::endl;

	for(int i = 0; i < t.size(); ++i)
	{
		file.setf(std::ios::left, std::ios::adjustfield);
		file.width(16);
		file << t[i] << "\t\t" << u[i] << "\t\t" << u_ex[i] << "\n";
	}

	file.close();

	return 0;

}
