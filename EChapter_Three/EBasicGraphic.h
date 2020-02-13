#include <opencv2/opencv.hpp>

#define WINDOW_WIDTH 600
class EBasicGraphic {
public:
	EBasicGraphic ();
	~EBasicGraphic ();

	static void DrawEllipse(cv::Mat img, double dAngle);
	static void DrawFilledCircle(cv::Mat img, cv::Point center);
	static void DrawPolygon(cv::Mat img);
	static void DrawLine(cv::Mat img, cv::Point start, cv::Point end);

private:

};