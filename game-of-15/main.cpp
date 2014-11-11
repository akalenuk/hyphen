#include "hge.h"
#include "hgegui.h"

#include <vector>
using namespace std;

#include "type_the.h"
#include "thing.h"
#include "context.h"
#include "hyphen_notation.h"
using namespace hyphen;

HGE*        hge = 0;
hgeQuad     bg;
HTEXTURE    cursor_texture;
hgeSprite*  cursor_sprite;
hgeGUI*     gui;

bool FrameFunc()
{
    float dt=hge->Timer_GetDelta();

    if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;

    bg.v[0].x=0;    bg.v[0].y=0;
    bg.v[1].x=800;  bg.v[1].y=0;
    bg.v[2].x=800;  bg.v[2].y=600;
    bg.v[3].x=0;    bg.v[3].y=600;

    vector<Thing>::iterator iter = context::get_things().begin();
    vector<Thing>::iterator eit = context::get_things().end();
    for(; iter != eit; ++iter){
        (*iter).Update(dt);
    }


    //
    // here's the whole code for the game logic
    //
    for(the I : from-1-to-15){
        the Tile = "tile_" & I;
        the EmptyTileX = "tile_16"-x;
        the EmptyTileY = "tile_16"-y;
        if( Tile-is-clicked ){
            if( abs( Tile-x - EmptyTileX ) + abs( Tile-y - EmptyTileY ) == 105 ){
                teleport-"tile_16"-to-(Tile-x)-(Tile-y);
                slide-Tile-to-EmptyTileX-EmptyTileY-in-200-ms;
            }
        }
    }
    teleport-"cursor"-to-(mouse-x)-(mouse-y);



    return false;
}

bool RenderFunc()
{
    hge->Gfx_BeginScene();
    hge->Gfx_Clear(0);

    hge->Gfx_RenderQuad(&bg);
    vector<Thing>::iterator it = context::get_things().begin();
    vector<Thing>::iterator eit = context::get_things().end();
    for(; it != eit; ++it){
        (*it).Render();
    }

    hge->Gfx_EndScene();
    return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    hge = hgeCreate(HGE_VERSION);
    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    hge->System_SetState(HGE_RENDERFUNC, RenderFunc);

    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_SCREENWIDTH, 800);
    hge->System_SetState(HGE_SCREENHEIGHT, 600);
    hge->System_SetState(HGE_SCREENBPP, 32);

    if(hge->System_Initiate()){
        context::set_hge(hge);

        bg.tex = hge->Texture_Load("stuff/bg.png");
        bg.blend = BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;
        for(int i=0;i<4;i++){
            bg.v[i].z=0.5f;
            bg.v[i].col=0xFFFFA000;
        }
        bg.v[0].tx=0.0f; bg.v[0].ty=0.0f;
        bg.v[1].tx=1.0f; bg.v[1].ty=0.0f;
        bg.v[2].tx=1.0f; bg.v[2].ty=1.0f;
        bg.v[3].tx=0.0f; bg.v[3].ty=1.0f;


        //
        // here's the whole code for the game initializing
        //
        for(the I : from-1-to-4){
            for(the J : from-1-to-4){
                the K = I * 4 + J - 4;
                the X = 85 + J * 105;
                the Y = I * 105 - 15;
                if( K < 16){
                    load-("stuff/tile_" & K & ".png")-as-("tile_" & K);
                    blend-it-glassy;
                }else{
                    make-"tile_16";
                }
                teleport-it-to-X-Y;
            }
        }
        load-"stuff/cursor.png"-as-"cursor";



        hge->System_Start();

        hge->Texture_Free(bg.tex);
        vector<Thing>::iterator it = context::get_things().begin();
        vector<Thing>::iterator eit = context::get_things().end();
        for(; it != eit; ++it){
            if(it->visible){
                context::get_hge()->Texture_Free( (*it).picture.tex );
            }
        }
    }else{
        MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    hge->System_Shutdown();
    hge->Release();
    return 0;
}

