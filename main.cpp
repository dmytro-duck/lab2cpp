#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "student.hpp"
#include "utils.hpp"

using namespace std;

// Отримати шлях до директорії
string getDirectory();

// Зчитує дані з усіх csv файлів в папці у вектор з studentIn
vector<studentIn> loadTable(string);

// Зберігає дані у таблицю
void saveTable(vector<studentOut>, string);

int main()
{
    string directory = getDirectory();
    vector<studentIn> table = loadTable(directory);
    vector<studentIn> table_budget = budgetStudents(table);
    vector<studentOut> table_rating = calcAverageMark(table_budget);
    sortingList(table_rating);
    cuttingList(table_rating);

    cout << "Мінімальна оцінка для стипендії це " << table_rating.back().avgRating << endl;

    saveTable(table_rating, "rating.csv");

    return 0;
}

string getDirectory()
{
    string directory;
    cout << "Введіть шлях папки з CSV фалами: ";
    getline(cin, directory);

    return directory;
}

vector<studentIn> loadCsv(string path)
{
    vector<studentIn> out;
    ifstream csv(path);
    string line;

    if (!csv.is_open())
    {
        cerr << "Не вдалося відкрити файл - \"" + path + "\"" << endl;
    }
    else
    {
        getline(csv, line); // пропускаємо перший рядок
        while (getline(csv, line))
            out.push_back(csv2studentIn(line));
    }
    csv.close();
    return out;
}

vector<studentIn> loadTable(string direcotry)
{
    vector<studentIn> out, tmp;
    vector<string> files = listFiles(direcotry, ".csv");
    for (string file : files)
    {
        tmp = loadCsv(file);
        out.insert(out.end(), tmp.begin(), tmp.end());
    }

    return out;
}

void saveTable(vector<studentOut> table_rating, string path)
{
    ofstream outcsv("./rating.csv");
    for (studentOut rating_student : table_rating)
    {
        outcsv << rating_student.surname << "," << rating_student.avgRating << endl;
    }
    outcsv.close();
}