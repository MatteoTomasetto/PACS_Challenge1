#ifndef HH__Cauchy_Utilities__HH
#define HH__Cauchy_Utilities__HH
#include <vector>
#include <tuple>
#include <functional>

/*!
 * solver_Cauchy --> computes the solution of the Cauchy problem {dy(t)/dt = f(t,y) until time T
 *                                                               {y(t0)=u0    
 * It approximates the time derivative with theta-method and solve the arising non-linear
 * equation with Newton method (the derivative of the non-linear function in the Newton method is approximated by 
 * centered finite differences).
 *
 * @param f RHS in the Cauchy problem
 * @param u0 initial solution
 * @param N number of time steps
 * @param T final time 
 * @param t0 initial time
 * @param t vector of time instants
 * @param u vector of the solution for each time step;
 * @param theta is the choice of the theta-method to use (backward Euler by default)
 * @return status (0 if it works)
 *
 */
int solver_Cauchy(const std::function<double (const double &, const double &)> &f, const double &u0, const unsigned int &N, const double &t0, const double &T,  std::vector<double> &t, std::vector<double> &u, const double &theta = 1.0);


/*!
 * Newton --> computes the zero of a scalar function with the Newton method.
 * It stops when |f(solution)| <= tol*|f(init)| + tola
 *
 * @param F non-linear function for which we want the zero
 * @param dF derivative of F (it could be also an approximation of the derivative, e.g. finite differences formula)
 * @param init initialization
 * @param tol relative tolerance
 * @param tola absolute tolerance
 * @param maxIt maximum number of iterations
 * @return The approximation of the zero of F and a status (false if not converging)
 *
 */
std::tuple<double, bool> Newton(const std::function<double (const double &)> &F, const std::function<double (const double &)> &dF, const double &init, const double &tol = 1e-4, const double &tola = 1.e-8, const unsigned int &maxIt = 200);

 
#endif
