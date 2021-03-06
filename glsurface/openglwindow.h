#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H
#include <QOpenGLTexture>

#include <QWindow>
#include <QMouseEvent>
#include <QVector3D>
#include <QVector2D>

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
class QScreen;
class QTimer;
class QOpenGLContext;
enum Pass { Normals, Depth , MarkerTex , Picking, Full , CameraSim , MarkerDepth};

enum DRAW_MODEL { VIRTUAL, REAL };

struct CameraParams{
    float height;
    float focalLength;
    float verticalAOV;
    float horizontalAOV;

    QMatrix4x4 projection;
};

struct Camera
{
    QVector3D position;
    QVector3D rotation;
    QVector2D scale;

    float angle;
};

struct Marker
{
    QString name;
    QVector3D position;
    QVector3D rotation;
    QVector2D scale;
    float angle;
    QImage* image;
    QOpenGLTexture* texture;
};
class OpenGLWindow : public QWindow
{
    Q_OBJECT

public:
    OpenGLWindow( QScreen* screen = 0 );
    ~OpenGLWindow();

    void initializeWindow(QOpenGLContext *glContext, int refreshRate);
    bool isOpenGLES();

protected:
    virtual void initializeGL() = 0;
    virtual void resizeGL(int w, int h) = 0;
    virtual void paintGL() = 0;
    virtual void cleanupGL() = 0;
    virtual void markerChanged(int index,Marker* marker)=0;

private slots:
    void _initializeGL();
    void _resizeGL();
    void _paintGL();
    void _cleanupGL();
public slots:
    void _markerChanged(int index,Marker* marker);
private:
    QOpenGLContext* m_context;
    QTimer *m_timer;
};

#endif // OPENGLWINDOW_H
