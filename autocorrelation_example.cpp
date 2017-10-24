/* the code is NOT optimized, it is for debugging purposes

input file lew.dat
output file out.dat

it computes the autocorrelation values for real number signals
using Wiener–Khinchin theorem and GSL library

--->  lew.dat
This data set was collected by H. S. Lew of NIST in 1969 to measure steel-concrete beam deflections. The response variable is the deflection of a beam from the center point. 
response ---> reference.dat file

*/

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>
#include <iostream>
#include <fstream>
#include <gsl/gsl_statistics.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])


int
main (void)
{
    int i;
    double data[2 * 4000];
    double data1[2 * 4000];
    int NUM = 200;    //-----------------------number of values in the input file----------------

    for (i = 0; i < 4000; i++)
	{
	    REAL(data, i) = 0.0; IMAG(data, i) = 0.0;
	    REAL(data1, i) = 0.0; IMAG(data1, i) = 0.0;
	}

    gsl_fft_complex_wavetable * wavetable;
    gsl_fft_complex_workspace * workspace;

    wavetable = gsl_fft_complex_wavetable_alloc (2*NUM);
    workspace = gsl_fft_complex_workspace_alloc (2*NUM);

    std::ifstream myfile;
    myfile.open ("lew.dat");

    for (int m = 0; m < NUM; m++)
	{
	    myfile >> data[2 * m];
	}
    for (i = 0; i < NUM; i++)
	{
	    data1[i]=REAL(data, i); IMAG(data,i) = 0.0;
	}
    double mean= gsl_stats_mean(data1, 1 , NUM);

    double norm=0.0;
    for (i=0; i < NUM; i++)
	{
	    REAL(data,i)=REAL(data, i)-mean;
	    norm=norm+REAL(data,i)*REAL(data,i);
	}




    printf ("----------------------------begin data------------------------------\n");
    for (i = 0; i < NUM; i++)
	{
	    printf ("%d %e %e\n", i, REAL(data, i), IMAG(data, i));
	}
    printf ("\n");
    printf ("----------------------------end data------------------------------\n");

    gsl_fft_complex_forward (data, 1, 2*NUM, wavetable, workspace);

    for (i = 0; i < 2 * NUM; i++)
	{
	    printf ("%d %e %e\n", i, REAL(data, i), IMAG(data, i));
	}
    printf ("----------------------------end forward------------------------------\n");
//    gsl_fft_complex_inverse (data, 1, NUM, wavetable, workspace);
//
//    for (i = 0; i < NUM; i++)
//	{
//	    printf ("%d %e %e\n", i, REAL(data, i), IMAG(data, i));
//	}

//    printf ("----------------------------end backward------------------------------\n");

    printf ("-----------------------------CALCULATION-------------------------------\n");

    for (int j = 0; j < 2 * NUM; j++)
	{
	    REAL(data1, j) = REAL(data, j) * REAL(data, j) + IMAG(data,j) * IMAG(data, j);
	    IMAG(data1, j) = 0.0;
	}

    gsl_fft_complex_inverse (data1, 1, 2*NUM, wavetable, workspace);

    printf ("-----------------------------AUTOCORRELATION-------------------------------\n");

    for (i = 0; i < NUM; i++)
	{
	    printf ("%d %e %e\n", i, REAL(data1, i)/norm, IMAG(data1, i) / NUM);  // 0.01005025
	}
    std::ofstream myfileo;
       myfileo.open ("out.dat");

       for (int m = 0; m < NUM; m++)
   	{
   	    myfileo << data1[2 * m]/norm << std::endl;
   	}
    gsl_fft_complex_wavetable_free (wavetable);
    gsl_fft_complex_workspace_free (workspace);
    return 0;
}

