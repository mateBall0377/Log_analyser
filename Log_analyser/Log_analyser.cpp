// Log_analyser.cpp: определяет точку входа для приложения.
//

#include "Log_analyser.h"


int main(int argc,char** argv)
{
	//Message msg("14:04:44 [DEBUG] [Module1] INFO");
	
	File ff("./test1.log");
	std::cout<<ff.get_badstat();

	return 0;
}
