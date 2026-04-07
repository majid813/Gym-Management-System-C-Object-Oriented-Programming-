#include<iostream>
#include<fstream>
#include <sstream>
#include<ctime>
#include <iomanip>
using namespace std;
int check=0;

class Member{
	protected:
		static int memberNumber;
		char memberName[20];
		char memberAge[20];
		char gender[20];
		char contactNumber[20];
		public:
		Member()
		{
		 memberName[0]='\0';
		 memberAge[0]='\0';
		 gender[0]='\0';
		 contactNumber[0]='\0';
		}
		char* getMemberName()
		{
			return memberName;
		}
		char* getMemberAge()
		{
			return memberAge;
		}
		char* getGender()
		{
			return gender;
		}
		char* getContact()
		{
			return contactNumber;
		}
	static int generateUniqueMemberNumber()
	{
	 		
		return memberNumber++;
	}
 void addMember() {
    ofstream memberFile;
    memberFile.open("MemberInfo.txt", ios::app);  // Open file in append mode
    
     generateUniqueMemberNumber();
     start:
    cout << "Enter Member Name: ";
    cin.ignore();
    cin.getline(memberName,19);
    try {
        for (int i = 0; memberName[i] != '\0'; i++) {
            if (isdigit(memberName[i])) {
                throw "Wrong input! You should Enter Character for Name.\n";
            }
        }
    } catch (const char* arr) {
        cout << arr;
        goto start;
    }
    start2:
    cout << "Enter Member Age: ";
   // cin.ignore();
    cin.getline(memberAge,19);
    try{
    	for(int i=0;memberAge[i] !='\0';i++)
    	{
    		if(!isdigit(memberAge[i]))
    		{
    			throw"Wrong Input!. You Should enter the Number\n";
			}
		}
	}
	catch(const char*err)
	{
		cout<<err;
		goto start2;
	}
	start3:
    cout << "Enter Member Gender: ";
    cin.ignore();
    cin.getline(gender,19);
    try{
    	for(int i=0;gender[i] !='\0';i++)
    	if(isdigit(gender[i]))
    	{
    		throw" Wrong Input!.You should entered the character for gender\n";
		}
	}
	catch(const char* arr1)
	{
		cout<<arr1;
		goto start3;
	}
    start4:
    cout << "Enter member contact number: ";
    cin.ignore();
    cin.getline(contactNumber,19);
    try{
    	for(int i=0;contactNumber[i] !='\0';i++)
    	{
    		if(!isdigit(contactNumber[i]))
    		{
    			throw"Wrong Input! You have to input Contact Number in Numeric Values.\n";
			}
		}
	}
	catch(const char* err1)
	{
		cout<<err1;
		goto start4;
	}
    // Add code to get and store the joining date
    time_t now = time(0);
    tm* currentDate = localtime(&now);
    char joiningDate[11];
    strftime(joiningDate, sizeof(joiningDate), "%d-%m-%Y", currentDate);

    // Append the joining date to the file
    memberFile << memberNumber << memberName << " " << memberAge << " " << gender << " " << " " << contactNumber << " " << joiningDate << endl;
    
    cout << "Member added successfully!\n";
    memberFile.close();  // Close the file
}

void selectPlanAndSave() {
    int selectedPlan;
    cout << "Select a plan (1 for Gold, 2 for Silver, 3 for Bronze): ";

    string planName;
    double planPrice;
    // Bronze Plan
    cout << "Bronze Plan:\n";
    cout << "Description: Basic access with limited features.\n";
    cout << "Monthly Fee: $10.0\n";
    cout << "Benefits:\n";
    cout << "- Limited access to gym facilities.\n";
    cout << "- Basic assistance from trainers.\n\n";

    // Silver Plan
    cout << "Silver Plan:\n";
    cout << "Description: Mid-tier plan with more features.\n";
    cout << "Monthly Fee: $25.0\n";
    cout << "Benefits:\n";
    cout << "- Unlimited access to gym facilities.\n";
    cout << "- Trainer assistance available.\n";
    cout << "- Customized Diet Plan.\n\n";

    // Gold Plan
    cout << "Gold Plan:\n";
    cout << "Description: Premium plan with exclusive features.\n";
    cout << "Monthly Fee: $50.0\n";
    cout << "Benefits:\n";
    cout << "- Unlimited access to gym facilities.\n";
    cout << "- Personal trainer assigned.\n";
    cout << "- Customized Diet Plan.\n";
    cout << "- Flexible time slots for workouts.\n";
        cin >> selectedPlan;


    switch (selectedPlan) {
        case 1:
            planName = "Gold";
            planPrice = 50.0;
            break;
        case 2:
            planName = "Silver";
            planPrice = 25.0;
            break;
        case 3:
            planName = "Bronze";
            planPrice = 10.0;
            break;
        default:
            cout << "Invalid plan choice.\n";
            return;
    }
      if (selectedPlan == 1 || selectedPlan == 2) {
        assignTrainerToGoldMember();
        assignTrainerToSilverMember();
    }

    // Open the file in append mode
    ofstream memberFile("MemberInfo.txt", ios::app);

    // Append the plan details to the file
    memberFile << "Plan: " << planName << "\tPrice: $" << planPrice << endl;

    cout << "Plan selected successfully!\n";
    memberFile.close();  // Close the file
}

void checkAndProvideDiscount() {
    ifstream memberFile("MemberInfo.txt");
    ofstream tempFile("temp.txt");

    string line;
    char searchID[20];

    start:
    cout << "Enter the  member ID of  member to check for a discount: ";
    cin.ignore();
    cin.getline(searchID,19);
    try{
    	for(int i=0;searchID[i] !='\0';i++)
    	{
    		if(!isdigit(searchID[i]))
    		{
    			throw"Wrong Input! You have to input Member ID in Numeric Values.\n";
			}
		}
	}
	catch(const char* err1)
	{
		cout<<err1;
		goto start;
	}
    bool found = false;

    while (getline(memberFile, line)) {
        // Find the position of the contact number in the line
        size_t pos = line.find(searchID);

        if (pos != string::npos) {
            // Display current member details
            cout << "Current details for member with memberID " << searchID << ":\n";
            cout << line << endl;

            // Extract the date joined information
            string dateJoined;
            stringstream ss(line);
            ss >> memberNumber >> memberName >> memberAge >> gender >> contactNumber >> dateJoined;

            // Convert dateJoined string to a time structure for comparison
            tm tmDateJoined = {0};
            istringstream dateStream(dateJoined);
            char dash; // to consume the dash between day-month-year
            dateStream >> tmDateJoined.tm_mday >> dash >> tmDateJoined.tm_mon >> dash >> tmDateJoined.tm_year;

            // Adjust month since tm_mon is 0-based
            tmDateJoined.tm_mon--;

            // Check if the date parsing was successful
            if (dateStream.fail()) {
                cerr << "Error parsing date: " << dateJoined << endl;
                // Handle the error as needed
            }

            // Get current time
            time_t currentTime;
            time(&currentTime);
            struct tm* tmCurrentTime = localtime(&currentTime);

            // Calculate the difference in years
            int yearsDifference = tmCurrentTime->tm_year - tmDateJoined.tm_year;

            // Check if the member has been with the gym for more than 5 years
            if (yearsDifference >= 5) {
                // Provide a discount (you can adjust this logic as needed)
                cout << "Congratulations! You qualify for a discount.\n";
            } else {
                cout << "Sorry, you don't qualify for a discount at this time.\n";
            }

            found = true;
        } else {
            tempFile << line << endl;  // Copy the line to temp file as it is
        }
    }

    if (!found) {
        cout << "Member with member number " << searchID << " not found.\n";
    }

    memberFile.close();
    tempFile.close();

    // Rename the temp file to the original file
    remove("MemberInfo.txt");
    rename("temp.txt", "MemberInfo.txt");
}

