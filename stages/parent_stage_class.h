//
// Created by lolpie on 25.06.22.
//

namespace parent_stage_class
{
    using namespace std;
    using namespace sf;
    using namespace objects_np;

    class parent_stage
    {
    private:
    public:
        info::stage_elements elements;
        sh_p<RenderWindow> window;
        sh_p<info::render> render;
        map<string, sh_p<info::parent>>* main_info;
    protected:
        virtual void before_events(){}
        virtual void after_events(){}
        virtual void before_start(){}
        virtual void after_end(){}
        virtual void init_gui_objects(){}
        virtual void init_game_objects(){}
        virtual void init_event_objects(){}
    public:
        parent_stage(map<string, sh_p<info::parent>>& main_info)
        {
            this->main_info = &main_info;
            window = info::get_info<info::render>(main_info, "render")->window;
            render = info::get_info<info::render>(main_info, "render");
            elements = info::stage_elements(window);
        }
        virtual void main()
        {
            init_gui_objects();
            init_game_objects();
            init_event_objects();

            before_start();
            while (window->isOpen())
            {
                before_events();
                Event event;
                while (window->pollEvent(event))
                {
                    render->event_manager.notify(event);
                    elements.event_manager.notify(event);
                }
                after_events();
                elements.move();
                window->clear();
                elements.draw();
                window->display();
            }
            after_end();
        }
    };

}