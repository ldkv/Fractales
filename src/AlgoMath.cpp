#include "stdafx.h"
#include "AlgoMath.h"

// Retourner un vecteur perpendiculaire au vecteur donné
QVector3D perp(const QVector3D &v)
{
	float min = fabs(v.x());
	QVector3D cardinalAxis(1, 0, 0);

	if (fabs(v.y()) < min)
	{
		min = fabs(v.y());
		cardinalAxis = QVector3D(0, 1, 0);
	}

	if (fabs(v.z()) < min)
		cardinalAxis = QVector3D(0, 0, 1);
	return QVector3D::crossProduct(v, cardinalAxis);
}

vector<QVector3D> vec;
QVector3D pprev = QVector3D(0, 0, 0);

void logSpiral(float centerX, float centerY, float radius, float sides, float coils, float rotation, int val) {

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
		float around = i * aroundRadians + rotation;
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
				logSpiral(x, y, pprev.distanceToPoint(QVector3D(x, y, 0)) / 2, 70, 2, t, val - 1); //(1/sides*i, 2)
			}
		}
		pprev = QVector3D(x, y, 0);
	}
	//glEnd();
}

// Génération aléatoire d'un nombre entier dans l'intervalle donnée
int randomGeneration(int min, int max)
{
	// the random device that will seed the generator
	std::random_device seeder;
	// make a mersenne twister engine
	std::mt19937 engine(seeder());
	// the distribution
	std::uniform_int_distribution<int> dist(min, max);
	// generate the integer
	return dist(engine);
}

// Convertir la classe QVector3D pour utiliser avec les fonctions OpenGL
void glVector3D(QVector3D p, bool vertex)
{
	GLfloat *temp = new GLfloat[3];
	temp[0] = p.x();
	temp[1] = p.y();
	temp[2] = p.z();
	if (vertex)
		glVertex3fv(temp);
	else
		glColor3fv(temp);
	delete[] temp;
}

// Convertir les couleurs entre valeurs entières et normalisées
QColor convertColor(QVector3D col)
{
	int r = (int)(col.x() * 255);
	int g = (int)(col.y() * 255);
	int b = (int)(col.z() * 255);
	return QColor(r, g, b);
}