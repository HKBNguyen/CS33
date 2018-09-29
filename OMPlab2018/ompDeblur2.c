//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name :
 * UCLA ID: 
 * Email id:
 */

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int OMP_xMax;
#define xMax OMP_xMax
int OMP_yMax;
#define yMax OMP_yMax
int OMP_zMax;
#define zMax OMP_zMax

int OMP_Index(int x, int y, int z)
{
	return ((z * yMax + y) * xMax + x);
}
#define Index(x, y, z) OMP_Index(x, y, z)

double OMP_SQR(double x)
{
	return pow(x, 2.0);
}
#define SQR(x) OMP_SQR(x)

double* OMP_conv;
double* OMP_g;

void OMP_Initialize(int xM, int yM, int zM)
{
	xMax = xM;
	yMax = yM;
	zMax = zM;
	assert(OMP_conv = (double*)malloc(sizeof(double) * xMax * yMax * zMax));
	assert(OMP_g = (double*)malloc(sizeof(double) * xMax * yMax * zMax));
}
void OMP_Finish()
{
	free(OMP_conv);
	free(OMP_g);
}
void OMP_GaussianBlur(double *u, double Ksigma, int stepCount)
{
	double lambda = (Ksigma * Ksigma) / (double)(stepCount + stepCount);
	double nu = (1.0 + lambda + lambda) - sqrt(1.0 + (lambda + lambda + lambda + lambda))/(lambda + lambda);
	int x, y, z, step;
	int yx = 16384;
	double boundryScale = 1.0 / (1.0 - nu);
	double postScale = pow(nu / lambda, (double)(stepCount + stepCount + stepCount));
	for(step = 0; step < stepCount; step++)
	{
		int index0 = Index(0,0,0);
		//#pragma omp parallel for private(y)
		for(z = 0; z < zMax; z++)
		{
		//	int index0 = Index(0,0,z);
		//	#pragma omp private(index0)
			for(y = 0; y < yMax; y++)
			{
				u[index0] *= boundryScale;
				index0 += xMax;
			}
			index0 -= 128*xMax;
			index0 += yx;
		}
		
		int index1 = Index(1,0,0);
		//#pragma omp parallel private(index1) 
		//#pragma omp parallel for private(y,x)
		for(z = 0; z < zMax; z++)
		{
		//	int index1 = Index(1,0,z);
		//	#pragma omp private(index1)
			//int index1 = Index(1,0,z);
		//	#pragma omp for nowait
			for(y = 0; y < yMax; y++)
			{
		//		#pragma omp nowait
				for( x = 1; x < xMax; x++)
				{
					u[index1] += u[index1 -1] * nu;
					++index1;
				}
				index1 -= 127;
				index1 += xMax;
			}
			index1 -= 128*xMax;
			index1 += yx;
		}
		int index2 = Index(0,0,0);
	//	#pragma omp parallel for private(y) 
		for(z = 0; z < zMax; z++)
		{
	//		int index2 = Index(0,0,z);
		//	#pragma omp for nowait
	//		#pragma omp private(index2)
			for(y = 0; y < yMax; y++)
			{
				u[index2] *= boundryScale;
				index2 += xMax;
			}
			index2 -= 128*xMax;
			index2 += yx;
		}

		int index3 = Index(126,0,0);
		//#pragma omp parallel private(index)
		//#pragma omp parallel for private(y,x)
		//int index1 = Index(126,0,0);
		for(z= 0; z< zMax; z++)
		{
		//	int index1 = Index(126,0,z);
		//	#pragma omp private(index1)
			for(y = 0; y < yMax; y++)
			{
				for(x = xMax -2; x >= 0; x--)
				{
					
					u[index3] += u[index3+1] * nu;
					--index3;
				}
				index3 += 127;
				index3 += xMax;
			}
			index3 -= 128*xMax;
			index3 += yx;
		}

		int index4 = Index(0,0,0);
		//#pragma omp parallel for private(y,x)
		for(z = 0; z < zMax; z++)
		{
		//	int index4 = Index(0,0,z);
		//	#pragma omp private(index4)
			for(y = 0; y < yMax; y++)
			{
			
				for(x = 0; x < xMax; x++)
				{
					u[index4] *= boundryScale;
					++index4;
				}
				index4 -= 128;
				index4 += xMax;
			}
			index4 -= 128*xMax;
			index4 += yx;
		}

		int index5 = Index(0,1,0);
	//	#pragma omp parallel for private(y,x)
		for(z = 0; z < zMax; z++)
		{
	//		int index5 = Index(0,1,z);
	//		#pragma omp private(index5)
			for(y = 1; y < yMax; y++)
			{
		//		#pragma omp nowait
				for(x = 0; x < xMax; x++)
				{
					u[index5] += u[index5 - xMax] * nu;
					++index5;
				}
				index5 -= 128;
				index5 += xMax;
			}
			index5 -= 127*xMax;
			index5 += yx;
		}

		int index6 = Index(0,127,0);
		//#pragma omp parallel private(index6)
	//	#pragma omp parallel for private(x)
		for(z = 0; z < zMax; z++)
		{
	//		int index6 = Index(0,127,z);
	//		#pragma omp private(index6)

			for(x = 0; x < xMax; x++)
			{
				u[index6] *= boundryScale;
				++index6;
			}
			index6 -= 128;
			index6 += yx;
		}

		int index7 = Index(0,126,0);
	//	#pragma omp parallel for private(y,x)
		//int index2 = Index(0,126,0);
		for(z = 0; z < zMax; z++)
		{
		//	int index7 = Index(0,126,z);
		//	#pragma omp private(index2)
			for(y = yMax - 2; y >= 0; y--)
			{
				for(x = 0; x < xMax; x++)
				{
					
					u[index7] += u[index7 + xMax] * nu;
					++index7;
				}
				index7 -= 128;
				index7 -= xMax;
			}
			index7 += 127*xMax;
			index7 += yx;
		}

		int index8 = Index(0,0,0);
	//	#pragma omp parallel for private(x)
		for(y = 0; y < yMax; y++)
		{
	//		int index8 = Index(0,y,0);
	//		#pragma omp private(index8)
			for(x = 0; x < xMax; x++)
			{
				u[index8] *= boundryScale;
				++index8;
			}
			index8 -= 128;
			index8 += xMax;
		}

		int index9 = Index(0,0,1);
		//#pragma omp parallel for private(y,x)
		for(z = 1; z < zMax; z++)
		{
	//		int index9 = Index(0,0,z);
	//		#pragma omp private(index9)
			for(y = 0; y < yMax; y++)
			{
		//		#pragma omp nowait
				for(x = 0; x < xMax; x++)
				{
					
					u[index9] = u[index9 - yx] * nu;
					++index9;
				}
				index9 -= 128;
				index9 += xMax;
			}
			index9 -= 128*xMax;
			index9 += yx;
		}

		int index10 = Index(0,0,127);
	//	#pragma omp parallel for private(x)
		for(y = 0; y < yMax; y++)
		{
	//		int index10 = Index(0,y,127);
	//		#pragma omp private(index10)
			for(x = 0;  x< xMax; x++)
			{
				u[index10] *= boundryScale;
				++index10;
			}
			index10 -= 128;
			index10 += xMax;
		}

		int index11 = Index(0,0,126);
	//	#pragma omp parallel for private(y,x)
	//	int index11 = Index(0,0,126);
		for(z = zMax - 2; z >= 0; z--)
		{
	//		int index11 = Index(0,0,z);
	//		#pragma omp private(index11)
			for(y = 0; y < yMax; y++)
			{
				for(x = 0; x < xMax; x++)
				{
					u[index11] += u[index11 + xMax*yMax] * nu;
					++index11;
				}
				index11 -= 128;
				index11 += xMax;
			}
			index11 -= 128*xMax;
			index11 -= yx;
		}
	//}
}
	int index12 = Index(0,0,0);
	//#pragma omp parallel for private(y,x)
	for(z = 0; z < zMax; z++)
	{
	//		int index12 = Index(0,0,z);
	//	#pragma omp for nowait
	//		#pragma omp private(index12)
		for(y = 0; y < yMax; y++)
		{
	//		#pragma omp nowait
			for(x = 0; x < xMax; x++)
			{
				u[index12] *= postScale;
				++index12;
			}
			index12 -= 128;
			index12 += xMax;
		}
		index12 -= 128*xMax;
		index12 += yx;
	}

}
void OMP_Deblur(double* u, const double* f, int maxIterations, double dt, double gamma, double sigma, double Ksigma)
{
	double epsilon = 1.0e-7;
	double sigma2 = SQR(sigma);
	int x, y, z, iteration;
	int x1, y1, z1;
	int converged = 0;
	int lastConverged = 0;
	int fullyConverged = 2048383;
	double* conv = OMP_conv;
	double* g = OMP_g;
	int yx = 16384;
	int tile = 16;
	//#pragma omp parallel for shared(lastConverged)
	for(iteration = 0; iteration < maxIterations && converged != fullyConverged; iteration++)
	{
		int index1 = Index(1,1,1);
		for(z = 1; z < zMax - 1; z++)
		{
			//double uIndex = u[index00z];
			for(y = 1; y < yMax - 1; y++)
			{
				for(x = 1; x < xMax - 1; x +=3)
				{
					double uIndex1 = u[index1];

				//	double * t = &u[index1];
					g[index1] = 1.0 / sqrt(epsilon + 
						SQR(uIndex1 - u[index1+1]) + 
						SQR(uIndex1 -  u[index1 -1])+ 
						SQR(uIndex1 - u[index1 + xMax]) + 
						SQR(uIndex1 - u[index1 - xMax]) + 
						SQR(uIndex1 - u[index1 + yx]) + 
						SQR(uIndex1 - u[index1 - yx]));
					double uIndex2 = u[index1+1];
					g[index1+1] = 1.0 / sqrt(epsilon + 
						SQR(uIndex2 - u[index1 + 1 + 1]) + 
						SQR(uIndex2 - u[index1 + 1 -1]) + 
						SQR(uIndex2 - u[index1 + 1 + xMax]) + 
						SQR(uIndex2 - u[index1 + 1 - xMax]) + 
						SQR(uIndex2 - u[index1 + 1 + yx]) + 
						SQR(uIndex2 - u[index1 +1 - yx]));
					double uIndex3 = u[index1+1+1];
					g[index1+1+1] = 1.0 / sqrt(epsilon + 
						SQR(uIndex3 - u[index1 + 1 + 1 + 1]) + 
						SQR(uIndex3 - u[index1 + 1 -1 + 1]) + 
						SQR(uIndex3 - u[index1 + 1 + 1+ xMax]) + 
						SQR(uIndex3 - u[index1 + 1 - xMax + 1]) + 
						SQR(uIndex3 - u[index1 + 1 + yx + 1]) + 
						SQR(uIndex3 - u[index1 +1 - yx + 1]));
					/*double uIndex4 = u[index1+1+1+1];
					g[index1+1+1+1] = 1.0 / sqrt(epsilon + 
						SQR(uIndex4 - *(t+4)) + 
						SQR(uIndex4 - *(t-4)) + 
						SQR(uIndex4 - *(t + 4*xMax)) + 
						SQR(uIndex4 - *(t - 4*xMax)) + 
						SQR(uIndex4 - *(t + 4*yx)) + 
						SQR(uIndex4 - *(t - 4*yx)));
					double uIndex5 = u[index1+1+1+1+1];
					g[index1+1+1+1+1] = 1.0 / sqrt(epsilon + 
						SQR(uIndex5 - *(t+5)) + 
						SQR(uIndex5 - *(t-5)) + 
						SQR(uIndex5 - *(t + 5*xMax)) + 
						SQR(uIndex5 - *(t - 5*xMax)) + 
						SQR(uIndex5 - *(t + 5*yx)) + 
						SQR(uIndex5 - *(t - 5*yx)));*/

					index1 +=3;
				}
				index1 -= 126;
				index1 += xMax;
			}
			index1 -= 126*xMax;
			index1 += yx;
		}
		memcpy(conv, u, sizeof(double) * 2097152);
		OMP_GaussianBlur(conv, Ksigma, 3);
		int index2 = Index(0,0,0);
		for(z = 0; z < zMax; z++)
		{
			for(y = 0; y < yMax; y++)
			{
				for(x = 0; x < xMax; x++)
				{
					//int index = Index(x,y,z);
					double convI = conv[index2];
					double fI = f[index2];
					double r = convI * fI / sigma2;
					r = (r * (2.38944 + r * (0.950037 + r))) / (4.65314 + r * (2.57541 + r * (1.48937 + r)));
					conv[index2] -= fI * r;
					index2++;
				}
				index2 -= 128;
				index2 += xMax;
			}
			index2 -= 128*xMax;
			index2 += yx;
		}
		OMP_GaussianBlur(conv, Ksigma, 3);
		converged = 0;
		int index3 = Index(1,1,1);
		for(z = 1; z < zMax - 1; z++)
		{
			for(y = 1; y < yMax - 1; y++)
			{
				for(x = 1; x < xMax - 1; x++)
				{
					double uIndex = u[index3];
					double oldVal = uIndex;
					double newVal = (uIndex + dt * ( 
						u[index3-1] * g[index3-1] + 
						u[index3+1] * g[index3+1] + 
						u[index3 - xMax] * g[index3 - xMax] + 
						u[index3 + xMax] * g[index3 + xMax] + 
						u[index3 - yx] * g[index3 - yx] + 
						u[index3 + yx] * g[index3 + yx] - gamma * conv[index3])) /
						(1.0 + dt * (g[index3+1] + g[index3-1] + g[index3 + xMax] + g[index3 - xMax] + g[index3 + yx] + g[index3 - yx]));
					if(fabs(oldVal - newVal) < epsilon)
					{
						converged++;
					}
					u[index3] = newVal;
					index3++;
				}
				index3 -= 126;
				index3 += xMax;
			}
			index3 -= 126*xMax;
			index3 += yx;
		}
		if(converged > lastConverged)
		{
			printf("%d pixels have converged on iteration %d\n", converged, iteration);
			lastConverged = converged;
		}
	}
}

