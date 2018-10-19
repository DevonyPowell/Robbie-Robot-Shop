//  GUI for Robbie Robot

//  shop:
//  - calls classes to make window & widgets

//  MakeWin:
//  - can be called to make a window with the given params

//  MakeBox:
//  - can be called to make a box with the given params

//  DisplayBox:
//  - can be called to make a display box

//  MakeButtons:
//  - creates unique buttons based on params
//  - each button has a callback & a handling method

//  A. Sims(10-30-16) : Need create a working Makefile so classes can be split into separate files. Need to figure out how to make menubar work with class structure
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Scroll.H>
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Chart.H>
void viewPieCharts(Fl_Widget* w, void* p);
//#include <cmath>//don't remember why i added this, if something doesn't work uncomment
using namespace std;

/*-------------------GLOBAL VARIABLES--------------------*/
// Used by Main for menu bar of main window
Fl_Menu_Bar *menu;
// Used by Main and MakeParts for user input
int gloArgc;
char **gloArgv;
// Used by MakeParts for txt input boxes
Fl_Input *name1;
Fl_Int_Input *num1;
Fl_Float_Input *weight1;
Fl_Float_Input *cost1;
Fl_Input *name2;
Fl_Int_Input *num2;
Fl_Float_Input *weight2;
Fl_Float_Input *cost2;
Fl_Input *name3;
Fl_Int_Input *num3;
Fl_Float_Input *weight3;
Fl_Float_Input *cost3;
Fl_Input *name4;
Fl_Int_Input *num4;
Fl_Float_Input *weight4;
Fl_Float_Input *cost4;
Fl_Input *name5;
Fl_Int_Input *num5;
Fl_Float_Input *weight5;
Fl_Float_Input *cost5;
Fl_Float_Input *powA;
Fl_Float_Input *powL;
Fl_Float_Input *powB;
Fl_Int_Input *batt;
Fl_Float_Input *speed;
Fl_Input *desc1;
Fl_Input *desc2;
Fl_Input *desc3;
Fl_Input *desc4;
Fl_Input *desc5;
// Used by MakeParts to create window & left browser menu
Fl_Window *wind = 0;
Fl_Hold_Browser *bro = 0;
Fl_Group *grp[5] = { 0,0,0,0,0 };
// Used by MakeMods to create window & left browser menu
Fl_Window *windM = 0;
Fl_Hold_Browser *broM = 0;
Fl_Group *grpM[2] = { 0,0 };
Fl_Input *name;
Fl_Int_Input *num;
Fl_Input *arm1;
Fl_Float_Input *armP1;
Fl_Input *arm2;
Fl_Float_Input *armP2;
Fl_Input *torso;
Fl_Float_Input *torP;
Fl_Input *head;
Fl_Float_Input *headP;
Fl_Input *loco;
Fl_Float_Input *locoP;
Fl_Input *battM;
Fl_Float_Input *battP;
Fl_Float_Input *price;
Fl_Output *cost;
// Used by MakeOrders to create txt input, create window & left browser menu
Fl_Input *customerName;
Fl_Input *associateName;
Fl_Int_Input *modelIndex;
char modelName[100];//used in checkout
char *saleDate;//used in checkout
char modelPrice[100];
char total[1000];
char modelCost[100];
Fl_Int_Input *quantity;
Fl_Input *comments;
Fl_Int_Input *orderNumber;
Fl_Window *windO = 0;
Fl_Hold_Browser *broO = 0;
Fl_Group *grpO[3] = { 0,0,0 };
// Used by MakeSalesAssociate to create txt input, create window & left browser menu
Fl_Input *salesAssociateName;
Fl_Int_Input *employeeNumber;
Fl_Window *windSA = 0;
Fl_Hold_Browser *broSA = 0;
Fl_Group *grpSA[2] = { 0,0 };
Fl_Text_Buffer *buff4;
Fl_Text_Display *disp4;
// Used by PBViewSalesLog Class to create txt input, create window & left browser menu
Fl_Window *windPB = 0;
Fl_Hold_Browser *broPB = 0;
Fl_Group *grpPB[3] = { 0,0,0 };
Fl_Input *month;
Fl_Int_Input *day;
Fl_Int_Input *year;
Fl_Text_Buffer *buff;
Fl_Text_Display *disp;
Fl_Text_Buffer *buff3;
Fl_Text_Display *disp3;
Fl_Text_Buffer *buff1;
Fl_Text_Display *disp1;
char testing[100];
char* result = new char[2000];
//View Individual Employee Reports
Fl_Input *employeeName;
Fl_Input *theChosenOne;
//User by Make Customers
Fl_Hold_Browser *broC = 0;
Fl_Group *grpC[1] = { 0 };
Fl_Input *customerFirstName;
Fl_Input *customerLastName;
Fl_Input *customerEmail;
Fl_Input *customerPhone;
Fl_Input *customerAdddress;

// Vector of filenames for undo feature
vector<string> fileNames;

