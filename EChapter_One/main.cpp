#include "ELibDef.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "EMacro.h"
#include "EFormatManual.h"
#include "EFormatFactory.h"

void ImageErode() {
	cv::Mat srcImage = cv::imread("erode.jpg");
	cv::imshow("show src image", srcImage);

	cv::Mat srcElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
	cv::Mat dstImage;
	erode(srcImage, dstImage, srcElement);
	cv::imshow("erode image:", dstImage);
	cv::waitKey(0);
}

void ImageBlur() {
	cv::Mat srcImage = cv::imread("blur.jpg");
	cv::imshow("show src image", srcImage);

	cv::Mat dstImage;
	cv::blur(srcImage, dstImage, cv::Size(7, 7));
	cv::imshow("blur image:", dstImage);
	cv::waitKey(0);
}

void ImageCanny() {
	cv::Mat srcImage = cv::imread("canny.jpg");
	cv::imshow("src canny image", srcImage);

	cv::Mat dstImage, edge, grayImage;

	dstImage.create(srcImage.size(), srcImage.type());
	cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

	blur(grayImage, edge, cv::Size(3, 3));

	cv::Canny(edge, edge, 3, 9, 3);
	cv::imshow("canny image:", edge);
	cv::waitKey(0);
}

void ImageVideo() {
	cv::VideoCapture capture("video.avi");

	while (true) {
		cv::Mat frame;
		capture >> frame;
		if (frame.data == NULL) {
			break;
		}
		cv::imshow("show video", frame);
		cv::waitKey(30);
	}
}

int main() {
	EFormatManual::GetInstance()->Print(4, "erode", "blur", "canny", "video");
	EFormatFactory pImgFactory;
	pImgFactory.RegisterCmd(4, (void*)&ImageErode, (void*)&ImageBlur, (void*)&ImageCanny, (void*)&ImageVideo);
	pImgFactory.ExecCmd();
	return 0;
}