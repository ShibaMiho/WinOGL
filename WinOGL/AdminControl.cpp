
#include "pch.h"
#include "AdminControl.h"

#define _USE_MATH_DEFINES
#define ID_CREATE_MODE 1
#define ID_EDIT_MODE 2

#define POINT_SELECT 1
#define SHAPE_SELECT 2
#define LINE_SELECT 3

#include<math.h>


CAdminControl::CAdminControl()
{
	shape_head = new CShape();
	AxisFlag = false;
	LButtonFlag = false;
	RButtonFlag = false;
	MoveErrorFlag = false;
	select_vertex = NULL;
	before_select_vertex = NULL;
	select_shape = NULL;
	before_shape = NULL;
	mode = ID_CREATE_MODE;
	sub_mode = NULL;
}

CAdminControl::~CAdminControl()
{
	FreeShape();
	delete before_shape;
}


void CAdminControl::Draw()
{
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(6);

	for (CShape* s = shape_head; s != NULL; s = s->GetNext()) {
		glBegin(GL_POINTS);		//頂点描画
		for (CVertex* p = s->GetVertexHead(); p != NULL; p = p->GetNext()) {
			glVertex2f(p->GetX(), p->GetY());
		}
		glEnd();

		glBegin(GL_LINE_STRIP);		//線描画
		for (CVertex* p = s->GetVertexHead(); p != NULL; p = p->GetNext()) {
			glVertex2f(p->GetX(), p->GetY());
		}
		glEnd();
	}

	if (mode == ID_EDIT_MODE) {

		if (sub_mode == POINT_SELECT) {
			glColor3f(0.0, 1.0, 0.0);
			glPointSize(9);

			glBegin(GL_POINTS);		//頂点描画
			glVertex2f(select_vertex->GetX(), select_vertex->GetY());
			glEnd();

			if (MoveErrorFlag == true) {
				glColor3f(1.0, 0.0, 0.0);	//赤
				glPointSize(9);

				glBegin(GL_POINTS);		//頂点描画
				glVertex2f(select_vertex->GetX(), select_vertex->GetY());
				glEnd();

			}
		}

		if (sub_mode == SHAPE_SELECT) {
			glColor3f(0.0, 1.0, 0.0);
			glPointSize(9);

			glBegin(GL_POINTS);
			for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
				glVertex2f(p->GetX(), p->GetY());
			}
			glEnd();
			glBegin(GL_LINE_STRIP);
			for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
				glVertex2f(p->GetX(), p->GetY());
			}
			glEnd();

			if (MoveErrorFlag == true) {
				glColor3f(1.0, 0.0, 0.0);	//赤
				glPointSize(9);

				glBegin(GL_POINTS);
				for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
					glVertex2f(p->GetX(), p->GetY());
				}
				glEnd();
				glBegin(GL_LINE_STRIP);
				for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
					glVertex2f(p->GetX(), p->GetY());
				}
				glEnd();
			}
		}

		if (sub_mode == LINE_SELECT) {
			glColor3f(0.0, 1.0, 0.0);
			glPointSize(9);

			glBegin(GL_LINE_STRIP);
			glVertex2f(select_vertex->GetX(), select_vertex->GetY());
			glVertex2f(select_vertex->GetNext()->GetX(), select_vertex->GetNext()->GetY());
			glEnd();
		}

	}
	
	//AxisFlagがtrueのとき座標軸を描画する
	if (AxisFlag) {
		DrawAxis();
	}
	
}

