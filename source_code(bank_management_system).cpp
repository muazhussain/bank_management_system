//******************************//
/*    Bank Management System   */
//*****************************//

#include<bits/stdc++.h>
using namespace std;

// Class used in project

class user_account{
    private:
        string user_name;
        int account_no{};
        int deposit_amount{};
        char account_type;
        
    public:
        void create_account(); // Function for creating new account
        void show_info(); // Function for showing data of an account
        void modify_account(); // Function for modifying user account
        void deposit(int); // Function for accept amount and add to balance
        void withdraw(int); // Function for accept amount and subtract from balance
        void report_account(); // Function for show data in tabular format
        int show_account_no(); // Function for showing account no.
        int show_balance(); // Function for showing account balance
        char show_type(); // Fuaction for showing account type
    }; // Class ends here
    
    
// Function declaration //

void write_account(); // Function to write record in binary file
void display_info(int); // Function to display account details given by user
void modify_info(int); // Function to modify record of the file
void delete_account(int); // Function to delete record of the file
void display_all(); // Function to display all account info
void deposit_withdraw(int, int); 

    
int main(){
    cout << "\n\n\t\t Welcome To Easy Banking System" << endl << endl << endl;
    int acc_num{};
    bool proceed = true;
    do{
        cout << "\t\t MAIN MENU:: " << endl << endl << endl;
        cout << "\t\t 1. Create Account" << endl << endl;
        cout << "\t\t 2. Modify Account" << endl << endl;
        cout << "\t\t 3. Close Account" << endl << endl;
        cout << "\t\t 4. Deposit Money" << endl << endl;
        cout << "\t\t 5. Withdraw Money" << endl << endl;
        cout << "\t\t 6. Balance Enquiry" << endl << endl;
        cout << "\t\t 7. All Account Holder List" << endl << endl;
        cout << "\t\t 8. Exit" << endl << endl;
        
        cout << "Select Your Option(1-8): ";
        int option_no{};
        cin >> option_no;
        while(option_no < 0 || option_no > 8){
            cout << "Invalid Input. \nPress Right Option: ";
            cin >> option_no;
        }
        switch(option_no){
            case 1:
                write_account();
                break;
            case 2:
                cout << "Enter The Account No. : ";
                cin >> acc_num;
                modify_info(acc_num);
                break;
            case 3:
                cout << "Enter The Account No. : ";
                cin >> acc_num;
                delete_account(acc_num);
                break;
             case 4:
                cout << "Enter The Account No. : ";
                cin >> acc_num;
                deposit_withdraw(acc_num, 1);
                break;
            case 5:
                cout << "Enter The Account No. : ";
                cin >> acc_num;
                deposit_withdraw(acc_num, 2);
                break;
            case 6:
                cout << "Enter The Account No. : ";
                cin >> acc_num;
                display_info(acc_num);
                break;
            case 7:
                display_all();
                break;
            case 8:
                cout << "Thanks For Using Our Banking System." << endl << endl;
                proceed = false;
                break;
        }
    }while(proceed == true);
    
    return 0;
}

// Functions decleared in class //

void user_account :: create_account(){
   cout << "Account No. : ";
    cin >> account_no;
    cout << "Account Holder Name: ";
    cin.ignore();
    getline(cin, user_name);
    cout << "Account Type(C/S): ";
    cin >> account_type;
    cout << "Initial deposit amount: ";
    cin >> deposit_amount;
    account_type = toupper(account_type);
    cout << "\n\nNew Account Created..." << endl;
}

void user_account :: show_info(){
    cout << "Your Account No. : " << account_no << endl;
    cout << "Account Holder Name: " << user_name << endl;
    cout << "Account Type(C/S): " << account_type << endl;
    cout << "Current Balance: " << deposit_amount << endl;
}

void user_account :: modify_account(){
    cout << "Your Account No. : " << account_no << endl;
    cout << "Account Holder Name: ";
    cin.ignore();
    getline(cin, user_name);
    cout << "Account Type(C/S): ";
    cin >> account_type;
    cout << "Initial deposit amount: ";
    cin >> deposit_amount;
    account_type = toupper(account_type);
    cout << "New Information Stored..." << endl;
}

void user_account :: deposit(int x){
    deposit_amount += x;
}

void user_account :: withdraw(int x){
    deposit_amount -= x;
}

void user_account :: report_account(){
    cout << account_no << setw(10) << "  " << user_name << setw(10) << "  " << account_type << setw(6) << "  " << deposit_amount << endl;
}

int user_account :: show_account_no(){
    return account_no;
}

int user_account :: show_balance(){
    return deposit_amount;
}

char user_account :: show_type(){
    return account_type;
}

// Ends here //


// Global functions //

void write_account(){
    user_account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(user_account));
	outFile.close();
}

void display_info(int n){
    user_account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !!";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(user_account)))
	{
		if(ac.show_account_no() == n)
		{
			ac.show_info();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

void modify_info(int n){
    bool found=false;
	user_account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !!";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(user_account));
		if(ac.show_account_no()==n)
		{
			ac.show_info();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify_account();
			int pos=(-1)*static_cast<int>(sizeof(user_account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(user_account));
			cout<<"\n\n\t Record Updated...";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found... ";
}

void delete_account(int n){
    user_account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !!";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(user_account)))
	{
		if(ac.show_account_no()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(user_account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all(){
    user_account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !!";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(user_account)))
	{
		ac.report_account();
	}
	inFile.close();
}

void deposit_withdraw(int n, int choice){
    int amount;
	bool found=false;
	user_account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !!";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(user_account));
		if(ac.show_account_no()==n)
		{
			ac.show_info();
			if(choice == 1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amount;
				ac.deposit(amount);
			}
			if(choice == 2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amount;
				int bal=ac.show_balance()-amount;
				if((bal<500 && ac.show_type()=='S') || (bal<1000 && ac.show_type()=='C'))
					cout<<"Insufficience balance";
				else
					ac.withdraw(amount);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(user_account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