    void modifyMemberDetails() {
    ifstream memberFile("MemberInfo.txt");
    ofstream tempFile("temp.txt");

    string line;
    char searchID[20];
     
     start:
    cout << "Enter the member ID to modify member details: ";
    cin.ignore();
    cin.getline(searchID,19);
    try{
    	for(int i=0;searchID[i] !='\0';i++)
    	{
    		if(!isdigit(searchID[i]))
    		{
    			throw"Wrong Input! You have to input Member ID in Numeric Values.\n";
			}
		}
	}
	catch(const char* err1)
	{
		cout<<err1;
		goto start;
	}
    bool found = false;

    while (getline(memberFile, line)) {
        // Find the position of the contact number in the line
        size_t pos = line.find(searchID);

        if (pos != string::npos) {
        	char option;
cout << "What do you want to modify? ";
cout << "1. Modify Name:" << endl;
cout << "2. Modify Age:" << endl;
cout << "3. Modify Contact:" << endl;
cout << "4. Modify Gender:" << endl;
cin>>option;

switch (option) {
    case '1':
        cout << "Enter Member Name: ";
        cin>>memberName;
        break;
    case '2':
        cout << "Enter Member Age: ";
        cin>>memberAge;
        break;
    case '3':
        cout << "Enter Member Contact: ";
        cin>>contactNumber;
        break;
    case '4':
        cout << "Enter Member Gender: ";
        cin>>gender;
        break;
    default:
        cout << "Invalid" << endl;
        break;
}
            
            tempFile << memberNumber << memberName << " " << memberAge << " " << gender << " " << searchID << endl;
            cout << "Member details modified successfully!\n";
            found = true;
        } else {
            tempFile << line << endl;  // Copy the line to temp file as it is
        }
    }

    if (!found) {
        cout << "Member with id number " << searchID << " not found.\n";
    }

    memberFile.close();
    tempFile.close();

    // Rename the temp file to the original file
    remove("MemberInfo.txt");
    rename("temp.txt", "MemberInfo.txt");
}
	void deleteMember() {
    ifstream memberFile("MemberInfo.txt");
    ofstream tempFile("temp.txt");

    string line;

  char searchID[20];
     
    start:
    cout << "Enter the member ID to Delete member details: ";
    cin.ignore();
    cin.getline(searchID,19);
    try{
    	for(int i=0;searchID[i] !='\0';i++)
    	{
    		if(!isdigit(searchID[i]))
    		{
    			throw"Wrong Input! You have to input Member ID in Numeric Values.\n";
			}
		}
	}
	catch(const char* err1)
	{
		cout<<err1;
		goto start;
	}

    bool found = false;

    while (getline(memberFile, line)) {
        // Find the position of the contact number in the line
        size_t pos = line.find(searchID);

        if (pos != string::npos) {
            // Member found, skip this line to exclude it from temp file
            cout << "Member with id number " << searchID << " deleted successfully!\n";
            found = true;
        } else {
            tempFile << line << endl;  // Copy the line to temp file as it is
        }
    }

    if (!found) {
        cout << "Member with id number " << searchID << " not found.\n";
    }

    memberFile.close();
    tempFile.close();

    // Rename the temp file to the original file
    remove("MemberInfo.txt");
    rename("temp.txt", "MemberInfo.txt");
}
	void cancelMemberPlan() {
    ifstream memberFile("MemberInfo.txt");
    ofstream tempFile("temp.txt");

     string line;
     char searchID[20];
     
    start:
    cout << "Enter the member ID to Cancel member details: ";
    cin.ignore();
    cin.getline(searchID,19);
    try{
    	for(int i=0;searchID[i] !='\0';i++)
    	{
    		if(!isdigit(searchID[i]))
    		{
    			throw"Wrong Input! You have to input Member ID in Numeric Values.\n";
			}
		}
	}
	catch(const char* err1)
	{
		cout<<err1;
		goto start;
	}

    bool found = false;

    while (getline(memberFile, line)) {
        // Find the position of the contact number in the line
        size_t pos = line.find(searchID);

        if (pos != string::npos) {
            // Display current plan details
            cout << "Current plan details for member with member number " << searchID << ":\n";
            cout << line << endl;

            // Ask if the member wants to cancel the plan
            char cancelChoice;
            cout << "Do you want to cancel the plan? (y/n): ";
            cin >> cancelChoice;

            if (cancelChoice == 'y' || cancelChoice == 'Y') {
                // Update the line with plan cancellation
                tempFile << memberNumber << memberName << " " << memberAge << " " << gender << " " << searchID << " PlanCanceled\n";
                cout << "Member plan canceled successfully!\n";
            } else {
                // Keep the original line if the plan is not canceled
                tempFile << line << endl;
                cout << "Member plan not canceled.\n";
            }

            found = true;
        } else {
            tempFile << line << endl;  // Copy the line to temp file as it is
        }
    }

    if (!found) {
        cout << "Member with ID number " << searchID << " not found.\n";
    }

    memberFile.close();
    tempFile.close();

    // Rename the temp file to the original file
    remove("MemberInfo.txt");
    rename("temp.txt", "MemberInfo.txt");
}

void giveReview() {
    ifstream memberFile("MemberInfo.txt");
    ofstream tempFile("temp.txt");

    string line;
  char searchID[20];
     
     start:
    cout << "Enter the member ID to give review member details: ";
    cin.ignore();
    cin.getline(searchID,19);
    try{
    	for(int i=0;searchID[i] !='\0';i++)
    	{
    		if(!isdigit(searchID[i]))
    		{
    			throw"Wrong Input! You have to input Member ID in Numeric Values.\n";
			}
		}
	}
	catch(const char* err1)
	{
		cout<<err1;
		goto start;
	}
    bool found = false;

    while (getline(memberFile, line)) {
        // Find the position of the contact number in the line
        size_t pos = line.find(searchID);

        if (pos != string::npos) {
            // Display current member details
            cout << "Your current details:\n";
            cout << line << endl;

            // Ask for the review
            string review;
            cout << "Enter your review: ";
            cin.ignore();  // Ignore the newline character left in the stream
            getline(cin, review);

            // Update the line with the review
            tempFile << memberNumber << memberName << " " << memberAge << " " << gender << " " << searchID << " " << review << endl;
            cout << "Review submitted successfully!\n";

            found = true;
        } else {
            tempFile << line << endl;  // Copy the line to temp file as it is
        }
    }

    if (!found) {
        cout << "Member with ID number " << searchID << " not found.\n";
    }

    memberFile.close();
    tempFile.close();

    // Rename the temp file to the original file
    remove("MemberInfo.txt");
    rename("temp.txt", "MemberInfo.txt");
}	
			
