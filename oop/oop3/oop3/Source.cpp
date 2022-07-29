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

		//cout << "конструктор без параметрів класу Date\n";
		
	day = 0;
	month = 0;
	year = 0;
	}
	
	Date(int d, int m, int y) {

		day = d;
		month = m;
		year = y;

		//cout << "конструктор з параметрами класу Date\n";
	}
	
	~Date() {

		//cout << "деструктор класу Date\n";

	};

	int get_day() { return this->day; }
	int get_month() { return this->month; }
	int get_year() { return this->year; }
	Date& set_day(int d) { day = d; return *this; }
	Date& set_month(int m) { month = m; return *this; }
	Date& set_year(int y) { year = y; return *this; }
	friend ostream& operator<< (ostream&, Date&);
	friend istream& operator >> (istream&, Date&);
	void print() {

		if (this->day < 10) cout << '0' << this->day << '.';
		else cout << this->day << '.';

		if (this->month < 10) cout << '0' << this->month << '.';
		else cout << this->month << '.';

		if (this->year % 100 < 10) cout << '0' << this->year % 100;
		else cout << this->year % 100;

	}

	
	Date operator-(Date& dd) {
		
		Date temp;

		temp.day = this->day - dd.day;
		temp.month = this->month - dd.month;
		temp.year = this->year - dd.year;

		return temp;
	}

};


enum period {
	ev_week,
	ev_month,
	ev_quorter
};


class author {

	string aname;
	string surname;
	Date birth_day;

public:

	author() {

		aname = "";
		surname = "";
		birth_day.set_day(0), birth_day.set_month(0), birth_day.set_year(0);

		//cout << "конструктор без параметрів класу author\n";
	}

	author(string name_, string surname_, int day_, int month_, int year_) {

		aname = name_;
		surname = surname_;
		birth_day.set_day(day_); birth_day.set_month(month_); birth_day.set_year(year_);

		//cout << "конструктор з параметрами класу author\n";

	}

	author(author& a) {

		aname = a.aname;
		surname = a.surname;
		birth_day = a.birth_day;

		//cout << "конструктор копій класу author\n";

	};

	virtual ~author() {

		//cout << "деструктор класу author\n";

	};

	string get_aname() { return this->aname; }
	string get_surname() { return this->surname; }
	Date& get_date() { return this->birth_day; }
	//author& set_name(string name_) { name = name_; return *this; }
	author& set_aname(string name__) { aname = name__; return *this; }
	author& set_surname(string surname_) { surname = surname_; return *this; }
	author& set_date(int day_, int month_, int year_) { birth_day.set_day(day_); birth_day.set_month(month_); birth_day.set_year(year_); return *this; }
	friend ostream& operator<< (ostream&, author&);
	friend istream& operator >> (istream&, author&);
	//friend ostream& operator << (ostream, author&);


	virtual void print() { cout << surname << " " << aname << " (нар. "; birth_day.print(); cout << ");\n"; }



	bool operator == (author& aa) {

		if (this->aname != aa.aname) return false;
		if (this->surname != aa.surname) return false;
		if (this->birth_day.get_day() != aa.birth_day.get_day()) return false;
		if (this->birth_day.get_month() != aa.birth_day.get_month()) return false;
		if (this->birth_day.get_year() != aa.birth_day.get_year()) return false;

		return true;
	}

	bool operator != (author& aa) {

		return !(*this == aa);
	}

	
};


class article : public author {

	string name;
	int count;
	int fee;

public:

	article() : author() { name = ""; count = 0; fee = 0; /*cout << "конструктор без параметрів класу article\n";*/ }

	article(string author_name, string author_surname, int day, int month, int year, string article_name, int count_, int fee_) :

		author(author_name, author_surname, day, month, year) {

		name = article_name;
		count = count_;
		fee = fee_;

		//cout << "конструктор з параметрами класу article\n";
	}

