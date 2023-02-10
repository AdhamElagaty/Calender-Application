#include <iostream>
#include <string>
#include <ctime>
using namespace std;

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
    string Modify_data_certain_specified_node(int pos, string t);
    string Modify_data_certain_specified_node(int pos, int y, int m, int d);
    string Modify_data_certain_specified_node(int pos, int h, int min);
    void Delete(string t);
    string Delete_at_pos(int pos);
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
    void Modify_data_certain_specified_node(string t,string newvalue);
    void Modify_data_certain_specified_node(string t, int y, int m, int d);
    void Modify_data_certain_specified_node(string t, int h, int min);
    string pop();
    void display();
    void peek();
    void Delete(string t);
    int count();
    bool IsFound(string t);
};

void Perform_Calender_Application(int &Choice, int &year, int &month, R_Linkedlist &r, R_Stack &rs, bool &t);
void Perform_Reminder(R_Linkedlist &r,R_Stack &rs, int &Choice);
void Calender_Interface(Calender c, bool x);
void Reminder_Interface(R_Linkedlist &r, R_Stack &rs, int Choice);

int main(){
    system("color 2F");
    system("cls");
    int Choice;
    bool t = true;
    Calender C;
    R_Linkedlist r;
    R_Stack rs;
    int year = C.get_year(),month = C.get_month();
    do {
        if (t)
        {
            year = C.get_year();
            month = C.get_month();
            Calender_Interface(C, false);
            t = false;
        }
        cout << "\t ---> Enter Your Choice: ";
        cin >> Choice;
        Perform_Calender_Application(Choice,year,month,r,rs,t);
    } while (Choice != 7);
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
        cout << "\t\t\t@#@#@# Find a Date :) #@#@#@#@\n" << endl;
        int y , m;
        cout << "\t-Enter Year to Search:";
        cin >> y;
        A.set_year(y);
        year = y;
        cout << "\n\t-Enter Month to Search:";
        cin >> m;
        A.set_month(m);
        month = m;
        system("cls");
        Calender_Interface(A,false);
    }else if(Choice == 4){
        system("cls");
        t = true;
    }else if(Choice == 5){
        cout << "\n\t\t  %&%&%& Current Day Task &%&%&%\n" << endl;
        r.DisPlay_Current_Day();
        system("pause");
        system("cls");
        Calender_Interface(A,false);
    } else if(Choice == 6){
        int ch;
        do {
            system("cls");
            Reminder_Interface(r,rs,0);
            cout << "\t ---> Enter Your Choice: ";
            cin >> ch;
            Perform_Reminder(r,rs,ch);
        } while (ch != 6);
        system("cls");
        Calender_Interface(A,false);
    }
}

