// 1653096_1653099_Lab01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"



int main(int agrc, char** argv)
{
    std::cout << "Hello World!\n"; 
	Mat image1, image2;
	image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	image2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);
	vector<vector<unsigned int>> hists1, hists2;
	if (isGrayscaleImg(image1))
		cout << "anh trang den" << endl;
	else
		cout << "anh mau" << endl;

	calcHistogram(image1, hists1);
	calcHistogram(image2, hists2);

	double cp1, cp2;
	cp1 = compareHist(image1, image2);
	cout << cp1 << endl;

}


