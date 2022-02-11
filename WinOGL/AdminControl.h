
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
	void SelectSubMode(double x,double y);
	//�`�󔻒�
	bool CheckShape();

	//�}�`��ǉ�����
	void AppendShape();

	//���Ȍ������������
	bool CalcKousa(double x1,double y1,double x2,double y2);
	bool CalcKousa(CShape* shape);
	bool CalcCopyKousa(CShape* shape);
	//���������������
	bool CalcTakousa(double x1,double y1);
	bool CalcTakousa(CShape* shape);
	//���O���������
	bool CalcNaigai(double x,double y);
	CShape* CalcNaigai2(double x,double y);
	bool CalcCopyNaigai(double x, double y, CShape* shape, int z);
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
	//�@���̌v�Z������
	double CalcHousen();
	//��Βl�̌v�Z������
	double CalcAbsoluteValue(double x);

	//�`��`��
	void DrawShape();

	//xyz����\������
	void DrawAxis();
	//AxisFlag�̐؂�ւ�
	void ChangeAxisFlag();
	bool GetAxisFlag();

	//�ʂ̕\��
	void DrawPolygon(CShape* shape);
	void Draw3DPolygon(CShape* shape);
	//PolygonFlag�̐؂�ւ�
	void ChangePolygonFlag();
	bool GetPolygonFlag();

	//���C�e�B���O�\��
	//ViewLightFlag�̐؂�ւ�
	void ChangeViewLightFlag();
	bool GetViewLightFlag();

	//View3DFlag�̐؂�ւ�
	void ChangeView3DFlag();
	bool GetView3DFlag();

	//LButtonDownFlag
	void SetLButtonDownFlag(bool x);
	bool GetLButtonDownFlag();
	//RButtonDownFlag
	void SetRButtonDownFlag(bool x);
	bool GetRButtonDownFlag();
	
	void LButtonDownSwitch(double x,double y);
	void LButtonUpSwitch(double x, double y);
	void MouseMoveSwitch(double x, double y);
	void LButtonDblClkSwitch(double x, double y);
	void RButtonDownSwitch(double x, double y);
	void RButtonUpSwitch(double x, double y);
	void MouseWheelSwitch(short zDelta);
	void KeyDownSwitch(UINT nChar);

	//Create_mode�ւ̐؂�ւ�
	void ChangeModeCreate();
	bool GetCreateModeFlag();
	//Edit_mode�ւ̐؂�ւ�
	void ChangeModeEdit();
	bool GetEditModeFlag();
	//Delete_mode�ւ̐؂�ւ�
	void ChangeModeDelete();
	bool GetDeleteModeFlag();
	//View_mode�ւ̐؂�ւ�
	void ChangeModeView();
	bool GetViewModeFlag();

	//���_�ύX�؂�ւ�
	void ChangeViewModeIdou();
	void ChangeViewModeKaiten();
	void ChangeViewModeKakudai();
	void ChangeViewModeSyukusyou();
	int GetViewMode();

	//shape�̕ۑ�
	void SaveBeforeShape();
	//before_shape�ɖ߂�
	void RedoShape();
	//�`��ۑ�
	void CopyShape(CShape* shape);

	//select_vertex�̍폜
	void DeleteSelectVertex();
	//���_�ǉ�
	void AddVertex(double x, double y);
	//�}�`�ړ�
	void MoveShape(double x,double y);
	//�}�`�g��E�k��
	void EXShape(short zDelta);
	//�}�`��]
	void RotateShape(double kiten_x, double kiten_y, short zDelta);
	//��_
	void SetKiten(double x, double y);
	double GetKiten_x();
	double GetKiten_y();
	//�I�����ꂽ�`����폜����
	void DeleteShape(double x,double y);
	//���_�ύX
	void ViewShape();
	//���s�ݒ�
	void ViewDepth();
	//���C�e�B���O�\��
	void ViewLight();

	//select_vertex��vertex_head���m�F����
	bool CheckSelectVertex();

	CVertex* CheckClickVertexLine(double x, double y, CShape* shape);

	//���̌`��̌���Ԃ�
	int CountShape();

	void FreeShape();

private:
	CShape* shape_head;

	bool AxisFlag;
	bool PolygonFlag;
	bool View3DFlag;
	bool ViewLightFlag;
	bool CreateModeFlag;
	bool EditModeFlag;
	bool DeleteModeFlag;
	bool ViewModeFlag;

	bool LButtonDownFlag;
	bool RButtonDownFlag;
	bool MoveErrorFlag;
	bool KitenFlag;

	CVertex* select_vertex;
	CVertex* before_select_vertex;
	CShape* select_shape;
	CShape* before_shape;
	CShape* copy_shape;
	double kiten_x;
	double kiten_y;
	int mode;
	int sub_mode;
	int view_mode;
	int view_hantei;
	int view_idou;
	int depth_hantei;
	double depth_idou;
	
};

