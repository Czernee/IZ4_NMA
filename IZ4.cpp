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

int init(Machine* ptr)
    {
    ifstream fin("input.txt");
    int cnt, cntFinites, state;
    fin >> cnt;
    for (int i = 0; i < cnt; i++)
        {
        fin >> ptr[i].whatToReplace >> ptr[i].replaceTo;
        ptr[i].ifEnd = true;
        }
    fin >> cntFinites;
    for (int i = 0; i < cntFinites; i++)
        {
        fin >> state;
        ptr[state - 1].ifEnd = false;
        }
    return cnt;
    }

string transition(Machine* ptr, string str, int cntStates, bool* isEnd)
    {
    string s = str;
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < cntStates; i++)
        {
        if (ptr[i].whatToReplace == "_")
            {
            str = ptr[i].replaceTo + str;
            *isEnd = ptr[i].ifEnd;

            cout << "(" << i + 1 << ") " << s << " -> ";
            for (int k = 0; k < str.size(); k++)
                {
                SetConsoleTextAttribute(hConsoleHandle, (k < ptr[i].replaceTo.size()) ? 4 : 15);
                cout << str[k];
                }
            SetConsoleTextAttribute(hConsoleHandle, 15);

            cout << endl;
            return str;
            }

        size_t replacePos = str.find(ptr[i].whatToReplace);
        if (replacePos != string::npos)
            {
            if (ptr[i].replaceTo == "_")
                str.erase(replacePos, ptr[i].whatToReplace.size());
            else
                str.replace(replacePos, ptr[i].whatToReplace.size(), ptr[i].replaceTo);

            *isEnd = ptr[i].ifEnd;

            cout << "(" << i + 1 << ") ";
            for (int k = 0; k < s.size(); k++)
                {
                SetConsoleTextAttribute(hConsoleHandle, (k >= replacePos && k < replacePos + ptr[i].whatToReplace.size()) ? 4 : 15);
                cout << s[k];
                }
            cout << " -> ";
            for (int k = 0; k < str.size(); k++)
                {
                SetConsoleTextAttribute(hConsoleHandle, (k >= replacePos && k < replacePos + ptr[i].replaceTo.size()) ? 4 : 15);
                cout << str[k];
                }
            SetConsoleTextAttribute(hConsoleHandle, 15);

            cout << endl;
            return str;
            }
        }

    *isEnd = false;
    return str;
    }


bool isValidInput(string input)
    {
    for (char c : input)
        if (!strchr("1*", c))
            return false;
    return true;
    }

int main()
    {
    setlocale(LC_ALL, "Russian");
    string str;
    char choice;
    bool flag;
    Machine* ptr;
    ptr = new Machine[32];
    int cntStates = init(ptr);
    do
        {
        cout << "Введите исходное слово: ";
        cin >> str;
        flag = isValidInput(str);
        if (flag == 1)
            {
            flag = true;
            bool* isEnd = &flag;
            while (*isEnd == 1)
                str = transition(ptr, str, cntStates, isEnd);
            cout << "Результат: " << str << endl;
            }
        else
            cout << "Неверный ввод. Проверьте строку на корректность ввода. (Допустимые символы: 1, *)" << endl;
        str.clear();
        cout << "Хотите продолжить работу? (y/n)" << endl;
        cin >> choice;
        } while (choice == 'Y' || choice == 'y');

        return 0;
    }

