// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../Logger/Log.h"
#include "../WatchCore/Value.h"
#include <time.h>
#include <iostream>

int main()
{
	Integer aa = 6;
	Integer bb = aa;
	Integer cc;
	if (aa  > 10)
		cc = aa + bb;
	time_t tt = time(nullptr);

	char szTime[128];
	ctime_s(szTime, sizeof(szTime), &tt);
	std::cout << szTime << std::endl;

    return 0;
}
