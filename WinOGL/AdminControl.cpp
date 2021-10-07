
#include "pch.h"
#include "AdminControl.h"


CAdminControl::CAdminControl()
{
}

CAdminControl::~CAdminControl()
{
	FreeVertex();
}



void CAdminControl::Draw()
{

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);

	for (CVertex* p = vertex_head; p != NULL; p = p->GetNext()) {
		glVertex2f(p->GetX(), p->GetY());
	}
	glEnd();
}


void CAdminControl::AppendVertex(double x,double y)
{
	CVertex* vertex = new CVertex();

	vertex->SetXY(x, y);
	vertex->SetNext(vertex_head);

	vertex_head = vertex;
}

void CAdminControl::FreeVertex()
{
	while (vertex_head != NULL) {
		CVertex* p = vertex_head;
		vertex_head = vertex_head->GetNext();
		delete p;
	}
}
