
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
	void SelectSubMode(double x,double y);
	//形状判定
	bool CheckShape();

	//図形を追加する
	void AppendShape();

	//自己交差判定をする
	bool CalcKousa(double x1,double y1,double x2,double y2);
	bool CalcKousa(CShape* shape);
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

	//絶対値の計算をする
	double CalcAbsoluteValue(double x);

	//xyz軸を表示する
	void DrawAxis();
	//AxisFlagの切り替え
	void ChangeAxisFlag();
	//LButtonFlag
	void SetLButtonFlag(bool x);
	bool GetLButtonFlag();
	//RButtonFlag
	void SetRButtonFlag(bool x);
	bool GetRButtonFlag();
	
	void LButtonDownSwitch(double x,double y);
	void LButtonUpSwitch(double x, double y);
	void MouseMoveSwitch(double x, double y);
	void LButtonDblClkSwitch(double x, double y);
	void RButtonDownSwitch(double x, double y);
	void RButtonUpSwitch(double x, double y);
	void MouseWheelSwitch(short zDelta);

	//Create_modeへの切り替え
	void ChangeModeCreate();
	//Edit_modeへの切り替え
	void ChangeModeEdit();

	//shapeの保存
	void SaveBeforeShape();
	//before_shapeに戻す
	void RedoShape();

	//select_vertexの削除
	void DeleteSelectVertex();
	//頂点追加
	void AddVertex(double x, double y);
	//図形移動
	void MoveShape(double x,double y);
	//図形拡大・縮小
	void EXShape(short zDelta);

	//select_vertexがvertex_headか確認する
	bool CheckSelectVertex();

	CVertex* CheckClickVertexLine(double x, double y, CShape* shape);

	void FreeShape();

private:
	CShape* shape_head;
	bool AxisFlag;
	bool LButtonFlag;
	bool RButtonFlag;
	bool MoveErrorFlag;
	CVertex* select_vertex;
	CVertex* before_select_vertex;
	CShape* select_shape;
	CShape* before_shape;
	int mode;
	int sub_mode;
	
};

