import random
import pyttsx3
import time

with open("./lines.txt", "r", encoding="utf-8") as file:
    lines = file.readlines()
random_line = random.choice(lines).strip()

engine = pyttsx3.init()
voices = engine.getProperty("voices")
japanese_voice_found = False

for voice in voices:
    print(voice.name)
    if "Japanese" in voice.name:
        engine.setProperty("voice", voice.id)
        japanese_voice_found = True
        break

if not japanese_voice_found:
    print("no japanese voice found!")
    exit()

engine.setProperty("rate", 120)

words = random_line.split()
for word in words:
    engine.say(word)
    engine.runAndWait()
    time.sleep(0.5)

_ = input("Press Enter to continue...")

print(f"Selected line: {random_line}")