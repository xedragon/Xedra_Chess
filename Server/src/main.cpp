// Design Mode.cpp: 定义应用程序的入口点。
//

#include <main.h>
#include "../config.h"
#include <libconfig\source\DataService.h>
#include <Facade.h>
using namespace std;

int main()
{
	Facade::getInstance().Start();
}
