//Academy
#include <iostream>
#include<fstream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-------------------------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	static const int TYPE_WIDTH = 12;
	static const int NAME_WIDTH = 12;
	static const int AGE_WIDTH = 5;
	static int count; //Объявление статической переменной
	std::string last_name;
	std::string first_name;
	int age;
public:
	static int get_count()
	{
		return count;
	}

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
		count++;
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		count--;
		cout << "HDestructor:\t" << this << endl;
	}
	//				Methods
	virtual std::ostream& info(std::ostream& os)const //Base class
	{
		os.width(TYPE_WIDTH); //Метод width(N) задает размер поля, в которое будет выведено значение
		os << std::left;
		os << std::string(strchr(typeid(*this).name(), ' ') + 1) + ":"; // strchr(const char* str, char symbol); в указанной строке (str) находит
		//указанный символ (symbol) и возвращает указатель на найденный символ или 'nullptr'
		//если указанный символ отсутствует в указанной строке
		//return os << last_name << "," << first_name << "," << age;
		os.width(NAME_WIDTH);
		os << last_name;
		os.width(NAME_WIDTH);
		os << first_name;
		os.width(AGE_WIDTH);
		os << age;
		return os;
	}

	virtual void print()const
	{
		cout << last_name << " " << first_name << " " << age;
	}
};

int Human::count = 0; //Инициализация статической переменной (относится к определению класса - class Definition)

std::ostream& operator << (std::ostream & os, const Human & obj)
{
	return obj.info(os);
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance


class Student :public Human
{
	static const int SPECIALITY_WIDTH = 32;
	static const int GROUP_WIDTH = 8;
	static const int RAT_WIDTH = 8;
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
		//return Human::info(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(GROUP_WIDTH);
		os << group;
		os.width(RAT_WIDTH);
		os << rating;
		os.width(RAT_WIDTH);
		os << attendance;
		return os;
	}

	void print()const override
	{
		Human::print();
		cout << " " << speciality << " " << group << " " << rating << " " << attendance;
	}

};

#define TEACHER_TAKE_PARAMETERS const std::string & speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher :public Human
{
	static const int SPECIALITY_WIDTH = 32;
	static const int EXPERIENCE_WIDTH = 5;
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
		//return Human::info(os) << " " << speciality << " " << experience;
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(EXPERIENCE_WIDTH);
		os << experience;
		return os;
	}

	void print()const override
	{
		Human::print();
		cout << " " << speciality << " " << experience;
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

	void print()const override
	{
		Student::print();
		cout << " " << supervisor << " " << topic << " " << grade << " " << subject;
	}
};

void Print(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		group[i]->info(cout);
		cout << delimiter << endl;
	}
	cout << "Количество объектов: " << group[0]->get_count() << endl;
	cout << "Количество объектов: " << Human::get_count() << endl;

}

void Save(Human* group[], const int n, const std::string& filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}

	fout.close();
	std::string cmd = "start notepad ";
	cmd += filename;
	system(cmd.c_str()); // Метод c_str возвращает строку в виде массива символов (char* );
}

Human** Load(const std::string& filename, int& n)
{
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//1) Подсчитаваем количество объектов в файле
		n = 0;
		std::string buffer;
		while (!fin.eof())
		{
			std::getline(fin, buffer);
			if (buffer.size() < 20) continue;
			n++;
		}
		cout << "Количество объектов: " << n << endl;

		//2) Выделяем память под объекты:
		group = new Human * [n];

		//3) Возвращаемся в начало файла, для того чтобы прочитать из него сами объекты:
		cout << "Position " << fin.tellg() << endl; //Метод tellg() возвращает текущую Get-позицию курсора на чтение. -1 конец файла
		fin.clear();
		fin.seekg(0); // Метод seekg(n) переводит Get-курсор (на чтение) в указанную позицию, которая 'n';
		cout << "Position " << fin.tellg() << endl; //Метод tellg() возвращает текущую Get-позицию курсора на чтение. -1 конец файла

		for (int i = 0; i < n; i++)
		{
			std::getline(fin, buffer, ':');
			//cout << buffer << endl;
			if (std::strcmp("Human", buffer.c_str()) == 0) group[i] = new Human("", "", 0);
			else if (std::strcmp("Student", buffer.c_str()) == 0) group[i] = new Student("", "", 0, "", "", 0, 0);
			else if (std::strcmp("Graduate", buffer.c_str()) == 0) group[i] = new Graduate("", "", 0, "", "", 0, 0, "", "", "", "");
			else if (std::strcmp("Teacher", buffer.c_str()) == 0) group[i] = new Teacher("", "", 0, "", 0);
			std::getline(fin, buffer);
			//cout << *group[i];
		}



	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	
	//) ? Закрываем файл
	fin.close();
	return group;
}

void Clear(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
		cout << delimiter << endl;
	}

}


//#define INHERITANCE
//#define POLYMORPHISM
//#define READ_FROM_FILE
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

	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
		cout << delimiter << endl;
	}
#endif // POLYMORPHISM

	int n = 0;
	Human** group = Load("group.txt", n);
	Print(group, n);
	Clear(group, n);

#ifdef READ_FROM_FILE
	std::ifstream fin("group.csv");
	const int G_SIZE = 15;
	int count_el = 0;
	Human* group[G_SIZE] = {};

	if (fin.is_open())
	{
		while (!fin.eof())
		{

			const int T_SIZE = 16;
			const int B_SIZE = 256;
			char* tokens[T_SIZE] = {};
			char* context = NULL;
			int count_token = 0;
			char buffer[B_SIZE] = {};
			char* ps;
			fin.getline(buffer, B_SIZE);
			ps = strtok_s(buffer, ",", &context);
			while (ps)
			{
				tokens[count_token++] = ps;
				ps = strtok_s(NULL, ",", &context);
			}

			switch (count_token)
			{
			case 3: group[count_el++] = new Human(tokens[0], tokens[1], atoi(tokens[2]));
				break;
			case 5: group[count_el++] = new Teacher(tokens[0], tokens[1], atoi(tokens[2]), tokens[3], atoi(tokens[4]));
				break;
			case 7: group[count_el++] = new Student(tokens[0], tokens[1], atoi(tokens[2]), tokens[3], tokens[4],
				atof(tokens[5]), atof(tokens[6]));
				break;
			case 11: group[count_el++] = new Graduate(tokens[0], tokens[1], atoi(tokens[2]), tokens[3], tokens[4],
				atof(tokens[5]), atof(tokens[6]), tokens[7], tokens[8], tokens[9], tokens[10]);
				break;

			}
		}
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	fin.close();

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		if (group[i] != nullptr)
		{
			group[i]->print();
			cout << delimiter << endl;
		}
	}

	for (int i = 0; i < count_el; i++)
	{
		delete group[i];
	}


#endif // READ_FROM_FILE



}