void CAdminControl::CreateShape(double x, double y)
{
	CVertex* vertex = shape_head->GetVertexHead();
	
	if (CalcBeforeSame(x, y) == false) {

		//頂点が3点以上あった場合
		if (shape_head->CountVertex() >= 3) {

			//打たれた点が初めの点とほぼ一緒の時
			double sa_x = x - shape_head->GetFirstVertex()->GetX();
			double sa_y = y - shape_head->GetFirstVertex()->GetY();
			
			sa_x = CalcAbsoluteValue(sa_x);
			sa_y = CalcAbsoluteValue(sa_y);

			if (sa_x <= 0.03 && sa_y <= 0.03) {
				x = shape_head->GetFirstVertex()->GetX();
				y = shape_head->GetFirstVertex()->GetY();
			}

			if (CalcKousa(x, y, vertex->GetX(), vertex->GetY()) == false) {
				if (CalcTakousa(x, y) == false) {
					if (CalcNaihou(x, y) == false) {
						//交差、他交差、内包していない場合

						CVertex* p = shape_head->GetFirstVertex();

						double p_x = p->GetX() - x;
						double p_y = p->GetY() - y;

						p_x = CalcAbsoluteValue(p_x);
						p_y = CalcAbsoluteValue(p_y);

						if (p_x <= 0.05 && p_y <= 0.05) {
							shape_head->AppendVertex(p->GetX(), p->GetY());
							AppendShape();
						}
						else {
							shape_head->AppendVertex(x, y);
						}
					}
				}
			}

		}
		//頂点が1点以上あった場合
		else if (shape_head->CountVertex() >= 1) {
			if (CalcTakousa(x, y) == false) {
				//他交差していない場合
				shape_head->AppendVertex(x, y);
			}
		}
		//頂点が0点の場合
		else {
			if (CalcNaigai(x, y) == false) {
				//内外していない場合
				shape_head->AppendVertex(x, y);
			}
		}
	}
}

//sub_modeの設定
void CAdminControl::SelectSubMode(double x, double y)
{
	sub_mode = NULL;
	double x1 = 0.0;
	double y1 = 0.0;
	double sa_x = 0.0;
	double sa_y = 0.0;

	CVertex* vertex1 = NULL;

	for (CShape* shape = shape_head->GetNext(); shape!= NULL; shape = shape->GetNext()) {
		//頂点の選択判定
		CVertex* vertex = shape->GetVertexHead();
		while (vertex != NULL) {
			x1 = vertex->GetX();
			y1 = vertex->GetY();

			sa_x = CalcAbsoluteValue(x - x1);
			sa_y = CalcAbsoluteValue(y - y1);

			if (sa_x < 0.01 && sa_y < 0.01) {
				select_shape = shape;
				select_vertex = vertex;
				sub_mode = POINT_SELECT;
				break;
			}
			vertex = vertex->GetNext();
		}

		//稜線の選択判定
		if (sub_mode == NULL) {
			vertex1 = CheckClickVertexLine(x, y, shape);
			if (vertex1 != NULL) {
				select_vertex = vertex1;
				select_shape = shape;
				sub_mode = LINE_SELECT;
			}
		}

		//図形の選択
		if (sub_mode == NULL) {
			CShape* shape_naigai = CalcNaigai2(x, y);
			if (shape == shape_naigai) {
				sub_mode = SHAPE_SELECT;
				select_shape = shape;
			}
		}
		
	}
}

//形状判定
bool CAdminControl::CheckShape()
{
	bool hantei = NULL;

	for (CShape* shape = shape_head->GetNext(); shape != NULL; shape = shape->GetNext()) {
		CVertex* vertex = shape->GetVertexHead();
		if (CalcKousa(shape) == true) {
			hantei = false;
			return false;
			break;
		}
		if (hantei == NULL) {
			if (CalcTakousa(shape) == true) {
				hantei = false;
				return false;
				break;
			}
		}
		if (hantei == NULL) {
			if (CalcNaihou(shape) == true) {
				hantei = false;
				return false;
				break;
			}
		}
	}
	if (hantei == NULL) {
		return true;
	}
}

//図形を追加する
void CAdminControl::AppendShape()
{
	CShape* shape = new CShape();

	shape->SetNext(shape_head);

	shape_head = shape;
}