/*--------------------SelectPrtsGroupCB----------------------*/
void SelectGroupCB(Fl_Widget*, void*) {
  // Show the 'selected' group
  for ( int t=0; t<5; t++ ) {
    if ( t == (bro->value()-1) ) { grp[t]->show(); }
    else { grp[t]->hide(); }
  }
}
/*-------------------SelectModGroupCB--------------------*/
void SelectModGroupCB(Fl_Widget*, void*) {
  // Show the 'selected' group
  for ( int t=0; t<2; t++ ) {
    if ( t == (broM->value()-1) ) { grpM[t]->show(); }
    else { grpM[t]->hide(); }
  }
}
/*-------------------SelectOrdGroupCB--------------------*/
void SelectOrdGroupCB(Fl_Widget*, void*) {
  // Show the 'selected' group
  for ( int t=0; t<3; t++ ) {
    if ( t == (broO->value()-1) ) { grpO[t]->show(); }
    else { grpO[t]->hide(); }
  }
}
/*-------------------SelectCustGroupCB--------------------*/
void SelectCustGroupCB(Fl_Widget*, void*) {
  // Show the 'selected' group
  for ( int t=0; t<1; t++ ) {
    if ( t == (broC->value()-1) ) { grpC[t]->show(); }
    else { grpC[t]->hide(); }
  }
}
/*-------------------SelectAssociatesGroupCB--------------------*/
void SelectAssociatesGroupCB(Fl_Widget*, void*) {
  // Show the 'selected' group
  for ( int t=0; t<2; t++ ) {
    if ( t == (broSA->value()-1) ) { grpSA[t]->show(); }
    else { grpSA[t]->hide(); }
  }
}
/*-------------------SelectSalesGroupCB--------------------*/
void SelectSalesGroupCB(Fl_Widget*, void*) {
  // Show the 'selected' group
  for ( int t=0; t<3; t++ ) {
    if ( t == (broPB->value()-1) ) { grpPB[t]->show(); }
    else { grpPB[t]->hide(); }
  }
}
/*---------------------Checkout CB, Works in combination with saveords------------------*/
static void checkoutCB(Fl_Widget *w, void*)
{
  //reading models to get the needed information
  ifstream theFile("models.txt");
  if( theFile.fail() ){
    cerr << "failed to open orders file" << endl;
    // use displaybox class to show error w/GUI
  }
  int number;
  char *arm1= new char[100], *arm2= new char[100], *torsoName= new char[100], *headName= new char[100], *locomotorName= new char[100], *batteryName= new char[100];
  int index = atoi(modelIndex->value());
  for(int i=-1; i <index; i++){
    theFile >> modelName >> number >> headName >> arm1 >> arm2 >> torsoName >> locomotorName >> batteryName >> modelPrice >> modelCost;
  }
  double buffer = stod(modelPrice) * atof(quantity->value());
  sprintf(total, "%1.2f", buffer);
  //strcpy(total, buffer);
  Fl_Window *win = new Fl_Window(650, 480);       // create new win for display
  Fl_Text_Buffer *buff = new Fl_Text_Buffer();    // make a buffer to display text
  Fl_Text_Display *disp = new Fl_Text_Display(20, 20, 650-40, 480-40, "Checkout Summary");   // display box
  disp->buffer(buff);     // set buffer
  win->resizable(*disp);  // make window resizable
  win->show();            //show window
  //txt to display in window
  //TODO: NEED TO WRITE MODEL NAME, AND PRICE TO ORDERS FOLDER
  //grabb current date
  time_t now = time(0);
  // convert now to string form
  saleDate = ctime(&now);
  saleDate[ strlen(saleDate) - 1 ] = '\0';
  char* result = new char[1000];
  strcat(result, "Customer Name: ");
  strcat(result, customerName->value());
  strcat(result, "\nOrder Number: ");
  strcat(result, orderNumber->value());
  strcat(result, "\nDate of Sale: ");
  strcat(result, saleDate);
  strcat(result, "\nModel Name: ");
  strcat(result, modelName);
  strcat(result, "\nModel Price: $");
  strcat(result, modelPrice);
  strcat(result, "\nQuantity: x");
  strcat(result, quantity->value());
  strcat(result, "\nTotal: $");
  strcat(result, total);
  buff->text(result);
}
/*----------------------saveCust CB----------------------*/
void saveCustCB(Fl_Widget* w, void* p){

  ofstream modsFile("customers.txt", ios_base::out|ios_base::app);

  if( modsFile.fail() ){
    cerr << "failed to open file" << endl;
    // use displaybox class to show error w/GUI
  }

  //will store the data after submit is pressed
  modsFile << customerFirstName->value() << " ";
  modsFile << customerLastName->value() << " ";
  modsFile << customerEmail->value() << " ";
  modsFile << customerPhone->value() << " ";
  modsFile << customerAdddress->value() << "\n";
  //clears value of input boxes after they're stored

  customerFirstName->value("");
  customerLastName->value("");
  customerEmail->value("");
  customerPhone->value("");
  customerAdddress->value("");

  fileNames.push_back("customers.txt");
  //close??
  //MakeOrders orders(10,10,350,700-20,"Create Robot Orders");
}
/*----------------------saveAssociateCB CB----------------------*/
void saveAssociateCB(Fl_Widget* w, void* p){
  // open  salesAssociate file
  ofstream salesAssociateFile("salesAssociate.txt", ios_base::out|ios_base::app);
  if( salesAssociateFile.fail() ){
    cerr << "failed to open orders file" << endl;
  }
  salesAssociateFile << salesAssociateName->value() << " ";
  salesAssociateFile << employeeNumber->value() << "\n";
  //reset values
  salesAssociateName->value("");
  employeeNumber->value("");

  fileNames.push_back("salesAssociates.txt");
}
/*----------------------saveOrds CB----------------------*/
void saveOrdsCB(Fl_Widget* w, void* p){
  ofstream ordsFile("orders.txt", ios_base::out|ios_base::app);
  /*------------NOT YET READY TO IMPLEMENT-----------------------------------------*/
  /*ofstream salesAssociateFile("salesAssociate.txt", ios_base::out|ios_base::app);
   ifstream readSalesAssociateFile("salesAssociate.txt");
   if( salesAssociateFile.fail() ){
   cerr << "failed to open orders file" << endl;
   }*/
  /*--------------------------------------------------------------------------------*/
  if( ordsFile.fail() ){
    cerr << "failed to open orders file" << endl;
    // use displaybox class to show error w/GUI
  }

  //will store to the data to orders after checkout is pressed
  ordsFile << associateName->value() << " ";
  ordsFile << customerName->value() << " ";
  ordsFile << orderNumber->value() << " ";
  ordsFile << saleDate << " ";
  ordsFile << modelIndex->value() << " ";
  ordsFile << modelName << " ";
  ordsFile << quantity->value() << " ";
  ordsFile << total << " ";
  ordsFile << modelCost << " ";
  ordsFile << comments->value() << "\n";
  //will store to the data to sales associate after checkout is pressed
  //TODO: HAVE CONDITION WHEN TO SAVE ASSOCIATES NAME IF ASSOCIATENAME->VALUE EQUALS A NAME IN THE FILE DO NOT ADD AGAIN
  /* char existingAssociateName[500];
   string restOfLine;
   int i=0, no =0;
   while(i==0 || readSalesAssociateFile >> existingAssociateName) {
   getline(readSalesAssociateFile, restOfLine);
   cout << existingAssociateName << "restofLine: "<<restOfLine<<endl;
   if(strcmp(associateName->value(), existingAssociateName) == 0){
   no =1;;
   break;
   }
   i++;
   strcpy(existingAssociateName, "");
   }
   if(no == 0){
   salesAssociateFile << associateName->value() << "\n";
   //salesAssociateFile << orderNumber->value() << "\n";//just a place holder
   }*/
  //clears value of input boxes after they're stored
  //I'm gonna need these values to create the checkout summary
  associateName->value("");
  customerName->value("");
  orderNumber->value("");
  strcpy(saleDate, "");
  modelIndex->value("");
  strcpy(modelName, "");
  quantity->value("");
  strcpy(total, "");
  strcpy(modelCost, "");
  comments->value("");

  fileNames.push_back("orders.txt");
}
/*----------------------viewImage CB---------------------*/
void viewImage(Fl_Widget* w, void* p){
  // register for use of images
  fl_register_images();
  char *fileName[50];
  Fl_JPEG_Image *jpg;

  // create window
  Fl_Double_Window *win = new Fl_Double_Window(300,300);

  // scrolling is a widget, must create
  Fl_Scroll *scr = new Fl_Scroll(0,0,300,300);

  switch ((intptr_t)p){
    case 1:
      jpg = new Fl_JPEG_Image("Robot_Images/full_business_can.jpg");
      break;
    case 2:
      jpg = new Fl_JPEG_Image("Robot_Images/full_button_can.jpg");
      break;
    case 3:
      jpg = new Fl_JPEG_Image("Robot_Images/full_humanoid_soldier.jpg");
      break;
    case 4:
      jpg = new Fl_JPEG_Image("Robot_Images/full_medic_can.jpg");
      break;
    case 5:
      jpg = new Fl_JPEG_Image("Robot_Images/full_orange_can.jpg");
      break;
    case 6:
      jpg = new Fl_JPEG_Image("Robot_Images/full_orange_humanoid_meditating.jpg");
      break;
    case 7:
      jpg = new Fl_JPEG_Image("Robot_Images/full_orange_humanoid_with_laptop.jpg");
      break;
    case 8:
      jpg = new Fl_JPEG_Image("Robot_Images/full_white_can.jpg");
      break;
  }

  // error check image file was retreived
  if ( jpg->h() == 0 ){
    cout << "Failed to load" << fileName << endl;
    exit(1);
  }

  // create box to fit image
  Fl_Box *box = new Fl_Box(0,0,jpg->w(),jpg->h());

  // put image in box
  box->image(jpg);

  // allow window to be resized for scrolling
  win->resizable(win);

  // no more window edits & show
  win->end();
  win->show();
}

/*----------------------saveMods CB----------------------*/
void saveModsCB(Fl_Widget* w, void* p){

  ofstream modsFile("models.txt", ios_base::out|ios_base::app);

  if( modsFile.fail() ){
    cerr << "failed to open file" << endl;
    // use displaybox class to show error w/GUI
  }

  ofstream pieFile("pieParts.txt", ios_base::out|ios_base::app);

  if( pieFile.fail() ){
    cerr << "failed to open file" << endl;
  }
  //will store the data after submit is pressed
  modsFile << name->value() << " ";
  modsFile << num->value() << " ";
  modsFile << head->value() << " ";
  modsFile << arm1->value() << " ";
  modsFile << arm2->value() << " ";
  modsFile << torso->value() << " ";
  modsFile << loco->value() << " ";
  modsFile << battM->value() << " ";
  modsFile << price->value() << " ";
  modsFile << cost->value() << "\n";
  // will store the data for pie chart
  pieFile << "#" << endl;
  pieFile << name->value() << endl;
  pieFile << arm1->value() << endl;
  pieFile << armP1->value() << endl;
  pieFile << arm2->value() << endl;
  pieFile << armP2->value() << endl;
  pieFile << torso->value() << endl;
  pieFile << torP->value() << endl;
  pieFile << head->value() << endl;
  pieFile << headP->value() << endl;
  pieFile << loco->value() << endl;
  pieFile << locoP->value() << endl;
  pieFile << battM->value() << endl;
  pieFile << battP->value() << endl;
  //clears value of input boxes after they're stored
  name->value("");
  num->value("");
  arm1->value("");
  arm2->value("");
  torso->value("");
  head->value("");
  loco->value("");
  battM->value("");
  price->value("");
  cost->value("");
  armP1->value("");
  armP2->value("");
  torP->value("");
  headP->value("");
  locoP->value("");
  battP->value("");

  fileNames.push_back("orders.txt");
}

