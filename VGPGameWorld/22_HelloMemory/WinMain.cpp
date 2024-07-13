#include <../KEIEngine/Inc/KEIEngine.h>

using namespace KEIEngine;
using namespace KEIEngine::Core;

class Student
{
public:
	Student(const std::string& name)
		:mName(name)
		, mGrade(0)
	{

	}

	void SetGrade(int grade)
	{
		mGrade = grade;
	}

private:
	std::string mName;
	int mGrade;
};


int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 200);

	std::vector<Student*> students;
	for (uint32_t i = 0; i < 100; ++i)
	{
		std::string name = "Student" + std::to_string(i);
		students.push_back(studentPool.New(name));
	}

	// testing delete
	for (uint32_t i = 0; i < 20; ++i)
	{
		auto student = students.back();
		students.pop_back();
		studentPool.Delete(student);
	}

	// testing reuse
	for (uint32_t i = 0; i < 50; ++i)
	{
		std::string name = "Student_new" + std::to_string(i);
		students.push_back(studentPool.New(name));
	}

	// clear all
	for (auto student : students)
	{
		studentPool.Delete(student);
	}

	return(0);
}