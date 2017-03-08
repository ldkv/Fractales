#include "stdafx.h"
#include "GLWidget.h"
#include <GL/glu.h>

// Initialisation de la sc�ne OpenGL
GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_theta(180.0f), m_phi(0.0f), m_aspectRatio(1.0)
{
	int seconde = 1000; // 1 seconde = 1000 ms
	int timerInterval = seconde / 60;
	t_Timer = new QTimer(this);
	connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
	t_Timer->start(timerInterval);
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);

	// Scale de la sc�ne (zoom)
	m_scale = 1;
	m_incrementScale = 1;
	// Position des deux lumi�res et couleurs ambiant et diffuse
	lights[0].posLight = { 0, 0, 300 };
	lights[0].iAmbiant = { 1.0,1.0,1.0 };
	lights[0].iDiffuse = { 1.0,1.0,1.0 };
	lights[1].posLight = { -100, 150, 150 };
	lights[1].iAmbiant = { 1.0,0.0,1.0 };
	lights[1].iDiffuse = { 1.0,0.0,1.0 };
}

// A la suppression du programme
GLWidget::~GLWidget()
{
	delete[] t_Timer;
}

// Pour garder les FPS � 60
void GLWidget::timeOutSlot()
{
	update();
}

// Initialisation du module OpenGL
void GLWidget::initializeGL()
{
	// Initialisation des proprietes OpenGL du programme
	glClearColor(0, 0, 0, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Angle de la camera
	range = 100.0;

	// Chargement de la texture
	LoadGLTextures("texture.jpg");
}

// Redimensionner de la sc�ne pour adapter � la fen�tre principale
void GLWidget::resizeGL(int width, int height)
{
	screenH = height;
	screenW = width;

	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// D�finition de la matrice orthogonale de la camera
	m_aspectRatio = double(width) / double(height);
	if (width <= height)
		glOrtho(-range, range, -range / m_aspectRatio, range / m_aspectRatio, range*4, -range*4);
	else
		glOrtho(-range * m_aspectRatio, range * m_aspectRatio, -range, range, range*4, -range*4);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Fonction mettre � jour de la sc�ne OpenGL
void GLWidget::paintGL()
{
	// Matrice de dessin de la camera
	m_modelMatrix.setToIdentity();
	m_modelMatrix.rotate(45, 0, 1, 0);
	QMatrix4x4 modelViewMatrix = m_viewMatrix*m_modelMatrix;

	// Nettoyage des buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);

	// Shape Marking
	glPushMatrix();
	glRotatef(m_theta, 1.0f, 0.0f, 0.0f);
	glRotatef(m_phi, 0.0f, 0.0f, 1.0f);
	glScalef(m_scale, m_scale, m_scale);

	// Draw scene
	drawScene(modelViewMatrix);

	glPopMatrix();
}

// Fonction rendu de la sc�ne
void GLWidget::drawScene(QMatrix4x4 mvMatrix)
{
	Cone cone;
	drawCone(cone, precision, QVector3D(0, 1, 0));
	vector<QVector3D> spirals = DrawSpiral(cone, thetaLimit, precision);
	for (int i = 0; i < 0; i++)
	{
		QVector3D c = cone.apex - cone.d * cone.h;
		QVector3D M = spirals[i];
		QVector3D normal = QVector3D::crossProduct(cone.apex - c, M - c);
		normal = QVector3D::crossProduct(M - cone.apex, normal);
		normal.normalize();
		Cone co;
		co.d = normal;
		co.h = 100;
		co.r = 50;
		co.apex = M + co.d*co.h;
		drawCone(co, precision, QVector3D(0, 0, 1));
	}

	// Afficher la grille et les Axes dans la sc�ne
	if (showGrid)
		drawGridandAxes();

	// Affichage des points de controle et des vertex du patch
	if (showPts)
	{
		
	}
}

// Fonction pour dessiner un c�ne
// n: nombre des tranches triangles � dessiner
// R�f�rences: http://www.freemancw.com/2012/06/opengl-cone-function/
vector<QVector3D> GLWidget::drawCone(Cone cone, int n, QVector3D color)
{
	// centre du cercle de base
	QVector3D c = cone.apex + (-cone.d * cone.h);
	QVector3D e0 = perp(cone.d);
	QVector3D e1 = QVector3D::crossProduct(e0, cone.d);
	float angInc = 360.0 / n * (PI / 180.0);

	// calculate points around directrix
	vector<QVector3D> pts;
	for (int i = 0; i <= n; ++i)
	{
		float rad = angInc * i;
		QVector3D p = c + (((e0 * cos(rad)) + (e1 * sin(rad))) * cone.r);
		pts.push_back(p);
	}

	// draw cone top
	glBegin(GL_TRIANGLE_FAN);
	glVector3D(color, false);
	glVertex3f(cone.apex.x(), cone.apex.y(), cone.apex.z());
	for (int i = 0; i <= n; ++i)
		glVertex3f(pts[i].x(), pts[i].y(), pts[i].z());
	glEnd();

	// draw cone bottom
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(c.x(), c.y(), c.z());
	for (int i = n; i >= 0; --i)
		glVertex3f(pts[i].x(), pts[i].y(), pts[i].z());
	glEnd();
	pts.push_back(c);
	pts.push_back(cone.apex);
	//drawPoints(pts, QVector3D(255,0,0), 10);
	return pts;
}

vector<QVector3D> GLWidget::DrawSpiral(Cone cone, float thetaLimit, int precision)
{
	float x, y, z;
	float theta = -PI;
	float angInc = (thetaLimit-theta) / precision;
	float k = cone.r / pow(E, RATIO*thetaLimit);
	float expo = k*pow(E, RATIO*theta);
	x = cone.apex.x() + expo * cos(theta);
	y = cone.apex.y() + expo * sin(theta);
	z = cone.apex.z() - (cone.h / cone.r) * expo;
	vector<QVector3D> spirals;
	QVector3D M = QVector3D(x, y, z);
	spirals.push_back(M);
	
	while (theta <= thetaLimit)
	{
			QVector3D cen = cone.apex - cone.d * cone.h;
			QVector3D normal = QVector3D::crossProduct(cone.apex - cen, M - cen);
			normal = QVector3D::crossProduct(M - cone.apex, normal);
			normal.normalize();
			Cone c;
			c.d = normal;
			c.h = abs(z) - cone.apex.z();
			c.r = c.h / cone.h * cone.r;
			c.apex = M + c.d*c.h;
			drawCone(c, precision, QVector3D(0, 0, 1));

		glBegin(GL_LINES);
		glVertex3f(x, y, z);
		theta += angInc;
		expo = k*pow(E, RATIO*theta);
		x = cone.apex.x() + expo * cos(theta);
		y = cone.apex.y() + expo * sin(theta);
		z = cone.apex.z() - (cone.h / cone.r) * expo;
		M = QVector3D(x, y, z);
		spirals.push_back(M);
		glVertex3f(x, y, z);
		glEnd();
	}
	drawPoints(spirals, QVector3D(255, 0, 0), 10);
	return spirals;
}



// Rotation du patch
void GLWidget::doRotation(QVector3D rot, bool obj)
{
	QVector3D rotDiff = rot - rotObj;
	rotObj = rot;
	//Quaternion quat = Quaternion::fromEulerAngles(rotDiff);
	QQuaternion quat = QQuaternion::fromEulerAngles(rotDiff);
	//posCam = quat.rotatedVector(posCam);
	return;
}

void GLWidget::LoadGLTextures(const char * name)
{
	QImage img;

	if (!img.load(name)) {
		std::cerr << "ERROR in loading image" << std::endl;
	}

	QImage t = QGLWidget::convertToGLFormat(img);

	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

QVector3D GLWidget::processLighting(QVector3D p1Face, QVector3D p2Face, QVector3D p3Face, QVector3D p4Face, Light light) 
{
	//glColor3fv(iAmbiant*kAmbiant);

	QVector3D u = p2Face - p1Face;
	QVector3D v = p4Face - p1Face;
	QVector3D normal = QVector3D::crossProduct(u, v).normalized();
	QVector3D dir = light.posLight - p1Face;
	float cosAngle = QVector3D::dotProduct(normal, dir) / (normal.length() * dir.length());
	cosAngle = (cosAngle <= 0) ? 0 : cosAngle;
	QVector3D R = dir - 2 * normal*(QVector3D::dotProduct(normal, dir));
	float ns = QVector3D::dotProduct(R, p1Face - posCam) / (R.length() * (p1Face - posCam).length());

	ns = (ns <= 0 || cosAngle <= 0) ? 0 : ns;
	ns = pow(ns, 32);

	float ior = 1.517f;
	QVector3D refraction;
	float k = 1.0 - ior * ior * (1.0 - QVector3D::dotProduct(normal, dir) * QVector3D::dotProduct(normal, dir));
	if (k < 0.0)
		R = { 0,0,0 };
	else
		R = ior * dir - (ior * QVector3D::dotProduct(normal, dir) + sqrt(k)) * normal;

	QVector3D l = light.iAmbiant * kAmbiant * objectColor;

	if (showLightDiffuse)
		l += light.iDiffuse * objectColor * kDiffuse * cosAngle;
	if (showLightSpecular)
		l += light.iDiffuse * kSpecular * ns;

	return l;
}

// Dessiner des points
void GLWidget::drawPoints(vector<QVector3D> pts, QVector3D color, int ptSize)
{
	int nbPoints = pts.size();
	if (nbPoints == 0)
		return;
	glVector3D(color, false);
	glPointSize(ptSize);
	glBegin(GL_POINTS);
	for (int i = 0; i < nbPoints; i++)
		glVector3D(pts[i], true);
	glEnd();
}

// Conversion de coordonn�es d'�cran � coordonn�es de la sc�ne OPENGL
QVector3D GLWidget::convertXY(int X, int Y)
{
	return QVector3D((int)((float)X * 2.0 * range * m_aspectRatio / screenW - range * m_aspectRatio), (int)((float)Y * 2.0 * range / screenH - range), 0);
}

// Callback pour le mouvement de la souris
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	mouse = event->pos();
	mouseWorld = convertXY(mouse.x(), mouse.y());
	emit mouseMoved();
}

// Dessiner la grille et les axes dans la sc�ne
void GLWidget::drawGridandAxes()
{
	// Grid
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.1, 0.1, 0.1);
	for (float x = -100; x < 100; x += 5)
	{
		glVertex3d(x, -100, 0);
		glVertex3d(x, 100, 0);
	}
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.1, 0.1, 0.1);
	for (float z = -100; z < 100; z += 5)
	{
		glVertex3d(-100, z, 0);
		glVertex3d(100, z, 0);
	}
	glEnd();

	// Axis
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 50, 0);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(50, 0, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 50);
	glEnd();
}