void Perform_Reminder(R_Linkedlist &r,R_Stack &rs,int &Choice){
    if (Choice == 1){
        int ch;
        do{
            system("cls");
            Reminder_Interface(r,rs,Choice);
            cin >> ch;
            if (ch == 1){
                system("cls");
                Reminder_Interface(r,rs,4);
                int pos;
                string t;
                cout << "\t\t\t@#@#@# Update Task Name :) #@#@#@#@\n" << endl;
                cout << "\t-Enter the Number of Reminder(Task): ";
                cin >> pos;
                cout << "\n\t-Enter the New Title: ";
                cin >> t;
                rs.Modify_data_certain_specified_node(r.Modify_data_certain_specified_node(pos-1,t),t);
                system("pause");
            }else if(ch == 2){
                system("cls");
                Reminder_Interface(r,rs,4);
                int pos;
                int y,m,d;
                cout << "\t\t\t@#@#@# Update Task Date :) #@#@#@#@\n" << endl;
                cout << "\t-Enter the Number of Reminder(Task): ";
                cin >> pos;
                cout << "\n\t-Enter the New Year(Date): ";
                cin >> y;
                cout << "\n\t-Enter the New Month(Date): ";
                cin >> m;
                cout << "\n\t-Enter the New Day(Date): ";
                cin >> d;
                rs.Modify_data_certain_specified_node(r.Modify_data_certain_specified_node(pos-1,y,m,d),y,m,d);
                system("pause");
            }else if(ch == 3){
                system("cls");
                Reminder_Interface(r,rs,4);
                int pos;
                int h,min;
                cout << "\t\t\t@#@#@# Update Task Time :) #@#@#@#@\n" << endl;
                cout << "\t-Enter the Number of Reminder(Task): ";
                cin >> pos;
                cout << "\n\t-Enter the New Hour(Time): ";
                cin >> h;
                cout << "\n\t-Enter the New Minute(Time): ";
                cin >> min;
                rs.Modify_data_certain_specified_node(r.Modify_data_certain_specified_node(pos-1,h,min),h,min);
                system("pause");
            }else if(ch == 4){
                system("cls");
                Reminder_Interface(r,rs,4);
                int pos;
                cout << "\t\t\t@#@#@# Delete Task :) #@#@#@#@\n" << endl;
                cout << "\t-Enter the Number of Reminder(Task) to Delete: ";
                cin >> pos;
                rs.Delete(r.Delete_at_pos(pos-1));
                system("pause");
            }
        }while(ch != 5);
    }else if (Choice == 2){
        int ch;
        do {
            system("cls");
            Reminder_Interface(r,rs,Choice);
            cin >> ch;
            if (ch == 1){
                system("cls");
                Reminder_Interface(r,rs,5);
                rs.peek();
                system("pause");
            }else if(ch == 2){
                system("cls");
                Reminder_Interface(r,rs,5);
                r.Delete(rs.pop());
                system("pause");
                system("cls");
                Reminder_Interface(r,rs,Choice);
            }
        } while(ch != 3);
    }else if(Choice == 3){
        system("cls");
        Reminder_Interface(r,rs,5);
        string t;
        cout << "To Search for any Task Please Enter the Name of Task:";
        cin >> t;
        r.Display(t);
        system("pause");
    }else if(Choice == 4){
        cout << "\n\t -Number of Tasks is " << rs.count() << " Task :).\n" << endl;
        system("pause");
    }else if(Choice == 5){
        system("cls");
        Reminder_Interface(r,rs,5);
        string t;
        int y, m, d, h, min;
        cout << "\t\t\t@#@#@# Add New Task :) #@#@#@#@\n" << endl;
        cout << "\t-Enter the Reminder(Task) Name:";
        cin >> t;
        cout << "\n\t-Enter the Reminder(Task) Year(Date):";
        cin >> y;
        cout << "\n\t-Enter the Reminder(Task) month(Date):";
        cin >> m;
        cout << "\n\t-Enter the Reminder(Task) day(Date):";
        cin >> d;
        cout << "\n\t-Enter the Reminder(Task) Hour(Time):";
        cin >> h;
        cout << "\n\t-Enter the Reminder(Task) Minute(Time):";
        cin >> min;
        r.InsertEnd(t,y,m,d,h,min);
        rs.push(t,y,m,d,h,min);
    }
}

void Calender_Interface(Calender c, bool x){
    time_t now = time(nullptr);
    string  date_and_time = ctime(&now);
    cout << "\t\t\t\t\t\t\t\t          @#$ Welcome :) @#$\n" <<endl;
    cout <<"\t\t\t----> Current Date & Time : " << date_and_time << endl;
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
    c.Print_Calender();
    system("color 2F");
    if(x){
    }else{
        cout << "\t [1] Next Month." << endl;
        cout << "\t [2] Previous Month." << endl;
        cout << "\t [3] Search for Year & Month." << endl;
        cout << "\t [4] Get Current Date." << endl;
        cout << "\t [5] Show Current Day Reminders(Task)." << endl;
        cout << "\t [6] Reminders Option." << endl;
        cout << "\t [7] Exit.\n" << endl;
    }
}

