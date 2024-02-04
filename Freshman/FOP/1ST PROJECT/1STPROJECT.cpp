#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdlib.h>

class Level {
public:
	int input_num, input_index;
	int inputs[100];
	int space_num;//表示关卡中空格数
	int space[8];
	bool avliable_space[8];//表示有积木的空格
	bool avliable_command[8];//8位数组 表示每位对应的指令集是否可用
	int output_index;
	int outputs[100];
	int std_outputs[100];
	bool pass();
};

bool Level::pass() {
	for (int i = 0; i < 100; ++i) if (outputs[i] != std_outputs[i]) return false;
	return true;
}

class Command {
private:
	int counter,counter_p;//表示玩家一共输入了多少行指令集
public:
	Command() { this->counter = this->counter_p = 0; for (int i = 0; i < 100; ++i) collection[i][0] = collection[i][1] = 0; };

	int collection[100][2];//第一位表示指令 第二位表示可能的指令参数，没有则用-1代替 
	bool add_command(std::string);
	bool setCounter(int);
	int getCounter() { return this->counter; };
};

bool Command::add_command(std::string a) {
	if ("" == a) return false;
	std::istringstream convert(a);
	std::string c;
	convert >> c;
	float ar = -1;
	int arg = -1;
	if (convert) convert >> ar;
	if (ar == int(ar) * 1.0) arg = ar;
	else return false;
	if ("inbox" == c) {
		this->collection[counter_p][0] = 0;
		this->collection[counter_p][1] = arg;
		++counter_p;
		return true;
	}
	else if ("outbox" == c) {
		this->collection[counter_p][0] = 1;
		this->collection[counter_p][1] = arg;
		++counter_p;
		return true;
	}
	else if ("add" == c) {
		this->collection[counter_p][0] = 2;
		this->collection[counter_p][1] = arg;
		++counter_p;
		return true;
	}
	else if ("sub" == c) {
		this->collection[counter_p][0] = 3;
		this->collection[counter_p][1] = arg;
		++counter_p;
		return true;
	}
	else if ("copyto" == c) {
		this->collection[counter_p][0] = 4;
		this->collection[counter_p][1] = arg;
		++counter_p;
		return true;
	}
	else if ("copyfrom" == c) {
		this->collection[counter_p][0] = 5;
		this->collection[counter_p][1] = arg;
		++counter_p;
		return true;
	}
	else if ("jump" == c) {
		this->collection[counter_p][0] = 6;
		this->collection[counter_p][1] = arg;
		++counter_p;
		return true;
	}
	else if ("jumpifzero" == c) {
		this->collection[counter_p][0] = 7;
		this->collection[counter_p][1] = arg;
		++counter_p;
		return true;
	}
	else return false;
}

bool Command::setCounter(int a) {
	if (a >= 1) this->counter = a;
	else return false;
	return true;
}

class Robot {
private:
	int boxInHand;
	bool hasBoxInHand;
public:
	Robot() { boxInHand = 0; hasBoxInHand = false; };
	int inbox(Level*);
	bool outbox(Level*);
	bool add(Level, int);
	bool sub(Level, int);
	bool copyto(Level*, int);
	bool copyfrom(Level, int);
	int jump(Command, int);//返回目标的行数 error为-1
	int jumpifzero(Command, int);//返回目标的行数 error为-1 不操作为-2
	int executeCommmands(Level*, Command);
};

int Robot::inbox(Level* level) {
	if (level->input_index >= level->input_num) return -1;
	if (level->input_index >= level->input_num) return 0;
	boxInHand = level->inputs[level->input_index];
	++level->input_index;
	hasBoxInHand = true;
	return 1;
}

bool Robot::outbox(Level* level) {
	if (!hasBoxInHand) return false;
	else {
		level->outputs[level->output_index] = boxInHand;
		++level->output_index;
		hasBoxInHand = false;
		return true;
	}
}