/*----------------------calcCostCB----------------------*/
void calcCostCB(Fl_Widget* w, void* p){

  double arm1 = atof(armP1->value());
  double arm2 = atof(armP2->value());
  double tor = atof(torP->value());
  double head = atof(headP->value());
  double loco = atof(locoP->value());
  double batt = atof(battP->value());
  double total = arm1+arm2+tor+head+loco+batt;

  char* costTot;
  costTot = new char[to_string(total).length()+1];
  sprintf(costTot, "%1.2f", total);
  cost->value(costTot);
}
/*-----------------------savePrt CB----------------------*/
void savePrtCB(Fl_Widget* w, void* p){
  ofstream prtsFile("parts.txt", ios_base::out|ios_base::app);
  if( prtsFile.fail() ){
    cerr << "failed to open file" << endl;
    // use displaybox class to show error w/GUI
  }
  switch ((intptr_t)p){
    case 1:{
      //will store the data after submit is pressed
      prtsFile << "Head" << " ";
      prtsFile << name1->value() << " ";
      prtsFile << num1->value() << " ";
      prtsFile << weight1->value() << " ";
      prtsFile << cost1->value() << " ";
      prtsFile << desc1->value() << "\n";
      //clears value of input boxes after they're stored
      name1->value("");
      num1->value("");
      weight1->value("");
      cost1->value("");
      desc1->value("");
    }
      break;
    case 2:{
      prtsFile << "Arms" << " ";
      prtsFile << name2->value() << " ";
      prtsFile << num2->value() << " ";
      prtsFile << weight2->value() << " ";
      prtsFile << cost2->value() << " ";
      prtsFile << powA->value() << " ";
      prtsFile << desc2->value() << "\n";
      //clears value of input boxes after they're stored
      name2->value("");
      num2->value("");
      weight2->value("");
      cost2->value("");
      powA->value("");
      desc2->value("");
    }
      break;
    case 3:{
      prtsFile << "Torso" << " ";
      prtsFile << name3->value() << " ";
      prtsFile << num3->value() << " ";
      prtsFile << weight3->value() << " ";
      prtsFile << cost3->value() << " ";
      prtsFile << batt->value() << " ";
      prtsFile << desc3->value() << "\n";
      //clears value of input boxes after they're stored
      name3->value("");
      num3->value("");
      weight3->value("");
      cost3->value("");
      batt->value("");
      desc3->value("");
    }
      break;
    case 4:{
      prtsFile << "Locomotor" << " ";
      prtsFile << name4->value() << " ";
      prtsFile << num4->value() << " ";
      prtsFile << weight4->value() << " ";
      prtsFile << cost4->value() << " ";
      prtsFile << speed->value() << " ";
      prtsFile << powL->value() << " ";
      prtsFile << desc4->value() << "\n";
      //clears value of input boxes after they're stored
      name4->value("");
      num4->value("");
      weight4->value("");
      cost4->value("");
      speed->value("");
      powL->value("");
      desc4->value("");
    }
      break;
    case 5:{
      prtsFile << "Batteries" << " ";
      prtsFile << name5->value() << " ";
      prtsFile << num5->value() << " ";
      prtsFile << weight5->value() << " ";
      prtsFile << cost5->value() << " ";
      prtsFile << powB->value() << " ";
      prtsFile << desc5->value() << "\n";
      //clears value of input boxes after they're stored
      name5->value("");
      num5->value("");
      weight5->value("");
      cost5->value("");
      powB->value("");
      desc5->value("");
    }
      break;
    default:
      break;
  }

  fileNames.push_back("parts.txt");
}
/*----------------------salesByDate_CB CB--------------------*/
void salesByDate_CB(Fl_Widget* w, void* p){
  // Open & read models file
  ifstream readLine("orders.txt");
  if(!readLine.is_open()){
    cout << "Failed" << endl;
    exit(EXIT_FAILURE);
  }
  //Date from user input
  char fullDate[100]="";
  strcat(fullDate, month->value());
  strcat(fullDate, day->value());
  strcat(fullDate, year->value());
  //date read from orders file
  char fileFullDate[100];
  //char* result = new char[2000];
  int counter =0, temp=0;
  double modelTotal, modelCost, quantity, totalProfit;
  string comments;
  //save stuff from file to variables to display
  char associateName[100], customerName[100], orderNumber[100], dTemp1[100], monthTemp[100], dayTemp[100], dTemp4[500], yearTemp[100], modelIndex[100], modelName[100], modelQuantity[100], total[100], profitMargin[100];
  //THIS WILL NOT WORK WHEN COMMENTS HAS MORE THAN ONE WORD. NEED TO FIND A FIX TO READ MULTIPLE WORDS TO COMMENTS
  while(readLine >> associateName >> customerName >> orderNumber >> dTemp1 >> monthTemp >> dayTemp >> dTemp4 >> yearTemp >> modelIndex >>modelName >> quantity >> modelTotal >> modelCost){
    getline(readLine, comments);
    strcat(fileFullDate, monthTemp);
    strcat(fileFullDate, dayTemp);
    strcat(fileFullDate, yearTemp);
    //execute only once to put date on top
    if(temp ==0){
      strcat(result, "Date: ");
      strcat(result, month->value());
      strcat(result, " ");strcat(result, day->value());
      strcat(result, " ");strcat(result, year->value());
      strcat(result, "\n\n");
      temp++;
    }
    if(strcmp(fullDate, fileFullDate) == 0){
      totalProfit += (quantity*modelTotal) - (quantity*modelCost);
      sprintf(total, "%1.2f", modelTotal*quantity);
      sprintf(profitMargin, "%1.2f", (quantity*modelTotal) - (quantity*modelCost));
      sprintf(modelQuantity, "%1.0f", quantity);
      char count[10]; sprintf(count, "%d", counter);
      strcat(result, count);
      strcat(result, ") Sold By: ");
      strcat(result, associateName);
      strcat(result, "\n     Customer Name: ");
      strcat(result, customerName);
      strcat(result, "\n     Order Number: ");
      strcat(result, orderNumber);
      strcat(result, "\n     Sold Quantity: x");
      strcat(result, modelQuantity);
      strcat(result, "\n     Total Model Price: $");
      strcat(result, total);
      strcat(result, "\n     Profit Margin: ");
      strcat(result, profitMargin);
      strcat(result, "\n\n");
      counter++;
    }
    strcpy(fileFullDate, "");
  }
  char buffer[100];
  sprintf(buffer, "%1.2f", totalProfit);
  strcat(result, "Total Profit: $");
  strcat(result, buffer);
  disp->buffer(buff);
  buff->text(result);
  month->value("");
  day->value("");
  year->value("");
  strcpy(result, "");
}
/*----------------------showSales CB--------------------*/
void showSales_cb(Fl_Widget* w, void* p){
  // Open & read models file
  ifstream readLine("orders.txt");
  if(!readLine.is_open()){
    cout << "Failed" << endl;
    exit(EXIT_FAILURE);
  }
  char* result = new char[2000];
  int counter =1;
  double totalSales;
  //save stuff from file to variables to display
  string comments;//reads multiple space separated words
  char associateName[100], customerName[100], orderNumber[100], dTemp1[100], dTemp2[100], dTemp3[100], dTemp4[500], dTemp5[100], modelIndex[100], modelName[100], quantity[100], total[100];
  while(readLine >> associateName >> customerName >> orderNumber >> dTemp1 >> dTemp2 >> dTemp3 >> dTemp4 >> dTemp5 >> modelIndex >>modelName >> quantity >> total){
    getline(readLine, comments);
    if(strcmp(associateName, theChosenOne->value()) == 0){
      totalSales += atof(total);
      char count[10]; sprintf(count, "%d", counter);
      strcat(result, count);
      strcat(result, ") Sold By: ");
      strcat(result, associateName);
      strcat(result, "\n     Order Number: ");
      strcat(result, orderNumber);
      strcat(result, "\n     Customer Name: ");
      strcat(result, customerName);
      strcat(result, "\n     Total Price: $");
      strcat(result, total);
      strcat(result, "\n\n");
      counter++;
    }
  }
  theChosenOne->value("");
  char count[10]; sprintf(count, "%d", (counter-1));
  char buffer[1000];
  sprintf(buffer, "%1.2f", totalSales);
  strcat(result, "\n\nTotal Sales: ");
  strcat(result, count);
  strcat(result, "        Total Sales Revenue: $");
  strcat(result, buffer);
  disp3->buffer(buff3);
  buff3->text(result);
  theChosenOne->value("");
  strcpy(result, "");
}

/*----------------------showOrders CB--------------------*/
void showOrders_cb(Fl_Widget* w, void* p){
  // Open & read models file
  ifstream readLine("orders.txt");
  if(!readLine.is_open()){
    cout << "Failed" << endl;
    exit(EXIT_FAILURE);
  }
  char* result = new char[2000];
  int counter =1;
  double totalSales;
  //save stuff from file to variables to display
  string comments;//reads multiple space separated words
  char associateName[100], customerName[100], orderNumber[100], dTemp1[100], dTemp2[100], dTemp3[100], dTemp4[500], dTemp5[100], modelIndex[100], modelName[100], quantity[100], total[100];
  while(readLine >> associateName >> customerName >> orderNumber >> dTemp1 >> dTemp2 >> dTemp3 >> dTemp4 >> dTemp5 >> modelIndex >>modelName >> quantity >> total){
    getline(readLine, comments);
    if(strcmp(customerName, theChosenOne->value()) == 0)
    {
      totalSales += atof(total);
      char count[10]; sprintf(count, "%d", counter);
      strcat(result, count);
      strcat(result, ") Sold By: ");
      strcat(result, associateName);
      strcat(result, "\n     Order Number: ");
      strcat(result, orderNumber);
      strcat(result, "\n     Customer Name: ");
      strcat(result, customerName);
      strcat(result, "\n     Total Price: $");
      strcat(result, total);
      strcat(result, "\n\n");
      counter++;
    }
  }
  theChosenOne->value("");
  char count[10]; sprintf(count, "%d", (counter-1));
  char buffer[1000];
  sprintf(buffer, "%1.2f", totalSales);
  strcat(result, "\n\nTotal Orders: ");
  strcat(result, count);
  //strcat(result, "        Total Sales Revenue: $");
  //strcat(result, buffer);
  disp3->buffer(buff3);
  buff3->text(result);
  theChosenOne->value("");
  strcpy(result, "");
}

