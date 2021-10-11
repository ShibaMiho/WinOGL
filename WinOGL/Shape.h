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

	//’¸“_‚ð’Ç‰Á‚·‚é
	void AppendVertex(double x, double y);

	void FreeVertex();

};