//自己交差判定をする
bool CAdminControl::CalcKousa(double x1, double y1, double x2, double y2)
{
	CVertex* p = shape_head->GetVertexHead()->GetNext();
	while (p->GetNext() != NULL) {

		double x3 = p->GetX();
		double y3 = p->GetY();

		p = p->GetNext();
		double x4 = p->GetX();
		double y4 = p->GetY();

		double a_x = CalcVector(x1, x2);
		double a_y = CalcVector(y1, y2);

		double a1_x = CalcVector(x4, x2);
		double a1_y = CalcVector(y4, y2);

		double a2_x = CalcVector(x3, x2);
		double a2_y = CalcVector(y3, y2);

		double b_x = CalcVector(x3, x4);
		double b_y = CalcVector(y3, y4);

		double b1_x = CalcVector(x2, x4);
		double b1_y = CalcVector(y2, y4);

		double b2_x = CalcVector(x1, x4);
		double b2_y = CalcVector(y1, y4);

		double ca1 = CalcGaiseki(a_x, a_y, a1_x, a1_y);
		double ca2 = CalcGaiseki(a_x, a_y, a2_x, a2_y);
		double cb1 = CalcGaiseki(b_x, b_y, b1_x, b1_y);
		double cb2 = CalcGaiseki(b_x, b_y, b2_x, b2_y);

		if (ca1 * ca2 < 0 && cb1 * cb2 < 0) {
			//交差する時
			return true;
		}
		
	}
	return false;
}

bool CAdminControl::CalcKousa(CShape* shape)
{
	CVertex* p1 = shape->GetVertexHead();
	if(shape->CountVertex() >= 4){
		while (p1->GetNext() != NULL) {
			double x1 = p1->GetX();
			double y1 = p1->GetY();

			p1 = p1->GetNext();
			double x2 = p1->GetX();
			double y2 = p1->GetY();

			CVertex* p2 = shape->GetVertexHead()->GetNext()->GetNext();
			while (p2->GetNext() != NULL) {
				double x3 = p2->GetX();
				double y3 = p2->GetY();

				p2 = p2->GetNext();
				double x4 = p2->GetX();
				double y4 = p2->GetY();

				double a_x = CalcVector(x1, x2);
				double a_y = CalcVector(y1, y2);

				double a1_x = CalcVector(x4, x2);
				double a1_y = CalcVector(y4, y2);

				double a2_x = CalcVector(x3, x2);
				double a2_y = CalcVector(y3, y2);

				double b_x = CalcVector(x3, x4);
				double b_y = CalcVector(y3, y4);

				double b1_x = CalcVector(x2, x4);
				double b1_y = CalcVector(y2, y4);

				double b2_x = CalcVector(x1, x4);
				double b2_y = CalcVector(y1, y4);

				double ca1 = CalcGaiseki(a_x, a_y, a1_x, a1_y);
				double ca2 = CalcGaiseki(a_x, a_y, a2_x, a2_y);
				double cb1 = CalcGaiseki(b_x, b_y, b1_x, b1_y);
				double cb2 = CalcGaiseki(b_x, b_y, b2_x, b2_y);

				if (ca1 * ca2 < 0 && cb1 * cb2 < 0) {
					//交差する時
					return true;
				}
			}
		}
	}
	return false;
}

//他交差判定をする
bool CAdminControl::CalcTakousa(double x1,double y1)
{
	double x2 = shape_head->GetVertexHead()->GetX();
	double y2 = shape_head->GetVertexHead()->GetY();

	double a_x = CalcVector(x1, x2);
	double a_y = CalcVector(y1, y2);

	for (CShape* s = shape_head->GetNext(); s != NULL; s = s->GetNext()) {
		CVertex* p = s->GetVertexHead();
		while (p->GetNext() != NULL) {

			double x3 = p->GetX();
			double y3 = p->GetY();

			p = p->GetNext();
			double x4 = p->GetX();
			double y4 = p->GetY();

			double a1_x = CalcVector(x4, x2);
			double a1_y = CalcVector(y4, y2);

			double a2_x = CalcVector(x3, x2);
			double a2_y = CalcVector(y3, y2);

			double b_x = CalcVector(x3, x4);
			double b_y = CalcVector(y3, y4);

			double b1_x = CalcVector(x2, x4);
			double b1_y = CalcVector(y2, y4);

			double b2_x = CalcVector(x1, x4);
			double b2_y = CalcVector(y1, y4);

			double ca1 = CalcGaiseki(a_x, a_y, a1_x, a1_y);
			double ca2 = CalcGaiseki(a_x, a_y, a2_x, a2_y);
			double cb1 = CalcGaiseki(b_x, b_y, b1_x, b1_y);
			double cb2 = CalcGaiseki(b_x, b_y, b2_x, b2_y);

			if (ca1 * ca2 <= 0 && cb1 * cb2 <= 0) {
				//他交差する時
				return true;
			}

		}
	}
	return false;
}

