#ifndef ALGRAPH_H
#define ALGRAPH_H

#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

// �ض���߽ڵ㣬���ڲ���
typedef struct ArcNode *Position;

/* �߽ڵ�
 * ����Ԫ��:
 * adjvex:�����������Ľڵ�
 * Weight:������ߵ�Ȩ��
 * Next:�������ͷ�ڵ�������߽ڵ�
 */
struct ArcNode {
	int adjvex;
	int Weight;
	Position Next;
};

/* ����ڵ�
 * ����Ԫ��:
 * Name:�ýڵ��������
 * firstArc:�ö������ӵĵ�һ������ߣ�
 */
struct VexNode {
	int Name;
	Position firstArc;
};

/* ��ڵ�
 * ����Ԫ��:
 * Known:�ýڵ���״̬��
 * Dist:�ýڵ㵽Ŀ��ڵ����С���룻
 * Path:��С����ʱ�����ӵ���һ���ڵ㣻
 */
struct TNode {
	bool Known;
	int Dist;
	int Path;
};

/* ALGraph��
 * �ӿ�:
 * Creat:�������ܣ���ѡ���ڵ�֮�䴴������ߣ�
 * MakeEmpty:�ÿչ��ܣ������������ɾ������ʼ���������㣻
 * Unweighted:�����ܣ��ҳ�ѡ�����������������������Ȩ·����
 * Display:չʾ���ܣ�չʾ��ͼ��·����Ϣ��
 * Dijkstra:Dijkstra�㷨�����ڼ��㸳Ȩͼ���·��
 * WeightNegative:�����ܣ����ڼ�����и���ֵ��ͼ�����·��
 */
class ALGraph
{
public:
	// ���캯��
	ALGraph(int = 10);
	// ��������
	~ALGraph();

	// �ӿں���
	// ��������
	void Creat();
	void MakeEmpty();
	void Display();

	// ���·������
	void Unweighted(int);
	void Dijkstra(int);
	void WeightNegative(int);

private:
	// ��������
	void InitTable();

	// ���ݳ�Ա
	int VexNum; // ���涥����
	int ArcNum; // �������
	VexNode *AdjList; // �����ڽӱ�
	TNode *Table; // ��������
};


#endif // !ALGRAPH_H 


