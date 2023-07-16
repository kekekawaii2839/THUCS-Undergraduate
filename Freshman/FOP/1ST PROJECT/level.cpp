#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

struct Level{
	int input_num;
	int inputs[1000];
	int space_num;
	bool avliable_command[8];//8λ���� ��ʾÿλ��Ӧ��ָ��Ƿ����
	int std_outputs[1000];
};

class Command{
	private:
		int counter;
	public:
		Command(){this->counter=0;};
		
		int collection[100][2];//��һλ��ʾָ�� �ڶ�λ��ʾ���ܵ�ָ�������û������-1���� 
		bool add_command(std::string);
		bool setCounter(int);
		int getCounter(){return this->counter;}
};

bool Command::add_command(std::string a){
	int i=0;
	for(i=0;i<a.length();++i){
		if(' '==a[i]) break;
	}
	std::string c;
	for(int u=0;u<i;++u) c[u]=a[u];
	c[i]='\0';
	int arg=a[i+1]-48;//Ŀǰ��Ϊ����Ϊһλ���� 
	std::cout<<"c="<<c<<std::endl;
	if("inbox"==c){
		this->collection[counter][0]=0;
		this->collection[counter][1]=arg;
		++counter;
		return true;
	}
	else if("outbox"==c){
		this->collection[counter][0]=1;
		this->collection[counter][1]=arg;
		++counter;
		return true;
	}
	else if("add"==c){
		this->collection[counter][0]=2;
		this->collection[counter][1]=arg;
		++counter;
		return true;
	}
	else if("sub"==c){
		this->collection[counter][0]=3;
		this->collection[counter][1]=arg;
		++counter;
		return true;
	}
	else if("copyto"==c){
		this->collection[counter][0]=4;
		this->collection[counter][1]=arg;
		++counter;
		return true;
	}
	else if("copyfrom"==c){
		this->collection[counter][0]=5;
		this->collection[counter][1]=arg;
		++counter;
		return true;
	}
	else if("jump"==c){
		this->collection[counter][0]=6;
		this->collection[counter][1]=arg;
		++counter;
		return true;
	}
	else if("jumpifzero"==c){
		this->collection[counter][0]=7;
		this->collection[counter][1]=arg;
		++counter;
		return true;
	}
	else return false;
}

bool Command::setCounter(int a){
	if(a>=1) this->counter=a;
	else return false;
	return true;
}

int main(){
	int level_seq=0;
	std::cin>>level_seq;
	if(1==level_seq){//��1�� 
		std::cout<<"level 1!"<<std::endl;
		Level level;
		level.input_num=2;
		level.inputs[0]=1;
		level.inputs[1]=2;
		level.space_num=0;
		level.std_outputs[0]=1;
		level.std_outputs[1]=2;
	}
	else if(2==level_seq){//��2�� 
		//
	}
	else if(3==level_seq){//��3�� 
		//
	}
	else if(4==level_seq){//�Զ���ؿ� 
		//
	}
	else{//����Ƿ����� 
		std::cout<<"error level_seq"<<std::endl;
		return 1;
	}
	
	std::string filePath;//C:\Users\li_ha\Desktop\command.txt
	std::cin>>filePath;
	char temp[256]={0};
	strcpy(temp,filePath.c_str());
	std::ifstream commands(temp);
	char buffer[256]={0};
	Command* command=new Command();
	if(commands.is_open()){
		int time=0;
		while(!commands.eof()){//���ж�ָ��ļ����д��� 
			commands.getline(buffer,100);
			std::cout<<buffer<<std::endl;
			if(time!=0){
				if(!command->add_command(buffer)) return 3;
			}
			else command->setCounter(buffer[0]-48);
			time++;
		}
	}
	else{//������ 
		std::cout<<"noooooooo"<<std::endl;
		return 2;
	}
	commands.close();
	
	std::cout<<"......................"<<std::endl<<command->getCounter()<<std::endl;
	for(int i=0;i<command->getCounter();++i){
		std::cout<<command->collection[i][0]<<' '<<command->collection[i][1]<<std::endl;
	}
	
	return 0;
}
