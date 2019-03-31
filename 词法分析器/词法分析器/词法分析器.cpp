#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

/*
�����
<\0,0>
1����32:include����while
33����74��+����!
90������
100����ʶ��
*/


//�����ֱ�
static char Reservedword[32][20] = {
	 "include", "break", "case", "char", "const", "continue",
	  "default", "do", "double", "else", "stdio", "extern",
	  "float", "for", "goto", "if", "int", "long",
	  "register", "return", "short", "signed", "sizeof", "static",
	  "struct", "switch", "typedef", "union", "unsigned", "void",
	  "volatile", "while"
};

//���ű�
static char Operator[42][10] = {
	  ";", "(", ")", "^", ",", "\"", "\'", "#",  "%", "~",  "[", "]", "{",
	 "}", ".", "\?", ":","\\","+","+=","++", "-","-=","--", "*","*=", "/","/=", "<", "<=", ">", ">=", "=", "==","!=", "&","&&", "|", "||", "<<", ">>",  "!"
};



//������ų����г��ֵı�ʶ��
static char Identifier[100][20] = { "" };


//���ұ�����
int SearchReservedword(char Reservedword[][20], char s[])
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(Reservedword[i], s) == 0)
			return i + 1;
	}
	return -1;
}

//�ж��Ƿ�Ϊ��ĸ
bool IsLetter(char s)
{
	if (s >= 'a'&&s <= 'z' || s >= 'A'&&s <= 'Z' || s == '_')
		return true;
	else
		return false;
}


//�ж��Ƿ�Ϊ����
bool IsNum(char s)
{
	if (s >= '0'&&s <= '9')
		return true;
	else
		return false;
}

//����ע��
void Clearnotes(char resourse[], int item)
{
	char newsourse[10000] = { "" };//�������ע�ͺ���ַ���
	int flag = 0;//�������±�
	for (int i = 0; i < item; i++)
	{
		if (resourse[i] == '/'&&resourse[i + 1] == '/')
		{
			while (resourse[i] != '\n')
				i++;
		}
		if (resourse[i] == '/'&&resourse[i + 1] == '*')
		{
			i += 2;
			while (resourse[i] != '*'&&resourse[i + 1] != '/')
			{
				i++;
				if (resourse[i] == '\0')
				{
					printf("�������\n");
					exit(0);
				}
			}
		}
		if(resourse[i]!='\n'&&resourse[i]!='\t'&&resourse[i]!='\v'&&resourse[i]!='\r')//���˵�ˮƽ�Ʊ�����س����س����з�����ֱָ���
		{
			newsourse[flag++] = resourse[i];
		}
	}
	strcpy(resourse, newsourse);
}

