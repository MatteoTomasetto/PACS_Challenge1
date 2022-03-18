#include "cauchy_utilities.hpp"
#include <iostream>
#include <cmath>

/*
 * Implementation of the solver of the Cauchy problem {dy(t)/dt = f(t,y)
 *                                                    {y(t0)=u0   
*/

int solver_Cauchy(const std::function<double (const double &, const double &)> &f, const double &u0, const unsigned int &N, const double &t0, const double &T, std::vector<double> &t, std::vector<double> &u, const double &theta)
{

	t.push_back(t0);	// intial time
	u.push_back(u0);	// initial solution
	const double h = (T - t0) / static_cast<double>(N); // time step

	for(int i = 1; i < N; ++i)
	{

		t.push_back(t.at(i-1) + h); // new time instant

		// Non-linear function for Newton method
		auto F = [f,h,t,u,i,theta](const double &x)
		{
			return x - h * theta * f(t.at(i),x) - u.at(i-1) - h * (1 - theta) * f(t.at(i-1),u.at(i-1));
		};
        
		// Derivative of the non-linear function for Newton method approximated by centered finite differences       
		auto dF = [F,h](const double &x)
		{
		return (F(x+h) - F(x-h)) / (2. * h);
		};
		
		std::tuple<double, bool> res = Newton(F, dF, u.at(i-1)); // Newton method: it gives result and convergence status

		if(!std::get<1>(res))
		{
			std::cout << "Newton does not converge at time " << t.at(i) << std::endl;
			std::cout << "Solution found until time " << t.at(i) << std::endl;
			return 1; // exit if Newton does not converge
		}

		else{u.push_back(std::get<0>(res));}; // save the result if Newton reaches convergence 
	}

	return 0;
}



// Implementation of the Newton method
std::tuple<double, bool> Newton(const std::function<double (const double &)> &F, const std::function<double (const double &)> &dF, const double &init, const double &tol, const double &tola, const unsigned int &maxIt)
{
	double			sol(init); //solution of Newton method
	double			evalF = F(init);
	double			resid = std::abs(evalF);
	unsigned int	iter{0u}; // iteration number
	double			check = tol * resid + tola;
	bool			goOn = resid > check; // condition to go on with the iterations
	while(goOn && iter < maxIt)
	{
		++iter;
		sol += - evalF / dF(sol); // upgrade in Newton method
		evalF = F(sol);
		resid = std::abs(evalF);
		goOn = resid > check;
	}

	return std::make_tuple(sol, (iter < maxIt));
}

