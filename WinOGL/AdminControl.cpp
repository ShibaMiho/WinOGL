
#include "pch.h"
#include "AdminControl.h"


CAdminControl::CAdminControl()
{
	shape_head = new CShape();
}

CAdminControl::~CAdminControl()
{
}



void CAdminControl::Draw()
{

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);		//“_•`‰æ

	for (CVertex* p = shape_head->GetVertexHead(); p != NULL; p = p->GetNext()) {
		glVertex2f(p->GetX(), p->GetY());
	}
	glEnd();

	glBegin(GL_LINE_STRIP);		//ü•`‰æ

	for (CVertex* p = shape_head->GetVertexHead(); p != NULL; p = p->GetNext()) {
		glVertex2f(p->GetX(), p->GetY());
	}
	glEnd();
}

void CAdminControl::CreateShape(double x, double y)
{
	shape_head->AppendVertex(x,y);
}

