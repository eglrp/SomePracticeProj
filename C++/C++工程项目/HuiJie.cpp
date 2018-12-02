#include <iostream>
#include <fstream>
#include <string>

using namespace std;

inline string change(char c)
{
    string data;
    for(int i=0;i<8;i++)
    {
        //  data+=c&(0x01<<i);
        if ( ( c >>(i-1) ) & 0x01 == 1 )
        {
            data+="1";
        }
        else
        {
            data+="0";
        }

    }
    for(int a=1;a<5;a++)
    {
        char x=data[a];
        data[a]=data[8-a];
        data[8-a]=x;

    }

   return data;
}

int main(){

	char a[1024];

	FILE *pf1 = fopen("C:\\Users\\Neverland_LY\\Desktop\\123.txt","r");
	for(int i=0;i < 30;i++)
	{
		fread(&a[i],1,1,pf1);
		cout << change(a[i]) << " ";  //printf("%0X ",a[i]);
	}
	fclose(pf1);//关闭文件

	cout << "\n--------\n" ;

	return 0;
}
