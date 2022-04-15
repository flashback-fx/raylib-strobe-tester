#include <raylib.h>
#include <stdbool.h>

#define TIME_LIMIT 30.0

#define VIDEO_WIDTH 320
#define VIDEO_HEIGHT 240
#define SCALE 3
#define SCREEN_WIDTH VIDEO_WIDTH * SCALE
#define SCREEN_HEIGHT VIDEO_HEIGHT * SCALE

#define RECTANGLE_POSITION_X 50
#define RECTANGLE_POSITION_Y 50
#define RECTANGLE_WIDTH 150
#define RECTANGLE_HEIGHT 150

static RenderTexture2D framebuffer = {0};
static int target_fps = 60;
static bool showing_fps = true;

static void init_screen();
static void set_target_fps(int fps);
static void render_fps_counter(int x, int y);

int main(void)
{
	Color strobe[] = {BLACK, BROWN};
	bool strobe_flashing = true;

	init_screen();

	while (!WindowShouldClose() && GetTime() < TIME_LIMIT) {
		if (IsKeyPressed(KEY_ONE)) {
			set_target_fps(60);
		}
		if (IsKeyPressed(KEY_TWO)) {
			set_target_fps(0);
		}
		if (IsKeyPressed(KEY_THREE)) {
			showing_fps = !showing_fps;
		}

		strobe_flashing = !strobe_flashing;

		BeginTextureMode(framebuffer);
			ClearBackground(BLACK);
			DrawRectangle(
				RECTANGLE_POSITION_X,
				RECTANGLE_POSITION_Y,
				RECTANGLE_WIDTH,
				RECTANGLE_HEIGHT,
				strobe[strobe_flashing]
			);
			if (showing_fps) {
				render_fps_counter(20, 20);
			}
		EndTextureMode();

		BeginDrawing();
			DrawTexturePro(
				framebuffer.texture,
				(Rectangle){
					.x = 0.0f,
					.y = 0.0f,
					.width = VIDEO_WIDTH,
					.height = -VIDEO_HEIGHT
				},
				(Rectangle){
					.x = 0.0f,
					.y = 0.0f,
					.width = SCREEN_WIDTH,
					.height = SCREEN_HEIGHT
				},
				(Vector2){
					0.0f,
					0.0f
				},
				0.0f,
				WHITE
			);
		EndDrawing();
	}

	UnloadRenderTexture(framebuffer);
	CloseWindow();

	return 0;
}

static void init_screen()
{
#ifdef VSYNC
	SetConfigFlags(FLAG_VSYNC_HINT);
#endif
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "strobe");
	SetTargetFPS(target_fps);
	framebuffer = LoadRenderTexture(VIDEO_WIDTH, VIDEO_HEIGHT);
}

static void set_target_fps(int fps)
{
	target_fps = fps;
	SetTargetFPS(target_fps);
}

static void render_fps_counter(int x, int y)
{
	#define FONT_SIZE 10

	DrawText(TextFormat("%6d", GetFPS()), x, y - FONT_SIZE, FONT_SIZE, GREEN);
	DrawText("FPS", x, y - FONT_SIZE * 2, FONT_SIZE, GREEN);
}