bool Robot::add(Level level, int spaceIndex) {
	if (!hasBoxInHand) return false;
	else if (!level.avliable_space[spaceIndex]) return false;
	else if (spaceIndex >= level.space_num) return false;
	else {
		boxInHand += level.space[spaceIndex];
		return true;
	}
}

bool Robot::sub(Level level, int spaceIndex) {
	if (!hasBoxInHand) return false;
	else if (!level.avliable_space[spaceIndex]) return false;
	else if (spaceIndex >= level.space_num) return false;
	else {
		boxInHand -= level.space[spaceIndex];
		return true;
	}
}

bool Robot::copyto(Level* level, int spaceIndex) {
	if (!hasBoxInHand) return false;
	else if (spaceIndex >= level->space_num) return false;
	else {
		level->avliable_space[spaceIndex] = true;
		level->space[spaceIndex] = boxInHand;
		return true;
		//hasBoxInHand = false;因为是将手中积木复制到目标空地，所以不用将hasBoxInHand设置为false
	}
}

bool Robot::copyfrom(Level level, int spaceIndex) {
	if (!level.avliable_space[spaceIndex]) return false;
	else if (spaceIndex >= level.space_num) return false;
	else {
		hasBoxInHand = true;
		boxInHand = level.space[spaceIndex];
		return true;
	}
}

int Robot::jump(Command command, int targetLine) {
	if (targetLine <= command.getCounter() && targetLine >= 1) {
		//std::cout << "jump to Line " << targetLine << std::endl;
		return targetLine - 1;
	}
	else return -1;
}

int Robot::jumpifzero(Command command, int targetLine) {
	if (targetLine <= command.getCounter() && targetLine >= 1 && hasBoxInHand) {
		if (0 == boxInHand) return targetLine - 1;
		else return -2;
	}
	else return - 1;
}

int Robot::executeCommmands(Level* level, Command command){//完成对指令集在本关是否可用的校验 并执行
	int i = 0;
	bool flag = true;
	while (i < command.getCounter() && flag) {
		//std::cout << "i=" << i << std::endl;
		switch (command.collection[i][0])
		{
		case 0: {
			int temp = inbox(level);
			if (!level->avliable_command[0] || 0 == temp) return i;
			else if (-1 == temp) flag = false;
			//std::cout << "inbox" << std::endl;
			break;
		}
		case 1:
			if (!level->avliable_command[1] || !outbox(level)) return i;
			//std::cout << "outbox" << std::endl;
			break;
		case 2:
			if (!level->avliable_command[2] || !add(*level, command.collection[i][1])) return i;
			//std::cout << "add" << std::endl;
			break;
		case 3:
			if (!level->avliable_command[3] || !sub(*level, command.collection[i][1])) return i;
			//std::cout << "sub" << std::endl;
			break;
		case 4:
			if (!level->avliable_command[4] || !copyto(level, command.collection[i][1])) return i;
			//std::cout << "copyto" << std::endl;
			break;
		case 5:
			if (!level->avliable_command[5] || !copyfrom(*level, command.collection[i][1])) return i;
			//std::cout << "copyfrom" << std::endl;
			break;
		case 6: {
			int temp = jump(command, command.collection[i][1]);
			if (-1 == temp || !level->avliable_command[6]) return i;
			else i = temp - 1;
			//std::cout << "jump" << std::endl;
			break;
		}
		case 7: {
			int temp = jumpifzero(command, command.collection[i][1]);
			if (-1 == temp || !level->avliable_command[7]) return i;
			else if (-2 != temp) i = temp - 1;
			//std::cout << "jumpifzero" << std::endl;
			break;
		}
		default:
			break;
		}
		++i;
	}
	return -1;
}

