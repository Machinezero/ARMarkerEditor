#include "viewcamera.h"

ViewCamera::ViewCamera()
{
    m_view.setToIdentity();

    cameraPos = QVector3D(0.0f, 0.0f, 1.0f);
    cameraVec = QVector3D(0.0f, 0.0f, 0.0f);
    upVec = QVector3D(0.0f, 1.0f, 0.0f);

    cameraForward = (QVector3D(cameraVec - cameraPos));
    cameraForward.normalize();
    m_view.lookAt(
                cameraPos,    // Camera Position
                cameraVec,    // Point camera looks towards
                upVec);   // Up vector
    shiftPressed=false;
    fpsView=false;
}

void ViewCamera::walkForward(){
    float shiftValue= ((float)!shiftPressed)+0.01;
    cameraPos+=cameraForward/(10.0*shiftValue);
}

void ViewCamera::walkBackward(){
    float shiftValue= ((float)!shiftPressed)+0.01;
    cameraPos-=cameraForward/(10.0*shiftValue);
}

QVector3D ViewCamera::getForwardPos(){
    return (cameraPos + cameraForward*3);
}


void ViewCamera::eagleView(){
    cameraForward=QVector3D(0.0,-0.99,0.0);
}

void ViewCamera::setupCamera(QVector3D eye,QVector3D center,QVector3D up){
    if(center.y()==-10000){
        if(eye.y()!=-10000) center=eye+cameraForward;
        else center=cameraPos+cameraForward;
    }

    if(eye.y()==-10000){
        eye=cameraPos;
    }

    if(up.y()==-10000){
        up=upVec;
    }


    m_view.setToIdentity();
    m_view.lookAt(
                eye,    // Camera Position
                center,    // Point camera looks towards
                up);   // Up vector

}

void ViewCamera::mouseRotate(float valx,float valy){
    //Left/Right Camera Rotation

    cameraForward = rotate(cameraForward,upVec, -valx);
    cameraForward.normalize();

    //Up/Down Camera Rotation
    QVector3D upV= QVector3D::crossProduct(upVec,cameraForward);
    rotate(upVec, upV, valy);
    cameraForward =rotate(cameraForward, upV, valy);

    cameraForward.normalize();

}



QMatrix4x4 ViewCamera::getViewM(){
    return m_view;
}


void ViewCamera::resize(int h,int w){

}

QVector3D ViewCamera::rotate(QVector3D Vx,QVector3D axis, float angle) {
  float ca = cos(angle);
  float sa = sin(angle);

  QVector3D cross = QVector3D::crossProduct(Vx,axis);

  float dot= QVector3D::dotProduct(axis,Vx);

  QVector3D r=Vx*ca + cross*sa + dot*axis*(1-ca);

  return r;
}
