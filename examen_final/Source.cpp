#include <iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
Mat framesMap;
Mat final_filtrada;
Mat canales_copoa[3];
//parametros click _1
int r_1, g_1, b_1;
int x_1 = 0;
int y_1 = 0;


// parametros click _2
int r_2, g_2, b_2;
int x_2 = 0;
int y_2 = 0;
// parametros click _3

int r_3, g_3, b_3;
int x_3 = 0;
int y_3 = 0;
// parametros click _4
int r_4, g_4, b_4;
int x_4 = 0;
int y_4 = 0;


int distancia = 0;
int distancia_1 = 0;
int limite_superior_x = 0;
int limite_inferior_x = 0;
int limite_superior_y = 0;
int limite_inferior_y = 0;
int limite = 10;
float promedio;
Mat vector_vacio_g;
Mat vector_vacio_r;
Mat vector_vacio_b;
int index_1 = 0;
int index_2 = 0;
float promedio_g = 0;
float promedio_r = 0;
float promedio_b = 0;
int contador = 1;
int desface = 50;
int desface_1 = 40;
int resta_x = 0;
int resta_y = 0;
int resta_x_1 = 0;
int resta_y_1 = 0;
void onMouse(int event, int x, int y, int, void*);

int main()
{
	VideoCapture cap(0);
	while (true)
	{

		Point p;
		int filas, columnas;
		Mat RGBchannels[3];
		vector_vacio_g = Mat::ones(20, 20, CV_32F);
		vector_vacio_r = Mat::ones(20, 20, CV_32F);
		vector_vacio_b = Mat::ones(20, 20, CV_32F);
		Mat image = imread("frutas.jpg");
		

		split(image, RGBchannels);
		framesMap = image.clone();
		split(framesMap, canales_copoa);
		namedWindow("window");
		imshow("window", image);
		//imshow("window_1", framesMap);
		setMouseCallback("window", onMouse, 0);

		filas = framesMap.rows;
		columnas = framesMap.cols;

		// calculo de la distancia de la region de interes
		distancia = sqrt((pow(x_4 - x_3, 2)) + (pow(y_4 - y_3, 2)));
		distancia_1 = sqrt((pow(x_2 - x_1, 2)) + (pow(y_2 - y_1, 2)));
		// calculo del area del rectangulo a sacar el valor promdio de la zona de interes
		limite_superior_x = x_4 + limite;
		if (limite_superior_x >= columnas)
		{
			limite_superior_x = columnas;
		}
		limite_inferior_x = x_4 - limite;
		if (limite_inferior_x <= 0)
		{
			limite_inferior_x = 0;
		}

		limite_superior_y = y_4 + limite;
		if (limite_superior_y >= filas)
		{
			limite_superior_y = filas;
		}

		limite_inferior_y = y_4 - limite;
		if (limite_inferior_y <= 0)
		{
			limite_inferior_y = 0;
		}
		cout << "posiciones y rgb de la imagen" << endl;
		cout << x_1 << "," << y_1 << endl;
		cout << r_1 << "," << g_1 << "," << b_1 << endl;
		cout << "impresion de los limtes a analizar para sacar el promedio de cada matriz" << endl;
		cout << limite_superior_x << "," << limite_inferior_x << endl;
		cout << limite_superior_y << "," << limite_inferior_y << endl;
		// guardar esos datos en un vector para luego sacar el promedio
		for (int i = limite_inferior_y; i < limite_superior_y; i++)
		{

			index_2 = 0;
			for (int j = limite_inferior_x; j < limite_superior_x; j++)
			{

				vector_vacio_g.at<float>(index_1, index_2) = int(canales_copoa[1].at<uint8_t>(i, j));
				vector_vacio_r.at<float>(index_1, index_2) = int(canales_copoa[2].at<uint8_t>(i, j));
				vector_vacio_b.at<float>(index_1, index_2) = int(canales_copoa[0].at<uint8_t>(i, j));

				index_2 = index_2 + 1;
			}
			index_1 = index_1 + 1;
		}
		// calculo del promedio
		for (int i = 0; i < 20; i++)
		{

			for (int j = 0; j < 20; j++)
			{

				promedio_g = promedio_g + vector_vacio_g.at<float>(i, j);
				promedio_r = promedio_r + vector_vacio_r.at<float>(i, j);
				promedio_b = promedio_b + vector_vacio_b.at<float>(i, j);

				contador = contador + 1;
			}

		}
		promedio_g = int(promedio_g / contador);
		promedio_r = int(promedio_r / contador);
		promedio_b = int(promedio_b / contador);
		//cout << vector_vacio_g << endl;
		//cout << promedio_g << "," << promedio_r << "," << promedio_b << endl;
		// analisis de cada pixel para ahcer 255 cuando se cumpla
		for (int i = 0; i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				if ((int(RGBchannels[1].at<uint8_t>(i, j)) > promedio_g - desface && int(RGBchannels[1].at<uint8_t>(i, j)) < promedio_g + desface) && (int(RGBchannels[2].at<uint8_t>(i, j)) > promedio_r - desface && int(RGBchannels[2].at<uint8_t>(i, j)) < promedio_r + desface) && (int(RGBchannels[0].at<uint8_t>(i, j)) > promedio_b - desface && int(RGBchannels[0].at<uint8_t>(i, j)) < promedio_b + desface))
				{
					// redio del primer elemento seleccionado
					resta_x = abs(j - x_4);
					resta_y = abs(i - y_4);

					if ((resta_x < distancia) && (resta_y < distancia))
					{
						RGBchannels[1].at<uint8_t>(i, j) = 255;
						RGBchannels[2].at<uint8_t>(i, j) = 255;
						RGBchannels[0].at<uint8_t>(i, j) = 255;
					}


				}
				if ((int(RGBchannels[1].at<uint8_t>(i, j)) > g_2 - desface_1 && int(RGBchannels[1].at<uint8_t>(i, j)) < g_2 + desface_1) && (int(RGBchannels[2].at<uint8_t>(i, j)) > r_2 - desface_1 && int(RGBchannels[2].at<uint8_t>(i, j)) < r_2 + desface_1) && (int(RGBchannels[0].at<uint8_t>(i, j)) > b_2 - desface_1 && int(RGBchannels[0].at<uint8_t>(i, j)) < b_2 + desface_1))
				{
					// radio del segundo elemeento seleecionado
					resta_x_1 = abs(j - x_2);
					resta_y_1 = abs(i - y_2);

					if ((resta_x_1 < distancia_1) && (resta_y_1 < distancia_1))
					{
						RGBchannels[1].at<uint8_t>(i, j) = 255;
						RGBchannels[2].at<uint8_t>(i, j) = 255;
						RGBchannels[0].at<uint8_t>(i, j) = 255;
					}

					//cout << int(RGBchannels[1].at<uint8_t>(i, j)) << endl;
				}




			}
		}
		//union de los canales
		merge(RGBchannels, 3, final_filtrada);
		imshow("matriz rojo", RGBchannels[2]);
		imshow("matriz verde", RGBchannels[1]);
		imshow("matriz azul", RGBchannels[0]);
		imshow("el filtro final es", final_filtrada);
		if (waitKey(1) == 27)
			break;
		


	}
		
}
// obtencion de coores mediante mouse
void onMouse(int event, int x, int y, int, void*)
{
	if (event != CV_EVENT_LBUTTONDOWN)
		return;

	Point pt = Point(x, y);


	if (framesMap.channels() == 3)
	{
		std::cout << "(" << pt.x << ", " << pt.y << ") ...... [blue] " << int(framesMap.at<Vec3b>(y, x)[0]) << " [green] " << int(framesMap.at<Vec3b>(y, x)[1]) << " [red] " << int(framesMap.at<Vec3b>(y, x)[2]) << '\n';
		//parametros delclick_4
		r_4 = r_3;
		g_4 = g_3;
		b_4 = b_3;
		x_4 = x_3;
		y_4 = y_3;
		//parametros delclick_3
		r_3 = r_2;
		g_3 = g_2;
		b_3 = b_2;
		x_3 = x_2;
		y_3 = y_2;
		//parametros del click_2
		r_2 = r_1;
		g_2 = g_1;
		b_2 = b_1;
		x_2 = x_1;
		y_2 = y_1;
		// parametros del click_1
		r_1 = int(framesMap.at<Vec3b>(y, x)[2]);
		g_1 = int(framesMap.at<Vec3b>(y, x)[1]);
		b_1 = int(framesMap.at<Vec3b>(y, x)[0]);
		x_1 = pt.x;
		y_1 = pt.y;
	}
	else
	{
		std::cout << "(" << pt.x << ", " << pt.y << ") ......  " << int(framesMap.at<uchar>(y, x)) << '\n';
	}
}