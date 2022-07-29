#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include<string>
#include <windows.h>

using namespace std;

class Date{
	
	int day, month, year;

public:
	Date();
	Date(int, int, int);
	Date(Date&);
	~Date() {} ;
	void print();
	int get_day() { return this->day; }
	int get_month() { return this->month; }
	int get_year() { return this->year; }
	Date& set_day(int d) { day = d; return *this; }
	Date& set_month(int m) { month = m; return *this; }
	Date& set_year(int y) { year = y; return *this; }
};

Date::Date(){
	time_t t = time(0);
	tm* now = localtime(&t);
	year = now->tm_year +1900;
	month = now->tm_mon + 1;
	day = now->tm_mday;
}

Date::Date(int d, int m, int y) {
	day = d;
	month = m;
	year = y;
}

Date::Date(Date& date) {
	day = date.day;
	month = date.month;
	year = date.year;
}


void Date::print() {

	if (this->day < 10) cout << '0' << this->day << '.';
	else cout << this->day << '.';

	if (this->month < 10) cout << '0' << this->month << '.';
	else cout << this->month << '.';
	
	if (this->year % 100 < 10) cout << '0' << this->year % 100;
	else cout << this->year % 100 ;

}



enum period {
	ev_week,
	ev_month,
	ev_quorter
};

class author {

	string name;
	string surname;
	Date birth_day;

public:

	author() { name = ""; 	surname = ""; birth_day.set_day(0), birth_day.set_month(0), birth_day.set_year(0); }
	author(string name_, string surname_, int day_, int month_, int year_) { name = name_; surname = surname_; birth_day.set_day(day_); birth_day.set_month(month_); birth_day.set_year(year_);}
	author(author& a) { name = a.name; surname = a.surname; birth_day = a.birth_day; };
	~author() {};
	string get_name() { return this->name; }
	string get_surname() { return this->surname; }
	Date& get_date() { return this->birth_day; }
	author& set_name(string name_) { name = name_; return *this;  }
	author& set_surname(string surname_) { surname = surname_; return *this; }
	author& set_date(int day_, int month_, int year_) {birth_day.set_day(day_); birth_day.set_month(month_); birth_day.set_year(year_); return *this;}
	void print() { cout << surname << " " << name << " (нар. "; birth_day.print(); cout << ");\n"; }
};


class article {

	author auth;
	string name;
	int count;
	int fee;

public:

	article() { auth.set_name(""); auth.set_surname(""); auth.set_date(0, 0, 0); name = ""; count = 0; fee = 0; }

	article(string author_name, string author_surname, int day, int month, int year, string article_name, int count_, int fee_) {
		auth.set_name(author_name);
		auth.set_surname(author_surname);
		auth.set_date(day, month, year);
		name = article_name;
		count = count_;
		fee = fee_;
	}

	article(article& a) {
		auth = a.auth;
		name = a.name;
		count = a.count;
		fee = a.fee;
	}

	~article(){}


	author get_author() { return this->auth; }
	string get_name() { return this->name; }
	int get_count() { return this->count; }
	int get_fee() { return this->fee; }

	article& set_author(string name_, string surname_, int day_, int month_, int year_) {
		auth.set_date(day_, month_, year_);
		auth.set_name(name_);
		auth.set_surname(surname_);

		return *this;
	}

	article& set_name(string name_) {name = name_; return *this;}

	article& set_count(int count_)  { count = count_; return *this; }

	article& set_fee(int fee_) { fee = fee_; return *this; }

	void print() {
		cout << "назва: " << name + ";  " << "к-сть сорінок: " << count << "; гонорар: " << fee << "; автор: ";
		auth.print();
	}


 };


class magazine {

	period per;
	author auth;
	string name;
	int number_of_articles;
	article* all_articles;

public:

	magazine() {
		per = period::ev_week;
		auth.set_date(0, 0, 0);
		auth.set_name("");
		auth.set_surname("");
		name = "";
		number_of_articles = 0;
		all_articles = new article[number_of_articles];
	}

	magazine(period per_, string author_name, string author_surname, int day_, int month_, int year_, string magazine_name, int number_of_articles_, article *articles) {
		
		per = per_;
		auth.set_name(author_name);
		auth.set_surname(author_surname);
		auth.set_date(day_, month_, year_);
		name = magazine_name;


		number_of_articles = number_of_articles_;

		all_articles = articles;


	}

	magazine(magazine& a) {
		per = a.per;
		
		auth.set_name(a.auth.get_name());
		auth.set_surname(a.auth.get_surname());
		auth.set_date(a.auth.get_date().get_day(), a.auth.get_date().get_month(), a.auth.get_date().get_year());

		name = a.name;

		number_of_articles = a.number_of_articles;


		all_articles = new article[number_of_articles];
		for (int i = 0; i < number_of_articles; i++) all_articles[i] = a.all_articles[i];
	}

	~magazine() {
		delete[] all_articles;
	}

	period get_period() { return this->per; }
	author get_auth() { return this->auth; }
	string get_name(){ return this->name; }
	int get_number_of_articles() { return this->number_of_articles; }
	article* get_all_articles() { return this->all_articles; }

