#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>

class SceneWidget: public QGLWidget
	{ // 

	Q_OBJECT

	public:
    SceneWidget(QWidget *parent);
    int rotangle;
    int yrotangle;
    int _speed;
    int _globeSpeed,_tempglobeSpeed;
    int _fanSpeed, _tempfanSpeed;
    int _tapSpeed,_temptapSpeed;
    QImage globePic;
    QImage markusPic;
    QImage marcPic;
    QImage floorPic;
    QImage wallPic;
    QImage topPic;
    QImage wall2Pic;
    QImage wall3Pic;
    int _oscSize;
    double _scale;
    double _cx;
    double _cy;


	public slots:
        // called by the timer in the main window
    void updateTime();
    void rotasion(int);
    void yrotasion(int);
    void updateSpeed(int);
    void oscSize(int);
    void updateGlobe(int);
    void updateFan(int);
    void updateTap(int);

    void updateWallpaper(int);
    void updateScale(double);
    void updateNeckSize(double);
    void updateGlobeSize(double);

	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:

	void plane();
    void cone();
    void smallCylinder1();
    void smallCylinder2();
    void bigFanPart();
    void fan();
    void fanBlade();
    void globe();
    void floor();
    void marcDekamps();
    void markus();
    void room();
    void finger(int);
    void hand();
    void thumb(int);
    void palm();
    void littleString();
    void figureBody();
    void figureCylinder();
    void circularBodyPart();
    void cylinderBodyPart();
    void fingerJoint();
    void pinchingHand();
    void circleCover();
    void furniture();
    void wall(QImage,int);
    void feet();
    void chair();

	double _angle;

	}; // class PlaneWidget
	
#endif
