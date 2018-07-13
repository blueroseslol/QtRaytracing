#ifndef CAMERA_H
#define CAMERA_H


class Camera
{
public:
    Camera();

    int hres;
    int vres;
    float s;
    float gamma;
    float inv_gamma;
};

#endif // CAMERA_H
