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

	CVertex* GetVertexHead();

	//���_��ǉ�����
	void AppendVertex(double x, double y);

	//���̒��_����Ԃ�
	int CountVertex();

	CVertex* GetFirstVertex();

	void FreeVertex();

};

