#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <limits>
using namespace std;
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

class Calender{
private:
    int Y, M, CY, CM, CD;
public:
    Calender();
    Calender(int year, int month);
    int get_year();
    int get_month();
    void set_year(int y);
    void set_month(int m);
    int get_current_day();
    int get_current_month();
    int get_current_year();
    int dayNumber(int day, int month, int year);
    void Print_Calender();
    void DisplayNextMonth(int &month,int &year);
    void DisplayPrevMonth(int &month,int &year);
};

class Reminder{
public:
    string title, to_string;
    int year, month, day, hour, minute;
    long long intN;
    Reminder* Next;
    Reminder* Prev;
    Reminder();
};

class R_Linkedlist{
private:
    Reminder* head;
public:
    R_Linkedlist();
    bool IsEmpty();
    void InsertFirst(string t, int y, int m, int d, int h, int min);
    void InsertEnd(string t, int y, int m, int d, int h, int min);
    void Modify_data_certain_specified_node(int pos, string t, string &T, int &Y, int &M, int &D, int &H, int &Min);
    void Modify_data_certain_specified_node(int pos, int y, int m, int d, string &T, int &Y, int &M, int &D, int &H, int &Min);
    void Modify_data_certain_specified_node(int pos, int h, int min, string &T, int &Y, int &M, int &D, int &H, int &Min);
    void Delete(string t, int y, int m, int d, int h, int min);
    void Delete_at_pos(int pos, string &t, int &y, int &m, int &d, int &h, int &min);
    bool IsFound(string t);
    void get_N();
    void sort();
    void Display();
    void Display(string t);
    void DisPlay_Current_Day();
};

class Reminder_node_stack{
public:
    string title;
    int year, month, day, hour, minute;
    Reminder_node_stack *Next;
    Reminder_node_stack();
};

class R_Stack{
    Reminder_node_stack *top;
public:
    R_Stack();
    bool IsEmpty();
    void push(string t, int y, int m, int d, int h, int min);
    void Modify_data_certain_specified_node(string t, string T, int Y, int M, int D, int H, int Min);
    void Modify_data_certain_specified_node(int y, int m, int d, string T, int Y, int M, int D, int H, int Min);
    void Modify_data_certain_specified_node(int h, int min, string T, int Y, int M, int D, int H, int Min);
    void pop(string &t, int &y, int &m, int &d, int &h, int &min);
    void display();
    void peek();
    void Delete(string t, int y, int m, int d, int h, int min);
    int count();
    bool IsFound(string t);
};


class SystemFile
{
public:
    void insert_task(string t, int y, int m, int d, int h, int min);
    void insert_in_memory(R_Linkedlist &r, R_Stack &rs);
    void delete_task(string t, int y, int m, int d, int h, int min);
    void Modify_data(string TN, string t, int y, int m, int d, int h, int min);
    void Modify_data(int YN, int MN, int DN, string t, int y, int m, int d, int h, int min);
    void Modify_data(int HN, int MinN, string t, int y, int m, int d, int h, int min);
    void task_reset_data_in_file_system();
    int get_number_of_task(int Case);
};

void Perform_Calender_Application(int &Choice, int &year, int &month, R_Linkedlist &r, R_Stack &rs, bool &t);
void Perform_Reminder(R_Linkedlist &r,R_Stack &rs, int &Choice);
void Calender_Interface(Calender c, bool x);
void Reminder_Interface(R_Linkedlist &r, R_Stack &rs, int Choice);

int main(){
    system ("color 2F");
    system("cls");
    SystemFile f;
    int Choice;
    bool t = true;
    Calender C;
    R_Linkedlist r;
    R_Stack rs;
    f.insert_in_memory(r,rs);
    int year = C.get_year(),month = C.get_month();
    Calender_Interface(C,false);
    system("cls");
    do {
        if (t)
        {
            year = C.get_year();
            month = C.get_month();
            Calender_Interface(C, false);
            t = false;
        }
        cout << "\t ---> Enter Your Choice: ";
        SetConsoleTextAttribute(color,32);
        cin >> Choice;
        if (!Choice){
            SetConsoleTextAttribute(color,47);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            Choice = 8;
        }
        SetConsoleTextAttribute(color,47);
        Perform_Calender_Application(Choice,year,month,r,rs,t);
    } while (Choice != 7);
    return 0;
}

void SystemFile::insert_task(string t, int y, int m, int d, int h, int min) {
    ofstream out_movie;
    out_movie.open("Store_Tasks.txt", ios::app);
    out_movie << "#" << endl << t << endl << y << endl << m << endl << d << endl << h << endl << min << endl;
}

void SystemFile::insert_in_memory(R_Linkedlist &r, R_Stack &rs) {
    string x, t;
    int a = 0, y, m, d, h, min;
    ifstream in_x;
    in_x.open("Store_Tasks.txt");
    while (getline(in_x, x)){
        if (x == "#"){
            a = 0;
            continue;
        }else{
            if (a == 0){
                t = x;
            } else if (a == 1){
                y = stoi(x);
            } else if (a == 2){
                m = stoi(x);
            } else if (a == 3){
                d = stoi(x);
            } else if (a == 4){
                h = stoi(x);
            } else if (a == 5){
                min = stoi(x);
            }
            if (a == 5)
            {
                r.InsertEnd(t,y,m,d,h,min);
                rs.push(t,y,m,d,h,min);
            }
            a++;
        }
    }
}

void SystemFile::delete_task(string t, int y, int m, int d, int h, int min){
    string X, T;
    int a = 0, Y, M, D, H, Min, pos = 0;
    bool r1,r2,r3,r4,r5,r6;
    r1=r2=r3=r4=r5=r6= false;
    ifstream in_X;
    in_X.open("Store_Tasks.txt");
    while (getline(in_X, X)){
        if (X == "#"){
            r1=r2=r3=r4=r5=r6= false;
            a = 0;
            pos++;
            continue;
        }else{
            if (a == 0){
                T = X;
                if (T == t){
                    r1 = true;
                }
            } else if (a == 1){
                Y = stoi(X);
                if (Y == y){
                    r2 = true;
                }
            } else if (a == 2){
                M = stoi(X);
                if (M == m){
                    r3 = true;
                }
            } else if (a == 3){
                D = stoi(X);
                if (D == d){
                    r4 = true;
                }
            } else if (a == 4){
                H = stoi(X);
                if (H == h){
                    r5 = true;
                }
            } else if (a == 5){
                Min = stoi(X);
                if (Min == min){
                    r6 = true;
                }
            }
            if (r1 && r2 && r3 && r4 && r5 && r6 && a == 5)
            {
                break;
            }
            a++;
        }
    }
    in_X.close();
    string x;
    ofstream Out_x;
    Out_x.open("Temp_Store_Tasks.txt", ios::app);
    ifstream in_x;
    in_x.open("Store_Tasks.txt");
    int i = 0,z = get_number_of_task(1);
    while (getline(in_x, x)){
        if(x == "#" && i == z-1 && i == pos-1){
            i++;
            continue;
        }
        if (i != pos ){
            Out_x << x << endl;
        }
        if(x == "#")
        {
            i++;
        }
    }
    in_x.close();
    Out_x.close();
    remove("Store_Tasks.txt");
    rename("Temp_Store_Tasks.txt", "Store_Tasks.txt");
    get_number_of_task(1);
}

