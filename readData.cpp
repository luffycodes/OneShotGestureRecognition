/* For reading a single file given by fileId*/
#include "readData.h"

vector <int> endFrameOfGesture;
vector <string> endTimeGesture;
vector <double> approxEndTimeGesture;
vector <double> difference;
string fileId;// = "P1_1_9_p21";//"P1_1_8_p19";

void readData(string fileName)
{  
  fileId = fileName;
  
  endFrameOfGesture.erase(endFrameOfGesture.begin(),endFrameOfGesture.end());
  endTimeGesture.erase(endTimeGesture.begin(),endTimeGesture.end());
  approxEndTimeGesture.erase(approxEndTimeGesture.begin(),approxEndTimeGesture.end());
  difference.erase(difference.begin(),difference.end());
  
  approxEndTimeGestureCalc(fileId);
  endTimeGestureCalc(fileId);
  readEachGestureInFile();  
}

void readEachGestureInFile()
{
  string path = "/media/20FCDB6EFCDB3D2A/Users/shashcs/Desktop/KINECT BTP/MicrosoftGestureDataset/MicrosoftGestureDataset-RC/data/";
  string fileName = path + fileId + ".csv";
  int gestureID = findGestureNo(fileId);
  ifstream infile(fileName.c_str());
  
  string frameString;
  vector <vector<double> >allGestures;
  joint origin(0,0,0);
  joint head(0,0,0);
  joint foot_right(0,0,0);
    
  int i = 0, counter = 0;
  while(getline(infile,frameString))
  {
    string coordinate = "";
    vector <double> frame;
    for(i=0;i<frameString.length();i++)
    {
      if(frameString.at(i)!=' ')
	coordinate = coordinate + frameString.at(i);
      else
      {	
	frame.push_back(atof(coordinate.c_str()));
	coordinate = "";
      }
    }
    if(frame[4] == 1)
    {
      if(counter == 0)
      {
	for(int i = 0;i<=2;i++)
	{
	  origin.dimesion_xyz[i] = frame[9+i]; //origin is taken to be SHOULDER_CENTER
	  head.dimesion_xyz[i] = frame[13+i];
	  foot_right.dimesion_xyz[i] = frame[77+i];
	}
      }
      else
      {
	// Do weighted mean..
	for(int i = 0;i<=2;i++)
	{
	  origin.dimesion_xyz[i] = (origin.dimesion_xyz[i]*counter +frame[9+i])/(counter+1);
	  head.dimesion_xyz[i] = (head.dimesion_xyz[i]*counter +frame[13+i])/(counter+1);
	  foot_right.dimesion_xyz[i] = (foot_right.dimesion_xyz[i]*counter +frame[77+i])/(counter+1);	
	}
	//cout << dist(head, foot_right) << ",";
      }
      counter ++;
    }
    allGestures.push_back(frame);
  }
  double height = dist(head, foot_right);
  cout << height << "\n";
  cout << allGestures.size() << "\n";
  
  cubeTrajectory(allGestures, origin, height, gestureID);
  //cubeTrajectory(allGestures, origin, height, GestureNo);
}

//extern vector< string[20] > gesture[12];
void cubeTrajectory(vector <vector<double> >allGestures, joint origin, double height, int gestureNo)
{ 
  int frameCounter = 0;
  for(int i =0; i <endFrameOfGesture.size();i++)
  {
    //frameCounter =0;
    vector<string> jointInCubes;
    for(int j=0;j<20;j++)
    {
      jointInCubes.push_back("");
    }
    while(frameCounter!=endFrameOfGesture[i]+1)
    {
      vector<double> frame;
      frame = allGestures[frameCounter];
      if(frame[4] == 1)
      {
	int jointID = 0;
	int framePosX;
	for(jointID = 0; jointID<20;jointID ++)
	{
	  framePosX = 4*jointID +1;
	  joint bodyJoint(frame[framePosX]-origin.dimesion_xyz[0], frame[framePosX+1]-origin.dimesion_xyz[1], frame[framePosX+2]-origin.dimesion_xyz[2]);
	  int cube_xyz[3];
	  for(int j=0;j<=2;j++)
	  {
	    if(bodyJoint.dimesion_xyz[j] < - height/6)
	      cube_xyz[j] = 0;
	    else if(bodyJoint.dimesion_xyz[j] > height/6)
	      cube_xyz[j] = 2;
	    else
	      cube_xyz[j] = 1;	
	  }
	  stringstream ss;
	  //ss << pow(3,cube_xyz[0])+pow(3,cube_xyz[1])+pow(3,cube_xyz[2]);
	  ss << cube_xyz[0]+3*cube_xyz[1]+9*cube_xyz[2]+1;
	  jointInCubes[jointID]= jointInCubes[jointID]+ss.str()+" ";
	}
      }
      frameCounter ++;
    }
    for(int i=0; i<jointInCubes.size();i++)
    {
      jointInCubes[i] = MakeTimeInvariant(jointInCubes[i]);
    }
    //For each gesture, jointInCubes is 20 sized array each having an array for cube traversal of each joint
    gesture[gestureNo].push_back(jointInCubes);
    //cout << "\n";
  }
}

