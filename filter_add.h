#pragma once
#include "filter.h"
/// <summary>
	/// Specjalny filtr bazujacy na macierzy, wybierajacy najwiekszy element w zasiegu.
	/// </summary>
	/// <returns>Zaleznie od wybranej operacji moze stworzyc nowy filtr, wyswietlic go i przefiltrowac obrazek, ale nie moze zmieniac swoich parametrow.</returns>
class filter_add : protected filter
{
protected:
	int red_val = 0;
	int green_val = 0;
	int blue_val = 0;

public:
	int val_red()
	{
		return red_val;
	}
	int val_green()
	{
		return green_val;
	}
	int val_blue()
	{
		return blue_val;
	}
	/// <summary>
	/// tworzy filtr podstawowy
	/// </summary>
	/// <param name="size">wartosc int opisujaca wielkosc macierzy</param>
	filter_add(int rv, int gv, int bv)
		: filter(1),
		red_val(rv),
		green_val(gv),
		blue_val(bv)
	{}
	/// <summary>
	/// tworzy filtr podstawowy
	/// </summary>
	/// <param name="size">wartosc int opisujaca wielkosc macierzy</param>
	virtual void showMatrix() { filter::showMatrix(); }
	/// <summary>
	/// przeciazenie, wirtualna metoda uzywajaca specjalnego typu filtrowania, w tym przypadku wybiera element najwiekszy z zasiegu
	/// </summary>
	/// <param name="img_initial">obrazek oryginalny w formie klasy Mat</param>
	/// <returns>klase Mat przechowujaca przefiltrowany obrazek</returns>
	virtual Mat Filter(Mat img_initial)
	{
		if (img_initial.rows < size || img_initial.cols < size)
		{
			cout << "\nCannot filter, filter matrix larger than image!" << endl;
			exit(-1);
		}
		Mat img_after_filter = Mat::zeros(Size(img_initial.cols, img_initial.rows), CV_8UC3);

		for (int r = 0; r < img_initial.rows; r++)
		{
			for (int c = 0; c < img_initial.cols; c++)
			{
				for (int i = 0; i < img_initial.at<Vec3b>(r, c).channels; i++)
				{
					if (i == 0)
						img_after_filter.at<Vec3b>(r, c)[i] = img_initial.at<Vec3b>(r, c)[i] + val_red();
					if (i == 1)
						img_after_filter.at<Vec3b>(r, c)[i] = img_initial.at<Vec3b>(r, c)[i] + val_green();
					if (i == 2)
						img_after_filter.at<Vec3b>(r, c)[i] = img_initial.at<Vec3b>(r, c)[i] + val_blue();
					if (img_after_filter.at<Vec3b>(r, c)[i] < 0)
						img_after_filter.at<Vec3b>(r, c)[i] = 256 - img_after_filter.at<Vec3b>(r, c)[i];
				}

			}
		}
		return img_after_filter;
	}
};