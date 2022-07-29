#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include<string>
#include <windows.h>

using namespace std;


class Date {

	int day, month, year;

public:
	Date() {

		time_t t = time(0);
		tm* now = localtime(&t);
		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;

		cout << "конструктор без параметр≥в класу Date\n";

	}

	Date(int d, int m, int y) {

		day = d;
		month = m;
		year = y;

		cout << "конструктор з параметрами класу Date\n";
	}

	Date(Date& date) {

		day = date.day;
		month = date.month;
		year = date.year;

		cout << "конструктор коп≥й класу Date\n";
	}

	~Date() {
	
		cout << "деструктор класу Date\n";

	};

	int get_day() { return this->day; }
	int get_month() { return this->month; }
	int get_year() { return this->year; }
	Date& set_day(int d) { day = d; return *this; }
	Date& set_month(int m) { month = m; return *this; }
	Date& set_year(int y) { year = y; return *this; }
	void print() {

		if (this->day < 10) cout << '0' << this->day << '.';
		else cout << this->day << '.';

		if (this->month < 10) cout << '0' << this->month << '.';
		else cout << this->month << '.';

		if (this->year % 100 < 10) cout << '0' << this->year % 100;
		else cout << this->year % 100;

	}
};


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

	author(){
		
		name = "";
		surname = "";
		birth_day.set_day(0), birth_day.set_month(0), birth_day.set_year(0);
	
		cout << "конструктор без параметр≥в класу author\n";
	}

	author(string name_, string surname_, int day_, int month_, int year_){
		
		name = name_;
		surname = surname_;
		birth_day.set_day(day_); birth_day.set_month(month_); birth_day.set_year(year_);

		cout << "конструктор з параметрами класу author\n";
	
	}

	author(author& a) {
		
		name = a.name;
		surname = a.surname;
		birth_day = a.birth_day;
	
		cout << "конструктор коп≥й класу author\n";

	};

	~author() {
	
		cout << "деструктор класу author\n";
	
	};

	string get_name() { return this->name; }
	string get_surname() { return this->surname; }
	Date& get_date() { return this->birth_day; }
	author& set_name(string name_) { name = name_; return *this; }
	author& set_surname(string surname_) { surname = surname_; return *this; }
	author& set_date(int day_, int month_, int year_) { birth_day.set_day(day_); birth_day.set_month(month_); birth_day.set_year(year_); return *this; }
	void author_print() { cout << surname << " " << name << " (нар. "; birth_day.print(); cout << ");\n"; }
};


class article: public author {

	string name;
	int count;
	int fee;

public:

	article() : author() { name = ""; count = 0; fee = 0; cout << "конструктор без параметр≥в класу article\n"; }

	article(string author_name, string author_surname, int day, int month, int year, string article_name, int count_, int fee_):
		
		author(author_name, author_surname, day,month,year) {

		name = article_name;
		count = count_;
		fee = fee_;

		cout << "конструктор з параметрами класу article\n";
	}

	article(article& a): author(a.get_name(),a.get_surname(),a.get_date().get_day(), a.get_date().get_month(), a.get_date().get_year()) {

		name = a.name;
		count = a.count;
		fee = a.fee;
	
		cout << "конструктор коп≥й класу article\n";

	}

	~article() {
	
		cout << "деструктор класу article\n";
	}


	string get_name() { return this->name; }
	int get_count() { return this->count; }
	int get_fee() { return this->fee; }


	article& set_name(string name_) { name = name_; return *this; }

	article& set_count(int count_) { count = count_; return *this; }

	article& set_fee(int fee_) { fee = fee_; return *this; }

	void print() {
		cout << "назва: " << name + ";  " << "к-сть сор≥нок: " << count << "; гонорар: " << fee << "; автор: ";
		this->author_print();
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
		number_of_articles = 1;
		all_articles = new article[number_of_articles];

		cout << "конструктор без параметр≥в класу magazine\n";
	}

