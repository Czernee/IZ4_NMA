#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Machine
    {
    string whatToReplace;
    string replaceTo;
    bool ifEnd;
    };

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

string transition(Machine* ptr, string str, int cntStates, bool& isEnd)
    {
    string s = str;
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < cntStates; i++)
        {
        size_t foundPos = str.find(ptr[i].whatToReplace);
        if (foundPos != string::npos)
            {
            string replacedStr = str;
            if (ptr[i].replaceTo == "_")
                {
                replacedStr.replace(foundPos, ptr[i].whatToReplace.size(), "");
                }
            else
                {
                replacedStr.replace(foundPos, ptr[i].whatToReplace.size(), ptr[i].replaceTo);
                }
            cout << "(" << i + 1 << ") ";
            for (int k = 0; k < s.size(); k++)
                {
                if (k >= foundPos && k < foundPos + replacedStr.size())
                    {
                    SetConsoleTextAttribute(hConsoleHandle, 4);
                    cout << s[k];
                    }
                else
                    {
                    SetConsoleTextAttribute(hConsoleHandle, 15);
                    cout << s[k];
                    }
                }
            cout << " -> ";
            for (int k = 0; k < replacedStr.size(); k++)
                {
                SetConsoleTextAttribute(hConsoleHandle, 4);
                cout << replacedStr[k];
                }
            SetConsoleTextAttribute(hConsoleHandle, 15);
            cout << endl;
            str = replacedStr;
            isEnd = ptr[i].ifEnd;
            return str;
            }
        }
    isEnd = false;
    return str;
    }

bool isValidInput(const string& input)
    {
    for (char c : input)
        {
        if (c != '1' && c != '*')
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
    Machine ptr[32];
    int cntStates = init(ptr);
    do
        {
        cout << "Введите исходное слово: ";
        cin >> str;
        bool flag = isValidInput(str);
        if (flag)
            {
            bool isEnd = true;
            while (isEnd)
                {
                str = transition(ptr, str, cntStates, isEnd);
                }
            cout << "Результат: " << str << endl;
            }
        else
            {
            cout << "Неверный ввод. Проверьте строку на корректность ввода. (Допустимые символы: 1, *)" << endl;
            }
        str.clear();
        cout << "Хотите продолжить работу? (y/n)" << endl;
        cin >> choice;
        } while (choice == 'Y' || choice == 'y');

        return 0;
    }