/*----------------------showBill CB--------------------*/
void showBill_cb(Fl_Widget* w, void* p){
  // Open & read models file
  ifstream readLine("orders.txt");
  if(!readLine.is_open()){
    cout << "Failed" << endl;
    exit(EXIT_FAILURE);
  }
  char* result = new char[2000];
  int counter =1;
  double totalSales;
  //save stuff from file to variables to display
  string comments;//reads multiple space separated words
  char associateName[100], customerName[100], orderNumber[100], dTemp1[100], dTemp2[100], dTemp3[100], dTemp4[500], dTemp5[100], modelIndex[100], modelName[100], quantity[100], total[100];
  while(readLine >> associateName >> customerName >> orderNumber >> dTemp1 >> dTemp2 >> dTemp3 >> dTemp4 >> dTemp5 >> modelIndex >>modelName >> quantity >> total){
    getline(readLine, comments);
    if(strcmp(orderNumber, theChosenOne->value()) == 0)
    {
      strcat(result, "Customer Name: ");
      strcat(result, customerName);
      strcat(result, "\nOrder Number: ");
      strcat(result, orderNumber);
      strcat(result, "\nModel Name: ");
      strcat(result, modelName);
      strcat(result, "\nQuantity: x");
      strcat(result, quantity);
      strcat(result, "\nTotal Price: $");
      strcat(result, total);
      strcat(result, "\n\n");
      counter++;
    }
  }
  theChosenOne->value("");
  disp3->buffer(buff3);
  buff3->text(result);
  theChosenOne->value("");
  strcpy(result, "");
}

/*-------------------------MenuBar CB----------------------*/
void undoCB(Fl_Widget *, void *)
{
  string undoFile = fileNames[fileNames.size() - 1];
  string line;
  vector<string> lines;
  ifstream inputStream(undoFile);

  while (getline(inputStream,line)) {
    lines.push_back(line);
  }
  inputStream.close();

  fstream outputStream(undoFile, ios::out | ios::trunc);
  if (outputStream.is_open())
  {
    for (int i=0; i < lines.size()-1; i++)
    {
      outputStream << lines[i] << "\n";
    }
    outputStream.close();
  }

  fileNames.pop_back();
}
/*----------------------MakeWin Base CLASS--------------------*/
// Generic class to make new windows
class MakeWin{
public:
  // Constructor w/no prams, for derived classes
  MakeWin(){};
  // Constructor w/method initialization for window
  MakeWin(int x,int y,const char* L): X(x),Y(y),lab(L){}
  void winProps(){
    win = new Fl_Window(X, Y, lab);     //make window
    win->color( FL_WHITE );    //background color white

    // Menu bar
    menu = new Fl_Menu_Bar(0,0,1400,25);
    menu->add("File/Undo",   FL_CTRL+'u', undoCB);
    //menu->add("NextTab", FL_CTRL+'t', nextTabCB);
    //menu->add("Edit/Submenu/Aaa");
    //menu->add("Edit/Submenu/Bbb");
  }
  void showWin(){
    win->end();     //no more additions
    win->show();    //show window
  }
private:
  int X, Y;
  const char* lab;
  Fl_Window *win;
};

/*----------------------MakeBox Base CLASS--------------------*/
// Main window display box thats on top of buttons
class MakeBox
{
public:
  MakeBox(){};
  MakeBox(int s, int x, int y, int w, int h, const char* L):S(s),X(x),Y(y),W(w),H(h),lab(L){}
  void boxProps(){
    Fl_Box *box = new Fl_Box(X,Y,W,H,lab);
    box->box(FL_RSHADOW_BOX);
    box->align(FL_ALIGN_WRAP);  // wrap text
    box->labelfont(FL_BOLD);
    box->labelsize(S);
    box->labeltype(FL_SHADOW_LABEL);
  }
private:
  int S, X, Y, W, H;
  const char* lab;
};
/*---------------------DisplayBox Base CLASS------------------*/
class DisplayBox{
public:
  DisplayBox(){};
  DisplayBox(int wx, int wy, int s, int x, int y, int w, int h, const char* L){
    Fl_Window *win = new Fl_Window(wx,wy);
    Fl_Box *box = new Fl_Box(x,y,w,h,L);
    box->box(FL_UP_BOX);
    box->align(FL_ALIGN_WRAP);
    box->labelfont(FL_BOLD);
    box->labelsize(s);
    box->labeltype(FL_NORMAL_LABEL);
    win->end();
    win->show();
  }
};
/*---------------------MakeParts CLASS-------------------*/
class MakeParts : public MakeWin{
public:
  MakeParts(){}
  MakeParts(int x,int y,const char* l){
    wind = new Fl_Window(x,y,l);

    // Browser to act as "tab selector"
    bro = new Fl_Hold_Browser(10,10,150,400-20);
    bro->add("Head");
    bro->add("Arms");
    bro->add("Torso");
    bro->add("Locomotor");
    bro->add("Batteries");

    // Make 6 groups with different contents
    grp[0] = new Fl_Group(170,10,450-30,400-20,"New Part: Head");
    grp[0]->box(FL_ENGRAVED_BOX); grp[0]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grp[0]->labelsize(24);
    name1 = new Fl_Input(170+140,140+00,200,20,"Part Name:");
    num1 = new Fl_Int_Input(170+140,140+30,200,20,"Part Number:");
    weight1 = new Fl_Float_Input(170+140,140+60,200,20,"Part Weight (lbs):");
    cost1 = new Fl_Float_Input(170+140,140+90,200,20,"Part Cost $:");
    desc1 = new Fl_Input(170+140,140+120,200,20,"Part Description:");
    Fl_Button* sub1 = new Fl_Button(170+140,140+150,200,20,"Submit");
    sub1->callback(savePrtCB, (void*)1);
    grp[0]->end();

    grp[1] = new Fl_Group(170,10,450-30,400-20,"New Part: Arms");
    grp[1]->box(FL_ENGRAVED_BOX); grp[1]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grp[1]->labelsize(24);
    name2 = new Fl_Input(170+140,140+00,200,20,"Part Name:");
    num2 = new Fl_Int_Input(170+140,140+30,200,20,"Part Number:");
    weight2 = new Fl_Float_Input(170+140,140+60,200,20,"Part Weight (lbs):");
    cost2 = new Fl_Float_Input(170+140,140+90,200,20,"Part Cost $:");
    powA = new Fl_Float_Input(170+140,140+120,200,20,"Power Consumed\n(Watts):");
    desc2 = new Fl_Input(170+140,140+150,200,20,"Part Description:");
    Fl_Button* sub2 = new Fl_Button(170+140,140+180,200,20,"Submit");
    sub2->callback(savePrtCB, (void*)2);  // when submit is pushed
    grp[1]->end();

    grp[2] = new Fl_Group(170,10,450-30,400-20,"New Part: Torso");
    grp[2]->box(FL_ENGRAVED_BOX); grp[2]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grp[2]->labelsize(24);
    name3 = new Fl_Input(190+140,140+00,200,20,"Part Name:");
    num3 = new Fl_Int_Input(190+140,140+30,200,20,"Part Number:");
    weight3 = new Fl_Float_Input(190+140,140+60,200,20,"Part Weight (lbs):");
    cost3 = new Fl_Float_Input(190+140,140+90,200,20,"Part Cost $:");
    batt = new Fl_Int_Input(190+140,140+120,200,20,"Number of Battery\nCompartments(up to 3):");
    desc3 = new Fl_Input(190+140,140+150,200,20,"Part Description:");
    Fl_Button* sub3 = new Fl_Button(190+140,140+180,200,20,"Submit");
    sub3->callback(savePrtCB, (void*)3);  // when submit is pushed
    grp[2]->end();

    grp[3] = new Fl_Group(170,10,450-30,400-20,"New Part: Locomotor");
    grp[3]->box(FL_ENGRAVED_BOX); grp[3]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grp[3]->labelsize(24);
    name4 = new Fl_Input(170+140,140+00,200,20,"Part Name:");
    num4 = new Fl_Int_Input(170+140,140+30,200,20,"Part Number:");
    weight4 = new Fl_Float_Input(170+140,140+60,200,20,"Part Weight (lbs):");
    cost4 = new Fl_Float_Input(170+140,140+90,200,20,"Part Cost $:");
    speed = new Fl_Float_Input(170+140,140+120,200,20,"Max Speed (MPH):");
    powL = new Fl_Float_Input(170+140,140+150,200,20,"Power Consumed\n(Watts):");
    desc4 = new Fl_Input(170+140,140+180,200,20,"Part Description:");
    Fl_Button* sub4 = new Fl_Button(170+140,140+210,200,20,"Submit");
    sub4->callback(savePrtCB, (void*)4);  // when submit is pushed
    grp[3]->end();

    grp[4] = new Fl_Group(170,10,450-30,400-20,"New Part: Batteries");
    grp[4]->box(FL_ENGRAVED_BOX); grp[4]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grp[4]->labelsize(24);
    name5 = new Fl_Input(170+140,140+00,200,20,"Part Name:");
    num5 = new Fl_Int_Input(170+140,140+30,200,20,"Part Number:");
    weight5 = new Fl_Float_Input(170+140,140+60,200,20,"Part Weight (lbs):");
    cost5 = new Fl_Float_Input(170+140,140+90,200,20,"Part Cost $:");
    powB = new Fl_Float_Input(170+140,140+120,200,20,"Contained Power\n(kWh):");
    desc5 = new Fl_Input(170+140,140+150,200,20,"Part Description:");
    Fl_Button* sub5 = new Fl_Button(170+140,140+180,200,20,"Submit");
    sub5->callback(savePrtCB, (void*)5);  // when submit is pushed
    grp[4]->end();

    // Set a callback for the browser, initialize first selection
    bro->callback(SelectGroupCB);
    bro->select(1);
    SelectGroupCB(0,0);                // (updates visible group based on our select()tion)
    wind->end();
    wind->show();
  }
};
/*---------------------MakeMods CLASS--------------------*/
class MakeModels{
public:
  MakeModels(){}
  MakeModels(int x,int y,int w,int h,const char* l){
    windM = new Fl_Window(800,700,l);

    // Open & read parts file
    ifstream readLine;
    string display;
    char *data;
    readLine.open("parts.txt");

    if(!readLine.is_open()){
      cout << "Failed" << endl;
      exit(EXIT_FAILURE);
    }

    string line;
    int count = 0;
    while (!readLine.eof()) {
      getline(readLine, line);
      display = display + line + "\n";
    }

    data = new char[display.length()+1];
    strcpy(data,display.c_str());

    // Browser to act as "tab selector"
    broM = new Fl_Hold_Browser(x,y,w-200,h);
    broM->add("View Parts");
    broM->add("Create Models");

    // Create new output box
    Fl_Multiline_Output *output;

    // Make 2 groups with different contents
    grpM[0] = new Fl_Group(17*x,y,(2*w)-30,h,"Available Parts");
    grpM[0]->box(FL_ENGRAVED_BOX); grpM[0]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP|FL_ALIGN_CENTER); grpM[0]->labelsize(24);
    output = new Fl_Multiline_Output(170+10,240+00,605,h/2);
    output->value(data);
    grpM[0]->end();

