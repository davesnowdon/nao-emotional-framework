from kivy.app import App
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.image import Image
from kivy.properties import ObjectProperty
from kivy.lang import Builder

from kivy.graphics import Color, Ellipse


Builder.load_string('''
<CustomLayout>
    canvas.before:
        BorderImage:
            # BorderImage behaves like the CSS BorderImage
            border: 10, 10, 10, 10
            texture: self.background_image.texture
            pos: self.pos
            size: self.size

<RootWidget>
    CustomLayout:
        size_hint: .9, .9
        pos_hint: {'center_x': .5, 'center_y': .5}
        rows:1
        
''')


class CustomLayout(GridLayout):

    background_image = ObjectProperty(
        Image(
            source='VA_emotion_graph_background_for_kivy_UI.jpg'))


class RootWidget(FloatLayout):
    def on_touch_down(self, touch):
        print (touch)

        with self.canvas:
            Color(1, 1, 1)
            d = 30.
            Ellipse(pos=(touch.x - d / 2, touch.y - d / 2), size = (d, d))

    def on_touch_up(self, touch):
        self.canvas.clear()


class MainApp(App):

    def build(self):
        return RootWidget()

if __name__ == '__main__':
    MainApp().run()