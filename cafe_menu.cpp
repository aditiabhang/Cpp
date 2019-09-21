#include <iostream>
#include <iomanip>
using namespace std;

const int menu_size = 10;           //size of the menu
const double tax_rate = 0.08;            //tax applied to the bill

struct MenuItems {
    string description;             //item name
    float price;                    //price of the menu item
    int count;                      //the count of the items
};

//*************************************************************************//
// displayMenuItem() - displays the menu in terms of its description,
// the ordering numbers for each item on the menu. The ordering number
// is (index+1).
// menu[] - array of menu_size MenuItem struct
//*************************************************************************//
void displayMenuItems(MenuItems menu[]) {
    for(int i = 0; i < menu_size; i++) {
        cout << "[" << i+1 << "]" <<
        left << setw(15) << menu[i].description <<
        right << setw(5) << menu[i].price << endl;
    }
}
//*************************************************************************//
// takeAnOrder() - Askes the user to input the item order number, sums up 
// the prices of the items ordered. Also increments the count of the ordered
// items.
// menu[] - array of menu_size MenuItem struct
// returns - the subtotal of the ordered items.
//*************************************************************************//
double takeAnOrder(MenuItems menu[]) {
    cout <<  "Please enter the order of the items you wish to order. Select 0 to quit." << endl;
    int choice;         //current menu item number
    float subtotal = 0;       //accumulates the prices of the ordered items
    cin >> choice;
    while ( choice!= 0)
    {
        if (choice >= 1 && choice <= menu_size) {
            subtotal = subtotal + menu[choice-1].price;
            menu[choice-1].count++;
        }
        else
            cout << "Invalid selection. Please select again." << endl;
        cin >> choice;
    }
    return subtotal;
}
//*************************************************************************//
// getMostOftenOrdered -  finds the index of the item with the highest count.
// menu[] - array of menu_size MenuItems struct
// returns - the index of the item with highest count
//*************************************************************************//
int getMostOftenOrdered(MenuItems menu[]) {
    int max_index = 0;
    for(int i = 0; i < menu_size; i++) {
        if(menu[i].count > menu[max_index].count)
            max_index = i;
    }
    return max_index;
}
//*************************************************************************//
// ------------------------ Driver Program --------------------------------//
//*************************************************************************//
int main() {
    MenuItems menu[menu_size] = {
                      {"Express Coffee", 1.50, 0},
                      {"Cutting Chai", 1.50, 0},
                      {"Adrak Chai", 1.75, 0},
                      {"Pohe", 3.50, 0},
                      {"Sabudana Khichadi", 3.50, 0},
                      {"Misal Pav", 3.75, 0},
                      {"Idli Sambhar", 2.75, 0},
                      {"Medu Wada Sambhar", 2.75, 0},
                      {"Plain Dosa", 3.00, 0},
                      {"Masala Dosa", 3.25, 0}
                      };
    
    cout << fixed << setprecision(3);               //output formatting

    double dailyTotal = 0;                          //sums up all orders
    char choice;                                    //No (continue) and E (Exit)

    //loop to take in all the orders
    do {
        displayMenuItems(menu);

        double subTotal = takeAnOrder(menu);      //takes the first order 
        cout << "Subtotal......: $" << setw(5) << subTotal << endl;

        double tax = subTotal * tax_rate;
        cout << "Tax......: $" << setw(5) << tax << endl;
        
        double total_bill = tax + subTotal;
        cout << "Total......: $" << setw(5) << total_bill << endl;

        dailyTotal += total_bill;

        cout << "Please select 'N' to continue with a new order, or select 'E' to exit." << endl;
        cin >> choice;
    } 
    while (choice == 'N');
    
    //end of day statistics
    cout << "End of the day" << endl;
    cout << "Total money gained: $" << dailyTotal << endl;
    int most = getMostOftenOrdered(menu);              // to find out the most often ordered item
    cout << "Today's most ordered item is: " << menu[most].description << ", and it was ordered " << menu[most].count << " times." << endl;
}