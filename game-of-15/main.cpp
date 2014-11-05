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
HTEXTURE	cursor_texture;
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

    vector<Thing>::iterator it = context::get_things().begin();
	vector<Thing>::iterator eit = context::get_things().end();
	for(; it != eit; ++it){
        (*it).Update();
	}

    float Mouse_x;
    float Mouse_y;
    context::get_hge()->Input_GetMousePos(&Mouse_x, &Mouse_y);
    teleport-"cursor"-to-Mouse_x-Mouse_y;

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
        bg.blend=BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;
		for(int i=0;i<4;i++){
			bg.v[i].z=0.5f;
			bg.v[i].col=0xFFFFA000;
		}
		bg.v[0].tx=0.0f; bg.v[0].ty=0.0f;
		bg.v[1].tx=1.0f; bg.v[1].ty=0.0f;
		bg.v[2].tx=1.0f; bg.v[2].ty=1.0f;
		bg.v[3].tx=0.0f; bg.v[3].ty=1.0f;

        for(the I : {0, 1, 2, 3}){
            for(the J : {0, 1, 2, 3}){
                the K = I * 4 + J + 1;
                if( K < 16){
                    the X = 185 + J * 105;
                    the Y = 85 + I * 105;
                    load-("stuff/tile_" & K & ".png")-as-("tile_" & K);
                    teleport-it-to-X-Y;
                }
            }
        }
        load-"stuff/cursor.png"-as-"cursor";

		hge->System_Start();

		hge->Texture_Free(bg.tex);
		vector<Thing>::iterator it = context::get_things().begin();
        vector<Thing>::iterator eit = context::get_things().end();
        for(; it != eit; ++it){
            context::get_hge()->Texture_Free( (*it).picture.tex );
        }
	}else{
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	hge->System_Shutdown();
	hge->Release();
	return 0;
}

