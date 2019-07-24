#include<iostream>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<cmath>

using std::endl;
using std::cout;
using std::sin;
using std::cos;
using std::tan;

const int MAX=80;//Maximum character in an expression include the terminating character '\0'

//This function overwrites the spaces in the array of the expression entered by the user.
void eatspace(char* str){
	int i=0;									//index for the array copied to without the spaces
	int j=0;									//index for the array copied from that has the spaces
	//Note: in this function, the the array of the expression copies from itself to itself
	//		but with different indices, i.e 'i and j'.
	while((*(str+i)=*(str+j++))!='\0'){			//while the next character in the array is not a terminating character '\0',
												//copy to the array with index i.
		if(*(str+i)!=' ')						//If the current character in the new array is not a space,
			i++;								//increment it's index.
												//but if it is a space, the index is not incremented
	}											//and the next character which is not also a space overwrites it.
}

//Returns the the character '^' underneath the unwanted character in the expression entered by the user.
void error(char* str,int index){
	index-=1;
	cout<<str<<endl;
	for(int i=0;i<index;i++)
		cout<<" ";

	cout<<'^'<<endl;
}

const double RAN_DEG=57.2957795;
double sind(double num){
	return sin(num/RAN_DEG);
}

double tand(double num){
	return tan(num/RAN_DEG);
}

double cosd(double num){
	return cos(num/RAN_DEG);
}
//Returns the value of the current number() function value raised to the power of the value following the character '^'
double power(double a,double b){
	double pow=1;
	for(int i=0;i<b;i++)
		pow*=a;

	return pow;
}

//This function Extracts the substring that is within a parenthese
char* extract(char* str,int& index){
	char buffer[MAX];
	char* pstr=0;
	int numL=0;
	int bufindex=index;
	
	do{
		buffer[index-bufindex]=*(str+index);
		switch(buffer[index-bufindex]){
			case ')':
				if(numL==0){
					buffer[index-bufindex]='\0';
					++index;
					pstr=new char[index-bufindex];
					if(!pstr){
						cout<<"\nMemory Allocation Failed!!!\n";
						system("pause");
						exit(1);
					}
					strcpy_s(pstr,index-bufindex,buffer);
					return pstr;
				}
				else
					numL--;
					break;
				
			case '(':
				numL++;
				break;
		}
	}while(*(str+index++)!='\0');
	//if it eventually reaches the terminating character without seeing a single closing parenthese,
	//it will display the message below.
	cout<<"Ran Off The End Of The Expression!!!\nProgram Terminates.\n";
	system("pause");
	exit(1);
	return pstr;
}
double expr(char* string);
//This function returns a number which is a group of digits and sometimes with decimal point.
double number(char* str, int& index){
	double value=0.0;							//initialize the return value to 0.0.
	
	if(*(str+index)=='s'){
		index+=3;
		if(*(str+(index))=='d'){
			double num=number(str,++index);
			return sind(num);
		}
		else if(*(str+index)=='('){
			double num=number(str,index);
			return sin(num);
		}
	}
	if(*(str+index)=='t'){
		index+=3;
		if(*(str+(index))=='d'){
			double num=number(str,++index);
			return tand(num);
		}
		else if(*(str+index)=='('){
			double num=number(str,index);
			return tan(num);
		}
	}
	if(*(str+index)=='c'){
		index+=3;
		if(*(str+(index))=='d'){
			double num=number(str,++index);
			return cosd(num);
		}
		else if(*(str+index)=='('){
			double num=number(str,index);
			return cos(num);
		}
	}

	if(*(str+index)=='('){
		char* psubstr=0;
		psubstr=extract(str,++index);
		value=expr(psubstr);
		delete[] psubstr;
		return value;
	}
	//Note: in this function, another function (isdigit(int c) ) which is defined in the header file (cctype.h)
	//		is used to check if a character is digit or not and returns true if the character is and false if it is not a digit.
	//		Other function in the cctype.h header file are isalpha(int c),isupper(int c),islower(int c)
	//		which check if a character is an alphabet, an uppercase character or a lowercase character respeectively.
	while((*(str+index))>='0'&&(*(str+index))<='9'){//the condition in the while is my idea
													//original condition is "while(isdigit(*(str+index)))" which is equivalent to mine.
		value=10*value+(*(str+index++)-'0');
	}
	if(*(str+index)!='.')
		return value;
		
	double factor=1.0;
	while(isdigit(*(str+(++index)))){
		factor*=0.1;
		value=value+(*(str+index)-'0')*factor;
	}
	return value;
}

//This function returns either a number or the value of an expression with either a multiplication or devision operator
double term(char* str, int& index){
	double value;
	value=number(str,index);
	
	while(*(str+index)=='*'||*(str+index)=='/'||*(str+index)=='^'){
		if(*(str+index)=='^')
			value=power(value,number(str,++index));

		if(*(str+index)=='*')
			value*=number(str,++index);
			
		if(*(str+index)=='/')
			value/=number(str,++index);
	}
	return value;
}

//This function returns the value of an expression.
double expr(char* str){
	double value=0.0;
	int index=0;
	
	value=term(str,index);
	for(;;){
		switch (*(str+index++)){
			case '\0':
				return value;
				
			case '+':
				value+=term(str,index);
				break;
				
			case '-':
				value-=term(str,index);
				break;
				
			default:
				cout<<"\nERROR!!!\nUnwanted Character has been entered.\n";
				error(str,index);
				system("pause");
				exit(1);
		}
	}
}