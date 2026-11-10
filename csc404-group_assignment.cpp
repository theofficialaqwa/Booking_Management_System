//------------------------------------------------------------------------------//
/*
    CSC099		: 	PROGRAMMING II (PROJECT)
    TITLE		  : 	Hotel Management System
    DUE DATE 	: 	WEEK 14 / 11 JULY 2026 (MONDAY BEFORE 12.00 p.m)
    LEADER		:   MUHAMMAD AQIEL WAZIF BIN ZULKIFLI     (2025224526)
    MEMBER 1	:   MUHAMMAD EZANI BIN ZULKEFLI           (2025226032)
    MEMBER 2	:   MUHAMMAD AMEER SUFI BIN ABDUL HAFIZ   (2025224902)
    MEMBER 3	:   MUHAMMAD ARIEF SHAHMI BIN SHAHID SHAM (2025246228)
    MEMBER 4	:	  DANIAL KHALIS BIN KHALILI             (2025421592)

    OUR OBJECTIVE:
    1- Room booking and availability management.
    2- Check-in and check-out process.
    3- Billing, payment, and receipt generation.
    4- Customer feedback and satisfaction survey module.
    5- Create total report sale for month.
    6- save and load previous customer data

*/
//------------------------------------------------------------------------------//

// library file
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct CustomerBlueprint
{
  string No_Ic;
  string Name;
  string FeedbackValidation;
  string RoomType;
  int Room;
  int DayIn;
  int Total_price;
  int Floor;
};

CustomerBlueprint CustomerData[3][12];

// Possible function use
void CustomerMenu();
void WelcomeScreen();
void ViewHotel();
void ViewPrice(CustomerBlueprint CustomerData[3][12], double Price[6]);
int package_check(CustomerBlueprint CustomerData[3][12], int count, int &loop);

void Registration(CustomerBlueprint CustomerData[3][12], double Price[6]);
void room_check(string &noIc, int &dayIn, int &add_room, int &floor, int &package, int &total_price, CustomerBlueprint CustomerData[3][12], double Price[6]);
void Checkout(CustomerBlueprint CustomerData[3][12]);
void Feedback(CustomerBlueprint CustomerData[3][12], string Feedbacks[252], int starCount[7][6]);

void AdminMenu(CustomerBlueprint CustomerData[3][12], double Price[6], string Feedbacks[252], int starCount[7][6]);
void Room_Price_Edit(double Price[6]);
void Edit_Customer_Data(CustomerBlueprint CustomerData[3][12], double Price[6]);
void PackageChange(CustomerBlueprint CustomerData[3][12], int packOption, int &floor, int &room);

void ReviewFeedbacks(CustomerBlueprint CustomerData[3][12], string Feedbacks[252], int starCount[7][6]);
void Data_Review(CustomerBlueprint CustomerData[3][12]);
void Sales_Report(CustomerBlueprint CustomerData[3][12]);
void SaveData(CustomerBlueprint CustomerData[3][12], int starCount[7][6]);
void LoadData(CustomerBlueprint CustomerData[3][12], int starCount[7][6]);

int main()
{ // main source for all coding both admin and custome

  // variable
  int option, PassAttempts = 0, ChoiceAttempts = 0;
  string Pass;
  // array
  string Feedbacks[252];
  int starCount[7][6] = {0};
  double Price[6] = {80.00, 120.00, 180.00, 250.00, 280.00, 320.00};

  LoadData(CustomerData, starCount); // Load hotel_database.csv and feedback_count.txt

  cout << fixed << setprecision(2); // because we dealing with RM
  while (ChoiceAttempts < 3)
  {

    system("cls");   // clear the system
    WelcomeScreen(); // calling function display
    cout << setw(105)
         << "Enter 1 for if you're admin and 2 if you're a Customer: " << endl;
    cout << setw(91) << "Are you an Admin or a Customer?\n"
         << endl;
    cout << "Input (Enter 0 to Exit) = ";
    cin >> option;

    if (option == 1)
    { // there is three option, 1 for admin, 2 for customer, 0
      // to end the command

      while (PassAttempts < 3)
      {
        cout << "Enter Admin Password (Enter 0 to go back) = ";
        cin >> Pass;

        if (Pass == "1234")
        { // the password for admin
          system("cls");
          WelcomeScreen();
          // displaying for admin home page
          AdminMenu(CustomerData, Price, Feedbacks, starCount);
          break;
        }
        else if (Pass == "0")
        { // incase the customer accidently press for 1
          // in main menu
          PassAttempts = 0;
          break;
        }
        else
        {
          PassAttempts++;

          if (PassAttempts == 3)
          {
            cout
                << "\nToo many wrong tries, program will automatically exit...";
            ChoiceAttempts = 3;
            break;
          }

          cout << "\nWrong password, try again.\n"
               << endl;
        }
      }
    }
    else if (option == 2)
    { // Customer home main
      system("cls");
      CustomerMenu();
      cout << "Select the option: ";
      cin >> option;
      system("cls");

      while (option != 0)
      {

        CustomerMenu();

        switch (option)
        {
        case 1:
        { // display hotel layout with room and floor
          ViewHotel();
          break;
        }
        case 2:
        { // display the room package with number of availability room
          ViewPrice(CustomerData, Price);
          break;
        }
        case 3:
        { // displaying check-in for customer
          Registration(CustomerData, Price);
          break;
        }
        case 4:
        { // displaying check-out for customer
          Checkout(CustomerData);
          break;
        }
        case 5:
        { // displaying feedback for current check-in customer
          Feedback(CustomerData, Feedbacks, starCount);
          SaveData(CustomerData, starCount);
          break;
        }
        default:
        { // other than above
          cout << "\nInvalid option,please try again\n"
               << endl;
          break;
        }
        }
        cout << "Select the option: ";
        cin >> option;
        system("cls");
      }
    }
    else if (option == 0)
    { // to end the program
      SaveData(CustomerData, starCount);
      break;
    }
    else // other than 0, 1, 2
    {
      ChoiceAttempts++;
      if (ChoiceAttempts == 3)
      {
        cout << "\nToo many invalid choices,program will automatically exit";
        cout << "Please refer to the cashier for further assitance...Thank "
                "you\n";
        break;
      }

      cout << "\nInvalid choice, try again.\n"
           << endl;
      system("pause");
    }
  }
  return 0;
}

void WelcomeScreen()
{ // header progra

  cout << setfill('=') << setw(148) << "=" << endl;
  cout << setfill(' ') << setw(80) << "WELCOME TO" << endl;
  cout << setfill(' ') << setw(81) << "TRANSLYVANIA'S HOTEL" << endl;
  cout << setfill('=') << setw(148) << "=" << endl
       << endl;
  cout << setfill(' ');
}

// admin home page
void AdminMenu(CustomerBlueprint CustomerData[3][12], double Price[6], string Feedbacks[252], int starCount[7][6])
{

  // variable
  int AdminChoice, option;

  do
  { // looping1 for adminchoice
    cout << setw(80) << "Welcome Admin!" << endl;
    cout << "\n[Admin Menu]" << endl;
    cout << "1. Edit Room Price" << endl;
    cout << "2. Edit Customer Data" << endl;
    cout << "3. Review Feedback" << endl;
    cout << "4. Review Customers Data" << endl;
    cout << "5. Sale Report" << endl;
    cout << "0. Exit Admin menu" << endl;
    cout << "Enter your choice: ";
    cin >> AdminChoice;
    cout << endl;

    switch (AdminChoice)
    {
    case 0:
    { // exit the home page
      return;
      break;
    }
    case 1:
    { // change current price with new one
      system("cls");
      WelcomeScreen();
      Room_Price_Edit(Price); // calling function
      system("cls");
      WelcomeScreen();
      option = 0;
      break;
    }
    case 2:
    { // change current Customer data with new one
      system("cls");
      WelcomeScreen();
      Edit_Customer_Data(CustomerData, Price); // calling function
      break;
    }
    case 3:
    { // review overall 7 question
      system("cls");
      WelcomeScreen();
      ReviewFeedbacks(CustomerData, Feedbacks, starCount); // calling function
      system("cls");
      WelcomeScreen();
      option = 0;
      break;
    }
    case 4:
    {                            // display all customer data at once
      Data_Review(CustomerData); // calling function
      system("cls");
      WelcomeScreen();
      option = 0;
      break;
    }
    case 5:
    { // display sales report	(sorting,min,max,total,average)
      system("cls");
      WelcomeScreen();
      Sales_Report(CustomerData); // calling function
      system("cls");
      WelcomeScreen();
      option = 0;
      break;
    }
    default:
    { // other than that, invalid
      system("cls");
      WelcomeScreen();
      cout << "\nInvalid Admin choice." << endl; // need extra word
      break;
    }
    }
  } while (option == 0);
}

