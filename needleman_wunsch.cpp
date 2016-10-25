#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sstream>
using namespace std;

int similarity[28][28];

double calcPenalty(int i, int j, int len1, int len2, int normPenality);

void initialise_similarity_matrix()
{
	// creating a map 000 - 1, 001 -1 so on... 222 - 27
	int i,j,k;
	vector< vector<int> > mapCubeIdtoCoordinate;
	
	// making mapping start from 1 so 0th location is 999
	vector <int> temp;
	temp.push_back(999);
	mapCubeIdtoCoordinate.push_back(temp);
	
	for(i=0;i<=2;i++)
	{
		for(j=0;j<=2;j++)
		{
			for(k=0;k<=2;k++)
			{
				vector <int> temp;
				temp.push_back(k);
				temp.push_back(j);
				temp.push_back(i);
				mapCubeIdtoCoordinate.push_back(temp);			
			}
		}
	}
	
	//make a similarity matrix first	
	int pos_x_i, pos_x_j, pos_y_i, pos_y_j, pos_z_i, pos_z_j;
	
	for(i=1;i<=27;i++)
	{
		pos_x_i = mapCubeIdtoCoordinate[i][2];
		pos_y_i = mapCubeIdtoCoordinate[i][1];
		pos_z_i = mapCubeIdtoCoordinate[i][0];
		
		for(j=1;j<=27;j++)
		{
			pos_x_j = mapCubeIdtoCoordinate[j][2];
			pos_y_j = mapCubeIdtoCoordinate[j][1];
			pos_z_j = mapCubeIdtoCoordinate[j][0];
			
			double distSq = pow((pos_x_i - pos_x_j),2) + pow((pos_y_i - pos_y_j),2) + pow((pos_z_i - pos_z_j),2);
			
			similarity[i][j] = -distSq;
		}			
	}

	//Nvr used
	similarity[0][0] = 0;
	for(i=0;i<=27;i++)
	{
		similarity[i][0] = 0;
		similarity[0][i] = 0;
	}	
}

double JointSeqSimilarity(string str1,string str2)
{
	vector<int> cubeSeq1;
	vector<int> cubeSeq2;
	istringstream tokeniser1(str1);
	istringstream tokeniser2(str2);
	string token1;
	string token2;
		
	while(getline(tokeniser1, token1, ','))
	{
	  cubeSeq1.push_back(atoi(token1.c_str()));
	}
	while(getline(tokeniser2, token2, ','))
	{
	  cubeSeq2.push_back(atoi(token2.c_str()));
	}

	int len1, len2;
	len1 = cubeSeq1.size();
	len2 = cubeSeq2.size();

	double costMatrix[len1+1][len2+1];
	int i,j;
	
	int penalty = -1.7;
	for(i=0;i<=len1;i++)
	{
		costMatrix[i][0] = i*penalty;
	}
	for(j=0;j<=len2;j++)
	{
		costMatrix[0][j] = j*penalty;
	}
	for(i=1;i<=len1;i++)
	{
		int id1 = cubeSeq1[i-1];
		for(j=1;j<=len2;j++)
		{
			int id2 = cubeSeq2[j-1];
			double temp = max(costMatrix[i-1][j], costMatrix[i][j-1]) + calcPenalty(i,j,len1,len2,penalty-3);
			double temp2 = max( temp , costMatrix[i-1][j-1]+similarity[id1][id2]);
			costMatrix[i][j] = temp2;
		}
	}
	return costMatrix[len1][len2];  
}

double calcPenalty(int i, int j, int len1, int len2, int normPenality)
{
	if(i>len1/2)
	  i = len1 - i;
	if(j>len2/2)
	  j = len2 - j;
	
	return (4*(i)*(j)*normPenality)/(len1*len2);
}

double GestureSeqSimilarity(vector<string> gesture1, vector<string> gesture2)
{
	int i;
	double sumDist = 0;
	double GestureDist = 0;
	for(i=0;i<20;i++)
	{
		int maxLengthDist = 2 * max(gesture1[i].size(), gesture2[i].size());
		sumDist = sumDist + maxLengthDist;
		GestureDist = GestureDist + JointSeqSimilarity(gesture1[i], gesture2[i])  * maxLengthDist;
	}
	return GestureDist/sumDist*100;
}

int main()
{
	initialise_similarity_matrix();
	string str1, str2;
	cout << "Enter first string \n";
	cin >> str1;
	cout << "Enter second string \n";
	cin >> str2;
	
	cout << return_similarity(str1,str2);	
}
