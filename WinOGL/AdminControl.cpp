
#include "pch.h"
#include "AdminControl.h"
#include<math.h>


CAdminControl::CAdminControl()
{
	shape_head = new CShape();
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
		glBegin(GL_POINTS);		//’¸“_•`‰æ
		for (CVertex* p = s->GetVertexHead(); p != NULL; p = p->GetNext()) {
			glVertex2f(p->GetX(), p->GetY());
		}
		glEnd();

		glBegin(GL_LINE_STRIP);		//ü•`‰æ
		for (CVertex* p = s->GetVertexHead(); p != NULL; p = p->GetNext()) {
			glVertex2f(p->GetX(), p->GetY());
		}
		glEnd();
	}
	
}

void CAdminControl::CreateShape(double x, double y)
{

	CVertex* vertex = shape_head->GetVertexHead();
	
	if (shape_head->CountVertex() >= 3) {
		if (CalcKousa(x, y, vertex->GetX(), vertex->GetY()) == false) {
			if (CalcTakousa(x, y) == false) {

				CVertex* p = shape_head->GetVertexHead();
				
				while (p->GetNext() != NULL)
				{
					p = p->GetNext();
				}


				double p_x = p->GetX() - x;
				double p_y = p->GetY() - y;

				if (p_x < 0) {
					p_x = -1 * p_x;
				}
				if (p_y < 0) {
					p_y = -1 * p_y;
				}

				if (p_x <= 0.05 && p_y <= 0.05) {
					shape_head->AppendVertex(p->GetX(),p->GetY());
					AppendShape();
				}
				else {
					shape_head->AppendVertex(x, y);
				}

			}
		}
	}
	else if (shape_head->CountVertex() >= 1) {
		//‘¼Œð·”»’è
		if (CalcTakousa(x,y)==false) {
			shape_head->AppendVertex(x, y);
		}
	}
	else {
		/*if (CalcNaihou() == false) {
			“à•ï‚µ‚Ä‚¢‚È‚¢ê‡*/
			shape_head->AppendVertex(x, y);
		//}
		
	}
	
}

//}Œ`‚ð’Ç‰Á‚·‚é
void CAdminControl::AppendShape()
{
	CShape* shape = new CShape();

	shape->SetNext(shape_head);

	shape_head = shape;
}

//Œð·”»’è‚ð‚·‚é
bool CAdminControl::CalcKousa(double x1, double y1, double x2, double y2)
{
	CVertex* p = shape_head->GetVertexHead()->GetNext();
	while (p->GetNext() != NULL) {

		double x3 = p->GetX();
		double y3 = p->GetY();

		p = p->GetNext();
		double x4 = p->GetX();
		double y4 = p->GetY();

		double a_x = CalcVectorX(x1, x2);
		double a_y = CalcVectorY(y1, y2);

		double a1_x = CalcVectorX(x4, x2);
		double a1_y = CalcVectorY(y4, y2);

		double a2_x = CalcVectorX(x3, x2);
		double a2_y = CalcVectorY(y3, y2);

		double b_x = CalcVectorX(x3, x4);
		double b_y = CalcVectorY(y3, y4);

		double b1_x = CalcVectorX(x2, x4);
		double b1_y = CalcVectorY(y2, y4);

		double b2_x = CalcVectorX(x1, x4);
		double b2_y = CalcVectorY(y1, y4);

		double ca1 = CalcGaiseki(a_x, a_y, a1_x, a1_y);
		double ca2 = CalcGaiseki(a_x, a_y, a2_x, a2_y);
		double cb1 = CalcGaiseki(b_x, b_y, b1_x, b1_y);
		double cb2 = CalcGaiseki(b_x, b_y, b2_x, b2_y);


		if (ca1 * ca2 <= 0 && cb1 * cb2 <= 0) {
			return true;
		}
		
	}
	return false;
}

bool CAdminControl::CalcTakousa(double x1,double y1)
{
	CVertex* p = shape_head->GetVertexHead();

	double x2 = shape_head->GetVertexHead()->GetX();
	double y2 = shape_head->GetVertexHead()->GetY();

	double a_x = CalcVectorX(x1, x2);
	double a_y = CalcVectorY(y1, y2);

	for (CShape* s = shape_head->GetNext(); s != NULL;s=s->GetNext()) {
		CVertex* p = s->GetVertexHead();
		while(p->GetNext() != NULL) {

			double x3 = p->GetX();
			double y3 = p->GetY();

			p = p->GetNext();
			double x4 = p->GetX();
			double y4 = p->GetY();

			double a1_x = CalcVectorX(x4, x2);
			double a1_y = CalcVectorY(y4, y2);

			double a2_x = CalcVectorX(x3, x2);
			double a2_y = CalcVectorY(y3, y2);

			double b_x = CalcVectorX(x3, x4);
			double b_y = CalcVectorY(y3, y4);

			double b1_x = CalcVectorX(x2, x4);
			double b1_y = CalcVectorY(y2, y4);

			double b2_x = CalcVectorX(x1, x4);
			double b2_y = CalcVectorY(y1, y4);

			double ca1 = CalcGaiseki(a_x, a_y, a1_x, a1_y);
			double ca2 = CalcGaiseki(a_x, a_y, a2_x, a2_y);
			double cb1 = CalcGaiseki(b_x, b_y, b1_x, b1_y);
			double cb2 = CalcGaiseki(b_x, b_y, b2_x, b2_y);


			if (ca1 * ca2 <= 0 && cb1 * cb2 <= 0) {
				return true;
			}

		}
	}
	return false;
}

double CAdminControl::CalcVectorX(double x1, double x2)
{
	return x1 - x2;
}

double CAdminControl::CalcVectorY(double y1, double y2)
{
	return y1 - y2;
}

//ŠOÏ‚ÌŒvŽZ‚ð‚·‚é
double CAdminControl::CalcGaiseki(double a1, double a2, double b1, double b2)
{
	return a1 * b2 - a2 * b1;
}

void CAdminControl::FreeShape()
{
	while (shape_head != NULL) {
		CShape* s = shape_head;
		shape_head = shape_head->GetNext();
		delete s;
	}
}