		void assignTrainerToGoldMember() {
        ifstream memberFile("MemberInfo.txt");
        ofstream tempFile("temp.txt");

        string line;
        char searchID[20];
        start:
        cout<<"Enter the member number of gold member to assign the trainer:"<<endl;
        cin.ignore();
        cin.getline(searchID,19);
        try{
    	for(int i=0;searchID[i] !='\0';i++)
    	{
    		if(!isdigit(searchID[i]))
    		{
    			throw"Wrong Input! You have to input Member ID in Numeric Values.\n";
			}
		}
	}
	catch(const char* err1)
	{
		cout<<err1;
		goto start;
	};

        bool found = false;

        while (getline(memberFile, line)) {
            // Find the position of the contact number in the line
            size_t pos = line.find(searchID);

            if (pos != string::npos) {
                // Display current member details
                cout << "Current details for Gold member with member number " << searchID << ":\n";
                cout << line << endl;

                // Assign a trainer (you can replace this with your actual trainer assignment logic)
                cout << "Trainer assigned to Gold member successfully!\n";
                tempFile << line << " GoldTrainerAssigned\n";

                found = true;
            } else {
                tempFile << line << endl;  // Copy the line to temp file as it is
            }
        }

        if (!found) {
            cout << "Gold member with member number " << searchID << " not found.\n";
        }

        memberFile.close();
        tempFile.close();

        // Rename the temp file to the original file
        remove("MemberInfo.txt");
        rename("temp.txt", "MemberInfo.txt");
    }
    
    
    void assignTrainerToSilverMember() {
        ifstream memberFile("MemberInfo.txt");
        ofstream tempFile("temp.txt");

        string line;
        char searchID[20];
        
        start:
        cout << "Enter the member number of the Silver member to assign a trainer: ";
        cin.ignore();
    cin.getline(searchID,19);
    try{
    	for(int i=0;searchID[i] !='\0';i++)
    	{
    		if(!isdigit(searchID[i]))
    		{
    			throw"Wrong Input! You have to input Member ID in Numeric Values.\n";
			}
		}
	}
	catch(const char* err1)
	{
		cout<<err1;
		goto start;
	}

        bool found = false;

        while (getline(memberFile, line)) {
            // Find the position of the contact number in the line
            size_t pos = line.find(searchID);

            if (pos != string::npos) {
                // Display current member details
                cout << "Current details for Silver member with member number " << searchID << ":\n";
                cout << line << endl;

                // Assign a trainer (you can replace this with your actual trainer assignment logic)
                cout << "Trainer assigned to Silver member successfully!\n";
                tempFile << line << " SilverTrainerAssigned\n";

                found = true;
            } else {
                tempFile << line << endl;  // Copy the line to temp file as it is
            }
        }

        if (!found) {
            cout << "Silver member with member number " << searchID << " not found.\n";
        }

        memberFile.close();
        tempFile.close();

        // Rename the temp file to the original file
        remove("MemberInfo.txt");
        rename("temp.txt", "MemberInfo.txt");
    }	
void display()	
{
	ifstream memberFile("MemberInfo.txt");

    if (!memberFile.is_open()) {
        cout << "Unable to open file. No member data available.\n";
        return;
    }

    cout << "******** Member Information ********\n";
    cout << "ID\t\tName\t\tAge\t\tGender\t\tContact\n";

    string line;
    while (getline(memberFile, line)) {
        stringstream ss(line);
        ss >>memberNumber>> memberName >> memberAge >> gender >> contactNumber;

        // Display member details
        cout <<memberNumber<<"\t\t"<< memberName << "\t\t" << memberAge << "\t\t" << gender << "\t\t" <<contactNumber<< "\n";
    }

    memberFile.close();
}
};

