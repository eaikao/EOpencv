#include "ELibDef.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include "EMacro.h"
#include "EFormatManual.h"
#include "EFormatFactory.h"

void ImageMat() {
	cv::Mat A = cv::imread("erode.jpg");
	cv::Mat B(A);
	cv::Mat C = A;

	printf("A.data = %p\nB.data = %p\nC.data = %p\n", A.data, B.data, C.data);

	//cv::waitKey(0);
}

void ImageMatCreate() {
	cv::Mat M1(3, 3, CV_8UC4, cv::Scalar(0, 0, 0, 255));
	std::cout << "M1 = " << std::endl << M1 << std::endl;

	int sz[2] = { 3, 3 };
	cv::Mat M2(2, sz, CV_8UC1, cv::Scalar::all(0));
	std::cout << "M2 = " << std::endl << M2 << std::endl;

	cv::Mat M3;
	M3.create(4, 4, CV_8UC(1));
	std::cout << "M3 = " << std::endl << M3 << std::endl;

	cv::Mat Me = cv::Mat::eye(4, 4, CV_64F);
	std::cout << "Me = " << std::endl << Me << std::endl;

	cv::Mat Mo = cv::Mat::ones(4, 4, CV_64F);
	std::cout << "Mo = " << std::endl << Mo << std::endl;

	cv::Mat Mz = cv::Mat::zeros(4, 4, CV_64F);
	std::cout << "Mz = " << std::endl << Mz << std::endl;


	cv::Mat M4 = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 0, 0, 0, 0, 1);
	std::cout << "M4 = " << std::endl << M4 << std::endl;

	cv::Mat M5 = M4.row(1).clone();
	std::cout << "M5 = " << std::endl << M5 << std::endl;

}

void CompressedPixel1(cv::Mat& srcImage, cv::Mat& dstImage, int div) {
	int nRows = dstImage.rows;
	int nCols = dstImage.cols * dstImage.channels();

	for (int i = 0; i < nRows; ++i) {
		uchar* pSrcData = srcImage.ptr<uchar>(i);
		uchar* pDstData = dstImage.ptr<uchar>(i);
		for (int j = 0; j < nCols; ++j) {
			pDstData[j] = pSrcData[j] / div * div + div / 2;
		}
	}
}

void CompressedPixel2(cv::Mat& srcImage, cv::Mat& dstImage, int div) {
	// 迭代器，按照三通道进行迭代
	cv::Mat_<cv::Vec3b>::iterator iterSrcCur = srcImage.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator iterSrcEnd = srcImage.end<cv::Vec3b>();

	cv::Mat_<cv::Vec3b>::iterator iterDstCur = dstImage.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator iterDstEnd = dstImage.end<cv::Vec3b>();

	for (; iterSrcCur != iterSrcEnd && iterDstCur != iterDstEnd; ++iterSrcCur, ++iterDstCur){
		(*iterDstCur)[0] = (*iterSrcCur)[0] / div * div + div / 2;
		(*iterDstCur)[1] = (*iterSrcCur)[1] / div * div + div / 2;
		(*iterDstCur)[2] = (*iterSrcCur)[2] / div * div + div / 2;
	}
}

void CompressedPixel3(cv::Mat& srcImage, cv::Mat& dstImage, int div) {
	int nRows = dstImage.rows;
	int nCols = dstImage.cols;

	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			dstImage.at<cv::Vec3b>(i, j)[0] = srcImage.at<cv::Vec3b>(i, j)[0] / div * div + div / 2;
			dstImage.at<cv::Vec3b>(i, j)[1] = srcImage.at<cv::Vec3b>(i, j)[1] / div * div + div / 2;
			dstImage.at<cv::Vec3b>(i, j)[2] = srcImage.at<cv::Vec3b>(i, j)[2] / div * div + div / 2;
		}
	}
}

void AccessMatData1() {
	cv::Mat srcImage = cv::imread("1.jpg");
	cv::imshow("src image", srcImage);

	cv::Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	double dStratTime = static_cast<double>(cv::getTickCount());

	CompressedPixel1(srcImage, dstImage, 32);
	
	double dTime = ((double)cv::getTickCount() - dStratTime) / cv::getTickFrequency();
	std::cout << "operation hours: " << dTime << "s" << std::endl;

	cv::imshow("dst image", dstImage);
	cv::waitKey(0);
}

void AccessMatData2() {
	cv::Mat srcImage = cv::imread("1.jpg");
	cv::imshow("src image", srcImage);

	cv::Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	double dStratTime = static_cast<double>(cv::getTickCount());

	CompressedPixel2(srcImage, dstImage, 32);

	double dTime = ((double)cv::getTickCount() - dStratTime) / cv::getTickFrequency();
	std::cout << "operation hours: " << dTime << "s" << std::endl;

	cv::imshow("dst image", dstImage);
	cv::waitKey(0);
}

void AccessMatData3() {
	cv::Mat srcImage = cv::imread("1.jpg");
	cv::imshow("src image", srcImage);

	cv::Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	double dStratTime = static_cast<double>(cv::getTickCount());

	CompressedPixel3(srcImage, dstImage, 32);

	double dTime = ((double)cv::getTickCount() - dStratTime) / cv::getTickFrequency();
	std::cout << "operation hours: " << dTime << "s" << std::endl;

	cv::imshow("dst image", dstImage);
	cv::waitKey(0);
}

void GraftingImage() {
	cv::Mat matSrcImage = cv::imread("dota_pa.jpg");
	cv::Mat matLogoImage = cv::imread("dota_logo.jpg");

	cv::Mat matRoiImage = matSrcImage(cv::Rect(200, 250, matLogoImage.cols, matLogoImage.rows));

	//加载掩模
	cv::Mat maskImage = cv::imread("dota_logo.jpg", 0);
	matLogoImage.copyTo(matRoiImage, maskImage);

	cv::imshow("Grafting Image", matSrcImage);
	cv::waitKey(0);
}

int main() {
	EFormatManual::GetInstance()->Print(6, "Mat", "Mat Create", "Access Mat Data1", "Access Mat Data2", "Access Mat Data3", "Grafting Image");
	EFormatFactory pImgFactory;
	pImgFactory.RegisterCmd(6, (void*)&ImageMat, (void*)&ImageMatCreate, (void*)&AccessMatData1, (void*)&AccessMatData2, (void*)&AccessMatData3, (void*)&GraftingImage);
	pImgFactory.ExecCmd();
	return 0;
}