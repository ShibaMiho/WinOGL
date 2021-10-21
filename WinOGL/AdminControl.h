
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

	//図形を追加する
	void AppendShape();

	//交差判定をする
	bool CalcKousa(double x1,double y1,double x2,double y2);
	//他交差判定をする
	bool CalcTakousa(double x1,double y1);
	//内包判定をする
	bool CalcNaihou(double x,double y);
	//内外判定をする
	//bool CalcNaigai(double x,double y);

	//ベクトルの計算をする
	double CalcVector(double x1,double x2);
	//内積の計算をする
	double CalcNaiseki(double a1, double a2, double b1, double b2);
	//外積の計算をする
	double CalcGaiseki(double a1, double a2, double b1, double b2);

	void FreeShape();

private:
	CShape* shape_head;
};