    grpM[1] = new Fl_Group(17*x,y,(2*w)-30,h,"Build a Robot Model");
    grpM[1]->box(FL_ENGRAVED_BOX); grpM[1]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grpM[1]->labelsize(24);
    name = new Fl_Input(170+200,140+00,200,20,"Model Name: ");
    num = new Fl_Int_Input(170+200,140+30,200,20,"Model Number: ");
    head = new Fl_Input(170+200,140+60,200,20,"Head Part Name: ");
    headP = new Fl_Float_Input(170+490,140+60,100,20,"Cost $: ");
    arm1 = new Fl_Input(170+200,140+90,200,20,"Right Arm Part Name: ");
    armP1 = new Fl_Float_Input(170+490,140+90,100,20,"Cost $: ");
    arm2 = new Fl_Input(170+200,140+120,200,20,"Left Arm Part Name: ");
    armP2 = new Fl_Float_Input(170+490,140+120,100,20,"Cost $: ");
    torso = new Fl_Input(170+200,140+150,200,20,"Torso Part Name: ");
    torP = new Fl_Float_Input(170+490,140+150,100,20,"Cost $: ");
    loco = new Fl_Input(170+200,140+180,200,20,"Locomotor Part Name: ");
    locoP = new Fl_Float_Input(170+490,140+180,100,20,"Cost $: ");
    battM = new Fl_Input(170+200,140+210,200,20,"Battery Part Name: ");
    battP = new Fl_Float_Input(170+490,140+210,100,20,"Cost $: ");
    price = new Fl_Float_Input(170+200,140+240,200,20,"Model Price $:");
    cost = new Fl_Output(170+490,140+240,100,20,"Total Cost $: ");
    Fl_Button* sub = new Fl_Button(170+200,140+270,200,20,"Submit");
    sub->callback(saveModsCB);
    Fl_Button* calc = new Fl_Button(170+490,140+270,100,20,"Calculate");
    calc->callback(calcCostCB);
    grpM[1]->end();

    broM->callback(SelectModGroupCB);
    broM->select(1);
    SelectModGroupCB(0,0);
    windM->end();
    windM->show();
  }
};
/*---------------------MakeSalesAssociate CLASS--------------------*/
class MakeSalesAssociate{
private:
public:
  MakeSalesAssociate(){}
  MakeSalesAssociate(int x,int y,int w,int h,const char* l){
    windSA = new Fl_Window(800,700,l);
      //creates file if does not exist before reading
    ofstream associateFile("salesAssociate.txt", ios_base::out|ios_base::app);
      if( associateFile.fail() ){
          cerr << "failed to open file" << endl;
          // use displaybox class to show error w/GUI
      }
    // open & read salesAssociate file
    ifstream readSalesAssociateFile("salesAssociate.txt");
    if( !readSalesAssociateFile.is_open() ){
      cerr << "failed to open orders file" << endl;
    }
    // Browser to act as "tab selector"
    broSA = new Fl_Hold_Browser(x,y,w-180,h);
    broSA->add("View Current Associates");
    broSA->add("Create Associate");

    grpSA[0] = new Fl_Group(17*x,y,(2*w)-30,h,"Current Associates");
    grpSA[0]->box(FL_ENGRAVED_BOX); grpSA[0]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grpSA[0]->labelsize(24);
    buff4 = new Fl_Text_Buffer();
    disp4 = new Fl_Text_Display(170+10,y+80,605,h/1.25);
    ifstream readLine("salesAssociate.txt");
    if(!readLine.is_open()){
      cout << "Failed" << endl;
      exit(EXIT_FAILURE);
    }
    char* result = new char[2000];
    int counter =1;
    //save stuff from file to variables to display
    char associateName[100], employeeNumber2[100];
    while(readLine >> associateName >> employeeNumber2){
      char count[10]; sprintf(count, "%d", counter);
      strcat(result, count);
      strcat(result, ") Associate Name: ");
      strcat(result, associateName);
      strcat(result, "\n     Employee Number: ");
      strcat(result, employeeNumber2);
      strcat(result, "\n\n");
      counter++;
    }
    char count[10]; sprintf(count, "%d", (counter-1));
    char buffer[1000];
    disp4->buffer(buff4);
    buff4->text(result);
    strcpy(result, "");
    grpSA[0]->end();

    grpSA[1] = new Fl_Group(17*x,y,(2*w)-30,h,"Create Sales Associate");
    grpSA[1]->box(FL_ENGRAVED_BOX); grpSA[1]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP|FL_ALIGN_CENTER); grpSA[1]->labelsize(24);
    salesAssociateName = new Fl_Input(170+240,140+00,200,20,"Associate First Name: ");
    employeeNumber = new Fl_Int_Input(170+240,140+30,200,20,"Employee Number: ");
    Fl_Button* sub1 = new Fl_Button(170+240,140+60,200,20,"Submit");
    sub1->callback(saveAssociateCB);
    grpSA[1]->end();


    broSA->callback(SelectAssociatesGroupCB);
    broSA->select(1);
    SelectAssociatesGroupCB(0,0);
    windSA->end();
    windSA->show();
  }
};
/*---------------------MakeOrders CLASS--------------------*/
class MakeOrders{
private:
public:
  MakeOrders(){}
  MakeOrders(int x,int y,int w,int h,const char* l){
    windM = new Fl_Window(800,700,l);

    // Open & read models file
    ifstream readLine("models.txt");
    string display;
    char *data;
    if(!readLine.is_open()){
      cout << "Failed" << endl;
      exit(EXIT_FAILURE);
    }
      
    string line;
    int i=0, counter=0;
    //int count;
    while (getline(readLine, line)) {
      display += to_string(i++) + ") ";
      display = display + line + "\n";
      counter++;
    }

    data = new char[display.length()+1];
    strcpy(data,display.c_str());

    ifstream readLine2("customers.txt");
    string custDisplay;
    char *custData;
    if(!readLine2.is_open()){
      cout << "Failed" << endl;
      //exit(EXIT_FAILURE);
    }

    string line2;
    int j=0;
    //int count;
    while (getline(readLine2, line2)) {
      custDisplay += to_string(j++) + ") ";
      custDisplay = custDisplay + line2 + "\n";
    }
    custData = new char[custDisplay.length()+1];
    strcpy(custData,custDisplay.c_str());


    // Browser to act as "tab selector"
    broO = new Fl_Hold_Browser(x,y,w-200,h);
    broO->add("View Models");
    broO->add("Create Order");
    broO->add("View Customers");

    // Create new output box
    Fl_Multiline_Output *output;

    // Make 3 groups with different contents
    grpO[0] = new Fl_Group(17*x,y,(2*w)-30,h,"Available Models");
    grpO[0]->box(FL_ENGRAVED_BOX); grpO[0]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP|FL_ALIGN_CENTER); grpO[0]->labelsize(24);
    output = new Fl_Multiline_Output(170+10,240+00,605,h/2);
    output->value(data);
    grpO[0]->end();
    
    grpO[1] = new Fl_Group(17*x,y,(2*w)-30,h,"Build a New Robot Order");
    grpO[1]->box(FL_ENGRAVED_BOX); grpO[1]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grpO[1]->labelsize(24);
    associateName = new Fl_Input(170+240,140+00,200,20,"Associate First Name: ");
    customerName= new Fl_Input(170+240,140+30,200,20,"Customer First Name: ");
    modelIndex = new Fl_Int_Input(170+240,140+60,200,20,"Model Index: ");
    quantity = new Fl_Int_Input(170+240,140+90,200,20,"Quantity: ");
    orderNumber = new Fl_Int_Input(170+240,140+120,200,20,"Order Number: ");
    comments = new Fl_Input(170+240,140+150,200,20,"Comments: ");
    Fl_Button* sub2 = new Fl_Button(170+140,140+180,150,20,"Checkout Summary");
    Fl_Button* sub1 = new Fl_Button(170+320,140+180,150,20,"Submit");
    sub1->callback(saveOrdsCB);
    sub2->callback(checkoutCB);
    grpO[1]->end();