void Room_Price_Edit(double Price[6])
{ // change price room

  // variable
  int choice, Loop;
  double PriceChange;

  do
  { // main loop
    Loop = 0;
    system("cls");
    WelcomeScreen();
    cout << "[Price list]" << endl;
    cout << "1.Compact Single = " << Price[0] << endl;
    cout << "2.Twin Room = " << Price[1] << endl;
    cout << "3.Big Room = " << Price[2] << endl;
    cout << "4.Family Room = " << Price[3] << endl;
    cout << "5.Large Family = " << Price[4] << endl;
    cout << "6.Family suite = " << Price[5] << endl
         << endl;
    cout << "To change price, input 1-6 (Input 0 to go back) :" << endl;
    cout << "\nInput = ";
    cin >> choice;

    while (choice != 0)
    {

      switch (choice)
      { // all case make with same code
      case 1:
      {

        cout << "\nEnter the new desired amount for the price = ";
        cin >> PriceChange;
        cout << "\nConfirm price change for this package? (Input 1 if yes, 0 if no) = ";
        cin >> choice;

        if (choice == 1)
        {
          Price[0] = PriceChange;
          cout << "\nPrice for the Compact Single package has been "
                  "successfully changed to "
               << Price[0] << endl;
        }
        else
        {
          cout << "\nPrice change cancelled." << endl
               << endl;
          cout << "\nInput 1 to go back to the price list or 0 to go back to "
                  "admin menu"
               << endl;
          cout << "Input = ";
          cin >> Loop;
          cout << "\n";
          system("cls");
          break;
        }

        break;
      }
      case 2:
      {

        cout << "\nEnter the new desired amount for the price = ";
        cin >> PriceChange;
        cout << "\nConfirm price change for this package? (Input 1 if yes, 0 "
                "if no) = ";
        cin >> choice;

        if (choice == 1)
        {
          Price[1] = PriceChange;
          cout << "\nPrice for the Twin Room package has been successfully "
                  "changed to "
               << Price[1] << endl;
        }
        else
        {
          cout << "\nPrice change cancelled." << endl
               << endl;
          cout << "\nInput 1 to go back to the price list or 0 to go back to "
                  "main menu."
               << endl;
          cout << "Input = ";
          cin >> Loop;
          cout << "\n";
          system("cls");
          break;
        }

        break;
      }
      case 3:
      {

        cout << "\nEnter the new desired amount for the price = ";
        cin >> PriceChange;
        cout << "\nConfirm price change for this package? (Input 1 if yes, 0 "
                "if no) = ";
        cin >> choice;

        if (choice == 1)
        {
          Price[2] = PriceChange;
          cout << "\nPrice for the Big Room package has been successfully "
                  "changed to "
               << Price[2] << endl;
        }
        else
        {
          cout << "\nPrice change cancelled." << endl
               << endl;
          cout << "\nInput 1 to go back to the price list or 0 to go back to "
                  "Admin menu."
               << endl;
          cout << "Input = ";
          cin >> Loop;
          cout << "\n";
          system("cls");
          break;
        }

        break;
      }
      case 4:
      {

        cout << "\nEnter the new desired amount for the price = ";
        cin >> PriceChange;
        cout << "\nConfirm price change for this package? (Input 1 if yes, 0 "
                "if no) = ";
        cin >> choice;

        if (choice == 1)
        {
          Price[3] = PriceChange;
          cout << "\nPrice for the Family Room package has been successfully "
                  "changed to "
               << Price[3] << endl;
        }
        else
        {
          cout << "\nPrice change cancelled." << endl
               << endl;
          cout << "\nInput 1 to go back to the price list or 0 to go back to "
                  "main menu."
               << endl;
          cout << "Input = ";
          cin >> Loop;
          cout << "\n";
          system("cls");
          break;
        }

        break;
      }
      case 5:
      {

        cout << "\nEnter the new desired amount for the price = ";
        cin >> PriceChange;
        cout << "\nConfirm price change for this package? (Input 1 if yes, 0 "
                "if no) = ";
        cin >> choice;

        if (choice == 1)
        {
          Price[4] = PriceChange;
          cout << "\nPrice for the Large Family package has been successfully "
                  "changed to "
               << Price[4] << endl;
        }
        else
        {
          cout << "\nPrice change cancelled." << endl
               << endl;
          cout << "\nInput 1 to go back to the price list or 0 to go back to "
                  "main menu."
               << endl;
          cout << "Input = ";
          cin >> Loop;
          cout << "\n";
          system("cls");
          break;
        }
      }
      case 6:
      {

        cout << "\nEnter the new desired amount for the price = ";
        cin >> PriceChange;
        cout << "\nConfirm price change for this package? (Input 1 if yes, 0 "
                "if no) = ";
        cin >> choice;

        if (choice == 1)
        {
          Price[5] = PriceChange;
          cout << "\nPrice for the Family Suite package has been successfully "
                  "changed to "
               << Price[5] << endl;
        }
        else
        {
          cout << "\nPrice change cancelled." << endl
               << endl;
          cout << "\nInput 1 to go back to the price list or 0 to go back to "
                  "main menu."
               << endl;
          cout << "Input = ";
          cin >> Loop;
          cout << "\n";
          system("cls");
          break;
        }
        break;
      }
      default:
      {

        cout << "\nInvalid option,please try again\n"
             << endl;
        Loop = 1;
        system("pause");
        break;
      }
      }

      if (choice > 0 && choice < 7)
      {
        cout << "\nInput 1 to go back to the price list or 0 to go back to "
                "main menu."
             << endl;
        cout << "Input = ";
        cin >> Loop;
        cout << "\n";
        system("cls");
        WelcomeScreen();
      }

      break;
    }

  } while (Loop == 1 || Loop != 0);
}

