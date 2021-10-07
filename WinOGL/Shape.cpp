#include "pch.h"
#include "Shape.h"

CShape::CShape()
{
	vertex_head = NULL;
	next = NULL;
}

CShape::~CShape()
{
	FreeVertex();
}

void CShape::SetNext(CShape* n)
{
	next = n;
}

CShape* CShape::GetNext()
{
	return next;
}

CVertex* CShape::GetVertexHead()
{
	return vertex_head;
}



void CShape::AppendVertex(double x, double y)
{
	CVertex* vertex = new CVertex();

	vertex->SetXY(x, y);
	vertex->SetNext(vertex_head);

	vertex_head = vertex;
}

void CShape::FreeVertex()
{
	while (vertex_head != NULL) {
		CVertex* p = vertex_head;
		vertex_head = vertex_head->GetNext();
		delete p;
	}
}

