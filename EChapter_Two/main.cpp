#include "ELibDef.h"
#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "EMacro.h"
#include "EFormatManual.h"
#include "EFormatFactory.h"

void CreateAlphaMat(cv::Mat &mat) {
	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			cv::Vec4b &rgba = mat.at<cv::Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = cv::saturate_cast<uchar>((float(mat.cols - j)) / (float(mat.cols)) * UCHAR_MAX);
			rgba[0] = cv::saturate_cast<uchar>((float(mat.rows - j)) / (float(mat.rows)) * UCHAR_MAX);
			rgba[0] = cv::saturate_cast<uchar>(0.5 * (rgba[1] + rgba[1]));
		}
	}
}

void WriteAlphaMat() {
	cv::Mat mat(480, 640, CV_8UC4);
	CreateAlphaMat(mat);

	std::vector<int> compression_params;
	compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try {
		cv::imwrite("alpha.png", mat, compression_params);
		cv::imshow("created png", mat);
		cv::waitKey();
	}
	catch (std::runtime_error* e) {
		fprintf(stderr, e->what());
	}
}

void MixerImage() {
	cv::Mat image = cv::imread("dota.jpg");
	cv::namedWindow("dota windows");
	cv::imshow("dota windows", image);

	cv::Mat logo = cv::imread("dota_logo.jpg");
	cv::namedWindow("dota_logo windows");
	cv::imshow("dota_logo windows", logo);

	//800 and 350 are imageRoi location on image
	cv::Mat imageRoi = image(cv::Rect(800, 350, logo.cols, logo.rows));

	// add logo in imageRoi, mixer imageRoi and logo
	cv::addWeighted(imageRoi, 0.5, logo, 0.3, 0.0, imageRoi);
	cv::namedWindow("mixed_dota");
	cv::imshow("mixed_dota", image);
	cv::imwrite("mixed_dota.jpg", image);

	cv::waitKey();
}

#define WINDOW_NAME "track bar demo"
const int g_nMaxAlphaValue = 100;
int g_nAlphaSlider;
double g_dAlphaValue;
double g_dBetaValue;

cv::Mat g_srcImage1;
cv::Mat g_srcImage2;
cv::Mat g_dstImage;

void OnTrackBar(int, void*) {
	g_dAlphaValue = (double)((double)g_nAlphaSlider / (double)g_nMaxAlphaValue);
	g_dBetaValue = 1.0 - g_dAlphaValue;

	cv::addWeighted(g_srcImage2, g_dAlphaValue, g_srcImage1, g_dBetaValue, 0.0, g_dstImage);
	cv::imshow(WINDOW_NAME, g_dstImage);
}

void TrackbarDemo() {
	g_srcImage1 = cv::imread("trackbar1.jpg");
	g_srcImage2 = cv::imread("trackbar2.jpg");

	g_nAlphaSlider = 70;
	cv::namedWindow(WINDOW_NAME, 1);

	char cTracebarName[20];
	sprintf_s(cTracebarName, "alpha value %d", g_nMaxAlphaValue);

	cv::createTrackbar(cTracebarName, WINDOW_NAME, &g_nAlphaSlider, g_nMaxAlphaValue, OnTrackBar);
	OnTrackBar(g_nAlphaSlider, 0);

	cv::waitKey();
}

int main() {

	EFormatManual::GetInstance()->Print(3, "write alpha mat", "mixer image", "track bar");
	EFormatFactory pImgFactory;
	pImgFactory.RegisterCmd(3, (void*)&WriteAlphaMat, (void*)&MixerImage, (void*)&TrackbarDemo);
	pImgFactory.ExecCmd();
	return 0;
}