#include"pch.h"


bool isGrayscaleImg(Mat srcImg)
{
	uchar typeImage;
	Mat rgb[3];
	split(srcImg, rgb);
	Mat dif;
	absdiff(rgb[0], rgb[1], dif);
	if (countNonZero(dif))
		return false;				//image is RGB image
	else
	{
		absdiff(rgb[0], rgb[2], dif);
		if (countNonZero(dif))
			return false;
		else
			return true;			//image is Grayscale image.
	}
}




int calcHistogram(Mat srcImg, vector<vector<unsigned int >> &hists)
{

	Vec3b a;
	if (isGrayscaleImg(srcImg))
	{
		vector<unsigned int> grayHist;
		for (int i = 0; i < 256; i++)
		{
			grayHist.push_back(0);
		}
		for (int x = 0; x < srcImg.rows; x++)
		{
			for (int y = 0; y < srcImg.cols; y++)
			{
				unsigned int a = (unsigned int)srcImg.at<uchar>(x, y);
				grayHist[a]++;
			}
		}
		hists.push_back(grayHist);
		return 1;
	}
	else
	{
		Mat rgb[3];
		split(srcImg, rgb);

		vector<unsigned int> redHist, greenHist, blueHist;
		for (int i = 0; i < 256; i++)
		{
			redHist.push_back(0);
			greenHist.push_back(0);
			blueHist.push_back(0);
		}
		for (int x = 0; x < rgb[0].rows; x++)
		{
			for (int y = 0; y < rgb[0].cols; y++)
			{
				unsigned int red = (unsigned int)rgb[0].at<uchar>(x, y);
				unsigned int green = (unsigned int)rgb[1].at<uchar>(x, y);
				unsigned int blue = (unsigned int)rgb[2].at<uchar>(x, y);
				redHist[red]++;
				greenHist[green]++;
				blueHist[green]++;
			}
		}
		hists.push_back(redHist);
		hists.push_back(greenHist);
		hists.push_back(blueHist);
		return 1;

	}
	return 0;

}

double avarageHist(vector<unsigned int> hist)
{
	double total = 0;
	for (int i = 0; i < hist.size(); i++)
	{
		total = total + hist[i];
	}
	double result = total / hist.size();
	return result;
}

double compareTwoHist(vector<unsigned int> hist1, vector<unsigned int> hist2, double avg1, double avg2)
{
	double result = 0;
	double num = 0;
	double denom1 = 0, denom2 = 0;
	for (int i = 0; i < hist1.size(); i++)
	{
		num = num + (hist1[i] - avg1) * (hist2[i] - avg2);
		denom1 = denom1 + pow((hist1[i] - avg1), 2);
		denom2 = denom2 + pow((hist2[i] - avg2), 2);
	}
	result = num / sqrt(denom1 * denom2);
	return result;
}

double compareHist(Mat srcImg1, Mat srcImg2)
{
	double result = 0;
	if (isGrayscaleImg(srcImg1) != isGrayscaleImg(srcImg2))
	{
		cout << "khac loai anh" << endl;
		return 0;
	}
	else
	{
		vector<vector<unsigned int>> histSrc1, histSrc2;
		calcHistogram(srcImg1, histSrc1);
		calcHistogram(srcImg2, histSrc2);

		if (isGrayscaleImg(srcImg1))
		{
			
			
			double avargeHist1 = avarageHist(histSrc1[0]);
			double avargeHist2 = avarageHist(histSrc2[0]);

			result = compareTwoHist(histSrc1[0], histSrc2[0], avargeHist1, avargeHist2);
			return result;
		}

		else
		{
			double avargeHistRed1 = avarageHist(histSrc1[0]);
			double avargeHistGreen1 = avarageHist(histSrc1[1]);
			double avargeHistBlue1 = avarageHist(histSrc1[2]);

			double avargeHistRed2 = avarageHist(histSrc2[0]);
			double avargeHistGreen2 = avarageHist(histSrc2[1]);
			double avargeHistBlue2 = avarageHist(histSrc2[2]);

			double resultCompareRedChannel, resultCompareGreenChannel, resultCompareBlueChannel;

			resultCompareRedChannel = compareTwoHist(histSrc1[0], histSrc2[0], avargeHistRed1, avargeHistRed2);
			resultCompareGreenChannel = compareTwoHist(histSrc1[1], histSrc2[1], avargeHistGreen1, avargeHistGreen2);
			resultCompareBlueChannel = compareTwoHist(histSrc1[2], histSrc2[2], avargeHistBlue1, avargeHistBlue2);

			result = (resultCompareRedChannel + resultCompareGreenChannel + resultCompareBlueChannel) / 3;
			return result;
		}
	}
	return 0;
}