bool CAdminControl::CalcTakousa(CShape* shape)
{
	CVertex* vertex = shape->GetVertexHead();
	while (vertex->GetNext() != NULL) {
		double x1 = vertex->GetX();
		double y1 = vertex->GetY();
		
		vertex = vertex->GetNext();
		double x2 = vertex->GetX();
		double y2 = vertex->GetY();

		double a_x = CalcVector(x1, x2);
		double a_y = CalcVector(y1, y2);

		for (CShape* s = shape_head->GetNext(); s != NULL; s = s->GetNext()) {
			if (shape != s) {
				CVertex* p = s->GetVertexHead();
				while (p->GetNext() != NULL) {

					double x3 = p->GetX();
					double y3 = p->GetY();

					p = p->GetNext();
					double x4 = p->GetX();
					double y4 = p->GetY();

					double a1_x = CalcVector(x4, x2);
					double a1_y = CalcVector(y4, y2);

					double a2_x = CalcVector(x3, x2);
					double a2_y = CalcVector(y3, y2);

					double b_x = CalcVector(x3, x4);
					double b_y = CalcVector(y3, y4);

					double b1_x = CalcVector(x2, x4);
					double b1_y = CalcVector(y2, y4);

					double b2_x = CalcVector(x1, x4);
					double b2_y = CalcVector(y1, y4);

					double ca1 = CalcGaiseki(a_x, a_y, a1_x, a1_y);
					double ca2 = CalcGaiseki(a_x, a_y, a2_x, a2_y);
					double cb1 = CalcGaiseki(b_x, b_y, b1_x, b1_y);
					double cb2 = CalcGaiseki(b_x, b_y, b2_x, b2_y);

					if (ca1 * ca2 <= 0 && cb1 * cb2 <= 0) {
						//他交差する時
						return true;
					}
				}
			}
		}
	}
	return false;
}

//内外判定をする
bool CAdminControl::CalcNaigai(double x, double y)
{
	for (CShape* s = shape_head->GetNext(); s != NULL; s = s->GetNext()) {
		double sum = 0.0;
		double kakudo = 0.0;
		CVertex* p = s->GetVertexHead();
		while (p->GetNext() != NULL) {
			double x1 = p->GetX();
			double y1 = p->GetY();

			p = p->GetNext();
			double x2 = p->GetX();
			double y2 = p->GetY();

			double a_x = CalcVector(x1, x);
			double a_y = CalcVector(y1, y);

			double b_x = CalcVector(x2, x);
			double b_y = CalcVector(y2, y);

			double nai = CalcNaiseki(a_x, a_y, b_x, b_y);
			double gai = CalcGaiseki(a_x, a_y, b_x, b_y);

			kakudo = atan2(gai, nai);
			sum = kakudo + sum;
		}

		if (sum < 0) {
			sum = -1 * sum;
		}

		double hantei = sum - 2 * M_PI;
		if (hantei < 0) {
			hantei = -1 * hantei;
		}
		if (hantei <= 0.001) {
			//内外する時
			return true;
		}
	}

	return false;
}

