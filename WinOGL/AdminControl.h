
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
	//頂点
	void SelectEdit(double x,double y);

	//図形を追加する
	void AppendShape();

	//交差判定をする
	bool CalcKousa(double x1,double y1,double x2,double y2);
	//他交差判定をする
	bool CalcTakousa(double x1,double y1);
	//内外判定をする
	bool CalcNaigai(double x,double y);

	CShape* CalcNaigai2(double x,double y);
	//内包判定をする
	bool CalcNaihou(double x,double y);

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

	//modeの判定
	void LButtonSwitch(double x,double y);

	void ChangeModeCreate();
	//Edit_modeへの切り替え
	void ChangeModeEdit();

private:
	CShape* shape_head;
	bool AxisFlag;
	CVertex* select_vertex;
	CShape* select_shape;
	int mode;
	int sab_mode;
};

