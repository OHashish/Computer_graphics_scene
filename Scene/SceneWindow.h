#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QTimer>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
#include "SceneWidget.h"

class SceneWindow: public QWidget
	{ 
    Q_OBJECT
	public:
       
	
	// constructor / destructor
    SceneWindow(QWidget *parent);
    ~SceneWindow();

	// visual hierarchy
	// menu bar
	QMenuBar *menuBar;
		// file menu
		QMenu *fileMenu;
			// quit action
			QAction *actionQuit;

	// window layout
	QBoxLayout *windowLayout;

    QVBoxLayout *windowLayoutMain;
    QHBoxLayout *windowLayoutUI;
    QHBoxLayout *windowLayouttest;

	// beneath that, the main widget
    SceneWidget *sceneWidget;
	// and a slider for the number of vertices
    QSlider *oscSlider;
    QSlider *leftRightSlider;
    QSlider *upDownSlider;
    QSlider *fanSpeedSlider,*globeSpeedSlider,*otherSpeedSlider,*tapSpeedSlider;

    QDoubleSpinBox *sinputbox;
    QDoubleSpinBox *nSizeinputbox;
    QDoubleSpinBox *gSizeinputbox;

    QComboBox *dropDown;
    //Labels
    QLabel *oscLabel,*globeSpLabel,*fanSpLabel,*oscSpLabel,*tapSpLabel,*upDownLabel,*leftRightLabel
    ,*zoomLabel,*neckLabel,*globeSizeLabel;

	// a timer
	QTimer *ptimer;

	// resets all the interface elements
	void ResetInterface();
	}; 
	
#endif
