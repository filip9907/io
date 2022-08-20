#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
/// <summary>
	/// Podstawowy filtr bazujacy na macierzy.
	/// </summary>
	/// <returns>Zaleznie od wybranej operacji moze zwracac elementy zwiazane ze swoja macierza, zmieniac je lub bazujac na nich zwrocic przefiltrowany obrazek.</returns>
class filter
{
protected:
	/// <summary>
	/// wartosc int opisujaca wielkosc macierzy
	/// </summary>
	int size;
	/// <summary>
	/// wartosc int opisujaca zasieg od srodkowego elementu macierzy
	/// </summary>
	int reach;
	/// <summary>
	/// dynamicznie alokowana macierz kwadratowa elementow double
	/// </summary>
	double** matrix;
public:

	/// <summary>
	/// zwraca sume wag lub 1, gdy jest ona rowna 0
	/// </summary>
	/// <returns>wartosc double wag</returns>

	double calcK()
	{
		double sum = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				sum += matrix[i][j];
			}
		}
		if (sum == 0) { return 1; }
		return sum;
	}
	/// <summary>
	/// zwraca rozmiar macierzy
	/// </summary>
	/// <returns>wartosc int rozmiaru macierzy</returns>
	int returnSize()
	{
		return size;
	}
	/// <summary>
	/// zwraca zasieg od srodka macierzy
	/// </summary>
	/// <returns>wartosc int zasiegu</returns>
	int returnReach()
	{
		return reach;
	}
	/// <summary>
	/// zwraca element macierzy z podanych koordynatow
	/// </summary>
	/// <param name="x">koordynata x w postaci liczby int</param>
	/// <param name="y">koordynata y w postaci liczby int</param>
	/// <returns>wartosc double elementu</returns>
	double returnMatrixElement(int x, int y) 
	{
		if (x < 0 || y < 0 || x >= size || y >= size)
		{
			cout << "\nYou are trying to retrieve wrong coordinates! Returning default value" << endl;
			waitKey(0);
			return 1;
		}
		return matrix[x][y];
	}
	/// <summary>
	/// wyswietla aktualna macierz
	/// </summary>
	void showMatrix()
	{
		cout << "\nCurrent filter matrix: " << endl;
		for (int i = 0; i < size; i++)
		{
			cout << endl;
			for (int j = 0; j < size; j++)
			{
				cout << matrix[i][j] << " ";
			}
		}
	}
	/// <summary>
	/// ustawia wartosc calej macierzy na podana wartosc
	/// </summary>
	/// <param name="a">wartosc double na ktora ma byc ustawiona cala macierz</param>
	void setMatrix(double a) 
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = a;
			}
		}
	}
	/// <summary>
	/// ustawia pojedynczy element macierzy o podanych koordynatach na a
	/// </summary>
	/// <param name="a">wartosc double na ktora ma zostac ustawiony element macierzy</param>
	/// <param name="x">koordynata x w postaci liczby int</param>
	/// <param name="y">koordynata y w postaci liczby int</param>
	void setMatrixCo(double a, int x, int y) 
	{
		if(x<0||y<0||x>=size|| y >= size)
			{
				cout<<"\nWrong coordinates!"<<endl;
				waitKey(0);
				return;
			}
		matrix[x][y] = a;
	}
	/// <summary>
	/// ustawia wielkosc i automatycznie zasieg
	/// </summary>
	/// <param name="a">wartosc int wielkosci macierzy</param>
	void setSize(int a) 
	{
		size = a;
		setReach(floor(a / 2));
	}
	/// <summary>
	/// ustawia zasieg
	/// </summary>
	/// <param name="a">wartosc zasiegu</param>
	void setReach(int a)
	{
		reach = a;
	}
	///destruktor usuwajacy dynamicznie alokowana macierz
	~filter()
	{
		for (int i = 0; i < size; ++i)
		{
			delete [] matrix[i];
		}
		delete [] matrix;
	}
	/// <summary>
	/// tworzy macierz o podanym rozmiarze
	/// </summary>
	/// <param name="size">wartosc int wielkosci macierzy</param>
	filter(int size) :
		size(abs(size)),
		reach(abs(floor(size / 2))),
		matrix( new double * [abs(size)])
		{
		if (size % 2 == 0||size<1)
		{
			//Free the array of pointers
			delete[] matrix;
			while (size % 2 == 0||size<1)
			{
				cout << "\nPlease enter an odd number larger than 0 as size!" << endl;
				cout << "\nSize = ";
				cin >> size;
				
			}
			setSize(abs(size));
			matrix = new double* [abs(size)];
		}

		for (int i = 0; i < abs(size); ++i)
			{
				matrix[i] = new double[abs(size)];
			}
		setMatrix(1);
		};
	/// <summary>
	/// ustawia domyslna macierz w przypadku braku parametru wielkosci
	/// </summary>
	filter() :
		size(3),
		reach(floor(size/2)),
		matrix(new double* [3])
	{
		for (int i = 0; i < 3; ++i) {
			matrix[i] = new double[3];
		}
		setMatrix(1);
	};
	/// <summary>
	/// metoda zwracajaca przefiltrowany obrazek w formacie Mat bazujac na podanej macierzy filtru i podanym obrazku
	/// </summary>
	/// <param name="img_initial">wartosc w formacie Mat opisujaca oryginalny obrazek</param>
	/// <returns>wartosc w formacie Mat opisujaca przefiltrowany obrazek</returns>
	Mat Filter(Mat img_initial) 
	{
		if(img_initial.rows<size||img_initial.cols<size)
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
					double suma = 0;
					for (int p = 0 - returnReach(); p <= returnReach(); p++)
					{
						//if (r - p<0 || r + p>img_initial.rows) { break; }
						for (int o = 0 - (returnReach()); o <= returnReach(); o++)
						{
							//if (c - o<0 || c + o>img_initial.cols) { break; }
							suma += returnMatrixElement(p + returnReach(), o + returnReach()) * img_initial.at<Vec3b>(r + o, c + p)[i];
						}
					}
					int am = suma / calcK();
					if (am < 0) { am = 256 - am; }
					img_after_filter.at<Vec3b>(r, c)[i] = am;
				}

			}
		}
		return img_after_filter;
	}

};

