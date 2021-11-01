
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

	//�}�`�����
	void CreateShape(double x,double y);
	//���_
	void SelectEdit(double x,double y);

	//�}�`��ǉ�����
	void AppendShape();

	//�������������
	bool CalcKousa(double x1,double y1,double x2,double y2);
	//���������������
	bool CalcTakousa(double x1,double y1);
	//���O���������
	bool CalcNaigai(double x,double y);

	CShape* CalcNaigai2(double x,double y);
	//����������
	bool CalcNaihou(double x,double y);

	//1�O�̓_�ƈꏏ����r����
	bool CalcBeforeSame(double x,double y);

	//�x�N�g���̌v�Z������
	double CalcVector(double x1,double x2);
	//���ς̌v�Z������
	double CalcNaiseki(double a1, double a2, double b1, double b2);
	//�O�ς̌v�Z������
	double CalcGaiseki(double a1, double a2, double b1, double b2);

	void FreeShape();

	//xyz����\������
	void DrawAxis();
	//AxisFlag�̐؂�ւ�
	void ChangeAxisFlag();

	//mode�̔���
	void LButtonSwitch(double x,double y);

	void ChangeModeCreate();
	//Edit_mode�ւ̐؂�ւ�
	void ChangeModeEdit();

private:
	CShape* shape_head;
	bool AxisFlag;
	CVertex* select_vertex;
	CShape* select_shape;
	int mode;
	int sab_mode;
};

