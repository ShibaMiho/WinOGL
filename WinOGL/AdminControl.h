
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
	//sub_mode�̐ݒ�
	void SelectEdit(double x,double y);
	//�`�󔻒�
	bool CheckShape();

	//�}�`��ǉ�����
	void AppendShape();

	//���Ȍ������������
	bool CalcKousa(double x1,double y1,double x2,double y2);
	bool CalcKousa(double x1, double y1, double x2, double y2, CShape* shape);
	//���������������
	bool CalcTakousa(double x1,double y1);
	bool CalcTakousa(CShape* shape);
	//���O���������
	bool CalcNaigai(double x,double y);
	CShape* CalcNaigai2(double x,double y);
	//����������
	bool CalcNaihou(double x,double y);
	bool CalcNaihou(CShape* shape);

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
	//LButtonFlag
	void SetLButtonFlag(bool x);
	bool GetLButtonFlag();

	//mode�̔���
	void LButtonSwitch(double x,double y);
	void LButtonUpSwitch(double x, double y);

	//Create_mode�ւ̐؂�ւ�
	void ChangeModeCreate();
	//Edit_mode�ւ̐؂�ւ�
	void ChangeModeEdit();
	//mode�̎擾
	int GetMode();
	//sub_mode�̎擾
	int GetSubMode();

	void SetSubMode(int x);

	void SaveBeforeShape();
	void RedoShape();

	bool CheckSelectVertex();

private:
	CShape* shape_head;
	bool AxisFlag;
	bool LButtonFlag;
	CVertex* select_vertex;
	CVertex* before_select_vertex;
	CShape* select_shape;
	CShape* before_shape;
	int mode;
	int sub_mode;
	
};

