/*
2445. (10分) 小明的数列
题目描述
	小明最喜欢数列了！今天的他又想到了一个关于数列的小问题：从数列中选出若干个数字（至少选择一个），这些数字相对顺序与它们对应在数列中的相对顺序一致，同时要求其大小单调递增。求满足条件的这些数字的最大和，你能解决这个问题吗？
输入描述
	第一行输入1个整数，N，其中N表示数列大小。（1<=N<=2000）
	第二行输入N个整数，表示数列中的每个数字A_i。（-10000<=A_i<=10000）
输出描述
	一个整数，表示满足条件的这些数字的最大和。
样例输入
	5
	1 3 1 5 -2
样例输出
	9
*/

/*#include<iostream>

using namespace std;

int a[2000]={0},dp[2000]={0};

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;++i) cin>>a[i];
	for(int i=0;i<n;++i){//ö����a[i]��β�ĵ��������� 
		dp[i]=a[i];
		for(int j=0;j<i;++j){
			if(a[j]<a[i]) dp[i]=max(dp[i],dp[j]+a[i]);
		}
	}
	int maxx=-1e8;
	for(int i=0;i<n;++i) if(maxx<dp[i]) maxx=dp[i];
	cout<<maxx;
	return 0;
}*/

/*
2450. (25分) 排队游戏
题目描述
	几个小朋友站成一列玩排队游戏。但他们因为谁排在谁前面发生了争执，这时候老师提出了一些排列规则，来帮助小朋友们排成一列，以下为规则描述：
	1、ADD name height。添加一个小朋友站在队伍的最后。如ADD A h表示添加身高为h名字为A的小朋友站在队伍最后。
	2、SELECT name。抽取队伍中的某个小朋友站在队伍最前面（被抽取的小朋友一定在队伍中）。如SELECT B表示让队伍中的小朋友B站在队伍最前面。
	3、LEAVE name。让队伍中的某个小朋友离开队伍（要离开的小朋友一定在队伍中）。如LEAVE C表示让小朋友C离队。
	4、ORDER。所有小朋友按身高由低到高排序（低的靠前），如果身高相同，则按小朋友名字的字典序排列。
	注意：名字是由大写字母组成的字符串，小朋友们的名字是相互不同的。身高是正整数。
	（字典序定义为：用于比较两个字符串的先后排列关系，取决于两个字符串从左到右第一个不同字符的ASCII值的大小关系。如，ALICE和ANNA，从左到右首个不同的字母分别是L和N，而L<N，因此二者的排序关系为ALICE<ANNA。）
	【数据范围】
	字符串长度最大为20。
	保证小朋友的身高均为在合理身高区间[130, 170]内的正整数。
	100%的数据满足：1<=n<=1000
输入描述
	输入第一行为规则个数n。之后的n行每行为一条规则。
输出描述
	输出小朋友排好队后的序列，每个小朋友一行，每行为名字和身高，用空格隔开。
*/

/*#include<iostream>
#include<algorithm>

using namespace std;

class shit{
public:
	string name;
	int height;
}poop[1000];

static bool biggershit(shit &a,shit &b){
	if(a.height==b.height) return a.name<b.name;
	else return a.height<b.height;
}

int index=0,n;

void add(string n,int h){
	poop[index].name=n;
	poop[index++].height=h;
}

void select(string n){
	int p=0;
	for(int i=0;i<index;++i){
		if(poop[i].name==n){
			p=i;
			break;
		}
	}
	shit temp=poop[p];
	for(int i=p-1;i>=0;--i){
		poop[i+1]=poop[i];
	}
	poop[0]=temp;
}

void leave(string n){
	int p=0;
	for(int i=0;i<index;++i){
		if(poop[i].name==n){
			p=i;
			break;
		}
	}
	for(int i=p;i<index;++i){
		poop[i]=poop[i+1];
	}
	poop[index].name="";
	poop[index--].height=0;
}

int main(){
	cin>>n;
	for(int i=0;i<n;++i){
		string comm;
		cin>>comm;
		if("ADD"==comm){
			string a;
			int b;
			cin>>a>>b;
			add(a,b);
		}
		else if("SELECT"==comm){
			string a;
			cin>>a;
			select(a);
		}
		else if("LEAVE"==comm){
			string a;
			cin>>a;
			leave(a);
		}
		else if("ORDER"==comm){
			sort(poop,poop+index,biggershit);
		}
	}
	for(int i=0;i<index;++i) cout<<poop[i].name<<' '<<poop[i].height<<endl;
	return 0;
}*/ 

