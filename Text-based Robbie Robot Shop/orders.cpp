#include "orders.h"

void Orders::createOrders(RobotModels models, SalesAssociate associate)  //add
{
  Orders ordr;
  ordr.associate = associate;
  
  string name;
  int choice, key, quantity;
  cout <<"\n\n******* CREATING ORDER **********\n";
  cout << "\nEnter customer Name: ";
  cin.ignore();
  getline(cin, name);
    
  ordr.customer.setName( name );                         //chgd
  //custName = customer.getName();                    //chgd
  
  
  while(key != 2)
  {
    //cin.ignore();
    cout << endl;
    cout << "What would you like to do?" << endl;
    cout << "1) Select from catalog" << endl;
    cout << "2) Checkout" << endl;
    cout << "Command: ";
    cin >> key;
    
    if(key == 1)
    {
      models.displayRobotModel();
      cout << "Enter catalog number: ";
      cin >> choice;
      cout << "Enter quantity: ";
      cin >> quantity;
      ordr.quantities.push_back(quantity);
      ordr.cart.push_back(choice);
    }
    else if(key == 2)
    {
      cout << "\n\n******* CHECKOUT SUMMARY *******" << endl;
      cout << "Customer: " << name << endl;
      ordr.setOrderNumber();
      cout << "Order number: " << ordr.getOrderNumber() << endl;
      cout << "Date: ";
      getTime();
      
      for(int i = 0; i < ordr.cart.size(); i++)
      {
        double price = 0;
        price = models.getModelPrice(ordr.cart[i]) * ordr.quantities[i];
        ordr.setTotalPrice(price);
        models.display(ordr.cart[i]);
        cout << "Quantity: x" << ordr.quantities[i] << endl;
        cout << endl;
        
      }
      
      cout << "\n\nSubTotal: $" << ordr.getTotalPrice();
      allOrders.push_back(ordr);
    }
    else
      cout <<"\nXXXXX Invalid key, Try again XXXXX"<< endl;
  }
  
  
}

void Orders::setTotalPrice(double price)
{
  totalPrice += price;
}

double Orders::getTotalPrice()
{
  return totalPrice;
}

void Orders::getTime()
{
  // current date/time based on current system
  time_t now = time(0);
  
  // convert now to string form
  char* dt = ctime(&now);
  
  cout  << dt << endl;

}

void Orders::setOrderNumber()
{
  orderNumber = rand() % 100000000;
}
int Orders::getOrderNumber()
{
  return orderNumber;
  
}

void Orders::displayOrders()
{
  cout << endl;
  cout << "_____________________________________________" << endl;
  cout << "\t******** Display Orders ********" << endl;
  cout << "_____________________________________________" << endl;
  for (int i = 0; i < allOrders.size(); i++)
  {
    cout << endl;
    cout << i << ". ";
    cout << "Customer Name: " << allOrders[i].customer.getName() << endl;             //chgd
    cout << endl;
    cout << "   Order Number: " << allOrders[i].orderNumber << endl;
    cout << "   Sold By: " << allOrders[i].associate.getName()<< endl;
 /*   for(int j = 0; j < allOrders[i].cart.size(); j++)
    {
      cout << "   Products: " << allOrders[i].cart[j] << endl;
      cout << "   Quantity: " << allOrders[i].quantities[j] << endl;
    }
  
*/
    cout << "   Total Price: " << allOrders[i].totalPrice << endl;

  }
  if (allOrders.size() == 0)
    cout << "\nNo model created" << endl;
}

/*----------------------------------------------------------------------------------------------------------------------*/
void Orders::orderHistory()
{
    cout << "Name: ";
    cin.ignore();
    getline( cin, token );
    
    for ( int i = 0; i < allOrders.size(); i++ )
    {
        string custName = allOrders[i].customer.getName();
        if ( allOrders.size() == 0 )             //check if any orders are stored
        {
            cout << endl << "No sales have been made." << endl << endl << "Exiting..." << endl;
            break;
        }
        else if ( token.compare( custName ) == 0)              //chgd
        {
            printOrderHistory(i);
            index = 1;
            cout << "View the bill?";
        }
    }
    if( index != 1 && allOrders.size() != 0 )
        cout << "You have no orders. ";
}

/*----------------------------------------------------------------------------------------------------------------------*/
void Orders::printOrderHistory( int x )
{
    cout << endl;
    cout << "_____________________________________________" << endl;
    cout << "\t******** Display Orders ********" << endl;
    cout << "_____________________________________________" << endl;
    cout << endl;
    cout << x << ". ";
    cout << "Customer Name: " << allOrders[x].customer.getName() << endl;
    cout << endl;
    cout << "   Order Number: " << allOrders[x].orderNumber << endl;
    cout << "   Sold By: " << allOrders[x].associate.getName()<< endl;
 /*   for(int i = 0; i < allOrders[x].cart.size(); i++)
    {
        cout << "   Products: " << allOrders[x].cart[i] << endl;
        cout << "   Quantity: " << allOrders[x].quantities[i] << endl;
    }
  */
    cout << "   Total Price: " << allOrders[x].totalPrice << endl;
}
/*----------------------------------------------------------------------------------------------------------------------*/
void Orders::viewCustBill()
{
    cout << "----------------------------------------" << endl;
    cout << "|      Robbie Robot Shop Invoice       |" << endl;
    cout << "________________________________________" << endl;
    cout << endl;
}