int main() {
	int level_seq = 0;
	std::string s_temp;
	getline(std::cin, s_temp);
	//std::cout << "s_temp= " << s_temp << std::endl;
	level_seq = atoi(s_temp.c_str());
	std::cin.clear();

	Level level;
	for (int i = 0; i < 100; ++i) level.inputs[i] = level.outputs[i] = level.std_outputs[i] = 0;
	for (int i = 0; i < 8; ++i) level.avliable_command[i] = level.space[i] = level.avliable_space[i] = 0;
	level.input_index = level.output_index = 0;

	if (1 == level_seq) {//第1关 
		//std::cout << "level 1!" << std::endl;
		level.input_num = 2;
		level.inputs[0] = 1;
		level.inputs[1] = 2;
		level.space_num = 0;
		level.std_outputs[0] = 1;
		level.std_outputs[1] = 2;
		level.avliable_command[0] = level.avliable_command[1] = true;
	}
	else if (2 == level_seq) {//第2关 
		//std::cout << "level 2!" << std::endl;
		level.input_num = 8;
		level.inputs[0] = 3;
		level.inputs[1] = 9;
		level.inputs[2] = 5;
		level.inputs[3] = 1;
		level.inputs[4] = -2;
		level.inputs[5] = -2;
		level.inputs[6] = 9;
		level.inputs[7] = -9;
		level.space_num = 3;
		level.std_outputs[0] = -6;
		level.std_outputs[1] = 6;
		level.std_outputs[2] = 4;
		level.std_outputs[3] = -4;
		level.std_outputs[4] = 0;
		level.std_outputs[5] = 0;
		level.std_outputs[6] = 18;
		level.std_outputs[7] = -18;
		for (int i = 0; i < 8; ++i) level.avliable_command[i] = true;
	}
	else if (3 == level_seq) {//第3关 
		//std::cout << "level 3!" << std::endl;
		level.input_num = 8;
		level.inputs[0] = 6;
		level.inputs[1] = 2;
		level.inputs[2] = 7;
		level.inputs[3] = 7;
		level.inputs[4] = -9;
		level.inputs[5] = 3;
		level.inputs[6] = -3;
		level.inputs[7] = -3;
		level.space_num = 3;
		level.std_outputs[0] = 7;
		level.std_outputs[1] = -3;
		for (int i = 0; i < 8; ++i) level.avliable_command[i] = true;
	}
	else if (4 == level_seq) {//自定义关卡 
		//
	}
	else {//处理非法输入 
		//std::cout << "error level_seq" << std::endl;
		return 1;
	}

	int m;
	std::string m_temp;
	getline(std::cin, m_temp);
	//std::cout << "m_temp= " << m_temp << std::endl;
	m = atoi(m_temp.c_str());
	std::cin.clear();
	Command* command = new Command();
	command->setCounter(m);
	std::string* cs = new std::string[m];
	for (int i = 0; i < m; ++i) {
		getline(std::cin, cs[i]);
		std::cin.clear();
		//std::cout << "cs[i]= " << cs[i] << std::endl;
	}
	for (int i = 0; i < m; ++i) {
		bool f = command->add_command(cs[i]);
		if (!f) {
			std::cout << "Error on instruction " << i + 1 << std::endl;
			return 3;
		}
	}

	/*std::cout << "...................................." << std::endl << command->getCounter() << std::endl;
	for (int i = 0; i < command->getCounter(); ++i) {
		std::cout << command->collection[i][0] << ' ' << command->collection[i][1] << std::endl;
	}
	std::cout << "...................................." << std::endl;*/

	Robot* robot = new Robot();
	int result = robot->executeCommmands(&level, *command);
	if (-1 != result) {
		std::cout << "Error on instruction " << result + 1 << std::endl;
		return 2;
	}

	//std::cout << "inbox	outbox	standard answer" << std::endl;
	/*for (int i = 0; i < level.output_index; ++i) {
		std::cout << level.inputs[i] << '	' << level.outputs[i] << '	' << level.std_outputs[i] << std::endl;
	}*/
	if (level.pass()) std::cout << "Success" << std::endl;
	else std::cout << "Fail" << std::endl;

	return 0;
}