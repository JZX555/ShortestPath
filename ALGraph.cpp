#include "stdafx.h"
#include "ALGraph.h"


/* ���캯��:��ʼ������
 * ����ֵ:��
 * ����:vnum:ͼ����Ҫ�Ķ�����
 */
ALGraph::ALGraph(int vnum)
: VexNum(vnum), ArcNum(0){
	// �����ڽӱ�
	AdjList = new VexNode[VexNum + 1];
	// ��������
	Table = new TNode[VexNum + 1];

	// �ж��Ƿ�����ɹ�
	if (AdjList == NULL || Table == NULL)
		cout << "�ڽӱ�����ʧ��!" << endl;

	else {
		for (int i = 0; i < VexNum + 1; i++) {
			// ��ʼ���ڽӱ�
			AdjList[i].Name = i;
			AdjList[i].firstArc = NULL;

			// ��ʼ�������
			Table[i].Dist = INT_MAX;
			Table[i].Known = false;
			Table[i].Path = 0;
		}
	}
	
}

/* ��������:��������ʱ���մ���ռ�
 * ����ֵ:��
 * ����:��
 */
ALGraph::~ALGraph()
{
	// �ÿ����б�
	MakeEmpty();

	// ɾ���ڽӱ�
	delete AdjList;
	AdjList = NULL;

	// ɾ�������
	delete Table;
	Table = NULL;
}

/* ��������:��ָ���Ķ���֮�䴴�������
 * ����ֵ:��
 * ����:��
 */
void ALGraph::Creat() {
	// ����˴δ����ı���
	// �����µ��ܱ�����
	int tmp;
	cout << "������Ҫ�����ı���:";
	cin >> tmp;
	ArcNum += tmp;

	// ���������µ������
	for (int i = 0; i < tmp; i++) {
		// v:����ߵ�ͷ���
		// w:����ߵ�β�ڵ�
		// weight:����ߵ�Ȩֵ
		int v, w, weight;
		cout << "������Ҫ��������ߵ���������(v,w): ";
		cin >> v >> w;
		cout << "��������Ȩֵ:";
		cin >> weight;

		// �����µĽ׶�
		Position P = new ArcNode();
		if (P == NULL) {
			cout << "����ߴ���ʧ��!" << endl;
			return;
		}

		// ���½ڵ���Ϣ
		P->adjvex = w;
		P->Weight = weight;
		P->Next = AdjList[v].firstArc;

		// ���ӵ��ڽӱ���
		AdjList[v].firstArc = P;
	}

}

/* ��ʼ������:��ʼ�������
 * ����ֵ:��
 * ����:��
 */
void ALGraph::InitTable() {
	// ���������
	for (int i = 0; i < VexNum + 1; i++) {
		// ��ʼ������
		Table[i].Dist = INT_MAX;
		Table[i].Known = false;
		Table[i].Path = 0;
	}
}

/* �ÿպ���:�����е�������ÿ�
 * ����ֵ:��
 * ����:��
 */
void ALGraph::MakeEmpty() {
	// ��ʱ�����м�ڵ�
	Position P;

	// �����ڽӱ�
	for (int i = 1; i < VexNum + 1; i++) {
		P = AdjList[i].firstArc;

		// �����������ӵı�
		while (P != NULL) {
			AdjList[i].firstArc = P->Next;
			delete P;
			P = AdjList[i].firstArc;
		}
	}
}

/* ������:�ҳ�ָ���ڵ���������ڵ�������Ȩ·��
 * ����ֵ:��
 * ����:Start:��Ҫ���в��ҵĽڵ�
 */
void ALGraph::Unweighted(int Start) {
	// Q:������У����ڴ���UnKnown�ڵ�
	// v:����ߵ�ͷ���
	// w:����ߵ�β�ڵ�
	queue <int> Q;
	int v, w;
	
	// ��ʼ�������
	InitTable();

	// ��ʼ�ڵ����Ϊ0����ѹ�����
	Table[Start].Dist = 0;
	Q.push(Start);

	while (!Q.empty()) {
		// ��ȡ����Ԫ�أ���ɾ��
		v = Q.front();
		Q.pop();

		// �ýڵ���֪��������Ҫʹ��
		Table[v].Known = true;

		// ���������Ըýڵ�Ϊͷ���������
		Position P = AdjList[v].firstArc;
		while (P != NULL) {
			// ��ȡβ�ڵ�
			w = P->adjvex;
			// �ж�β�ڵ��Ƿ���Ҫ����
			if (Table[w].Dist == INT_MAX) {
				// ������Ϣ
				Table[w].Dist = Table[v].Dist + 1;
				Table[w].Path = v;
				// ����ѹ�����
				Q.push(w);
			}

			// ���������λ��
			P = P->Next;
		}
	}
}