CShape* CAdminControl::CalcNaigai2(double x, double y)
{
	for (CShape* s = shape_head->GetNext(); s != NULL; s = s->GetNext()) {
		double sum = 0.0;
		double kakudo = 0.0;
		CVertex* p = s->GetVertexHead();
		while (p->GetNext() != NULL) {
			double x1 = p->GetX();
			double y1 = p->GetY();

			p = p->GetNext();
			double x2 = p->GetX();
			double y2 = p->GetY();

			double a_x = CalcVector(x1, x);
			double a_y = CalcVector(y1, y);

			double b_x = CalcVector(x2, x);
			double b_y = CalcVector(y2, y);

			double nai = CalcNaiseki(a_x, a_y, b_x, b_y);
			double gai = CalcGaiseki(a_x, a_y, b_x, b_y);

			kakudo = atan2(gai, nai);
			sum = kakudo + sum;
		}

		if (sum < 0) {
			sum = -1 * sum;
		}

		double hantei = sum - 2 * M_PI;
		if (hantei < 0) {
			hantei = -1 * hantei;
		}
		if (hantei <= 0.001) {
			//内外する時
			return s;
		}
	}

	return NULL;
}

//内包判定をする
bool CAdminControl::CalcNaihou(double x, double y)
{
	for (CShape* s = shape_head->GetNext(); s != NULL; s = s->GetNext()) {
		double sum = 0.0;
		double kakudo = 0.0;
		double x1 = x;
		double y1 = y;

		CVertex* p = s->GetVertexHead();
		double x3 = p->GetX();
		double y3 = p->GetY();

		CVertex* vertex = shape_head->GetVertexHead();
		while (vertex != NULL) {
			double x2 = vertex->GetX();
			double y2 = vertex->GetY();

			double a_x = CalcVector(x1, x3);
			double a_y = CalcVector(y1, y3);

			double b_x = CalcVector(x2, x3);
			double b_y = CalcVector(y2, y3);

			double nai = CalcNaiseki(a_x, a_y, b_x, b_y);
			double gai = CalcGaiseki(a_x, a_y, b_x, b_y);

			kakudo = atan2(gai, nai);
			sum = kakudo + sum;

			x1 = x2;
			y1 = y2;
			vertex = vertex->GetNext();
		}

		if (sum < 0) {
			sum = -1 * sum;
		}

		double hantei = sum - 2 * M_PI;
		if (hantei < 0) {
			hantei = -1 * hantei;
		}
		if (hantei <= 0.001) {
			//内包する時
			return true;
		}
	}
	
	return false;
}

bool CAdminControl::CalcNaihou(CShape* shape)
{
	for (CShape* s = shape_head->GetNext(); s != NULL; s = s->GetNext()) {
		if (shape != s) {
			double sum = 0.0;
			double kakudo = 0.0;

			CVertex* p = s->GetVertexHead();
			double x3 = p->GetX();
			double y3 = p->GetY();

			CVertex* vertex = shape->GetVertexHead();
			while (vertex->GetNext() != NULL) {
				double x1 = vertex->GetX();
				double y1 = vertex->GetY();

				vertex = vertex->GetNext();
				double x2 = vertex->GetX();
				double y2 = vertex->GetY();

				double a_x = CalcVector(x1, x3);
				double a_y = CalcVector(y1, y3);

				double b_x = CalcVector(x2, x3);
				double b_y = CalcVector(y2, y3);

				double nai = CalcNaiseki(a_x, a_y, b_x, b_y);
				double gai = CalcGaiseki(a_x, a_y, b_x, b_y);

				kakudo = atan2(gai, nai);
				sum = kakudo + sum;
			}

			if (sum < 0) {
				sum = -1 * sum;
			}

			double hantei = sum - 2 * M_PI;
			if (hantei < 0) {
				hantei = -1 * hantei;
			}
			if (hantei <= 0.001) {
				//内包する時
				return true;
			}
		}
	}
	return false;
}

