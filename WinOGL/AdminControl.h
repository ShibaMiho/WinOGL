
#pragma once
#include<gl/GL.h>
#include "Vertex.h"

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	
	void Draw();

private:
	CVertex* vertex_head = NULL;

public:
	void AppendVertex(double x,double y);

	void FreeVertex();
};

