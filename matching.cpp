#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
using namespace std;

struct Order
{
    int instrument;
    int price;
};

struct Quantity
{
    int instrument;
    int quantity;
    int quantity_sold;
    int price;
};

using std::cin;
using std::cout;
using std::endl;
int last_sell, last_buy;
bool check(int curr)
{
    if (curr > 0 and curr < 4)
        return true;
    return false;
}

void create_orders(unordered_map<int, Order> &orders, int &n)
{
    cout << "1-->BTC / 2-->ETH / 3 -->USDT " << endl;
    cout << "Choose from 1 / 2 / 3 " << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "1st instrument  and 2nd price" << endl;
        cin >> orders[i].instrument;
        if (!check(orders[i].instrument))
        {
            cout << "1-->BTC / 2-->ETH / 3 -->USDT " << endl;
            cout << "Choose from 1 / 2 / 3 " << endl;
            cout << endl;
            cout << endl;
            return;
        }

        cin >> orders[i].price;
        cout << endl;

        cout << "instrument " << orders[i].instrument << " price " << orders[i].price << endl;
    }
}

bool match(unordered_map<int, Order> &orders, int price, int curr, int &n)
{
    for (int i = 0; i < n; i++)
    {
        if (orders[i].instrument == curr and orders[i].price == price)
        {
            return true;
        }
    }
    return false;
}

void print(unordered_map<int, Order> &orders, int &n)
{
    for (int i = 0; i < n; i++)
    {
        if (orders[i].price == 0)
            continue;
        cout << "Instrument -> " << orders[i].instrument << " Price " << orders[i].price << endl;
    }
}

// Delete Order from Record
void delete_item(unordered_map<int, Order> &orders, int &n)
{
    cout << "What do You want to delete from record " << endl;
    cout << "Please enter 1) Instrument and  2) Price " << endl;
    int price, curr;
    cin >> curr;
    if (!check(curr))
    {
        cout << " 1-->BTC / 2-->ETH / 3 -->USDT " << endl;
        cout << "Choose from 1 / 2 / 3 " << endl;
        return;
    }
    cin >> price;
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (orders[i].instrument == curr and orders[i].price == price)
        {
            cout << "item which you want to delete " << endl;
            cout << i << "Instrument " << orders[i].instrument << "Price  " << orders[i].price << endl;

            orders.erase(i);
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "Order Delete from Record " << endl;
            flag = true;
        }
    }
    if (!flag)
    {
        cout << "item you want to delete is not in record" << endl;
    }
}

// //Retrive trade based on instrument
void print_instrument(unordered_map<int, Order> &orders, int &n)
{
    cout << "We have 3 types of instrument" << endl;
    cout << "1 -->BTC 2 -->ETH 3 -->USDT " << endl;
    cout << "Enter type of instrument out of these 3" << endl;
    int curr;
    cin >> curr;
    if (check(curr))
    {

        for (int i = 0; i < n; i++)
        {
            if (orders[i].instrument == curr)
            {
                if (orders[i].price == 0)
                    continue;
                cout << "Instrument -> " << orders[i].instrument << " Price " << orders[i].price << endl;
            }
        }
    }
    else
    {
        cout << "sorry type of instrument you want not exist" << endl;
    }
}

