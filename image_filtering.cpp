#include <iostream>
#include <opencv2/opencv.hpp>
#include "filter.h"
#include "filter_median.h"
#include "filter_min.h"
#include "filter_max.h"
#include "filter_add.h"
#include "load.h"
#include "image.h"
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
        cv::namedWindow("image1", WINDOW_NORMAL); // okno wyswietlajace odczytany obrazek
        cv::imshow("image1", img); // wyswietlenie obrazka
        destroyWindow("image1"); // usuniecie probnego okna
    }
    catch (cv::Exception& e)
    {
        const char* err_msg = e.what(); // zmienna przechowujaca opis wyjatku
        std::cout << "\nException caught: " << err_msg << std::endl; // wyswietlenie wyjatku
        cv::waitKey(0);
        exit(-1);
    }

    image img(imread(name));

    cv::namedWindow("before filtering", WINDOW_NORMAL); // otwarcie okna przed filtrowaniem
    cv::imshow("before filtering", img.get_current_img()); // otwarcie w nim obrazka oryginalnego
    cv::waitKey(1); // update obrazka

   // filters line{ "line", nullptr, nullptr, nullptr, nullptr, nullptr };

    while (1)
    {
        cout << "\nAvailable filters: \n";
        for (int i = 0; i < filtry.size(); i++)
        {
            cout << i << ". " << filtry[i]->filter_name << endl;
        }
        cout << filtry.size() + 1 << ". undo\n";
        cout << filtry.size() + 2 << ". redo\n";
        cout << filtry.size() + 3 << ". other\n";
        cout << filtry.size() + 4 << ". used filters list\n";
        cout << filtry.size() + 5 << ". draw a line\n";
        cout << "\nSelect corresponding number: ";
        int sel;
        cin >> sel;
        if (sel == filtry.size() + 1)
        {
            img.undo_current_img();
        }
        else if (sel == filtry.size() + 2)
            img.redo_current_img();
        else if (sel == filtry.size() + 3)
        {
            cout << "\nType in file name: ";
            cin >> name;
            img.reset_current_img(imread(name));
            cv::namedWindow("before filtering", WINDOW_NORMAL); // otwarcie okna przed filtrowaniem
            cv::imshow("before filtering", img.get_current_img()); // otwarcie w nim obrazka oryginalnego
            cv::waitKey(1);
        }
        else if (sel == filtry.size() + 4)
        {
            vector<filters*> filt_hist = img.get_filters_history();
            for (int fhi = 0; fhi < filt_hist.size(); fhi++)
            {
                cout << filt_hist[fhi]->filter_name << endl;
            }
        }
        else if (sel == filtry.size() + 5)
        {
            cv::Mat tmp = img.get_current_img().clone();
            int xs, ys, xk, yk, cb, cg, cr, thickness, lt;

            cout << "\nStarting point X coordinate: ";
            cin >> xs;
            cout << "\nStarting point Y coordinate: ";
            cin >> ys;
            cout << "\nEnding point X coordinate: ";
            cin >> xk;
            cout << "\nEnding point Y coordinate: ";
            cin >> yk;
            cout << "\nBlue colour value: ";
            cin >> cb;
            cout << "\nGreen colour value: ";
            cin >> cg;
            cout << "\nRed colour value: ";
            cin >> cr;
            cout << "\nSet thickness: ";
            cin >> thickness;

            cv::line(tmp, cv::Point2d(xs, ys), cv::Point2d(xk, yk), cv::Scalar(cb, cg, cr), thickness, cv::LINE_AA, 0);
            
            img.change_current_img( tmp, new filters{ "line" ,  nullptr, nullptr, nullptr, nullptr, nullptr });

        }
        else if (sel<0 || sel>filtry.size())
            cout << "\nWrong parameter selected\n";
        else if (filtry[sel]->filter != nullptr)
            img.change_current_img(filtry[sel]->filter->Filter(img.get_current_img()), filtry[sel]);
        else if (filtry[sel]->filter_add != nullptr)
            img.change_current_img(filtry[sel]->filter_add->Filter(img.get_current_img()), filtry[sel]);
        else if (filtry[sel]->filter_min != nullptr)
            img.change_current_img(filtry[sel]->filter_min->Filter(img.get_current_img()), filtry[sel]);
        else if (filtry[sel]->filter_median != nullptr)
            img.change_current_img(filtry[sel]->filter_median->Filter(img.get_current_img()), filtry[sel]);
        else if (filtry[sel]->filter_max != nullptr)
            img.change_current_img(filtry[sel]->filter_max->Filter(img.get_current_img()), filtry[sel]);

        cv::namedWindow("after filtering", WINDOW_NORMAL); // otworzenie okna w ktorym bedzie wyswietlony przefiltrowany obrazek
        cv::imshow("after filtering", img.get_current_img()); // wyswietlenie obrazka przefiltrowanego
        cv::waitKey(1);
        //zapis imwrite("nazwa.rozszerzenie", img.get_current_image());
    }

    return 0;
}