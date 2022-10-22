//
// Created by lolpie on 10/21/22.
//

namespace gui
{
    class slider: gui_object
    {
        sh_p<Texture> picker_texture;
    public:
        double min_value = 0;
        double max_value = 1;
        double step = 0.01;
        double current_value = 0;

        slider(Point position, Point size, sh_p<texture::slider> new_texture):
            gui_object(position, size, new_texture->get_slider()){}
    };
}
