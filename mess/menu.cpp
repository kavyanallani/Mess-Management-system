#include<bits/stdc++.h>
#include<ctime>
#include<string.h>
using namespace std;

int main() {
    int sec = 8; // No. of sections
    list<string> *morning = new list<string>[sec];
    morning[72-'A'].push_back("10:30");
    morning[72-'B'].push_back("10:40");
    morning[72-'C'].push_back("10:50");
    morning[72-'D'].push_back("11:00");
    morning[72-'E'].push_back("11:10");
    morning[72-'F'].push_back("11:20");
    morning[72-'G'].push_back("11:30");
    morning[72-'H'].push_back("11:40");

    list<string> *lunch = new list<string>[sec];
    lunch[72-'A'].push_back("12:30");
    lunch[72-'B'].push_back("12:40");
    lunch[72-'C'].push_back("12:50");
    lunch[72-'D'].push_back("13:00");
    lunch[72-'E'].push_back("13:10");
    lunch[72-'F'].push_back("13:20");
    lunch[72-'G'].push_back("13:30");
    lunch[72-'H'].push_back("13:40");

    list<string> *snacks = new list<string>[sec];
    snacks[72-'A'].push_back("16:30");
    snacks[72-'B'].push_back("16:40");
    snacks[72-'C'].push_back("16:50");
    snacks[72-'D'].push_back("17:00");
    snacks[72-'E'].push_back("17:10");
    snacks[72-'F'].push_back("17:20");
    snacks[72-'G'].push_back("17:30");
    snacks[72-'H'].push_back("17:40");

    list<string> *dinner = new list<string>[sec];
    dinner[72-'A'].push_back("20:30");
    dinner[72-'B'].push_back("20:40");
    dinner[72-'C'].push_back("20:50");
    dinner[72-'D'].push_back("21:00");
    dinner[72-'E'].push_back("21:10");
    dinner[72-'F'].push_back("21:20");
    dinner[72-'G'].push_back("21:30");
    dinner[72-'H'].push_back("21:40");

    char name[20];
    string items[100];
    char breakfast1[]="Idli", breakfast2[]="Dosa", breakfast3[]="Puri",
         breakfast4[]="Vada", breakfast5[]="Sandwich", breakfast6[]="Pongal",
         breakfast7[]="BoiledEggs";

    char lunch1[]="Chicken Biryani", lunch2[]="Veg Biryani",
         lunch3[]="Rice Meal", lunch4[]="Chapathi", lunch5[]="Mixed Vegetable Salad", lunch6[]="Soup";

    char snacks1[]="Samosa", snacks2[]="French fries",
         snacks3[]="Cutlet", snacks4[]="Panipuri", snacks5[]="Boiled Ground Nuts", snacks6[]="Bhel Puri";

    char dinner1[]="Fruit Salad", dinner2[]="Jeera Rice",
         dinner3[]="Fried rice", dinner4[]="Curd Rice", dinner5[]="Omelete";

    int pchoice=0,bchoice,bchoice1, quantity,cost=0;
    char gotostart;

    cout<<"Please Enter Your Name: ";
    cin.ignore();
    cin.getline(name, 30); // Fixed name input

    char SEC;
    cout<<"Please enter your section: ";
    cin>>SEC;

    time_t present = time(0);
    char* ct = ctime(&present);
    cout<<"present time is: " << ct << endl;

    time_t now = time(0);
    char* dt = ctime(&now);

    int i=0;
    char *c=strtok(dt," ");
    while(c!=NULL) {
        if(i==3) break;
        c=strtok(NULL," ");
        i++;
    }

    string str1="";
    i=0;
    while(c!=NULL) {
        str1=str1+c[i];
        i++;
        if(i==5) break;
    }

    if (str1.size() == 4)
        str1.replace(1, 1, "");
    if (str1.size() == 5)
        str1.replace(2,1,"");

    int time1 = stoi(str1);

    if(time1>=930 && time1<=1140) {
        cout<<"Hello "<<name <<"\n\nWhat would you like to order?\n\n";
        cout<<"1) Breakfast\n  Enter your choice as 1\n";
    } else if(time1>=1230 && time1<=1340) {
        cout<<"Hello "<<name<<"\n\nWhat would you like to order?\n\n";
        cout<<"2) Lunch\n  Enter your choice as 2\n";
    } else if(time1>=1630 && time1<=1740) {
        cout<<"Hello "<<name<<"\n\nWhat would you like to order?\n\n";
        cout<<"3) Snacks\n  Enter your choice as 3\n";
    } else if(time1>=2030 && time1<=2140) {
        cout<<"Hello "<<name<<"\n\nWhat would you like to order?\n\n";
        cout<<"4) Dinner\n  Enter your choice as 4\n";
    } else {
        cout<<"Sorry, the mess is currently closed.\n";
        return 0;
    }

    cout<<"\nPlease Enter your Choice: ";
    cin>>pchoice;

    string str2;
    if(pchoice==1) str2=string(morning[72-SEC].front());
    else if(pchoice==2) str2=string(lunch[72-SEC].front());
    else if(pchoice==3) str2=string(snacks[72-SEC].front());
    else if(pchoice==4) str2=string(dinner[72-SEC].front());

    if (str2.size() == 4) str2.replace(1, 1, "");
    if (str2.size() == 5) str2.replace(2, 1, "");

    int time2 = stoi(str2);
    int hourDiff = time2 / 100 - time1 / 100 - 1;
    int minDiff = time2 % 100 + (60 - time1 % 100);
    if (minDiff >= 60) {
        hourDiff++;
        minDiff = minDiff - 60;
    }

    cout << "\nTime left for break: " << hourDiff << " hour(s) and " << minDiff << " minute(s)\n";
    if (hourDiff == 0 && minDiff <= 15 && pchoice != 2) { // Fixed quick items for lunch
        cout << "\nSuggested Quick Items (ready-to-serve):\n";
        cout << "- Sandwich\n- Boiled Eggs\n- French Fries\n- Fruit Salad\n";
    } else if (hourDiff == 0 && minDiff <= 30 && pchoice != 2) {
        cout << "\nSuggested Fast-Prep Items:\n";
        cout << "- Dosa\n- Cutlet\n- Omelet\n- Bhel Puri\n";
    } else {
        cout << "\nFull menu available.\n";
    }

        int total = 0;
        int ind = 0;
        beginning:
        if(pchoice==1 ) {
            cout<<"1) "<<breakfast1<<"\n";
            cout<<"2) "<<breakfast2<<"\n";
            cout<<"3) "<<breakfast3<<"\n";
            cout<<"4) "<<breakfast4<<"\n";
            cout<<"5) "<<breakfast5<<"\n";
            cout<<"6) "<<breakfast6<<"\n";
            cout<<"7) "<<breakfast7<<"\n";
            cout<<"What would you like to have for Breakfast?:";
            cin>>bchoice;
            if(bchoice>=1 && bchoice<=7) {
                cout<<"1) Two per plate = Rs.20\n"<<"2) Three per plate = Rs.30\n"<<"3) Four per plate = Rs.40\n";
                cout<<"Choose Plate Size Please:";
                cin>>bchoice1;
                if(bchoice1>=1 && bchoice1<=3) {
                cout<<"Please Enter Quantity: ";
                cin>>quantity;
                switch(bchoice1) {
                    case 1: cost = 20*quantity; break;
                    case 2: cost = 30*quantity; break;
                    case 3: cost = 40*quantity; break;
                }
                total=total+cost;
                cost=total;
                switch (bchoice) {
                    case 1:
                        cout<<"    Given Order\n";
                        cout<<""<<quantity<<" "<<breakfast1<<"\n";
                        items[ind]=breakfast1;
                        break;
                    case 2:
                        cout<<"    Given Order\n";
                        cout<<""<<quantity<<" "<<breakfast2<<"\n";
                        items[ind]=breakfast2;
                        break;
                    case 3:
                        cout<<"    Given Order\n";
                        cout<<""<<quantity<<" "<<breakfast3<<"\n";
                        items[ind]=breakfast3;
                        break;
                    case 4:
                        cout<<"    Given Order\n";
                        cout<<""<<quantity<<" "<<breakfast4<<"\n";
                        items[ind]=breakfast4;
                        break;
                    case 5:
                        cout<<"    Given Order\n";
                        cout<<""<<quantity<<" "<<breakfast5<<"\n";
                        items[ind]=breakfast5;
                        break;
                    case 6:
                        cout<<"    Given Order\n";
                        cout<<""<<quantity<<" "<<breakfast6<<"\n";
                        items[ind]=breakfast6;
                        break;
                    case 7:
                        cout<<"    Given Order\n";
                        cout<<""<<quantity<<" "<<breakfast7<<"\n";
                        items[ind]=breakfast7;
                        break;
                }
                cout<<"Your Total Bill is: Rs."<<total<<"\nYou will receive your order in 30 Minutes\n";
                cout<<"Would you like to order anything else? Y / N:";
                cin>>gotostart;
                if(gotostart=='Y' || gotostart=='y') {
                    ind=ind+1;
                    goto beginning;
                }
                }
            }
        }
        else if(pchoice==2) {
            cout<<"1) "<<lunch1<<" Rs.220\n";
            cout<<"2) "<<lunch2<<" Rs.170\n";
            cout<<"3) "<<lunch3<<" Rs.120\n";
            cout<<"4) "<<lunch4<<" Rs.80\n";
            cout<<"5) "<<lunch5<<" Rs.70\n";
            cout<<"6) "<<lunch6<<" Rs.60\n";
            cout<<"What would you like to have for Lunch?:";
            cin>>bchoice1;
            if(bchoice1>=1 && bchoice1<=6) {
                cout<<"Please Enter Quantity: ";
                cin>>quantity;
                int prices[] = {220, 170, 120, 80, 70, 60};
                cost = prices[bchoice1-1] * quantity;
                total += cost;
                char* lunchItems[] = {lunch1, lunch2, lunch3, lunch4, lunch5, lunch6};
                cout<<"    Given Order: "<<quantity<<" "<<lunchItems[bchoice1-1]<<"\n";
                items[ind]=lunchItems[bchoice1-1];
                cout<<"Your Total Bill is: Rs."<<total<<"\nYou will receive your order in 30 Minutes\n";
                cout<<"Would you like to order anything else? Y / N:";
                cin>>gotostart;
                if(gotostart=='Y' || gotostart=='y') {
                    ind++;
                    goto beginning;
                }
            }
        }
        else if(pchoice==3) {
            cout<<"1) "<<snacks1<<" Rs.40\n";
            cout<<"2) "<<snacks2<<" Rs.40\n";
            cout<<"3) "<<snacks3<<" Rs.40\n";
            cout<<"4) "<<snacks4<<" Rs.40\n";
            cout<<"5) "<<snacks5<<" Rs.20\n";
            cout<<"6) "<<snacks6<<" Rs.40\n";
            cout<<"What would you like to have for Snacks:";
            cin>>bchoice1;
            if(bchoice1>=1 && bchoice1<=6) {
                cout<<"Please Enter Quantity: ";
                cin>>quantity;
                int prices[] = {40, 40, 40, 40, 20, 40};
                cost = prices[bchoice1-1] * quantity;
                total += cost;
                char* snacksItems[] = {snacks1, snacks2, snacks3, snacks4, snacks5, snacks6};
                cout<<"    Given Order: "<<quantity<<" "<<snacksItems[bchoice1-1]<<"\n";
                items[ind]=snacksItems[bchoice1-1];
                cout<<"Your Total Bill is: Rs."<<total<<"\nYou will receive your order in 30 Minutes\n";
                cout<<"Would you like to order anything else? Y / N:";
                cin>>gotostart;
                if(gotostart=='Y' || gotostart=='y') {
                    ind++;
                    goto beginning;
                }
            }
        }
        else if(pchoice==4) {
            cout<<"1) "<<dinner1<<" Rs.65\n";
            cout<<"2) "<<dinner2<<" Rs.60\n";
            cout<<"3) "<<dinner3<<" Rs.40\n";
            cout<<"4) "<<dinner4<<" Rs.30\n";
            cout<<"5) "<<dinner5<<" Rs.40\n";
            cout<<"What would you like to have for Dinner?: ";
            cin>>bchoice1;
            if(bchoice1>=1 && bchoice1<=5) {
                cout<<"Please Enter Quantity: ";
                cin>>quantity;
                int prices[] = {65, 60, 40, 30, 40};
                char* dinnerItems[] = {dinner1, dinner2, dinner3, dinner4, dinner5};
                cost = prices[bchoice1-1] * quantity;
                total += cost;
                cout<<"    Given Order: "<<quantity<<" "<<dinnerItems[bchoice1-1]<<"\n";
                items[ind]=dinnerItems[bchoice1-1];
                cout<<"Your Total Bill is: Rs."<<total<<"\nYou will receive your order in 30 Minutes\n";
                cout<<"Would you like to order anything else? Y / N:";
                cin>>gotostart;
                if(gotostart=='Y' || gotostart=='y') {
                    ind++;
                    goto beginning;
                }
            }
        }

    if( hourDiff>=1 && minDiff<=30 ) {
        cout<<"\n your order cannot be taken ";
    } 

        cout << "\nSelect Payment Method:\n";
        cout << "1. UPI\n2. Card\n3. Cash\n";
        int paymentChoice;
        cin >> paymentChoice;
        switch (paymentChoice) {
            case 1: cout << "Processing UPI Payment...\nUPI Payment Successful!\n"; break;
            case 2: cout << "Processing Card Payment...\nCard Payment Successful!\n"; break;
            case 3: cout << "Please pay cash at the counter.\n"; break;
            default: cout << "Invalid choice. Defaulting to cash payment.\n"; break;
        }

        if(gotostart=='n' || gotostart=='N') {
            cout<<"\n List of ordered items are: ";
            for(int j=0;j<=ind;j++) {
                cout<<"\n"<<items[j];
            }
        }
        return 0;
    }