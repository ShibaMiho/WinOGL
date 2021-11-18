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

	//’¸“_‚ğ’Ç‰Á‚·‚é
	void AppendVertex(double x, double y);

	//¡‚Ì’¸“_”‚ğ•Ô‚·
	int CountVertex();

	CVertex* GetFirstVertex();

	void FreeVertex();

};

