#include <QApplication>
#include <QVBoxLayout>
#include "SceneWindow.h"

int main(int argc, char *argv[])
	{ // main()
	// create the application
	QApplication app(argc, argv);


	// create a master widget
        SceneWindow *window = new SceneWindow(NULL);

	// create a controller to hook things up
	//	GLPolygonController *controller = new GLPolygonController(window, polygon);

	// resize the window
    window->resize(1200, 1000);

	// show the label
	window->show();

	// start it running
	app.exec();

	// clean up
	//	delete controller;
	delete window;
	
	// return to caller
	return 0; 
	} // main()