//1つ前の点と一緒か比較する
bool CAdminControl::CalcBeforeSame(double x, double y)
{
	double pre_x = 0.0;
	double pre_y = 0.0;
	if (shape_head->GetVertexHead() != NULL) {
		pre_x = CalcAbsoluteValue(x - shape_head->GetVertexHead()->GetX());
		pre_y = CalcAbsoluteValue(y - shape_head->GetVertexHead()->GetY());
		
		if (pre_x < 0.05 && pre_y < 0.05) {
			return true;
		}

	}
	return false;
}

//ベクトルの計算をする
double CAdminControl::CalcVector(double x1, double x2)
{
	return x1 - x2;
}

//内積の計算をする
double CAdminControl::CalcNaiseki(double a1, double a2, double b1, double b2)
{
	return a1 * b1 + a2 * b2;
}

//外積の計算をする
double CAdminControl::CalcGaiseki(double a1, double a2, double b1, double b2)
{
	return a1 * b2 - a2 * b1;
}

//絶対値の計算をする
double CAdminControl::CalcAbsoluteValue(double x)
{
	if (x < 0) {
		x = -1 * x;
	}
	return x;
}

//xyz軸を表示する
void CAdminControl::DrawAxis(void)
{
	glBegin(GL_LINES);

	//x軸
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	
	//y軸
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	//z軸
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);

	glEnd();
}

//AxisFlagの切り替え
void CAdminControl::ChangeAxisFlag()
{
	if (AxisFlag == true) {
		AxisFlag = false;
	}
	else if(AxisFlag==false){
		AxisFlag = true;
	}
}

void CAdminControl::SetLButtonFlag(bool x)
{
	LButtonFlag = x;
}

bool CAdminControl::GetLButtonFlag()
{
	return LButtonFlag;
}

void CAdminControl::SetRButtonFlag(bool x)
{
	RButtonFlag = x;
}

bool CAdminControl::GetRButtonFlag()
{
	return RButtonFlag;
}

void CAdminControl::LButtonDownSwitch(double x, double y)
{
	if (mode == ID_CREATE_MODE) {
		CreateShape(x, y);
	}
	else if (mode == ID_EDIT_MODE) {
		SelectSubMode(x, y);
	}
}

void CAdminControl::LButtonUpSwitch(double x, double y)
{
	if (mode == ID_EDIT_MODE) {
		if (sub_mode == POINT_SELECT) {
			//頂点移動
			if (CheckSelectVertex() == true) {
				select_shape->GetFirstVertex()->SetXY(x, y);
			}
			select_vertex->SetXY(x, y);
			if (CheckShape() == false) {
				RedoShape();
			}
			MoveErrorFlag = false;
		}
		if (sub_mode == SHAPE_SELECT) {
			//図形移動
			MoveShape(x, y);
			if (CheckShape() == false) {
				RedoShape();
			}
			MoveErrorFlag = false;
		}
	}
}

void CAdminControl::MouseMoveSwitch(double x, double y)
{
	if (mode == ID_EDIT_MODE) {
		if (sub_mode == POINT_SELECT) {
			//頂点移動
			if (CheckSelectVertex() == true) {
				select_shape->GetFirstVertex()->SetXY(x, y);
			}
			select_vertex->SetXY(x, y);
			if (CheckShape() == false) {
				MoveErrorFlag = true;
			}
			else {
				MoveErrorFlag = false;
			}
		}
		if (sub_mode == SHAPE_SELECT) {
			//図形移動
			MoveShape(x, y);
			if (CheckShape() == false) {
				MoveErrorFlag = true;
			}
			else {
				MoveErrorFlag = false;
			}
		}
	}
}

void CAdminControl::LButtonDblClkSwitch(double x, double y)
{
	if (mode == ID_EDIT_MODE) {
		if (sub_mode == POINT_SELECT) {
			//頂点削除
			DeleteSelectVertex();
			if (CheckShape() == false) {
				RedoShape();
			}
		}
		if (sub_mode == LINE_SELECT) {
			//頂点追加
			AddVertex(x, y);
		}
	}
}

