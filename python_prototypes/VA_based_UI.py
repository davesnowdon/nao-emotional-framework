''' A simple UI that shows a valence arousal (VA) graph with 6 universal emotion touch points.
	Will write values to NAO memory.

'''


from kivy.app import App
from kivy.uix.widget import Widget
from kivy.graphics import Color, Ellipse, Line
from kivy.uix.floatlayout import FloatLayout
from kivy.lang import Builder

from kivy.uix.gridlayout import GridLayout
from kivy.uix.image import Image
from kivy.properties import ObjectProperty

from kivy.uix.button import Button
from kivy.uix.label import Label


class emotionWidget(Widget):

	def __init__(self, **kwargs):
		super(emotionWidget, self).__init__(**kwargs)
		with self.canvas:
			Line(points=[400, 0, 400, 600], width = 1)
			Line(points=[0, 300, 800, 300], width = 1)
			Label(text = 'valence')


class emotionApp(App):

	def build(self):
		parent = Widget()
		grid = emotionWidget()
		happy_btn = Button(text = 'happy', pos = (700, 500), size = (50, 50))
		angry_btn = Button(text = 'angry', pos = (100, 500), size = (50, 50))
		surprise_btn = Button(text = 'surprise', pos = (375, 400), size = (50, 50))
		disgust_btn = Button(text = 'disgust', pos = (200, 350), size = (50, 50))
		think_btn = Button(text = 'think', pos = (450, 275), size = (50, 50))
		fear_btn = Button(text = 'fear', pos = (50, 275), size = (50, 50))
		sad_btn = Button(text = 'sad', pos = (100, 100), size = (50, 50))
		label_valence = Label(text = 'valence', pos = (700, 225))
		label_arousal = Label(text = 'arousal', pos = (400, 0))


		parent.add_widget(grid)
		parent.add_widget(happy_btn)
		parent.add_widget(angry_btn)
		parent.add_widget(surprise_btn)
		parent.add_widget(disgust_btn)
		parent.add_widget(think_btn)
		parent.add_widget(fear_btn)
		parent.add_widget(sad_btn)
		parent.add_widget(label_valence)
		parent.add_widget(label_arousal)

		def happy(obj):
			print "happy"

		def angry(obj):
			print "angry"

		def surprise(obj):
			print "surprise"

		def disgust(obj):
			print "disgust"

		def think(obj):
			print "think"

		def fear(obj):
			print "fear"

		def sad(obj):
			print "sad"
			
		happy_btn.bind(on_release=happy)
		angry_btn.bind(on_release=angry)
		surprise_btn.bind(on_release=surprise)
		disgust_btn.bind(on_release=disgust)
		think_btn.bind(on_release=think)
		fear_btn.bind(on_release=fear)
		sad_btn.bind(on_release=sad)


		return parent


if __name__ == "__main__":
	emotionApp().run()


