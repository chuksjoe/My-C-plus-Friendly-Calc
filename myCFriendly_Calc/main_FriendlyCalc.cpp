#include "functions.h"

using std::cin;

int main(int ac,char* pargl)
{
	char buffer[MAX]={0};

	cout<<">>>>>>>>>>>WELCOME TO EXPRESSION CALCULATOR PROGRAM<<<<<<<<<<<\n"
		<<"Enter your Expression and send with Enter(send empty line to Quit):\n";

	for(;;)
	{
		cin.getline(buffer,sizeof buffer);

		if(!buffer[0])
			return 0;

		eatspace(buffer);
		cout<<"Ans = "<<expr(buffer)<<endl<<endl;
	}
	system("pause");
}