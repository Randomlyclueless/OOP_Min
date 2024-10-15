#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Subject
{
private:
    string name;
    double marks;
    double credits;

public:
    Subject() : name(""), marks(0.0), credits(0.0) {}
    Subject(const string &n, double m, double c) : name(n), marks(m), credits(c) {}

    double getCredits() const { return credits; }
    double getGradePoints() const
    {
        if (marks >= 90)
            return 10;
        else if (marks >= 80)
            return 9;
        else if (marks >= 70)
            return 8;
        else if (marks >= 60)
            return 7;
        else if (marks >= 50)
            return 6;
        else if (marks >= 40)
            return 5;
        else
            return 0;
    }

    string getName() const { return name; }
    double getMarks() const { return marks; }

    void setValues(const string &n, double m, double c)
    {
        name = n;
        marks = m;
        credits = c;
    }
};

class Student
{
private:
    Subject *subjects;
    int totalSubjects;

public:
    Student(int numSubjects) : totalSubjects(numSubjects)
    {
        if (numSubjects <= 0)
            throw invalid_argument("Number of subjects must be positive.");
        subjects = new Subject[numSubjects];
    }

    ~Student() { delete[] subjects; }

    void addSubject(int index, const string &name, double marks, double credits)
    {
        if (index < 0 || index >= totalSubjects)
            throw out_of_range("Index out of range.");
        subjects[index].setValues(name, marks, credits);
    }

    double calculateGPA() const
    {
        double totalCredits = 0;
        double totalGradePoints = 0;

        for (int i = 0; i < totalSubjects; ++i)
        {
            totalCredits += subjects[i].getCredits();
            totalGradePoints += subjects[i].getGradePoints() * subjects[i].getCredits();
        }

        return totalCredits > 0 ? totalGradePoints / totalCredits : 0;
    }

    int getTotalCredits() const
    {
        int totalCredits = 0;
        for (int i = 0; i < totalSubjects; ++i)
        {
            totalCredits += static_cast<int>(subjects[i].getCredits());
        }
        return totalCredits;
    }

    void displaySubjects() const
    {
        cout << "\n| Subject Name     | Marks | Credits | Grade Points |\n";
        cout << "|-------------------|-------|---------|--------------|\n";
        for (int i = 0; i < totalSubjects; ++i)
        {
            cout << "| " << subjects[i].getName()
                 << string(18 - subjects[i].getName().length(), ' ')
                 << "| " << subjects[i].getMarks()
                 << string(6 - to_string((int)subjects[i].getMarks()).length(), ' ')
                 << "| " << subjects[i].getCredits()
                 << string(7 - to_string((int)subjects[i].getCredits()).length(), ' ')
                 << "| " << subjects[i].getGradePoints()
                 << string(12 - to_string((int)subjects[i].getGradePoints()).length(), ' ')
                 << "|\n";
        }
        cout << "|-------------------|-------|---------|--------------|\n";
    }
};

double getInput(const string &prompt, double minValue, double maxValue)
{
    double value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (!cin.fail() && value >= minValue && value <= maxValue)
        {
            cin.ignore(10000, '\n');
            return value;
        }
        else
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a value between " << minValue << " and " << maxValue << ".\n";
        }
    }
}

string getStringInput(const string &prompt)
{
    string value;
    cout << prompt;
    cin.ignore();
    getline(cin, value);
    return value;
}

int main()
{
    try
    {
        int totalSubjects;
        cout << "Enter the total number of subjects: ";
        cin >> totalSubjects;

        if (cin.fail() || totalSubjects <= 0)
        {
            throw invalid_argument("Invalid input. Please enter a positive integer for the number of subjects.");
        }

        Student student(totalSubjects);

        cout << "\n=====================\n";
        cout << "  Subject Details\n";
        cout << "=====================\n";

        for (int i = 0; i < totalSubjects; ++i)
        {
            string subjectName = getStringInput("Enter name for subject " + to_string(i + 1) + ": ");
            double marks = getInput("Enter marks for subject " + to_string(i + 1) + " (0-100): ", 0.0, 100.0);
            double credits = getInput("Enter credits for subject " + to_string(i + 1) + ": ", 1.0, 10.0);
            student.addSubject(i, subjectName, marks, credits);
        }

        student.displaySubjects();

        double GPA = student.calculateGPA();
        int totalCredits = student.getTotalCredits();

        cout << "\n=============================\n";
        cout << "  Summary of Results\n";
        cout << "=============================\n";
        cout << "Total Credits: " << totalCredits << endl;
        cout << "GPA out of 10: " << GPA << endl;
        cout << "=============================\n";
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
