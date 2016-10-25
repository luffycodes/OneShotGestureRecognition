# OneShotGestureRecognition
Train hand gestures using depth data from Kinect in just one shot. Tested on 20 hand gestures.

## Algorithm
As the body moves through space, kinect sensor gives depth data of 20 body joints in real time. As the user starts to train, record the trajectory followed by the hand. When he repeats the same gesture, the trajectories are compared using needleman wunsch algorithm.

## Acknowledgments
* Professor [Harish Karnick](http://www.iitk.ac.in/new/dr-harish-karnick), CSE, IIT Kanpur
