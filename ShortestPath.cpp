// 最短路径.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ALGraph.h"

int main()
{
	ALGraph A(7);
	A.Creat();
	A.Dijkstra(1);
	A.Display();

    return 0;
}

