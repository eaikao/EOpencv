#include "ELibDef.h"
#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "EMacro.h"
#include "EFormatManual.h"
#include "EFormatFactory.h"
#include "EBasicGraphic.h"

void DrawAtomImage() {
	cv::Mat atomImage = cv::Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	EBasicGraphic::DrawEllipse(atomImage, 90);
	EBasicGraphic::DrawEllipse(atomImage, 0);
	EBasicGraphic::DrawEllipse(atomImage, 45);
	EBasicGraphic::DrawEllipse(atomImage, -45);

	EBasicGraphic::DrawFilledCircle(atomImage, cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	cv::imshow("atom image", atomImage);
	cv::moveWindow("atom image", 0, 200);
	cv::waitKey();
}

void DrawRookImage() {
	cv::Mat rookImage = cv::Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	EBasicGraphic::DrawPolygon(rookImage);

	cv::rectangle(rookImage,
		cv::Point(0, 7 * WINDOW_WIDTH / 8),
		cv::Point(WINDOW_WIDTH, WINDOW_WIDTH),
		cv::Scalar(0, 255, 255),
		-1,
		8);

	EBasicGraphic::DrawLine(rookImage, cv::Point(0, 15 * WINDOW_WIDTH / 16), cv::Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	EBasicGraphic::DrawLine(rookImage, cv::Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), cv::Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	EBasicGraphic::DrawLine(rookImage, cv::Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
	EBasicGraphic::DrawLine(rookImage, cv::Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), cv::Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));

	cv::imshow("rook image", rookImage);
	cv::moveWindow("rook image", WINDOW_WIDTH, 200);

	cv::waitKey(0);
}

int main() {
	EFormatManual::GetInstance()->Print(2, "draw atom image", "draw rook image", "track bar");
	EFormatFactory pImgFactory;
	pImgFactory.RegisterCmd(2, (void*)&DrawAtomImage, (void*)&DrawRookImage);
	pImgFactory.ExecCmd();
	return 0;
}