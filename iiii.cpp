#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <limits>
using namespace std;

enum enquestionlevel {level_easy=1 , level_med=2 , level_hard =3 , level_mix=4};
enum enquestionoptype {op_add =1 , op_sub =2 , op_mul=3 , op_div=4 , op_mix=5};
struct stquestion
{
	short number1 = 0;
	short number2 = 0;
	enquestionoptype optype;
	enquestionlevel questionlevel;
	int correctanswer = 0;
	int playeranswer = 0;
	bool answerresult = false;
};
struct stquizz
{
	stquestion question[100];
	short howmanyguizz=0;
	enquestionlevel quizzlevel;
	enquestionoptype optype;
	short rightanswer = 0;
	short wronganswer = 0;
	bool pass = false;
};
short howmanyquestion()
{
	short number = 0;
	do
	{
		cout << "How many questions do you wnat to answer ? ";
		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "invalid portion , please enter valid one? ";
			cin >> number;
		}
	} while (number < 1);
	return number;
}
enquestionlevel read_guestionlevel()
{
	short number = 0;
	do
	{
		cout << "Enter question level [1]:Easy , [2]:Mediam , [3]:Hard , [4]:Mix ? ";
		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "invalid value , please enter valid one? ";
			cin >> number;
		}
	} while (number < 1 || number>4);
	return (enquestionlevel)number;
}
enquestionoptype read_optype()
{
	short number = 0;
	do
	{
		cout << "Enter question operation type  [1]:Add , [2]:Sub , [3]:Mul , [4]:Div , [5]:Mix ? ";
		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "invalid value , please enter valid one? ";
			cin >> number;
		}
	} while (number < 1 || number>5);
	return (enquestionoptype)number;
}
int random_number(int from, int to)
{
	int random = rand() % (to - from + 1) + from;
	return random;
}
int calculate(int num1, int num2, enquestionoptype optype)
{
	switch (optype)
	{
	case enquestionoptype::op_add:
		return num1 + num2;
	case enquestionoptype::op_mul:
		return num1 * num2;
	case enquestionoptype::op_div:
		return num1 / num2;
	case enquestionoptype::op_sub:
		return num1 - num2;
	default:
		return num1 + num2;
	}
}
stquestion genaratequizz(enquestionlevel levelquizz , enquestionoptype optype )
{
	stquestion question;
	if (levelquizz == enquestionlevel::level_mix)
		levelquizz = (enquestionlevel)random_number(1, 3);
	if (optype == enquestionoptype::op_mix)
		optype = (enquestionoptype)random_number(1, 4);
	question.optype = optype;
	switch (levelquizz)
	{
	case enquestionlevel::level_easy:
		question.number1 = random_number(1, 20);
		question.number2 = random_number(1, 20);
		question.questionlevel = levelquizz;
		question.correctanswer = calculate(question.number1, question.number2, optype);
		return question;
	case enquestionlevel::level_med:
		question.number1 = random_number(20, 50);
		question.number2 = random_number(20, 50);
		question.questionlevel = levelquizz;
		question.correctanswer = calculate(question.number1, question.number2, optype);
		return question;
	case enquestionlevel::level_hard:
		question.number1 = random_number(50, 100);
		question.number2 = random_number(50, 100);
		question.questionlevel = levelquizz;
		question.correctanswer = calculate(question.number1, question.number2, optype);
		return question;
	case enquestionlevel::level_mix:
		question.number1 = random_number(1, 100);
		question.number2 = random_number(1, 100);
		question.questionlevel = levelquizz;
		question.correctanswer = calculate(question.number1, question.number2, optype);
		return question;
	}
	return question;
}
void genaratequestionquizz(stquizz &quizz)
{
	for (short game = 0; game < quizz.howmanyguizz; game++)
	{
		quizz.question[game] = genaratequizz(quizz.quizzlevel, quizz.optype);
	}
}
string get_optype(enquestionoptype optype)
{
	string arr[5] = { "+" , "-" , "*" , "/" , "Mix" };
	return arr[optype - 1];
}
string get_questionslevel(enquestionlevel level)
{
	string arr[4] = { "Easy" , "Medium" , "Hard" , "Mix" };
	return arr[level - 1];
}
void print_result(stquizz quizz , short number)
{
	cout << "\nQuestion [" << number + 1 << "/" << quizz.howmanyguizz << "]\n" << endl;
	cout << quizz.question[number].number1 << endl;
	cout << quizz.question[number].number2 << " ";
	cout << get_optype(quizz.question[number].optype) << endl; 
	cout << "-------------" << endl;
}
int get_playeranswer()
{
	int number = 0;
	cin >> number;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "invalid portion , please enter valid one? ";
		cin >> number;
	}
	return  number;
}
void getandcorrectplayeranswer(stquizz &quizz , short number)
{
	if (quizz.question[number].playeranswer == quizz.question[number].correctanswer)
	{
		quizz.rightanswer++;
		quizz.question[number].answerresult = true;
		cout << "\nRigth answer :-)" << endl;
	}
	else
	{
		quizz.wronganswer++;
		quizz.question[number].answerresult = false;
		cout << "Wrong answer :-(" << endl;
		cout << "The rigth answer is: " << quizz.question[number].correctanswer << endl;
	}
}
void askandcorrect_answer(stquizz &quizz)

{
	for (short game = 0; game < quizz.howmanyguizz; game++)
	{
	     print_result(quizz , game);
		 quizz.question[game].playeranswer = get_playeranswer();
		 getandcorrectplayeranswer(quizz, game);
	}
	quizz.pass=(quizz.rightanswer >= quizz.wronganswer);
}
string get_pass(stquizz quizz)
{
	if (quizz.pass)
	{
		system("color 2f");
		return  "Pass :-)";
	}
	else
	{
		system("color 4f");
		cout << "\a";
		return  "fail :-(";
	}
}
void print_finalresults(stquizz &quizz)
{
	cout << "\n__________________________________" << endl;
	cout << "\n   Final Results is " << get_pass(quizz) << endl;
	cout << "__________________________________" << endl;
	cout << "\nNumber of questions is    : " << quizz.howmanyguizz << endl;
	cout << "Questions level           : " << get_questionslevel(quizz.quizzlevel) << endl;
	cout << "Operation type            : " <<"[" << get_optype(quizz.optype)<<"]" << endl;
	cout << "Number of Right answer is : "<<quizz.rightanswer <<endl;
	cout << "Number of Wrong answer is : "<<quizz.wronganswer <<endl;
	cout << "__________________________________" << endl;
}
void play_game()
{
	stquizz quizz;
	quizz.howmanyguizz = howmanyquestion();
	quizz.quizzlevel = read_guestionlevel();
	quizz.optype = read_optype();
	genaratequestionquizz(quizz);
	askandcorrect_answer(quizz);
	print_finalresults(quizz);
}
void clear_screen()
{
	system("cls");
	system("color 0f");
}
void start_game()
{
	char playagain = 'y';
	do
	{
		clear_screen();
		play_game();
		cout << "\nDo you want to play again ? Y/N ? ";
		cin >> playagain;
	} while (playagain == 'y' || playagain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	start_game();
}