// Les contr�les de clavier
void GLWidget::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
	case Qt::Key_Escape:
		qApp->quit();
		break;
	case Qt::Key_Left:
		m_phi -= 2.0f;
		break;
	case Qt::Key_Right:
		m_phi += 2.0f;
		break;
	case Qt::Key_Up:
		m_theta += 2.0f;
		break;
	case Qt::Key_Down:
		m_theta -= 2.0f;
		break;
	default:
		break;
	}
}

// Contr�le molette pour zoomer
void GLWidget::wheelEvent(QWheelEvent * event)
{	  
	m_incrementScale += event->delta() / 120;
	if (m_incrementScale == 0 && event->delta() / 120 > 0) 
	{
		m_incrementScale = 1.0f;
	}
	if (m_incrementScale == 0 && event->delta() / 120 < 0) 
	{
		m_incrementScale = -1.0f;
	}
	if (m_incrementScale < 0) 
	{
		m_scale = 1 / -m_incrementScale;
	}
	else
	{
		m_scale = m_incrementScale;
	}
	//resizeGL(screenH, screenW);
};

// R�initialiser le cam�ra au param�tres par d�faut
void GLWidget::resetCamera() 
{
	m_theta = 180.0f;
	m_phi = 0.0f;
	//QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

// R�initialiser les donn�es
void GLWidget::resetData()
{
	
}