// hold you breath, this is long and confusing code
void Edit_Customer_Data(CustomerBlueprint CustomerData[3][12], double Price[6])
{

  // variable
  string temp_ic;
  int i, j, Reconfirm, attempts = 0, Loop = 0, found = 0,
                       choice; // Track invalid attempts

  while (attempts < 3)
  { // first loop for verification
    cout << "Enter a customer's Identity Card number (or 0 to cancel) = ";
    cin >> temp_ic;

    // Exit if the user inputs 0
    if (temp_ic == "0")
    {
      cout << "\nCancelling and returning to the Admin menu...\n"
           << endl;
      system("pause");
      system("cls");
      WelcomeScreen();
      return;
    }

    // Check if the IC number is exactly 12 characters long
    if (temp_ic.length() != 12)
    {
      cout << "\nInvalid IC number. IC must be exactly 12 characters long.\n"
           << endl;
      attempts++; // Increment invalid attempts
      continue;
    }

    // Reset found to 0 before starting the search each time
    found = 0;

    // Search for the IC number in the database
    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 12; j++)
      {
        if (CustomerData[i][j].No_Ic == temp_ic)
        {
          found = 1;
          break;
        }
      }
      if (found == 1)
        break;
    }

    // If the customer is not found
    if (found == 0)
    {
      cout << "\nCustomer data not found.\n"
           << endl;
      attempts++; // Increment invalid attempts

      // Check if attempts exceed 3
      if (attempts == 3)
      {
        cout << "\nToo many invalid attempts. Automatically returning to the "
                "Admin menu...\n"
             << endl;
        system("pause");
        system("cls");
        WelcomeScreen(); // Go back to the Admin menu after 3 failed attempts
        return;          // Exit and go to Admin menu
      }

      // Retry or return to Admin menu
      while (true)
      {
        cout << "Enter 1 to try again, 0 to return to Admin Menu: ";
        cin >> choice;

        if (choice == 1)
        {
          break; // Try again
        }
        else if (choice == 0)
        {
          cout << "Returning to the Admin menu...\n";
          system("cls");
          WelcomeScreen();
          return;
        }
        else
          cout << "\nInvalid input. Please enter 1 to retry or 0 to go back.\n"
               << endl;
      }
    }
    else
    {
      cout << "\nCustomer found. Proceeding with editing...\n"
           << endl;
      system("pause");
      Loop++;
      break; // IC is valid and found, exit loop
    }
  }

  // If the user exceeds the maximum invalid attempts
  if (attempts == 3)
  {
    cout << "Too many invalid attempts. Automatically returning to the Admin "
            "menu...\n"
         << endl;
    system("pause");
    system("cls");
    WelcomeScreen(); // Go back to the Admin menu after 3 failed attempts
    return;
  }
  while (Loop == 1)
  {

    int option;

    system("cls");
    WelcomeScreen();
    ViewPrice(CustomerData, Price);

    // Displays a customer's information (customers that have checked in)
    cout << "\n=====Customer's Information=====\n";
    cout << "IC Number: " << CustomerData[i][j].No_Ic << endl;
    cout << "Name: " << CustomerData[i][j].Name << endl;
    cout << "Estimated Rent Duration: " << CustomerData[i][j].DayIn << " days"
         << endl;
    cout << "Room Type Rented: " << CustomerData[i][j].RoomType << endl;
    cout << "Total Price: RM" << CustomerData[i][j].Total_price << endl;
    cout << "Room: " << CustomerData[i][j].Room + 1 << endl;
    cout << "Floor: " << CustomerData[i][j].Floor + 1 << endl;

    // Options for admin on what kind of data desired to edit/change
    cout << "\nWhich type of this customer's data would you like to "
            "edit/change?\n"
         << endl;
    cout << "1. IDENTITY CARD NUMBER\n";
    cout << "2. NAME\n";
    cout << "3. RENT DURATION\n";
    cout << "4. ROOM PACKAGE BOUGHT\n";
    cout << "0. RETURN TO ADMIN MENU\n";
    cout << "Enter your choice: ";

    cin >> option;
    cout << endl;

    if (option == 0)
    { // exit the customer edit data page
      break;
    }

    char confirm;

    system("cls");
    WelcomeScreen();
    ViewPrice(CustomerData, Price);

    // Displays a customer's information (customers that have checked in)
    cout << "\n\n=====Customer's Information=====\n";
    cout << "IC Number: " << CustomerData[i][j].No_Ic << endl;
    cout << "Name: " << CustomerData[i][j].Name << endl;
    cout << "Estimated Rent Duration: " << CustomerData[i][j].DayIn << " days"
         << endl;
    cout << "Room Type Rented: " << CustomerData[i][j].RoomType << endl;
    cout << "Total Price: RM" << CustomerData[i][j].Total_price << endl;
    cout << "Room: " << CustomerData[i][j].Room + 1 << endl;
    cout << "Floor: " << CustomerData[i][j].Floor + 1 << endl;

    switch (option)
    {
    case 1:
    { // change identity card number

      Reconfirm = 0;
      string newIc;

      cout << "Change " << CustomerData[i][j].No_Ic << " to: ";
      cin >> newIc;

      while (Reconfirm == 0)
      {
        cout << "Confirm change? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y' || confirm == 'n' ||
            confirm == 'N')
        {
          Reconfirm = 1;
        }
        else
        {
          cout << "Invalid input. Please enter 'y' or 'n' only.\n";
        }
      }

      if (confirm == 'y' || confirm == 'Y')
      {
        CustomerData[i][j].No_Ic = newIc;
        cout << "Customer's Identity Card Number has been successfully "
                "changed.\n"
             << endl;
      }
      else
        cout << "\nCancelled customer's Identity Card change...\n"
             << endl;
      break;
    }
    case 2:
    { // change customer name

      Reconfirm = 0;
      string newName;

      cout << "Change " << CustomerData[i][j].Name << " to: ";
      cin.ignore();
      getline(cin, newName);

      while (Reconfirm == 0)
      {
        cout << "Confirm change? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y' || confirm == 'n' ||
            confirm == 'N')
        {
          Reconfirm = 1;
        }
        else
        {
          cout << "Invalid input. Please enter 'y' or 'n' only.\n";
        }
      }

      if (confirm == 'y' || confirm == 'Y')
      {
        CustomerData[i][j].Name = newName;
        cout << "\nCustomer's name has been successfully changed.\n"
             << endl;
      }
      else
        cout << "\nCancelled customer's name change...\n"
             << endl;
      break;
    }
    case 3:
    { // change customer rent duration

      Reconfirm = 0;
      int newDuration;

      cout << "Change " << CustomerData[i][j].DayIn << " days to: ";
      cin >> newDuration;

      while (Reconfirm == 0)
      {
        cout << "Confirm change? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y' || confirm == 'n' ||
            confirm == 'N')
          Reconfirm = 1;
        else
          cout << "Invalid input. Please enter 'y' or 'n' only.\n";
      }

      if (confirm == 'y' || confirm == 'Y')
      {
        CustomerData[i][j].DayIn = newDuration;
        cout << "Duration has been successfully changed.\n"
             << endl;
      }

      else
      {
        cout << "\nCancelled customer's rent duration change...\n"
             << endl;
        break;
      }

      // Updates Total Price
      if (CustomerData[i][j].RoomType == "Compact Single")
      {
        CustomerData[i][j].Total_price = Price[0] * newDuration;
      }
      else if (CustomerData[i][j].RoomType == "Twin Room")
      {
        CustomerData[i][j].Total_price = Price[1] * newDuration;
      }
      else if (CustomerData[i][j].RoomType == "Big Room")
      {
        CustomerData[i][j].Total_price = Price[2] * newDuration;
      }
      else if (CustomerData[i][j].RoomType == "Family Room")
      {
        CustomerData[i][j].Total_price = Price[3] * newDuration;
      }
      else if (CustomerData[i][j].RoomType == "Large Family")
      {
        CustomerData[i][j].Total_price = Price[4] * newDuration;
      }
      else
      {
        CustomerData[i][j].Total_price = Price[5] * newDuration;
      }

      cout << "Customer's total price has been updated to RM"
           << CustomerData[i][j].Total_price << ".\n";
      break;
    }
    case 4:
    { // change customer package but not duration

      Reconfirm = 0;
      int packOption;
      string newPackage;

      cout << "Room Packages:\n";
      cout << "1. Compact Single\n2. Twin Room\n3. Big Room\n4. Family "
              "Room\n5. Large Family\n6. Family Suite\n";
      cout << "Change package from " << CustomerData[i][j].RoomType
           << " to (enter number): ";
      cin >> packOption;

      PackageChange(CustomerData, packOption, i, j);
      switch (packOption)
      {
      case 1:
      {
        newPackage = "Compact Single";
        break;
      }
      case 2:
      {
        newPackage = "Twin Room";
        break;
      }
      case 3:
      {
        newPackage = "Big Room";
        break;
      }
      case 4:
      {
        newPackage = "Family Room";
        break;
      }
      case 5:
      {
        newPackage = "Large Family";
        break;
      }
      case 6:
      {
        newPackage = "Family Suite";
        break;
      }
      default:
      {
        cout << "Invalid package number.\n";
        continue;
      }
      }
      while (Reconfirm == 0)
      {

        cout << "Confirm change? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y' || confirm == 'n' ||
            confirm == 'N')
        {

          Reconfirm = 1;
        }
        else
        {
          cout << "Invalid input. Please enter 'y' or 'n' only.\n";
        }
      }

      if (confirm == 'y' || confirm == 'Y')
      {
        CustomerData[i][j].RoomType = newPackage;
        cout << "Package has been successfully changed.\n"
             << endl;
        system("pause");
      }
      else
      {
        cout << "\nCancelled customer's package change...\n"
             << endl;
        system("pause");
        break;
      }
      // Updates Total Price
      if (CustomerData[i][j].RoomType == "Compact Single")
      {
        CustomerData[i][j].Total_price = Price[0] * CustomerData[i][j].DayIn;
      }
      else if (CustomerData[i][j].RoomType == "Twin Room")
      {
        CustomerData[i][j].Total_price = Price[1] * CustomerData[i][j].DayIn;
      }
      else if (CustomerData[i][j].RoomType == "Big Room")
      {
        CustomerData[i][j].Total_price = Price[2] * CustomerData[i][j].DayIn;
      }
      else if (CustomerData[i][j].RoomType == "Family Room")
      {
        CustomerData[i][j].Total_price = Price[3] * CustomerData[i][j].DayIn;
      }
      else if (CustomerData[i][j].RoomType == "Large Family")
      {
        CustomerData[i][j].Total_price = Price[4] * CustomerData[i][j].DayIn;
      }
      else
      {
        CustomerData[i][j].Total_price = Price[5] * CustomerData[i][j].DayIn;
      }

      cout << "Customer's total price has been updated to RM"
           << CustomerData[i][j].Total_price << ".\n";
      break;
    }
    default:
    {
      cout << "Invalid input. Please try again.\n";
      system("pause");
      break;
    }
    }

    if (option < 0 || option > 4)
    {
      system("cls");
      WelcomeScreen();
    }

    if (option > 0 && option < 4)
    {
      cout << "Do you want to change another data for this customer? (Input 1 "
              "to continue editing and 0 to return to Admin Menu)\n";
      cout << "Input : ";
      cin >> Loop;
    }
  }
  system("cls");
  WelcomeScreen();
}

