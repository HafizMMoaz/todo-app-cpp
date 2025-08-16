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
int findUserById(int);

const int maxSize = 10;

int userId[maxSize], userRole[maxSize];
string userName[maxSize], userPassword[maxSize], userEmail[maxSize];
int userCount = 0;

int currentLoggedInUser = -1;

main()
{
    registerUser(0, "Admin", "admin", "admin@gmail.com", 1);

    string OnBoardingMenu[3] = {"Login", "Register", "Exit"};
    string MainMenu[10] = {"View Tasks", "Add Task", "Update Task", "Delete Task", "Profile", "Logout"};
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
                bool admin = isAdmin(currentLoggedInUser);
                int menuSize = 6;
                if (admin)
                {
                    for (int i = 6; i < 10; i++)
                    {
                        MainMenu[i] = AdminMenu[i - 6];
                    }
                    menuSize = 10;
                }

                int mainChoice = menu(MainMenu, menuSize);

                while (true)
                {
                    if (mainChoice == 1)
                    {
                        clearScreen();
                        printHeader("Tasks List");

                    }
                    else if (mainChoice == 2)
                    {
                        clearScreen();
                        printHeader("Add Task");
                    }
                    else if (mainChoice == 3)
                    {
                        clearScreen();
                        printHeader("Update Task");
                    }
                    else if (mainChoice == 4)
                    {
                        clearScreen();
                        printHeader("Delete Task");
                    }
                    else if (mainChoice == 5)
                    {
                        clearScreen();
                        printHeader("Profile");

                        cout << "User ID: " << userId[currentLoggedInUser] << endl;
                        cout << "Name: " << userName[currentLoggedInUser] << endl;
                        cout << "Email: " << userEmail[currentLoggedInUser] << endl;
                        cout << "Password: " << userPassword[currentLoggedInUser] << endl;
                        cout << "Role: " << (userRole[currentLoggedInUser] == 1 ? "Admin" : "User") << endl;
                        cout << endl;
                    }
                    else if (mainChoice == 6)
                    {
                        clearScreen();
                        printHeader("Logout");
                        currentLoggedInUser = -1;
                        cout << "You have been logged out." << endl;
                        break;
                    }
                    else if (mainChoice == 7 && admin)
                    {
                        clearScreen();
                        printHeader("Users List");

                        cout << "User ID\tName\tEmail\tRole" << endl;
                        for (int i = 0; i < userCount; i++)
                        {
                            cout << userId[i] << "\t" << userName[i] << "\t" << userEmail[i] << "\t" << (userRole[i] == 1 ? "Admin" : "User") << endl;
                        }
                        cout << endl;
                    }
                    else if (mainChoice == 8 && admin)
                    {
                        clearScreen();
                        printHeader("Add User");
                        int id = userCount;
                        int role;
                        string name, password, email;
                        cout << "Enter your Name: ";
                        cin >> name;
                        cout << "Enter your Password: ";
                        cin >> password;
                        cout << "Enter your Email: ";
                        cin >> email;
                        cout << "Enter Role (0 for User, 1 for Admin): ";
                        cin >> role;
                        while (role < 0 || role > 1)
                        {
                            cout << "Invalid role. Please enter 0 for User or 1 for Admin: ";
                            cin >> role;
                        }

                        if (registerUser(id, name, password, email, role))
                            cout << "Registration successful!" << endl;
                        else
                            cout << "Registration failed. User limit reached." << endl;
                    }
                    else if (mainChoice == 9 && admin)
                    {
                        clearScreen();
                        printHeader("Update User");
                        int userIdToUpdate;
                        cout << "Enter User ID to update: ";
                        cin >> userIdToUpdate;

                        int userIndex = findUserById(userIdToUpdate);
                        if(userIndex != -1)
                        {
                            string name, password, email;
                            int role;
                            cout << "Enter new Name (current: " << userName[userIndex] << "): ";
                            cin >> name;
                            cout << "Enter new Password (current: " << userPassword[userIndex] << "): ";
                            cin >> password;
                            cout << "Enter new Email (current: " << userEmail[userIndex] << "): ";
                            cin >> email;
                            cout << "Enter new Role (0 for User, 1 for Admin, current: "
                                 << (userRole[userIndex] == 1 ? "Admin" : "User") << "): ";
                            cin >> role;

                            while (role < 0 || role > 1)
                            {
                                cout << "Invalid role. Please enter 0 for User or 1 for Admin: ";
                                cin >> role;
                            }

                            userName[userIndex] = name;
                            userPassword[userIndex] = password;
                            userEmail[userIndex] = email;
                            userRole[userIndex] = role;

                            cout << "User updated successfully!" << endl;
                        }
                        else
                        {
                            cout << "User not found." << endl;
                        }

                    }
                    else if (mainChoice == 10 && admin)
                    {
                        clearScreen();
                        printHeader("Delete User");

                        int userIdToDelete;
                        cout << "Enter User ID to delete: ";
                        cin >> userIdToDelete;

                        int userIndex = findUserById(userIdToDelete);
                        if(userIndex != -1){
                            userCount--;
                            for(int i = userIndex; i < userCount; i++)
                            {
                                userId[i] = userId[i + 1];
                                userName[i] = userName[i + 1];
                                userPassword[i] = userPassword[i + 1];
                                userEmail[i] = userEmail[i + 1];
                                userRole[i] = userRole[i + 1];
                            }
                        }else{
                            cout << "User not found." << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                    holdScreen();
                    clearScreen();
                    printHeader("Welcome! " + userName[currentLoggedInUser]);
                    mainChoice = menu(MainMenu, menuSize);
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

int findUserById(int id){
    for(int i = 0; i < userCount; i++)
    {
        if (userId[i] == id)
        {
            return i;
        }
    }
    return -1; // User not found
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
