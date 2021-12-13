#include <iostream>
#include <cstddef>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <numeric>
#include <sstream>
#include <fstream>

using namespace std;

class Student
{
private:

    string name, surname;
    vector <double> nd;
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

    Student(string gname, string gsurname, vector <double> gnd, int gegz) {
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

    double countMED() {
        sort(nd.begin(), nd.end());

        if (nd.size() % 2 == 0) {
            galutinis = (nd[nd.size() / 2 - 1] + nd[nd.size() / 2]) / 2;
        }

        else {
            galutinis = nd[nd.size() / 2];
        }

        return galutinis;
    }

    void setStudent(string get_n, string get_surn, vector <double> get_nd, int get_egz) {
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

    double getGalutinisAVG(int ans) {
        if (ans == 1)
            countAVG();
        else if (ans == 2)
            countMED();
        return galutinis;
    }

    double getGalutinisMED() {
        countMED();
        return galutinis;
    }


};

int main()
{
    vector <string> vname, vsurname;
    vector <int> vegz;
    vector <double> nd;
    vector <vector <double>> vnd;
    string name = "", surname = "";
    int egz = 0, n, avgORmed, mokiniai = 0, gen, choice, file;

    cout << "Noredami duomenis nuskaityti is konsoles spauskite 1, noredami duomenis nuskaityti is failo, spauskite 2: ";
    cin >> file;

    if (file == 1) {
        cout << "Iveskite mokiniu kieki: ";
        cin >> mokiniai;

        Student* st = new Student[mokiniai];

        cout << "Jeigu norite ivesti duomenis rankiniu budu spauskite 1, jei norite, kad duomenys butu generuojami, spauskite 2: ";
        cin >> choice;

        if (choice == 1) {

            for (int i = 1; i <= mokiniai; i++) {
                cout << "Iveskite " << i << " studento varda : ";
                cin >> name;
                cout << "Iveskite " << i << "  studento pavarde: ";
                cin >> surname;
                cout << "Iveskite " << i << " studento namu darbu pazymiu kieki: ";
                cin >> n;

                vname.push_back(name);
                vsurname.push_back(surname);

                cout << "Jeigu norite ivesti pazymius rankiniu budu studentui nr. " << i << " spauskite 1" << endl << "Jeigu norite sugeneruoti atsitiktinius pazymius studentui nr. " << i << "  spauskite 2" << endl;
                cin >> gen;

                if (gen == 1) {
                    for (int j = 1; j <= n; j++) {
                        cout << "Iveskite " << j << " pazymi: ";
                        int temp;
                        cin >> temp;
                        nd.push_back(temp);
                    }
                    cout << "Iveskite " << i << " studento egzamino vertinimo pazymi: ";
                    cin >> egz;
                    vegz.push_back(egz);
                }
                else if (gen == 2) {
                    for (int j = 1; j <= n; j++)
                        nd.push_back(rand() % 10 + 1);
                    vnd.push_back(nd);
                    egz = rand() % 10 + 1;
                    vegz.push_back(egz);
                }

                nd.clear();
            }

            

            for (int i = 0; i < mokiniai; i++) {
                st[i].setStudent(vname[i], vsurname[i], vnd[i], vegz[i]);
            }
        }

        else if (choice == 2) {
            stringstream ss;

            cout << "Kiek namu darbu pazymiu tures visi mokiniai? ";
            cin >> n;

            for (int i = 1; i <= mokiniai; i++) {

                ss << "Vardas" << i;
                name = ss.str();
                ss.str(string());
                ss << "Pavarde" << i;
                surname = ss.str();
                ss.str(string());

                for (int j = 0; j < mokiniai; j++)
                    nd.push_back(rand() % 10 + 1);

                egz = rand() % 10 + 1;

                st[i - 1].setStudent(name, surname, nd, egz);

                nd.clear();
            }

        }

        cout << "Jeigu norite skaiciuoti pagal Vidurki spauskite 1" << endl << "Jeigu norite skaiciuoti pagal Mediana spauskite 2" << endl;
        cin >> avgORmed;

        if (avgORmed == 1 || avgORmed == 2) {
            cout << endl << setw(20) << left << "Pavarde" << setw(20) << left << "Vardas";
            if (avgORmed == 1) cout << setw(5) << left << "Galutinis (Vid.)" << endl;
            else if (avgORmed == 2) cout << setw(5) << left << "Galutinis (Med.)" << endl;
            cout << "--------------------------------------------------\n";
            for (int i = 1; i <= mokiniai; i++) {
                cout << setw(20) << left << st[i - 1].getSurname() << setw(20) << left << st[i - 1].getName() << setw(5) << left << fixed << setprecision(2) << st[i - 1].getGalutinisAVG(avgORmed) << left << endl;
            }
        }
    }

    else if (file == 2) { // read from file
        string txt;

        ifstream kursiokai("../kursiokai.txt");

        for (int i = 0; getline(kursiokai, txt); i++) {
            mokiniai++;
            int temp;

            kursiokai >> name >> surname;
            vname.push_back(name);
            vsurname.push_back(surname);
            
            for (int j = 0; j < 5; j++) {
                kursiokai >> temp;
                nd.push_back(temp);
            }
            vnd.push_back(nd);

            kursiokai >> egz;
            vegz.push_back(egz);

            cout << i + 1 << endl;
        }
        // eof

        Student* st = new Student[mokiniai];

        for (int i = 0; i < mokiniai; i++) 
            st[i].setStudent(vname[i], vsurname[i], vnd[i], vegz[i]);

        cout << "Jeigu norite skaiciuoti pagal Vidurki spauskite 1" << endl << "Jeigu norite skaiciuoti pagal Mediana spauskite 2" << endl;
        cin >> avgORmed;

        if (avgORmed == 1 || avgORmed == 2) {
            cout << endl << setw(20) << left << "Pavarde" << setw(20) << left << "Vardas";
            if (avgORmed == 1) cout << setw(5) << left << "Galutinis (Vid.)" << endl;
            else if (avgORmed == 2) cout << setw(5) << left << "Galutinis (Med.)" << endl;
            cout << "--------------------------------------------------\n";
            for (int i = 1; i <= mokiniai; i++) {
                cout << setw(20) << left << st[i - 1].getSurname() << setw(20) << left << st[i - 1].getName() << setw(5) << left << fixed << setprecision(2) << st[i - 1].getGalutinisAVG(avgORmed) << left << endl;
            }
        }
    }

    

    else cout << "ARBA 1 ARBA 2!";

    return 0;
}