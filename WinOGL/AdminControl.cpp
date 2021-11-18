
#include "pch.h"
#include "AdminControl.h"

#define _USE_MATH_DEFINES
#define ID_CREATE_MODE 1
#define ID_EDIT_MODE 2

#define POINT_SELECT 1
#define SHAPE_SELECT 2
#define LINE_SELECT 3
#define POINT_MOVE 4

#include<math.h>


CAdminControl::CAdminControl()
{
	shape_head = new CShape();
	AxisFlag = false;
	LButtonFlag = false;
	select_vertex = NULL;
	select_shape = NULL;
	before_shape = NULL;
	mode = ID_CREATE_MODE;
	sub_mode = NULL;
}

CAdminControl::~CAdminControl()
{
	FreeShape();
}


void CAdminControl::Draw()
{
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);

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
			glPointSize(8);

			glBegin(GL_POINTS);		//頂点描画
			glVertex2f(select_vertex->GetX(), select_vertex->GetY());
			glEnd();
		}

		if (sub_mode == SHAPE_SELECT) {
			glColor3f(0.0, 1.0, 0.0);
			glPointSize(8);

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

		if (sub_mode == LINE_SELECT) {
			glColor3f(0.0, 1.0, 0.0);
			glPointSize(5);

			glBegin(GL_LINE_STRIP);
			glVertex2f(select_vertex->GetX(), select_vertex->GetY());
			glVertex2f(select_vertex->GetNext()->GetX(), select_vertex->GetNext()->GetY());
			glEnd();
		}

		if (sub_mode == POINT_MOVE) {
			glColor3f(1.0, 1.0, 1.0);
			glPointSize(5);

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

			glColor3f(0.0, 1.0, 0.0);
			glPointSize(8);

			glBegin(GL_POINTS);		//頂点描画
			glVertex2f(select_vertex->GetX(), select_vertex->GetY());
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
			CVertex* sa = shape_head->GetVertexHead();
			while (sa->GetNext() != NULL)
			{
				sa = sa->GetNext();
			}
			double sa_x = x - sa->GetX();
			double sa_y = y - sa->GetY();
			if (sa_x < 0) {
				sa_x = -1 * sa_x;
			}
			if (sa_y < 0) {
				sa_y = -1 * sa_y;
			}
			if (sa_x <= 0.03 && sa_y <= 0.03) {
				x = sa->GetX();
				y = sa->GetY();
			}

			if (CalcKousa(x, y, vertex->GetX(), vertex->GetY()) == false) {
				if (CalcTakousa(x, y) == false) {
					if (CalcNaihou(x, y) == false) {
						//交差、他交差、内包していない場合

						CVertex* p = shape_head->GetVertexHead();

						while (p->GetNext() != NULL)
						{
							p = p->GetNext();
						}

						double p_x = p->GetX() - x;
						double p_y = p->GetY() - y;

						//絶対値を取る
						if (p_x < 0) {
							p_x = -1 * p_x;
						}
						if (p_y < 0) {
							p_y = -1 * p_y;
						}

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
void CAdminControl::SelectEdit(double x, double y)
{
	sub_mode = NULL;
	double x1 = 0.0;
	double y1 = 0.0;
	double sa_x = 0.0;
	double sa_y = 0.0;

	double pa_x = 0.0;
	double pa_y = 0.0;
	double pb_x = 0.0;
	double pb_y = 0.0;
	double ab_x = 0.0;
	double ab_y = 0.0;
	double hantei = 0.0;
	double bunsi = 0.0;

	double s = 0.0;

	for (CShape* shape = shape_head->GetNext(); shape!= NULL; shape = shape->GetNext()) {
		//頂点の選択判定
		CVertex* vertex = shape->GetVertexHead();
		while (vertex != NULL) {
			x1 = vertex->GetX();
			y1 = vertex->GetY();

			sa_x = x - x1;
			sa_y = y - y1;
			if (sa_x < 0) {
				sa_x = -1 * sa_x;
			}
			if (sa_y < 0) {
				sa_y = -1 * sa_y;
			}
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
			CVertex* vertexA = shape->GetVertexHead();
			while (vertexA->GetNext() != NULL) {
				CVertex* vertexB = vertexA->GetNext();

				pb_x = CalcVector(x,vertexB->GetX());
				pb_y = CalcVector(y, vertexB->GetY());
				ab_x = CalcVector(vertexA->GetX(), vertexB->GetX());
				ab_y = CalcVector(vertexA->GetY(),vertexB->GetY());
				s = CalcNaiseki(pb_x, pb_y, ab_x, ab_y) / CalcNaiseki(ab_x, ab_y, ab_x, ab_y);

				if (0 <= s && s < 1.05) {
					//最短距離の計算
					pa_x = CalcVector(x,vertexA->GetX());
					pa_y = CalcVector(y, vertexA->GetY());
					bunsi = pa_x * ab_y - pa_y * ab_x;
					if (bunsi < 0) {
						bunsi = -1 * bunsi;
					}
					hantei = bunsi / sqrt(pow(ab_x, 2) + pow(ab_y, 2));
					if (hantei < 0.01) {
						select_shape = shape;
						select_vertex = vertexA;
						sub_mode = LINE_SELECT;
						break;
					}
				}
				vertexA = vertexA->GetNext();
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
		if (CalcKousa(vertex->GetX(), vertex->GetY(), vertex->GetNext()->GetX(), vertex->GetNext()->GetY(), shape) == true) {
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

bool CAdminControl::CalcKousa(double x1, double y1, double x2, double y2, CShape* shape)
{
	CVertex* p = shape->GetVertexHead()->GetNext()->GetNext();
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
		pre_x = x - shape_head->GetVertexHead()->GetX();
		pre_y = y - shape_head->GetVertexHead()->GetY();
		if (pre_x < 0) {
			pre_x = -1 * pre_x;
		}
		if (pre_y < 0) {
			pre_y = -1 * pre_y;
		}

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

void CAdminControl::LButtonSwitch(double x, double y)
{
	if (mode == ID_CREATE_MODE) {
		CreateShape(x,y);
	}
	else if (mode == ID_EDIT_MODE) {
		SelectEdit(x,y);
	}
}

void CAdminControl::LButtonUpSwitch(double x, double y)
{
	if (mode==ID_EDIT_MODE) {
		if (sub_mode==POINT_SELECT) {
			if (CheckSelectVertex() == true) {
				select_shape->GetFirstVertex()->SetXY(x,y);
			}
			select_vertex->SetXY(x,y);
			if (CheckShape() == false) {
				RedoShape();
			}
		}
	}
}

//Create_modeへの切り替え
void CAdminControl::ChangeModeCreate()
{
	mode = ID_CREATE_MODE;
	select_shape = NULL;
	select_vertex = NULL;
	sub_mode = NULL;
}

//Edit_modeへの切り替え
void CAdminControl::ChangeModeEdit()
{
	mode = ID_EDIT_MODE;
}

//modeの取得
int CAdminControl::GetMode()
{
	return mode;
}

//sub_modeの取得
int CAdminControl::GetSubMode()
{
	return sub_mode;
}

void CAdminControl::SetSubMode(int x)
{
	sub_mode = x;
}

void CAdminControl::SaveBeforeShape()
{
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

bool CAdminControl::CheckSelectVertex()
{
	if (select_vertex==select_shape->GetVertexHead()) {
		return true;
	}
	return false;
}

void CAdminControl::FreeShape()
{
	while (shape_head != NULL) {
		CShape* s = shape_head;
		shape_head = shape_head->GetNext();
		delete s;
	}
}