void CAdminControl::RButtonDownSwitch(double x, double y)
{
}

void CAdminControl::RButtonUpSwitch(double x, double y)
{
}

void CAdminControl::MouseWheelSwitch(short zDelta)
{
	if (mode == ID_EDIT_MODE) {
		if (sub_mode == SHAPE_SELECT) {
			//図形拡大・縮小
			EXShape(zDelta);
			if (CheckShape() == false) {
				RedoShape();
			}
			MoveErrorFlag = false;
		}
	}
}

//Create_modeへの切り替え
void CAdminControl::ChangeModeCreate()
{
	mode = ID_CREATE_MODE;
	sub_mode = NULL;
	select_vertex = NULL;
	select_shape = NULL;
	before_select_vertex = NULL;
	before_shape = NULL;
}

//Edit_modeへの切り替え
void CAdminControl::ChangeModeEdit()
{
	mode = ID_EDIT_MODE;
}

//shapeの保存
void CAdminControl::SaveBeforeShape()
{
	if (before_shape != NULL) {
		delete before_shape;
	}
	if (select_shape != NULL) {
		before_shape = new CShape();
		for (CVertex* vertex = select_shape->GetVertexHead(); vertex != NULL; vertex = vertex->GetNext()) {
			before_shape->AppendVertex(vertex->GetX(), vertex->GetY());
			if (select_vertex != NULL) {
				if (select_vertex->GetX() == vertex->GetX() && select_vertex->GetY() == vertex->GetY()) {
					before_select_vertex = before_shape->GetVertexHead();
				}
			}
		}
	}
}

//before_shapeに戻す
void CAdminControl::RedoShape()
{
	select_shape->FreeVertex();
	for (CVertex* vertex = before_shape->GetVertexHead(); vertex != NULL; vertex = vertex->GetNext()) {
		select_shape->AppendVertex(vertex->GetX(), vertex->GetY());
	}
	if (before_select_vertex != NULL) {
		select_vertex = before_select_vertex;
	}
}

//頂点削除(select_vertexの削除)
void CAdminControl::DeleteSelectVertex()
{
	if (select_shape != NULL) {
		if (select_shape->CountVertex() >= 5) {
			if (select_vertex != NULL) {
				CVertex* vertex = select_vertex;
				if (CheckSelectVertex() == true) {
					select_shape->SetVertexHead(select_shape->GetVertexHead()->GetNext());
					for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
						if (p->GetNext() == select_shape->GetFirstVertex()) {
							delete select_shape->GetFirstVertex();
							p->SetNext(NULL);
							select_shape->AppendVertex(p->GetX(), p->GetY());
							break;
						}
					}
					
				}
				else {
					for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
						if (p->GetNext() == select_vertex) {
							p->SetNext(select_vertex->GetNext());
							break;
						}
					}
				}
				sub_mode = NULL;
				select_vertex = NULL;
				delete vertex;
			}
		}
	}
}

//頂点追加
void CAdminControl::AddVertex(double x, double y)
{
	CVertex* tmp_vertex = NULL;
	CVertex* tmp_vertex_head = NULL;
	CVertex* vertex = NULL;

	if (select_shape != NULL) {
		if (select_vertex != NULL) {
			tmp_vertex_head = select_shape->GetVertexHead();
			vertex = CheckClickVertexLine(x, y, select_shape);
			if (vertex != NULL) {
				if (select_vertex == vertex) {
					for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
						if (p == select_vertex) {
							select_shape->AppendVertex(x, y);
							tmp_vertex = select_vertex->GetNext();
							select_vertex->SetNext(select_shape->GetVertexHead());
							select_shape->GetVertexHead()->SetNext(tmp_vertex);
							select_shape->SetVertexHead(tmp_vertex_head);

							sub_mode = NULL;
							select_shape = NULL;
							select_vertex = NULL;
							break;
						}
					}
				}

			}
		}
	}
}