    // Create new output box
    Fl_Multiline_Output *output2;

    grpO[2] = new Fl_Group(17*x,y,(2*w)-30,h,"Customers");
    grpO[2]->box(FL_ENGRAVED_BOX);
    grpO[2]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP);
    grpO[2]->labelsize(24);
    output2 = new Fl_Multiline_Output(170+10,240+00,605,h/2);
    output2->value(custData);
    grpO[2]->end();

    broO->callback(SelectOrdGroupCB);
    broO->select(1);
    SelectOrdGroupCB(0,0);
    windM->end();
    windM->show();
  }
};
/*---------------------MakeCustomers CLASS--------------------*/
class MakeCustomers{
private:
public:
  MakeCustomers(){}
  MakeCustomers(int x,int y,int w,int h,const char* l){
    windM = new Fl_Window(800,700,l);

    broC = new Fl_Hold_Browser(x,y,w-200,h);
    broC->add("Create Customer");


    grpC[0] = new Fl_Group(17*x,y,(2*w)-30,h,"Create a New Customer");
    grpC[0]->box(FL_ENGRAVED_BOX);
    grpC[0]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP);
    grpC[0]->labelsize(24);

    customerFirstName = new Fl_Input(170+240,140+00,200,20,"First Name: ");
    customerLastName= new Fl_Input(170+240,140+30,200,20,"Last Name: ");
    customerEmail = new Fl_Input(170+240,140+60,200,20,"Email: ");
    customerPhone = new Fl_Input(170+240,140+90,200,20,"Phone Number: ");
    customerAdddress = new Fl_Input(170+240,140+120,200,20,"Home Address: ");

    Fl_Button* sub3 = new Fl_Button(170+240,140+150,200,20,"Submit");
    sub3->callback(saveCustCB);
    grpC[0]->end();

    broC->callback(SelectCustGroupCB);
    broC->select(1);
    SelectCustGroupCB(0,0);

    windM->end();
    windM->show();
  }
};
/*----------------used for scroll bar-----------------*/
class Drawing : public Fl_Widget {
  void draw();
public:
  Drawing(int X,int Y,int W,int H,const char* L) : Fl_Widget(X,Y,W,H,L) {
    align(FL_ALIGN_TOP);
    box(FL_FLAT_BOX);
    color(FL_WHITE);
  }
};
/*----------------PBViewSalesLog CLASS-----------------*/
class PBViewSalesLog{
private:
public:
  PBViewSalesLog(){};
  PBViewSalesLog(int x,int y,int w,int h,const char* l){
    windPB = new Fl_Window(800,700,l);

    // Browser to act as "tab selector"
    broPB = new Fl_Hold_Browser(x,y,w-200,h);
    broPB->add("View All Sales");
    broPB->add("View Sales by Date");
    broPB->add("View Associate Sales");

    // Make 3 groups with different contents
    grpPB[0] = new Fl_Group(17*x,y,(2*w)-30,h,"All Sales");
    grpPB[0]->box(FL_ENGRAVED_BOX); grpPB[0]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP|FL_ALIGN_CENTER); grpPB[0]->labelsize(24);
    //causing it to crash
    buff1 = new Fl_Text_Buffer();
    disp1 = new Fl_Text_Display(170+10,y+80,605,h/1.25);
    ifstream readLine("orders.txt");
    if(!readLine.is_open()){
      cout << "Failed" << endl;
      exit(EXIT_FAILURE);
    }
    char* result = new char[2000];
    int counter =0;
    double modelTotal, modelCost, quantity, totalProfit;
    string comments;
    //save stuff from file to variables to display
    char associateName[100], customerName[100], orderNumber[100], dTemp1[100], dTemp2[100], dTemp3[100], dTemp4[500], dTemp5[100], modelIndex[100], modelName[100], modelQuantity[100], total[100], profitMargin[100];
    //THIS WILL NOT WORK WHEN COMMENTS HAS MORE THAN ONE WORD. NEED TO FIND A FIX TO READ MULTIPLE WORDS TO COMMENTS
    while(readLine >> associateName >> customerName >> orderNumber >> dTemp1 >> dTemp2 >> dTemp3 >> dTemp4 >> dTemp5 >> modelIndex >>modelName >> quantity >> modelTotal >> modelCost){
      getline(readLine, comments);
      totalProfit += (quantity*modelTotal) - (quantity*modelCost);
      sprintf(total, "%1.2f", modelTotal*quantity);
      sprintf(profitMargin, "%1.2f", (quantity*modelTotal) - (quantity*modelCost));
      sprintf(modelQuantity, "%1.0f", quantity);
      char count[10]; sprintf(count, "%d", counter);
      strcat(result, count);
      strcat(result, ") Sold By: ");
      strcat(result, associateName);
      strcat(result, "\n     Customer Name: ");
      strcat(result, customerName);
      strcat(result, "\n     Order Number: ");
      strcat(result, orderNumber);
      strcat(result, "\n     Sold Quantity: x");
      strcat(result, modelQuantity);
      strcat(result, "\n     Total Model Price: $");
      strcat(result, total);
      strcat(result, "\n     Profit Margin: ");
      strcat(result, profitMargin);
      strcat(result, "\n\n");
      counter++;
    }
    char temp[100];
    sprintf(temp, "%1.2f", totalProfit);
    strcat(result, "Total Profit: $");
    strcat(result, temp);
    disp1->buffer(buff1);
    buff1->text(result);
    grpPB[0]->end();
    /*-------------------------------------------------------------------------------------------------------------------------------------------*/
    grpPB[1] = new Fl_Group(17*x,y,(2*w)-30,h,"Sales by Date");
    grpPB[1]->box(FL_ENGRAVED_BOX); grpPB[1]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grpPB[1]->labelsize(24);
    month = new Fl_Input(170+160,y+50,60,20,"Month (Ex. Nov, Dec): ");
    day = new Fl_Int_Input(170+260,y+50,60,20,"Day: ");
    year = new Fl_Int_Input(170+450,y+50,60,20,"Year (4 Digit Year): ");
    Fl_Button* sub1 = new Fl_Button(170+520,y+50,80,20,"Enter");
    sub1->callback(salesByDate_CB);
    buff = new Fl_Text_Buffer();
    disp = new Fl_Text_Display(170+10,y+80,605,h/1.25);
    grpPB[1]->end();

    grpPB[2] = new Fl_Group(17*x,y,(2*w)-30,h,"Associate Sales");
    grpPB[2]->box(FL_ENGRAVED_BOX); grpPB[2]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP); grpPB[2]->labelsize(24);
    theChosenOne = new Fl_Input(170+160,y+50,200,20,"Associates First Name: ");
    sub1 = new Fl_Button(170+370,y+50,150,20,"Submit");
    sub1->callback(showSales_cb);
    //TODO: NEED TO FIGURE OUT A WAY TO DISPLAY HERE INSTEAD OF NEW WINDOW
    buff3 = new Fl_Text_Buffer();
    disp3 = new Fl_Text_Display(170+10,y+80,605,h/1.25);
    grpPB[2]->end();

    broPB->callback(SelectSalesGroupCB);
    broPB->select(1);
    SelectSalesGroupCB(0,0);
    windPB->resizable(disp1);
    windPB->resizable(disp);
    windPB->resizable(disp3);
    windPB->end();
    windPB->show();
  }

};
/*----------------ViewYourSalesLog CLASS-----------------*/
class ViewYourSalesLog{
private:
public:
  ViewYourSalesLog(){}
  ViewYourSalesLog(int x,int y,int w,int h,const char* l){
    windM = new Fl_Window(800,700,l);
    grpPB[0] = new Fl_Group(17*x,y,(2*w)-30,h,"Associate Sales");
    grpPB[0]->box(FL_ENGRAVED_BOX); grpPB[0]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP|FL_ALIGN_CENTER); grpPB[0]->labelsize(24);
    theChosenOne = new Fl_Input(170+160,y+50,200,20,"Associates First Name: ");
    Fl_Button* sub1 = new Fl_Button(170+370,y+50,150,20,"Submit");
    sub1->callback(showSales_cb);
    buff3 = new Fl_Text_Buffer();
    disp3 = new Fl_Text_Display(170+10,y+80,605,h/1.25);
    grpPB[0]->end();
    windM->resizable(disp3);
    windM->end();
    windM->show();
  }
};

/*----------------ViewYourOrdersLog CLASS-----------------*/
class ViewYourOrdersLog{
private:
public:
  ViewYourOrdersLog(){}
  ViewYourOrdersLog(int x,int y,int w,int h,const char* l){
    windM = new Fl_Window(800,700,l);
    grpPB[0] = new Fl_Group(17*x,y,(2*w)-30,h,"Customer Orders");
    grpPB[0]->box(FL_ENGRAVED_BOX); grpPB[0]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP|FL_ALIGN_CENTER); grpPB[0]->labelsize(24);
    theChosenOne = new Fl_Input(170+160,y+50,200,20,"Customers First Name: ");
    Fl_Button* sub1 = new Fl_Button(170+370,y+50,150,20,"Submit");
    sub1->callback(showOrders_cb);
    buff3 = new Fl_Text_Buffer();
    disp3 = new Fl_Text_Display(170+10,y+80,605,h/1.25);
    grpPB[0]->end();
    windM->resizable(disp3);
    windM->end();
    windM->show();
  }
};

