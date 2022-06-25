//
// Created by lolpie on 25.06.22.
//

namespace parent_stage_class
{
    using namespace std;
    using namespace sf;
    using namespace objects;

    class parent_stage
    {
    private:

    protected:
        sh_p<RenderWindow> window;
        sh_p<info::render> render;
        info::gui gui;
        map<string, sh_p<info::parent>>* main_info;
        virtual void before_events(){}
        virtual void after_events(){}
        virtual void before_start(){}
        virtual void after_end(){}
        virtual void init_gui_objects(){}
        virtual void init_event_objects(){}
        void add_scale()
        {
            for(gui_objects* i : gui.objects)
            {
                i->scale(*window);
                new event::scale(i, window, gui.event_manager);
            }
        }
    public:
        parent_stage(map<string, sh_p<info::parent>>& main_info)
        {
            this->main_info = &main_info;
            window = info::get_info<info::render>(main_info, "render")->window;
            render = info::get_info<info::render>(main_info, "render");
        }
        virtual void main()
        {
            init_gui_objects();
            init_event_objects();

            before_start();
            while (window->isOpen())
            {
                before_events();
                Event event;
                while (window->pollEvent(event))
                {
                    render->event_manager.notify(event);
                    gui.event_manager.notify(event);
                }
                after_events();
                window->clear();
                gui.draw(*window);
                window->display();
            }
            after_end();
        }
    };

}