void SystemFile::Modify_data(string TN, string t, int y, int m, int d, int h, int min){
    string X, T;
    int a = 0, Y, M, D, H, Min, pos = 0;
    bool r1,r2,r3,r4,r5,r6;
    r1=r2=r3=r4=r5=r6= false;
    ifstream in_X;
    in_X.open("Store_Tasks.txt");
    while (getline(in_X, X)){
        if (X == "#"){
            r1=r2=r3=r4=r5=r6= false;
            a = 0;
            pos++;
            continue;
        }else{
            if (a == 0){
                T = X;
                if (T == t){
                    r1 = true;
                }
            } else if (a == 1){
                Y = stoi(X);
                if (Y == y){
                    r2 = true;
                }
            } else if (a == 2){
                M = stoi(X);
                if (M == m){
                    r3 = true;
                }
            } else if (a == 3){
                D = stoi(X);
                if (D == d){
                    r4 = true;
                }
            } else if (a == 4){
                H = stoi(X);
                if (H == h){
                    r5 = true;
                }
            } else if (a == 5){
                Min = stoi(X);
                if (Min == min){
                    r6 = true;
                }
            }
            if (r1 && r2 && r3 && r4 && r5 && r6 && a == 5)
            {
                break;
            }
            a++;
        }
    }
    in_X.close();
    string x;
    ofstream Out_x;
    Out_x.open("Temp_Store_Tasks.txt", ios::app);
    ifstream in_x;
    in_x.open("Store_Tasks.txt");
    int i = 0,z = get_number_of_task(1), n = 0;
    while (getline(in_x, x)){
        if (i != pos ){
            Out_x << x << endl;
        }else{
            if (n == 0){
                x = TN;
            }
            Out_x << x << endl;
            n++;
        }
        if(x == "#")
        {
            i++;
        }
    }
    in_x.close();
    Out_x.close();
    remove("Store_Tasks.txt");
    rename("Temp_Store_Tasks.txt", "Store_Tasks.txt");
}

void SystemFile::Modify_data(int YN, int MN, int DN, string t, int y, int m, int d, int h, int min){
    string X, T;
    int a = 0, Y, M, D, H, Min, pos = 0;
    bool r1,r2,r3,r4,r5,r6;
    r1=r2=r3=r4=r5=r6= false;
    ifstream in_X;
    in_X.open("Store_Tasks.txt");
    while (getline(in_X, X)){
        if (X == "#"){
            r1=r2=r3=r4=r5=r6= false;
            a = 0;
            pos++;
            continue;
        }else{
            if (a == 0){
                T = X;
                if (T == t){
                    r1 = true;
                }
            } else if (a == 1){
                Y = stoi(X);
                if (Y == y){
                    r2 = true;
                }
            } else if (a == 2){
                M = stoi(X);
                if (M == m){
                    r3 = true;
                }
            } else if (a == 3){
                D = stoi(X);
                if (D == d){
                    r4 = true;
                }
            } else if (a == 4){
                H = stoi(X);
                if (H == h){
                    r5 = true;
                }
            } else if (a == 5){
                Min = stoi(X);
                if (Min == min){
                    r6 = true;
                }
            }
            if (r1 && r2 && r3 && r4 && r5 && r6 && a == 5)
            {
                break;
            }
            a++;
        }
    }
    in_X.close();
    string x;
    ofstream Out_x;
    Out_x.open("Temp_Store_Tasks.txt", ios::app);
    ifstream in_x;
    in_x.open("Store_Tasks.txt");
    int i = 0,z = get_number_of_task(1), n = 0;
    while (getline(in_x, x)){
        if (i != pos ){
            Out_x << x << endl;
        }else{
            if (n == 1){
                x = to_string(YN);
            }else if (n == 2){
                x = to_string(MN);
            }else if (n == 3){
                x = to_string(DN);
            }
            Out_x << x << endl;
            n++;
        }
        if(x == "#")
        {
            i++;
        }
    }
    in_x.close();
    Out_x.close();
    remove("Store_Tasks.txt");
    rename("Temp_Store_Tasks.txt", "Store_Tasks.txt");
}

void SystemFile::Modify_data(int HN, int MinN, string t, int y, int m, int d, int h, int min){
    string X, T;
    int a = 0, Y, M, D, H, Min, pos = 0;
    bool r1,r2,r3,r4,r5,r6;
    r1=r2=r3=r4=r5=r6= false;
    ifstream in_X;
    in_X.open("Store_Tasks.txt");
    while (getline(in_X, X)){
        if (X == "#"){
            r1=r2=r3=r4=r5=r6= false;
            a = 0;
            pos++;
            continue;
        }else{
            if (a == 0){
                T = X;
                if (T == t){
                    r1 = true;
                }
            } else if (a == 1){
                Y = stoi(X);
                if (Y == y){
                    r2 = true;
                }
            } else if (a == 2){
                M = stoi(X);
                if (M == m){
                    r3 = true;
                }
            } else if (a == 3){
                D = stoi(X);
                if (D == d){
                    r4 = true;
                }
            } else if (a == 4){
                H = stoi(X);
                if (H == h){
                    r5 = true;
                }
            } else if (a == 5){
                Min = stoi(X);
                if (Min == min){
                    r6 = true;
                }
            }
            if (r1 && r2 && r3 && r4 && r5 && r6 && a == 5)
            {
                break;
            }
            a++;
        }
    }
    in_X.close();
    string x;
    ofstream Out_x;
    Out_x.open("Temp_Store_Tasks.txt", ios::app);
    ifstream in_x;
    in_x.open("Store_Tasks.txt");
    int i = 0,z = get_number_of_task(1), n = 0;
    while (getline(in_x, x)){
        if (i != pos ){
            Out_x << x << endl;
        }else{
            if (n == 4){
                x = to_string(HN);
            }else if (n == 5){
                x = to_string(MinN);
            }
            Out_x << x << endl;
            n++;
        }
        if(x == "#")
        {
            i++;
        }
    }
    in_x.close();
    Out_x.close();
    remove("Store_Tasks.txt");
    rename("Temp_Store_Tasks.txt", "Store_Tasks.txt");
}

void SystemFile::task_reset_data_in_file_system(){
    ofstream Out_task;
    Out_task.open("Temp_Store_Tasks.txt", ios::app);
    Out_task.close();
    remove("Store_Tasks.txt");
    rename("Temp_Store_Tasks.txt", "Store_Tasks.txt");
    get_number_of_task(1);
}

int SystemFile::get_number_of_task(int Case){
    if (Case == 0){
        ifstream in;
        in.open("Number_Of_Tasks.txt");
        int x;
        in >> x;
        return x;
    }else if (Case == 1){
        string x;
        ifstream in_x;
        in_x.open("Store_Tasks.txt");
        ofstream Out_x;
        Out_x.open("Number_Of_Tasks.txt");
        int count = 0;
        while (getline(in_x, x)){
            if(x == "#")
            {
                count++;
            }
        }
        Out_x << count;
        in_x.close();
        Out_x.close();
        return count;
    }
    return 0;
}

void Perform_Calender_Application(int &Choice, int &year, int &month, R_Linkedlist &r, R_Stack &rs, bool &t){
    Calender C;
    Calender A(year,month);
    if(Choice == 1){
        system("cls");
        A.DisplayNextMonth(month, year);
    }else if(Choice == 2){
        system("cls");
        A.DisplayPrevMonth(month, year);
    }else if(Choice == 3){
        system("cls");
        Calender_Interface(C, true);
        cout << "\t\t\t@#@#@# ";
        SetConsoleTextAttribute(color,37);
        cout << "Find a Date :)";
        SetConsoleTextAttribute(color,47);
        cout << " #@#@#@#@\n" << endl;
        int y , m;
        cout << "\t-Enter Year to Search:";
        SetConsoleTextAttribute(color,32);
        cin >> y;
        SetConsoleTextAttribute(color,47);
        A.set_year(y);
        year = y;
        cout << "\n\t-Enter Month to Search:";
        SetConsoleTextAttribute(color,32);
        cin >> m;
        SetConsoleTextAttribute(color,47);
        A.set_month(m);
        month = m;
        system("cls");
        Calender_Interface(A,false);
    }else if(Choice == 4){
        system("cls");
        t = true;
    }else if(Choice == 5){
        cout << "\n\t\t  %&%&%& ";
        SetConsoleTextAttribute(color,37);
        cout << "Current Day Task";
        SetConsoleTextAttribute(color,47);
        cout << " &%&%&%\n" << endl;
        r.DisPlay_Current_Day();
        system("pause");
        system("cls");
        Calender_Interface(A,false);
    } else if(Choice == 6){
        int ch;
        system("cls");
        Reminder_Interface(r,rs,0);
        do {
            cout << "\t ---> Enter Your Choice: ";
            SetConsoleTextAttribute(color,32);
            cin >> ch;
            if (!ch){
                SetConsoleTextAttribute(color,47);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                ch = 8;
            }
            SetConsoleTextAttribute(color,47);
            Perform_Reminder(r,rs,ch);
        } while (ch != 7);
        system("cls");
        Calender_Interface(A,false);
    } else if(Choice == 7){}else{
        system("cls");
        Calender_Interface(A, false);
        SetConsoleTextAttribute(color,36);
        cout << "\t-Error! Enter Correct Choice must to be (Number)" << endl;
        SetConsoleTextAttribute(color,47);
    }
}

