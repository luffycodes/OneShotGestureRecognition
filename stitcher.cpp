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
  
//   string str1, str2;
//   cout << "Enter first string \n";
//   cin >> str1;
//   cout << "Enter second string \n";
//   cin >> str2;
  
//   cout << GestureSeqSimilarity(str1,str2);	
//   string fileName1;
//   cout << "Enter the first file name\n";
//   cin >> fileName1;
//  string file_throw = "P1_1_8_p19";
//  string file_had_enough = "P1_1_9_p21";
  string allFiles = "gestureFileNames";
  ifstream allGesturesFile(allFiles.c_str());
  string fileName;
  
  while(getline(allGesturesFile,fileName))
  {
    //if(findGestureNo(fileName) == 8 || findGestureNo(fileName) == 9)
      cout << fileName << "\n";
      readData(fileName);
  }
  
//   readData(file_throw);
//   readData(file_had_enough);
  
  int gestureNoThrow = 8;//findGestureNo(file_throw);
  int gestureNoHadEnough = 9;//= findGestureNo(file_had_enough);
  
  int throwGestureSize = gesture[gestureNoThrow].size();
  int hadEnoughGestureSize = gesture[gestureNoHadEnough].size();
  
  int i,j;
  
  string temp;/* = "diff_8_9";
  ofstream diff_8_9(temp.c_str());
  
  temp = "same_8_8";
  ofstream same_8_8(temp.c_str());
  
  temp = "same_9_9";
  ofstream same_9_9(temp.c_str());
  
  temp = "gesture_9";
  ofstream gesture_9(temp.c_str());*/
  
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
      
  
//   for(i=1;i<throwGestureSize;i++)
//   {
//       for(j=1;j<hadEnoughGestureSize;j++)
//       {
// 	//cout << "Similarity between differents \n";
// 	//cout << gesture[gestureNoThrow][i][10] << " and " << gesture[gestureNoHadEnough][j][10] << "is \n";
// 	diff_8_9 << GestureSeqSimilarity(gesture[gestureNoThrow][i] , gesture[gestureNoHadEnough][j]) << "\n";
// 	//cout << "\n";
//       }      
//   }
  /*cout << "\n\n\n Now for same";
  cout << throwGestureSize << " " << hadEnoughGestureSize << "\n";
  
  for(i=1;i<throwGestureSize;i++)
  {
      for(j=i+1;j<throwGestureSize;j++)
      {
	//cout << "Similarity between Same's\n";
	//cout << gesture[gestureNoThrow][i][10] << " and " << gesture[gestureNoThrow][j][10] << "is \n";
	same_8_8 << GestureSeqSimilarity(gesture[gestureNoThrow][i] , gesture[gestureNoThrow][j])<< "\n";
	//cout << "\n";
      }
  }
  cout << "\n\n\n Now for same";
  
  for(i=1;i<hadEnoughGestureSize;i++)
  {
      for(j=i+1;j<hadEnoughGestureSize;j++)
      {
	//cout << "Similarity between Same's\n";
	//cout << gesture[gestureNoHadEnough][i][10] << " and " << gesture[gestureNoHadEnough][j][10] << "is \n";
	same_9_9 << GestureSeqSimilarity(gesture[gestureNoHadEnough][i] , gesture[gestureNoHadEnough][j])<< " ";
	//cout << "\n";
      }
  }*/  
  
  /*for(int i =0; i <gesture[9].size();i++)
  {
    gesture_9 << "---------------------------------------------------------------------------\n";
    gesture_9 << "\nGesture No. " << i << "\n";
    for(int j =0; j<20;j++)
    {
      gesture_9 << "Joint ID:" << j << "\tCube Sequence ->" << gesture[9][i][j] << "\n";      
    }    
  } */ 
  
  return 0;
}