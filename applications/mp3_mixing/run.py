from pydub import AudioSegment

CROSS_FADE_MS = 5_000
SONG_1_SEG_START_MS = 0
SONG_1_SEG_END_MS = 35_000
SONG_2_SEG_START_MS = 25_000
SONG_2_SEG_END_MS = 240_000

FRAME_RATE_HZ = 44_100

# Load your audio (any formats pydub/ffmpeg supports)
song1 = AudioSegment.from_file("song1.mp3")
song2 = AudioSegment.from_file("song2.mp3")

# (Optional) Do your earlier trims here, e.g.:
song1 = song1[SONG_1_SEG_START_MS:SONG_1_SEG_END_MS]
song2 = song2[SONG_2_SEG_START_MS:SONG_2_SEG_END_MS]

# Make sure both have the same channels / sample rate (good practice)
song1 = song1.set_channels(2).set_frame_rate(FRAME_RATE_HZ)
song2 = song2.set_channels(2).set_frame_rate(FRAME_RATE_HZ)

# Crossfade length: 10 seconds, but never longer than the shortest track
xfade_ms = min(CROSS_FADE_MS, len(song1), len(song2))

# This does: song1 then song2, overlapping the last xfade_ms of song1
# with the first xfade_ms of song2
final = song1.append(song2, crossfade=xfade_ms)

final.export("halloween_2025_soundtrack.mp3", format="mp3")
