from pynput.mouse import Listener, Button
import time
import os


INDEX = 6
DATA_ROOT = "CLICKTIME"
counter = 1

dirs = rf'{DATA_ROOT}/time/{INDEX}'

if not os.path.exists(dirs):
    os.makedirs(dirs)

save_file = rf'{dirs}/time.txt'
if os.path.exists(save_file):
    raise FileExistsError("File Exsist. CHECK YOUR INDEX !!!")

def on_click(x, y, button, pressed):
    global counter
    if button in [Button.left, Button.right] and pressed:
        with open(save_file, 'a') as f:
            print(f"Counter:{counter}")
            counter += 1
            click_time = time.time()
            button_type = 'L' if button == Button.left else 'R'
            f.write(f'{button_type}:{click_time}\n')

with Listener(on_click=on_click) as listener:
    listener.join()