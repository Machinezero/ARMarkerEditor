#ifndef GLSIGNALEMITTER_H
#define GLSIGNALEMITTER_H

#include <QObject>
#include <glsurface/openglwindow.h>

class GLSignalEmitter : public QObject
{
    Q_OBJECT
public:
    explicit GLSignalEmitter(QObject *parent = 0);


signals:
    Camera* editCamera(int index,Camera* camera,bool* runSim,CameraParams* camParams, int* simCount );
    Marker* editMarker(int index,Marker* camera);

public slots:
};

#endif // GLSIGNALEMITTER_H