void endTimeGestureCalc(string fileId)
{
  string path = "/media/20FCDB6EFCDB3D2A/Users/shashcs/Desktop/KINECT BTP/MicrosoftGestureDataset/MicrosoftGestureDataset-RC/data/";
  string fileName = path + fileId +".csv";
  ifstream infile(fileName.c_str());
  
  string time = "";
  double realTime;
  string frameString;
  int frameNum = -1;
  
  while(getline(infile,frameString))
  {
    frameNum ++;
    time = "";
    for(int i =0;i<frameString.length();i++)
    {
      if(frameString[i]!=' ')
      {
	time = time + frameString[i];
      }
      else
      {
	realTime = atof(time.c_str());
	break;
      }
    }
    
    for(int j = 0;j<approxEndTimeGesture.size();j++)
    {
      double newDifference = abs(approxEndTimeGesture[j] - realTime);
      if(newDifference <= difference[j])
      {
	endTimeGesture[j] = time;
	endFrameOfGesture[j] = frameNum;
	difference[j] = newDifference;
      }
    }
  }
  
  //output gesture start values - these are end gesture values :P
  //for(int j =0;j<endTimeGesture.size();j++)
  //  cout << endFrameOfGesture[j] << ", ";
}

void approxEndTimeGestureCalc(string fileId)
{
  string path = "/media/20FCDB6EFCDB3D2A/Users/shashcs/Desktop/KINECT BTP/MicrosoftGestureDataset/MicrosoftGestureDataset-RC/data/";
  string tagName = path + fileId + ".tagstream";
  ifstream inTagfile(tagName.c_str());
  
  string approxTime ="";
  string tagString;
  getline(inTagfile,tagString);
  
  while(getline(inTagfile,tagString))
  {
    approxTime = "";
    for(int i =0;i<tagString.length();i++)
    {
      if(tagString[i]!=';')
      {
	approxTime = approxTime + tagString[i];
      }
      else
      {
	approxEndTimeGesture.push_back(((atof(approxTime.c_str())*1000 + 49875/2)/49875));
	endTimeGesture.push_back("");
	endFrameOfGesture.push_back(0);
	difference.push_back(999999999999);
	break;
      }
    }
  }
}

double dist(joint a, joint b)
{
  double square_dist = 0.0;
  for(int i =0;i <=2;i++)
  {
    square_dist = square_dist + pow(a.dimesion_xyz[i]-b.dimesion_xyz[i],2);
  }
  return pow(square_dist, 0.5);  
}

int findGestureNo(string fileName)
{
  //for(int i =0;i<fileNa
  istringstream fileNaam(fileName);
  string token;
  getline(fileNaam,token,'_');
  getline(fileNaam,token,'_');
  getline(fileNaam,token,'_');
  if(token[token.length()-1] == 'A')
    token = token.substr(0,token.length()-1);
  cout << "token_no" << token << "\n";
  return atoi(token.c_str());
}

string MakeTimeInvariant(string cubeSeq)
{
  vector<string> allTokens;
  string token;
  istringstream cubeSequence(cubeSeq);
  
  while(getline(cubeSequence,token,' '))
  {
    allTokens.push_back(token);
  }
  string newCubeSeq = "";
  for(int i =0;i<allTokens.size()-1;i++)
  {
    if(allTokens[i].compare(allTokens[i+1])!=0)
      newCubeSeq = newCubeSeq + "," + allTokens[i];
  }
  //Last is always returned.
  newCubeSeq = newCubeSeq + "," + allTokens[allTokens.size()-1];
  newCubeSeq = newCubeSeq.substr(1,newCubeSeq.length());
  
  return newCubeSeq;
}