void PackageChange(CustomerBlueprint CustomerData[3][12], int choice, int &floor, int &room)
{
  int package1[] = {1, 4, 7, 10};
  int package2[] = {0, 2, 3, 5, 6, 8, 9, 11};
  int package3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  int package4[] = {2, 3, 8, 9};
  int package5[] = {1, 4, 7, 10};
  int package6[] = {0, 5, 6, 11};

  int *rooms = NULL;
  int size = 0;
  int newFloor = 0;

  switch (choice)
  {
  case 1:
    rooms = package1;
    size = 4;
    newFloor = 0;
    break;

  case 2:
    rooms = package2;
    size = 8;
    newFloor = 0;
    break;

  case 3:
    rooms = package3;
    size = 12;
    newFloor = 1;
    break;

  case 4:
    rooms = package4;
    size = 4;
    newFloor = 2;
    break;

  case 5:
    rooms = package5;
    size = 4;
    newFloor = 2;
    break;

  case 6:
    rooms = package6;
    size = 4;
    newFloor = 2;
    break;

  default:
    cout << "Invalid package.\n";
    return;
  }

  for (int i = 0; i < size; i++)
  {
    if (CustomerData[newFloor][rooms[i]].No_Ic == "")
    {
      CustomerData[newFloor][rooms[i]] = CustomerData[floor][room];
      CustomerData[floor][room] = CustomerBlueprint();
      floor = newFloor;
      room = rooms[i];
      CustomerData[floor][room].Floor = floor;
      CustomerData[floor][room].Room = room;

      return;
    }
  }

  cout << "No available room for this package.\n";
}

void ReviewFeedbacks(CustomerBlueprint CustomerData[3][12], string Feedbacks[252], int starCount[7][6])
{

  // Counters for each question's stars
  int Input;

  string questions[7] = {"1. Amenities expectation", "2. Cleanliness rating",
                         "3. Staff helpfulness", "4. Dining experience",
                         "5. Wi-Fi quality", "6. Fair pricing",
                         "7. Overall satisfaction"};

  cout << "\n=== Customer Feedback Summary ===\n";
  for (int a = 0; a < 7; a++)
  {
    cout << "\n"
         << questions[a] << ":\n";

    for (int stars = 5; stars >= 0; stars--)
    {
      cout << stars << " stars: " << starCount[a][stars] << " people" << endl;
    }
  }

  cout << "Press any number to continue = ";
  cin >> Input;
  cin.ignore();
}

void Sales_Report(CustomerBlueprint CustomerData[3][12])
{
  int Loop, count;
  int total_price;
  double average_price;

  CustomerBlueprint occupied[36];

  do
  {
    system("cls");
    WelcomeScreen();

    cout << "\n========== Hotel Sale Report ==========\n";

    count = 0;
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 12; j++)
      {
        if (CustomerData[i][j].No_Ic != "")
        {
          occupied[count] = CustomerData[i][j];
          count++;
        }
      }
    }

    if (count == 0)
    {
      cout << "\nNo customer has checked in yet. No report to generate.\n";
    }
    else
    {
      for (int x = 0; x < count - 1; x++)
      { // Bubble Sort Highest to low
        for (int y = 0; y < count - 1; y++)
        {
          if (occupied[y].Total_price < occupied[y + 1].Total_price)
          {
            CustomerBlueprint temp = occupied[y];
            occupied[y] = occupied[y + 1];
            occupied[y + 1] = temp;
          }
        }
      }

      total_price = 0;
      for (int x = 0; x < count; x++)
      {
        total_price += occupied[x].Total_price; // Sum
      }

      average_price = (double)total_price / count; // Average

      cout << "\n====== Highest Spending Customer ======\n";
      cout << "Name		: " << occupied[0].Name << endl;
      cout << "Room 		: " << occupied[0].Room + 1 << endl;
      cout << "Floor		: " << occupied[0].Floor + 1 << endl;
      cout << "Total Price	: RM" << fixed << setprecision(2) << occupied[0].Total_price << endl;

      cout << "\n====== Lowest Spending Customer ======\n";
      cout << "Name		: " << occupied[count - 1].Name << endl;
      cout << "Room 		: " << occupied[count - 1].Room + 1 << endl;
      cout << "Floor		: " << occupied[count - 1].Floor + 1 << endl;
      cout << "Total Price	: RM" << fixed << setprecision(2) << occupied[count - 1].Total_price << endl;

      cout << "\n====== All Occupied Rooms (Sorted by Total Price) =====\n";
      for (int x = 0; x < count; x++)
      {
        cout << setw(2) << x + 1 << ". " << setw(15) << occupied[x].Name
             << "\t| Room " << setw(2) << occupied[x].Room + 1
             << "\t| Floor" << setw(2) << occupied[x].Floor + 1
             << "\t| RM" << fixed << setprecision(2) << occupied[x].Total_price << endl;
      }

      cout << "\n---- Summary ----\n";
      cout << "Total occupied rooms 	: " << count << endl;
      cout << "Total revenue		: RM" << fixed << setprecision(2) << total_price << endl;
      cout << "Average revenue	: RM" << fixed << setprecision(2) << average_price << endl;
    }

    cout << "\n\nInput 0 to go back to admin's menu." << endl;
    cout << "Input = ";
    cin >> Loop;
    cout << "\n";
  } while (Loop == 1);
}

void Data_Review(CustomerBlueprint CustomerData[3][12])
{

  int Loop; // local variable

  do
  { // main loop
    bool dataFound;
    system("cls");
    WelcomeScreen();

    cout << "\n========== All Checked-In Customer Data ==========\n";

    dataFound = false;
    // it will show all current active customer only
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 12; j++)
      {
        if (CustomerData[i][j].No_Ic != "")
        {
          dataFound = true;
          cout << "\n--------------------------------------";
          cout << "\nNo IC       : " << CustomerData[i][j].No_Ic;
          cout << "\nName        : " << CustomerData[i][j].Name;
          cout << "\nStay (days) : " << CustomerData[i][j].DayIn;
          cout << "\nPackage     : " << CustomerData[i][j].RoomType;
          cout << "\nTotal Price : RM" << CustomerData[i][j].Total_price;
          cout << "\nRoom        : " << CustomerData[i][j].Room + 1;
          cout << "\nFloor       : " << CustomerData[i][j].Floor + 1;
          cout << "\n--------------------------------------";
        }
      }
    }

    if (!dataFound)
      cout << "\nNo customers have checked in yet.\n";

    cout << "\n\nInput 0 to go to back to admin's menu." << endl;
    cout << "Input = ";
    cin >> Loop;
    cout << "\n";

  } while (Loop == 1);
}

// Customer Source Code

void CustomerMenu()
{

  WelcomeScreen();
  cout << "1. View Hotel Room\n";
  cout << "2. View Hotel Price\n";
  cout << "3. Check in / Book Hotel Room\n";
  cout << "4. Checkout & Billing\n";
  cout << "5. Feedback\n";
  cout << "0. Exit\n";
}

void ViewHotel()
{ // display layout onl

  cout << "Hotel Room and Floor" << endl;
  cout << "	        __________" << endl;
  cout << "[R3] [R2] [R1] |  Lobby   | [R12] [R11] [R10]" << endl;
  cout << "	       |  Floor 1 | " << endl;
  cout << "[R4] [R5] [R6] |__________| [R7]  [R8]  [R9]" << endl;
  cout << endl;

  cout << "	        __________" << endl;
  cout << "[R3] [R2] [R1] |  Lobby   | [R12] [R11] [R10]" << endl;
  cout << "	       |  Floor 2 | " << endl;
  cout << "[R4] [R5] [R6] |__________| [R7]  [R8]  [R9]" << endl;
  cout << endl;

  cout << "	        __________" << endl;
  cout << "[R3] [R2] [R1] |  Lobby   | [R12] [R11] [R10]" << endl;
  cout << "	       |  Floor 3 | " << endl;
  cout << "[R4] [R5] [R6] |__________| [R7]  [R8]  [R9]" << endl;
  cout << endl;
}