int Member::memberNumber=0;

class Admin:public Member{
	protected:
		char name[20];
		char pass[20];
		public:
			Admin()
			{
				name[0]='\0';
				pass[0]='\0';
			}
			char* getName()
			{
				return name;
			}
			char* getPassword()
			{
				return pass;
			}
		void adLogin()
	{
		start:           
		cout << "\t\t\t\t\t\t";
		cout << "ENTER THE ADMIN Name : " << endl;
		cout << "\t\t\t\t\t\t";
		cin.ignore();
        cin.getline(name,19);
        try {
        for (int i = 0; name[i] != '\0'; i++) {
            if (isdigit(name[i])) {
                throw "Wrong input! You should Enter Character for Name.\n";
            }
        }
      } catch (const char* arr) {
        cout << arr;
        goto start;
    }
        start1:
		cout << "\t\t\t\t\t\t";
		cout << "ENTER Your Password: " << endl;
		cout << "\t\t\t\t\t\t";
		cin.ignore();
        cin.getline(pass,19);
    try {
             for (int i = 0; pass[i] != '\0'; i++) {
            if (isdigit(pass[i])) {
                throw "Wrong input! You should Enter Character for Passwrord.\n";
            }
        }
    } catch (const char* arr) {
        cout << arr;
        goto start1;
    }
	}
		void checkAdmininfo()
	{
		ifstream obj1;
		obj1.open("AdminInfo.txt",ios::in);
		string adname;
		string adpassword;
		string temp_str;
		while(!obj1.eof())
		{
			obj1>>adname;
			obj1>>adpassword;
			if(adname.compare(name) == 0 && adpassword.compare(pass) == 0)
			{
				temp_str=adpassword;
				check=1;
				break;
			}
		}
		if(check==0)
		{
		  cout<<"You have Entered the Wrong information :)"<<endl;	
		}
	   obj1.close();
	}
	