void Reminder_Interface(R_Linkedlist &r, R_Stack &rs, int Choice){
    time_t now = time(nullptr);
    string  date_and_time = ctime(&now);
    cout << "\t\t\t\t\t\t\t\t          @#$ Welcome :) @#$\n" <<endl;
    cout << "\t\t\t----> Current Date & Time : " << date_and_time << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t &*&*&* Reminder *&*&*&\n" << endl;
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
    if(Choice == 1){
        r.get_N();
        r.sort();
        cout << "\t\t\t\t\t\t\t\t\t@#@#@# Display Tasks #@#@#@#@\n\n" << endl;
        r.Display();
        cout << "\t [1] Update on Title of Reminder." << endl;
        cout << "\t [2] Update on Date of Reminder." << endl;
        cout << "\t [3] Update on Time of Reminder." << endl;
        cout << "\t [4] Delete Task." << endl;
        cout << "\t [5] Back." << endl;
        cout << "\t ---> Enter Your Choice: ";
    }else if(Choice == 2){
        cout << "\t\t\t\t\t\t\t\t  @#@#@# Display Tasks in order of Entry #@#@#@#@\n\n" << endl;
        rs.display();
        cout << "\t [1] Show the last task that was added." << endl;
        cout << "\t [2] Delete the last task that was added." << endl;
        cout << "\t [3] Back." << endl;
        cout << "\t ---> Enter Your Choice: ";
    }else if(Choice == 4){
        r.get_N();
        r.sort();
        cout << "\t\t\t\t\t\t\t\t\t@#@#@# Display Tasks #@#@#@#@\n\n" << endl;
        r.Display();
    }else if(Choice == 5){
    }else {
        r.get_N();
        r.sort();
        cout << "\t\t\t\t\t\t\t\t\t@#@#@# Reminders Option #@#@#@#@\n\n" << endl;
        cout << "\t\t  %&%&%& Current Day Task &%&%&%\n" << endl;
        r.DisPlay_Current_Day();
        cout << "\t [1] Display." << endl;
        cout << "\t [2] Display in order of Entry." << endl;
        cout << "\t [3] Search for Reminder(Task)." << endl;
        cout << "\t [4] Show how many tasks." << endl;
        cout << "\t [5] Add Reminder(Task)." << endl;
        cout << "\t [6] Back." << endl;
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

    cout << "\t\t\t\t\t\t\t-----------------------------" << nameofmonth[M-1] << " " << Y << "-------------------------------" << "\n\n";
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
                cout << "      *" << i;
            }else {
                cout << "     *" << i;
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

string R_Linkedlist::Modify_data_certain_specified_node(int pos, string t)
{
    if (IsEmpty())
    {
        cout << "\t\t -Error! Reminder List is Empty, No Reminder(Task) to Update Name :(" << endl;
        return "";
    }
    else
    {
        string x;
        int i;
        if (pos == 0)
        {
            x = head->title;
            head->title = t;
            cout << "\t\t -The Name is updated Successfully :) \n" << endl;
            return x;
        }
        else
        {
            Reminder* Temp = head;
            for (i = 0; i < pos && Temp->Next != nullptr; ++i) {
                Temp = Temp->Next;
            }
            if(i != pos)
            {
                cout << "\t\t -Error! You Entered a Number that doesn`t Exist :( \n" << endl;
                return "";
            }
            x = Temp->title;
            Temp->title = t;
            cout << "\t\t -The Name is updated Successfully :) \n" << endl;
            return x;
        }
    }
}

string R_Linkedlist::Modify_data_certain_specified_node(int pos, int y, int m, int d){
    if (IsEmpty()){
        cout << "\t\t -Error! Reminder List is Empty, No Reminder(Task) to Update Date :(" << endl;
        return "";
    }else{
        int i;
        if (pos == 0){
            head->year = y;
            head->month = m;
            head->day = d;
            cout << "\t\t -The Date is updated successfully :) \n" << endl;
            return head->title;
        }else{
            Reminder* Temp = head;
            for (i = 0; i < pos && Temp->Next != nullptr; ++i) {
                Temp = Temp->Next;
            }
            if(i != pos){
                cout << "\t\t -Error! You Entered a Number that doesn`t Exist :( \n" << endl;
                return "";
            }
            Temp->year = y;
            Temp->month = m;
            Temp->day = d;
            cout << "\t\t -The Date is updated Successfully :) \n" << endl;
            return Temp->title;
        }
    }
}

string R_Linkedlist::Modify_data_certain_specified_node(int pos, int h, int min){
    if (IsEmpty()){
        cout << "\t\t -Error! Reminder List is Empty, No Reminder(Task) to Update Time :(" << endl;
        return "";
    }else{
        int i;
        if (pos == 0){
            head->hour = h;
            head->minute = min;
            cout << "\t\t -The time is updated Successfully :) \n" << endl;
            return head->title;
        }else{
            Reminder* Temp = head;
            for (i = 0; i < pos && Temp->Next != nullptr; ++i) {
                Temp = Temp->Next;
            }
            if(i != pos){
                cout << "\t\t -Error! You Entered a Number that doesn`t Exist :( \n" << endl;
                return "";
            }
            Temp->hour = h;
            Temp->minute = min;
            cout << "\t\t -The Time is updated Successfully :) \n" << endl;
            return Temp->title;
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

void R_Linkedlist::Delete(string t){
    if (IsEmpty()){
        cout << "\t\t -Error! Reminder List is Empty, No Items to Delete :(\n" << endl;
    }else{
        if (IsFound(t)){
            Reminder* delptr = head;
            if (head->title == t){
                head = delptr->Next;
                if(head != nullptr) {
                    head->Prev = nullptr;
                }
                delete delptr;
            }else{
                while (delptr!= nullptr && delptr->title != t){
                    delptr = delptr->Next;
                }
                delptr->Prev->Next = delptr->Next;
                if(delptr->Next != nullptr) {
                    delptr->Next->Prev = delptr->Prev;
                }
                delete delptr;
            }
            cout << "\t\t -This Reminder is Deleted Successfully :)" << endl;
        }else{
            cout << "\t\t -Error! This Task isn`t Found :(" << endl;
        }
    }
}

string R_Linkedlist::Delete_at_pos(int pos){
    if (IsEmpty()){
        return "";
    }else{
        Reminder* temp = head;
        if (pos == 0){
            head = temp->Next;
            if (head) {
                head->Prev = nullptr;
            }
            return temp->title;
            delete temp;
        }else{
            for (int i = 0; i < pos && temp != nullptr; i++) {
                temp = temp->Next;
            }
            if (temp == nullptr){
                return "";
            }
            temp->Prev->Next = temp->Next;
            if (temp->Next) {
                temp->Next->Prev = temp->Prev;
            }
            return temp->title;
            delete temp;
        }
    }
}

void R_Linkedlist::Display(){
    if (IsEmpty()){
        cout << "\t\t -Error! Reminder List is Empty, No Items to Display :(\n" << endl;
    }else{
        Reminder* Temp = head;
        int i = 1;
        while (Temp != nullptr){
            cout << "\t " << i << "- " << Temp->title << "   " << Temp->month << "/" << Temp->day << "/" << Temp->year <<"   " << Temp->hour << ":" << Temp->minute << endl;
            i++;
            Temp = Temp->Next;
        }
        cout << endl;
    }
}

void R_Linkedlist::Display(string t){
    if (IsEmpty()){
        cout << "\t\t -Error! Reminder List is Empty, No Items to Display :(\n" << endl;
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
            cout << "\t\t -Error! This Task isn`t Found :(\n" << endl;
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
        cout << "\t\t-No Reminds(Tasks) to Display today!.\n" << endl;
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
            cout << "\t\t-No Reminds(Tasks) to Display today!";
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

void R_Stack::Modify_data_certain_specified_node(string t, string newvalue) {
    if(t == "")
    {
        return;
    }
    if (IsEmpty())
    {
        return;
    } else{
        Reminder_node_stack* Temp = top;
        while (Temp->title != t)
        {
            Temp = Temp->Next;
        }
        Temp->title = newvalue;
    }
}

void R_Stack::Modify_data_certain_specified_node(string t, int y, int m, int d) {
    if(t == "")
    {
        return;
    }
    if (IsEmpty())
    {
        return;
    } else{
        Reminder_node_stack* Temp = top;
        while (Temp->title != t)
        {
            Temp = Temp->Next;
        }
        Temp->year = y;
        Temp->month = m;
        Temp->day = d;
    }
}

void R_Stack::Modify_data_certain_specified_node(string t, int h, int min) {
    if(t == "")
    {
        return;
    }
    if (IsEmpty()){
        return;
    } else{
        Reminder_node_stack* Temp = top;
        while (Temp->title != t)
        {
            Temp = Temp->Next;
        }
        Temp->hour = h;
        Temp->minute = min;
    }
}

string R_Stack::pop(){
    if (IsEmpty()){
        return "";
    }else{
        string  t;
        int y, m, d, h, min;
        Reminder_node_stack* ptr = top;
        top = top->Next;
        return ptr->title;
        delete ptr;
    }
}

void R_Stack::display(){
    if (IsEmpty()){
        cout << "\t\t -Error! Reminder List is Empty, No Items to Display :(\n" << endl;
    }else {
        Reminder_node_stack *Temp = top;
        int i = 1;
        while (Temp != nullptr) {
            cout << "\t " << i << "- "<< Temp->title << "   " << Temp->month << "/" << Temp->day << "/" << Temp->year << "   "
                 << Temp->hour << ":" << Temp->minute << endl;
            i++;
            Temp = Temp->Next;
        }
        cout << "\n";
    }
}

void R_Stack::peek(){
    if (IsEmpty()){
        cout << "\t\t -Error! Reminder List is Empty, No Items to Display :(\n" << endl;
    }else {
        cout << "\t-----> " << top->title << "   " << top->month << "/" << top->day << "/" << top->year << "   "
             << top->hour << ":" << top->minute << endl;
    }
}

void R_Stack::Delete(string t){
    if (IsEmpty()){
        cout << "\t\t -Error! Reminder List is Empty, No Items to Delete :(\n" << endl;
    }else{
        if (IsFound(t)){
            Reminder_node_stack* delptr = top;
            if (top->title == t){
                top = delptr->Next;
                delete delptr;
            }else{
                Reminder_node_stack* prev = nullptr;
                while (delptr!= nullptr && delptr->title != t){
                    prev = delptr;
                    delptr = delptr->Next;
                }
                prev->Next = delptr->Next;
                delete delptr;
            }
            cout << "\t\t -This Reminder is Deleted Successfully :)" << endl;
        }else{
            cout << "\t\t -Error! This Task isn`t Found :(" << endl;
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