void ViewPrice(CustomerBlueprint CustomerData[3][12], double Price[6])
{ // it display price room and for availability,we calling function

  // variable
  int slot = 0;
  int numbering = 0;

  cout << endl;
  cout << setfill(' ') << setw(90) << "--Room Price & Availability--" << endl;
  cout << setfill('-') << setw(160);
  cout << "\nRoom Type		" << "			Bed type			" << "Capacity		" << "Price(RM)	" << "	Slot Left" << endl;
  cout << setfill('-') << setw(166);
  cout << "\n1.Compact Single	" << "		1 x Single bed				" << "1 Person		" << Price[0] << "			[" << package_check(CustomerData, slot, numbering) << " /4 ] room left" << endl;
  cout << "2.Twin Room		" << "		2 x Single bed				" << "2 Person		" << Price[1] << "			[" << package_check(CustomerData, slot, numbering) << " /8 ] room left" << endl;
  cout << "3.Big Room		" << "		1 Queen bed + 1 x Single bed		" << "3 Person		" << Price[2] << "			[" << package_check(CustomerData, slot, numbering) << "/12] room left" << endl;
  cout << "4.Familly room		" << "		2 Queen bed				" << "4 Person		" << Price[3] << "			[" << package_check(CustomerData, slot, numbering) << " /4 ] room left" << endl;
  cout << "5.Large Family		" << "		2 Queen bed + 1 x Single bed		" << "5 Person		" << Price[4] << "			[" << package_check(CustomerData, slot, numbering) << " /4 ] room left" << endl;
  cout << "6.Family Suite		" << "		2 Queen bed + 2 x Single bed		" << "6 Person		" << Price[5] << "			[" << package_check(CustomerData, slot, numbering) << " /4 ] room left" << endl;
  cout << setfill('-') << setw(148) << '-';
  cout << endl;
}

int package_check(CustomerBlueprint CustomerData[3][12], int count, int &loop)
{ // all loop is same and it depend on local array to check

  // local variable
  int room, j;

  // local array
  int package1[4] = {1, 4, 7, 10};
  int package2[8] = {0, 2, 3, 5, 6, 8, 9, 11};
  int package4[4] = {2, 3, 8, 9};
  int package5[4] = {1, 4, 7, 10};
  int package6[4] = {0, 5, 6, 11};

  switch (loop)
  {
  case 0:
  {
    for (j = 0; j < 4; j++)
    {
      room = package1[j];
      if (CustomerData[0][room].No_Ic == "")
        count++;
    }
    break;
  }
  case 1:
  {
    for (j = 0; j < 8; j++)
    {
      room = package2[j];
      if (CustomerData[0][room].No_Ic == "")
        count++;
    }
    break;
  }
  case 2:
  {
    for (j = 0; j < 12; j++)
    {
      if (CustomerData[1][j].No_Ic == "")
        count++;
    }
    break;
  }
  case 3:
  {
    for (j = 0; j < 4; j++)
    {
      room = package4[j];
      if (CustomerData[2][room].No_Ic == "")
        count++;
    }
    break;
  }
  case 4:
  {
    for (j = 0; j < 4; j++)
    {
      room = package5[j];
      if (CustomerData[2][room].No_Ic == "")
        count++;
    }
    break;
  }
  case 5:
  {
    for (j = 0; j < 4; j++)
    {
      room = package6[j];
      if (CustomerData[2][room].No_Ic == "")
        count++;
    }
    break;
  }
  default:
  {
    cout << "default" << endl;
    break;
  }
  }
  loop++;
  return count;
}

void Registration(CustomerBlueprint CustomerData[3][12], double Price[6])
{
  string noIc, name;
  int i, j, roomcount;
  int dayIn = 0, add_room = 0, floor = 0, package = 0, total_price = 0,
      icAttempts = 0, IcDuplicate = 0, dayAttempts = 0, dayAttempts2 = 0,
      packageAttempts = 0;

  for (int f = 0; f < 3; f++)
  {
    for (int r = 0; r < 12; r++)
    {

      if (CustomerData[f][r].No_Ic != "")
      {
        roomcount++;
      }
    }
  }

  if (roomcount < 36)
  {
    cout << "Please enter the details\n";
    while (icAttempts < 3)
    {
      cout << "\nInsert Identity Card Number (without -) : ";
      cin >> noIc;

      if (noIc.length() != 12)
      {
        cout << "\nInvalid IC Number. Please enter exactly 12 digits.\n\n";
        icAttempts++;
        continue;
      }

      // Check for duplicate
      IcDuplicate = 0;
      for (i = 0; i < 3 && !IcDuplicate; i++)
      {
        for (j = 0; j < 12; j++)
        {
          if (CustomerData[i][j].No_Ic == noIc)
          {
            IcDuplicate = 1;
            break;
          }
        }
      }

      if (IcDuplicate)
      {
        cout << "\nThis IC number has already been registered. Please try "
                "another one.\n\n";
        icAttempts++;
      }
      else
      {
        break; // Valid and not a duplicate
      }
    }

    if (icAttempts >= 3)
    {
      cout << "Too many invalid tries, reverting back to customer menu...\n\n";
      cout << "Please refer to the cashier for further assitance...Thank you\n";
      system("pause");
      system("cls");
      CustomerMenu();
      return;
    }

    cout << "\nPlease enter your name/alias : ";
    cin.ignore();
    getline(cin, name);

    while (dayAttempts < 3)
    {
      cout << "\nPlease enter the number of days you're planning on staying : ";
      cin >> dayIn;
      if (dayIn <= 0)
      {
        cout << "\nInvalid input. Days must be more than 0.\n";
        dayAttempts++;
      }
      else if (dayIn > 30)
      {
        cout << "\nMaximum stay is up until 30 days only,please re-enter (1 - 30 "
                "days only) :";
        dayAttempts2++;
      }
      else
        break; // valid input
    }

    if (dayAttempts >= 3)
    {
      cout << "Too many invalid tries, reverting back to customer menu...\n\n";
      cout << "Please refer to the cashier for further assitance...Thank you\n";
      system("pause");
      system("cls");
      CustomerMenu();
      return;
    }
    ViewPrice(CustomerData, Price);

    while (packageAttempts < 3)
    {
      cout << "Choose your package (1-6) (enter 0 to cancel): ";
      cin >> package;

      if (package == 0)
      {
        cout << "\nCheck-in cancelled, returning to customer menu...\n";
        cout << "Please refer to the cashier for further assitance...Thank you\n";
        system("pause");
        system("cls");
        CustomerMenu();
        return;
      }
      else if (package >= 1 && package <= 6)
        break; // valid package
      else
      {
        cout << "\nInvalid package number. Please enter a number between 1 and "
                "6.\n\n";
        packageAttempts++;
      }
    }
    if (packageAttempts >= 3)
    {
      cout << "Too many invalid attempts. Check-in automatically cancelled. "
              "Returning to customer menu...\n\n";
      cout << "Please refer to the cashier for further assitance...Thank you\n";
      system("pause");
      system("cls");
      CustomerMenu();
      return;
    }

    room_check(noIc, dayIn, add_room, floor, package, total_price, CustomerData,
               Price);

    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 12; j++)
      {
        if (i == floor - 1 && j == add_room - 1 &&
            CustomerData[i][j].No_Ic == noIc)
        {
          CustomerData[i][j].Name = name;
          CustomerData[i][j].DayIn = dayIn;
          CustomerData[i][j].Total_price = total_price;
          CustomerData[i][j].Room = j;
          CustomerData[i][j].Floor = i;
        }
      }
    }
  }
  else
  {
    cout << "\nSorry, all the room is currently occupied with other customer.\nPlease refer to the cashier for further assitance...Thank you\n\n";
  }
}

