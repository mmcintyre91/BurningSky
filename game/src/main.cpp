#include <memory>


#include "BurningSky/Core/Application.h"
#include "GameLayer.h"


class BurningSkyGameApp : public BurningSky::Application {
	
public:
	BurningSkyGameApp() 
	{
		PushLayer(std::make_unique<BurningSky::GameLayer>());
	}
};

int main()
{
	BurningSkyGameApp app;
	app.Run();
	return 0;
}