//図形移動
void CAdminControl::MoveShape(double x, double y)
{
	double sum_x = 0.0;
	double sum_y = 0.0;
	double center_x = 0.0;
	double center_y = 0.0;
	double move_x = 0.0;
	double move_y = 0.0;
	int count_vertex = 0.0;

	if (select_shape != NULL) {
		count_vertex = select_shape->CountVertex() - 1;
		for (CVertex* p = select_shape->GetVertexHead(); p != select_shape->GetFirstVertex(); p = p->GetNext()) {
			sum_x = p->GetX() + sum_x;
			sum_y = p->GetY() + sum_y;
		}
		center_x = sum_x / count_vertex;
		center_y = sum_y / count_vertex;
		move_x = x - center_x;
		move_y = y - center_y;
		for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
			p->SetX(move_x + p->GetX());
			p->SetY(move_y + p->GetY());
		}
	}
}

//図形拡大・縮小
void CAdminControl::EXShape(short zDelta)
{
	double sum_x = 0.0;
	double sum_y = 0.0;
	double kiten_x = 0.0;
	double kiten_y = 0.0;
	int count_vertex = 0.0;
	if (select_shape != NULL) {
		count_vertex = select_shape->CountVertex() - 1;
		for (CVertex* p = select_shape->GetVertexHead(); p != select_shape->GetFirstVertex(); p = p->GetNext()) {
			sum_x = p->GetX() + sum_x;
			sum_y = p->GetY() + sum_y;
		}
		kiten_x = sum_x / count_vertex;
		kiten_y = sum_y / count_vertex;
		if (zDelta == 120) {
			for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
				p->SetX(1.2 * (p->GetX() - kiten_x) + kiten_x);
				p->SetY(1.2 * (p->GetY() - kiten_y) + kiten_y);
			}
		}
		else if (zDelta == -120) {
			for (CVertex* p = select_shape->GetVertexHead(); p != NULL; p = p->GetNext()) {
				p->SetX(0.8 * (p->GetX() - kiten_x) + kiten_x);
				p->SetY(0.8 * (p->GetY() - kiten_y) + kiten_y);
			}
		}
	}
}


//select_vertexがvertex_headか確認する
bool CAdminControl::CheckSelectVertex()
{
	if (select_vertex == select_shape->GetVertexHead()) {
		return true;
	}
	return false;
}

CVertex* CAdminControl::CheckClickVertexLine(double x, double y, CShape* shape)
{
	double pb_x = 0.0;
	double pb_y = 0.0;
	double ab_x = 0.0;
	double ab_y = 0.0;
	double s = 0.0;

	double pa_x = 0.0;
	double pa_y = 0.0;
	double bunsi = 0.0;
	double hantei = 0.0;

	CVertex* vertexA = shape->GetVertexHead();
	while (vertexA->GetNext() != NULL) {
		CVertex* vertexB = vertexA->GetNext();

		pb_x = CalcVector(x, vertexB->GetX());
		pb_y = CalcVector(y, vertexB->GetY());
		ab_x = CalcVector(vertexA->GetX(), vertexB->GetX());
		ab_y = CalcVector(vertexA->GetY(), vertexB->GetY());
		s = CalcNaiseki(pb_x, pb_y, ab_x, ab_y) / CalcNaiseki(ab_x, ab_y, ab_x, ab_y);

		if (0 <= s && s < 1.05) {
			//最短距離の計算
			pa_x = CalcVector(x, vertexA->GetX());
			pa_y = CalcVector(y, vertexA->GetY());
			bunsi = CalcAbsoluteValue(pa_x * ab_y - pa_y * ab_x);

			hantei = bunsi / sqrt(pow(ab_x, 2) + pow(ab_y, 2));
			if (hantei < 0.01) {
				return vertexA;
				break;
			}
		}
		vertexA = vertexA->GetNext();
	}
	return NULL;
}

void CAdminControl::FreeShape()
{
	while (shape_head != NULL) {
		CShape* s = shape_head;
		shape_head = shape_head->GetNext();
		delete s;
	}
}

