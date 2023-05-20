// ЮФУ ИКТИБ МОП ЭВМ
// Программирование и Основы Теории Алгоритмов 2
// Индивидуальное задание № 4 Проектирование и реализация нормального алгоритма Маркова
// КТбо1-7 Черноусов Даниил Владимирович 

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

typedef struct Machine
    {
    string whatToReplace;
    string replaceTo;
    bool ifEnd;
    } Machine;

int init(Machine* ptr_m)
    {
    ifstream fin("input.txt");
    int cnt, cntFinites, state;
    fin >> cnt;
    for (int i = 0; i < cnt; i++)
        {
        fin >> ptr_m[i].whatToReplace >> ptr_m[i].replaceTo;
        ptr_m[i].ifEnd = true;
        }
    fin >> cntFinites;
    for (int i = 0; i < cntFinites; i++)
        {
        fin >> state;
        ptr_m[state - 1].ifEnd = false;
        }
    return cnt;
    }

string transition(Machine* ptr_m, string str, int cntStates, bool* mar2)
    {
    string s;
    s = str;
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < cntStates; i++)
        {
        if (ptr_m[i].whatToReplace == "_")
            {
            str = ptr_m[i].replaceTo + str;
            *mar2 = ptr_m[i].ifEnd;
            cout << "(" << i + 1 << ") ";
            for (int k = 0; k < s.size(); k++) { cout << s[k]; }
            cout << " -> ";
            for (int k = 0; k < str.size(); k++)
                {
                if (k < ptr_m[i].replaceTo.size())
                    {
                    SetConsoleTextAttribute(hConsoleHandle, 4);
                    cout << str[k];
                    }
                else
                    {
                    cout << str[k];
                    }
                SetConsoleTextAttribute(hConsoleHandle, 15);
                }
            cout << endl;
            return str;
            }
        if (str.find(ptr_m[i].whatToReplace) <= str.size())
            {
            if (ptr_m[i].replaceTo == "_")
                {
                str.erase(str.find(ptr_m[i].whatToReplace), ptr_m[i].whatToReplace.size());
                cout << "(" << i + 1 << ") ";
                for (int k = 0; k < s.size(); k++)
                    {
                    if (k >= s.find(ptr_m[i].whatToReplace) && k < s.find(ptr_m[i].whatToReplace) + ptr_m[i].whatToReplace.size())
                        {
                        SetConsoleTextAttribute(hConsoleHandle, 4);
                        cout << s[k];
                        }
                    else
                        {
                        cout << s[k];
                        }
                    SetConsoleTextAttribute(hConsoleHandle, 15);
                    }
                cout << " -> ";
                for (int k = 0; k < str.size(); k++) { cout << str[k]; }
                cout << endl;
                }
            else
                {
                str.replace(str.find(ptr_m[i].whatToReplace), ptr_m[i].whatToReplace.size(), ptr_m[i].replaceTo);
                cout << "(" << i + 1 << ") ";
                for (int k = 0; k < s.size(); k++)
                    {
                    if (k >= s.find(ptr_m[i].whatToReplace) && k < s.find(ptr_m[i].whatToReplace) + ptr_m[i].whatToReplace.size())
                        {
                        SetConsoleTextAttribute(hConsoleHandle, 4);
                        cout << s[k];
                        }
                    else
                        {
                        cout << s[k];
                        }
                    SetConsoleTextAttribute(hConsoleHandle, 15);
                    }
                cout << " -> ";
                for (int k = 0; k < str.size(); k++)
                    {
                    if (k >= s.find(ptr_m[i].whatToReplace) && k < s.find(ptr_m[i].whatToReplace) + ptr_m[i].replaceTo.size())
                        {
                        SetConsoleTextAttribute(hConsoleHandle, 4);
                        cout << str[k];
                        }
                    else
                        {
                        cout << str[k];
                        }
                    SetConsoleTextAttribute(hConsoleHandle, 15);
                    }
                cout << endl;
                }
            *mar2 = ptr_m[i].ifEnd;
            return str;
            }
        }
    *mar2 = false;
    return str;
    }

bool isValidInput(const string& input)
    {
    for (char c : input)
        {
        if (!strchr("1*", c))
            {
            return false;
            }
        }
    return true;
    }

int main()
    {
    setlocale(LC_ALL, "Russian");
    string str;
    char choice;
    bool flag;
    Machine* ptr_m;
    ptr_m = new Machine[32];
    int l = init(ptr_m);
    do
        {
        cout << "Введите исходное слово: ";
        cin >> str;
        flag = isValidInput(str);
        if (flag == 1)
            {
            flag = true;
            bool* mar2 = &flag;
            while (*mar2 == 1)
                {
                str = transition(ptr_m, str, l, mar2);
                }
            cout << "Результат: " << str << endl;
            }
        else
            {
            cout << "Неверный ввод. Проверьте строку на корректность ввода. (Допустимые символы: 1, *)" << endl;
            }
        str.clear();
        cout << "Хотите продолжить работу? (y/n)" << endl;
        cin >> flag;
        } while (flag == 1);
        return 0;
    }

