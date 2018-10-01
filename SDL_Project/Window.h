
class Window {
private:
	struct SDL_Window* window;   
	struct SDL_Surface* screenSurface;
	int width, height;
	
public:
	char *windowName;
	Window(int width_, int height_, char * windowName_ );
	~Window();
	bool OnCreate();
	void OnDestroy();
	SDL_Window* GetSDL_Window();
};

