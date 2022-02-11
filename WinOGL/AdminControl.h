
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
	bool CalcCopyKousa(CShape* shape);
	//他交差判定をする
	bool CalcTakousa(double x1,double y1);
	bool CalcTakousa(CShape* shape);
	//内外判定をする
	bool CalcNaigai(double x,double y);
	CShape* CalcNaigai2(double x,double y);
	bool CalcCopyNaigai(double x, double y, CShape* shape, int z);
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
	//法線の計算をする
	double CalcHousen();
	//絶対値の計算をする
	double CalcAbsoluteValue(double x);

	//形状描画
	void DrawShape();

	//xyz軸を表示する
	void DrawAxis();
	//AxisFlagの切り替え
	void ChangeAxisFlag();
	bool GetAxisFlag();

	//面の表示
	void DrawPolygon(CShape* shape);
	void Draw3DPolygon(CShape* shape);
	//PolygonFlagの切り替え
	void ChangePolygonFlag();
	bool GetPolygonFlag();

	//ライティング表示
	//ViewLightFlagの切り替え
	void ChangeViewLightFlag();
	bool GetViewLightFlag();

	//View3DFlagの切り替え
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

	//Create_modeへの切り替え
	void ChangeModeCreate();
	bool GetCreateModeFlag();
	//Edit_modeへの切り替え
	void ChangeModeEdit();
	bool GetEditModeFlag();
	//Delete_modeへの切り替え
	void ChangeModeDelete();
	bool GetDeleteModeFlag();
	//View_modeへの切り替え
	void ChangeModeView();
	bool GetViewModeFlag();

	//視点変更切り替え
	void ChangeViewModeIdou();
	void ChangeViewModeKaiten();
	void ChangeViewModeKakudai();
	void ChangeViewModeSyukusyou();
	int GetViewMode();

	//shapeの保存
	void SaveBeforeShape();
	//before_shapeに戻す
	void RedoShape();
	//形状保存
	void CopyShape(CShape* shape);

	//select_vertexの削除
	void DeleteSelectVertex();
	//頂点追加
	void AddVertex(double x, double y);
	//図形移動
	void MoveShape(double x,double y);
	//図形拡大・縮小
	void EXShape(short zDelta);
	//図形回転
	void RotateShape(double kiten_x, double kiten_y, short zDelta);
	//基点
	void SetKiten(double x, double y);
	double GetKiten_x();
	double GetKiten_y();
	//選択された形状を削除する
	void DeleteShape(double x,double y);
	//視点変更
	void ViewShape();
	//奥行設定
	void ViewDepth();
	//ライティング表示
	void ViewLight();

	//select_vertexがvertex_headか確認する
	bool CheckSelectVertex();

	CVertex* CheckClickVertexLine(double x, double y, CShape* shape);

	//今の形状の個数を返す
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

