# Biscuit
Biscuit是一个轻量级的，C/C++环境下基于OpenGL的2D游戏引擎/框架

**如何构建工程文件？**

运行generateProjects，之后会自动生成解决方案，您可以使用Rider、Visuial Studio等IDE打开生成的biscuit.sln

其中，Biscuit项目为引擎源项目，Sandbox为您的游戏项目
## 开始
要实现一个最简单的游戏，您可以打开 Sandbox/Sandbox.cpp 并编辑：

```C++
#include "Biscuit.h"
using namespace Biscuit;

class Sandbox : public Application
{
public:
    std::shared_ptr<Sprite> gameObj = nullptr;

    void OnInit() override 
    {
        // Sprite的生成依赖材质，材质需要在程序最开始生成
        LoadTextureFromFile("本地图片路径", "111");
    }

    void OnGameStart() override
	{
        // 通过调用Sprite的工厂函数生成Sprite游戏对象并获得指针
        gameObj = Sprite::Create(GetTexture("111"));

        // 将您的Sprite游戏对象添加到场景
        AddSprite(gameObj);
    }
}

// 声明创建一个游戏程序对象
Application* CreateApplication()
{
	return new Sandbox();
}
```

如果您的程序编译成功，则您可以在游戏窗口中心看到您的游戏对象。

## Sprite及其生命周期
Biscuit引擎推荐进行组合式编程，如果您需要为游戏对象编写行为脚本，您可以编写类似下面的程序
```C++
gameObj->OnUpdate([=]()
{
    float speed = 300;
    if (Input::IsKeyPressed(KEY_W))
    {
        gameObj->SetPos(gameObj->GetPos() + Vec2(0, -speed * deltaTime));
    }
    if (Input::IsKeyPressed(KEY_A))
    {
        gameObj->SetPos(gameObj->GetPos() + Vec2(-speed * deltaTime, 0 ));
    }
    if (Input::IsKeyPressed(KEY_S))
    {
        gameObj->SetPos(gameObj->GetPos() + Vec2(0, speed * deltaTime));
    }
    if (Input::IsKeyPressed(KEY_D))
    {
        gameObj->SetPos(gameObj->GetPos() + Vec2(speed * deltaTime, 0 ));
    }
});
```
这段代码使您的Sprite可以响应按键进行四向移动，其中OnUpdate()每帧被调用，接受一个void()回调函数作为参数。

同时，Biscuit保留了继承式编程的方法，您可以创建自己的Sprite子类，并重写InOnUpdate()方法。
***

### Sprite具有以下生命周期钩子：
### OnClick(void(Vec2))
鼠标点击后触发，接受鼠标点击时的二维坐标为参数（需要 **SetCollidable(true)**）

### OnUpdate(void())
每帧触发

### OnCreated(void())
被构造后触发

### OnAttachedToScene(void())
被添加至场景中时触发

### OnRemoved(void())
被移除时触发

### OnCollision(void(std::shared_ptr<Sprite>))
与其他Sprite碰撞后触发，接受与其碰撞的对象指针作为参数（需要 **SetCollidable(true)**）



与重写InOnUpdate()同理，您在创建自己的Sprite子类时可以重写 InOnClick(Vec2) 等

## Biscuit引擎中的GUI
所有GUI API在Biscuit::BCUI命名空间下

以下代码创建并显示了一个简单的UI层
```C++
#include "Biscuit.h"

using namespace Biscuit;

class Sandbox : public Application
{
public:
    Sandbox(const Window::WindowProps& props):Application(props){}

    void OnInit() override
    {
        LoadFontFromFile("C:\\Windows\\Fonts\\Impact.ttf","Impact");
    }
	
    void OnGameStart() override
    {
        auto ui = new BCUI::BCUI();
		
        auto label = new BCUI::Label(Vec2(400,320),Vec2(400,100));
        label->SetText("Label");
        label->SetLabelFont(GetFont("Impact"), 42);
		
        auto button = new BCUI::Button(Vec2(500,300),Vec2(400,100));
        button->SetLabelFont(GetFont("Impact"), 20);
        button->OnClick([]()
        {
            BC_TRACE("Clicked!");
        });
              
        ui->Add(label);
        ui->Add(button);
        PushOverLay(ui);
    }
};

Biscuit::Application* Biscuit::CreateApplication()
{
    Window::WindowProps* props = new Window::WindowProps("Game",1920,1080);
    return new Sandbox(*props);
}

```
这个程序生成了一个1920*1080的窗口，并在其中生成了自定义字体的标签和按钮，按下按钮后控制台会输出“Clicked!”字样。

**与加载材质相同，字体的加载也应该放在游戏的初始化阶段**