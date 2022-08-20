#pragma once
#include "filter.h"
/// <summary>
	/// Specjalny filtr bazujacy na macierzy, wybierajacy medianowy element w zasiegu.
	/// </summary>
	/// <returns>Zaleznie od wybranej operacji moze stworzyc nowy filtr, wyswietlic go i przefiltrowac obrazek, ale nie moze zmieniac swoich parametrow.</returns>
class filter_median : protected filter
{
public:
	/// <summary>
	/// tworzy filtr podstawowy
	/// </summary>
	/// <param name="size">wartosc int opisujaca wielkosc macierzy</param>
	filter_median(int size)
		: filter(size) 
	{}
	/// <summary>
	/// wirtualna metoda odwolujaca sie do klasy po ktorej dziedziczy w celu wyswietlenia macierzy
	/// </summary>
	virtual void showMatrix() { filter::showMatrix(); }
	/// <summary>
	/// przeciazenie, wirtualna metoda uzywajaca specjalnego typu filtrowania, w tym przypadku wybiera element medianowy z zasiegu
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
		for (int r = returnReach(); r < img_initial.rows - returnReach(); r++)
		{
			for (int c = returnReach(); c < img_initial.cols - returnReach(); c++)
			{
				for (int i = 0; i < img_initial.at<Vec3b>(r, c).channels; i++)
				{
					vector<int>vec;
					for (int p = 0 - returnReach(); p <= returnReach(); p++)
					{
						//if (r - p<0 || r + p>img_initial.rows) { break; }
						for (int o = 0 - (returnReach()); o <= returnReach(); o++)
						{
							//if (c - o<0 || c + o>img_initial.cols) { break; }
							vec.push_back(returnMatrixElement(p + returnReach(), o + returnReach()) * img_initial.at<Vec3b>(r + o, c + p)[i]);
						}
					}
					sort(vec.begin(),vec.end());
					int am = vec.at(floor(vec.size()/2));
					if (am < 0) { am = 256 - am; }
					img_after_filter.at<Vec3b>(r, c)[i] = am;
					vec.clear();
				}

			}
		}
		return img_after_filter;
	}
};