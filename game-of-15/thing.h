#ifndef THING_H_INCLUDED
#define THING_H_INCLUDED

#include "hge.h"
#include <vector>
#include <map>
#include <string>

struct Thing{
    hgeQuad picture;

    float real_x = 0.0f;
    float real_y = 0.0f;
    float transition_time = 0.0f;
    enum class TransitionType{
        None,
        Slide
    } transition_type = TransitionType::None;
    float time_left = 0.0f;

    int w = 0;
    int h = 0;

    int from_x = 0;
    int from_y = 0;
    int to_x = 0;
    int to_y = 0;

    bool visible = true;

    void LoadPicture(std::string path);
    void Update(float dt);
    void Render();
    void Teleport(int x, int y);
    void Slide(int x, int y, int ms);
    void Fly(int x, int y, int ms);
    void Blend(int blend_mode);
};

#endif // THING_H_INCLUDED
