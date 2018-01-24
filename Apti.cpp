#include <fstream>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#define PASSWORD "kanishk"

using namespace std;

class Question
{
	char ques[1001];
	char a[51], b[51], c[51], d[51];    //options
	char correctOption;
public:
	 void input();
	 void display(int flag = 0);
	 void modify();
	 int getLength() {
	 	return strlen(ques);
	 }
	 int isCorrect(char choice);
};

int Question::isCorrect(char choice) {
	if(choice == correctOption || (correctOption - 32) == choice)
		return 1;
	else
		return 0;
}

void Question::modify() {
	cout << "Enter updated value or press . to skip" << endl;
	char uq[1001];
	cout << ques << endl;
	//cin.ignore();
	cin.getline(uq, 1001);
	if(strcmp(uq,"."))
		strcpy(ques, uq);

	cout << "A." << a << endl;
	cin.getline(uq, 51);
	if(strcmp(uq,"."))
		strcpy(a, uq);

	cout << "B." << b << endl;
	cin.getline(uq, 51);
	if(strcmp(uq,"."))
		strcpy(b, uq);

	cout << "C." << c << endl;
	cin.getline(uq, 51);
	if(strcmp(uq,"."))
		strcpy(c, uq);

	cout << "D." << d << endl;
	cin.getline(uq, 51);
	if(strcmp(uq,"."))
		strcpy(d, uq);

	char c;
	cout << "Correct Option: " << correctOption << endl;
	cin >> c;
	cin.ignore();
	if(c != '.')
		correctOption = c;

	cout << "Updated question is: " << endl;
	this->display(); 
}

void Question::display(int flag /*default=0*/) {
	cout << endl << ques << endl;
	cout << "A. " << setw(20) <<left<< a << "" << "B. " << setw(20) << b << endl;
	cout << "C. " << setw(20) <<left<< c << "" << "D. " << setw(20) << d << endl;
	if(!flag)
		cout << "Correct Option: " << correctOption << endl;
}

void Question::input() {
	cout << "Enter question: \n";
	//cin.ignore();
	cin.getline(ques,1001);
	
	cout << "Enter option A: ";
	cin.getline(a,51);
	cout << "Enter option B: ";
	cin.getline(b,51);
	cout << "Enter option C: ";
	cin.getline(c,51);
	cout << "Enter option D: ";
	cin.getline(d,51);
	cout << "Enter Correct Option: ";
	cin >> correctOption;
	cin.ignore();
}

class Apti
{
	int score;
	int numberOfQuestions;
	int getNumberOfQuestions();
	void setNumberOfQuestions(int numberOfQuestions);
	void add_ques();
	void del_ques();
	void modify_ques();
public:
	Apti();
	void start();
	void settings();
	void disp_all_questions();
};

void Apti::settings() {
	cout << "Enter PASSWORD: ";
	char ch[1];
	char arr[51] ="";
	while((ch[0] = getch()) != '\r') {
		cout << '*';
		strcat(arr,ch);
	}
	strcat(arr,"\0");
	if(strcmp(PASSWORD, arr)) {
		cout << "\nIncorrect PASSWORD...";
		return;
	}
	system("cls");
	cout << "MENU\n"
	 	 << "1. Add questions\n"
	 	 << "2. Update questions\n"
	 	 << "3. Delete questions\n"
	 	 << "4. Display all Questions\n"
	 	 << "5. Exit\n"
	 	 << "Enter choice: ";
	int choice;
	cin >> choice;
	cin.ignore();

	switch(choice) {
		case 1:
			add_ques();
		break;

		case 2:
			modify_ques();
		break;

		case 3:
			del_ques();
		break;

		case 4:
			disp_all_questions();
		break;

		case 5:
			return;

		default:
			cout << "\nInvalid choice...\n";
	}
}

void Apti::del_ques() {
	if(numberOfQuestions == 0) {
		cout << "Question list empty...\n";
		return;
	}

	ifstream ifi("questions.dat", ios::binary);
	ofstream ofi("temporary.dat", ios::binary);

	Question Q; char choice; int count = 0;

	while(ifi.read((char*)&Q, sizeof(Q))) {
		Q.display();
		cout << "Delete this question? ";
		cin >> choice;
		cin.ignore();
		if(choice == 'n' || choice == 'N')
			ofi.write((char*)&Q, sizeof(Q));
		else count++;
	}

	ofi.close();
	ifi.close();
	remove("questions.dat");
		
	rename("temporary.dat", "questions.dat");

	cout << endl << count << " questions are deleted successfully.\n";
	numberOfQuestions -= count;
	setNumberOfQuestions(numberOfQuestions);
}

Apti::Apti() {
	score = 0;
	numberOfQuestions = 0;
	if(getNumberOfQuestions() < 0) {
		setNumberOfQuestions(numberOfQuestions);
	}
}

int Apti::getNumberOfQuestions() {
	ifstream ifi;
	ifi.open("numberOfQuestions.dat");
	if(ifi) {
		ifi >> numberOfQuestions;
		ifi.close();
		return 1;
	}
	else return -1;
}

void Apti::setNumberOfQuestions(int numberOfQuestions) {
	ofstream ofi("numberOfQuestions.dat");
	ofi << numberOfQuestions;
	ofi.close();
}

