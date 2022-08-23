#include <iostream>
#include <opencv2/opencv.hpp>
#include "filter.h"
#include "filter_median.h"
#include "filter_min.h"
#include "filter_max.h"
#include "filter_add.h"
#include "load.h"
#include <sstream>
#include <vector>
#include <filesystem>
using namespace std;
using namespace cv;

int main()
{
    string name; // zmienna wyboru wczytywanego pliku graficznego
    cout << "\nType in name file: ";
    cin >> name;
    vector<filters*> filtry;
    filtry = load();
    try
    {
        Mat img = imread(name); // macierz przechowujaca probny odczytany obrazek
        namedWindow("image1", WINDOW_NORMAL); // okno wyswietlajace odczytany obrazek
        imshow("image1", img); // wyswietlenie obrazka
        destroyWindow("image1"); // usuniecie probnego okna
    }
    catch (cv::Exception& e)
    {
        const char* err_msg = e.what(); // zmienna przechowujaca opis wyjatku
        std::cout << "\nException caught: " << err_msg << std::endl; // wyswietlenie wyjatku
        waitKey(0);
        exit(-1);
    }
    
    Mat img = imread(name); // wczytanie obrazka o podanej nazwie
    namedWindow("before filtering", WINDOW_NORMAL); // otwarcie okna przed filtrowaniem
    imshow("before filtering", img); // otwarcie w nim obrazka oryginalnego
    for (int i = 0; i < filtry.size(); i++)
    {
        Mat lena1;
        if (filtry[i]->filter != nullptr)
            lena1 = filtry[i]->filter->Filter(img);
        else if (filtry[i]->filter_add != nullptr)
            lena1 = filtry[i]->filter_add->Filter(img);
        else if (filtry[i]->filter_min != nullptr)
            lena1 = filtry[i]->filter_min->Filter(img);
        else if (filtry[i]->filter_median != nullptr)
            lena1 = filtry[i]->filter_median->Filter(img);
        else if (filtry[i]->filter_max != nullptr)
            lena1 = filtry[i]->filter_max->Filter(img);
        namedWindow("after filtering", WINDOW_NORMAL); // otworzenie okna w ktorym bedzie wyswietlony przefiltrowany obrazek
        string aft = "after filtering" + i;
        imshow(aft, lena1); // wyswietlenie obrazka przefiltrowanego

    }
    waitKey(0);
    return 0;
}
/*
int eeee(int argc, char** argv)
{
    int operation; // zmienna wyboru trybu operacji
    string name; // zmienna wyboru wczytywanego pliku graficznego
    int size; // zmienna wielkosci macierzy filtru
    if (argc == 4)
    {
    name = argv[1]; // przypisanie nazwy wczytywanego pliku graficznego
    stringstream intValueSize(argv[2]); // wykorzystanie stringstream w celu zamiany na wartosc int
    size = 0;
    intValueSize >> size;
    stringstream intValueOperation(argv[3]); // funkcja podobna do poprzedniego stringstream
    operation = 0;
    intValueOperation >> operation;
    }
    else
    {
        cout << "\nArgument count is not equal to 4!" << endl;
        cout << "\nType in name file: ";
        cin >> name;
        operation = -1;
        while (operation < 0 || operation>8)
        {
            cout << "\nPlease select operation:\n0. new filter\n1. average\n2. highpass\n3. lowpass\n4. median\n5. detect edge\n6. min\n7. max\n8. add" << endl;
            cin >> operation;
        }
        cout << "\nType in size of matrix (must be odd): ";
        cin >> size;
    }

    while (operation < 0 || operation>8)
    {
        cout << "\nPlease select operation:\n0. new filter\n1. average\n2. highpass\n3. lowpass\n4. median\n5. detect edge\n6. min\n7. max\n8. add" << endl;
        cin >> operation;
    }

    try
    {
        Mat img = imread(name); // macierz przechowujaca probny odczytany obrazek
        namedWindow("image1", WINDOW_NORMAL); // okno wyswietlajace odczytany obrazek
        imshow("image1", img); // wyswietlenie obrazka
        destroyWindow("image1"); // usuniecie probnego okna
    }
    catch (cv::Exception& e)
    {
        const char* err_msg = e.what(); // zmienna przechowujaca opis wyjatku
        std::cout << "\nException caught: " << err_msg << std::endl; // wyswietlenie wyjatku
        waitKey(0);
        exit(-1);
    }
    
    if (operation == 0) // przypadek tworzenia swojego nowego filtru
    {
        filter nowy(size); // stworzenie nowego filtru zwyklego
        cout << "\nSelected operation: new filter" << endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << "\nCurrent filter: " << endl;
                nowy.showMatrix();
                cout << "\nCurrent coordinate: [" << i << "], [" << j << "]" << endl;
                double x; // zmienna przechowujaca wartosc, ktora bedzie przypisywana elementowi macierzy
                cin >> x;
                nowy.setMatrixCo(x, i, j);
            }
        }
        nowy.showMatrix(); // wyswietlenie macierzy po ukonczeniu jej wypelniania
        Mat img = imread(name); // wczytanie obrazka o podanej nazwie
        namedWindow("before filtering", WINDOW_NORMAL); // otwarcie okna przed filtrowaniem
        imshow("before filtering", img); // otwarcie w nim obrazka oryginalnego
        Mat lena1 = nowy.Filter(img); // stworzenie przefiltrowanego obrazka
        namedWindow("after filtering", WINDOW_NORMAL); // otworzenie okna w ktorym bedzie wyswietlony przefiltrowany obrazek
        imshow("after filtering", lena1); // wyswietlenie obrazka przefiltrowanego
    }
    else if (operation == 1) // przypadek bazowego filtru usredniajacego
    {
        filter nowy(size); 
        nowy.showMatrix();
        cout << "\nSelected operation: averege" << endl;
        Mat img = imread(name);
        namedWindow("before filtering", WINDOW_NORMAL);
        imshow("before filtering", img);
        Mat lena1 = nowy.Filter(img);
        namedWindow("after filtering", WINDOW_NORMAL);
        imshow("after filtering", lena1);
    }
    else if (operation == 2) // przypadek tworzenia bazowego filtru gornoprzepustowego
    {
        filter nowy(size); 
        nowy.setMatrix(-1);
        nowy.setMatrixCo(size*size, nowy.returnReach(), nowy.returnReach());
        nowy.showMatrix();
        cout << "\nSelected operation: highpass" << endl;
        Mat img = imread(name);
        namedWindow("before filtering", WINDOW_NORMAL);
        imshow("before filtering", img);
        Mat lena1 = nowy.Filter(img);
        namedWindow("after filtering", WINDOW_NORMAL);
        imshow("after filtering", lena1);
    }
    else if (operation == 3) // przypadek tworzenia bazowego filtru dolnoprzepustowego
    {
        filter nowy(size);
        nowy.setMatrixCo(size*size, nowy.returnReach(), nowy.returnReach());
        nowy.showMatrix();
        cout << "\nSelected operation: lowpass" << endl;
        Mat img = imread(name);
        namedWindow("before filtering", WINDOW_NORMAL);
        imshow("before filtering", img);
        Mat lena1 = nowy.Filter(img);
        namedWindow("after filtering", WINDOW_NORMAL);
        imshow("after filtering", lena1);
    }
    else if (operation == 4) // przypadek tworzenia filtru medianowego
    {
        filter_median nowy(size);
        cout << "\nSelected operation: median" << endl;
        Mat img = imread(name);
        namedWindow("before filtering", WINDOW_NORMAL);
        imshow("before filtering", img);
        Mat lena1 = nowy.Filter(img);
        namedWindow("after filtering", WINDOW_NORMAL);
        imshow("after filtering", lena1);
    }
    else if (operation == 5) // przypadek tworzenia bazowego filtru wykrywajacego krawedzie
    {
        filter nowy(size);
        nowy.setMatrix(0);
        nowy.setMatrixCo(1, nowy.returnReach(), nowy.returnReach());
        if (size != 1)
        {
            nowy.setMatrixCo(-1, nowy.returnReach()-1, nowy.returnReach());
        }
        cout << "\nSelected operation: detect edge" << endl;
        Mat img = imread(name);
        namedWindow("before filtering", WINDOW_NORMAL);
        imshow("before filtering", img);
        Mat lena1 = nowy.Filter(img);
        namedWindow("after filtering", WINDOW_NORMAL);
        imshow("after filtering", lena1);
    }
    else if (operation == 6) // przypadek tworzenia filtru minimalnego elementu
    {
        filter_min nowy(size);
        cout << "\nSelected operation: min" << endl;
        Mat img = imread(name);
        namedWindow("before filtering", WINDOW_NORMAL);
        imshow("before filtering", img);
        Mat lena1 = nowy.Filter(img);
        namedWindow("after filtering", WINDOW_NORMAL);
        imshow("after filtering", lena1);
    }
    else if (operation == 7) // przypadek tworzenia filtru maksymalnego elementu
    {
        filter_max nowy(size);
        cout << "\nSelected operation: max" << endl;
        Mat img = imread(name);
        namedWindow("before filtering", WINDOW_NORMAL);
        imshow("before filtering", img);
        Mat lena1 = nowy.Filter(img);
        namedWindow("after filtering", WINDOW_NORMAL);
        imshow("after filtering", lena1);
    }
    else if (operation == 8)
    {
    int rv, gv, bv;
    cout << "\nSelected operation: add" << endl;
    cout << "\nRed value: ";
    cin >> rv;
    cout << "\nGreen value: ";
    cin >> gv;
    cout << "\nBlue value: ";
    cin >> bv;
    filter_add nowy(rv, gv, bv);
    Mat img = imread(name);
    namedWindow("before filtering", WINDOW_NORMAL);
    imshow("before filtering", img);
    Mat lena1 = nowy.Filter(img);
    namedWindow("after filtering", WINDOW_NORMAL);
    imshow("after filtering", lena1);
    }
    else
    {
        cout << "\nCannot determine filter type, please try again!" << endl;
        exit(-1);
    }
    waitKey(0);
    return 0;
}

*/