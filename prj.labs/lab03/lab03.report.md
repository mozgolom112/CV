## Работа 3. Яркостные преобразования
автор: Голованов Н.С.
дата: 2021-03-05T20:41:45

Репозиторий на [SVN](https://mysvn.ru/mozgolom112/CV/)
Репозиторий на [GitHub](https://github.com/mozgolom112/CV)

### Задание
1. В качестве тестового использовать изображение data/cross_0256x0256.png
2. Сгенерировать нетривиальную новую функцию преобразования яркости (не стоит использовать линейную функцию, гамму, случайная).
3. Сгенерировать визуализацию функцию преобразования яркости в виде изображения размером 512x512, черные точки а белом фоне.
4. Преобразовать пиксели grayscale версии тестового изображения при помощи LUT для сгенерированной функции преобразования.
4. Преобразовать пиксели каждого канала тестового изображения при помощи LUT для сгенерированной функции преобразования.
5. Результы сохранить для вставки в отчет.

### Результаты

![](lab03_rgb.png)
Рис. 1. Исходное тестовое изображение

![](lab03_gre.png)
Рис. 2. Тестовое изображение greyscale

![](lab03_gre_res.png)
Рис. 3. Результат применения функции преобразования яркости для greyscale

![](lab03_rgb_res.png)
Рис. 4. Результат применения функции преобразования яркости для каналов

![](lab03_viz_func.png)
Рис. 5. Визуализация функции яркостного преобразования

### Текст программы

```cpp
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
```
