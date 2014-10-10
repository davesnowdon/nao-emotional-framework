''' A simple UI that shows a valence arousal (VA) graph with 6 universal emotion touch points.
    Will write values to NAO memory.

'''

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.graphics import Color, Ellipse, Line
from kivy.uix.button import Button
from kivy.uix.label import Label

from naoqi import ALProxy

NAO_IP = 'mistcalf.local'

# Global variables for proxies.
memory = None

class emotionWidget(Widget):

    global memory
    
    def __init__(self, **kwargs):
        super(emotionWidget, self).__init__(**kwargs)

        with self.canvas:
            Line(points=[400, 0, 400, 600], width = 1)
            Line(points=[0, 300, 800, 300], width = 1)
            Label(text = 'valence')


class emotionApp(App):

    global memory

    def build(self):

        emotional_dictionary = {"happiness" : (1.00, 0.75),
                            "sadness" : (-0.75, -0.75),
                            "anger" : (-0.75, 0.75),
                            "fear" : (-1.00, 0.00),
                            "surprise" : (0.00, 0.50),
                            "disgust" : (-0.4, 0.25),
                            "thinking" : (0.25, 0.00)
                             }

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
            key = "happiness"
            valence = emotional_dictionary[key][0]
            arousal = emotional_dictionary[key][1]
            current_emotion = [(valence, arousal), ("valence_mood", "arousal_mood"), ("personality"), (key, "param2")]
            memory.insertData("Emotion/Current", current_emotion)
            print "emotion: ", memory.getData("Emotion/Current")

        def angry(obj):
            key = "anger"
            valence = emotional_dictionary[key][0]
            arousal = emotional_dictionary[key][1]
            current_emotion = [(valence, arousal), ("valence_mood", "arousal_mood"), ("personality"), (key, "param2")]
            memory.insertData("Emotion/Current", current_emotion)
            print "emotion: ", memory.getData("Emotion/Current")

        def surprise(obj):
            key = "surprise"
            valence = emotional_dictionary[key][0]
            arousal = emotional_dictionary[key][1]
            current_emotion = [(valence, arousal), ("valence_mood", "arousal_mood"), ("personality"), (key, "param2")]
            memory.insertData("Emotion/Current", current_emotion)
            print "emotion: ", memory.getData("Emotion/Current")

        def disgust(obj):
            key = "disgust"
            valence = emotional_dictionary[key][0]
            arousal = emotional_dictionary[key][1]
            current_emotion = [(valence, arousal), ("valence_mood", "arousal_mood"), ("personality"), (key, "param2")]
            memory.insertData("Emotion/Current", current_emotion)
            print "emotion: ", memory.getData("Emotion/Current")

        def think(obj):
            key = "thinking"
            valence = emotional_dictionary[key][0]
            arousal = emotional_dictionary[key][1]
            current_emotion = [(valence, arousal), ("valence_mood", "arousal_mood"), ("personality"), (key, "param2")]
            memory.insertData("Emotion/Current", current_emotion)
            print "emotion: ", memory.getData("Emotion/Current")

        def fear(obj):
            key = "fear"
            valence = emotional_dictionary[key][0]
            arousal = emotional_dictionary[key][1]
            current_emotion = [(valence, arousal), ("valence_mood", "arousal_mood"), ("personality"), (key, "param2")]
            memory.insertData("Emotion/Current", current_emotion)
            print "emotion: ", memory.getData("Emotion/Current")

        def sad(obj):
            key = "sadness"
            valence = emotional_dictionary[key][0]
            arousal = emotional_dictionary[key][1]
            current_emotion = [(valence, arousal), ("valence_mood", "arousal_mood"), ("personality"), (key, "param2")]
            memory.insertData("Emotion/Current", current_emotion)
            print "emotion: ", memory.getData("Emotion/Current")
            
        happy_btn.bind(on_release=happy)
        angry_btn.bind(on_release=angry)
        surprise_btn.bind(on_release=surprise)
        disgust_btn.bind(on_release=disgust)
        think_btn.bind(on_release=think)
        fear_btn.bind(on_release=fear)
        sad_btn.bind(on_release=sad)


        return parent

def NAO_setup():
    global memory

    try:
        memory = ALProxy("ALMemory", NAO_IP, 9559)
    except Exception, e:
        print 'Could not setup ALMemory, error: ', e


def main():
    NAO_setup()
    emotionApp().run()

if __name__ == "__main__":
    main()


