#include <Game/App.h>

using namespace UT;

UT::App::App()
	:wnd(def_width, def_height, "Unreal Tournament"),
	gfx(wnd.GetWidth(), wnd.GetHeight())
{
	gfx.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, float(wnd.GetHeight()) / float(wnd.GetWidth()), 0.5f, 100.0f));
}

winrt::IAsyncAction UT::App::InitializeAsync()
{
	co_await winrt::when_all(gfx.InitializeAsync(wnd.GetHandle()), 
		graph.InitializeAsync(gfx));
}

int UT::App::Go()
{
	float dt = 0.01f;
	while (true)
	{
		if (const auto a = wnd.ProcessMessages())
			return (int)a.value();
		DoFrame(dt);
	}
}
void UT::App::DoFrame(float dt)
{
	if (!wnd.IsActive())return;
	ProcessInput(dt);

	graph.Execute(gfx);
	gfx.EndFrame();
}

void App::ProcessInput(float dt)
{
	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
		case VK_INSERT:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			return;
		}
	}

	//if (!wnd.CursorEnabled())
	//{
	//	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	//	{
	//		dt *= 2;
	//	}
	//	if (wnd.kbd.KeyIsPressed('W'))
	//	{
	//		cam.Translate({ 0.0f,0.0f,dt });
	//	}
	//	if (wnd.kbd.KeyIsPressed('A'))
	//	{
	//		cam.Translate({ -dt,0.0f,0.0f });
	//	}
	//	if (wnd.kbd.KeyIsPressed('S'))
	//	{
	//		cam.Translate({ 0.0f,0.0f,-dt });
	//	}
	//	if (wnd.kbd.KeyIsPressed('D'))
	//	{
	//		cam.Translate({ dt,0.0f,0.0f });
	//	}
	//	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	//	{
	//		cam.Translate({ 0.0f,dt,0.0f });
	//	}
	//	if (wnd.kbd.KeyIsPressed('C'))
	//	{
	//		cam.Translate({ 0.0f,-dt,0.0f });
	//	}
	//}

	//while (const auto delta = wnd.mouse.ReadRawDelta())
	//{
	//	if (!wnd.CursorEnabled())
	//	{
	//		cam.Rotate((float)delta->x, (float)delta->y);
	//	}
	//}
}