void Perform_Reminder(R_Linkedlist &r,R_Stack &rs,int &Choice){
    SystemFile f;
    if (Choice == 1){
        int ch;
        system("cls");
        Reminder_Interface(r,rs,Choice);
        do{
            cout << "\t ---> Enter Your Choice: ";
            SetConsoleTextAttribute(color,32);
            cin >> ch;
            SetConsoleTextAttribute(color,47);
            if (ch == 1){
                system("cls");
                Reminder_Interface(r,rs,4);
                int pos, Y, M, D, H, Min;
                string t, T;
                cout << "\t\t\t@#@#@# ";
                SetConsoleTextAttribute(color,37);
                cout  << "Update Task Name :)";
                SetConsoleTextAttribute(color,47);
                cout << " #@#@#@#@\n" << endl;
                cout << "\t-Enter the Number of Reminder(Task): ";
                SetConsoleTextAttribute(color,32);
                cin >> pos;
                SetConsoleTextAttribute(color,47);
                if (!pos){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                cout << "\n\t-Enter the New Title: ";
                SetConsoleTextAttribute(color,32);
                cin >> t;
                SetConsoleTextAttribute(color,47);
                r.Modify_data_certain_specified_node(pos-1,t,T,Y,M,D,H,Min);
                rs.Modify_data_certain_specified_node(t,T,Y,M,D,H,Min);
                f.Modify_data(t,T,Y,M,D,H,Min);
                system("pause");
            }else if(ch == 2){
                system("cls");
                Reminder_Interface(r,rs,4);
                string T;
                int pos, y, m, d, Y, M, D, H, Min;
                cout << "\t\t\t@#@#@# ";
                SetConsoleTextAttribute(color,37);
                cout  << "Update Task Date :)";
                SetConsoleTextAttribute(color,47);
                cout << " #@#@#@#@\n" << endl;
                cout << "\t-Enter the Number of Reminder(Task): ";
                SetConsoleTextAttribute(color,32);
                cin >> pos;
                SetConsoleTextAttribute(color,47);
                if (!pos){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                cout << "\n\t-Enter the New Year(Date): ";
                SetConsoleTextAttribute(color,32);
                cin >> y;
                SetConsoleTextAttribute(color,47);
                if (!y){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                if (y < 1){
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                cout << "\n\t-Enter the New Month(Date): ";
                SetConsoleTextAttribute(color,32);
                cin >> m;
                SetConsoleTextAttribute(color,47);
                if (!m){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                if (m > 12 || m < 0){
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                cout << "\n\t-Enter the New Day(Date): ";
                SetConsoleTextAttribute(color,32);
                cin >> d;
                SetConsoleTextAttribute(color,47);
                if (!d){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                if (d > 31 || d < 1){
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                r.Modify_data_certain_specified_node(pos-1,y,m,d,T,Y,M,D,H,Min);
                rs.Modify_data_certain_specified_node(y,m,d,T,Y,M,D,H,Min);
                f.Modify_data(y,m,d,T,Y,M,D,H,Min);
                system("pause");
            }else if(ch == 3){
                system("cls");
                Reminder_Interface(r,rs,4);
                string T, x;
                int pos, h, min, y, m, d, Y, M, D, H, Min;
                cout << "\t\t\t@#@#@# ";
                SetConsoleTextAttribute(color,37);
                cout  << "Update Task Time :)";
                SetConsoleTextAttribute(color,47);
                cout << " #@#@#@#@\n" << endl;
                cout << "\t-Enter the Number of Reminder(Task): ";
                SetConsoleTextAttribute(color,32);
                cin >> pos;
                SetConsoleTextAttribute(color,47);
                if (!pos){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                cout << "\n\t-Enter the New Hour(Time): ";
                SetConsoleTextAttribute(color,32);
                cin >> h;
                SetConsoleTextAttribute(color,47);
                if (!h){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                if (h > 24 || h < 1){
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                cout << "\n\t-Enter the New Minute(Time): ";
                SetConsoleTextAttribute(color,32);
                cin >> x;
                SetConsoleTextAttribute(color,47);
                try {
                    std::stoi(x);
                } catch (std::exception& e) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    system("cls");
                    Reminder_Interface(r,rs,0);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                min = stoi(x);
                if (min > 60 || min < 0){
                    system("cls");
                    Reminder_Interface(r,rs,0);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                r.Modify_data_certain_specified_node(pos-1,h,min,T,Y,M,D,H,Min);
                rs.Modify_data_certain_specified_node(h,min,T,Y,M,D,H,Min);
                f.Modify_data(h,min,T,Y,M,D,H,Min);
                system("pause");
            }else if(ch == 4){
                system("cls");
                Reminder_Interface(r,rs,4);
                string t;
                int pos, y, m, d, h, min;
                cout << "\t-Enter the Number of Reminder(Task) to Delete: ";
                SetConsoleTextAttribute(color,32);
                cin >> pos;
                SetConsoleTextAttribute(color,47);
                if (!pos){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    system("cls");
                    Reminder_Interface(r,rs,Choice);
                    SetConsoleTextAttribute(color,36);
                    cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
                    SetConsoleTextAttribute(color,47);
                    continue;
                }
                r.Delete_at_pos(pos-1,t,y,m,d,h,min);
                system("pause");
                rs.Delete(t,y,m,d,h,min);
                f.delete_task(t,y,m,d,h,min);
                system("pause");
            }else{
                SetConsoleTextAttribute(color,47);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                system("cls");
                Reminder_Interface(r,rs,Choice);
                SetConsoleTextAttribute(color,36);
                cout << "\t-Error! Enter Correct Choice must to be (Number)" << endl;
                SetConsoleTextAttribute(color,47);
                continue;
            }
            system("cls");
            Reminder_Interface(r,rs,Choice);
        }while(ch != 5);
    }else if (Choice == 2){
        int ch;
        system("cls");
        Reminder_Interface(r,rs,Choice);
        do {
            cout << "\t ---> Enter Your Choice: ";
            SetConsoleTextAttribute(color,32);
            cin >> ch;
            SetConsoleTextAttribute(color,47);
            if (ch == 1){
                system("cls");
                Reminder_Interface(r,rs,5);
                cout << "\t\t\t\t\t\t\t\t\t#$#$#$#$";
                SetConsoleTextAttribute(color,37);
                cout << "View the last task entry";
                SetConsoleTextAttribute(color,47);
                cout << " $#$#$#$#\n" << endl;
                SetConsoleTextAttribute(color,33);
                rs.peek();
                SetConsoleTextAttribute(color,47);
                system("pause");
            }else if(ch == 2){
                string t;
                int y, m, d, h, min;
                system("cls");
                Reminder_Interface(r,rs,5);
                SetConsoleTextAttribute(color,33);
                rs.pop(t,y,m,d,h,min);
                r.Delete(t,y,m,d,h,min);
                f.delete_task(t,y,m,d,h,min);
                SetConsoleTextAttribute(color,47);
                system("pause");
                system("cls");
                Reminder_Interface(r,rs,Choice);
            }else{
                SetConsoleTextAttribute(color,47);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                system("cls");
                Reminder_Interface(r,rs,Choice);
                SetConsoleTextAttribute(color,36);
                cout << "\t-Error! Enter Correct Choice must to be (Number)" << endl;
                SetConsoleTextAttribute(color,47);
                continue;
            }
            system("cls");
            Reminder_Interface(r,rs,Choice);
        } while(ch != 3);
    }else if(Choice == 3){
        system("cls");
        Reminder_Interface(r,rs,5);
        string t;
        cout << "To Search for any Task Please Enter the Name of Task:";
        SetConsoleTextAttribute(color,32);
        cin >> t;
        SetConsoleTextAttribute(color,47);
        r.Display(t);
        system("pause");
    }else if(Choice == 4){
        SetConsoleTextAttribute(color,33);
        cout << "\n\t -Number of Tasks is " << rs.count() << " Task :).\n" << endl;
        SetConsoleTextAttribute(color,47);
        system("pause");
    }else if(Choice == 5){
        system("cls");
        Reminder_Interface(r,rs,5);
        string t,x;
        int y, m, d, h, min;
        cout << "\t\t\t@#@#@# ";
        SetConsoleTextAttribute(color,37);
        cout << "Add New Task :)";
        SetConsoleTextAttribute(color,47);
        cout << "#@#@#@#@\n" << endl;
        cout << "\t-Enter the Reminder(Task) Name:";
        SetConsoleTextAttribute(color,32);
        cin >> t;
        SetConsoleTextAttribute(color,47);
        cout << "\n\t-Enter the Reminder(Task) Year(Date):";
        SetConsoleTextAttribute(color,32);
        cin >> y;
        SetConsoleTextAttribute(color,47);
        if (!y){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        if (y < 1){
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        cout << "\n\t-Enter the Reminder(Task) month(Date):";
        SetConsoleTextAttribute(color,32);
        cin >> m;
        SetConsoleTextAttribute(color,47);
        if (!m){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        if (m > 12 || m < 0){
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        cout << "\n\t-Enter the Reminder(Task) day(Date):";
        SetConsoleTextAttribute(color,32);
        cin >> d;
        SetConsoleTextAttribute(color,47);
        if (!d){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        if (d > 31 || d < 1){
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        cout << "\n\t-Enter the Reminder(Task) Hour(Time):";
        SetConsoleTextAttribute(color,32);
        cin >> h;
        SetConsoleTextAttribute(color,47);
        if (!h){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        if (h > 24 || h < 1){
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        cout << "\n\t-Enter the Reminder(Task) Minute(Time):";
        SetConsoleTextAttribute(color,32);
        cin >> x;
        SetConsoleTextAttribute(color,47);
        try {
            std::stoi(x);
        } catch (std::exception& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        min = stoi(x);
        if (min > 60 || min < 0){
            system("cls");
            Reminder_Interface(r,rs,0);
            SetConsoleTextAttribute(color,36);
            cout << "\t Error! You have an Error in Last Progress please try again correctly :)" << endl;
            SetConsoleTextAttribute(color,47);
            return;
        }
        r.InsertEnd(t,y,m,d,h,min);
        rs.push(t,y,m,d,h,min);
        f.insert_task(t,y,m,d,h,min);
    }else if(Choice == 6){
        string a;
        bool t = false;
        do {
            system("cls");
            Reminder_Interface(r,rs,5);
            cout << "\t\t\t\t\t\t\t\t\t@#@#@# ";
            SetConsoleTextAttribute(color,37);
            cout << "Reset All Reminder Data";
            SetConsoleTextAttribute(color,47);
            cout << " #@#@#@#@\n\n" << endl;
            if (t){
                SetConsoleTextAttribute(color,36);
                cout << "\t\t\t\t\tError! Please Enter correct Answer :)." << endl;
                SetConsoleTextAttribute(color,47);
            }
            cout << "\t\t\t\tAre you sure to delete all tasks? (y/n) : ";
            SetConsoleTextAttribute(color,32);
            cin >> a;
            SetConsoleTextAttribute(color,47);
            t = true;
        } while (a!="y" && a!="Y" && a!="yes" && a!="Yes" && a!="YES" && a!="yES" && a!="yEs" && a!="YeS" && a!="n" && a!="N" && a!="no" && a!="No" && a!="NO" && a!="nO");
        if (a=="y" || a=="Y" || a=="yes" || a=="Yes" || a=="YES" || a=="yES" || a=="yEs" || a=="YeS") {
            R_Linkedlist rn;
            R_Stack rsn;
            r = rn;
            rs = rsn;
            f.task_reset_data_in_file_system();
            SetConsoleTextAttribute(color,33);
            cout << "\t\t\t\t\tAll task data has been Deleted(Reset) Successfully :)" << endl;
            SetConsoleTextAttribute(color,47);
            system("pause");
        }
    }else if (Choice == 7){}else{
        system("cls");
        system("cls");
        Reminder_Interface(r,rs,0);
        SetConsoleTextAttribute(color,36);
        cout << "\t-Error! Enter Correct Choice must to be (Number)" << endl;
        SetConsoleTextAttribute(color,47);
        return;
    }
    system("cls");
    Reminder_Interface(r,rs,0);
}

void Calender_Interface(Calender c, bool x){
    time_t now = time(nullptr);
    string  date_and_time = ctime(&now);
    cout << "\n\t\t\t\t\t\t\t\t          ";
    SetConsoleTextAttribute(color,22);
    cout << "@#$ Welcome :) @#$";
    SetConsoleTextAttribute(color,47);
    cout << "\n" <<endl;
    cout <<"\t\t\t";
    SetConsoleTextAttribute(color,37);
    cout << "----> Current Date & Time :";
    SetConsoleTextAttribute(color,47);
    cout << " " << date_and_time << endl;
    SetConsoleTextAttribute(color,32);
    cout << "\t\t\t\t\t\t\t\t      (@                        @%      " << endl;
    cout << "\t\t\t\t\t\t\t\t      (@                        @%      " << endl;
    cout << "\t\t\t\t\t\t\t\t*@@@@@(@/@@@@@@@@@@@@@@@@@@@@@@(@%@@@@@#" << endl;
    cout << "\t\t\t\t\t\t\t\t@@@@@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "\t\t\t\t\t\t\t\t@@....................................%@" << endl;
    cout << "\t\t\t\t\t\t\t\t@@                                    #@" << endl;
    cout << "\t\t\t\t\t\t\t\t@@    @@@@@@&    @@@@@@,   %@@@@@@    #@" << endl;
    cout << "\t\t\t\t\t\t\t\t@@    @@@@@@&    @@@@@@,   %@@@@@@    #@" << endl;
    cout << "\t\t\t\t\t\t\t\t@@    @@@@@@&    @@@@@@,   %@@@@@@    #@" << endl;
    cout << "\t\t\t\t\t\t\t\t@@                                 ~$.@," << endl;
    cout << "\t\t\t\t\t\t\t\t@@    @@@@@@&    @@@@@@,       %@/       *@@" << endl;
    cout << "\t\t\t\t\t\t\t\t@@    @@@@@@&    @@@@@@,    .@       &       @*" << endl;
    cout << "\t\t\t\t\t\t\t\t@@    @@@@@@&    @@@@@@,   (&        &        /@" << endl;
    cout << "\t\t\t\t\t\t\t\t@@                         @         &         @." << endl;
    cout << "\t\t\t\t\t\t\t\t/@@@@@@@@@@@@@@@@@@@@@@@@@.@     *** @         @," << endl;
    cout << "\t\t\t\t\t\t\t\t                           %%                 ,@" << endl;
    cout << "\t\t\t\t\t\t\t\t                            *@               @%" << endl;
    cout << "\t\t\t\t\t\t\t\t                              .@&         %@*" << endl;
    cout << "\t\t\t\t\t\t\t\t                                 .@/.$,/@." << endl;
    cout << "\n\n";
    SetConsoleTextAttribute(color,47);
    c.Print_Calender();
    if(x){
    }else{
        SetConsoleTextAttribute(color,33);
        cout << "\t [1] ";
        SetConsoleTextAttribute(color,47);
        cout << "Next Month." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [2] ";
        SetConsoleTextAttribute(color,47);
        cout << "Previous Month." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [3] ";
        SetConsoleTextAttribute(color,47);
        cout << "Search for Year & Month." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [4] ";
        SetConsoleTextAttribute(color,47);
        cout << "Get Current Date." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [5] ";
        SetConsoleTextAttribute(color,47);
        cout << "Show Current Day Reminders(Task)." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [6] ";
        SetConsoleTextAttribute(color,47);
        cout << "Reminders Option." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [7] ";
        SetConsoleTextAttribute(color,47);
        cout << "Exit.\n" << endl;
    }
}

void Reminder_Interface(R_Linkedlist &r, R_Stack &rs, int Choice){
    time_t now = time(nullptr);
    string  date_and_time = ctime(&now);
    cout << "\n\t\t\t\t\t\t\t\t          ";
    SetConsoleTextAttribute(color,22);
    cout << "@#$ Welcome :) @#$";
    SetConsoleTextAttribute(color,47);
    cout << "\n" <<endl;
    cout <<"\t\t\t";
    SetConsoleTextAttribute(color,37);
    cout << "----> Current Date & Time :";
    SetConsoleTextAttribute(color,47);
    cout << " " << date_and_time << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t@#@#@# ";
    SetConsoleTextAttribute(color,37);
    cout << "Reminders";
    SetConsoleTextAttribute(color,47);
    cout << " #@#@#@#@\n\n" << endl;
    SetConsoleTextAttribute(color,32);
    cout << "\t\t\t\t\t\t\t\t                         .~??7:" << endl;
    cout << "\t\t\t\t\t\t\t\t                        !##J?P@P:" << endl;
    cout << "\t\t\t\t\t\t\t\t              ......!YPG@@P   @@&GPJ!......" << endl;
    cout << "\t\t\t\t\t\t\t\t             5&&&&&&@@@@@@@&&@@@@@@@&&&&&&5~" << endl;
    cout << "\t\t\t\t\t\t\t\t             P@@~~~~B@@@@@@@@@@@@@@@@~~~P@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t             G@G                        7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t             G@G     :::::::::::: ^YY:  7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t             G@G                        7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t             G@G     :::::::::::: ^YY:  7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t             G@G                        7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t             G@G     :::::::::::: ^YY:  7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t             G@G                        7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t      :~.    G@G :~. :::::::::::: ^YY:  7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t      :~.    G@G :~.                    7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t ~777!G@P!777#@#!J@#!7777:::::::: ^YY:  7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t~@@@@#B@G#@@@@@@@P@#G@@@@5              7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t~@@                     @P              7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t^GG  @@@  @@@  @@@  @@@ GJ              7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t~@&  @@@  @@@  @@@  @@@ @5              7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t~@&                     @P              7@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t~@@  @@@  @@@  @@@  @@@ @&GGGGGGGGGGGGGB@@@~" << endl;
    cout << "\t\t\t\t\t\t\t\t~@&  @@@  @@@  @@@  @@@ @BJJJJJJJJJJJJJJJJ?." << endl;
    cout << "\t\t\t\t\t\t\t\t~@&                     @B" << endl;
    cout << "\t\t\t\t\t\t\t\t~@@!^^~&G?Y!?@7^^^B@@@@@@5" << endl;
    cout << "\t\t\t\t\t\t\t\t ~777!G@P!777#@#!J@#!7777\n\n" << endl;
    SetConsoleTextAttribute(color,47);
    if(Choice == 1){
        r.get_N();
        r.sort();
        cout << "\t\t\t\t\t\t\t\t\t@#@#@# ";
        SetConsoleTextAttribute(color,37);
        cout << "Display & Edit Tasks";
        SetConsoleTextAttribute(color,47);
        cout << " #@#@#@#@\n\n" << endl;
        SetConsoleTextAttribute(color,33);
        r.Display();
        SetConsoleTextAttribute(color,33);
        cout << "\t [1] ";
        SetConsoleTextAttribute(color,47);
        cout << "Update on Title of Reminder." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [2] ";
        SetConsoleTextAttribute(color,47);
        cout << "Update on Date of Reminder." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [3] ";
        SetConsoleTextAttribute(color,47);
        cout << "Update on Time of Reminder." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [4] ";
        SetConsoleTextAttribute(color,47);
        cout << "Delete Task." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [5] ";
        SetConsoleTextAttribute(color,47);
        cout << "Back." << endl;
    }else if(Choice == 2){
        cout << "\t\t\t\t\t\t\t\t  @#@#@# ";
        SetConsoleTextAttribute(color,37);
        cout << "Display Tasks in order of Entry";
        SetConsoleTextAttribute(color,47);
        cout << " #@#@#@#@\n\n" << endl;
        SetConsoleTextAttribute(color,33);
        rs.display();
        SetConsoleTextAttribute(color,33);
        cout << "\t [1] ";
        SetConsoleTextAttribute(color,47);
        cout << "Show the last task that was added." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [2] ";
        SetConsoleTextAttribute(color,47);
        cout << "Delete the last task that was added." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [3] ";
        SetConsoleTextAttribute(color,47);
        cout << "Back." << endl;
    }else if(Choice == 4){
        r.get_N();
        r.sort();
        cout << "\t\t\t\t\t\t\t\t\t@#@#@# ";
        SetConsoleTextAttribute(color,37);
        cout << "Display Tasks to Delete";
        SetConsoleTextAttribute(color,47);
        cout << " #@#@#@#@\n\n" << endl;
        SetConsoleTextAttribute(color,33);
        r.Display();
        SetConsoleTextAttribute(color,47);
    }else if(Choice == 5){
    }else {
        r.get_N();
        r.sort();
        cout << "\t\t\t\t\t\t\t\t\t@#@#@# ";
        SetConsoleTextAttribute(color,37);
        cout << "Reminders Option";
        SetConsoleTextAttribute(color,47);
        cout << " #@#@#@#@\n\n" << endl;
        cout << "\t\t  %&%&%& ";
        SetConsoleTextAttribute(color,37);
        cout << "Current Day Task";
        SetConsoleTextAttribute(color,47);
        cout << " &%&%&%\n" << endl;
        SetConsoleTextAttribute(color,33);
        r.DisPlay_Current_Day();
        SetConsoleTextAttribute(color,33);
        cout << "\t [1] ";
        SetConsoleTextAttribute(color,47);
        cout << "Display." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [2] ";
        SetConsoleTextAttribute(color,47);
        cout << "Display in order of Entry." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [3] ";
        SetConsoleTextAttribute(color,47);
        cout << "Search for Reminder(Task)." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [4] ";
        SetConsoleTextAttribute(color,47);
        cout << "Show how many tasks." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [5] ";
        SetConsoleTextAttribute(color,47);
        cout << "Add Reminder(Task)." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [6] ";
        SetConsoleTextAttribute(color,47);
        cout << "Reset All Reminder Data." << endl;
        SetConsoleTextAttribute(color,33);
        cout << "\t [7] ";
        SetConsoleTextAttribute(color,47);
        cout << "Back." << endl;
    }
}

Calender::Calender(){
    time_t now = time(nullptr);
    tm * t = localtime(&now);
    Y = (t -> tm_year) + 1900;
    M = (t -> tm_mon) + 1;
    CD = t -> tm_mday;
    CY = Y;
    CM = M;
}

Calender::Calender(int year, int month){
    Y = year;
    M = month;
}

int Calender::get_year(){
    return Y;
}

int Calender::get_month(){
    return M;
}

void Calender::set_year(int y){
    Y = y;
}

void Calender::set_month(int m){
    M = m;
}

int Calender::get_current_day(){
    return CD;
}

int Calender::get_current_month(){
    return CM;
}

int Calender::get_current_year(){
    return CY;
}

int Calender::dayNumber(int day, int month, int year){
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    return ( year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}

void Calender::Print_Calender(){
    Calender c;
    int numberofdays = 0, current;
    current = dayNumber(1, M, Y);
    if (M == 1) { // January
        numberofdays = 31;
    }
    else if (M == 2){ // February

        if (Y % 400 == 0 || (Y % 4 == 0 && Y % 100 != 0)) {
            numberofdays = 29;
        }
        else {
            numberofdays = 28;
        }
    }
    else if (M == 3) { // March
        numberofdays = 31;
    }
    else if (M == 4) { // April
        numberofdays = 30;
    }
    else if (M == 5) { // May
        numberofdays = 31;
    }
    else if (M == 6) { // June
        numberofdays = 30;
    }
    else if (M == 7) { // July
        numberofdays = 31;
    }
    else if (M == 8) { // August
        numberofdays = 31;
    }
    else if (M == 9) { // September
        numberofdays = 30;
    }
    else if (M == 10) { // October
        numberofdays = 31;
    }
    else if (M == 11) { // November
        numberofdays = 30;
    }
    else if  (M == 12) { // December
        numberofdays = 31;
    }
    string nameofmonth[12] = { "January", "February", "March",
                               "April", "May", "June",
                               "July", "August", "September",
                               "October", "November", "December" };

    cout << "\t\t\t\t\t\t\t-----------------------------";
    SetConsoleTextAttribute(color,37);
    cout << nameofmonth[M-1] << " " << Y;
    SetConsoleTextAttribute(color,47);
    cout << "-------------------------------" << "\n\n";
    cout <<"\t\t\t\t\t\t\t         "<< "  Sun    Mon     Tue    Wed     Thu     Fri     Sat\n\n";
    cout << "\t\t\t\t\t\t\t    ";
    int k;
    for (k = 0; k < current; k++)
    {
        cout << "        ";
    }
    for (int i = 1;i <= numberofdays;i++){
        if (c.get_current_day() == i && c.get_current_month() == M && c.get_current_year() == Y){
            if(i<10) {
                cout << "       ";
                SetConsoleTextAttribute(color,36);
                cout << i;
                SetConsoleTextAttribute(color,47);
            }else {
                cout << "      ";
                SetConsoleTextAttribute(color,36);
                cout << i;
                SetConsoleTextAttribute(color,47);
            }
        }else{
            if(i<10) {
                cout << "       " << i;
            }else {
                cout << "      " << i;
            }
        }
        if (++k > 6) {
            k = 0;
            cout << "\n";
            cout << "\t\t\t\t\t\t\t    ";
        }
    }
    cout<<"\n\n\n";
}

void Calender::DisplayNextMonth(int &month, int &year){
    if(month<12 && month>=1){
        month++;
        Calender C(year,month);
        Calender_Interface(C,false);
    }else{
        month=1;
        year++;
        Calender C(year,month);
        Calender_Interface(C,false);
    }
}

void Calender::DisplayPrevMonth(int &month, int &year){
    if(month<=12&&month>1){
        month--;
        Calender C(year,month);
        Calender_Interface(C,false);
    }else{
        month=12;
        year--;
        Calender C(year,month);
        Calender_Interface(C,false);
    }
}

Reminder::Reminder(){
    title = "";
    to_string = "";
    year = 0;
    month = 0;
    day = 0;
    hour = 0;
    minute = 0;
    intN = 0;
    Next = nullptr;
    Prev = nullptr;
}

R_Linkedlist::R_Linkedlist() {
    head = nullptr;
}

bool R_Linkedlist::IsEmpty() {
    return (head == nullptr);
}

void R_Linkedlist::InsertFirst(string t, int y, int m, int d, int h, int min){
    Reminder* newnode = new Reminder();
    newnode->title = t;
    newnode->year = y;
    newnode->month = m;
    newnode->day = d;
    newnode->hour = h;
    newnode->minute = min;
    if (IsEmpty()){
        newnode->Next = nullptr;
        head = newnode;
        newnode->Prev = nullptr;
    }else{
        newnode->Next = head;
        head->Prev = newnode;
        newnode->Prev = nullptr;
        head = newnode;
    }
}

void R_Linkedlist::InsertEnd(string t, int y, int m, int d, int h, int min){
    if (IsEmpty()){
        InsertFirst(t,y,m,d,h,min);
    }else{
        Reminder* newnode = new Reminder();
        Reminder* Temp = head;
        newnode->title = t;
        newnode->year = y;
        newnode->month = m;
        newnode->day = d;
        newnode->hour = h;
        newnode->minute = min;
        newnode->Next = nullptr;
        while (Temp->Next != nullptr){
            Temp = Temp->Next;
        }
        Temp->Next = newnode;
        newnode->Prev = Temp;
    }
}

void R_Linkedlist::Modify_data_certain_specified_node(int pos, string t, string &T, int &Y, int &M, int &D, int &H, int &Min)
{
    if (IsEmpty())
    {
        SetConsoleTextAttribute(color,36);
        cout << "\t\t -Error! Reminder List is Empty, No Reminder(Task) to Update Name :(" << endl;
        SetConsoleTextAttribute(color,47);
        return;
    }
    else
    {
        string x;
        int i;
        if (pos == 0)
        {
            T = head->title;
            Y = head->year;
            M = head->month;
            D = head->day;
            H = head->hour;
            Min = head->minute;
            head->title = t;
            SetConsoleTextAttribute(color,33);
            cout << "\t\t -The Name is updated Successfully :) \n" << endl;
            SetConsoleTextAttribute(color,47);
        }
        else
        {
            Reminder* Temp = head;
            for (i = 0; i < pos && Temp->Next != nullptr; ++i) {
                Temp = Temp->Next;
            }
            if(i != pos)
            {
                SetConsoleTextAttribute(color,36);
                cout << "\t\t -Error! You Entered a Number that doesn't Exist :( \n" << endl;
                SetConsoleTextAttribute(color,47);
                return;
            }
            T = Temp->title;
            Y = Temp->year;
            M = Temp->month;
            D = Temp->day;
            H = Temp->hour;
            Min = Temp->minute;
            Temp->title = t;
            SetConsoleTextAttribute(color,33);
            cout << "\t\t -The Name is updated Successfully :) \n" << endl;
            SetConsoleTextAttribute(color,47);
        }
    }
}

void R_Linkedlist::Modify_data_certain_specified_node(int pos, int y, int m, int d, string &T, int &Y, int &M, int &D, int &H, int &Min){
    if (IsEmpty()){
        SetConsoleTextAttribute(color,36);
        cout << "\t\t -Error! Reminder List is Empty, No Reminder(Task) to Update Date :(" << endl;
        SetConsoleTextAttribute(color,47);
        return;
    }else{
        int i;
        if (pos == 0){
            T = head->title;
            Y = head->year;
            M = head->month;
            D = head->day;
            H = head->hour;
            Min = head->minute;
            head->year = y;
            head->month = m;
            head->day = d;
            SetConsoleTextAttribute(color,33);
            cout << "\t\t -The Date is updated successfully :) \n" << endl;
            SetConsoleTextAttribute(color,47);
        }else{
            Reminder* Temp = head;
            for (i = 0; i < pos && Temp->Next != nullptr; ++i) {
                Temp = Temp->Next;
            }
            if(i != pos){
                SetConsoleTextAttribute(color,36);
                cout << "\t\t -Error! You Entered a Number that doesn't Exist :( \n" << endl;
                SetConsoleTextAttribute(color,47);
                return;
            }
            T = Temp->title;
            Y = Temp->year;
            M = Temp->month;
            D = Temp->day;
            H = Temp->hour;
            Min = Temp->minute;
            Temp->year = y;
            Temp->month = m;
            Temp->day = d;
            SetConsoleTextAttribute(color,33);
            cout << "\t\t -The Date is updated Successfully :) \n" << endl;
            SetConsoleTextAttribute(color,47);
        }
    }
}

void R_Linkedlist::Modify_data_certain_specified_node(int pos, int h, int min, string &T, int &Y, int &M, int &D, int &H, int &Min){
    if (IsEmpty()){
        SetConsoleTextAttribute(color,36);
        cout << "\t\t -Error! Reminder List is Empty, No Reminder(Task) to Update Time :(" << endl;
        SetConsoleTextAttribute(color,47);
        return;
    }else{
        int i;
        if (pos == 0){
            T = head->title;
            Y = head->year;
            M = head->month;
            D = head->day;
            H = head->hour;
            Min = head->minute;
            head->hour = h;
            head->minute = min;
            SetConsoleTextAttribute(color,33);
            cout << "\t\t -The time is updated Successfully :) \n" << endl;
            SetConsoleTextAttribute(color,47);
        }else{
            Reminder* Temp = head;
            for (i = 0; i < pos && Temp->Next != nullptr; ++i) {
                Temp = Temp->Next;
            }
            if(i != pos){
                SetConsoleTextAttribute(color,36);
                cout << "\t\t -Error! You Entered a Number that doesn't Exist :( \n" << endl;
                SetConsoleTextAttribute(color,47);
                return;
            }
            T = Temp->title;
            Y = Temp->year;
            M = Temp->month;
            D = Temp->day;
            H = Temp->hour;
            Min = Temp->minute;
            Temp->hour = h;
            Temp->minute = min;
            SetConsoleTextAttribute(color,33);
            cout << "\t\t -The Time is updated Successfully :) \n" << endl;
            SetConsoleTextAttribute(color,47);
        }
    }
}

bool R_Linkedlist::IsFound(string t){
    Reminder* Temp = head;
    while (Temp != nullptr){
        if (t == Temp->title){
            return true;
        }
        Temp = Temp->Next;
    }
    return false;
}

void R_Linkedlist::get_N(){
    Reminder* Temp = head;
    while (Temp != nullptr){
        string M = to_string(Temp->month), D = to_string(Temp->day), H = to_string(Temp->hour), MIN = to_string(Temp->minute);
        if(Temp->month < 10){
            M = "0"+ to_string(Temp->month);
        }
        if(Temp->day < 10){
            D = "0"+ to_string(Temp->day);
        }
        if(Temp->hour < 10){
            H = "0"+ to_string(Temp->hour);
        }
        if(Temp->minute < 10){
            MIN = "0"+ to_string(Temp->minute);
        }
        Temp->to_string = to_string(Temp->year) + M + D + H + MIN;
        Temp->intN = stoll(Temp->to_string);
        Temp = Temp->Next;
    }
}

void R_Linkedlist::sort(){
    Reminder* cur1 = head;
    Reminder* cur2 = head;
    while (cur1 != nullptr) {
        while (cur2 != nullptr) {
            if (cur1->intN > cur2->intN) {
                swap(cur1->year, cur2->year);
                swap(cur1->title, cur2->title);
                swap(cur1->month, cur2->month);
                swap(cur1->day, cur2->day);
                swap(cur1->hour, cur2->hour);
                swap(cur1->minute, cur2->minute);
                swap(cur1->intN, cur2->intN);
                swap(cur1->to_string, cur2->to_string);
            }
            cur2 = cur2->Next;
        }
        cur2 = cur1->Next;
        cur1 = cur1->Next;
    }
}

void R_Linkedlist::Delete(string t, int y, int m, int d, int h, int min){
    if (IsEmpty()){
        SetConsoleTextAttribute(color,36);
        cout << "\t\t -Error! Reminder List is Empty, No Items to Delete :(\n" << endl;
        SetConsoleTextAttribute(color,47);
    }else{
        if (IsFound(t)){
            Reminder* delptr = head;
            if (head->title == t && head->year == y && head->month == m && head->day == d && head->hour == h && head->minute == min){
                head = delptr->Next;
                if(head != nullptr) {
                    head->Prev = nullptr;
                }
                delete delptr;
            }else{
                bool r = true;
                while (delptr!= nullptr && r){
                    delptr = delptr->Next;
                    if (delptr->title == t && delptr->year == y && delptr->month == m && delptr->day == d && delptr->hour == h && delptr->minute == min){
                        r = false;
                    }
                }
                delptr->Prev->Next = delptr->Next;
                if(delptr->Next != nullptr) {
                    delptr->Next->Prev = delptr->Prev;
                }
                delete delptr;
            }
            SetConsoleTextAttribute(color,33);
            cout << "\t\t -This Reminder is Deleted Successfully :)" << endl;
            SetConsoleTextAttribute(color,47);
        }else{
            SetConsoleTextAttribute(color,36);
            cout << "\t\t -Error! This Task isn`t Found :(" << endl;
            SetConsoleTextAttribute(color,47);
        }
    }
}

void R_Linkedlist::Delete_at_pos(int pos, string &t, int &y, int &m, int &d, int &h, int &min){
    if (IsEmpty()){
        return;
    }else{
        Reminder* temp = head;
        if (pos == 0){
            head = temp->Next;
            if (head) {
                head->Prev = nullptr;
            }
            t = temp->title;
            y = temp->year;
            m = temp->month;
            d = temp->day;
            h = temp->hour;
            min = temp->minute;
            delete temp;
        }else{
            for (int i = 0; i < pos && temp != nullptr; i++) {
                temp = temp->Next;
            }
            if (temp == nullptr){
                return;
            }
            temp->Prev->Next = temp->Next;
            if (temp->Next) {
                temp->Next->Prev = temp->Prev;
            }
            t = temp->title;
            y = temp->year;
            m = temp->month;
            d = temp->day;
            h = temp->hour;
            min = temp->minute;
            delete temp;
        }
    }
}

void R_Linkedlist::Display(){
    if (IsEmpty()){
        SetConsoleTextAttribute(color,36);
        cout << "\t\t -Error! Reminder List is Empty, No Items to Display :(\n" << endl;
        SetConsoleTextAttribute(color,47);
    }else{
        Reminder* Temp = head;
        int i = 1;
        while (Temp != nullptr){
            cout << "\t\t\t " << i << "- " << Temp->title << "   " << Temp->month << "/" << Temp->day << "/" << Temp->year <<"   " << Temp->hour << ":" << Temp->minute << endl;
            i++;
            Temp = Temp->Next;
        }
        cout << endl;
    }
}

void R_Linkedlist::Display(string t){
    if (IsEmpty()){
        SetConsoleTextAttribute(color,36);
        cout << "\t\t -Error! Reminder List is Empty, No Items to Display :(\n" << endl;
        SetConsoleTextAttribute(color,47);
    }else{
        if (IsFound(t)){
            Reminder* Temp = head;
            while (Temp != nullptr){
                if (Temp->title == t)
                {
                    cout <<"\t-----> " << Temp->title << "   " << Temp->month << "/" << Temp->day << "/" << Temp->year <<"   " << Temp->hour << ":" << Temp->minute << endl;
                }
                Temp = Temp->Next;
            }
        }else{
            SetConsoleTextAttribute(color,36);
            cout << "\t\t -Error! This Task isn`t Found :(\n" << endl;
            SetConsoleTextAttribute(color,47);
        }
    }
}

void R_Linkedlist::DisPlay_Current_Day(){
    time_t now = time(nullptr);
    tm * t = localtime(&now);
    int Y = (t -> tm_year) + 1900;
    int M = (t -> tm_mon) + 1;
    int D = t -> tm_mday;
    if (IsEmpty()){
        SetConsoleTextAttribute(color,36);
        cout << "\t\t-No Reminds(Tasks) to Display today!.\n" << endl;
        SetConsoleTextAttribute(color,47);
    }else{
        Reminder* Temp = head;
        int i = 1;
        bool r = true;
        while (Temp != nullptr){
            if (Temp->year == Y && Temp->month == M && Temp->day == D) {
                cout << "\t\t"<< i << "- " << Temp->title << "   " << Temp->month << "/" << Temp->day << "/" << Temp->year
                     << "   " << Temp->hour << ":" << Temp->minute << endl;
                r = false;
                i++;
            }
            Temp = Temp->Next;
        }
        if (r){
            SetConsoleTextAttribute(color,36);
            cout << "\t\t-No Reminds(Tasks) to Display today!." << endl;
            SetConsoleTextAttribute(color,47);
        }
        cout << "\n" << endl;
    }
}

Reminder_node_stack::Reminder_node_stack(){
    this->title = "";
    this->year = 0;
    this->month = 0;
    this->day = 0;
    this->hour = 0;
    this->minute = 0;
    this->Next = nullptr;
}

R_Stack::R_Stack(){
    top = nullptr;
}

bool R_Stack::IsEmpty(){
    return(top == nullptr);
}

void R_Stack::push(string t, int y, int m, int d, int h, int min){
    Reminder_node_stack* newnode = new Reminder_node_stack();
    newnode->title = t;
    newnode->year = y;
    newnode->month = m;
    newnode->day = d;
    newnode->hour = h;
    newnode->minute = min;
    if (IsEmpty()){
        top = newnode;
        newnode->Next = nullptr;
    }else{
        newnode->Next = top;
        top = newnode;
    }
}

void R_Stack::Modify_data_certain_specified_node(string t, string T, int Y, int M, int D, int H, int Min) {
    if(T == "")
    {
        return;
    }
    if (IsEmpty())
    {
        return;
    } else{
        Reminder_node_stack* Temp = top;
        bool r = true;
        if (Temp->title == T && Temp->year == Y && Temp->month == M && Temp->day == D && Temp->hour == H && Temp->minute == Min){
            r = false;
        }
        while (r)
        {
            Temp = Temp->Next;
            if (Temp->title == T && Temp->year == Y && Temp->month == M && Temp->day == D && Temp->hour == H && Temp->minute == Min){
                r = false;
            }
        }
        Temp->title = t;
    }
}

void R_Stack::Modify_data_certain_specified_node(int y, int m, int d, string T, int Y, int M, int D, int H, int Min) {
    if(T == "")
    {
        return;
    }
    if (IsEmpty())
    {
        return;
    } else{
        Reminder_node_stack* Temp = top;
        bool r = true;
        if (Temp->title == T && Temp->year == Y && Temp->month == M && Temp->day == D && Temp->hour == H && Temp->minute == Min){
            r = false;
        }
        while (r)
        {
            Temp = Temp->Next;
            if (Temp->title == T && Temp->year == Y && Temp->month == M && Temp->day == D && Temp->hour == H && Temp->minute == Min){
                r = false;
            }
        }
        Temp->year = y;
        Temp->month = m;
        Temp->day = d;
    }
}

void R_Stack::Modify_data_certain_specified_node(int h, int min, string T, int Y, int M, int D, int H, int Min) {
    if(T == "")
    {
        return;
    }
    if (IsEmpty()){
        return;
    } else{
        Reminder_node_stack* Temp = top;
        bool r = true;
        if (Temp->title == T && Temp->year == Y && Temp->month == M && Temp->day == D && Temp->hour == H && Temp->minute == Min){
            r = false;
        }
        while (r)
        {
            Temp = Temp->Next;
            if (Temp->title == T && Temp->year == Y && Temp->month == M && Temp->day == D && Temp->hour == H && Temp->minute == Min){
                r = false;
            }
        }
        Temp->hour = h;
        Temp->minute = min;
    }
}

void R_Stack::pop(string &t, int &y, int &m, int &d, int &h, int &min){
    if (IsEmpty()){
        return;
    }else{
        Reminder_node_stack* ptr = top;
        top = top->Next;
        t = ptr->title;
        y = ptr->year;
        m = ptr->month;
        d = ptr->day;
        h = ptr->hour;
        min = ptr->minute;
        delete ptr;
    }
}

void R_Stack::display(){
    if (IsEmpty()){
        SetConsoleTextAttribute(color,36);
        cout << "\t\t -Error! Reminder List is Empty, No Items to Display :(\n" << endl;
        SetConsoleTextAttribute(color,47);
    }else {
        Reminder_node_stack *Temp = top;
        int i = 1;
        while (Temp != nullptr) {
            cout << "\t\t\t " << i << "- "<< Temp->title << "   " << Temp->month << "/" << Temp->day << "/" << Temp->year << "   "
                 << Temp->hour << ":" << Temp->minute << endl;
            i++;
            Temp = Temp->Next;
        }
        cout << "\n";
    }
}

void R_Stack::peek(){
    if (IsEmpty()){
        SetConsoleTextAttribute(color,36);
        cout << "\t\t -Error! Reminder List is Empty, No Items to Display :(\n" << endl;
        SetConsoleTextAttribute(color,47);
    }else {
        cout << "\t-----> " << top->title << "   " << top->month << "/" << top->day << "/" << top->year << "   "
             << top->hour << ":" << top->minute << endl;
    }
}

void R_Stack::Delete(string t, int y, int m, int d, int h, int min){
    if (IsEmpty()){
        SetConsoleTextAttribute(color,36);
        cout << "\t\t -Error! Reminder List is Empty, No Items to Delete :(\n" << endl;
        SetConsoleTextAttribute(color,47);
    }else{
        if (IsFound(t)){
            Reminder_node_stack* delptr = top;
            if (top->title == t && top->year == y && top->month == m && top->day == d && top->hour == h && top->minute == min){
                top = delptr->Next;
                delete delptr;
            }else{
                Reminder_node_stack* prev = nullptr;
                bool r = true;
                while (delptr!= nullptr && r){
                    prev = delptr;
                    delptr = delptr->Next;
                    if (delptr->title == t && delptr->year == y && delptr->month == m && delptr->day == d && delptr->hour == h && delptr->minute == min){
                        r = false;
                    }
                }
                prev->Next = delptr->Next;
                delete delptr;
            }
            SetConsoleTextAttribute(color,33);
            cout << "\t\t -This Reminder is Deleted Successfully :)" << endl;
            SetConsoleTextAttribute(color,47);
        }else{
            SetConsoleTextAttribute(color,36);
            cout << "\t\t -Error! This Task isn`t Found :(" << endl;
            SetConsoleTextAttribute(color,47);
        }
    }
}

int R_Stack::count(){
    int counter = 0;
    Reminder_node_stack* temp = top;
    while (temp != nullptr){
        counter++;
        temp = temp->Next;
    }
    return counter;
}

bool R_Stack::IsFound(string t){
    bool found = false;
    Reminder_node_stack* temp = top;
    while (temp != nullptr){
        if (temp->title == t){
            found = true;
            break;
        }
        temp = temp->Next;
    }
    return found;
}