	magazine(period per_, string author_name, string author_surname, int day_, int month_, int year_, string magazine_name, int number_of_articles_, article* articles) {

		per = per_;
		auth.set_name(author_name);
		auth.set_surname(author_surname);
		auth.set_date(day_, month_, year_);
		name = magazine_name;

		number_of_articles = number_of_articles_;

		if(all_articles) delete[] all_articles;
		all_articles = new article[number_of_articles];

		for (int i = 0; i < number_of_articles; i++) {

			all_articles[i].set_date(articles[i].get_date().get_day(), articles[i].get_date().get_month(), articles[i].get_date().get_year());
			all_articles[i].set_name(articles[i].get_name());
			all_articles[i].set_surname(articles[i].get_surname());
			all_articles[i].set_count(articles[i].get_count());
			all_articles[i].set_fee(articles[i].get_fee());
			all_articles[i].set_name(articles[i].get_name());

			all_articles[i].set_count(articles[i].get_count());
			all_articles[i].set_fee(articles[i].get_fee());
			all_articles[i].set_name(articles[i].get_name());

		}


		cout << "конструктор з параметрами класу magazine\n";
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
		cout << "коструктор коп≥й класу magazine\n";
	}

	~magazine() {
		delete[] all_articles;
		cout << "деструктор класу magazine\n";
	}

	period get_period() { return this->per; }
	author get_auth() { return this->auth; }
	string get_name() { return this->name; }
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

		cout << "\nжурнал \"" << name << "\" публ≥куЇтьс€ що";

		switch (per) {

		case period::ev_month:
			cout << "м≥с€ц€, ";
			break;

		case period::ev_quorter:
			cout << "кварталу, ";
			break;

		case period::ev_week:
			cout << "тижн€, ";
			break;
		}

		cout << "автор - " << auth.get_surname() << " " << auth.get_name() << "(нар. ";
		auth.get_date().print();
		cout << ") к-сть статтей: " << number_of_articles << "\n\n";

		if (number_of_articles > 0) {

			cout << "статт≥, що вход€ть до журналу:\n";

			for (int i = 0; i < number_of_articles; i++) {
				cout << " -";
				all_articles[i].print();
			}

			cout << "\n";
		}

	}

	void short_print() {

		int count = 0;

		for (int i = 0; i < number_of_articles; i++) count += all_articles[i].get_count();

		cout << "∆урнал " << name << ", к-сть стор≥нок: " << count;

	}


	magazine& append(article value) {


		article* new_arr = new article[number_of_articles + 1];


		for (int i = 0; i < number_of_articles; i++) {

			new_arr[i].set_date(all_articles[i].get_date().get_day(), all_articles[i].get_date().get_month(), all_articles[i].get_date().get_year());
			new_arr[i].set_name(all_articles[i].get_name());
			new_arr[i].set_surname(all_articles[i].get_surname());
			new_arr[i].set_count(all_articles[i].get_count());
			new_arr[i].set_fee(all_articles[i].get_fee());
			new_arr[i].set_name(all_articles[i].get_name());

			new_arr[i].set_count(all_articles[i].get_count());
			new_arr[i].set_fee(all_articles[i].get_fee());
			new_arr[i].set_name(all_articles[i].get_name());

		}

		new_arr[number_of_articles].set_date(value.get_date().get_day(), value.get_date().get_month(), value.get_date().get_year());
		new_arr[number_of_articles].set_name(value.get_name());
		new_arr[number_of_articles].set_surname(value.get_surname());
		new_arr[number_of_articles].set_count(value.get_count());
		new_arr[number_of_articles].set_fee(value.get_fee());
		new_arr[number_of_articles].set_name(value.get_name());

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


	author auth("”сик", "ќлександр", 17, 1, 1987);
	auth.author_print();

	cout << "-------------------------------------------------------\n\n";

	article art("Ѕра€н", "ћей", 19, 7, 1947, "музика", 25, 10000);
	art.print();
	
	cout << "-------------------------------------------------------\n\n";

	art.author_print();

	cout << "-------------------------------------------------------\n\n";

	article mas[1] = {art};

	period period_ = period::ev_week;

	magazine cq(period_, "≤гор", "√аран≥н", 12,12 , 1976, "GQ", 1,mas);
	
	cout << "\n\n\n";
	cq.short_print();

	cout << "\n\n\-------------------------------------------------------\n\n";

	return 0;
}

