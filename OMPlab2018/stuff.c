int index1 = Index(1,1,1);
		for(z = 1; z < zMax - 1; z+= tile)
		{
			//double uIndex = u[index00z];
			for(y = 1; y < yMax - 1; y+= tile)
			{
				for(x = 1; x < xMax - 1; x+= tile)
				{
					for (int z1 = z; z1 < z + tile; z1++)
					{
						for (int y1 = y; y1 < y + tile; y1++)
						{
							for(int x1 = x; x1 < x + tile; x1++)
							{
								double uIndex = u[index1];
								double * t = &u[index1];
								g[index00z] = 1.0 / sqrt(epsilon + 
								SQR(uIndex - *(t+1)) + 
								SQR(uIndex - *(t-1)) + 
								SQR(uIndex - *(t + xMax)) + 
								SQR(uIndex - *(t - xMax)) + 
								SQR(uIndex - *(t + yx)) + 
								SQR(uIndex - *(t - yx)));
								index1++;
							}
							index1 -= 16;
							index1 += xMax;
						}
						index1 -= 16*xMax;
						index1 += yx;
					}
				}
			}
		}

int index1 = Index(1,1,1);
		for(z = 1; z < zMax - 1; z++)
		{
			//double uIndex = u[index00z];
			for(y = 1; y < yMax - 1; y++)
			{
				for(x = 1; x < xMax - 1; x +=3)
				{
					double uIndex1 = u[index1];

					double * t = &u[index1];
					g[index1] = 1.0 / sqrt(epsilon + 
						SQR(uIndex1 - *(t+1)) + 
						SQR(uIndex1 - *(t-1)) + 
						SQR(uIndex1 - *(t + xMax)) + 
						SQR(uIndex1 - *(t - xMax)) + 
						SQR(uIndex1 - *(t + yx)) + 
						SQR(uIndex1 - *(t - yx)));
					double uIndex2 = u[index1+1];
					g[index1+1] = 1.0 / sqrt(epsilon + 
						SQR(uIndex2 - *(t+2)) + 
						SQR(uIndex2 - *(t-2)) + 
						SQR(uIndex2 - *(t + 2*xMax)) + 
						SQR(uIndex2 - *(t - 2*xMax)) + 
						SQR(uIndex2 - *(t + 2*yx)) + 
						SQR(uIndex2 - *(t - 2*yx)));
					double uIndex3 = u[index1+1+1];
					g[index1+1+1] = 1.0 / sqrt(epsilon + 
						SQR(uIndex3 - *(t+3)) + 
						SQR(uIndex3 - *(t-3)) + 
						SQR(uIndex3 - *(t + 3*xMax)) + 
						SQR(uIndex3 - *(t - 3*xMax)) + 
						SQR(uIndex3 - *(t + 3*yx)) + 
						SQR(uIndex3 - *(t - 3*yx)));
					index1 +=3;
				}
				index1 -= 126;
				index1 += xMax;
			}
			index1 -= 126*xMax;
			index1 += yx;
		}