#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;
int prime[1000];
long long PlainText[100];
long long Cipher[100];
int n;
int e=0,d;//公钥和私钥 
bool tag=false;
int isMutual_Prime(int a,int b){
	if(b==0) return a;
	else return isMutual_Prime(b,a%b);
}
//计算1000以内素数的数目 
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
//反复求幂的模 
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
//欧几里得扩展算法
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
	//随机生成两个素数 
	int p = prime[rand()%count];
	int q = prime[rand()%count];
	for(int i=0;i<100;i++) PlainText[i] = rand()%1000;
	cout<<"生成100个随机数："<<endl;
	for(int i=0;i<100;i++) cout<<PlainText[i]<<" ";
	cout<<endl; 
	n = p * q;
	int On = (p-1) * (q-1);
	//生成e 和 d
	//随机选择一个整数e，条件是1< e < φ(n)，且e与φ(n) 互质
	int j=rand()%p+3;//保证公钥的随机性 
	for(;j<On;j+=1){
		if(isMutual_Prime(j,On)==1 && Exgcd(j,On,d)==1 && d>0){
			e = j;
			break;
		}
	}
	//如果找不到乘法逆元，自己定义一个 
	if(j==On){
		e=5327;
		d=25775;
		n=373319;
	}
	cout<<q<<" "<<p<<" "<<"n: "<<n<<" "<<"公钥:"<<e<<"  私钥:"<<d<<endl; 
}
void RSA_encrypt(){
	for(int i=0;i<100;i++){
		Cipher[i] = Exponent_Mode(PlainText[i],e,n);
	}
	cout<<"RSA加密后：\n";
	for(int i=0;i<100;i++){
		cout<<Cipher[i]<<" ";
	}
	cout<<endl;
}
void RSA_decrypt(){
	tag=true;
	for(int i=0;i<100;i++){
		Cipher[i] = Exponent_Mode(Cipher[i],d,n);
	}
	cout<<"RSA解密后：\n";
	for(int i=0;i<100;i++){
		cout<<Cipher[i]<<" ";
		if(Cipher[i]!=PlainText[i]) tag=false;
	}
	cout<<endl;
	if(tag) cout<<"解密成功\n";
	else cout<<"解密失败\n";
}
int main(){ 
	RSA_Initialize();
	RSA_encrypt();
	RSA_decrypt();
} 