	magazine& set_period(period per_) { per = per_; return *this; }
	magazine& set_auth(string name_, string surname_, int day_, int month_, int year_) {
		auth.set_date(day_, month_, year_);
		auth.set_name(name_);
		auth.set_surname(surname_);
		
		return *this;
	}
	magazine& set_name(string name_) {
		name = name_;
		return *this;
	}
	magazine& set_array_of_articles(int number_of_articles_, article* arr) {

		number_of_articles = number_of_articles_;

		if (all_articles) delete[] all_articles;

		for (int i = 0; i < number_of_articles; i++) all_articles[i] = arr[i];
	}

	void full_print() {
		
		cout << "\nжурнал \"" << name << "\" публікується що";

		switch (per) {

		case period::ev_month:
			cout << "місяця, ";
			break;

		case period::ev_quorter:
			cout << "кварталу, ";
			break;

		case period::ev_week:
			cout << "тижня, ";
			break;
		}

		cout << "автор - " << auth.get_surname() << " " << auth.get_name() << "(нар. ";
		auth.get_date().print();
		cout << ") к-сть статтей: " << number_of_articles << "\n\n";

		if (number_of_articles > 0) {
			
			cout << "статті, що входять до журналу:\n";

			for (int i = 0; i < number_of_articles; i++) { 
				cout << " -";
				all_articles[i].print(); }
            
			cout << "\n";
		}

	}

	void short_print() {

		int count = 0;

		for (int i = 0; i < number_of_articles; i++) count += all_articles[i].get_count();

		cout << "Журнал " << name << ", к-сть сторінок: " << count;

	}


	magazine& append(article value) {

		
		article *new_arr = new article[number_of_articles+1];

		
		for (int i = 0; i < number_of_articles ; i++) {
		
			new_arr[i].set_author(
				all_articles[i].get_author().get_name(),
				all_articles[i].get_author().get_surname(),
				all_articles[i].get_author().get_date().get_day(),
				all_articles[i].get_author().get_date().get_month(),
				all_articles[i].get_author().get_date().get_year());

			new_arr[i].set_count(all_articles[i].get_count());
			new_arr[i].set_fee(all_articles[i].get_fee());
			new_arr[i].set_name(all_articles[i].get_name());

		}


		
		new_arr[number_of_articles].set_author(
			value.get_author().get_name(),
			value.get_author().get_surname(),
			value.get_author().get_date().get_day(),
			value.get_author().get_date().get_month(),
			value.get_author().get_date().get_year());

		new_arr[number_of_articles].set_count(value.get_count());
		new_arr[number_of_articles].set_fee(value.get_fee());
		new_arr[number_of_articles].set_name(value.get_name());
		

		delete[] all_articles;
		
		all_articles = new_arr;
	
		number_of_articles++;

		return *this;

	}



};



int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	magazine magazine1;
	cout << "magazine1\nfull print:";

	magazine1.full_print();

	cout << "\nshort print:\n";

	magazine1.short_print();

	cout << "\n\n--------------------------------------------------------------------\n\n";

	
	string name = "", surname = "", name_ = "";
	int day = 0, month = 0, year = 0, count = 0, fee = 0, p = 0;

	period period_;

	cout << "Введіть інформацію про статтю(фамілія,ім\'я автора/дату його народження/назву/к-сть стор./гонорар):\n";
	
	article* article_arr = new article[2];

	for (int i = 0; i < 2; i++) {

		cin >> surname >> name >> day >> month >> year >> name_ >> count >> fee;
		article_arr[i].set_author(name, surname, day, month, year);
		article_arr[i].set_count(count);
		article_arr[i].set_fee(fee);
		article_arr[i].set_name(name_);
	}


	cout << "\n\n";

	cout << "\nВведіть назву журналу, фамілію та ім\'я автора, дату його народження, а також періодичнсть, з якою він виходить(т/м/к):\n";

	cin >> name_ >> surname >> name >> day >> month >> year >> p;

	switch (p) {

	case(0): 
		period_ = period::ev_week;
		break;
	case(1):
		period_ = period::ev_month;
		break;
	case(2):
		period_ = period::ev_quorter;
	}
	
	magazine magazine2(period_,name,surname,day,month,year,name_,2,article_arr);

	cout << "\nmagazine2:\n\nfull print:\n";
	magazine2.full_print();

	cout << "\nshort print:\n\n";

	magazine2.short_print();

	cout << "\n\n--------------------------------------------------------------------\n\n";

	cout << "\nmagazine3:\n\nfull print:\n";
	magazine magazine3(magazine2);

	magazine3.full_print();

	cout << "\nshort print:\n\n";

	magazine3.short_print();


	cout << "\n\n--------------------------------------------------------------------\n\n";

	cout << "Введіть інформацію про статтю(фамілія,ім\'я автора/дату його народження/назву/к-сть стор./гонорар):\n";
	
	cin >> surname >> name >> day >> month >> year >> name_ >> count >> fee;

	article article1(name, surname, day, month, year, name_, count, fee);

	magazine3.append(article1);
	
	cout << "\n\nfull print:\n";

	magazine3.full_print();

	cout << "\nshort print:\n\n";

	magazine3.short_print();

	return 0;
	}

/*
Козак Назар 8 8 2003 програмування 25 1800
Мей Браян 19 7 1947 музика 13 2000

CQ Нельсон Джимм  8 3 1963 0

Усик Олександр 17 1 1987 бокс 10 2000
*/