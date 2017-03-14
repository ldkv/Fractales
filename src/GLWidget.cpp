#include "stdafx.h"
#include "GLWidget.h"
#include <GL/glu.h>

// Initialisation de la scène OpenGL
GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_theta(180.0f), m_phi(0.0f), m_aspectRatio(1.0)
{
	int seconde = 1000; // 1 seconde = 1000 ms
	int timerInterval = seconde / 60;
	t_Timer = new QTimer(this);
	connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
	t_Timer->start(timerInterval);
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);

	// Scale de la scène (zoom)
	m_scale = 1;
	m_incrementScale = 1;
	// Position des deux lumières et couleurs ambiant et diffuse
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

// Pour garder les FPS à 60
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

// Redimensionner de la scène pour adapter à la fenêtre principale
void GLWidget::resizeGL(int width, int height)
{
	screenH = height;
	screenW = width;

	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Définition de la matrice orthogonale de la camera
	m_aspectRatio = double(width) / double(height);
	if (width <= height)
		glOrtho(-range, range, -range / m_aspectRatio, range / m_aspectRatio, range*4, -range*4);
	else
		glOrtho(-range * m_aspectRatio, range * m_aspectRatio, -range, range, range*4, -range*4);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Fonction mettre à jour de la scène OpenGL
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
	drawScene();

	glPopMatrix();
}

// Fonction rendu de la scène
void GLWidget::drawScene()
{
	Cone cone;
	//cone.apex = { 0, 0, 90 };
	drawCone(cone, precision, QVector3D(0, 1, 0));
	vector<QVector3D> spirals = DrawSpiral(cone, thetaLimit, precision, -PI*5);
	//vector<QVector3D> spirals2 = DrawSpiral(cone, thetaLimit, precision, -PI * 2 + 1);
	/*for (int i = 0; i < 0; i++)
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
	}*/

	DrawSpiral2D();

	// Afficher la grille et les Axes dans la scène
	if (showGrid)
		drawGridandAxes();
}

// Fonction pour dessiner un cône
// n: nombre des tranches triangles à dessiner
// Références: http://www.freemancw.com/2012/06/opengl-cone-function/
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

	if (showPts)
	{
		glVector3D(QVector3D(255, 0, 0), false);
		glBegin(GL_LINES);
		for (int i = 0; i < pts.size() - 1; i++)
		{
			glVertex3f(pts[pts.size() - 1].x(), pts[pts.size() - 1].y(), pts[pts.size() - 1].z());
			glVertex3f(pts[i].x(), pts[i].y(), pts[i].z());
			//glVertex3f(pts[i + 1].x(), pts[i + 1].y(), pts[i + 1].z());
		}
		glEnd();
	}

	return pts;
}

vector<QVector3D> GLWidget::DrawSpiral(Cone cone, float thetaLimit, int precision, float theta)
{
	float x, y, z;
	//float theta = -PI;
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
		c.h /= 2;
		c.r = c.h / cone.h * cone.r;
		//c.r /= 1.1;
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


// centerX-- X origin of the spiral.
// centerY-- Y origin of the spiral.
// radius--- Distance from origin to outer arm.
// sides---- Number of points or sides along the spiral's arm.
// coils---- Number of coils or full rotations. (Positive numbers spin clockwise, negative numbers spin counter-clockwise)
// rotation- Overall rotation of the spiral. ('0'=no rotation, '1'=360 degrees, '180/360'=180 degrees)
//

void  GLWidget::logSpiral(float centerX, float centerY, float radius, float sides, float coils, float rotation, int val) {

	//
	// How far to rotate around center for each side.
	float aroundStep = coils / sides;// 0 to 1 based.
									 //
									 // Convert aroundStep to radians.
	float aroundRadians = aroundStep * 2 * 3.14f;//Math.PI;
												 //
												 // Convert rotation to radians.
	rotation *= 2 * 3.14f; //Math.PI;
						   //
						   // For every side, step around and away from center.
						   //glBegin(GL_LINE);
	for (int i = 1; i <= sides; i++) {
		//
		// How far away from center
		float away = pow(radius, i / sides);//radius pow((sqrt(5)+1)/2, i)*radius //pow((sqrt(5) + 1) / 2, i/sides*coils)*
											//
											// How far around the center.
		float around = i * aroundRadians + rotation /*+ rotation*i / sides*/;
		//
		// Convert 'around' and 'away' to X and Y.
		float x = centerX + cos(around) * away;
		float y = centerY + sin(around) * away;
		//
		// Now that you know it, do it.
		//glVertex3f(x, y, 0);
		vec.push_back(QVector3D(x, y, 0));
		if (val > 0) {
			for (float t = 0; t < 1; t += 0.125)
			{
				logSpiral(x, y, pprev.distanceToPoint(QVector3D(x, y, 0))/2, 70, 2, t, val - 1); //(1/sides*i, 2)
			}
		}
		pprev = QVector3D(x, y, 0);
	}
	//glEnd();
}


void GLWidget::DrawSpiral2D()
{
	//  (centerX, centerY, radius, sides, coils, rotation, iteration)
	//logSpiral(0, 0, 10, 70, 14, 0.4, 1);
	if(vec.size() < 2)
	for (float i = 0; i < 1; i += 0.125)
	{
		//logSpiral(0, 0, 40, 70, 2, i, 1);
		logSpiral(0, 0, 40, 70, -2, i, 0);
	}
	/*for (float i = 0; i < 1; i += 0.07)
	{
	logSpiral(0, 0, 40, 70, 1, i, 0);
	}*/

	//logSpiral(0, 0, 40, 70, 2, 0.5, 0);
	//logSpiral(0, 0, 320, 70, 14, .5, 0);
	//
	//

	glBegin(GL_LINES);
	for (int i = 0; i < vec.size()-1; i++)
	{
		//if (i / 70 != 1) {
			glVertex3f(vec[i].x(), vec[i].y(), vec[i].z());
			glVertex3f(vec[i + 1].x(), vec[i + 1].y(), vec[i + 1].z());
		//}
	}
	glEnd();
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

// Conversion de coordonnées d'écran à coordonnées de la scène OPENGL
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

// Dessiner la grille et les axes dans la scène
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

// Les contrôles de clavier
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

// Contrôle molette pour zoomer
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

// Réinitialiser le caméra au paramètres par défaut
void GLWidget::resetCamera() 
{
	m_theta = 180.0f;
	m_phi = 0.0f;
	//QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

// Réinitialiser les données
void GLWidget::resetData()
{
	
}