	void memberPlans(){
    cout << "******** Membership Plans ********\n\n";

    // Bronze Plan
    cout << "Bronze Plan:\n";
    cout << "Description: Basic access with limited features.\n";
    cout << "Monthly Fee: $10.0\n";
    cout << "Benefits:\n";
    cout << "- Limited access to gym facilities.\n";
    cout << "- Basic assistance from trainers.\n\n";

    // Silver Plan
    cout << "Silver Plan:\n";
    cout << "Description: Mid-tier plan with more features.\n";
    cout << "Monthly Fee: $25.0\n";
    cout << "Benefits:\n";
    cout << "- Unlimited access to gym facilities.\n";
    cout << "- Trainer assistance available.\n";
    cout << "- Customized Diet Plan.\n\n";

    // Gold Plan
    cout << "Gold Plan:\n";
    cout << "Description: Premium plan with exclusive features.\n";
    cout << "Monthly Fee: $50.0\n";
    cout << "Benefits:\n";
    cout << "- Unlimited access to gym facilities.\n";
    cout << "- Personal trainer assigned.\n";
    cout << "- Customized Diet Plan.\n";
    cout << "- Flexible time slots for workouts.\n";
}	
	   int menu(){
    	int op;
                    cout << "\n******** Menu ********\n";
                    cout << "1. Add Member\n";
                    cout << "2. Select Plans\n";
                    cout << "3. Modify Member Details\n";
                    cout << "4. Delete Member\n";
                    cout << "5. Cancel Member Plan\n";
                    cout << "6. Give Review\n";
                    cout << "8. Check and Provide Discount\n";
                    cout << "7. To Display\n";
                    cout << "8  To Exit: ";
					cin>>op;
                 	return op;
					 
				
			}	
};
class Trainer{
	protected:
		Admin obj;
	public:
		string generateDietPlanBasedOnExperience(const string& experience) {
        // Replace this with your actual logic to generate a diet plan based on experience
        if (experience == "Beginner") {
        cout<<"Breakfast: Oatmeal with berries and a tablespoon of almond butter\n";
		cout<<" Protien: 10 gram, Carbohydrates: 40 gram, Fat: 8 gram";
        cout<<"Lunch: Grilled chicken or tofu salad with a variety of colorful vegetables\n"; 
        cout<<" Protien: 20 gram, Carbohydrates: 40 gram, Fat: 10 gram";   
		cout<<"Snack: Greek yogurt with a handful of mixed nuts", 
        cout<<" Protien: 15 gram, Carbohydrates: 15 gram, Fat: 15 gram";        
		cout<<"Dinner: Baked fish or a plant-based protein source (e.g., lentils) with steamed broccoli and sweet potatoes", 
        cout<<" Protien: 25 gram, Carbohydrates: 40 gram, Fat: 15 gram"; 
    
        } 
		else if (experience == "Intermediate") {
            cout<<"Breakfast: Whole grain toast with avocado and poached eggs\n";
        cout<<"A protein smoothie with fruits, Greek yogurt, and a scoop of protein powder\n";
		cout<<" Protien: 25g, Carbohydrates: 50g, Fat: 15g\n";
        cout<<"Lunch: Grilled salmon or tempeh with quinoa and a mix of roasted vegetables.\n"; 
        cout<<"A small serving of mixed fruit.\n";
        cout<<" Protien: 30g, Carbohydrates: 40g, Fat: 15 g\n";   
		cout<<"Pre-Workout: Whole grain crackers with hummus\n",
		cout<<"Protein: 10g, Carbohydrates: 20g, Fat: 10g\n";
		cout<<"Post-Workout: Protein shake with banana\n";
		cout<<"Protein: 20g, Carbohydrates: 30g, Fat: 5g\n";        
		cout<<"Lean beef stir-fry with a variety of colorful vegetables and brown rice\n", 
        cout<<" Protien: 35g, Carbohydrates: 40g, Fat: 10g";
        } 
		else if (experience == "Advanced") {
            cout<<"Breakfast: Egg whites omelet with spinach, tomatoes, and feta cheese\n";
        cout<<"Whole grain toast or sweet potato\n";
		cout<<"Protien: 30g, Carbohydrates: 30g, Fat: 15g";
        cout<<"Mid-Morning Snack: Greek yogurt with a handful of almonds and a drizzle of honey\n"; 
        cout<<"Protien: 20g, Carbohydrates: 20g, Fat: 15g\n";   
		cout<<"Lunch: Grilled chicken breast with quinoa, steamed asparagus, and a side of mixed berries\n", 
        cout<<"Protien: 40g, Carbohydrates: 40g, Fat: 10g"; 
		cout<<"Pre-workout: Brown rice cakes with almond butter and sliced banana.";
		cout<<"Protien: 10g, Carbohydrates: 30g, Fat: 15g\n";        
		cout<<"Post-workout:Whey protein shake with a serving of high-glycemic fruits like pineapple\n", 
        cout<<"Protien: 25g, Carbohydrates: 30g, Fat: 5g\n";  
        cout<<"Dinner: Baked cod or turkey with a large serving of mixed vegetables and quinoa";
        cout<<"Protien: 30g, Carbohydrates: 40g, Fat: 10g\n";
        } 
		else{
            return "Invalid experience level";
        }
    }

