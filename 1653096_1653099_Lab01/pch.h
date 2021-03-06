// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H


#include"Libraries/Headers/opencv2/core/core.hpp"
#include"Libraries/Headers/opencv2/highgui/highgui.hpp"
#include"Libraries/Headers/opencv2/imgproc/imgproc.hpp"


#include<iostream>
#include<string>
#include<cmath>
using namespace std;
using namespace cv;


//sub-functions
bool isGrayscaleImg(Mat srcImg);
double avarageHist(vector<unsigned int> hist);
double compareTwoHist(vector<unsigned int> hist1, vector<unsigned int> hist2, double avg1, double avg2);
//main-functions
//void convertArrIntToMat(unsigned int* Map, Mat srcImg, vector<Mat> &hists);


int calcHistogram(Mat srcImg, vector<vector<unsigned int >> &hists);
double compareHist(Mat srcImg1, Mat srcImg2);
// TODO: add headers that you want to pre-compile here

#endif //PCH_H
