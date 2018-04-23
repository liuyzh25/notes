#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;
int prime[1000];
long long PlainText[100];
long long Cipher[100];
int n;
int e=0,d;//��Կ��˽Կ 
//����1000������������Ŀ 
int countPrime(int prime[]){
	int vis[1000],count=0;
	memset(vis,0,sizeof(vis));
	for(int i=2;i<=1000;i++){
		if(!vis[i]){
			prime[count++] = i;
			for(int j=i*i;j<=1000;j+=i){
				vis[j] = 1;
			}
		}
	}
	return count;
}
//�������ݵ�ģ 
long long Exponent_Mode(long long a,int b,int n){
	long long t=1;
	while(b>0){
		if(b%2==1) {
			t=(a*t)%n;
		}
		b=b/2;
		a=(a*a)%n;
	}
	return t;
}
//ŷ�������չ�㷨
int Exgcd(int m,int n,int &x){
	int x1,y1,x0,y0,y;
	x0=1;y0=0;
	x1=0;y1=1;
	x=0;y=1;
	int r=m%n;
	int q=(m-r)/n;
	while(r){
		x=x0-q*x1;y=y0-q*y1;
		x0=x1;y0=y1;
		x1=x;y1=y;
		m=n;n=r;
		r=m%n;
		q=(m-r)/n;
	}
	return n;
}
void RSA_Initialize(){
	int count = countPrime(prime);
	srand((unsigned)time(NULL));
	//��������������� 
	int p = prime[rand()%count];
	int q = prime[rand()%count];
	for(int i=0;i<100;i++) PlainText[i] = rand()%1000;
	cout<<"����100���������"<<endl;
	for(int i=0;i<100;i++) cout<<PlainText[i]<<" ";
	cout<<endl; 
	n = p * q;
	int On = (p-1) * (q-1);
	//����e �� d
	for(int j=3;j<On;j+=1){
		if(Exgcd(j,On,d)==1 && d>0){
			e = j;
			break;
		}
	}
	cout<<q<<" "<<p<<" "<<"n: "<<n<<" "<<"��Կ:"<<e<<"  ˽Կ:"<<d<<endl; 
}
void RSA_encrypt(){
	for(int i=0;i<100;i++){
		Cipher[i] = Exponent_Mode(PlainText[i],e,n);
	}
	cout<<"RSA���ܺ�\n";
	for(int i=0;i<100;i++){
		cout<<Cipher[i]<<" ";
	}
	cout<<endl;
}
void RSA_decrypt(){
	for(int i=0;i<100;i++){
		Cipher[i] = Exponent_Mode(Cipher[i],d,n);
	}
	cout<<"RSA���ܺ�\n";
	for(int i=0;i<100;i++){
		cout<<Cipher[i]<<" ";
	}
	cout<<endl;
}
int main(){ 
	RSA_Initialize();
	PlainText[0]=665;
	RSA_encrypt();
	RSA_decrypt();
} 
