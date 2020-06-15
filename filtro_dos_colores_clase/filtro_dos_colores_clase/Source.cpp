#include <iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0);
	Mat img, src_gray, dst1, dst2, dst3, dst4, fig_1, fig_2, img_final;

	while (true) {
		//cap >> img;
		Mat img = imread("FERNANDO.png", CV_LOAD_IMAGE_COLOR);

		cvtColor(img, src_gray, CV_BGR2GRAY);

		threshold(src_gray, dst1, 75, 255, THRESH_BINARY);
		threshold(src_gray, dst2, 77, 255, THRESH_BINARY_INV);
		fig_1 = dst1 & dst2;

		threshold(src_gray, dst3, 225, 255, THRESH_BINARY);
		threshold(src_gray, dst4, 227, 255, THRESH_BINARY_INV);
		fig_2 = dst3 & dst4;

		img_final = fig_1 | fig_2;

		imshow("1.Imagen Original", img);
		imshow("2.Imagen Gris", src_gray);
		imshow("3 OTRO COLOR", fig_1);
		imshow("4.UN COLOR", fig_2);
		imshow("FILTRO TOTAL", img_final);

		if (waitKey(1) == 27)
			break;
	}
	return 0;
}