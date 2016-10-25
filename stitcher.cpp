#include "readData.cpp"
#include <iostream>
#include <string>
#include <vector>
#include "needleman.cpp"
#include <fstream>
#include <sstream>
using namespace std;

vector< vector<string> > gesture[13];

int main()
{
  initialise_similarity_matrix();
  string allFiles = "gestureFileNames";
  ifstream allGesturesFile(allFiles.c_str());
  string fileName;
  
  while(getline(allGesturesFile,fileName))
  {
      cout << fileName << "\n";
      readData(fileName);
  }
  
  int gestureNoThrow = 8;//findGestureNo(file_throw);
  int gestureNoHadEnough = 9;//= findGestureNo(file_had_enough);
  
  int throwGestureSize = gesture[gestureNoThrow].size();
  int hadEnoughGestureSize = gesture[gestureNoHadEnough].size();
  
  int i,j;
  
  string temp;
  
  for(i=1;i<=12;i++)
  {  
    ostringstream ssi;
    ssi << i;
    string tempI = ssi.str();
    
    for(j=i;j<=12;j++)
    {      
      stringstream ssj;
      ssj << j;
      string tempJ = ssj.str();
      
      if(i==j)
      	temp = "same"+ tempI +tempJ;
      else
	temp = "diff"+ tempI + tempJ;      	  

      ofstream tempFile(temp.c_str());
      cout << temp <<"\n";
      
      for(int p=1;p<gesture[i].size();p++)
      {
	  for(int q=1;q<gesture[j].size();q++)
	  {   
	    tempFile << GestureSeqSimilarity(gesture[i][p] , gesture[j][q]) << "\n";    
	  }      
      }
    }
  }
  
  return 0;
}
