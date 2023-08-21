import webbrowser
from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.image import Image
from kivy.uix.label import Label

class FirstScreen(Screen):
    def __init__(self, **kwargs):
        super(FirstScreen, self).__init__(**kwargs)
        layout = BoxLayout(orientation='vertical')
        btn1 = Button(text='Go to Screen 2')
        btn1.bind(on_press=self.change_screen)
        layout.add_widget(btn1)
        btn2 = Button(text='Go to Screen 3')
        btn2.bind(on_press=self.change_screen)
        layout.add_widget(btn2)
        btn3 = Button(text='Go to Screen 4')
        btn3.bind(on_press=self.change_screen)
        layout.add_widget(btn3)
        self.add_widget(layout)
    
    def change_screen(self, instance):
        if instance.text == 'Go to Screen 2':
            self.manager.current = 'screen2'
        elif instance.text == 'Go to Screen 3':
            self.manager.current = 'screen3'
        elif instance.text == 'Go to Screen 4':
            self.manager.current = 'screen4'

class OtherScreen(Screen):
    def __init__(self, **kwargs):
        super(OtherScreen, self).__init__(**kwargs)
        layout = BoxLayout(orientation='vertical')
        btn = Button(text='Back to Home Screen')
        btn.bind(on_press=self.change_screen)
        layout.add_widget(btn)
        self.add_widget(layout)
    
    def change_screen(self, instance):
        self.manager.current = 'screen1'

class SecondScreen(OtherScreen):
    def __init__(self, **kwargs):
        super(SecondScreen, self).__init__(**kwargs)
        btn = Button(text='Go to URL')
        btn.bind(on_press=self.open_url)
        self.children[0].add_widget(btn)
    
    def open_url(self, instance):
        webbrowser.open('http://10.0.0.32')

class ThirdScreen(OtherScreen):
    def __init__(self, **kwargs):
        super(ThirdScreen, self).__init__(**kwargs)
        img = Image(source='path_to_your_image.png') # Add the path to your image file
        self.children[0].add_widget(img)

class FourthScreen(OtherScreen):
    def __init__(self, **kwargs):
        super(FourthScreen, self).__init__(**kwargs)
        lbl = Label(text='Your Text String')
        self.children[0].add_widget(lbl)

class ScreenManagement(ScreenManager):
    def __init__(self, **kwargs):
        super(ScreenManagement, self).__init__(**kwargs)
        self.add_widget(FirstScreen(name='screen1'))
        self.add_widget(SecondScreen(name='screen2'))
        self.add_widget(ThirdScreen(name='screen3'))
        self.add_widget(FourthScreen(name='screen4'))

class MyApp(App):
    def build(self):
        return ScreenManagement()

if __name__ == '__main__':
    MyApp().run()
