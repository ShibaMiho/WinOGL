#include "pch.h"
#include "Shape.h"

CShape::CShape()
{
	vertex_head = NULL;
	next = NULL;
	depth = 0.0;
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

void CShape::SetVertexHead(CVertex* vertex)
{
	vertex_head = vertex;
}

CVertex* CShape::GetVertexHead()
{
	return vertex_head;
}

//頂点を追加する
void CShape::AppendVertex(double x, double y)
{
	CVertex* vertex = new CVertex();

	vertex->SetXY(x, y);
	vertex->SetNext(vertex_head);

	vertex_head = vertex;
}

//今の頂点数を返す
int CShape::CountVertex()
{
	int count = 0;
	for (CVertex* p = GetVertexHead(); p != NULL; p = p->GetNext()) {
		count++;
	}
	return count;
}

//初めの頂点を返す
CVertex* CShape::GetFirstVertex()
{
	CVertex* vertex=vertex_head;
	while (vertex->GetNext() != NULL) {
		vertex = vertex->GetNext();
	}
	return vertex;
}

void CShape::SetDepth(double new_depth)
{
	depth = new_depth;
}

double CShape::GetDepth()
{
	return depth;
}

void CShape::FreeVertex()
{
	while (vertex_head != NULL) {
		CVertex* p = vertex_head;
		vertex_head = vertex_head->GetNext();
		delete p;
	}
}

