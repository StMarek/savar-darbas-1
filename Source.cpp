#include <iostream>
#include <cstddef>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <numeric>

using namespace std;

class Student
{
private:

    string name, surname;
    vector <int> nd;
    int egz, avg;
    double galutinis;

    char* cstring;
    Student(const char* s, size_t n)
        : cstring(new char[n])
    {
        memcpy(cstring, s, n);
    }
public:
    Student(const char* s = "")
        : Student(s, strlen(s) + 1)
    {}

    Student(string gname, string gsurname, vector <int> gnd, int gegz) {
        name = gname;
        surname = gsurname;
        nd = gnd;
        egz = gegz;
    }

    ~Student()
    {
        delete[] cstring;
    }
    Student(const Student& other)
        : Student(other.cstring)
    {}
    Student& operator=(const Student& other)
    {
        if (this == &other) return *this;
        size_t n{ strlen(other.cstring) + 1 };
        char* new_cstring = new char[n];
        memcpy(new_cstring, other.cstring, n);
        delete[] cstring;
        cstring = new_cstring;
        return *this;
    }
public:
    operator const char* () const { return cstring; }

public:
    void countAVG() {

        double sum = accumulate(nd.begin(), nd.end(), 0);
        double avg = sum / nd.size();

        double nd_vid = avg * 0.4;
        galutinis = nd_vid + (egz * 0.6);
    }

    void setStudent(string get_n, string get_surn, vector <int> get_nd, int get_egz) {
        name = get_n;
        surname = get_surn;
        nd = get_nd;
        egz = get_egz;
    }

    string getName() {
        return name;
    }

    string getSurname() {
        return surname;
    }
    double getGalutinis() {
        countAVG();
        return galutinis;
    }
};

int main()
{
    string name = "", surname = "";
    vector <int> nd;
    int egz = 0, n;
    Student st1{ "" }, st2;

    cout << "Iveskite 1 studento varda: ";
    cin >> name;
    cout << "Iveskite 1 studento pavarde: ";
    cin >> surname;
    cout << "Iveskite 1 studento namu darbu pazymiu kieki: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Iveskite " << i + 1 << " pazymi: ";
        int temp;
        cin >> temp;
        nd.push_back(temp);
    }

    cout << "Iveskite 1 studento egzamino vertinimo pazymi: ";
    cin >> egz;

    st1.setStudent(name, surname, nd, egz);
    nd.clear();

    cout << "Iveskite 2 studento varda: ";
    cin >> name;
    cout << "Iveskite 2 studento pavarde: ";
    cin >> surname;
    cout << "Iveskite 2 studento namu darbu pazymiu kieki: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Iveskite " << i + 1 << " pazymi: ";
        int temp;
        cin >> temp;
        nd.push_back(temp);
    }

    cout << "Iveskite 2 studento egzamino vertinimo pazymi: ";
    cin >> egz;

    st2.setStudent(name, surname, nd, egz);

    cout << endl << setw(15) << left << "Pavarde" << setw(15) << left << "Vardas" << setw(5) << left << "Galutinis (Vid.)" << endl;
    cout << "--------------------------------------------------\n";
    cout << setw(15) << left << st1.getSurname() << setw(15) << left << st1.getName() << setw(5) << left << fixed << setprecision(2) << st1.getGalutinis() << endl;
    cout << setw(15) << left << st2.getSurname() << setw(15) << left << st2.getName() << setw(5) << left << st2.getGalutinis() << endl;

}