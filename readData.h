//void readData(string fileId)
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>
#include <sstream>

#define HIP_CENTER  0
#define SPINE  1
#define SHOULDER_CENTER  2
#define HEAD  3
#define SHOULDER_LEFT  4
#define ELBOW_LEFT  5
#define WRIST_LEFT  6
#define HAND_LEFT  7
#define SHOULDER_RIGHT  8
#define ELBOW_RIGHT  9
#define WRIST_RIGHT  10
#define HAND_RIGHT  11
#define HIP_LEFT  12
#define KNEE_LEFT  13
#define ANKLE_LEFT  14
#define FOOT_LEFT  15
#define HIP_RIGHT  16
#define KNEE_RIGHT  17
#define ANKLE_RIGHT  18
#define FOOT_RIGHT  19
using namespace std;

extern vector< vector<string> > gesture[13];

class joint
{
  public:
    vector<double> dimesion_xyz;
    joint(double, double, double);
};

joint::joint(double a,double b,double c)
{
  dimesion_xyz.push_back(a);
  dimesion_xyz.push_back(b);
  dimesion_xyz.push_back(c);
}

void readData(string fileName);
void endTimeGestureCalc(string fileId);
void approxEndTimeGestureCalc(string fileId);
double dist(joint, joint);
void cubeTrajectory(vector <vector<double> >gesture, joint origin, double height, int jointID);
void readEachGestureInFile();
int findGestureNo(string);
string MakeTimeInvariant(string cubeSeq);

/*
 * REMARKS..
P1_1_2_p21
Start after discarding 0 frames but still the first frame is very long.
They are End times of the gesture.
Gesture "G2  Duck", frame 202
Gesture "G2  Duck", frame 287
Gesture "G2  Duck", frame 382
Gesture "G2  Duck", frame 462
Gesture "G2  Duck", frame 549
Gesture "G2  Duck", frame 632
Gesture "G2  Duck", frame 714
Gesture "G2  Duck", frame 798
Gesture "G2  Duck", frame 894
Gesture "G2  Duck", frame 979

P1_1_8_p19
Gesture "G8  Throw", frame 126
Gesture "G8  Throw", frame 233
Gesture "G8  Throw", frame 358
Gesture "G8  Throw", frame 452
Gesture "G8  Throw", frame 546
Gesture "G8  Throw", frame 634
Gesture "G8  Throw", frame 731
Gesture "G8  Throw", frame 813
Gesture "G8  Throw", frame 897
Gesture "G8  Throw", frame 989

*/