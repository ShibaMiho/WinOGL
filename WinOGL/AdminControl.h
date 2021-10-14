
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

	//�}�`��ǉ�����
	void AppendShape();

	//�������������
	bool CalcKousa(double x1,double y1,double x2,double y2);

	bool CalcTakousa(double x1,double y1);

	double CalcVectorX(double x1,double x2);
	double CalcVectorY(double y1, double y2);

	//�O�ς̌v�Z������
	double CalcGaiseki(double a1,double b1,double a2,double b2);

	void FreeShape();

private:
	CShape* shape_head;
};

