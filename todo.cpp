#include <iostream>
#include <conio.h>
using namespace std;

void printHeader(string);
void clearScreen();
void holdScreen();
int menu(string[], int);
bool registerUser(int, string, string, string, int);
bool login(string, string);
bool isAdmin(int);

const int maxSize = 10;

int userId[maxSize], userRole[maxSize];
string userName[maxSize], userPassword[maxSize], userEmail[maxSize];
int userCount = 0;

int currentLoggedInUser = -1;

main()
{
    registerUser(0, "Admin", "admin", "admin@gmail.com", 1);

    string OnBoardingMenu[3] = {"Login", "Register", "Exit"};
    string MainMenu[10] = {"View Tasks", "Add Task","Update Task", "Delete Task", "Profile", "Logout"};
    string AdminMenu[4] = {"View Users", "Add User", "Update User", "Delete User"};
    clearScreen();
    printHeader("");

    int choice = menu(OnBoardingMenu, 3);
    while (true)
    {
        if (choice == 1)
        {
            cout << "You selected Login." << endl;
            clearScreen();
            printHeader("Login");
            string email, password;
            cout << "Enter your Email: ";
            cin >> email;
            cout << "Enter your Password: ";
            cin >> password;
            if (login(email, password))
            {
                clearScreen();
                printHeader("Welcome! " + userName[currentLoggedInUser]);
                if(isAdmin(currentLoggedInUser)){
                    for(int i = 6; i < 10; i++){
                        MainMenu[i] = AdminMenu[i - 6];
                    }
                }
            }
            else
            {
                cout << "Login failed. Please try again." << endl;
            }
        }
        else if (choice == 2)
        {
            clearScreen();
            printHeader("Register New User");
            int id = userCount;
            int role = 0;
            string name, password, email;
            cout << "Enter your Name: ";
            cin >> name;
            cout << "Enter your Password: ";
            cin >> password;
            cout << "Enter your Email: ";
            cin >> email;

            if (registerUser(id, name, password, email, role))
                cout << "Registration successful!" << endl;
            else
                cout << "Registration failed. User limit reached." << endl;
        }
        else if (choice == 3)
        {
            cout << "Exiting the application." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
        holdScreen();
        clearScreen();
        printHeader("");
        choice = menu(OnBoardingMenu, 3);
    }
    getch();
}

int menu(string menu[], int size)
{
    int choice = 0;
    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << ". " << menu[i] << endl;
    }
    cout << endl;
    cout << "Please select an option: ";
    cin >> choice;

    return choice;
}

bool registerUser(int id, string name, string password, string email, int role)
{
    if (userCount < maxSize)
    {
        userId[userCount] = id;
        userName[userCount] = name;
        userPassword[userCount] = password;
        userEmail[userCount] = email;
        userRole[userCount] = role;
        userCount++;
        return true;
    }
    else
    {
        cout << "User limit reached." << endl;
        return false;
    }
}

bool login(string email, string password)
{
    for (int i = 0; i < userCount; i++)
    {
        if (userEmail[i] == email && userPassword[i] == password)
        {
            currentLoggedInUser = i;
            cout << "Login successful! Welcome, " << userName[i] << "." << endl;
            return true;
        }
    }
    cout << "Login failed. Invalid email or password." << endl;
    return false;

}

bool isAdmin(int userId)
{
    if (userRole[userId] == 1)
    {
        return true;
    }
    return false;
}

void printHeader(string screenName)
{
    cout << "**********************************" << endl;
    cout << "*                                *" << endl;
    cout << "*          TODO LIST             *" << endl;
    cout << "*                                *" << endl;
    cout << "**********************************" << endl;
    cout << endl;
    if (!screenName.empty())
    {
        cout << screenName << endl;
        cout << endl;
    }
}

void clearScreen()
{
    system("cls");
}

void holdScreen()
{
    system("pause");
}
