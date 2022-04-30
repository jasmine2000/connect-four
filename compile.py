from os import path

prefix = "/usr/bin/clang -fdiagnostics-color=always -g"
directory = "/Users/jasminewu/Documents/6115/game"

files = ["main", "setup", "gameplay", "leaderboard", "fake_tft"]

suffix = "-o /Users/jasminewu/Documents/6115/game/main"

segments = []
segments.append(prefix)

for file in files:
    segments.append(path.join(directory, file + ".c"))

segments.append(suffix)

print(" ".join(segments))