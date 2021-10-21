
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
	//���������������
	bool CalcTakousa(double x1,double y1);
	//����������
	bool CalcNaihou(double x,double y);
	//���O���������
	//bool CalcNaigai(double x,double y);

	//�x�N�g���̌v�Z������
	double CalcVector(double x1,double x2);
	//���ς̌v�Z������
	double CalcNaiseki(double a1, double a2, double b1, double b2);
	//�O�ς̌v�Z������
	double CalcGaiseki(double a1, double a2, double b1, double b2);

	void FreeShape();

private:
	CShape* shape_head;
};