void room_check(string &noIc, int &dayIn, int &add_room, int &floor, int &package, int &total_price, CustomerBlueprint CustomerData[3][12], double Price[6])
{ // package, total_price, dayIn, noIc, add_room, floor

  int newPackage, PackageRetry = 1, j;
  if (package <= 6 && package >= 0)
  {

    switch (package)
    {
    case 1:
    { // Register for package 1
      total_price = dayIn * Price[0];

      if (CustomerData[0][1].No_Ic == "")
      {
        CustomerData[0][1].No_Ic = noIc;
        CustomerData[0][1].RoomType = "Compact Single";
        add_room = 2;
      }
      else if (CustomerData[0][4].No_Ic == "")
      {
        CustomerData[0][4].No_Ic = noIc;
        CustomerData[0][4].RoomType = "Compact Single";
        add_room = 5;
      }
      else if (CustomerData[0][7].No_Ic == "")
      {
        CustomerData[0][7].No_Ic = noIc;
        CustomerData[0][7].RoomType = "Compact Single";
        add_room = 8;
      }
      else if (CustomerData[0][10].No_Ic == "")
      {
        CustomerData[0][10].No_Ic = noIc;
        CustomerData[0][10].RoomType = "Compact Single";
        add_room = 11;
      }
      else
      {
        while (PackageRetry < 3)
        {
          cout << "\nRoom for Package 1 (Compact Single) is full.\n";
          cout << "Please consider selecting another package.\n";
          cout << "Enter a new package number (1-6) or 0 to cancel: ";
          cin >> newPackage;

          if (newPackage == 0)
          {
            cout << "\nCheck-in cancelled, returning to customer menu...\n";
            cout << "Please refer to the cashier for further assitance...Thank "
                    "you\n";
            system("pause");
            system("cls");
            CustomerMenu();
            return;
          }

          if (newPackage >= 1 && newPackage <= 6)
          {
            package = newPackage;
            room_check(noIc, dayIn, add_room, floor, package, total_price,
                       CustomerData, Price);
            return; // successful retry
          }
          else
          {
            cout << "Invalid package number. Please enter a value between 1 "
                    "and 6 or 0 to cancel.\n"
                 << endl;
            PackageRetry++;
          }
        }
        cout << "\nToo many invalid attempts. Returning to customer menu...\n";
        cout << "Please refer to the cashier for further assitance...Thank "
                "you\n";
        system("pause");
        system("cls");
        CustomerMenu();
        return;
      }

      floor = 1;
      cout << "\nPackage bought : Compact Single" << endl;
      cout << "\nYour room is Room " << add_room << " on floor " << floor
           << endl;
      cout << "Total price is RM" << total_price << endl
           << endl;
      break;
    }

    case 2:
    { // Register for package 2
      total_price = dayIn * Price[1];

      if (CustomerData[0][0].No_Ic == "")
      { // room[1][1]
        CustomerData[0][0].No_Ic = noIc;
        CustomerData[0][0].RoomType = "Twin Room";
        add_room = 1;
      }
      else if (CustomerData[0][2].No_Ic == "")
      { // room[1][3]
        CustomerData[0][2].No_Ic = noIc;
        CustomerData[0][2].RoomType = "Twin Room";
        add_room = 3;
      }
      else if (CustomerData[0][3].No_Ic == "")
      { // room[1][4]
        CustomerData[0][3].No_Ic = noIc;
        CustomerData[0][3].RoomType = "Twin Room";
        add_room = 4;
      }
      else if (CustomerData[0][5].No_Ic == "")
      { // room[1][6]
        CustomerData[0][5].No_Ic = noIc;
        CustomerData[0][5].RoomType = "Twin Room";
        add_room = 6;
      }
      else if (CustomerData[0][6].No_Ic == "")
      { // room[1][7]
        CustomerData[0][6].No_Ic = noIc;
        CustomerData[0][6].RoomType = "Twin Room";
        add_room = 7;
      }
      else if (CustomerData[0][8].No_Ic == "")
      { // room[1][9]
        CustomerData[0][8].No_Ic = noIc;
        CustomerData[0][8].RoomType = "Twin Room";
        add_room = 9;
      }
      else if (CustomerData[0][9].No_Ic == "")
      { // room[1][10]
        CustomerData[0][9].No_Ic = noIc;
        CustomerData[0][9].RoomType = "Twin Room";
        add_room = 10;
      }
      else if (CustomerData[0][11].No_Ic == "")
      { // room[1][12]
        CustomerData[0][11].No_Ic = noIc;
        CustomerData[0][11].RoomType = "Twin Room";
        add_room = 12;
      }
      else
      {
        while (PackageRetry < 4)
        {
          cout << "\nRoom for Package 2 (Twin Room) is full.\n";
          cout << "Please consider selecting another package.\n";
          cout << "Enter a new package number (1-6) or 0 to cancel: ";
          cin >> newPackage;

          if (newPackage == 0)
          {
            cout << "\nCheck-in cancelled, returning to customer menu...\n";
            cout << "Please refer to the cashier for further assitance...Thank "
                    "you\n";
            system("pause");
            system("cls");
            CustomerMenu();
            return;
          }

          if (newPackage >= 1 && newPackage <= 6)
          {
            package = newPackage;
            room_check(noIc, dayIn, add_room, floor, package, total_price,
                       CustomerData, Price);
            return; // successful retry
          }
          else
          {
            cout << "Invalid package number. Please enter a value between 1 "
                    "and 6 or 0 to cancel.\n"
                 << endl;
            PackageRetry++;
          }
        }
        cout << "\nToo many invalid attempts. Returning to customer menu...\n";
        cout << "Please refer to the cashier for further assitance...Thank "
                "you\n";
        system("pause");
        system("cls");
        CustomerMenu();
        return;
      }
      floor = 1;
      // we should put room package 2 on 1st floor : [1, 3, 4, 6, 7, 9, 10, 12]
      cout << "\nPackage bought : Twin Room" << endl;
      cout << "\nyour room is Room " << add_room << " on floor " << floor
           << endl;
      cout << "Total price is RM" << total_price << endl
           << endl;
      break;
    }
    case 3:
    { // Register for package 3
      total_price = dayIn * Price[2];
      for (j = 0; j < 12; j++)
      {
        if (CustomerData[1][j].No_Ic == "")
        {
          CustomerData[1][j].No_Ic = noIc;
          CustomerData[1][j].RoomType = "Big Room";
          add_room = j + 1;
          floor = 2;

          cout << "\nPackage bought : Big Room" << endl;
          cout << "\nYour room is Room " << add_room << " on floor " << floor
               << endl;
          cout << "Total price is RM" << total_price << endl
               << endl;
          break;
        }
      }
      if (j == 12)
      {
        while (PackageRetry < 4)
        {
          cout << "\nRoom for Package 3 (Big Room) is full.\n";
          cout << "Please consider selecting another package.\n";
          cout << "Enter a new package number (1-6) or 0 to cancel: ";
          cin >> newPackage;

          if (newPackage == 0)
          {
            cout << "\nCheck-in cancelled, returning to customer menu...\n";
            cout << "Please refer to the cashier for further assitance...Thank "
                    "you\n";
            system("pause");
            system("cls");
            CustomerMenu();
            return;
          }

          if (newPackage >= 1 && newPackage <= 6)
          {
            package = newPackage;
            room_check(noIc, dayIn, add_room, floor, package, total_price,
                       CustomerData, Price);
            return; // successful retry
          }
          else
          {
            cout << "Invalid package number. Please enter a value between 1 "
                    "and 6 or 0 to cancel.\n"
                 << endl;
            PackageRetry++;
          }
        }
        cout << "\nToo many invalid attempts. Returning to customer menu...\n";
        cout << "Please refer to the cashier for further assitance...Thank "
                "you\n";
        system("pause");
        system("cls");
        CustomerMenu();
        return;
      }

      break;
    }
    case 4:
    { // Register for package 4
      total_price = dayIn * Price[3];

      if (CustomerData[2][2].No_Ic == "")
      { // room[3][3]
        CustomerData[2][2].No_Ic = noIc;
        CustomerData[2][2].RoomType = "Family Room";
        add_room = 3;
      }
      else if (CustomerData[2][3].No_Ic == "")
      { // room[3][4]
        CustomerData[2][3].No_Ic = noIc;
        CustomerData[2][3].RoomType = "Family Room";
        add_room = 4;
      }
      else if (CustomerData[2][8].No_Ic == "")
      { // room[3][9]
        CustomerData[2][8].No_Ic = noIc;
        CustomerData[2][8].RoomType = "Family Room";
        add_room = 9;
      }
      else if (CustomerData[2][9].No_Ic == "")
      { // room[3][10]
        CustomerData[2][9].No_Ic = noIc;
        CustomerData[2][9].RoomType = "Family Room";
        add_room = 10;
      }
      else
      {
        while (PackageRetry < 4)
        {
          cout << "\nRoom for Package 4 (Family Room) is full.\n";
          cout << "Please consider selecting another package.\n";
          cout << "Enter a new package number (1-6) or 0 to cancel: ";
          cin >> newPackage;

          if (newPackage == 0)
          {
            cout << "\nCheck-in cancelled, returning to customer menu...\n";
            cout << "Please refer to the cashier for further assitance...Thank "
                    "you\n";
            system("pause");
            system("cls");
            CustomerMenu();
            return;
          }

          if (newPackage >= 1 && newPackage <= 6)
          {
            package = newPackage;
            room_check(noIc, dayIn, add_room, floor, package, total_price,
                       CustomerData, Price);
            return; // successful retry
          }
          else
          {
            cout << "Invalid package number. Please enter a value between 1 "
                    "and 6 or 0 to cancel.\n"
                 << endl;
            PackageRetry++;
          }
        }
        cout << "\nToo many invalid attempts. Returning to customer menu...\n";
        cout << "Please refer to the cashier for further assitance...Thank "
                "you\n";
        system("pause");
        system("cls");
        CustomerMenu();
        return;
      }
      floor = 3;
      // we should put room package 4 on 3rd floor : [3, 4, 9, 10]
      cout << "\nPackage bought : Family Room" << endl;
      cout << "\nyour room is Room " << add_room << " on floor " << floor
           << endl;
      cout << "Total price is RM" << total_price << endl
           << endl;
      break;
    }
    case 5:
    { // Register for package 5
      total_price = dayIn * Price[4];

      if (CustomerData[2][1].No_Ic == "")
      { // room[3][2]
        CustomerData[2][1].No_Ic = noIc;
        CustomerData[2][1].RoomType = "Large Family";
        add_room = 2;
      }
      else if (CustomerData[2][4].No_Ic == "")
      { // room[3][5]
        CustomerData[2][4].No_Ic = noIc;
        CustomerData[2][4].RoomType = "Large Family";
        add_room = 5;
      }
      else if (CustomerData[2][7].No_Ic == "")
      { // room[3][8]
        CustomerData[2][7].No_Ic = noIc;
        CustomerData[2][7].RoomType = "Large Family";
        add_room = 8;
      }
      else if (CustomerData[2][10].No_Ic == "")
      { // room[3][11]
        CustomerData[2][10].No_Ic = noIc;
        CustomerData[2][10].RoomType = "Large Family";
        add_room = 11;
      }
      else
      {
        while (PackageRetry < 4)
        {
          cout << "\nRoom for Package 5 (Large Family) is full.\n";
          cout << "Please consider selecting another package.\n";
          cout << "Enter a new package number (1-6) or 0 to cancel: ";
          cin >> newPackage;

          if (newPackage == 0)
          {
            cout << "\nCheck-in cancelled, returning to customer menu...\n";
            cout << "Please refer to the cashier for further assitance...Thank "
                    "you\n";
            system("pause");
            system("cls");
            CustomerMenu();
            return;
          }

          if (newPackage >= 1 && newPackage <= 6)
          {
            package = newPackage;
            room_check(noIc, dayIn, add_room, floor, package, total_price,
                       CustomerData, Price);
            return; // successful retry
          }
          else
          {
            cout << "Invalid package number. Please enter a value between 1 "
                    "and 6 or 0 to cancel.\n"
                 << endl;
            PackageRetry++;
          }
        }
        cout << "\nToo many invalid attempts. Returning to customer menu...\n";
        cout << "Please refer to the cashier for further assitance...Thank "
                "you\n";
        system("pause");
        system("cls");
        CustomerMenu();
        return;
      }
      floor = 3;
      // we should put room package 5 on 3rd floor : [2, 5, 8, 11]
      cout << "\nPackage bought : Large Family" << endl;
      cout << "\nyour room is Room " << add_room << " on floor " << floor
           << endl;
      cout << "Total price is RM" << total_price << endl
           << endl;
      break;
    }
    case 6:
    { // Register for package 6
      total_price = dayIn * Price[5];

      if (CustomerData[2][0].No_Ic == "")
      { // room[3][1]
        CustomerData[2][0].No_Ic = noIc;
        CustomerData[2][0].RoomType = "Family Suite";
        add_room = 1;
      }
      else if (CustomerData[2][5].No_Ic == "")
      { // room[3][6]
        CustomerData[2][5].No_Ic = noIc;
        CustomerData[2][5].RoomType = "Family Suite";
        add_room = 6;
      }
      else if (CustomerData[2][6].No_Ic == "")
      { // room[3][7]
        CustomerData[2][6].No_Ic = noIc;
        CustomerData[2][6].RoomType = "Family Suite";
        add_room = 7;
      }
      else if (CustomerData[2][11].No_Ic == "")
      { // room[3][12]
        CustomerData[2][11].No_Ic = noIc;
        CustomerData[2][11].RoomType = "Family Suite";
        add_room = 12;
      }
      else
      {
        while (PackageRetry < 4)
        {
          cout << "\nRoom for Package 6 (Family Suite) is full.\n";
          cout << "Please consider selecting another package.\n";
          cout << "Enter a new package number (1-6) or 0 to cancel: ";
          cin >> newPackage;

          if (newPackage == 0)
          {
            cout << "\nCheck-in cancelled, returning to customer menu...\n";
            cout << "Please refer to the cashier for further assitance...Thank "
                    "you\n";
            system("pause");
            system("cls");
            CustomerMenu();
            return;
          }

          if (newPackage >= 1 && newPackage <= 6)
          {
            package = newPackage;
            room_check(noIc, dayIn, add_room, floor, package, total_price,
                       CustomerData, Price);
            return; // successful retry
          }
          else
          {
            cout << "Invalid package number. Please enter a value between 1 "
                    "and 6 or 0 to cancel.\n"
                 << endl;
            PackageRetry++;
          }
        }
        cout << "\nToo many invalid attempts. Returning to customer menu...\n";
        cout << "Please refer to the cashier for further assitance...Thank "
                "you\n";
        system("pause");
        system("cls");
        CustomerMenu();
        return;
      }
      floor = 3;
      // we should put room package 6 on 3rd floor : [1, 6, 7, 12]
      cout << "\nPackage bought : Family Suite" << endl;
      cout << "\nyour room is Room " << add_room << " on floor " << floor
           << endl;
      cout << "Total price is RM" << total_price << endl
           << endl;
      break;
    }
    default:
    {
      cout << "Check-in cancelled!" << endl;
      break;
    }
    }
  }
  else
  {
    system("cls");
    CustomerMenu();
    ViewPrice(CustomerData, Price);
    cout << "invalid package. Please try again." << endl
         << endl; // change this?
  }
}

