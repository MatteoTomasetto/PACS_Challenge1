# Code to solve Cauchy problem #

This program computes the solution of the Cauchy problem dy(t)/dt = f(t,y) with initial condition y(t0)=u0 until final time T.
In particular it considers f(t,y) = -t*exp(-y).

** Note** This program makes use of the theta-method to approximate the time derivative. Moreover it exploits the Newton method for the solution of the arising non-linear equation at each time step (the derivative of the non-linear function in the Newton method is approximated by centered finite differences).

The following parameters are taken in input from command line thanks to GetPot:
	1) theta = parameter of the theta-method;
	2) N     = number of time steps;
	3) t0    = initial time;
	4) T     = final time;
	5) u0    = initial condition.

Example of execution: `./main N=150 theta=0.5 t0=0.0 T=1.0 u0=0.0`
By default: N = 100, theta = 1 (Backward Euler scheme), t0 = 0.0, T = 1.0, u0 = 0.0.

In this directory, `make` produces the executable which is just called `main`.

Calling ``./plot.sh`` you are able to visualize the result stored in `result.dat`.