/* չʾ����:չʾ��ͼ��·����Ϣ
 * ����ֵ:��
 * ����:��
 */
void ALGraph::Display() {
	for (int i = 1; i < VexNum + 1; i++)
		cout << "Vex: " << i << "  ;Dist: " << Table[i].Dist << "  ; Path: " << Table[i].Path << endl;
}

/* Dijkstra�㷨:�Ը�Ȩͼ���е�Դ���·������
 * ����ֵ:��
 * ����:Start:�����㷨��ʼ����
 */
void ALGraph::Dijkstra(int Start) {
	// v:�����������ʼ�ڵ�
	// w:�����������ֵ�ڵ�
	int v, w;

	// ��ʼ�������
	InitTable();
	Table[Start].Dist = 0;

	// �������б�
	while (true) {
		// Min:�����ж��Ƿ���Ҫ����ִ���㷨
		int Min = INT_MAX;

		// �ر�ע��:
		//     �˴�Ѱ����С�ڵ�ʹ�õķ��������Լ�Ϊ�˷���ֱ��д�ģ����
		// �����ַ�����ʱ�临�Ӷ�Ӧ�ñȽϸߣ��ﲻ��O(N * logN)��Ҫ����
		// ����ȷ�ķ���Ӧ���ǰ�ÿ�����봢�������ȶ����У�
		//     ��Ȼ��ʹ�ò�ͬ�����ȶ���Ҳ���в�ͬ��Ч����������˵����ʱ
		// �临�Ӷ�: 
		//     쳲�������(O(E + V * logV)) < ��Զ�(O(E * logV)) < �����(O(E * logV + V * logV))

		// Ѱ����С�ģ��һ�δȷ���������
		// ������ͷ�����Ϊ���ε���ʼ�ڵ�
		for (int i = 1; i < VexNum + 1; i++)
			if (Table[i].Known == false && Min > Table[i].Dist) {
				v = i;
				Min = Table[i].Dist;
			}

		// ��ʼ�ڵ���֪�������ٲ�������
		Table[v].Known = true;

		// �㷨�˳�����
		if (Min == INT_MAX)
			break;

		// ���������Ը���ʼ�ڵ�Ϊͷ���������
		Position P = AdjList[v].firstArc;
		while (P != NULL) {
			w = P->adjvex;
			// �ж�β�ڵ��Ƿ���֪
			if(Table[w].Known == false)
				if (Table[w].Dist > Table[v].Dist + P->Weight) {
					// ����·��������
					Table[w].Path = v;
					Table[w].Dist = Table[v].Dist + P->Weight;
				}

			// ָ����һ���ڵ�
			P = P->Next;
		}
	}
}

/* ������:���ڼ�����и���ֵ��ͼ�����·��
 * ����ֵ:��
 * ����:Start:�������ʼ�ڵ�
 */
void ALGraph::WeightNegative(int Start) {
	// Q:���ڴ���ڵ����
	// v:�����������ʼ�ڵ�
	// w:�����������ֹ�ڵ�
	queue <int> Q;
	int v, w;

	// ��ʼ�������
	InitTable();
	Table[Start].Dist = 0;
	Table[Start].Known = true;
	// ����ʼ�ڵ�ѹ�����
	Q.push(Start);

	// ��������·��
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		Table[v].Known = false; // �˴�״̬��ʾû���ڶ�����

		// ���������Ѹýڵ�Ϊͷ���������
		Position P = AdjList[v].firstArc;
		while (P != NULL) {
			w = P->adjvex;

			// ����·������
			if (Table[w].Dist > Table[v].Dist + P->Weight) {
				Table[w].Dist = Table[v].Dist + P->Weight;
				Table[w].Path = v;
				// �����ڶ����У���ѹ�����
				if (Table[w].Known = false)
					Q.push(w);
			}
		}
	}
}