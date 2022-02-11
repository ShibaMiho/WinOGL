#pragma once

#include "Vertex.h"

class CShape
{
private:
	CVertex* vertex_head;
	CShape* next;
	double depth;

public:
	CShape();
	~CShape();

	void SetNext(CShape* n);
	CShape* GetNext();

	void SetVertexHead(CVertex* vertex);
	CVertex* GetVertexHead();

	//頂点を追加する
	void AppendVertex(double x, double y);

	//今の頂点数を返す
	int CountVertex();

	//初めの頂点を返す
	CVertex* GetFirstVertex();

	//奥行設定
	void SetDepth(double new_depth);
	double GetDepth();

	void FreeVertex();

};