	article(article& a) : author(a.get_aname(), a.get_surname(), a.get_date().get_day(), a.get_date().get_month(), a.get_date().get_year()) {

		name = a.name;
		count = a.count;
		fee = a.fee;

		//cout << "конструктор копій класу article\n";

	}

	~article() {

		//cout << "деструктор класу article\n";
	}


	string get_name() { return this->name; }
	int get_count() { return this->count; }
	int get_fee() { return this->fee; }


	article& set_name(string name_) { name = name_; return *this; }

	article& set_count(int count_) { count = count_; return *this; }

	article& set_fee(int fee_) { fee = fee_; return *this; }


	bool operator < (article& aa) {
		
		if (this->count < aa.count) return true;

		return false;
	}
	
	bool operator > (article& aa) {

		if (this->count > aa.count) return true;

		return false;
	}

	
	void print() {
		cout << "назва: " << name + ";  " << "к-сть сорінок: " << count << "; гонорар: " << fee << "; автор: " << this->get_surname() << " " << this->get_aname() << "\n";
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
		auth.set_aname("");
		auth.set_surname("");
		name = "";
		number_of_articles = 1;
		all_articles = new article[number_of_articles];

		//cout << "конструктор без параметрів класу magazine\n";
	}

	magazine(period per_, string author_name, string author_surname, int day_, int month_, int year_, string magazine_name, int number_of_articles_, article* articles) {

		per = per_;
		auth.set_aname(author_name);
		auth.set_surname(author_surname);
		auth.set_date(day_, month_, year_);
		name = magazine_name;

		number_of_articles = number_of_articles_;

		if (all_articles) delete[] all_articles;
		all_articles = new article[number_of_articles];

		for (int i = 0; i < number_of_articles; i++) {

			all_articles[i].set_date(articles[i].get_date().get_day(), articles[i].get_date().get_month(), articles[i].get_date().get_year());
			all_articles[i].set_aname(articles[i].get_aname());
			all_articles[i].set_surname(articles[i].get_surname());
			all_articles[i].set_count(articles[i].get_count());
			all_articles[i].set_fee(articles[i].get_fee());
			all_articles[i].set_name(articles[i].get_name());

			all_articles[i].set_count(articles[i].get_count());
			all_articles[i].set_fee(articles[i].get_fee());
			//all_articles[i].set_name(articles[i].get_name());

		}


		//cout << "конструктор з параметрами класу magazine\n";
	}

	magazine(magazine& a) {
		per = a.per;

		auth.set_aname(a.auth.get_aname());
		auth.set_surname(a.auth.get_surname());
		auth.set_date(a.auth.get_date().get_day(), a.auth.get_date().get_month(), a.auth.get_date().get_year());

		name = a.name;

		number_of_articles = a.number_of_articles;


		all_articles = new article[number_of_articles];
		for (int i = 0; i < number_of_articles; i++) all_articles[i] = a.all_articles[i];
		//cout << "коструктор копій класу magazine\n";
	}

	~magazine() {
		delete[] all_articles;
		//cout << "деструктор класу magazine\n";
	}

	period get_period() { return this->per; }
	author get_auth() { return this->auth; }
	string get_name() { return this->name; }
	int get_number_of_articles() { return this->number_of_articles; }
	article* get_all_articles() { return this->all_articles; }

