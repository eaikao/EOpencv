#include "EBasicGraphic.h"


EBasicGraphic::EBasicGraphic() {

}

EBasicGraphic::~EBasicGraphic() {

}

void EBasicGraphic::DrawEllipse(cv::Mat img, double dAngle) {
	int nThickness = 2;
	int nLineType = 8;

	cv::ellipse(img, cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), cv::Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16), 
		dAngle, 0 , 360, cv::Scalar(255, 129, 0), nThickness, nLineType);
}

void EBasicGraphic::DrawFilledCircle(cv::Mat img, cv::Point center) {
	int nThickness = 2;
	int nLineType = 8;

	cv::circle(img, center, WINDOW_WIDTH / 32, cv::Scalar(0, 0, 255), nThickness, nLineType);
}

void EBasicGraphic::DrawPolygon(cv::Mat img) {
	int lineType = 8;

	// first polygon
	cv::Point rookPoints[1][20];
	rookPoints[0][0] = cv::Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][1] = cv::Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][2] = cv::Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][3] = cv::Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][4] = cv::Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][5] = cv::Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][6] = cv::Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][7] = cv::Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][8] = cv::Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][9] = cv::Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][10] = cv::Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][11] = cv::Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][12] = cv::Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][13] = cv::Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][14] = cv::Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][15] = cv::Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][16] = cv::Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][17] = cv::Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][18] = cv::Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][19] = cv::Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);

	int npt[1] = { 20 };
	const cv::Point  *ppt[1] = { rookPoints[0] };

	cv::fillPoly(img, ppt, npt, 1, cv::Scalar(0, 0, 0), lineType);
}

void EBasicGraphic::DrawLine(cv::Mat img, cv::Point start, cv::Point end) {
	int nThickness = 2;
	int nLineType = 8;

	cv::line(img, start, end, cv::Scalar(0, 0, 0), nThickness, nLineType);
}