//�ʷ�������Ҫ����
void LexicalAnalysis(char resourse[], int &flag,char target[], int &item)
{
	char x;
	int count = 0;
	for (int i = 0; i < 20; i++)//ÿ�����target����
		target[i] = '\0';
	while (resourse[item] == ' ')//�����ո�
	{
		item++;
		x = resourse[item];
	}
	if (resourse[item] == '\0')
	{
		flag = 0;
		return;
	}		
	else if(resourse[item] == ';' || resourse[item] == '(' || resourse[item] == ')' || resourse[item] == '^' || resourse[item] == ',' || resourse[item] == '\"' || resourse[item] == '\'' || resourse[item] == '~' || resourse[item] == '#' || resourse[item] == '%' || resourse[item] == '['|| resourse[item] == ']' || resourse[item] == '{' || resourse[item] == '}' || resourse[item] == '\\' || resourse[item] == '.' || resourse[item] == '\?' || resourse[item] == ':')
	{
		target[0] = resourse[item];
		for (int i = 0; i < 42; i++)
		{
			if (strcmp(target, Operator[i])==0)
			{
				flag = 33 + i;
				break;
			}
		}
		item++;
		return;
	}
	else if (resourse[item] == '+')
	{//+,++,+=
		item++;
		if (resourse[item] == '+')
			flag = 53;
		else if (resourse[item] == '=')
			flag = 52;
		else
		{
			flag = 51;
			item--;
		}		
		item++;
		return;
	}
	else if (resourse[item] == '-')
	{
		item++;
		if (resourse[item] == '-')
			flag = 56;
		else if (resourse[item] == '=')
			flag = 55;
		else
		{
			flag = 54;
			item--;
		}			
		item++;
		return;
	}
	else if (resourse[item] == '*')
	{
		item++;
		if (resourse[item] == '=')
			flag = 58;
		else
		{
			flag = 57;
			item--;
		}			
		item++;
		return;
	}
	else if (resourse[item] == '/')
	{
		item++;
		if (resourse[item] == '=')
			flag = 60;
		else
		{
			flag = 59;
			item--;
		}
		item++;
		return;
	}
	else if (resourse[item] == '<')
	{
		item++;
		if (resourse[item] == '=')
			flag = 62;
		else if (resourse[item] == '<')
			flag = 72;
		else
		{
			flag = 61;
			item--;
		}
		item++;
		return;
	}
	else if (resourse[item] == '>')
	{
		item++;
		if (resourse[item] == '=')
			flag = 64;
		else if (resourse[item] == '>')
			flag = 73;
		else
		{
			flag = 63;
			item--;
		}
		item++;
		return;
	}
	else if (resourse[item] == '=')
	{
		item++;
		if (resourse[item] == '=')
			flag = 66;
		else
		{
			flag = 65;
			item--;
		}
		item++;
		return;
	}
	else if (resourse[item] == '!')
	{
		item++;
		if (resourse[item] == '=')
			flag = 67;
		else
		{
			flag = 74;
			item--;
		}
		item++;
		return;
	}
	else if (resourse[item] == '&')
	{
		item++;
		if (resourse[item] == '&')
			flag = 69;
		else
		{
			flag = 68;
			item--;
		}
		item++;
		return;
	}
	else if (resourse[item] == '|')
	{
		item++;
		if (resourse[item] == '|')
			flag = 71;
		else
		{
			flag = 70;
			item--;
		}
		item++;
		return;
	}
	else if (IsLetter(resourse[item]))
	{
		target[count] = resourse[item];
		count++;
		item++;
	while (IsLetter(resourse[item]) || IsNum(resourse[item]))
	{
		target[count] = resourse[item];
		count++;
		item++;
	}
		flag = SearchReservedword(Reservedword, target);
		if (flag == -1)
			flag = 100;
		return;
	}
	else if (IsNum(resourse[item]))
	{
		while (IsNum(resourse[item]))
		{
			target[count] = resourse[item];
			count++;
			item++;
		}
		flag = 90;
		return;
	}
	else
	{
		printf("�޷�ʶ��\n");
		exit(0);
	}
}

int main()
{
	char resourse[10000] = {""};
	char target[20] = { "" };
	int i = 0;//��¼���鳤��
	int flag = -1;//0������������ţ�1~32�������֣�33~74�����ţ�90��������100����ʶ��
	FILE *f1, *f2;
	if ((f1 = fopen("F:\\test\\test.cpp", "r"))==NULL)
	{
		printf("��ȡ�ļ�testʧ��\n");
		exit(0);
	}
	if ((f2 = fopen("F:\\test\\text2.txt", "w+")) == NULL)
	{
		printf("��ȡ�ļ�text2ʧ��\n");
		exit(0);
	}
	while (true)//��ȡf1�е�����
	{
		if (feof(f1))
			break;
		resourse[i] = fgetc(f1);
		i++;
	}
	fclose(f1);
	cout << resourse << endl;
	resourse[i] = '\0';
	Clearnotes(resourse, i);
	i = 0;
	while (flag != 0)
	{
		LexicalAnalysis(resourse, flag, target, i);
		if (flag == 100)
		{
			for (int j = 0; j < 100; j++)
			{
				if (strcmp(Identifier[j], target)==0)//��ʶ���Ѿ��ڱ���
					break;
				else if (strcmp(Identifier[j], "") == 0)//δд�룬����ʶ��д�����
				{
					strcpy(Identifier[j], target);
					break;
				}
			}
			fprintf(f2, "����ʶ����%s��\n", target);
		}
		else if (flag >= 1 && flag <= 32)
		{
			fprintf(f2, "�������֣�%s)\n", Reservedword[flag - 1]);
		}
		else if(flag==99)
			fprintf(f2, "��������%s��\n", target);
		else if (flag >= 33 && flag <= 74)
		{
			fprintf(f2, "�����ţ�%s��\n", Operator[flag - 33]);
		}
	}
	for (int j = 0; j < 100; j++)
	{
		if(Identifier[j]!="")
			fprintf(f2, "��%d����ʶ����%s\n", j + 1, Identifier[j]);
	}
	fclose(f2);
	getchar();
	return 0;
}