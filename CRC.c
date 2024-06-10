// выводит CRC8 при порождающем полиноме 285 (дес.сис.счисл.) и 96 битном исходном сообщении




#include <stdio.h>


char Xor (char pol_bit, char d_bit)
{
	char res;
	if (pol_bit == d_bit)
		res = 0;
	else
		res = 1;
	return res;
}


int main (){
	
	
char pol[9] ={1,0,0,0,1,1,1,0,1}; //полином 8 битный
//исходное сообщение 96+8=104
char d[104] = {1,0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0} ;
	
int i=0; int j=0;
char res_bit[9]; //Рез-т xor для каждых 8 бит
int m=0; //индексация текущего рассматриваемого бита в сообщении
char t[9]; //временное хранения результата XOR-действия

//временная переменная для хранения значения СRC без начальных нулей, если они есть
char crc[8];
for (i=0;i<8;i++)
	crc[i]=0;

//
for (i=0;i<104;i++)
{
	res_bit[i]=d[i];
}

//////////////////////////////////
int c=0; int nn=-10; //-10  проставил для контроля ошибок
//
while (c<200)
{
	c++;
	
	
	// отсекаем нули в начале числа
	while (res_bit[m]!=1)
	{
		m++;	
	}

	//Подсчёт СRC
	if (  (104-m)<9  )
	{
		i=0; j=m;
		while (j<=104)
		{
			if (j==104)
				nn = i+1;
			crc[i] = res_bit[j];
			i++; j++;		
		}
		break;
	}	

	//"Докидывает биты с исходного сообщения, потом производит побитово ХОR этих 12 бит с полиномом"
	i=m; j=0;
	while ( (i<(m+9)) )//& (j<13) )
	{
		t[j] = Xor(pol[j], res_bit[i]);
		res_bit[i] = t[j];	
		i++; j++;
	}

}	

//Формирование СRC
char crc1 [8];
for (i=0;i<(8-nn);i++)
{
	crc1[i] = 0;
}	

j=0;
for (i=(8-nn);i<8;i++)
{
	crc1[i] = crc[j];
	j++;
}	

//вывод crc
for (i=0;i<8;i++)
	printf ("%d", crc1[i]);
	
	
	
	
}