#ifndef __EXAMPLE__
#define __EXAMPLE__
	
class Example {
		
private:
	
	static int count;
	int id = 0;
	int _data;
			
public:
	
	Example(int data);
	void getData();
	~Example();

};
		
#endif