     void generateDietPlanForGoldMember() {
        ifstream memberFile("MemberInfo.txt");
        ofstream tempFile("temp.txt");

        string line;
        int searchID;

        cout << "Enter the member number of the Gold member to generate a diet plan: ";
        cin >> searchID;

        bool found = false;

        while (getline(memberFile, line)) {
            // Find the position of the contact number in the line
            size_t pos = line.find(searchID);

            if (pos != string::npos) {
                // Display current member details
                cout << "Current details for Gold member with member number " << searchID << ":\n";
                cout << line << endl;

                // Ask for experience
                string experience;
                cout << "Enter your experience level (Beginner/Intermediate/Advanced): ";
                cin >> experience;

                // Generate diet plan based on experience level (replace with your actual logic)
                string dietPlan = generateDietPlanBasedOnExperience(experience);

                // Update the line with diet plan details
                tempFile << line << " DietPlan: " << dietPlan << endl;

                cout << "Diet plan generated successfully!\n";
                found = true;
            } else {
                tempFile << line << endl;  // Copy the line to temp file as it is
            }
        }

        if (!found) {
            cout << "Gold member with member number " << searchID << " not found.\n";
        }

        memberFile.close();
        tempFile.close();

        // Rename the temp file to the original file
        remove("MemberInfo.txt");
        rename("temp.txt", "MemberInfo.txt");
    }
	void generateDietPlanForSilverMember() {
        ifstream memberFile("MemberInfo.txt");
        ofstream tempFile("temp.txt");

        string line;
        int searchID;

        cout << "Enter the member number of the Silver member to generate a diet plan: ";
        cin >> searchID;

        bool found = false;

        while (getline(memberFile, line)) {
            // Find the position of the contact number in the line
            size_t pos = line.find(searchID);

            if (pos != string::npos) {
                // Display current member details
                cout << "Current details for Silver member with member number " << searchID << ":\n";
                cout << line << endl;

                // Ask for experience
                string experience;
                cout << "Enter your experience level (Beginner/Intermediate/Advanced): ";
                cin >> experience;

                // Generate diet plan based on experience level (replace with your actual logic)
                string dietPlan = generateDietPlanBasedOnExperience(experience);

                // Update the line with diet plan details
                tempFile << line << " DietPlan: " << dietPlan << endl;

                cout << "Diet plan generated successfully!\n";
                found = true;
            } else {
                tempFile << line << endl;  // Copy the line to temp file as it is
            }
        }

        if (!found) {
            cout << "Silver member with member number " << searchID << " not found.\n";
        }

        memberFile.close();
        tempFile.close();

        // Rename the temp file to the original file
        remove("MemberInfo.txt");
        rename("temp.txt", "MemberInfo.txt");
    }
    
};
int main(){
    Admin adminObject;  // Instantiate an object of the admin class
    char choice;
	cout << "\n\n\n";
	cout << "\t\t\t\t----------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t|                                                                    |" << endl;
	cout << "\t\t\t\t|                   WELCOME TO THROWBACK FITNESS                     |" << endl;
	cout << "\t\t\t\t|                                                                    |" << endl;
	cout << "\t\t\t\t----------------------------------------------------------------------" << endl;
	cout << endl << "\t\t\t\t\t\t--PLESE Enter  YOUR UserName and Password--" << endl;
	adminObject.adLogin();
	system("cls");
    do {
    	//system("cls");
        choice = adminObject.menu();  // Display menu and get user's choice

        switch (choice) {
            case 1:
            	system("cls");
                adminObject.addMember();
                break;

            case 2:
            	system("cls");
                adminObject.selectPlanAndSave();
                break;

            case 3:
            	system("cls");
                adminObject.modifyMemberDetails();
                break;

            case 4:
            	system("cls");
                adminObject.deleteMember();
                break;

            case 5:
            	system("cls");
                adminObject.cancelMemberPlan();
                break;

            case 6:
            	system("cls");
                adminObject.giveReview();
                break;

            case 7:
            	system("cls");
                adminObject.display();
                break;
            case 8:
            	system("cls");
                adminObject.checkAndProvideDiscount();
                break;
            case 9:
                cout << "Exiting the program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    } while (choice != '9');  
    return 0;
}
