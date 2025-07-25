﻿//Academy
#include <iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-------------------------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}

	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//					Constructors
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	//				Methods
	virtual std::ostream& info(std::ostream& os)const //Base class
	{
		return os << last_name << " " << first_name << " " << age;
	}
};

std::ostream& operator << (std::ostream & os, const Human & obj)
{
	return obj.info(os);
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance


class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating; //успеваемость
	double attendance; //посещаемость

public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//				Constructors
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//				Methods
	std::ostream& info(std::ostream& os)const override //Derived Class
	{
		return Human::info(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
	}

};

#define TEACHER_TAKE_PARAMETERS const std::string & speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher :public Human
{
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	//				Constructors
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	std::ostream& info(std::ostream& os)const override //Derived Class
	{
		return Human::info(os) << " " << speciality << " " << experience;
	}
};

#define GRADUATE_TAKE_PARAMETERS const std::string & supervisor, const std::string& topic, const std::string& grade, const std::string& subject
#define GRADUATE_GIVE_PARAMETERS supervisor, topic, grade, subject

class Graduate :public Student
{
	std::string supervisor;
	std::string topic;
	std::string grade;
	std::string subject;
public:
	const std::string& get_supervisor()const
	{
		return supervisor;
	}
	const std::string& get_topic()const
	{
		return topic;
	}
	const std::string& get_grade()const
	{
		return grade;
	}
	const std::string& get_subject() const
	{
		return subject;
	}
	void set_supervisor(const std::string& supervisor)
	{
		this->supervisor = supervisor;
	}
	void set_topic(const std::string& topic)
	{
		this->topic = topic;
	}
	void set_grade(const std::string& grade)
	{
		this->grade = grade;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}

	//					Constructors
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS)
		:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_supervisor(supervisor);
		set_topic(topic);
		set_grade(grade);
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	//					Methods
	std::ostream& info(std::ostream& os)const override //Derived Class
	{
		return Student::info(os) << " " << supervisor << " " << topic << " " << grade << " " << subject;
	}
};


//#define INHERITANCE
#define POLYMORPHISM
void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE
	Human human("Montana", "Antonio", 25);
	human.info();

	Student student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 98);
	student.info();

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.info();

	Graduate graduate("Arny", "GuessWhat", 22, "Physics", "BB", 99, 99, "IronMan", "Sentinel", "Bachelor", "Physics");
	graduate.info();
#endif // INHERITANCE

#ifdef POLYMORPHISM
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 98),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Arny", "GuessWhat", 22, "Physics", "BB", 99, 99, "IronMan", "Sentinel", "Bachelor", "Physics"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};

	std::ofstream fout("group.txt");
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		group[i]->info(cout);
		fout << *group[i] << endl;
		cout << delimiter << endl;
	}
	fout.close();
	system("notepad group.txt");
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
		cout << delimiter << endl;
	}
#endif // POLYMORPHISM


}