	magazine& set_period(period per_) { per = per_; return *this; }
	magazine& set_auth(string name_, string surname_, int day_, int month_, int year_) {
		auth.set_date(day_, month_, year_);
		auth.set_aname(name_);
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

		cout << "автор - " << auth.get_surname() << " " << auth.get_aname() << "(нар. ";
		auth.get_date().print();
		cout << ") к-сть статтей: " << number_of_articles << "\n\n";

		if (number_of_articles > 0) {

			cout << "статті, що входять до журналу:\n";

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

		cout << "Журнал " << name << ", к-сть сторінок: " << count;

	}


	magazine& append(article value) {


		article* new_arr = new article[number_of_articles + 1];


		for (int i = 0; i < number_of_articles; i++) {

			new_arr[i].set_date(all_articles[i].get_date().get_day(), all_articles[i].get_date().get_month(), all_articles[i].get_date().get_year());
			new_arr[i].set_aname(all_articles[i].get_aname());
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

	article& operator [] (int i) {
		return all_articles[i];
	}


	friend istream& operator >> (istream& in, author& auth) {

		int day_, month_, year_;
		string aname_, surname_;

		in >> day_ >> month_ >> year_ >> aname_ >> surname_;

		auth.set_aname(aname_);
		auth.set_surname(surname_);
		auth.set_date(day_, month_, year_);
		return in;
	}

	friend ostream& operator<< (ostream& out, author& auth) {

		out << auth.surname << " " << auth.aname << "(" << "нар. " << auth.birth_day.get_day()<< "." << auth.birth_day.get_month() << "." << auth.birth_day.get_year() << ")" << "\n";
		
		return out;
	}

	friend istream& operator >> (istream& in , Date& d_) {

		int day_, month_, year_;
		in >> day_ >> month_ >> year_;

		d_.set_day(day_);
		d_.set_month(month_);
		d_.set_year(year_);

		return in;
	}

	friend ostream& operator<< (ostream& out, Date& d_) {

		out << "(" << d_.day << "." << d_.month << "." << d_.year << ")" << "\n";

		return out;
	}

};



int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	//оператор - для Date

	cout << "оператор - для Date:\n";
	Date a(1, 1, 1), b(2, 2, 2);
	Date c = a - b;

	a.print(); cout << " - "; b.print(); cout << " = "; c.print();

	cout << "\n";

	//логічні оператори < > для article

	article art1("Віталій", "Статкевич", 27, 12, 1990, "комбінаторика", 29, 1200);
	article art2("Юрій", "Бохонов", 27, 12, 1965, "матриці", 25, 1000);
	article art3("Олександр", "Усик", 27, 12, 2021, "бокс", 29, 1200);

	cout << "\nлогічні оператори < > для article:\n";

	if(art1 < art2) cout << "|art1 < art2| = 1\n";
	else cout << "|art1 < art2| = 0\n";

	if (art1 < art3) cout << "|art1 < art3| = 1\n";
	else cout << "|art1 < art3| = 0\n";

	if (art1 > art2) cout << "|art1 > art2| = 1\n";
	else cout << "|art1 > art2| = 0\n";

	//логічні оператори ==  != для author

	cout << "\nлогічні оператори ==  != для author:\n";

	author auth1("Назар", "Козак", 8, 8, 2003);
	author auth2("Назар", "Кощак", 8, 8, 2003);
	author auth3("Назар", "Козак", 8, 8, 2003);


	if (auth1 == auth2) cout << "|auth1 == auth2| = 1\n";
	else cout << "|auth1 == auth2| = 0\n";

	if (auth1 == auth3) cout << "|auth1 == auth3| = 1\n";
	else cout << "|auth1 == auth3| = 0\n";

	if (auth1 != auth2) cout << "|auth1 != auth2| = 1\n";
	else cout << "|auth1 != auth2| = 0\n";

	if (auth1 != auth3) cout << "|auth1 != auth3| = 1\n";
	else cout << "|auth1 != auth3| = 0\n";

	//оператор індексації для magazine

	cout << "\nоператор індексації для magazine:\n";

	article mas[3] = {art1, art2, art3};

	magazine gq(period::ev_week, "Ігор", "Гаранін", 12, 12, 1976, "GQ", 3, mas);

	gq[0].print(); 
	gq[1].print();
	gq[2].print();
	cout << "\n";

	//оператор <<  >>  для author

	cout << "оператор <<  >>  для author:\n";

	author auth4;
	cin >> auth4;
	cout << auth4;
	cout << "\n";

	cout << "оператор <<  >>  для Date:\n";

	Date d;
	cin >> d;
	cout << d;
	cout << "\n";

	cout << "віртуальні функції: \n";
	
	art1.print();
	auth1.print();

	cout << "\n\n";
	return 0;
}