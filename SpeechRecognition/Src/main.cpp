
#include"real_sence.hpp"
#include"window.hpp"
#include"input.hpp"
#include"log.hpp"
#include"utils.hpp"

using namespace Prizm;

void messageLoop(void)
{
	MSG msg = {};

	RealSence real_sence;
	real_sence.initialize();

	while (true)
	{
		if (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}

		if (Input::isKeyTriggered("escape"))
		{
			if (Input::isMouseCaptured())
			{
				Input::captureMouse(Window::getWindowHandle(), false);
			}
			else
			{
				if (MessageBoxA(Window::getWindowHandle(), "Quit ?", "User Notification", MB_YESNO | MB_DEFBUTTON2) == IDYES)
				{
					Log::info("[EXIT] KEY DOWN ESC");
					break;
				}
			}
		}

		if (Input::isKeyTriggered("1"))
			real_sence.startRec();

		if (Input::isKeyTriggered("2"))
			real_sence.stopRec();

		if (msg.message == WM_QUIT)	break;

		Input::postStateUpdate();
	}

	real_sence.finalize();
}

void initialize(void)
{
	std::string workspace_directory = DirectoryUtils::getSpecialFolderPath(DirectoryUtils::FolderType::APPDATA) + "\\Prizm";
	Log::initialize(Log::LogMode::CONSOLE, workspace_directory);

	Input::initialize();

	Window::initialize();
}

void finalize(void)
{
	Window::finalize();

	Log::finalize();
}

int main(void)
{
	initialize();

	messageLoop();

	finalize();

	return 0;
}