void Checkout(CustomerBlueprint CustomerData[3][12])
{
  string temp_ic;
  int opt, found = 0, icAttempt = 0;

  while (icAttempt < 3)
  {
    cout << "Enter IC Number to Checkout (or 0 to cancel): ";
    cin >> temp_ic;

    if (temp_ic == "0")
    {
      cout << "\nCheckout process cancelled...\n\n";
      system("pause");
      system("cls");
      CustomerMenu();
      return;
    }

    // Length check
    if (temp_ic.length() != 12)
    {
      cout << "\nInvalid IC Number. Please enter exactly 12 characters.\n\n";
      icAttempt++;
      continue;
    }

    // Check if IC exists in the records
    found = 0;
    for (int i = 0; i < 3 && found == 0; i++)
    {
      for (int j = 0; j < 12 && found == 0; j++)
      {
        if (CustomerData[i][j].No_Ic == temp_ic)
        {
          found = 1;

          // Display receipt
          cout << setw(50) << "" << setfill('=') << setw(50) << "="
               << setfill(' ') << endl;
          cout << setw(68) << "" << "HOTEL RECEIPT" << endl;
          cout << setw(50) << "" << setfill('=') << setw(50) << "="
               << setfill(' ') << endl;

          cout << setw(50) << "" << left << setw(20) << "Customer Name" << ": "
               << right << setw(28) << CustomerData[i][j].Name << endl;
          cout << setw(50) << "" << left << setw(20) << "IC Number" << ": "
               << right << setw(28) << CustomerData[i][j].No_Ic << endl;
          cout << setw(50) << "" << left << setw(20) << "Duration" << ": "
               << right << setw(19) << CustomerData[i][j].DayIn << " night(s)"
               << endl;
          cout << setw(50) << "" << left << setw(20) << "Total Price"
               << ":                       RM" << fixed << setprecision(2)
               << CustomerData[i][j].Total_price << endl;
          cout << setw(50) << "" << setfill('=') << setw(50) << "="
               << setfill(' ') << endl;

          // Payment options
          cout << setw(54) << "" << "How would you like to settle your payment?"
               << endl;
          cout << setw(50) << "" << setfill('=') << setw(50) << "="
               << setfill(' ') << endl;
          cout << setw(50) << "" << left << setw(20) << "Cash" << ": " << right
               << setw(28) << "Input 1" << endl;
          cout << setw(50) << "" << left << setw(20) << "Card" << ": " << right
               << setw(28) << "Input 2" << endl;
          cout << setw(50) << "" << setfill('=') << setw(50) << "="
               << setfill(' ') << endl
               << endl;

          int attempts = 0;
          while (attempts < 3)
          {
            cout << "Select the option (Input 0 to cancel): ";
            cin >> opt;

            if (opt == 0)
            {
              cout << "\nPayment has been successfully cancelled...\n\n";
              return;
            }
            else if (opt == 1 || opt == 2)
            {
              cout << setw(50) << "" << setfill('=') << setw(50) << "="
                   << setfill(' ') << endl;
              cout << setw(60) << "" << "Thank you for staying with us!"
                   << endl;
              cout << setw(50) << "" << setfill('=') << setw(50) << "="
                   << setfill(' ') << endl;

              // Clear data
              CustomerData[i][j].Name = "";
              CustomerData[i][j].No_Ic = "";
              CustomerData[i][j].Total_price = 0;
              CustomerData[i][j].DayIn = 0;
              CustomerData[i][j].FeedbackValidation = "";
              return;
            }
            else
            {
              cout << "Invalid option. Please try again.\n";
              attempts++;
            }
          }

          cout << "\nToo many invalid attempts. Payment has been automatically "
                  "cancelled.\n";
          cout << "Please refer to the cashier for any further "
                  "assitance...Thank you\n";
          return;
        }
      }
    }

    if (found == 0)
    {
      cout << "\nThis IC number has not been registered. Please try again.\n\n";
      icAttempt++;
    }
  }

  cout << "\nToo many invalid tries, automatically reverting back to customer "
          "menu...\n\n";
  cout << "Please refer to the cashier for further assitance...Thank you\n";
  system("pause");
  system("cls");
  CustomerMenu();
}

