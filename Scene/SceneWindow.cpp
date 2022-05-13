
#include "SceneWindow.h"

// constructor / destructor
SceneWindow::SceneWindow(QWidget *parent)
	: QWidget(parent)
	{ // constructor

	// create menu bar
	menuBar = new QMenuBar(this);
	
	// create file menu
	fileMenu = menuBar->addMenu("&File");

	// create the action
	actionQuit = new QAction("&Quit", this);

	// add the item to the menu
	fileMenu->addAction(actionQuit);
	
	// create the window layout
    windowLayoutMain = new QVBoxLayout(this);

    windowLayoutUI = new QHBoxLayout(this);

    windowLayouttest= new QHBoxLayout(this);

    QLabel *oscLabel,*globeSpLabel,*fanSpLabel,*oscSpLabel,*tapSpLabel;

    //Create Labels
    globeSpLabel = new QLabel("Globe Speed");
    fanSpLabel = new QLabel("Fan Speed");
    oscSpLabel = new QLabel("Oscillation & Body Speed");
    tapSpLabel = new QLabel("Tap speed");
    upDownLabel = new QLabel("Left & Right");
    leftRightLabel = new QLabel("Up & Down");
    zoomLabel = new QLabel("Zoom");
    neckLabel= new QLabel("Neck length");
    globeSizeLabel= new QLabel("Globe Size");

	// create main widget
    sceneWidget = new SceneWidget(this);
    windowLayoutMain->addWidget(sceneWidget);
    windowLayoutMain->addLayout(windowLayoutUI);
    windowLayoutUI->addLayout(windowLayouttest);

    //Left and Right Slider
    leftRightSlider = new QSlider(Qt::Horizontal);
    leftRightSlider->setMinimum(-40);
    leftRightSlider->setMaximum(40);
    leftRightSlider->setSliderPosition(0);
    leftRightSlider->setMaximumWidth(100);
    upDownLabel->setMaximumWidth(80);
    windowLayoutUI->addWidget(upDownLabel);
    windowLayoutUI->addWidget(leftRightSlider);
    connect(leftRightSlider, SIGNAL(valueChanged(int)),  sceneWidget  , SLOT(rotasion(int)));

    //Up and Down Slider
    upDownSlider = new QSlider(Qt::Horizontal);
    upDownSlider->setMinimum(-10);
    upDownSlider->setMaximum(25);
    upDownSlider->setSliderPosition(0);
    upDownSlider->setMaximumWidth(100);
    leftRightLabel->setMaximumWidth(80);
    windowLayoutUI->addWidget(leftRightLabel);
    windowLayoutUI->addWidget(upDownSlider);
    connect(upDownSlider, SIGNAL(valueChanged(int)),  sceneWidget  , SLOT(yrotasion(int)));

    //Fan Speed Slider
    fanSpeedSlider = new QSlider(Qt::Vertical);
    fanSpeedSlider->setMaximumWidth(80);
    fanSpeedSlider->setMaximumHeight(80);
    fanSpeedSlider->setMinimum(-10);
    fanSpeedSlider->setMaximum(10);
    fanSpeedSlider->setSliderPosition(1);
    windowLayouttest->addWidget(fanSpLabel);
    windowLayouttest->addWidget(fanSpeedSlider);
    connect(fanSpeedSlider, SIGNAL(valueChanged(int)),  sceneWidget  , SLOT(updateFan(int)));

    //Globe Rotation Speed Slider
    globeSpeedSlider = new QSlider(Qt::Vertical);
    globeSpeedSlider->setMaximumWidth(80);
    globeSpeedSlider->setMaximumHeight(80);
    globeSpeedSlider->setMinimum(0);
    globeSpeedSlider->setMaximum(5);
    globeSpeedSlider->setSliderPosition(1);
    windowLayouttest->addWidget(globeSpLabel);
    windowLayouttest->addWidget(globeSpeedSlider);
    connect(globeSpeedSlider, SIGNAL(valueChanged(int)),  sceneWidget  , SLOT(updateGlobe(int)));

    //Speed of Tapping Hand
    tapSpeedSlider = new QSlider(Qt::Vertical);
    tapSpeedSlider->setMaximumWidth(80);
    tapSpeedSlider->setMaximumHeight(80);
    tapSpeedSlider->setMinimum(0);
    tapSpeedSlider->setMaximum(5);
    tapSpeedSlider->setSliderPosition(1);
    windowLayouttest->addWidget(tapSpLabel);
    windowLayouttest->addWidget(tapSpeedSlider);
    connect(tapSpeedSlider, SIGNAL(valueChanged(int)),  sceneWidget  , SLOT(updateTap(int)));

    //Speed of Figure spiinning around table and oscillations
    otherSpeedSlider = new QSlider(Qt::Vertical);
    otherSpeedSlider->setMaximumWidth(80);
    otherSpeedSlider->setMaximumHeight(80);
    otherSpeedSlider->setMinimum(-3);
    otherSpeedSlider->setMaximum(3);
    otherSpeedSlider->setSliderPosition(1);
    windowLayouttest->addWidget(oscSpLabel);
    windowLayouttest->addWidget(otherSpeedSlider);
    connect(otherSpeedSlider, SIGNAL(valueChanged(int)),  sceneWidget  , SLOT(updateSpeed(int)));

    //Size of oscillation slider
    oscSlider= new QSlider(Qt::Horizontal);
    oscLabel = new QLabel(oscSlider);
    oscLabel->setText("Oscillation Size");
    oscLabel->setMaximumWidth(80);
    oscSlider->setMaximumWidth(80);
    oscSlider->setMaximumHeight(80);
    oscSlider->setTickInterval(10);
    oscSlider->setMinimum(25);
    oscSlider->setMaximum(55);
    oscSlider->setSliderPosition(25);
    windowLayoutUI->addWidget(oscLabel);
    windowLayoutUI->addWidget(oscSlider);
    connect(oscSlider, SIGNAL(valueChanged(int)),  sceneWidget  , SLOT(oscSize(int)));

    sinputbox =  new QDoubleSpinBox;
    sinputbox->setMaximumWidth(400);
    zoomLabel->setMaximumWidth(80);
    windowLayoutUI->addWidget(zoomLabel);
    windowLayoutUI->addWidget(sinputbox);
    sinputbox->setMinimum(0);
    sinputbox->setMaximum(45);
    connect(sinputbox, SIGNAL(valueChanged(double)),  sceneWidget  , SLOT(updateScale(double)));


    nSizeinputbox =  new QDoubleSpinBox;
    nSizeinputbox->setMaximumWidth(40);
    neckLabel->setMaximumWidth(80);
    windowLayoutUI->addWidget(neckLabel);
    windowLayoutUI->addWidget(nSizeinputbox);
    nSizeinputbox->setMinimum(0);
    nSizeinputbox->setMaximum(8);
    connect(nSizeinputbox, SIGNAL(valueChanged(double)),  sceneWidget  , SLOT(updateNeckSize(double)));

    gSizeinputbox =  new QDoubleSpinBox;
    gSizeinputbox->setMaximumWidth(40);
    globeSizeLabel->setMaximumWidth(80);
    windowLayoutUI->addWidget(globeSizeLabel);
    windowLayoutUI->addWidget(gSizeinputbox);
    gSizeinputbox->setMinimum(-8);
    gSizeinputbox->setMaximum(16);
    connect(gSizeinputbox, SIGNAL(valueChanged(double)),  sceneWidget  , SLOT(updateGlobeSize(double)));

    dropDown = new QComboBox;
    windowLayoutMain->addWidget(dropDown);
    dropDown->addItem("Bricks Wallpaper");
    dropDown->addItem("Space Wallpaper");
    dropDown->addItem("Hawaii Wallpaper");
    connect(dropDown, SIGNAL(activated(int)),  sceneWidget, SLOT(updateWallpaper(int)));

    ptimer = new QTimer(this);
      
    ptimer->start(20);

    connect(ptimer, SIGNAL(timeout()),  sceneWidget, SLOT(updateTime()));


	} // constructor

SceneWindow::~SceneWindow()
	{ // destructor
	delete ptimer;
    delete leftRightSlider;
    delete sceneWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void SceneWindow::ResetInterface()
	{ // ResetInterface()
    leftRightSlider->setMinimum(3);
    leftRightSlider->setMaximum(30);
	// now force refresh
    sceneWidget->update();
	update();
	} // ResetInterface()
