#include <QtWidgets/QLabel>
#include "Superviser/controler.h"
#include "Gui/mainGui.h"
#include "Core/model.h"
#include "Gui/GLViewer.h"
#include "Gui/viewerTab.h"


Controler::Controler(Model* coreEngine,QObject* parent) : QObject(parent)
{ 
}
void Controler::initControler(Model *coreEngine,QLabel* loadingScreen){
    this->coreEngine=coreEngine;
    graphicalInterface=new Gui();
    graphicalInterface->setControler(this);
    graphicalInterface->createGui();
	coreEngine->setControler(this);
#ifdef __POWITER_OSX__
	graphicalInterface->show();

#else
	graphicalInterface->showMaximized();
#endif

    loadingScreen->hide();
    delete loadingScreen;

    try{
        addNewNode(0,0,"Viewer");
    }catch(...){
        std::cout << "Couldn't create node viewer" << std::endl;
    }
    
}

Controler::~Controler(){
    delete coreEngine;
}

void Controler::exit(){
   //delete this;
}

QStringList& Controler::getNodeNameList(){
    return coreEngine->getNodeNameList();
}

void Controler::setProgressBarProgression(int value){

}
void Controler::addNewNode(qreal x,qreal y,QString name){
   
	QMutex *mutex=coreEngine->mutex();
   // Node* node=new Node(mutex);
    Node* node=NULL;
    UI_NODE_TYPE type;

    type=coreEngine->createNode(node,name,mutex);

    if(type!=UNDEFINED){
        graphicalInterface->addNode_ui(x,y,type,node);
		
    }else{
        throw "Node creation failed!";
        std::cout << "(Controler::addNewNode) Node creation failed " << std::endl;
    }
    



}