void Feedback(CustomerBlueprint CustomerData[3][12], string Feedbacks[252], int starCount[7][6])
{
  // Local variables
  string noIC;
  int i, j;
  char answer;

  cout << "Insert No IC (without '-') : ";
  cin >> noIC;
  cin.ignore();

  bool found = false;

  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 12; j++)
    {
      if (CustomerData[i][j].No_Ic == noIC)
      {
        found = true;

        // Check if feedback already submitted
        if (CustomerData[i][j].FeedbackValidation == "DONE")
        {
          cout << "\nYou have already submitted feedback.\n";
          return;
        }

        cout << "\nHello " << CustomerData[i][j].Name << "!" << endl
             << endl;

        int index = (i * 12 + j) *
                    7; // Calculate correct starting index for this customer

        do
        {
          cout << "Rate your experience using stars (e.g., *, ***, *****):"
               << endl
               << endl;

          cout << "1. Did the amenities in the room meet your expectations? : ";
          getline(cin, Feedbacks[index]);

          cout << "2. How would you rate the overall cleanliness of the hotel? "
                  ": ";
          getline(cin, Feedbacks[index + 1]);

          cout << "3. How friendly and helpful was our staff? : ";
          getline(cin, Feedbacks[index + 2]);

          cout << "4. How was your dining experience with us? : ";
          getline(cin, Feedbacks[index + 3]);

          cout << "5. Was the Wi-Fi connection strong and reliable? : ";
          getline(cin, Feedbacks[index + 4]);

          cout << "6. Do you feel the price you paid was fair for the quality "
                  "of your stay? : ";
          getline(cin, Feedbacks[index + 5]);

          cout << "7. Are you satisfied with our hotel? : ";
          getline(cin, Feedbacks[index + 6]);

          cout << "\nThank you for your feedback!\n";

          // Mark the completed feeback
          CustomerData[i][j].FeedbackValidation = "DONE";

          // Display all answers
          cout << "\nYour feedback preview:" << endl;
          cout << "Did the amenities meet expectations: " << Feedbacks[index]
               << endl;
          cout << "Cleanliness rating: " << Feedbacks[index + 1] << endl;
          cout << "Staff friendliness: " << Feedbacks[index + 2] << endl;
          cout << "Dining experience: " << Feedbacks[index + 3] << endl;
          cout << "Wi-Fi quality: " << Feedbacks[index + 4] << endl;
          cout << "Fair pricing opinion: " << Feedbacks[index + 5] << endl;
          cout << "Overall satisfaction: " << Feedbacks[index + 6] << endl;

          cout << "\nDo you want to re-answer feedbacks? (Y/N): ";
          cin >> answer;
          cin.ignore();
          answer = toupper(answer);

          if (answer != 'Y' && answer != 'N')
          {
            answer = 'Y'; // Force loop again if invalid
          }

        } while (answer == 'Y');

        // Analyze the feedback
        for (int a = 0; a < 7; a++)
        {
          int stars = Feedbacks[index + a].length();
          if (stars >= 0 && stars <= 5)
          {
            starCount[a][stars]++;
          }
        }

        cout << "Thank you for your final feedback!" << endl;
        return; // Finalization of feedback
      }
    }
  }

  if (!found)
  {
    cout << "\nNo IC not found in our system. Please make sure you have "
            "checked in.\n";
    cout << "Please refer to the cashier for further assitance...Thank you\n";
  }
}
void SaveData(CustomerBlueprint CustomerData[3][12], int starCount[7][6])
{
  ofstream outFile("hotel_database.csv");
  if (!outFile)
    return;

  outFile << "floor,room,No.ic,Name,Duration,total price,package,feedback validation" << endl;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 12; j++)
    {
      if (CustomerData[i][j].No_Ic != "")
      { // Only save rooms that aren't empty
        outFile << i + 1 << "," << j + 1 << "," << CustomerData[i][j].No_Ic << "," << CustomerData[i][j].Name << "," << CustomerData[i][j].DayIn << "," << CustomerData[i][j].Total_price << "," << CustomerData[i][j].RoomType << "," << CustomerData[i][j].FeedbackValidation << endl;
      }
    }
  }
  outFile.close();

  ofstream feedbackS("feedbacks_count.txt");
  if (!feedbackS)
    return;
  for (int a = 0; a < 7; a++)
  {
    for (int stars = 0; stars < 6; stars++)
    {
      feedbackS << starCount[a][stars] << " ";
    }
    feedbackS << endl;
  }
  feedbackS.close();
}
void LoadData(CustomerBlueprint CustomerData[3][12], int starCount[7][6])
{
  ifstream inFile("hotel_database.csv");
  int floor = 0, room = 0, dayin = 0, total_price = 0;
  stringstream convert;

  string line = "", subtract = "", FeedbackValidation = "";
  int location = 0;

  if (!inFile)
    return; // If file doesn't exist yet, do nothing

  getline(inFile, line);
  while (getline(inFile, line))
  {
    string temp_ic = "";
    string temp_name = "";
    string temp_pack = "";

    for (int i = 0; i < 7; i++)
    {
      location = line.find(',');
      subtract = line.substr(0, location);
      line = line.substr(location + 1);

      switch (i)
      {
      case 0:
      {
        convert << subtract;
        convert >> floor;
        break;
      }
      case 1:
      {
        convert << subtract;
        convert >> room;
        break;
      }
      case 2:
      {
        temp_ic = subtract;
        CustomerData[floor - 1][room - 1].No_Ic = temp_ic;
        break;
      }
      case 3:
      {
        temp_name = subtract;
        CustomerData[floor - 1][room - 1].Name = temp_name;
        break;
      }
      case 4:
      {
        convert << subtract;
        convert >> dayin;
        CustomerData[floor - 1][room - 1].DayIn = dayin;
        break;
      }
      case 5:
      {
        convert << subtract;
        convert >> total_price;
        CustomerData[floor - 1][room - 1].Total_price = total_price;
        break;
      }
      case 6:
      {
        temp_pack = subtract;
        CustomerData[floor - 1][room - 1].RoomType = subtract;
        break;
      }
      default:
        break;
      }
      CustomerData[floor - 1][room - 1].Floor = floor - 1;
      CustomerData[floor - 1][room - 1].Room = room - 1;

      convert.clear();
      convert.str("");
    }
    CustomerData[floor - 1][room - 1].FeedbackValidation = line;
    convert.clear();
    convert.str("");
  }
  inFile.close();

  ifstream feedbackL("feedbacks_count.txt");
  if (!feedbackL)
    return;

  for (int a = 0; a < 7; a++)
  {
    for (int stars = 0; stars < 6; stars++)
    {
      feedbackL >> starCount[a][stars];
    }
    feedbackL.ignore();
  }

  feedbackL.close();
}