// Buy Order
void buy(unordered_map<int, Order> &orders, unordered_map<int, Quantity> &total_quantity, int &id, int &n, int &flag)
{
    int temp_n;
    bool flag2 = false;

    cout << "What do You want to buy " << endl;
    cout << "Please enter 1) Instrument and  2) Price  in this order" << endl;
    int price, curr;
    cin >> curr;
    if (!check(curr))
    {
        cout << "1-->BTC / 2-->ETH / 3 -->USDT " << endl;
        cout << "Choose from 1 / 2 / 3 " << endl;
        return;
    }
    cin >> price;

    if (match(orders, price, curr, n))
    {
        cout << "we got a match now tell me how much u want to buy" << endl;

        int amt;
        cin >> amt;
        if (total_quantity.size() == 0)
        {
            total_quantity[0].instrument = curr;
            total_quantity[0].price = price;
            total_quantity[0].quantity = amt;
            total_quantity[0].quantity_sold = 0;
            last_buy = amt;
            cout << "purchase quantity -> " << total_quantity[0].quantity << endl;
            cout << "price -> " << total_quantity[0].price << endl;
            cout << "instrument -> " << total_quantity[0].instrument << endl;
            cout << "quantuity sold -> " << total_quantity[0].quantity_sold << endl;
            id = 1;
        }
        else
        {
            for (int j = 0; j < id; j++)
            {
                if (total_quantity[j].instrument == curr and total_quantity[j].price == price)
                {
                    total_quantity[j].quantity += amt;
                    total_quantity[j].quantity_sold = 0;
                    last_buy = amt;
                    cout << "purchase quantity -> " << total_quantity[j].quantity << endl;
                    cout << "price -> " << total_quantity[j].price << endl;
                    cout << "instrument -> " << total_quantity[j].instrument << endl;
                    cout << "quantuity sold -> " << total_quantity[0].quantity_sold << endl;
                    flag2 = true;
                }
            }
            if (!flag2)
            {

                id++;
                total_quantity[id].instrument = curr;
                total_quantity[id].price = price;
                total_quantity[id].quantity = amt;
                total_quantity[id].quantity_sold = 0;
                last_buy = amt;
                cout << "purchase quantity -> " << total_quantity[id].quantity << endl;
                cout << "price -> " << total_quantity[id].price << endl;
                cout << "instrument -> " << total_quantity[id].instrument << endl;
                cout << "quantity sold -> " << total_quantity[id].quantity_sold << endl;
                id++;
            }
        }
    }
    else
    {
        cout << "Sorry item you want is not in record" << endl;
    }
}

// Cancel Last Order
void last_created_order(unordered_map<int, Order> &orders, unordered_map<int, Quantity> &total_quantity, int &id, int &id1, int &n, int &flag)
{
    cout << "Cancle a existing order 1 to Buy and 2 to Sell" << endl;
    cin >> flag;
    if (flag == 1)
    {
        cout << "last trade purchase instrument " << total_quantity[id - 1].instrument << endl;
        cout << "last trade purchase price " << total_quantity[id - 1].price << endl;
        cout << "last trade purchase quantity " << total_quantity[id - 1].quantity << endl;
        cout << "last trade purchase no of item sold " << total_quantity[id - 1].quantity_sold << endl;
        cout << endl;
        cout << endl;

        cout << "After cancel last order " << endl;
        cout << endl;
        cout << endl;
        total_quantity[id - 1].quantity -= last_buy;
        cout << "purchase instrument " << total_quantity[id - 1].instrument << endl;
        cout << "purchase price " << total_quantity[id - 1].price << endl;
        cout << "purchase quantity " << total_quantity[id - 1].quantity << endl;
        cout << "purchase no of item sold " << total_quantity[id - 1].quantity_sold << endl;
    }
    if (flag == 2)
    {
        cout << "last item sell instrument " << total_quantity[id1 - 1].instrument << endl;
        cout << "last item sell price " << total_quantity[id1 - 1].price << endl;
        cout << "last item sell quantity " << total_quantity[id1 - 1].quantity << endl;
        cout << "last item sell no of item sold " << total_quantity[id1 - 1].quantity_sold << endl;
        cout << endl;
        cout << endl;

        cout << "After cancel last order " << endl;
        cout << endl;
        cout << endl;
        total_quantity[id1].quantity += last_sell;
        cout << "sell instrument " << total_quantity[id1 - 1].instrument << endl;
        cout << "sell price " << total_quantity[id1 - 1].price << endl;
        cout << "sell quantity " << total_quantity[id1 - 1].quantity << endl;
        cout << "sell no of item sold " << total_quantity[id1 - 1].quantity_sold << endl;
    }
}

// Retrive trade based on instrument
void retrive_all_inst_trade(unordered_map<int, Quantity> &total_quantity, int &id)
{
    cout << "Retrive All trdes happen based on instrument " << endl;
    cout << "Enter 1 --BTC/ 2 --> ETH / 3 -->USDT " << endl;
    int curr;
    cin >> curr;

    if (!check(curr))
    {
        cout << " 1-->BTC / 2-->ETH / 3 -->USDT " << endl;
        cout << "Choose from 1 / 2 / 3 " << endl;
        return;
    }

    for (int i = 0; i < id; i++)
    {
        if (total_quantity[i].instrument == curr)
        {
            if (total_quantity[i].price == 0)
                continue;

            cout << "trades based on " << total_quantity[i].instrument << " instrument" << endl;

            cout << "price " << total_quantity[i].price << endl;
            cout << "buy quantity :- " << total_quantity[i].quantity << endl;
            cout << "sold quantity :- " << total_quantity[i].quantity_sold << endl;
        }
    }
}

