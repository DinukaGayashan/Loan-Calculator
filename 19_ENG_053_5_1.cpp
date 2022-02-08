/********************************************************************
Course		:	CO2210 Programming Quest
Quest No	:	05
Title		:	Bank Loan Payment Calculator
Author		:	Kasthuriarachchi K.A.D.G.
Index No	:	19/ENG/053
Date		:	25-10-2021
********************************************************************/

//including needed header files
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <conio.h>
#include <fstream>
#include <algorithm>

using namespace std;

//structure to handle loan data
struct Loan
{
	int type, min_age, max_age, repay_period;
	float needed_income, loan_amount, annual_interest;
	Loan(int ty = 0, int miage = 0, int mxage = 0, float in = 0, float mxlo = 0, int rep = 0, float intr = 0)
		:type(ty), min_age(miage), max_age(mxage), needed_income(in), loan_amount(mxlo), repay_period(rep), annual_interest(intr) {}
};

//class to handle customer data and functions
class Customer
{
private:
	//attributes of a customer
	string name;
	int age;
	float monthly_income;
	Loan personalized_loan;
public:

	/*---------------------------------------------------------------------------------
	Member Function		:	take_input
	Description         :	takes inputs of an customer and checks whether the
							customer is eligible for a loan
	Input Parameters    :	-
	Return              :	condition of the eligibillity for a loan
	---------------------------------------------------------------------------------*/
	bool take_input()
	{
		char title = '0';
		do
		{
			cout << "\nChoose your title : \n\t1.Mr\t2.Ms\t3.Mrs\t";
			title = _getch();
			if (title != '1' && title != '2' && title != '3')
				cerr << "\nError: Must enter a number from 1,2,3\n";
		} while (title != '1' && title != '2' && title != '3');
		
		cout << "\n\nEnter your name : ";
		getline(cin, name);
		
		if (title == '3')
			name = "Mrs " + name;
		else if (title == '2')
			name = "Ms " + name;
		else
			name = "Mr " + name;
		
		do
		{
			cout << "\nEnter your age : ";
			cin >> age;
			if (age < 1 || age > 200)
			{
				cerr << "Error: Must be aged between 1-200 yrs\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (age < 1 || age > 200);

		do
		{
			cout << "\nEnter your monthly income : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> monthly_income;
			if (monthly_income < 1)
			{
				cerr << "Error: Must be a positive income\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (monthly_income < 1);

		if (age < 18 || monthly_income < 45000)
			return false;
		return true;
	}

	/*---------------------------------------------------------------------------------
	Member Function		:	available_loans
	Description         :	checks for eligible loan schemes for a customer
	Input Parameters    :	loans - vector of all available loans
	Return              :	vector of loans the customer is eligible
	---------------------------------------------------------------------------------*/
	vector<Loan> available_loans(vector<Loan> &loans) const
	{
		vector<Loan> avail;
		for (int i = 0; i < int(loans.size()); i++)
			if (loans[i].min_age <= age && loans[i].max_age >= age && loans[i].needed_income <= monthly_income)
				avail.push_back(loans[i]);
		return avail;
	}

	/*---------------------------------------------------------------------------------
	Member Function		:	print_loans
	Description         :	prints a table of loans to the console
	Input Parameters    :	loans - vector of loans
	Return              :	-
	---------------------------------------------------------------------------------*/
	void print_loans(const vector<Loan>& loans)
	{
		int length = 120;
		cout << endl;
		for (int i = 0; i < length; i++)
			cout << "-";
		cout << "\n   Loan name     Customer's age    Monthly income    Max loan amount   Max repay period (months)  Annual interest rate\n";
		for (int i = 0; i < length; i++)
			cout << "-";
		cout << endl;
		for (int i = 0; i < int(loans.size()); i++)
		{
			cout << i + 1 << "  ";

			if (loans[i].type == 1) cout << "Vehicle         ";
			else if (loans[i].type == 2) cout << "Housing         ";
			else if (loans[i].type == 3) cout << "Education       ";
			else if (loans[i].type == 4) cout << "Senior Citizen  ";
			else cout << "Personal        ";

			cout << loans[i].min_age << " - " << loans[i].max_age << "\t";

			cout << setw(15) << fixed << setprecision(2) << loans[i].needed_income << "  \t";

			cout << setw(10) << loans[i].loan_amount << " ";

			cout << setw(20) << loans[i].repay_period << "  ";

			cout << setw(20) << loans[i].annual_interest;

			cout << endl;
		}
		for (int i = 0; i < length; i++)
			cout << "-";
		cout << endl;
	}

	/*---------------------------------------------------------------------------------
	Member Function		:	personalize_loan
	Description         :	sets the values of the perzonalized loan
	Input Parameters    :	choosen_loan - choosen loan scheme by the customer
	Return              :	-
	---------------------------------------------------------------------------------*/
	void personalize_loan(const Loan &choosen_loan)
	{
		personalized_loan = choosen_loan;
		
		cout << endl << endl;
		if (choosen_loan.type == 1) cout << "Vehicle";
		else if (choosen_loan.type == 2) cout << "Housing";
		else if (choosen_loan.type == 3) cout << "Education";
		else if (choosen_loan.type == 4) cout << "Senior Citizen";
		else cout << "Personal";
		cout << " loan choosen...\n";

		float amount;
		do
		{
			cout << "\nEnter the amount you wish to borrow : ";
			cin >> amount;
			if (amount > choosen_loan.loan_amount || amount < 1)
			{
				cerr << "Error: Must be a value that can be borrowed\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (amount > choosen_loan.loan_amount || amount < 1);
		personalized_loan.loan_amount = amount;

		int time;
		do
		{
			cout << "\nEnter the possible repay period (months) : ";
			cin >> time;
			if (time > choosen_loan.repay_period || time < 1)
			{
				cerr << "Error: Must be a time in the range\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (time > choosen_loan.repay_period || time < 1);
		personalized_loan.repay_period = time;
	}

	/*---------------------------------------------------------------------------------
	Member Function		:	calculate_loan
	Description         :	calculates monthly repaiment data (remaining loan amount,
							interest, repaid loan amount) for the selected period
	Input Parameters    :	-
	Return              :	2D vector containing monthly repaiment data for the period
	---------------------------------------------------------------------------------*/
	vector<vector<double>> calculate_loan()
	{
		int n = personalized_loan.repay_period;
		double IR = personalized_loan.annual_interest / 1200.0;
		double D = (pow((1 + IR), n) - 1) / (IR * pow((1 + IR), n));
		double total_monthly_payment = personalized_loan.loan_amount / D;

		vector<vector<double>> repay;
		repay.push_back({ personalized_loan.loan_amount, personalized_loan.loan_amount * IR, total_monthly_payment - personalized_loan.loan_amount * IR });
		for (int i = 1; i < personalized_loan.repay_period; i++)
		{
			double remain_payment = repay[i - 1][0] - repay[i - 1][2];
			repay.push_back({ remain_payment, remain_payment * IR, total_monthly_payment - remain_payment * IR });
		}
		return repay;
	}

	/*---------------------------------------------------------------------------------
	Member Function		:	save_data
	Description         :	saves needed customer details to a text file
	Input Parameters    :	choosen_loan - choosen loan scheme by the customer
							total_payment - total repayment customer should do
							calculated_values - vector containing  monthly repaiment data
	Return              :	-
	---------------------------------------------------------------------------------*/
	void save_data(Loan& choosen_loan, double &total_payment, vector<vector<double>> &calculated_values) const
	{
		ofstream file;
		string file_name = name;
		replace(file_name.begin(), file_name.end(), ' ', '_');
		file.open("Customer Details\\" + file_name + ".txt");

		file << "Customer Details\n----------------\n";
		file << "\nCustomer name : " << name << endl;
		file << "\nSelected loan : ";
		if (personalized_loan.type == 1) file << "Vehicle";
		else if (personalized_loan.type == 2) file << "Housing";
		else if (personalized_loan.type == 3) file << "Education";
		else if (personalized_loan.type == 4) file << "Senior Citizen";
		else file << "Personal";
		file << endl;
		file << "\nMaximum repay period allowed : " << choosen_loan.repay_period << endl;
		file << "\nAnnual interest rate : " << fixed << setprecision(2) << personalized_loan.annual_interest << endl;
		file << "\nRequested loan amount : " << personalized_loan.loan_amount << endl;
		file << "\nRequested repay period : " << personalized_loan.repay_period << " months" << endl;

		int length = 75;
		file << endl;
		for (int i = 0; i < length; i++)
			file << "-";
		file << endl;
		file << "  Month     Remaining loan amount     Interest       Repaid loan amount\n";
		for (int i = 0; i < length; i++)
			file << "-";
		file << endl;
		for (int i = 0; i<int(calculated_values.size()); i++)
			file << setw(5) << i + 1 << setw(21) << calculated_values[i][0] << setw(20) << calculated_values[i][1] << setw(20) << calculated_values[i][2] << endl;
		for (int i = 0; i < length; i++)
			file << "-";
		file << endl;

		file << "\nTotal amount of money to be repaid : " << total_payment << endl;

		file.close();
	}

	/*---------------------------------------------------------------------------------
	Member Function		:	display_and_save_loan_calculations
	Description         :	displays choosen loan calculations and saves them to a file
	Input Parameters    :	choosen_loan - choosen loan scheme by the customer
	Return              :	-
	---------------------------------------------------------------------------------*/
	void display_and_save_loan_calculations(Loan &choosen_loan)
	{
		vector<vector<double>> calculated_values = calculate_loan();

		cout << "\n\nLoan Calculations...\n\n";
		double total_payment = 0;
		for (int i = 0; i < int(calculated_values.size()); i++)
		{
			cout << "Repayment for month " << i + 1 << " : " << fixed << setprecision(2) << calculated_values[i][2] << endl;
			total_payment += calculated_values[i][1] + calculated_values[i][2];
		}
		cout << "\nTotal amount to pay : " << fixed << setprecision(2) << total_payment;
		cout << "\nTotal amount of interest : " << fixed << setprecision(2) << total_payment - personalized_loan.loan_amount;

		save_data(choosen_loan, total_payment, calculated_values);
	}
};

int main()
{
	//initializing default loan schemes and assigning them into an vector
	Loan vehicle_loan(1, 18, 55, 45000, 1000000.00, 60, 14);
	Loan housing_loan(2, 25, 55, 100000, 2500000.00, 60, 8);
	Loan education_loan(3, 25, 35, 45000, 1500000.00, 84, 6);
	Loan senior_citizen_loan(4, 61, 200, 35000, 500000.00, 60, 4.5);
	Loan personal_loan_1(5, 30, 55, 100000, 2000000.00, 60, 14.5);
	Loan personal_loan_2(5, 30, 55, 100000, 3000000.00, 84, 16.2);
	vector<Loan> loan_types = { vehicle_loan,housing_loan,education_loan,senior_citizen_loan,personal_loan_1,personal_loan_2 };

	//looping while exitting
	while (true)
	{
		//clearing the console and printing header
		system("CLS");
		cout << "Bank Loan Calculator\n--------------------\n";

		//creating a customer for the instant
		Customer c;

		//taking customer data and checking for the eligibility
		bool valid;
		valid = c.take_input();
		
		//if not eligible for any loan scheme displaying error and exitting from the instant
		if (!valid)
		{
			cerr << "\nSorry! You are not eligible for any loan scheme.\n\n";
			system("PAUSE");
			continue;
		}

		//checking for the available loans to the customer and printing
		vector<Loan> avail_loans = c.available_loans(loan_types);
		c.print_loans(avail_loans);

		//choosing a loan scheme from the eligible loans and personalizing it
		int num;
		do
		{
			cout << "\nEnter the number of the loan to choose : ";
			cin >> num;
			if (num > avail_loans.size() || num < 1)
			{
				cerr << "Error: Must enter an available loan scheme number\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (num > avail_loans.size() || num < 1);
		Loan choosen_loan = avail_loans[num - 1];
		c.personalize_loan(avail_loans[num - 1]);

		//calculating the needed details and displaying and saving
		c.display_and_save_loan_calculations(choosen_loan);

		//waiting at the end of the instant
		cout << "\n\n";
		system("PAUSE");
	}

	return 0;
}