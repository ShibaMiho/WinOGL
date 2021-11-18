
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

	//図形を作る
	void CreateShape(double x,double y);
	//sub_modeの設定
	void SelectEdit(double x,double y);
	//形状判定
	bool CheckShape();

	//図形を追加する
	void AppendShape();

	//自己交差判定をする
	bool CalcKousa(double x1,double y1,double x2,double y2);
	bool CalcKousa(double x1, double y1, double x2, double y2, CShape* shape);
	//他交差判定をする
	bool CalcTakousa(double x1,double y1);
	bool CalcTakousa(CShape* shape);
	//内外判定をする
	bool CalcNaigai(double x,double y);
	CShape* CalcNaigai2(double x,double y);
	//内包判定をする
	bool CalcNaihou(double x,double y);
	bool CalcNaihou(CShape* shape);

	//1つ前の点と一緒か比較する
	bool CalcBeforeSame(double x,double y);

	//ベクトルの計算をする
	double CalcVector(double x1,double x2);
	//内積の計算をする
	double CalcNaiseki(double a1, double a2, double b1, double b2);
	//外積の計算をする
	double CalcGaiseki(double a1, double a2, double b1, double b2);

	void FreeShape();

	//xyz軸を表示する
	void DrawAxis();
	//AxisFlagの切り替え
	void ChangeAxisFlag();
	//LButtonFlag
	void SetLButtonFlag(bool x);
	bool GetLButtonFlag();

	//modeの判定
	void LButtonSwitch(double x,double y);
	void LButtonUpSwitch(double x, double y);

	//Create_modeへの切り替え
	void ChangeModeCreate();
	//Edit_modeへの切り替え
	void ChangeModeEdit();
	//modeの取得
	int GetMode();
	//sub_modeの取得
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

