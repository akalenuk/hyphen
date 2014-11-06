#include "thing.h"
#include "context.h"



void Thing::LoadPicture(std::string path){
    picture.tex = context::get_hge()->Texture_Load(path.c_str());
    picture.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;
    for(int i = 0; i < 4; i++){
        picture.v[i].z = 0.5f;
        picture.v[i].col = 0xFFFFA000;
    }
    picture.v[0].tx =0.0f;  picture.v[0].ty = 0.0f;
    picture.v[1].tx =1.0f;  picture.v[1].ty = 0.0f;
    picture.v[2].tx =1.0f;  picture.v[2].ty = 1.0f;
    picture.v[3].tx =0.0f;  picture.v[3].ty = 1.0f;

    w = context::get_hge()->Texture_GetWidth(picture.tex);
    h = context::get_hge()->Texture_GetHeight(picture.tex);

    picture.v[0].x = 0;     picture.v[0].y = 0;
    picture.v[1].x = w;     picture.v[1].y = 0;
    picture.v[2].x = w;     picture.v[2].y = h;
    picture.v[3].x = 0;     picture.v[3].y = h;
}

void Thing::Update(){
    int x = static_cast<int>(real_x);
    int y = static_cast<int>(real_y);
    picture.v[0].x=x;   picture.v[0].y=y;
    picture.v[1].x=x+w; picture.v[1].y=y;
    picture.v[2].x=x+w; picture.v[2].y=y+h;
    picture.v[3].x=x;   picture.v[3].y=y+h;
}

void Thing::Render(){
    context::get_hge()->Gfx_RenderQuad(&picture);
}

void Thing::Teleport(int x, int y){
    real_x = static_cast<float>(x);
    real_y = static_cast<float>(y);
    from_x = x;
    from_y = y;
    to_x = x;
    to_y = y;
    Update();
}

void Thing::Blend(int blend_mode){
    picture.blend = blend_mode;
}