/*
2422. (25分) 谁去了紫荆
题目描述
	徐老师晚上吃完饭回到实验室发现有4个学生A、B、C、D，想了解他们晚上去哪儿吃的饭。目前他已经获知四位学生中有1个人去了紫荆其他都去了桃李，徐老师想知道是他们中的哪一个人去了紫荆。四位学生分别给了徐老师一句回答，回答如下
	（回答中的X、Y、Z、Q为系统输入，值可以去A、B、C、D中的任意一个，X、Y、Z、Q可能指同一个人）。
	A：X晚上去了紫荆
	B：Y没去紫荆好吧
	C：Z去了紫荆，在四楼吃了个榴莲酥！
	D：Q去桃李吃的豚骨拉面，没去紫荆
	四位同学回答后，承认他们是为了给老师提供靠学生的素材，关于“谁去了紫荆”这件事儿，故意有2个人说真话、2个人说假话。你能帮徐老师分析一下，到底是谁去了紫荆吗？请你把满足条件所有可能的人按照字典序输出。
输入格式
	四个字母，分别对应X、Y、Z、Q指代的人。
输出描述
	若干个字母，表示可能去了紫荆的人，按照字典序输出
样例输入
	A A C C
样例输出
	ABCD
*/

/*#include<iostream>

using namespace std;

int main(){
	char x,y,z,q;
	cin>>x>>y>>z>>q;
	bool res[4]={0};
	for(char a='A';a<'D';++a){
		for(char b=a+1;b<='D';++b){
			
		}
	}
	for(char p='A';p<='D';++p){
		int count=(x==p)+(y!=p)+(z==p)+(q!=p);
		if(2==count){
			res[p-'A']=1;
		}
	}
	for(int i=0;i<4;++i){
		if(res[i]) cout<<char('A'+i);
	}
	return 0;
}*/ 


/*
2449. (20分) 时间冲突
题目描述
	会议室预定系统的一个基本功能，是判断对同一个会议室的两条预定是否有冲突。每条预定包括一个开始时刻startTime和一个结束时刻endTime（约定会议不跨夜，即开始时刻和结束时刻必须在同一天）。每个时刻表达为一个24小时制HH:MM格式的字符串（约定一天的范围为00:00-23:59）。如果先开始的预定的结束时刻早于或等于后开始的预定的开始时刻，则认为两条预定没有冲突。
	现在给定两次预定，你能判断两次预定是否有冲突吗？
输入描述
	第一行输入两个字符串，用空格隔开，分别表示第一条预定的开始时刻和结束时刻。
	第二行输入两个字符串，用空格隔开，分别表示第二条预定的开始时刻和结束时刻。
样例输入
	01:15 02:00
	02:00 03:00
样例输出
	-1
	样例1解释：
	第一条预定的结束时刻等于第二条预定的开始时刻，因此不存在冲突，输出-1。
注释
	样例输入2
	10:00 11:00
	10:20 15:00

	样例输出2
	40

	样例输出2解释
	两条预定存在时间冲突的时间段为10:20~11:00，冲突时长为40分钟，故输出40。
*/

#include<iostream>

using namespace std;

int main(){
	string a,b,c,d;
	cin>>a>>b>>c>>d;
	int t1=(a[0]*10+a[1]-480-48)*60+a[3]*10+a[4]-480-48;
	int t2=(b[0]*10+b[1]-480-48)*60+b[3]*10+b[4]-480-48;
	int t3=(c[0]*10+c[1]-480-48)*60+c[3]*10+c[4]-480-48;
	if(t3>1439) t3=(c[0]-48)*60+c[2]*10+c[3]-480-48;
	int t4=(d[0]*10+d[1]-480-48)*60+d[3]*10+d[4]-480-48;
	if(t1>t3){
		int temp=t1;
		t1=t3;
		t3=temp;
		temp=t2;
		t2=t4;
		t4=temp;
	}
	if(t1==t3&&t2>t4){
		int temp=t2;
		t2=t4;
		t4=temp;
	}
	if(t2<=t3) cout<<-1;
	else{
		cout<<min(t2,t4)-t3;
	}
	return 0;
}

/*
2448. (20分) 谁没签到
项目描述
	有N名同学（编号1~N）选课的课程转为线上教学。每位同学登录线上课程时会产生一次签到记录。由于网络可能出现不稳定，有的同学会中途断线再登录，从而产生额外的签到记录。现在，后台记录了M条签到记录，请找出哪位同学没有签到。
	【数据范围】
	1<=N<=10^4
	1<=M<=10^4
	1<=T_i<=N
输入描述
	输入第一行包含两个正整数N, M；第二行包含M个正整数T_i，用空格隔开，表示第i条签到记录的同学的编号。
输出描述
	输出为一行。如果N名同学全部完成了签到，则输出“ALL”；否则，按由小到大的顺序输出所有没有签到的同学的编号，以空格分隔。
样例输入
5 5
1 3 1 3 4
样例输出
2 5
注释
	样例输入2
	5 5
	1 5 3 2 4

	样例输出2
	ALL
*/

/*#include<iostream>

using namespace std;

bool a[10000]={0};

int main(){
	int n,m;
	cin>>n>>m;
	int *t=new int[m];
	for(int i=0;i<m;++i){
		cin>>t[i];
		a[t[i]-1]=true;
	}
	bool all=1;
	for(int i=0;i<n;++i){
		if(!a[i]){
			cout<<i+1<<' ';
			all=0;
		}
	}
	if(all) cout<<"ALL";
	return 0;
}*/