void Apti::start() {
	if(numberOfQuestions == 0) {
		cout << "No questions to ask...";
		return;
	}

	system("cls");
	cout<<" welcome to the aptitude test.. The following test will test your aptitude skills..\n\n"
	<<" THE RULES ARE AS FOLLOWS::\n 1.THE TEST CONTAINS 15 QUESTIONS \n"
	<<" 2. 10 MARKS WILL BE AWARDED FOR EACH CORRECT ANSWER \n"
	<<" 3. 4 MARKS WILL BE DEDUCTED FOR A WRONG ANSWER.. YOU CAN PASS THE QUESTION.\n"
	<<"  \n NOW .. LETS START THE TEST .. PRESS ANY KEY TO START THE TEST";
	getch();


	int array[numberOfQuestions];
	for(int i = 0; i < numberOfQuestions; ++i)
		array[i] = i;

	srand(time(NULL));
	int random, temp;
	for(int i = numberOfQuestions-1; i >=0 ; --i) {
		random = rand() % (numberOfQuestions - i);
		temp = array[i];
		array[i] = array[random];
		array[random] = temp;
	}
	
	ifstream ifi("questions.dat", ios::binary);
	Question Q; char choice;
	for(int i = 0; i < numberOfQuestions; ++i) {
		ifi.seekg(array[i] * sizeof(Question));
		ifi.read((char*)&Q, sizeof(Q));

		Q.display(1);
		cout << "Enter choice, or p to PASS: ";
		cin >> choice;
		cin.ignore();
		if(choice == 'p');
		if(Q.isCorrect(choice)) {
			score += 10;
		}
		else {
			score -= 4;
		}
		system("cls");
	}

	cout << "\nOver... Total score: \n" << score;
}

void Apti::disp_all_questions() {
	if(numberOfQuestions == 0)
	{
		cout << "Question list empty...";
		return;
	}
	ifstream ifi("questions.dat", ios::binary);
	Question Q;
	while(ifi.read((char*)&Q, sizeof(Question)))
		Q.display();
	ifi.close();
}

void Apti::add_ques() {
	int count = 0; //to count number of questions added

	char more = 'y';
	Question Q;

	ofstream ofi("questions.dat", ios::binary | ios::app);

	do {
		count++;	
		Q.input();
		ofi.write((char*)&Q, sizeof(Question));
		cout << "\nWant to enter more?: ";
		cin >> more;
		cin.ignore();
	}while(more == 'Y' || more == 'y');


	numberOfQuestions += count;
	setNumberOfQuestions(numberOfQuestions);
	ofi.close();
}

void Apti::modify_ques() {
	
	if(numberOfQuestions == 0) {
		cout << "Question list empty...\n";
		return;
	}	

	fstream ifi("questions.dat", ios::binary | ios::in | ios::out);

	Question Q;
	char ch = 'n';
	
	long pos = ifi.tellg();
	while(ifi.read((char*)&Q, sizeof(Question))) {
		Q.display();

		cout << "Modify this? ";
		cin >> ch;
		cin.ignore();

		if(ch == 'y' || ch == 'Y') {
			Q.modify();
			ifi.seekp(pos);
			ifi.write((char*)&Q, sizeof(Question));
		}
		pos = ifi.tellg();
	}
	getch();
	cout << "No more questions...";
	ifi.close();
}

int main()
{/*
	ifstream ifi("questions.dat", ios::binary);
	ofstream ofi("temporary.dat", ios::binary);

	Question Q; //char choice; 
	int count = 0;

	while(ifi.read((char*)&Q, sizeof(Q))) {
		Q.display();
		//cout << "Delete this question? ";
		//cin >> choice;
		//cin.ignore();
		if(Q.getLength() != 0)
			ofi.write((char*)&Q, sizeof(Q));
		else count++;
	}

	ofi.close();
	ifi.close();
	remove("questions.dat");
		
	rename("temporary.dat", "questions.dat");

	cout << endl << count << " questions are deleted successfully.\n";
*/

	while(1) {
		system("cls");
		cout<<"\n"<<"    #     # # #  # # #  #  # # #  #   #  ###    # # #       # # #  # # #  # # #  # # #             " ;
		cout<<"\n"<<"   # #    #    #   #    #    #    #   #  #  #   #             #    #      #        #   "  ;
		cout<<"\n"<<"  #####   # # #    #    #    #    #   #  #   #  # # #         #    # # #  # # #    #      "; 
		cout<<"\n"<<" #     #  #        #    #    #    #   #  #  #   #             #    #          #    #   ";
		cout<<"\n"<<"#       # #        #    #    #    # # #  ###    # # #         #    # # #  # # #    #   ";

		cout << "\n1. Start";
		cout << "\n2. Settings";
		cout << "\n3. Exit";
		cout << "\nEnter choice: ";

		int choice;
		cin >> choice;
		cin.ignore();
		Apti A;
	
		switch(choice) {
			case 1:
				A.start();
			break;

			case 2:
				A.settings();
			break;

			case 3: return 0;

			default:
				cout << "\nInvalid choice...\n";
		}
		getch();
	}
	return 0;
}