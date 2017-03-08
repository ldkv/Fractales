#ifndef Math5A_Bezier_H
#define Math5A_Bezier_H

#include <QtWidgets/QMainWindow>
#include "ui_maths5a_bezierquaternions.h"
#include "GLWidget.h"

class Math5A_Bezier : public QMainWindow
{
	Q_OBJECT

public:
	Math5A_Bezier(QWidget *parent = 0);
	~Math5A_Bezier();

private slots:
	void setModeRotation();
	void setRotation();
	void resetRotation();
	void resetData();
	void updateLabelTimer();
	void updateStatus();
	void setColor(int idButton);
	void quit();

private:
	Ui::math5a_bezierForm ui;
	QButtonGroup *bGroup;
	GLWidget *glScene;
};

#endif // Math5A_Bezier_H
