
#pragma once
#include<gl/GL.h>
#include "Vertex.h"
#include "Shape.h"

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	
	void Draw();

	void CreateShape(double x,double y);

	//ê}å`Çí«â¡Ç∑ÇÈ
	void AppendShape();

	void FreeShape();

private:
	CShape* shape_head;
};