/*----------------ViewYourBill CLASS-----------------*/
class ViewYourBill{
private:
public:
  ViewYourBill(){}
  ViewYourBill(int x,int y,int w,int h,const char* l){
    windM = new Fl_Window(800,700,l);
    grpPB[0] = new Fl_Group(17*x,y,(2*w)-30,h,"Customer Bill");
    grpPB[0]->box(FL_ENGRAVED_BOX); grpPB[0]->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP|FL_ALIGN_CENTER); grpPB[0]->labelsize(24);
    theChosenOne = new Fl_Input(170+160,y+50,200,20,"Order Number: ");
    Fl_Button* sub1 = new Fl_Button(170+370,y+50,150,20,"Submit");
    sub1->callback(showBill_cb);
    buff3 = new Fl_Text_Buffer();
    disp3 = new Fl_Text_Display(170+10,y+80,605,h/1.25);
    grpPB[0]->end();
    windM->resizable(disp3);
    windM->end();
    windM->show();
  }
};

/*-------------------MakeButtons CLASS-------------------*/
class MakeButtons : DisplayBox, MakeParts, MakeModels, MakeOrders{
public:

  MakeButtons(int x,int y,int w,int h,const char* L):X(x),Y(y),W(w),H(h),lab(L){}
  void butProps(int k){
    Fl_Button *but = new Fl_Button( X,Y,W,H,lab );
    switch( k )     // Get which button was pushed
    {
      case 1:
        but->callback( pmCB );    // callbacks
        break;
      case 2:
        but->callback( pbCB );
        break;
      case 3:
        but->callback( saCB );
        break;
      case 4:
        but->callback( bcCB );
        break;
      case 5:
        but->callback( docCB );
        break;
      case 6:
        but->callback( catCB );
    }
  }
  //---------------------PM Handle Method--------------------
  static void pmHandleMenu(Fl_Widget *w, void *v){
    if(!w || !v) return;    // no values passed
    const char* lab = "Create Parts";
    switch( (intptr_t)v ){
      case 1:
      {
        if(fl_choice("Are you the PM?", NULL, fl_no, fl_yes) == 2)
          MakeParts prts(600,400,lab);
        else
          DisplayBox box(640, 120, 36, 0, 0, 640, 120, "Only the PM can create parts");
        break;
      }
      case 2:
      {
        if(fl_choice("Are you the PM?", NULL, fl_no, fl_yes) == 2)
          MakeModels models(10,10,350,700-20,"Make Models");
        else
          DisplayBox box(640, 120, 36, 0, 0, 640, 120, "Only the PM can create models");
        break;
      }
      case 3:
      {
        if(fl_choice("Are you the PM?", NULL, fl_no, fl_yes) == 2)
          cout << "code to display robot Models" << endl;
        else
          DisplayBox box(640, 120, 36, 0, 0, 640, 120, "Only the PM can view parts");
      }
        break;
    }
  }
  //------------------------PM Callback----------------------
  static void pmCB(Fl_Widget *w, void*)
  {
    Fl_Menu_Item rclick_menu[] = {      // array of popup menu options
      { "Create Robot Parts",  0, pmHandleMenu, (void*)1 },
      { "Create Robot Models",  0, pmHandleMenu, (void*)2 },  // calls handle method with given #
      { "View Robot Parts",  0, pmHandleMenu, (void*)3 },
      { 0 },
      { 0 }
    };
    const Fl_Menu_Item *m = rclick_menu->popup( Fl::event_x(), Fl::event_y(), 0, 0, 0 );    // popup on right click
    if ( m )
      m->do_callback( w, m->user_data() );    // if right click rcvd do the callback
    return;
  }
  //---------------------PB Handle Method--------------------
  static void pbHandleMenu(Fl_Widget *w, void *v)    //works the same as the PM handlw method
  {
    if(!w || !v) return;
    switch( (intptr_t)v )
    {
      case 1:
      {
        if(fl_choice("Are you the PB?", NULL, fl_no, fl_yes) == 2)
        {
          PBViewSalesLog pbViewSales(10,10,350,700-20,"Sales Log");
        }
        else
          DisplayBox box(640, 120, 36, 0, 0, 640, 120, "Only the PB can view all sales");
        break;
      }
      case 2:
      {
        if(fl_choice("Are you the PB?", NULL, fl_no, fl_yes) == 2){
          //TODO: CREATE A SALES ASSOCIATE TIES BACK WITH CREATE ORDER
          //makeSalesAssociate
          MakeSalesAssociate salesAssociate(10,10,350,700-20,"Sales Associate");
        }
        else
          DisplayBox box(640, 120, 36, 0, 0, 640, 120, "Only the PB can view sales reports for all associates");
        break;
      }
      case 3:
      {
        if(fl_choice("Are you the PB?", NULL, fl_no, fl_yes) == 2)
          MakeCustomers customers(10,10,350,700-20,"Make Customers");
        else
          DisplayBox box(640, 120, 36, 0, 0, 640, 120, "Only the PB can edit/view the prefered customer list.");
        break;
      }
    }
  }
  //------------------------PB Callback----------------------
  static void pbCB(Fl_Widget *w, void*)    // Works the same as PM callback
  {
    Fl_Menu_Item rclick_menu[] = {
      { "View sales",  0, pbHandleMenu, (void*)1 },
      { "Create Sales Associate",  0, pbHandleMenu, (void*)2 },
      { "Create list of prefered customers",  0, pbHandleMenu, (void*)3 },
      { 0 },
      { 0 }
    };
    const Fl_Menu_Item *m = rclick_menu->popup( Fl::event_x(), Fl::event_y(), 0, 0, 0 );
    if ( m )
      m->do_callback( w, m->user_data() );
    return;
  }
  //---------------------SA Handle Method--------------------
  static void saHandleMenu(Fl_Widget *w, void *v)
  {
    if(!w || !v) return;
    switch( (intptr_t)v )
    {
      case 1:
      {
        if(fl_choice("Are you the SA?", NULL, fl_no, fl_yes) == 2)
          MakeOrders orders(10,10,350,700-20,"Create Robot Orders");
        else
          DisplayBox box(640, 120, 36, 0, 0, 640, 120, "Only the SA can create orders.");
        break;
      }
      case 2:
      {
        if(fl_choice("Are you a RRS staff memeber?", NULL, fl_no, fl_yes) == 2){
          ViewYourSalesLog salesLog(10,10,350,700-20,"Sales log");

        }
        else
          DisplayBox box(640, 120, 36, 0, 0, 640, 120, "Only RRS staff can view SA sales report");
        break;
      }
    }
  }
  //------------------------SA Callback----------------------
  static void saCB(Fl_Widget *w, void*)
  {
    Fl_Menu_Item rclick_menu[] = {
      {"Create robot order",0,saHandleMenu,(void*)1},
      {"View your sales log",0,saHandleMenu,(void*)2},
      { 0 },
      { 0 }
    };
    const Fl_Menu_Item *m = rclick_menu->popup( Fl::event_x(), Fl::event_y(), 0, 0, 0 );
    if ( m )
      m->do_callback( w, m->user_data() );
    return;
  }
  //---------------------BC Handle Method--------------------
  static void bcHandleMenu(Fl_Widget *w, void *v)
  {
    if(!w || !v) return;
    switch( (intptr_t)v )
    {
      case 1:
      {
        ViewYourOrdersLog ordersLog(10,10,350,700-20,"Orders Log");
        break;
      }
      case 2:
      {
        ViewYourBill bill(10,10,350,700-20,"Customer Bill");
        break;      }
    }
  }
  //------------------------BC Callback----------------------
  static void bcCB(Fl_Widget *w, void*)
  {
    Fl_Menu_Item rclick_menu[] = {
      { "View orders",  0, bcHandleMenu, (void*)1 },
      { "view bill",  0, bcHandleMenu, (void*)2 },
      { 0 },
      { 0 }
    };
    const Fl_Menu_Item *m = rclick_menu->popup( Fl::event_x(), Fl::event_y(), 0, 0, 0 );
    if ( m )
      m->do_callback( w, m->user_data() );
    return;
  }
  //------------------------Doc Callback----------------------
  static void docCB(Fl_Widget *w, void*)
  {
    Fl_Window *win = new Fl_Window(650, 480);       // create new win for display
    Fl_Text_Buffer *buff = new Fl_Text_Buffer();    // make a buffer to display text
    Fl_Text_Display *disp = new Fl_Text_Display(20, 20, 650-40, 480-40, "Program Documentation");   // display box
    disp->buffer(buff);     // set buffer
    win->resizable(*disp);  // make window resizable
    win->show();            //show window
    //txt to display in window
    buff->text("This program facilitates the following processes for Robbie Robot Shop: creating robot parts,\ncreating robot models, displaying the parts and models, creating orders, viewing order history\nand customer bill, and generating sales reports. The undo and save featres can be found under\nthe 'file' menubar tab.");
  }
  //------------------------cat Callback----------------------
  static void catCB(Fl_Widget *w, void*)
  {
    Fl_Window *win = new Fl_Window(650, 480);       // create new win for display

    //reading models to get the needed information
    ifstream readLine("models.txt");
    if( readLine.fail() ){
      cout << "Failed" << endl;
      exit(EXIT_FAILURE);
    }

    char* result = new char[2000];
    int counter =1;
    int y = 20;
    
    char* modLabel;

    //save stuff from file to variables to display
    string comments;
    char modName[100], modNumb[100], modHead[100], modArm1[100], modArm2[100], modTors[100], modLoco[500], modBatt[100], modPrice[100], modCost[100];

    while(readLine >> modName >> modNumb >> modHead >> modArm1 >> modArm2 >> modTors >> modLoco >> modBatt >> modPrice >>modCost){
      char count[10]; sprintf(count, "%d", counter);
      strcat(result, count);
      strcat(result, ") Model Name: ");
      strcat(result, modName);
      strcat(result, "\n    Model Number: ");
      strcat(result, modNumb);
      strcat(result, "\n    Model Head: ");
      strcat(result, modHead);
      strcat(result, "\n    Model Right Arm: ");
      strcat(result, modArm1);
      strcat(result, "\n    Model Left Arm: ");
      strcat(result, modArm2);
      strcat(result, "\n    Model Torso: ");
      strcat(result, modTors);
      strcat(result, "\n    Model Locomotor: ");
      strcat(result, modLoco);
      strcat(result, "\n    Model Battery: ");
      strcat(result, modBatt);
      strcat(result, "\n    Model Price $: ");
      strcat(result, modPrice);
      strcat(result, "\n    Production Cost $: ");
      strcat(result, modCost);
      strcat(result, "\n\n");

      modLabel = modName;
      Fl_Button* image = new Fl_Button(330,y,150,20);
      image->copy_label(modLabel);
        
      image->callback(viewImage,(void*)(size_t)counter);
      Fl_Button* pieChart = new Fl_Button(330,y+20,150,20,"View Pie Chart");
      pieChart->callback(viewPieCharts, (void*)(size_t)counter);
      y += 50;
      counter++;
    }

    // buffer to display text
    Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    // display box
    Fl_Text_Display *disp = new Fl_Text_Display(20, 20, 300, 480-40, "Model Catalogue");
    // set buffer
    disp->buffer(buff);
    win->resizable(*disp);  // make window resizable
    win->show();            //show window
    //txt to display in window
    buff->text(result);
  }
private:
  int X, Y, W, H, key;
  const char* lab;
};
/*-------------------------------------------------------Pie Chart Callback-----------------------------------------------*/
void viewPieCharts(Fl_Widget* w, void* p)
{

    const int NUM_COMPONENTS = 6;
    ifstream modelsFile;
    string line;
    int counter = 0;            // tells me how many model are in the file

    struct models
    {
        string chartNames[NUM_COMPONENTS];
        double chartCost[NUM_COMPONENTS];
        double headCost, rightArmCost, leftArmCost, torsoCost, locomotorCost, batteriesCost;
        string modelName, head, rightArm, leftArm, torso, locomotor, batteries;
    };


    modelsFile.open("pieParts.txt");  // reopen file
    if(!modelsFile)
    {
        cout << "ERROR: Failed to open file " << endl;
        exit(EXIT_FAILURE);
    }

    while (getline(modelsFile, line)) // counts the number of model in file
    {
        if(line == "#")
            counter++;
    }
    modelsFile.close();



    modelsFile.open("pieParts.txt");  // reopen file
    if(!modelsFile)
    {
        cout << "ERROR: Failed to open file " << endl;
        exit(EXIT_FAILURE);
    }

    models *mdl = new models[counter];                        // stores the model
    counter = 0;

    while (getline(modelsFile, line))            // read data from the file -> Parts_Program_File.txt
    {
      if(line == "#")
        continue;
      else
      {

        int i = 0;
        mdl[counter].modelName = line;

        getline(modelsFile, line);
        mdl[counter].rightArm = line;
        mdl[counter].chartNames[i] = mdl[counter].rightArm;

        getline(modelsFile, line);
        mdl[counter].rightArmCost = atof(line.c_str());
        mdl[counter].chartCost[i] = mdl[counter].rightArmCost;
        i++;

        getline(modelsFile, line);
        mdl[counter].leftArm = line;
        mdl[counter].chartNames[i] = mdl[counter].leftArm;

        getline(modelsFile, line);
        mdl[counter].leftArmCost = atof(line.c_str());
        mdl[counter].chartCost[i] = mdl[counter].leftArmCost;
        i++;

        getline(modelsFile, line);
        mdl[counter].torso = line;
        mdl[counter].chartNames[i] = mdl[counter].torso;

        getline(modelsFile, line);
        mdl[counter].torsoCost = atof(line.c_str());
        mdl[counter].chartCost[i] = mdl[counter].torsoCost;
        i++;

        getline(modelsFile, line);
        mdl[counter].head = line;
        mdl[counter].chartNames[i] = mdl[counter].head;

        getline(modelsFile, line);
        mdl[counter].headCost = atof(line.c_str());
        mdl[counter].chartCost[i] = mdl[counter].headCost;
        i++;

        getline(modelsFile, line);
        mdl[counter].locomotor = line;
        mdl[counter].chartNames[i] = mdl[counter].locomotor;

        getline(modelsFile, line);
        mdl[counter].locomotorCost = atof(line.c_str());
        mdl[counter].chartCost[i] = mdl[counter].locomotorCost;
        i++;

        getline(modelsFile, line);
        mdl[counter].batteries = line;
        mdl[counter].chartNames[i] = mdl[counter].batteries;

        getline(modelsFile, line);
        mdl[counter].batteriesCost = atof(line.c_str());
        mdl[counter].chartCost[i] = mdl[counter].batteriesCost;
        counter++;
     }
  }


    int index = (intptr_t)p;
    index--;    // minus 1 to index appropriate chart in "mdl"

    Fl_Window *win = new Fl_Window(1000, 480);
    Fl_Chart  *chart = new Fl_Chart(20, 20, win->w()-40, win->h()-40, mdl[index].modelName.c_str());
    chart->type(FL_PIE_CHART);


    for(int i = 0; i < NUM_COMPONENTS; i++)
    {
        char temp[100];
        sprintf(temp, "%1.2f", mdl[index].chartCost[i]);
        mdl[index].chartNames[i] = mdl[index].chartNames[i] + ": $" + temp;    // catenate right operand and store it inside left operand
    }

    int t = 0;      // use to loop through robot cost
    chart->add(mdl[index].chartCost[t], mdl[index].chartNames[t].c_str(), FL_GREEN);   // add value, name and color to pie chart
    t++;
    chart->add(mdl[index].chartCost[t], mdl[index].chartNames[t].c_str(), FL_GREEN);   // add value, name and color to pie chart
    t++;
    chart->add(mdl[index].chartCost[t], mdl[index].chartNames[t].c_str(), FL_RED);
    t++;
    chart->add(mdl[index].chartCost[t], mdl[index].chartNames[t].c_str(), FL_YELLOW);
    t++;
    chart->add(mdl[index].chartCost[t], mdl[index].chartNames[t].c_str(), FL_MAGENTA);
    t++;
    chart->add(mdl[index].chartCost[t], mdl[index].chartNames[t].c_str(), FL_BLUE);
    t++;

    win->resizable(win);
    win->show();
    Fl::run();
    modelsFile.close();
    delete [] mdl;
    mdl = NULL;
}
/*-------------------------------------------------------SHOP CLASS-------------------------------------------------------*/
int main(/*int argc,char **argv*/)
{
  //gloArgc = argc;
  //gloArgv = argv;
  const char *lab1 = "Robbie Robot Shop";
  const char *lab2 = "Welcome to the Robbie Robot Shop!\n\nPlease select a user type";
  const char *lab3 = "Project Manager Menu";
  const char *lab4 = "Shop Manager Menu";
  const char *lab5 = "Sales Associate Menu";
  const char *lab6 = "Customer Menu";
  const char *lab7 = "View Documentation";
  const char *lab8 = "View Robot Catalogue";

  // instance objects to make widgets w/given params
  //MakeWin mainWin(1400,600,lab1);
  MakeWin mainWin(Fl::w(),Fl::h(),lab1);
  MakeBox mainBox(36,450,100,500,200,lab2);
  MakeButtons mainBut1(470,350,155,50,lab3);
  MakeButtons mainBut2(625,350,155,50,lab4);
  MakeButtons mainBut3(780,350,155,50,lab5);
  MakeButtons mainBut4(470,400,155,50,lab6);
  MakeButtons mainBut5(625,400,155,50,lab7);
  MakeButtons mainBut6(780,400,155,50,lab8);

  // gives widgets their properties
  mainWin.winProps();
  mainBox.boxProps();
  mainBut1.butProps(1);
  mainBut2.butProps(2);
  mainBut3.butProps(3);//PM
  mainBut4.butProps(4);//SM
  mainBut5.butProps(5);//SA
  mainBut6.butProps(6);

  //mainWin.end();
  mainWin.showWin();

  return(Fl::run());
}
