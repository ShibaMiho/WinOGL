
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
	shape_head->AppendVertex(x, y);

	CVertex* p = shape_head->GetVertexHead();
	int c = 1;
	while (p->GetNext() != NULL)
	{
		p = p->GetNext();
		c++;

	}

	if (c > 3) {

		double p_x = p->GetX() - x;
		double p_y = p->GetY() - y;
		
		if (p_x < 0) {
			p_x = -1 * p_x;
		}
		if (p_y < 0) {
			p_y = -1 * p_y;
		}

		if (p_x <= 0.01 && p_y <= 0.01) {
			AppendShape();
		}
		
	}
}

//}Œ`‚ð’Ç‰Á‚·‚é
void CAdminControl::AppendShape()
{
	CShape* shape = new CShape();

	shape->SetNext(shape_head);

	shape_head = shape;
}

void CAdminControl::FreeShape()
{
	while (shape_head != NULL) {
		CShape* s = shape_head;
		shape_head = shape_head->GetNext();
		delete s;
	}
}

