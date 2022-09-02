#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "load.h"

using namespace std;
using namespace cv;

// generalnie obrazek musi miec historie zmian w obie strony, 3 funkcje na dole do wykorzystania

class image
{
protected:

	Mat current_img;
	vector<Mat> redo_history;
	vector<Mat> undo_history;
	vector<filters*> filters_history;
	vector<filters*> filters_redo_history;
public:

	vector<filters*> get_filters_history()
	{
		return filters_history;
	}

	image(Mat img) :
		current_img(img)
	{};

	void set_current_img(Mat img)
	{
		current_img = img;
	}

	Mat get_current_img()
	{
		return current_img;
	}

	void add_to_redo_history(Mat img)
	{
		redo_history.vector::push_back(img);
	}

	void remove_from_redo_history()
	{
		redo_history.vector::pop_back();
	}

	void clear_redo_history()
	{
		redo_history.vector::clear();
	}

	void add_to_undo_history(Mat img)
	{
		undo_history.vector::push_back(img);
	}

	void remove_from_undo_history()
	{
		undo_history.vector::pop_back();
	}

	void add_to_filters_history(filters *used_filters)
	{
		filters_history.vector::push_back(used_filters);
	}

	void remove_from_filters_history()
	{
		filters_history.vector::pop_back();
	}

	void add_to_redo_filter_history(filters *undone_filters)
	{
		filters_redo_history.vector::push_back(undone_filters);
	}

	void remove_from_filters_redo_history()
	{
		filters_redo_history.vector::pop_back();
	}

	void clear_redo_filter_history()
	{
		filters_redo_history.vector::clear();
	}

	void clear_filter_history()
	{
		filters_history.vector::clear();
	}

	void clear_undo_history()
	{
		undo_history.vector::clear();
	}

	void change_current_img(Mat img, filters *used_filters) // 1/4 ustawiamy nowy obrazek, np po filtrowaniu - wymagane wyczyszczenie redo, dodanie do undo i ustawienie current_img, dodajemy wskaznik na uzyty filtr
	{
		add_to_undo_history(current_img);
		clear_redo_history();
		set_current_img(img);
		add_to_filters_history(used_filters);
		clear_redo_filter_history();
	}

	void undo_current_img() // 2/4 dodajemy aktualny obrazek na stack redo, ustawiamy poprzedni obrazek jako aktualny, usuwamy obrazek ze stacku undo
	{
		if (undo_history.size() == 0)
			return;
		add_to_redo_history(current_img);
		set_current_img(undo_history.vector::back());
		remove_from_undo_history();
		add_to_redo_filter_history(filters_history.vector::back());
		remove_from_filters_history();
	}

	void redo_current_img() // 3/4 dodajemy aktualny obrazek na stack undo, ustawiamy "nastepny" obrazek jako aktualny, usuwamy obrazek ze stacku redo
	{
		if (redo_history.size() == 0)
			return;
		add_to_undo_history(current_img);
		set_current_img(redo_history.vector::back());
		remove_from_redo_history();
		add_to_filters_history(filters_redo_history.vector::back());
		remove_from_filters_redo_history();
	}
	
	void reset_current_img(Mat img)
	{
		clear_redo_filter_history();
		clear_filter_history();
		clear_redo_history();
		clear_undo_history();
		set_current_img(img);
	}
};

