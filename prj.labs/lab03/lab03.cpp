#include <opencv2/opencv.hpp>

int brightnessCorrection(int x) {
	float corr = 0;
	if (x <= 85) {
		corr = 0.5 * x;
	}
	if (x > 85 && x <= 170) {
		corr = 1.33*x - 71;
	}
	if (x > 170) {
		corr = 0.7*x + 36;
	}
	
	//float corr = exp(x)/(255*x);
	return corr;
}

std::vector<uchar> LUT_one_channel() { //gray for example
	std::vector<uchar> LUT;
	for (int i = 0; i < 256; i++) {
		LUT.push_back(brightnessCorrection(i));
	}
	return LUT;
}

int main() {
	cv::Mat img = cv::imread("./cross_0256x0256.png");
	//cv::imshow("img", img);
	cv::imwrite("./lab03_rgb.png", img);


	std::vector<uchar> lut_table = LUT_one_channel();
	cv::Mat visualisationLUT(cv::Size(512, 512), CV_8UC1, cv::Scalar(255,255,255));

	for (size_t i = 0; i < 256; i++) {
		visualisationLUT.at<uchar>(512 - 2 * lut_table[i], 2 * i) = 0;
		visualisationLUT.at<uchar>(512 - 2 * lut_table[i], 2 * i + 1) = 0;
		visualisationLUT.at<uchar>(512 - 2 * lut_table[i] - 1, 2 * i) = 0;
		visualisationLUT.at<uchar>(512 - 2 * lut_table[i] - 1, 2 * i + 1) = 0;
	}
	cv::imwrite("./lab03_viz_func.png", visualisationLUT);
	cv::Mat grayImg;
	cv::cvtColor(img, grayImg, cv::COLOR_RGB2GRAY);
	cv::imwrite("./lab03_gre.png", grayImg);
	cv::Mat grayLUT = cv::Mat::zeros(512, 512, CV_8U);;
	cv::LUT(grayImg, lut_table, grayLUT);
	cv::imwrite("./lab03_gre_res.png", grayLUT);
	cv::Mat imgLUT;
	cv::LUT(img, lut_table, imgLUT);
	cv::imwrite("./lab03_rgb_res.png", imgLUT);
	//cv::waitKey();
}