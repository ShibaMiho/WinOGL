#pragma once

#include "Vertex.h"

class CShape
{
private:
	CVertex* vertex_head;
	CShape* next;

public:
	CShape();
	~CShape();

	void SetNext(CShape* n);
	CShape* GetNext();

	void SetVertexHead(CVertex* vertex);
	CVertex* GetVertexHead();

	//���_��ǉ�����
	void AppendVertex(double x, double y);

	//���̒��_����Ԃ�
	int CountVertex();

	//���߂̒��_��Ԃ�
	CVertex* GetFirstVertex();

	void FreeVertex();

};