// Retrive All  trade
void retrive_all_trade(unordered_map<int, Quantity> &total_quantity, int &id)
{
    cout << "Retrive All trdes happen  " << endl;

    for (int i = 0; i < id; i++)
    {
        if (total_quantity[i].price == 0)
            continue;

        // cout << i << " " << total_quantity[i].instrument << " " << total_quantity[i].quantity << " " << total_quantity[i].quantity_sold << "  " << total_quantity[i].price << endl;
        cout << "instrument " << total_quantity[i].instrument << endl;

        cout << "price " << total_quantity[i].price << endl;
        cout << "buy quantity :- " << total_quantity[i].quantity << endl;
        cout << "sold quantity :- " << total_quantity[i].quantity_sold << endl;
        cout << endl;
        cout << endl;
        cout << endl;
    }
}

// Sell order
void sell(unordered_map<int, Order> &orders, unordered_map<int, Quantity> &total_quantity, int &id, int &id1, int &n, int &flag)
{
    int price, curr;
    cout << "1st instrument && 2nd price" << endl;
    cin >> curr;

    if (!check(curr))
    {
        cout << " 1-->BTC / 2-->ETH / 3 -->USDT " << endl;
        cout << "Choose from 1 / 2 / 3 " << endl;
        return;
    }

    cin >> price;

    bool flag2 = false;
    if (match(orders, price, curr, n))
    {
        for (int i = 0; i < id; i++)
        {
            if (total_quantity[i].instrument == curr and total_quantity[i].price == price)

            {
                flag2 = true;
                int amt;
                cout << "buyer max have " << total_quantity[i].quantity << " no of item at " << total_quantity[i].instrument << endl;
                cout << endl;

                cout << "At price " << total_quantity[i].price << endl;
                cin >> amt;
                last_sell = amt;
                if (total_quantity[i].quantity - amt < 0)
                {
                    cout << endl;
                    cout << "buyer max have " << total_quantity[i].quantity << "quantity " << endl;
                    cout << endl;
                }
                else
                {
                    total_quantity[i].quantity -= amt;
                    total_quantity[i].quantity_sold += amt;
                    cout << "quantity remaing " << total_quantity[i].quantity << endl;
                    cout << "quantity sold " << total_quantity[i].quantity_sold << endl;
                    cout << "instrument  " << total_quantity[i].instrument << endl;
                    cout << "price " << total_quantity[i].price << endl;

                    // if (total_quantity[i].quantity == 0)
                    // {
                    //     total_quantity.erase(i);
                    // }
                }
                id1 = i;
            }
        }
        if (!flag2)
        {
            cout << "Item is match and present in record but not bought" << endl;
            cout << "please buy first" << endl;
        }
    }
    else
    {
        cout << "item is not present in record " << endl;
    }
}

int main()
{
    unordered_map<int, Order> orders;
    unordered_map<int, vector<int>> currency_map;
    unordered_map<int, Quantity> total_quantity;
    int n;
    int id = 0, last_sell, last_buy, flag = 0, id1 = 0;

    int choice;

    do
    {
        cout << "Enter your choice: " << endl;
        cout << "1. Create Orders" << endl;
        cout << "2. buy" << endl;
        cout << "3. Sell" << endl;
        cout << "4. Print all orders" << endl;
        cout << "5. Print orders based on instrument" << endl;
        cout << "6. Delete Order" << endl;
        cout << "7. Cancle last order" << endl;
        cout << "8. Retrive trade based on instrument" << endl;
        cout << "9. Retrive All trade happen" << endl;
        cout << "10. Exit" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "How many Orders u want to create " << endl;
            cin >> n;
            create_orders(orders, n);
            break;

        case 2:

            buy(orders, total_quantity, id, n, flag);
            break;

        case 3:
            sell(orders, total_quantity, id, id1, n, flag);
            break;
        case 4:
            print(orders, n);
            break;
        case 5:
            print_instrument(orders, n);
            break;
        case 6:
            delete_item(orders, n);
            break;
        case 7:

            last_created_order(orders, total_quantity, id, id1, n, flag);
            break;
        case 8:

            retrive_all_inst_trade(total_quantity, id);
            break;
        case 9:

            retrive_all_trade(total_quantity, id);
            break;
        case 10:
            cout << "Exiting program..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please enter a valid choice." << endl;
            break;
        }
    } while (choice != 10);

    return 0;
}